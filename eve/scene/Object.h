
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


#ifndef __EVE_EVT_LISTENER_H__
#include "eve/evt/Listener.h"
#endif

#ifndef __EVE_MEMORY_POINTER_H__
#include "eve/mem/Pointer.h"
#endif


namespace eve
{
	namespace scene
	{
		/** 
		* \def eve::scene::ObjectType
		* \brief Enumerate scene objects types.
		*/
		enum ObjectType
		{
			ObjectType_UNDEFINED			= 0x00,

			ObjectType_Mesh					= 0x11,
			ObjectType_Mesh_Animated		= 0x12,

			ObjectType_Light_Area			= 0x23,
			ObjectType_Light_Directional	= 0x24,
			ObjectType_Light_Point			= 0x25,
			ObjectType_Light_Spot			= 0x26,

			ObjectType_Camera				= 0x37,

			ObjectType_Material				= 0x48,

			ObjectType_Scene				= 0x59,

			// This value is not used. It is just there to force the
			// compiler to map this enum to a 32 Bit integer.
			_ObjectType_SubForce32Bit = INT_MAX

		}; // enum ObjectType



		/** 
		* \class eve::scene::ObjectID
		* \brief A scene object ID is composed of its type, a pointer to itself and a pointer to its parent.
		*/
		class ObjectID final
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			eve::scene::ObjectType		m_type;				//!< Specifies object type.
			eve::evt::Listener *		m_pObject;			//!< Specifies a pointer to the object.
			eve::evt::Listener *		m_pObjectParent;	//!< Specifies a pointer to object's parent.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(ObjectID);

		public:
			/** \brief Class default constructor. */
			ObjectID(void);
			/** \brief Class constructor. */
			ObjectID(eve::scene::ObjectType p_type, eve::evt::Listener * p_pObj, eve::evt::Listener * p_pObjParent);


			/** \brief Class destructor. */
			virtual ~ObjectID(void);

		}; // class ObjectID



		/** 
		* \class eve::scene::Object
		* \brief Abstract base scene object class.
		* \note extends eve::mem::Pointer.
		*/
		class Object
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			eve::scene::ObjectType		m_type;				//!< Specifies object type.
			eve::scene::Object *		m_pParent;			//!< Specifies a pointer to object's parent.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Object);
			EVE_PROTECT_DESTRUCTOR(Object);

		protected:
			/** \brief Class constructor. */
			Object(eve::scene::ObjectType p_type, eve::scene::Object * m_pParent);


		}; // class Object

	} // namespace scene

} // namespace eve






namespace gl { class Box3DCornered; };


namespace scene
{


	/**
	* @class scene::Item
	*
	* Abstract base scene item (mesh/light/camera...) class, 
	* inherits from controlEventListenner and gl::Item
	*/
	class Item
		: public evt::EventListenner
	{

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
		std::string					m_name;	


	protected:
		ItemType					m_itemType;				//<! Object ItemType (mesh/light/camera...).
		ItemSubType					m_itemSubType;			//<! Object ItemSubType (Mesh->animated/not, Light->area/directionnal/point/spot ...).

		scene::Item *				m_pItemParent;			//<! Parent item shared pointer.

		ObjectID_t					m_objectType;			//<! Formated object type.

		bool						m_bVisible;				//<! Object visible state.
		bool						m_bLocked;				//<! Object locked state.

		gl::Box3DCornered *			m_pBox;					//<! Bounding box.

#ifndef NDEBUG
	protected:
		bool						m_bReleaseEnforcer;		//<! Convenience boolean to enforce static release method call.
#endif


		//////////////////////////////////////
		//				METHOD				//
		//////////////////////////////////////

		/** Invalidate copy constructor and assignation operator. */
		NATIVE_DISABLE_COPY( Item );


	protected:
		/** \! scene::Item constructor. */
		Item( scene::Item * pParent );

		/** \! scene::Item destructor. */
		virtual ~Item( void );


	protected:
		/** \! Allocate and init class members. */
		virtual void init( void );
		/** \! Deallocate and release class members. */
		virtual void release( void );


	public:
		/** Control event handling. */
		virtual void newControlEventMessage( evt::controlEventArgs & p_eventArgs ) = 0;


	public:
		/** \! Test ray intersection with target bounding box.
		* Return true if intersection occurred, false otherwise.
		*/
		bool hitTestBox( const Vec3f & p_origin, const Vec3f & p_direction );
		/** \! Test ray intersection with target bounding box.
		* Return true if intersection occurred, false otherwise.
		*/
		bool hitTestBox( const Rayf & p_ray );


		///////////////////////////////////////////////////////////////////////////////////////////
		//		GET / SET
		///////////////////////////////////////////////////////////////////////////////////////////

	public:
		/** Get item type as scene::ItemType. */
		virtual const scene::ItemType getType( void ) const;
		/** Get item sub type as scene::ItemSubType. */
		virtual const scene::ItemSubType getSubType( void ) const;


		/** Get parent as scene::Item pointer. */
		scene::Item * getParent( void ) const;


		/** Get object formated type. */
		const ObjectID_t & getObjectID( void ) const;


		/** \! Get object name. */
		const std::string & getName( void ) const;


		/** \! Get locked state. */
		const bool getLockedState( void ) const;
		/** \! Set locked state. */
		void setLockedState( bool p_bState );


		/** \! Get visible state. */
		const bool getVisibleState( void ) const;
		/** Set visible state. */
		void setVisibleState( bool p_bState );
	};

} // namespace scene


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
inline const scene::ItemType scene::Item::getType( void ) const
{
#ifndef NDEBUG
	NATIVE_ASSERT( (m_itemType!=Item_UNDEFINED) );
#endif

	return m_itemType;
}

//=================================================================================================
inline const scene::ItemSubType scene::Item::getSubType( void ) const
{
#ifndef NDEBUG
	NATIVE_ASSERT( (m_itemSubType!=Item_SUBUNDEFINED) );
#endif

	return m_itemSubType;
}


//=================================================================================================
inline scene::Item * scene::Item::getParent( void ) const
{
	return m_pItemParent;
}


//=================================================================================================
inline const ObjectID_t & scene::Item::getObjectID( void ) const
{
	return m_objectType;
}


//=================================================================================================
inline const std::string & scene::Item::getName( void ) const
{
	return m_name;
}


//=================================================================================================
inline const bool scene::Item::getLockedState( void ) const
{
	return m_bLocked;
}

//=================================================================================================
inline void scene::Item::setLockedState( bool p_bState )
{
	m_bLocked = p_bState;
}


//=================================================================================================
inline const bool scene::Item::getVisibleState( void ) const
{
	return m_bVisible;
}

//=================================================================================================
inline void scene::Item::setVisibleState( bool p_bState )
{
	m_bVisible = p_bState;
}


#endif // __SCENE_ITEM_H__
