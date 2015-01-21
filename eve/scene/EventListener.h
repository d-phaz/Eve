
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


#ifndef __EVE_SCENE_EVENT_H__
#include "eve/scene/Event.h"
#endif


namespace eve
{
	namespace scene
	{
		/**
		* \class eve::scene::EventListenerScene
		* \brief Abstract base scene event listener.
		* \note extends eve::evt::Listener.
		*/
		class EventListenerScene
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(EventListenerScene);
			EVE_PROTECT_DESTRUCTOR(EventListenerScene);

		protected:
			/** \brief Class constructor. */
			EventListenerScene(void);

		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtScene(eve::scene::EventArgsScene & p_args) = 0;

		}; // class EventListenerScene



		/**
		* \class eve::scene::EventListenerSceneObject
		* \brief Abstract base scene object event listener.
		* \note extends eve::evt::Listener.
		*/
		class EventListenerSceneObject
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(EventListenerSceneObject);
			EVE_PROTECT_DESTRUCTOR(EventListenerSceneObject);

		protected:
			/** \brief Class constructor. */
			EventListenerSceneObject(void);

		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneObject(eve::scene::EventArgsSceneObject & p_args) = 0;

		}; // class EventListenerSceneObject



		/**
		* \class eve::scene::EventListenerSceneMaterial
		* \brief Abstract base scene material event listener.
		* \note extends eve::evt::Listener.
		*/
		class EventListenerSceneMaterial
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(EventListenerSceneMaterial);
			EVE_PROTECT_DESTRUCTOR(EventListenerSceneMaterial);

		protected:
			/** \brief Class constructor. */
			EventListenerSceneMaterial(void);

		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneMaterial(eve::scene::EventArgsSceneMaterial & p_args) = 0;

		}; // class EventListenerSceneMaterial



		/**
		* \class eve::scene::EventListenerSceneCamera
		* \brief Abstract base scene camera event listener.
		* \note extends eve::evt::Listener.
		*/
		class EventListenerSceneCamera
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(EventListenerSceneCamera);
			EVE_PROTECT_DESTRUCTOR(EventListenerSceneCamera);

		protected:
			/** \brief Class constructor. */
			EventListenerSceneCamera(void);

		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneCamera(eve::scene::EventArgsSceneCamera & p_args) = 0;

		}; // class EventListenerSceneCamera



		/**
		* \class eve::scene::EventListenerSceneLight
		* \brief Abstract base scene light event listener.
		* \note extends eve::evt::Listener.
		*/
		class EventListenerSceneLight
			: public eve::evt::Listener
		{
			EVE_DISABLE_COPY(EventListenerSceneLight);
			EVE_PROTECT_DESTRUCTOR(EventListenerSceneLight);

		protected:
			/** \brief Class constructor. */
			EventListenerSceneLight(void);

		public:
			/** \brief Event handler callback (pure virtual). */
			virtual void cb_evtSceneLight(eve::scene::EventArgsSceneLight & p_args) = 0;

		}; // class EventListenerSceneLight		

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_EVENT_LISTENER_H__
