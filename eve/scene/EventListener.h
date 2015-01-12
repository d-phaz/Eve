
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
#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#define __EVE_SCENE_EVENT_LISTENER_H__


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
		* \def eve::scene::SceneEventType
		* \brief enumerate scene event types.
		*/
		enum SceneEventType
		{
			SceneEventType_UNDEFINED = 0,
			
			SceneEventType_add_sceneFromPath,
			SceneEventType_add_meshFromPath,

			SceneEventType_add_defaultLightArea,
			SceneEventType_add_defaultLightDirectional,
			SceneEventType_add_defaultLightPoint,
			SceneEventType_add_defaultLightSpot,
			SceneEventType_add_defaultCamera,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::SceneEventArgs
		* \brief Scene event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class SceneEventArgs
			: public eve::evt::EventArgs
		{
		public:
			SceneEventType		type;
			std::wstring		path;

			/** \brief Default constructor. */
			SceneEventArgs(void);
			/** \brief Copy constructor. */
			SceneEventArgs(const SceneEventArgs & p_other);
			/** \brief Assignment operator. */
			SceneEventArgs & operator = (const SceneEventArgs & p_other);
		};
		/** 
		* \def eve::scene::EventScene
		* \brief scene event type definition.
		*/
		typedef eve::evt::TEvent<SceneEventArgs> EventScene;
		/**
		* \class eve::scene::SceneEventListener
		* \brief Abstract base scene event listener.
		* \note extends eve::evt::Listener.
		*/
		class SceneEventListener
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(SceneEventListener);
			EVE_PROTECT_DESTRUCTOR(SceneEventListener);

		protected:
			/** \brief Class constructor. */
			SceneEventListener(void);

			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtScene(eve::scene::SceneEventArgs & p_args) = 0;

		}; // class SceneEventListener



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE OBJECT EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::SceneObjectEventType
		* \brief enumerate scene object event types.
		*/
		enum SceneObjectEventType
		{
			SceneObjectEventType_UNDEFINED = 0,

			SceneObjectEventType_TranslationX,
			SceneObjectEventType_TranslationY,
			SceneObjectEventType_TranslationZ,
			SceneObjectEventType_RotationX,
			SceneObjectEventType_RotationY,
			SceneObjectEventType_RotationZ,
			SceneObjectEventType_ScaleX,
			SceneObjectEventType_ScaleY,
			SceneObjectEventType_ScaleZ,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneObjectEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::SceneObjectEventArgs
		* \brief Scene object event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class SceneObjectEventArgs
			: public eve::evt::EventArgs
		{
		public:
			SceneObjectEventType	type;
			float					value;

			/** \brief Default constructor. */
			SceneObjectEventArgs(void);
			/** \brief Copy constructor. */
			SceneObjectEventArgs(const SceneObjectEventArgs & p_other);
			/** \brief Assignment operator. */
			SceneObjectEventArgs & operator = (const SceneObjectEventArgs & p_other);
		};
		/**
		* \def eve::scene::EventSceneObject
		* \brief scene object event type definition.
		*/
		typedef eve::evt::TEvent<SceneObjectEventArgs> EventSceneObject;
		/**
		* \class eve::scene::SceneObjectEventListener
		* \brief Abstract base scene object event listener.
		* \note extends eve::evt::Listener.
		*/
		class SceneObjectEventListener
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(SceneObjectEventListener);
			EVE_PROTECT_DESTRUCTOR(SceneObjectEventListener);

		protected:
			/** \brief Class constructor. */
			SceneObjectEventListener(void);

			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneObject(eve::scene::SceneObjectEventArgs & p_args) = 0;

		}; // class SceneObjectEventListener



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE CAMERA EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::SceneCameraEventType
		* \brief enumerate scene camera event types.
		*/
		enum SceneCameraEventType
		{
			SceneCameraEventType_UNDEFINED = 0,

			SceneCameraEventType_Fov,
			SceneCameraEventType_Zoom,

			//! This value is not used. It is just there to force the compiler to map this enum to a 32 Bit integer.
			_SceneCameraEventType_Force32Bit = INT_MAX
		};
		/**
		* \class eve::scene::SceneCameraEventArgs
		* \brief Scene camera event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class SceneCameraEventArgs
			: public eve::evt::EventArgs
		{
		public:
			SceneCameraEventType	type;
			float					value;

			/** \brief Default constructor. */
			SceneCameraEventArgs(void);
			/** \brief Copy constructor. */
			SceneCameraEventArgs(const SceneCameraEventArgs & p_other);
			/** \brief Assignment operator. */
			SceneCameraEventArgs & operator = (const SceneCameraEventArgs & p_other);
		};
		/**
		* \def eve::scene::EventSceneCamera
		* \brief scene camera event type definition.
		*/
		typedef eve::evt::TEvent<SceneCameraEventArgs> EventSceneCamera;
		/**
		* \class eve::scene::SceneCameraEventListener
		* \brief Abstract base scene camera event listener.
		* \note extends eve::evt::Listener.
		*/
		class SceneCameraEventListener
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(SceneCameraEventListener);
			EVE_PROTECT_DESTRUCTOR(SceneCameraEventListener);

		protected:
			/** \brief Class constructor. */
			SceneCameraEventListener(void);

			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneCamera(eve::scene::EventSceneCamera & p_args) = 0;

		}; // class SceneCameraEventListener



		///////////////////////////////////////////////////////////////////////////////////////////
		//		SCENE LIGHT EVENT
		///////////////////////////////////////////////////////////////////////////////////////////

		/**
		* \def eve::scene::SceneLightEventType
		* \brief enumerate scene light event types.
		*/
		enum SceneLightEventType
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
		* \class eve::scene::SceneLightEventArgs
		* \brief Scene light event arguments class.
		* \note extends eve::evt::EventArgs.
		*/
		class SceneLightEventArgs
			: public eve::evt::EventArgs
		{
		public:
			SceneLightEventType		type;
			float					valueFloat;
			bool					valueBool;

			/** \brief Default constructor. */
			SceneLightEventArgs(void);
			/** \brief Copy constructor. */
			SceneLightEventArgs(const SceneLightEventArgs & p_other);
			/** \brief Assignment operator. */
			SceneLightEventArgs & operator = (const SceneLightEventArgs & p_other);
		};
		/**
		* \def eve::scene::EventSceneLight
		* \brief scene light event type definition.
		*/
		typedef eve::evt::TEvent<SceneLightEventArgs> EventSceneLight;
		/**
		* \class eve::scene::SceneLightEventListener
		* \brief Abstract base scene light event listener.
		* \note extends eve::evt::Listener.
		*/
		class SceneLightEventListener
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(SceneLightEventListener);
			EVE_PROTECT_DESTRUCTOR(SceneLightEventListener);

		protected:
			/** \brief Class constructor. */
			SceneLightEventListener(void);

			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneLight(eve::scene::EventSceneLight & p_args) = 0;

		}; // class SceneLightEventListener		

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_EVENT_LISTENER_H__
