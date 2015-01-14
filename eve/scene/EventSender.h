
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
#ifndef __EVE_SCENE_EVENT_SENDER_H__
#define __EVE_SCENE_EVENT_SENDER_H__


#ifndef __EVE_SCENE_EVENT_H__
#include "eve/scene/Event.h"
#endif

#ifndef __EVE_SCENE_EVENT_LISTENER_H__
#include "eve/scene/EventListener.h"
#endif


namespace eve
{
	namespace scene
	{
		/**
		* \class eve::scene::EventSenderScene
		* \brief Base scene event sender.
		*/
		class EventSenderScene
		{

		protected:
			eve::scene::EventScene				m_evt;


			EVE_DISABLE_COPY(EventSenderScene);
			EVE_PROTECT_DESTRUCTOR(EventSenderScene);

		protected:
			/** \brief Class constructor. */
			EventSenderScene(void);

		public:
			/** \brief Add event listener. */
			void addListener(eve::scene::EventListenerScene * p_pListener);
			/** \brief Remove event listener. */
			void removeListener(eve::scene::EventListenerScene * p_pListener);
			
		public:
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeScene p_type);
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeScene p_type, const std::wstring & p_path);

		}; // class EventSenderScene	



		/**
		* \class eve::scene::EventSenderSceneObject
		* \brief Base scene object event sender.
		*/
		class EventSenderSceneObject
		{

		protected:
			eve::scene::EventSceneObject		m_evt;


			EVE_DISABLE_COPY(EventSenderSceneObject);
			EVE_PROTECT_DESTRUCTOR(EventSenderSceneObject);

		protected:
			/** \brief Class constructor. */
			EventSenderSceneObject(void);

		public:
			/** \brief Add event listener. */
			void addListener(eve::scene::EventListenerSceneObject * p_pListener);
			/** \brief Remove event listener. */
			void removeListener(eve::scene::EventListenerSceneObject * p_pListener);

		public:
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeSceneObject p_type, float p_value);

		}; // class EventSenderSceneObject



		/**
		* \class eve::scene::EventSenderSceneCamera
		* \brief Base scene camera event sender.
		*/
		class EventSenderSceneCamera
		{

		protected:
			eve::scene::EventSceneCamera		m_evt;


			EVE_DISABLE_COPY(EventSenderSceneCamera);
			EVE_PROTECT_DESTRUCTOR(EventSenderSceneCamera);

		protected:
			/** \brief Class constructor. */
			EventSenderSceneCamera(void);

		public:
			/** \brief Add event listener. */
			void addListener(eve::scene::EventListenerSceneCamera * p_pListener);
			/** \brief Remove event listener. */
			void removeListener(eve::scene::EventListenerSceneCamera * p_pListener);

		public:
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeSceneCamera p_type, float p_value);

		}; // class EventSenderSceneCamera		



		/**
		* \class eve::scene::EventSenderSceneLight
		* \brief Base scene light event sender.
		*/
		class EventSenderSceneLight
		{

		protected:
			eve::scene::EventSceneLight			m_evt;


			EVE_DISABLE_COPY(EventSenderSceneLight);
			EVE_PROTECT_DESTRUCTOR(EventSenderSceneLight);

		protected:
			/** \brief Class constructor. */
			EventSenderSceneLight(void);

		public:
			/** \brief Add event listener. */
			void addListener(eve::scene::EventListenerSceneLight * p_pListener);
			/** \brief Remove event listener. */
			void removeListener(eve::scene::EventListenerSceneLight * p_pListener);

		public:
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeSceneLight p_type, float p_value);
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeSceneLight p_type, bool p_value);
			/** \brief Notify event. */
			void notify(eve::scene::EventTypeSceneLight p_type, float p_valueFloat, bool p_valueBool);

		}; // class EventSenderSceneLight

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_EVENT_SENDER_H__
