
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
#ifndef __EVE_COMMAND_COMMAND_H__ 
#define __EVE_COMMAND_COMMAND_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_TCALLBACK_AUTO_H__
#include "eve/evt/TCallbackAuto.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif


namespace eve
{
	namespace cmd
	{
		
		/**
		* \class eve::cmd::Command
		* \brief Command used by undo/redo stack.
		*/
		class Command final
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			eve::evt::CallbackAuto *		_cb_undo;	//!< Undo callback.
			eve::evt::CallbackAuto *		_cb_redo;	//!< Redo callback.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Command);

		public:
			/** \brief Class constructor. */
			explicit Command(void);
			/** \brief Class destructor. */
			virtual ~Command(void);


		public:
			/** \brief Alloc and init class members. */
			void init(eve::evt::CallbackAuto * p_undo, eve::evt::CallbackAuto * p_redo);
			/** \brief Release and delete class members. */
			void release(void);


		public:
			/** \brief Execute undo callback. */
			void undo(void);
			/** \brief Execute redo callback. */
			void redo(void);

		}; // class Command

	} // namespace cmd

} // namespace eve

#endif // __EVE_COMMAND_COMMAND_H__
