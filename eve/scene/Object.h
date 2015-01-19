
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
#ifndef __EVE_SCENE_OBJECT_H__
#define __EVE_SCENE_OBJECT_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#include <assimp/scene.h>


namespace eve { namespace scene { class Scene; } }


namespace eve
{
	namespace scene
	{
		/** 
		* \def eve::scene::SceneObjectType
		* \brief Enumerates all supported scene object types. 
		*/
		enum SceneObjectType
		{
			SceneObject_UNDEFINED			= 0x00,

			SceneObject_Mesh				= 0x11,

			SceneObject_Light_Area			= 0x23,
			SceneObject_Light_Directional	= 0x24,
			SceneObject_Light_Point			= 0x25,
			SceneObject_Light_Spot			= 0x26,

			SceneObject_Camera				= 0x37,

			SceneObject_Material			= 0x48,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneObject_Force32Bit			= INT_MAX

		}; // enum SceneObjectType



		/** 
		* \class eve::scene::Object
		* \brief Abstract base scene object (mesh, light, camera...).
		* \note extends eve::mem::Pointer
		*/
		class Object
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			//<! Name is used to retrieve objects in scene node hierarchy at import.

			//<! Name of the mesh. 
			//<! Meshes can be named, but this is not a requirement and leaving this field empty is totally fine.
			//<! There are mainly three uses for mesh names: 
			//<!  - some formats name nodes and meshes independently.
			//<!  - importers tend to split meshes up to meet the
			//<!     one-material-per-mesh requirement. Assigning
			//<!     the same (dummy) name to each of the result meshes
			//<!     aids the caller at recovering the original mesh
			//<!     partitioning.
			//<!  - Vertex animations refer to meshes by their names.

			//<! The name of the light source. There must be a node in the scene graph with the same name.
			//<! This node specifies the position of the light in the scene  hierarchy and can be animated.

			//<! The name of the camera.
			//<! There must be a node in the scene graph with the same name.
			//<! This node specifies the position of the camera in the scene hierarchy and can be animated.
			std::string							m_name;


		protected:
			eve::scene::SceneObjectType			m_objectType;			//!< Specifies object type (mesh, light, camera, ...).
			eve::scene::Scene *					m_pScene;				//!< Specifies parent scene shared pointer.
			eve::scene::Object *				m_pParent;				//!< Specifies parent object shared pointer.

			bool								m_bVisible;				//!< Specifies object visible state.
			bool								m_bLocked;				//!< Specifies object locked state.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Object);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Object);

		protected:
			/** \brief Class constructor. */
			explicit Object(eve::scene::Scene * p_pScene, eve::scene::Object * p_pParent, eve::scene::SceneObjectType p_type);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


			///////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get object name. */
			const std::string & getName(void) const;
			/** \brief Get object type. */
			const eve::scene::SceneObjectType getType(void) const;
			/** \brief Get parent as scene::Item pointer. */
			eve::scene::Object * getParent(void) const;


			/** \brief Get locked state. */
			const bool getLockedState(void) const;
			/** \brief Set locked state. */
			void setLockedState(bool p_bState);


			/** \brief Get visible state. */
			const bool getVisibleState(void) const;
			/** \brief Set visible state. */
			void setVisibleState(bool p_bState);

		}; // class Object		

	} // namespace scene

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const std::string &				eve::scene::Object::getName(void) const				{ return m_name;			}
EVE_FORCE_INLINE const eve::scene::SceneObjectType	eve::scene::Object::getType(void) const				{ return m_objectType;		}
EVE_FORCE_INLINE eve::scene::Object *				eve::scene::Object::getParent(void) const			{ return m_pParent;			}


//=================================================================================================
EVE_FORCE_INLINE const bool							eve::scene::Object::getLockedState(void) const		{ return m_bLocked;			}
EVE_FORCE_INLINE void								eve::scene::Object::setLockedState(bool p_bState)	{ m_bLocked = p_bState;		}


//=================================================================================================
EVE_FORCE_INLINE const bool							eve::scene::Object::getVisibleState(void) const		{ return m_bVisible;		}
EVE_FORCE_INLINE void								eve::scene::Object::setVisibleState(bool p_bState)	{ m_bVisible = p_bState;	}

#endif // __EVE_SCENE_OBJECT_H__
