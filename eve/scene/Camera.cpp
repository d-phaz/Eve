
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
#include "eve/scene/Camera.h"

#ifndef __EVE_SCENE_SCENE_H__
#include "eve/scene/Scene.h"
#endif

#ifndef __EVE_OPENGL_CORE_UNIFORM_H__
#include "eve/ogl/core/Uniform.h"
#endif

#ifndef __EVE_OPENGL_CORE_VAO_H__
#include "eve/ogl/core/Vao.h"
#endif


//=================================================================================================
eve::scene::Camera * eve::scene::Camera::create_ptr(eve::scene::Scene *		p_pParentScene
												  , eve::scene::Object *	p_pParent
												  , const aiCamera *		p_pCamera
												  , const aiScene *			p_pScene
												  , eve::Axis				p_upAxis)
{
	EVE_ASSERT(p_pParentScene);
	EVE_ASSERT(p_pCamera);
	EVE_ASSERT(p_pScene);

	eve::scene::Camera * ptr = new eve::scene::Camera(p_pParentScene, p_pParent);
	if (!ptr->initFromAssimpCamera(p_pCamera, p_pScene, p_upAxis))
	{
		EVE_RELEASE_PTR(ptr);
	}

	return ptr;
}



//=================================================================================================
eve::scene::Camera::Camera(eve::scene::Scene * p_pParentScene, eve::scene::Object * p_pParent)
	// Inheritance
	: eve::scene::Object(p_pParentScene, p_pParent, SceneObject_Camera)
	, eve::scene::EventListenerSceneCamera()
	, eve::math::TCamera<float>()

	// Members init
	, m_pAiCamera(nullptr)
	, m_pVao(nullptr)
	, m_pUniformMatrices(nullptr)
{}



//=================================================================================================
bool eve::scene::Camera::initFromAssimpCamera(const aiCamera * p_pCamera, const aiScene * p_pScene, eve::Axis p_upAxis)
{
	EVE_ASSERT(p_pCamera);
	EVE_ASSERT(p_pScene);

	// Grab scene node. 
	const aiNode * pRoot = p_pScene->mRootNode;
	const aiNode * pNode = pRoot->FindNode(m_name.c_str());

	// Test scene node.
	bool ret = pNode != NULL; 
	EVE_ASSERT(ret);

	if (ret)
	{
		m_pAiCamera = p_pCamera;

		// Loaded camera data copy.
		m_name = std::string(m_pAiCamera->mName.data);

		m_aspectRatio	= m_pAiCamera->mAspect;
		m_nearClip		= m_pAiCamera->mClipPlaneNear;
		m_farClip		= m_pAiCamera->mClipPlaneFar;
		m_frustumDepth	= m_farClip - m_nearClip;
		m_fov			= eve::math::toDegrees(m_pAiCamera->mHorizontalFOV);

		m_eyePoint.x	= m_pAiCamera->mPosition.x;
		m_eyePoint.y	= m_pAiCamera->mPosition.y;
		m_eyePoint.z	= m_pAiCamera->mPosition.z;

		m_worldUp.x		= m_pAiCamera->mUp.x;
		m_worldUp.y		= m_pAiCamera->mUp.y;
		m_worldUp.z		= m_pAiCamera->mUp.z;

		m_target.x		= m_pAiCamera->mLookAt.x;
		m_target.y		= m_pAiCamera->mLookAt.y;
		m_target.z		= m_pAiCamera->mLookAt.z;

		
		// Compute scene node matrix 
		aiMatrix4x4 mat;
		while (pNode != pRoot)
		{
			mat = pNode->mTransformation * mat;
			pNode = pNode->mParent;
		}
		eve::math::TMatrix44<float> matrix(mat.a1, mat.b1, mat.c1, mat.d1
										 , mat.a2, mat.b2, mat.c2, mat.d2
										 , mat.a3, mat.b3, mat.c3, mat.d3
										 , mat.a4, mat.b4, mat.c4, mat.d4);

		// Correct Up Axis if needed.
		if (p_upAxis == eve::Axis_Z)
		{
			matrix.fromZupToYup();
		}

		// Invert matrix to retrieve camera view coordinates.
		matrix.invert();

		// Extract camera data from model view matrix.
		eve::math::get_look_at(matrix, m_eyePoint, m_target, m_worldUp);

		// Compute camera matrix required data.
		m_viewDirection		= (m_target - m_eyePoint).normalized();
		m_orientation		= eve::math::TQuaternion<float>(eve::math::TMatrix44<float>::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();
		m_centerOfInterest  = m_eyePoint.distance(m_target);	

		// Members init.
		this->init();
	}	

	return ret;
}



//=================================================================================================
void eve::scene::Camera::init(void)
{
	// Call parent class.
	eve::scene::Object::init();
	eve::math::TCamera<float>::init();

	// Uniform buffer.
	eve::ogl::FormatUniform fmtUniform;
	fmtUniform.blockSize = EVE_OGL_SIZEOF_MAT4 * 2;
	fmtUniform.dynamic	 = true;
	fmtUniform.data		 = this->getMatrixModelView().data(); // //
	m_pUniformMatrices	 = m_pScene->create(fmtUniform);
}

//=================================================================================================
void eve::scene::Camera::release(void)
{
	m_pUniformMatrices->requestRelease();
	m_pUniformMatrices = nullptr;
	m_pVao->requestRelease();
	m_pVao = nullptr;

	// Do not delete -> shared pointer.
	m_pAiCamera = nullptr;

	// Call parent class.
	eve::scene::Object::release();
	eve::math::TCamera<float>::release();
}



//=================================================================================================
void eve::scene::Camera::cb_evtSceneObject(eve::scene::EventArgsSceneObject & p_args)
{
	switch (p_args.type)
	{
	 	case SceneObjectEventType_RotateX:				this->rotateX(p_args.value);				break;
	 	case SceneObjectEventType_RotateY:				this->rotateY(p_args.value);				break;
	 	case SceneObjectEventType_RotateZ:				this->rotateZ(p_args.value);				break;
	 
	 	case SceneObjectEventType_TranslateX:			this->translateX(p_args.value);				break;
	 	case SceneObjectEventType_TranslateY:			this->translateY(p_args.value);				break;
	 	case SceneObjectEventType_TranslateZ:			this->translateZ(p_args.value);				break;	 
	 
	 	default: EVE_ASSERT_FAILURE; break;
	}
}

//=================================================================================================
void eve::scene::Camera::cb_evtSceneCamera(eve::scene::EventArgsSceneCamera & p_args)
{
	switch (p_args.type)
	{
	case SceneCameraEventType_Fov:				this->setFov(p_args.value);				break;
	//case SceneCameraEventType_Zoom:				this->zoom(p_args.value);				break; // TODO !!!

	default: EVE_ASSERT_FAILURE; break;
	}
}



//=================================================================================================
void eve::scene::Camera::oglBindMatrices(void)
{
	m_pUniformMatrices->bind(EVE_OGL_TRANSFORM_CAMERA);
}

//=================================================================================================
void eve::scene::Camera::oglUnbindMatrices(void)
{
	m_pUniformMatrices->unbind(EVE_OGL_TRANSFORM_CAMERA);
}



//=================================================================================================
void eve::scene::Camera::oglDraw(void)
{
// 	m_pUniformMatrix->oglUpdateData(m_matrixModelView.data());
// 	m_pUniformMatrix->bindModel();
// 
// 	m_pMaterial->bind();
// 	m_pVao->draw();
// 	m_pMaterial->unbind();
// 
// 	m_pUniformMatrix->unbind_model();
}
