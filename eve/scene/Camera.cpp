
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
	// Grab scene node. 
	const aiNode * pRoot = p_pScene->mRootNode;
	const aiNode * pNode = pRoot->FindNode(m_name.c_str());

	// Test scene node.
	bool ret = pNode != NULL;
	EVE_ASSERT(ret);

	

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
void eve::scene::Camera::cb_evtSceneCamera(eve::scene::EventArgsSceneCamera & p_args)
{
// 	switch (p_args.type)
// 	{
// 	case SceneObjectEventType_RotateX:				this->rotateX(p_args.value);				break;
// 	case SceneObjectEventType_RotateY:				this->rotateY(p_args.value);				break;
// 	case SceneObjectEventType_RotateZ:				this->rotateZ(p_args.value);				break;
// 
// 	case SceneObjectEventType_TranslateX:			this->translateX(p_args.value);				break;
// 	case SceneObjectEventType_TranslateY:			this->translateY(p_args.value);				break;
// 	case SceneObjectEventType_TranslateZ:			this->translateZ(p_args.value);				break;
// 
// 	case SceneObjectEventType_ScaleX:				this->scaleX(p_args.value);					break;
// 	case SceneObjectEventType_ScaleY:				this->scaleY(p_args.value);					break;
// 	case SceneObjectEventType_ScaleZ:				this->scaleZ(p_args.value);					break;
// 
// 
// 	case SceneObjectEventType_SetRotationX:			this->setRotationX(p_args.value);			break;
// 	case SceneObjectEventType_SetRotationY:			this->setRotationY(p_args.value);			break;
// 	case SceneObjectEventType_SetRotationZ:			this->setRotationZ(p_args.value);			break;
// 
// 	case SceneObjectEventType_SetTranslationX:		this->setTranslationX(p_args.value);		break;
// 	case SceneObjectEventType_SetTranslationY:		this->setTranslationY(p_args.value);		break;
// 	case SceneObjectEventType_SetTranslationZ:		this->setTranslationZ(p_args.value);		break;
// 
// 	case SceneObjectEventType_SetScaleX:			this->setScaleX(p_args.value);				break;
// 	case SceneObjectEventType_SetScaleY:			this->setScaleY(p_args.value);				break;
// 	case SceneObjectEventType_SetScaleZ:			this->setScaleZ(p_args.value);				break;
// 
// 
// 	default: EVE_ASSERT_FAILURE; break;
// 	}
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
