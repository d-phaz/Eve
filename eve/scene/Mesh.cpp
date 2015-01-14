
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Main header
#include "eve/scene/Mesh.h"


//=================================================================================================
eve::scene::Mesh * eve::scene::Mesh::create_ptr(eve::scene::Object * p_pParent, const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath)
{
	EVE_ASSERT(p_pParent);
	EVE_ASSERT(p_pMesh);
	EVE_ASSERT(p_pScene);

	eve::scene::Mesh * ptr = new eve::scene::Mesh(p_pParent);
	if (!ptr->initFromAssimpMesh(p_pMesh, p_pScene, p_upAxis, p_fullPath))
	{
		EVE_RELEASE_PTR(ptr);
	}

	return ptr;
}



//=================================================================================================
eve::scene::Mesh::Mesh(eve::scene::Object * p_pParent)
	// Inheritance
	: eve::scene::Object(p_pParent)
	, eve::scene::EventListenerSceneObject()
	, eve::math::TMesh<float>()

	// Members init
	, m_pVao(nullptr)
	, m_pAiMesh(nullptr)

	, m_numBones(0)
	, m_pBoneIndices(nullptr)
	, m_pWeights(nullptr)
{}



//=================================================================================================
bool eve::scene::Mesh::initFromAssimpMesh(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath)
{
	// Grab scene node. 
	const aiNode * pRoot = p_pScene->mRootNode;
	const aiNode * pNode = pRoot->FindNode(m_name.c_str());

	// Test scene node.
	bool ret = pNode != NULL;
	EVE_ASSERT(ret);

	// Stock mesh pointer.
	m_pAiMesh = p_pMesh;
	// Test mesh integrity.
	if (!m_pAiMesh->HasFaces() || !m_pAiMesh->HasPositions())
	{
		ret = false;
	}
	if (ret)
	{
		if (!m_pAiMesh->HasTextureCoords(0))
		{
			//NATIVESYSTEM::createErrorWindow("Loading error.", "Unable to load selected scene mesh, Texture Coordinates are missing.");
			ret = false;
		}

		if (!m_pAiMesh->HasNormals())
		{
			//NATIVESYSTEM::createErrorWindow("Loading info.", "Unable to load selected scene mesh, Normals Coordinates are missing.");
			ret = false;
		}
	}

	// If scene node found and mesh contains required data.
	if (ret)
	{
		/////////////////////////////////////////
		//	MATRIX
		/////////////////////////////////////////

		aiMatrix4x4 mat;
		while (pNode != pRoot)
		{
			mat = pNode->mTransformation * mat;
			pNode = pNode->mParent;
		}
		//aiMatrix4x4 mat	= pNode->mTransformation;
		eve::math::TMatrix44<float> matrix(mat.a1, mat.b1, mat.c1, mat.d1
										 , mat.a2, mat.b2, mat.c2, mat.d2
										 , mat.a3, mat.b3, mat.c3, mat.d3
										 , mat.a4, mat.b4, mat.c4, mat.d4);
		// Correct Up Axis if needed.
		if (p_upAxis == Axis_Z)
		{
			matrix.fromZupToYup();
		}
		// Invert matrix to retrieve camera view coordinates.
		matrix.invert();

		// Extract camera data from model view matrix.
		eve::math::TVec3<float> target, worldUp;
		eve::math::get_look_at(matrix, m_translation, target, worldUp);

		eve::math::TVec3<float> viewDirection = (target - m_translation).normalized();
		eve::math::TQuaternion<float> orientation = eve::math::TQuaternion<float>(eve::math::TMatrix44<float>::alignZAxisWithTarget(-viewDirection, worldUp)).normalized();

		// Grab rotation.
		m_rotation.x = orientation.getPitch();
		m_rotation.y = orientation.getYaw();
		m_rotation.z = orientation.getRoll();


		/////////////////////////////////////////
		//	MESH
		/////////////////////////////////////////
	}

	this->init();

	return ret;
}



//=================================================================================================
void eve::scene::Mesh::init(void)
{
	// Call parent class
	eve::scene::Object::init();
	eve::math::TMesh<float>::init();
}

//=================================================================================================
void eve::scene::Mesh::release(void)
{
	m_pVao->requestRelease();
	m_pVao = nullptr;

	// Do not delete -> shared pointer.
	m_pAiMesh = nullptr;

	EVE_RELEASE_PTR_C_SAFE(m_pBoneIndices);
	EVE_RELEASE_PTR_C_SAFE(m_pWeights);

	// Call parent class
	eve::scene::Object::release();
	eve::math::TMesh<float>::release();
}



//=================================================================================================
void eve::scene::Mesh::cb_evtSceneObject(eve::scene::EventArgsSceneObject & p_args)
{
	switch (p_args.type)
	{
	case SceneObjectEventType_RotateX:				this->rotateX(p_args.value);				break;
	case SceneObjectEventType_RotateY:				this->rotateY(p_args.value);				break;
	case SceneObjectEventType_RotateZ:				this->rotateZ(p_args.value);				break;

	case SceneObjectEventType_TranslateX:			this->translateX(p_args.value);				break;
	case SceneObjectEventType_TranslateY:			this->translateY(p_args.value);				break;
	case SceneObjectEventType_TranslateZ:			this->translateZ(p_args.value);				break;

	case SceneObjectEventType_ScaleX:				this->scaleX(p_args.value);					break;
	case SceneObjectEventType_ScaleY:				this->scaleY(p_args.value);					break;
	case SceneObjectEventType_ScaleZ:				this->scaleZ(p_args.value);					break;


	case SceneObjectEventType_SetRotationX:			this->setRotationX(p_args.value);			break;
	case SceneObjectEventType_SetRotationY:			this->setRotationY(p_args.value);			break;
	case SceneObjectEventType_SetRotationZ:			this->setRotationZ(p_args.value);			break;

	case SceneObjectEventType_SetTranslationX:		this->setTranslationX(p_args.value);		break;
	case SceneObjectEventType_SetTranslationY:		this->setTranslationY(p_args.value);		break;
	case SceneObjectEventType_SetTranslationZ:		this->setTranslationZ(p_args.value);		break;

	case SceneObjectEventType_SetScaleX:			this->setScaleX(p_args.value);				break;
	case SceneObjectEventType_SetScaleY:			this->setScaleY(p_args.value);				break;
	case SceneObjectEventType_SetScaleZ:			this->setScaleZ(p_args.value);				break;


	default: EVE_ASSERT_FAILURE; break;
	}
}



//=================================================================================================
void eve::scene::Mesh::oglDraw(void)
{
	m_pVao->draw();
}
