
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

#pragma once
#ifndef __EVE_SCENE_CAMERA_H__
#define __EVE_SCENE_CAMERA_H__


#ifndef __EVE_SCENE_OBJECT_H__
#include "eve/scene/Object.h"
#endif

#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#include "eve/scene/EventListener.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif


namespace eve { namespace ogl { class Uniform; } }
namespace eve { namespace ogl { class Vao; } }


namespace eve
{
	namespace scene
	{

		/** 
		* \class eve::scene::Camera
		* \brief Scene camera object.
		* \note extends eve::scene::Object, eve::scene::EventListenerSceneCamera, eve::math::Camera
		*/
		class Camera
			: public eve::scene::Object
			, public eve::scene::EventListenerSceneCamera
			, public eve::math::TCamera<float>
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			const aiCamera *		m_pAiCamera;			//!< Specifies Assimp camera (shared pointer).

			eve::ogl::Vao *			m_pVao;					//!< Specifies OpenGL vertex array object.
			eve::ogl::Uniform *		m_pUniformMatrices;		//!< Specifies uniform buffer containing matrices.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Camera);
			EVE_PUBLIC_DESTRUCTOR(Camera);

		public:
			/** \brief Create, init and return new pointer based on ASSIMP aiCamera \a p_pCamera. */
			static eve::scene::Camera * create_ptr(eve::scene::Scene *	p_pParentScene
											     , eve::scene::Object *	p_pParent
												 , const aiCamera *		p_pCamera
											     , const aiScene *		p_pScene
											     , eve::Axis			p_upAxis);


		public:
			/** \brief Class constructor. */
			explicit Camera(eve::scene::Scene * p_pParentScene, eve::scene::Object * p_pParent);


		protected:
			/** \brief Allocate and init class members based on ASSIMP aiCamera \a p_pCamera. */
			bool init(const aiCamera * p_pCamera, const aiScene * p_pScene, eve::Axis p_upAxis);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		protected:
// 			/** \brief Compute model view matrix. */
// 			virtual void calcModelView(void) const override;
// 			/** \brief Compute projection matrix. */
// 			virtual void calcProjection(void) const override;
			/** \brief Update model view matrix based on rot/trans/scale matrices concatenation. */
			virtual void updateMatrixModelView(void) override;
			/** \brief Update projection matrix. */
			virtual void updateMatrixProjection(void) override;


		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneObject(eve::scene::EventArgsSceneObject & p_args) override;
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneCamera(eve::scene::EventArgsSceneCamera & p_args) override;


		public:
			/** \brief Bind matrices buffer. */
			void oglBind(void);
			/** \brief Unbind matrices buffer. */
			void oglUnbind(void);

			/** \brief OpenGL VAO draw. */
			void oglDraw(void);

		}; // class Camera		

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_CAMERA_H__
