
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

			friend class eve::mem::Pointer;

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
			std::map<SceneImportParam, std::string>		m_mapImportParams;

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
			EVE_PROTECT_DESTRUCTOR(Scene);

		protected:
			/** \brief Class constructor. */
			explicit Scene(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtScene(eve::scene::EventArgsScene & p_args) override;


		public:
			/** \brief Load scene or mesh from file path. */
			bool loadFromFilePath(const std::wstring & p_filePath);


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
			void setImportParam(eve::scene::SceneImportParam p_param, const std::string & p_value);

		}; // class Scene

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_SCENE_H__



// 
// // Parent header
// #include "scene/Item.h"
// 
// 
// // Native header
// #ifndef __NATIVE_GLOBAL_MACRO_H__
// #include "Native_GlobalMacro.h"
// #endif
// 
// // External header
// #include <vector>
// 
// 
// struct aiCamera;
// struct aiLight;
// struct aiMesh;
// struct aiScene;
// 
// 
// namespace scene
// {
// 
// 	class Importer;
// 	class ItemCameraController;
// 	class ItemLight;
// 	class ItemLightArea;
// 	class ItemLightDirectional;
// 	class ItemLightPoint;
// 	class ItemLightSpot;
// 	class ItemMesh;
// 
// 	/**
// 	* @class scene::Scene
// 	*
// 	* Creates and manages scene items (mesh/light/camera...).
// 	* Inherits from scene::Item
// 	*/
// 	class Scene
// 		: public scene::Item
// 	{
// 
// 		//////////////////////////////////////
// 		//				DATAS				//
// 		//////////////////////////////////////
// 
// 	protected:
// 		scene::Importer *								m_pImporter;
// 
// 		std::vector<ItemCameraController*> *			m_pvecItemCamera;
// 		std::vector<ItemMesh*> *						m_pvecItemMesh;	
// 
// 		std::vector<ItemLight*> *						m_pvecItemLight;
// 		std::vector<ItemLightArea*> *					m_pvecItemLightArea;
// 		std::vector<ItemLightDirectional*> *			m_pvecItemLightDirectional;
// 		std::vector<ItemLightPoint*> *					m_pvecItemLightPoint;
// 		std::vector<ItemLightSpot*> *					m_pvecItemLightSpot;
// 
// 
// 		//////////////////////////////////////
// 		//				METHOD				//
// 		//////////////////////////////////////
// 
// 		/** Invalidate copy constructor and assignation operator. */
// 		NATIVE_DISABLE_COPY( Scene );
// 
// 
// 	protected:
// 		/** \! scene::Scene constructor. */
// 		Scene( void );
// 
// 		/** \! scene::Scene destructor. */
// 		virtual ~Scene( void );
// 
// 
// 		/** \! Allocate and init class members. */
// 		void init( void );
// 
// 		/** \! Deallocate and release class members. */
// 		void release( void );
// 
// 
// 		/** Control event handling. */
// 		virtual void newControlEventMessage( evt::controlEventArgs & p_eventArgs );
// 
// 
// 	public:
// 		/** \! Load scene or mesh from file path. */
// 		bool loadFromFilePath( const std::string & p_filePath );
// 
// 
// 	public:
// 		/** \! Activate controller, register to events. */
// 		virtual void activate( void );
// 		/** \! Deactivate controller, register to events. */
// 		virtual void deactivate( void );
// 
// 
// 	public:
// 		/** Add new camera item based on ASSIMP aiCamera pointer \a pCam */
// 		virtual bool addItem( aiCamera * pCam, const aiScene * p_pScene, const Vec3f & p_upAxis );
// 
// 		/** Add new light item based on ASSIMP aiLight pointer \a pLight */
// 		virtual bool addItem( aiLight * pLight, const aiScene * p_pScene, const Vec3f & p_upAxis );
// 
// 		/** Add new mesh item based on ASSIMP aiMesh pointer \a pMesh */
// 		virtual bool addItem( aiMesh * pMesh, const aiScene * p_pScene, const Vec3f & p_upAxis, const std::string & p_fullPath );
// 
// 
// 		/** \! Add new default camera. */
// 		virtual void addCamera( void );
// 
// 
// 		/** \! Add new default area light. */
// 		virtual void addLightArea( void );
// 
// 		/** \! Add new default directional light. */
// 		virtual void addLightDirectional( void );
// 
// 		/** \! Add new default point light. */
// 		virtual void addLightPoint( void );
// 
// 		/** \! Add new default spot light. */
// 		virtual void addLightSpot( void );
// 
// 
// 		///////////////////////////////////////////////////////////////////////////////////////////
// 		//		GET / SET
// 		///////////////////////////////////////////////////////////////////////////////////////////
// 
// 		/** \! Get camera controller vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemCameraController*> * getCameras( void ) const;
// 		
// 		/** \! Get light vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemLight*> *			 getLights( void ) const;
// 		/** \! Get area light vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemLightArea*> *		 getLightsArea( void ) const;
// 		/** \! Get directional light vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemLightDirectional*> * getLightsDirectional( void ) const;
// 		/** \! Get point light vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemLightPoint*> *		 getLightsPoint( void ) const;
// 		/** \! Get area light vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemLightSpot*> *		 getLightsSpot( void ) const;
// 
// 		/** \! Get mesh vector. Handle with care -> read only outside this class. */
// 		std::vector<ItemMesh*> * getMeshes( void ) const;
// 	};
// 
// } // namespace scene
// 
// 
// ///////////////////////////////////////////////////////////////////////////////////////////////////
// //		GET / SET
// ///////////////////////////////////////////////////////////////////////////////////////////////////
// 
// //=================================================================================================
// inline std::vector<scene::ItemCameraController*> *	scene::Scene::getCameras( void ) const
// {
// 	return m_pvecItemCamera;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemLight*> *				scene::Scene::getLights( void ) const
// {
// 	return m_pvecItemLight;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemLightArea*> *			scene::Scene::getLightsArea( void ) const
// {
// 	return m_pvecItemLightArea;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemLightDirectional*> *  scene::Scene::getLightsDirectional( void ) const
// {
// 	return m_pvecItemLightDirectional;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemLightPoint*> *		scene::Scene::getLightsPoint( void ) const
// {
// 	return m_pvecItemLightPoint;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemLightSpot*> *			scene::Scene::getLightsSpot( void ) const
// {
// 	return m_pvecItemLightSpot;
// }
// 
// //=================================================================================================
// inline std::vector<scene::ItemMesh*> *				scene::Scene::getMeshes( void ) const
// {
// 	return m_pvecItemMesh;
// }
// 
// #endif // __SCENE_SCENE_H__
