
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
#ifndef __EVE_OPENCL_CORE_KERNEL_H__
#define __EVE_OPENCL_CORE_KERNEL_H__

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
		* \class eve::ocl::Kernel
		*
		* \brief Create and maintain OpenCL kernel.
		*
		* \note extends eve::mem::Pointer
		*/
		class Kernel final
			: public eve::mem::Pointer
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			cl_program						m_program;				//!< OpenCL program (read only).
			std::string						m_name;					//!< Kernel name.
			cl_kernel						m_kernel;				//!< OpenCL kernel.

		private:
			cl_int							m_err;					//!< Error code.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Kernel);
			EVE_PUBLIC_DESTRUCTOR(Kernel);

		public:
			/** \brief Create new pointer. */
			static eve::ocl::Kernel * create_ptr(cl_program p_program, const std::string & p_name);


		public:
			/** \brief Class constructor. */
			explicit Kernel(cl_program p_program, const std::string & p_name);


		public:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void);


		public:
			/** \brief Set argument. Arguments are indexed using declaration order in kernel method. */
			void setArgument(cl_uint p_index, size_t p_size, void * p_arg);

		}; // class Kernel

	} // namespace ocl

} // namespace eve

#endif // __EVE_OPENCL_CORE_KERNEL_H__
