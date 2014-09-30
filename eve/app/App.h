
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
#ifndef __EVE_APPLICATION_APP_H__
#define __EVE_APPLICATION_APP_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace app
	{
		/** 
		* \class eve::app::App
		*
		* \brief Main application class using single or multiple window.
		*
		* \note extends eve::mem::Pointer
		*/
		class App final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		private:
			static eve::app::App *		m_p_instance;		//!< Class unique instance.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(App);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(App);


		private:
			/** \brief Create unique instance. */
			static eve::app::App * create_instance(void);
			/** \brief Get unique instance. */
			static eve::app::App * get_instance(void);
			/** \brief Release unique instance */
			static void release_instance(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			void cb_evtApplicationExit(void);

		}; // class App

	} // namespace app

} // namespace eve

#if defined(EVE_OS_DARWIN)
#define EVE_APPLICATION( APP, RENDERER )									\
	int main(int argc, char * const argv[]) 								\
	{																		\
		//cinder::app::AppBasic::prepareLaunch();								\
		//cinder::app::AppBasic *app = new APP;								\
		//cinder::app::RendererRef ren(new RENDERER);							\
		//cinder::app::AppBasic::executeLaunch(app, ren, #APP, argc, argv);	\
		//cinder::app::AppBasic::cleanupLaunch();								\
		return 0;															\
	}

#elif defined(EVE_OS_WIN)
#define EVE_APPLICATION( APP, RENDERER )																	\
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 		\
	{																										\
		//cinder::app::AppBasic::prepareLaunch();																\
		//cinder::app::AppBasic *app = new APP;																\
		//cinder::app::RendererRef ren(new RENDERER);															\
		//cinder::app::AppBasic::executeLaunch(app, ren, #APP);												\
		//cinder::app::AppBasic::cleanupLaunch();																\
		return 0;																							\
	}
#endif


#endif // __EVE_APPLICATION_APP_H__
