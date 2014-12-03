
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
#ifndef __EVE_OPENCL_CORE_COMMANDQUEUE_H__
#define __EVE_OPENCL_CORE_COMMANDQUEUE_H__

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_OPENCL_CORE_DEBUG_H__
#include "eve/ocl/core/Debug.h"
#endif

namespace eve
{
	namespace ocl
	{
		/** 
		* \class eve::ocl::CommandQueue
		*
		* \brief Create and maintain OpenCL command queue.
		*
		* \note extends eve::mem::Pointer
		*/
		class CommandQueue final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			cl_context						m_context;				//!< OpenCL context (read only).
			cl_device_id					m_device;				//!< Linked OpenCL device (read only).

			cl_command_queue				m_queue;				//!< OpenCL command queue.


		private:
			cl_int							m_err;					//!< Error code.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(CommandQueue);
			EVE_PROTECT_DESTRUCTOR(CommandQueue);

		public:
			/** \brief Create new pointer. */
			static eve::ocl::CommandQueue * create_ptr(cl_context p_context, cl_device_id p_device);


		private:
			/** \brief Class constructor. */
			explicit CommandQueue(cl_context p_context, cl_device_id p_device);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void);

		}; // class CommandQueue

	} // namespace ocl

} // namespace eve

#endif // __EVE_OPENCL_CORE_COMMANDQUEUE_H__
