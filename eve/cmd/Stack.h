
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
#ifndef __EVE_COMMAND_STACK_H__ 
#define __EVE_COMMAND_STACK_H__

#ifndef __EVE_COMMAND_COMMAND_H__
#include "eve/cmd/Command.h"
#endif


namespace eve
{
	namespace cmd
	{
		/**
		* \class eve::cmd::CommandStack
		* \brief Command FIFO stack used to undo/redo.
		* \note extends eve::mem::Pointer
		*/
		class CommandStack final
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			int64_t						_cursor;			//!< Current command id.
			std::list<Command*> *		_p_commands;		//!< Commands FIFO list.
			uint32_t					_max_size;			//!< Command list max size (default to 40).


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(CommandStack);
			EVE_PUBLIC_DESTRUCTOR(CommandStack);

		public:
			/** \brief Class constructor. */
			explicit CommandStack(void);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Add new command to stack. */
			void add(eve::evt::CallbackAuto * p_undo, eve::evt::CallbackAuto * p_redo);


		public:
			/** \brief Execute undo callback. */
			void undo(void);
			/** \brief Execute redo callback. */
			void redo(void);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get command list max size. */
			const uint32_t get_max_size(void) const;
			/** \brief Set command list max size. */
			void set_max_size(uint32_t p_size);


		public:
			/** \brief Get undo possible state. */
			const bool can_undo(void) const;
			/** \brief Get redo possible state. */
			const bool can_redo(void) const;

		}; // class CommandStack

	} // namespace cmd

} // namespace eve


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
EVE_FORCE_INLINE const uint32_t eve::cmd::CommandStack::get_max_size(void) const { return _max_size; }


//=================================================================================================
EVE_FORCE_INLINE const bool eve::cmd::CommandStack::can_undo(void) const { return (_p_commands->size() > 0 && _cursor > 0); }
EVE_FORCE_INLINE const bool eve::cmd::CommandStack::can_redo(void) const { return (_p_commands->size() > 0 && _cursor < _p_commands->size()); }

#endif // __EVE_COMMAND_STACK_H__
