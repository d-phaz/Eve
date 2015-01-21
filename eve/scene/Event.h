
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
#ifndef __EVE_SCENE_EVENT_H__
#define __EVE_SCENE_EVENT_H__


#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif


namespace eve
{
	namespace scene
	{

		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/** 
		* \def eve::scene::EventTypeScene
		* \brief enumerate scene event types.
		*/
		enum EventTypeScene
		{
			SceneEventType_UNDEFINED = 0,
			
			SceneEventType_add_fromPath,

			SceneEventType_add_defaultLightArea,
			SceneEventType_add_defaultLightDirectional,
			SceneEventType_add_defaultLightPoint,
			SceneEventType_add_defaultLightSpot,
			SceneEventType_add_defaultCamera,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::EventArgsScene
		* \brief Scene event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class EventArgsScene
			: public eve::evt::EventArgs
		{
		public:
			EventTypeScene		type;
			std::wstring		path;

			/** \brief Default constructor. */
			EventArgsScene(void);
			/** \brief Copy constructor. */
			EventArgsScene(const EventArgsScene & p_other);
			/** \brief Assignment operator. */
			EventArgsScene & operator = (const EventArgsScene & p_other);
		};
		/** 
		* \def eve::scene::EventScene
		* \brief scene event type definition.
		*/
		typedef eve::evt::TEvent<EventArgsScene> EventScene;



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE OBJECT EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::EventTypeSceneObject
		* \brief enumerate scene object event types.
		*/
		enum EventTypeSceneObject
		{
			SceneObjectEventType_UNDEFINED = 0,

			SceneObjectEventType_RotateX,
			SceneObjectEventType_RotateY,
			SceneObjectEventType_RotateZ,
			SceneObjectEventType_TranslateX,
			SceneObjectEventType_TranslateY,
			SceneObjectEventType_TranslateZ,
			SceneObjectEventType_ScaleX,
			SceneObjectEventType_ScaleY,
			SceneObjectEventType_ScaleZ,

			SceneObjectEventType_SetRotationX,
			SceneObjectEventType_SetRotationY,
			SceneObjectEventType_SetRotationZ,
			SceneObjectEventType_SetTranslationX,
			SceneObjectEventType_SetTranslationY,
			SceneObjectEventType_SetTranslationZ,
			SceneObjectEventType_SetScaleX,
			SceneObjectEventType_SetScaleY,
			SceneObjectEventType_SetScaleZ,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneObjectEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::EventArgsSceneObject
		* \brief Scene object event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class EventArgsSceneObject
			: public eve::evt::EventArgs
		{
		public:
			EventTypeSceneObject	type;
			float					value;

			/** \brief Default constructor. */
			EventArgsSceneObject(void);
			/** \brief Copy constructor. */
			EventArgsSceneObject(const EventArgsSceneObject & p_other);
			/** \brief Assignment operator. */
			EventArgsSceneObject & operator = (const EventArgsSceneObject & p_other);
		};
		/**
		* \def eve::scene::EventSceneObject
		* \brief scene object event type definition.
		*/
		typedef eve::evt::TEvent<EventArgsSceneObject> EventSceneObject;



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE MATERIAL EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::EventTypeSceneMaterial
		* \brief enumerate scene material event types.
		*/
		enum EventTypeSceneMaterial
		{
			SceneMaterialEventType_UNDEFINED = 0,

			SceneMaterialEventType_ValueDiffuse,
			SceneMaterialEventType_ValueSpecular,
			SceneMaterialEventType_ValueShininess,
			SceneMaterialEventType_ValueFresnel,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneMaterialEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::EventArgsSceneMaterial
		* \brief Scene material event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class EventArgsSceneMaterial
			: public eve::evt::EventArgs
		{
		public:
			EventTypeSceneMaterial	type;
			float					value;

			/** \brief Default constructor. */
			EventArgsSceneMaterial(void);
			/** \brief Copy constructor. */
			EventArgsSceneMaterial(const EventArgsSceneMaterial & p_other);
			/** \brief Assignment operator. */
			EventArgsSceneMaterial & operator = (const EventArgsSceneMaterial & p_other);
		};
		/**
		* \def eve::scene::EventSceneMaterial
		* \brief scene material event type definition.
		*/
		typedef eve::evt::TEvent<EventArgsSceneMaterial> EventSceneMaterial;



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE CAMERA EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::EventTypeSceneCamera
		* \brief enumerate scene camera event types.
		*/
		enum EventTypeSceneCamera
		{
			SceneCameraEventType_UNDEFINED = 0,

			SceneCameraEventType_Fov,
			SceneCameraEventType_Zoom,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneCameraEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::EventArgsSceneCamera
		* \brief Scene camera event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class EventArgsSceneCamera
			: public eve::evt::EventArgs
		{
		public:
			EventTypeSceneCamera	type;
			float					value;

			/** \brief Default constructor. */
			EventArgsSceneCamera(void);
			/** \brief Copy constructor. */
			EventArgsSceneCamera(const EventArgsSceneCamera & p_other);
			/** \brief Assignment operator. */
			EventArgsSceneCamera & operator = (const EventArgsSceneCamera & p_other);
		};
		/**
		* \def eve::scene::EventSceneCamera
		* \brief scene camera event type definition.
		*/
		typedef eve::evt::TEvent<EventArgsSceneCamera> EventSceneCamera;



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE LIGHT EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::EventTypeSceneLight
		* \brief enumerate scene light event types.
		*/
		enum EventTypeSceneLight
		{
			SceneLightEventType_UNDEFINED = 0,

			SceneLightEventType_ColorRed,
			SceneLightEventType_ColorGreen,
			SceneLightEventType_ColorBlue,

			SceneLightEventType_Intensity,

			SceneLightEventType_AttenuationConstant,
			SceneLightEventType_AttenuationLinear,
			SceneLightEventType_AttenuationQuadratic,

			SceneLightEventType_CastShadow,

			SceneLightEventType_AmbiantFactor,
			SceneLightEventType_AmbiantColor,
			SceneLightEventType_AmbiantColorRed,
			SceneLightEventType_AmbiantColorGreen,
			SceneLightEventType_AmbiantColorBlue,

			SceneLightEventType_Exponent,
			SceneLightEventType_CutOff,
			
			SceneLightEventType_AreaWidth,
			SceneLightEventType_AreaHeight,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneLightEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::EventArgsSceneLight
		* \brief Scene light event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class EventArgsSceneLight
			: public eve::evt::EventArgs
		{
		public:
			EventTypeSceneLight		type;
			float					valueFloat;
			bool					valueBool;

			/** \brief Default constructor. */
			EventArgsSceneLight(void);
			/** \brief Copy constructor. */
			EventArgsSceneLight(const EventArgsSceneLight & p_other);
			/** \brief Assignment operator. */
			EventArgsSceneLight & operator = (const EventArgsSceneLight & p_other);
		};
		/**
		* \def eve::scene::EventSceneLight
		* \brief scene light event type definition.
		*/
		typedef eve::evt::TEvent<EventArgsSceneLight> EventSceneLight;	

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_EVENT_H__
