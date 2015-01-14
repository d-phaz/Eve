
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
#ifndef __EVE_SCENE_MESH_H__
#define __EVE_SCENE_MESH_H__


#ifndef __EVE_SCENE_OBJECT_H__
#include "eve/scene/Object.h"
#endif

#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#include "eve/scene/EventListener.h"
#endif

#ifndef __EVE_MATH_TMESH_H__
#include "eve/math/TMesh.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_VAO_H__
#include "eve/ogl/core/Vao.h"
#endif


namespace eve
{
	namespace scene
	{

		/** 
		* \class eve::scene::Mesh
		* \brief Scene mesh object.
		* \note extends eve::scene::Object, eve::scene::EventListenerSceneObject, eve::math::TMesh
		*/
		class Mesh
			: public eve::scene::Object
			, public eve::scene::EventListenerSceneObject
			, public eve::math::TMesh<float>
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			eve::ogl::Vao *			m_pVao;					//<! Specifies OpenGL vertex array object.
			const aiMesh *			m_pAiMesh;				//<! Specifies Assimp mesh (shared pointer).

		protected:
			int32_t					m_numBones;				//<! Specifies the number of bones in mesh.
			eve::vec4ui_t *			m_pBoneIndices;			//<! Specifies bone indices array.
			eve::vec4f *			m_pWeights;				//<! Specifies bones weights array.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Mesh);
			EVE_PROTECT_DESTRUCTOR(Mesh);

		public:
			/** \brief Create, init and return new pointer based on ASSIMP aiMesh \a pMesh. */
			static eve::scene::Mesh * create_ptr(eve::scene::Object * p_pParent, const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath);


		protected:
			/** \brief Class constructor. */
			explicit Mesh(eve::scene::Object * p_pParent);


		protected:
			/** \! Allocate and init class members based on ASSIMP aiMesh \a pMesh. */
			bool initFromAssimpMesh(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneObject(eve::scene::EventArgsSceneObject & p_args) override;


		public:
			/** \brief OpenGL VAO draw. */
			virtual void oglDraw(void) override;


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL VAO. */
			eve::ogl::Vao * getVao(void) const;

		}; // class Mesh		

	} // namespace scene

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE eve::ogl::Vao * eve::scene::Mesh::getVao(void) const { return m_pVao; }

#endif // __EVE_SCENE_MESH_H__
