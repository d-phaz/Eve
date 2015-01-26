
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
#ifndef __EVE_SCENE_SCENE_H__
#define __EVE_SCENE_SCENE_H__


#ifndef __EVE_OPENGL_CORE_RENDER_H__
#include "eve/ogl/core/Renderer.h"
#endif

#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#include "eve/scene/EventListener.h"
#endif


struct aiCamera;
struct aiLight;
struct aiMesh;
struct aiScene;

namespace eve { namespace scene { class Camera; } }
namespace eve { namespace scene { class Mesh; } }


namespace eve
{
	namespace scene
	{
		/** 
		* \enum eve::scene::SceneImportParam
		* \brief Enumerates ASSIMP import parameters.
		*/
		enum SceneImportParam
		{
			SceneImportParam_UNDEFINED		= 0,

			SceneImportParam_Up_Axis,

			SceneImportParam_Flip_UV,

			SceneImportParam_Generate_Normals,
			SceneImportParam_Normals_Max_Angle,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneImportParam_Force32Bit	= INT_MAX

		}; // enum SceneImportParam


		/**
		* \class eve::scene::Scene
		* \brief Create, manage, render scene objects (mesh/light/camera...)..
		* \note extends eve::ogl::Renderer, eve::scene::EventListenerScene
		*/
		class Scene
			: public eve::ogl::Renderer
			, public eve::scene::EventListenerScene
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			//<! Import parameters map.
			//<!	Parameters are							Values are			Note
			//!<	SceneImportParam_Up_Axis				"X" / "Y" / "Z"
			//<!	SceneImportParam_Flip_UV				"Y" / "N"
			//<!	SceneImportParam_Generate_Normals		"Y" / "N"
			//<!	SceneImportParam_Normals_Max_Angle		"0.0... 175.0"		Used only when Generate_Normals is set to "Y"
			static std::map<SceneImportParam, std::string>	m_map_import_params;

		protected:
			std::vector<eve::scene::Camera*> *			m_pVecCamera;		//!< Specifies Camera objects vector.
			eve::scene::Camera *						m_pCameraActive;	//!< Specifies active camera shared pointer.

			std::vector<eve::scene::Mesh*> *			m_pVecMesh;			//!< Specifies Mesh objects vector.


		protected:
			eve::ogl::Shader *							m_pShaderMesh;		//!< Specifies mesh render shader.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Scene);
			EVE_PUBLIC_DESTRUCTOR(Scene);

		public:
			/** \brief Class constructor. */
			explicit Scene(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtScene(eve::scene::EventArgsScene & p_args) override;


		public:
			/** \brief Load scene or mesh from file path. */
			bool load(const std::wstring & p_filePath);


		public:
			/** \brief Add new mesh item based on ASSIMP aiMesh pointer \a p_pMesh. */
			virtual bool add(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis, const std::string & p_fullPath);
			/** \brief Add new mesh item based on ASSIMP aiCamera pointer \a p_pCamera. */
			virtual bool add(const aiCamera * p_pCamera, const aiScene * p_pScene, eve::Axis p_upAxis);


		public:
			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) override;


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Assign value to target import parameter. */
			static void set_import_param(eve::scene::SceneImportParam p_param, const std::string & p_value);

		}; // class Scene

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_SCENE_H__
