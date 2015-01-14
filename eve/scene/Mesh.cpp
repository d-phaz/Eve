
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

#ifndef __EVE_SCENE_SKELETON_H__
#include "eve/scene/Skeleton.h"
#endif


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
	, m_pSkeleton(nullptr)
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
			EVE_LOG_ERROR("Unable to load selected scene mesh, Texture Coordinates are missing.");
			ret = false;
		}

		if (!m_pAiMesh->HasNormals())
		{
			EVE_LOG_ERROR("Unable to load selected scene mesh, Normals Coordinates are missing.");
			ret = false;
		}
	}

	// If scene node found and mesh contains required data.
	if (ret)
	{
		/////////////////////////////////////////
		//	MESH
		/////////////////////////////////////////

		// In scene mesh name. 
		m_name = std::string(m_pAiMesh->mName.C_Str());

		// Mesh base data.
		int32_t	numVertices = m_pAiMesh->mNumVertices;
		int32_t numFaces	= m_pAiMesh->mNumFaces;
		int32_t numIndices	= numFaces * 3;

		// Allocate arrays memory.
		float *  pVertices = (float*)malloc(numVertices * 8 * sizeof(float));
		GLuint * pIndices  = (GLuint*)malloc(numIndices * sizeof(GLuint));

		float min_x = 0.0f;
		float min_y = 0.0f;
		float min_z = 0.0f;

		float max_x = 0.0f;
		float max_y = 0.0f;
		float max_z = 0.0f;

		float cur_x = 0.0f;
		float cur_y = 0.0f;
		float cur_z = 0.0f;

		// Denver style.
		aiVector3D * ai_vert = m_pAiMesh->mVertices - 1;
		aiVector3D * ai_texc = m_pAiMesh->mTextureCoords[0] - 1;
		aiVector3D * ai_norm = m_pAiMesh->mNormals - 1;

		// Run threw vertices and copy data.
		float * vert = pVertices - 1;
		for (int32_t j = 0; j < numVertices; j++)
		{
			cur_x = (*++ai_vert).x;
			cur_y =   (*ai_vert).y;
			cur_z =   (*ai_vert).z;

			// Positions
			*++vert = cur_x;
			*++vert = cur_y;
			*++vert = cur_z;
			// Bounding box
			if (cur_x < min_x)		{ min_x = cur_x; }
			else if (cur_x > max_x)	{ max_x = cur_x; }
			if (cur_y < min_y)		{ min_y = cur_y; }
			else if (cur_y > max_y)	{ max_y = cur_y; }
			if (cur_z < min_z)		{ min_z = cur_z; }
			else if (cur_z > max_z)	{ max_z = cur_z; }

			// Texture coordinates
			*++vert = (*++ai_texc).x;
			*++vert =   (*ai_texc).y;
			// Normals
			*++vert = (*++ai_norm).x;
			*++vert =   (*ai_norm).y;
			*++vert =   (*ai_norm).z;
		}
		// Bounding box
		//m_pBox = gl::Box3DCornered::create_ptr(Vec3f(min_x, min_y, min_z), Vec3f(max_x, max_y, max_z), UILayoutConfigColor::STAGE_BOUNDING_BOX);

		// Run threw indices and copy data.
		GLuint * ind = pIndices - 1;
		aiFace * ai_face = m_pAiMesh->mFaces - 1;
		for (int32_t j = 0; j < numFaces; j++)
		{
			*++ind = (*++ai_face).mIndices[0];
			*++ind =   (*ai_face).mIndices[1];
			*++ind =   (*ai_face).mIndices[2];
		}
		
		// Create VAO format.
		eve::ogl::FormatVao format;
		format.numVertices			= numVertices;
		format.numIndices			= numIndices;
		format.perVertexNumPosition = 3;
		format.perVertexNumDiffuse	= 2;
		format.perVertexNumNormal	= 3;
		format.vertices.reset(pVertices);
		format.indices.reset(pIndices);

		// TODO
		// Create VAO from scene renderer.

		// Skeleton.
		m_pSkeleton = eve::scene::Skeleton::create_ptr(p_pMesh, p_pScene, p_upAxis);


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
		//	MATERIAL
		/////////////////////////////////////////

// 		// Create material
// 		m_pMaterial = scene::ItemMaterial::create_ptr(this);
// 
// 		// Grab material
// 		if (p_pScene->HasMaterials())
// 		{
// 			aiMaterial * mat = p_pScene->mMaterials[m_pMesh->mMaterialIndex];
// 
// 			aiString path;
// 			std::string folderPath = NATIVESYSTEM::removeFileNameFromPath(p_fullPath);
// 			std::string fullPath;
// 
// 			if (aiGetMaterialString(mat, AI_MATKEY_TEXTURE_DIFFUSE(0), &path)/*mat->GetTexture(aiTextureType_DIFFUSE, 0, &path)*/ == AI_SUCCESS)
// 			{
// 				fullPath = folderPath + path.data;
// 				m_pMaterial->setTexDiffuse(fullPath);
// 			}
// 
// 			if (mat->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS)
// 			{
// 				fullPath = folderPath + path.data;
// 				m_pMaterial->setTexNormal(fullPath);
// 			}
// 
// 			if (mat->GetTexture(aiTextureType_EMISSIVE, 0, &path) == AI_SUCCESS)
// 			{
// 				fullPath = folderPath + path.data;
// 				m_pMaterial->setTexEmissive(fullPath);
// 			}
// 
// 			if (mat->GetTexture(aiTextureType_OPACITY, 0, &path) == AI_SUCCESS)
// 			{
// 				fullPath = folderPath + path.data;
// 				m_pMaterial->setTexOpacity(fullPath);
// 			}
// 
// 			float shininess = 0.0f;
// 			aiGetMaterialFloat(mat, AI_MATKEY_SHININESS_STRENGTH, &shininess); // AI_MATKEY_SHININESS
// 			m_pMaterial->setShininess(shininess);
// 		}

		this->init();
	}

	return ret;
}



//=================================================================================================
void eve::scene::Mesh::init(void)
{
	m_objectType = SceneObject_Mesh;

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
