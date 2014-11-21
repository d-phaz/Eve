
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
#ifndef __EVE_OPENCL_ENGINE_H__
#define __EVE_OPENCL_ENGINE_H__

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_OPENCL_DEBUG_H__
#include "eve/ocl/core/Debug.h"
#endif

namespace eve
{
	namespace ocl
	{
		/** 
		* \class eve::ocl::Engine
		*
		* \brief Detect and sort platform and device, depending on performances.
		*
		* \note extends eve::mem::Pointer
		*/
		class Engine final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			static eve::ocl::Engine *		m_p_instance;			//<! Class unique instance.


		private:
			cl_uint							m_numPlatforms;			//!< Number of available OpenCL platforms.
			cl_platform_id *				m_pPlatforms;			//!< Available OpenCL platforms.

			cl_uint							m_numDevices;			//!< Number of available OpenCL devices.
			cl_device_id *					m_pDevices;				//!< Available OpenCL devices.

			cl_device_id					m_deviceMaxFlops;		//!< Max flops device (compute units * clock frequency).
			cl_int							m_maxComputeUnits;		//!< Max flops device compute units number.
			cl_int							m_maxClockFrequency;	//!< Max flops device maximum clock frequency.
			cl_int							m_flops;				//!< Max flops device flops.

			cl_int							m_err;					//!< Error code.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Engine);
			EVE_PROTECT_DESTRUCTOR(Engine);

		public:
			/** \brief Create unique instance. */
			static eve::ocl::Engine * create_instance(void);
			/** \brief Release unique instance */
			static void release_instance(void);


		private:
			/** \brief Class constructor. */
			explicit Engine(void);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void);
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief get available platform(s) number. */
			static cl_uint				get_platforms_num(void);
			/** \brief Get available platform(s). */
			static cl_platform_id *		get_platforms(void);


		public:
			/** \brief get available device(s) number. */
			static cl_uint				get_devices_num(void);
			/** \brief Get available device(s). */
			static cl_device_id *		get_devices(void);


		public:
			/** \brief Get maximum flops device (fastest one). */
			static cl_device_id			get_max_flops_device(void);
			/** \brief Get maximum flops device (fastest one) maximum compute units number. */
			static cl_int				get_max_compute_units(void);
			/** \brief Get maximum flops device (fastest one) maximum clock frequency. */
			static cl_int				get_max_clock_frequency(void);
			/** \brief Get maximum flops device (fastest one) flops. */
			static cl_int				get_flops(void);

		}; // class Engine

	} // namespace ocl

} // namespace eve


//=================================================================================================
EVE_FORCE_INLINE cl_uint 			eve::ocl::Engine::get_platforms_num(void)		{ EVE_ASSERT(m_p_instance); return m_p_instance->m_numPlatforms;		}
EVE_FORCE_INLINE cl_platform_id *	eve::ocl::Engine::get_platforms(void)			{ EVE_ASSERT(m_p_instance); return m_p_instance->m_pPlatforms;			}


//=================================================================================================
EVE_FORCE_INLINE cl_uint			eve::ocl::Engine::get_devices_num(void)			{ EVE_ASSERT(m_p_instance); return m_p_instance->m_numDevices;			}
EVE_FORCE_INLINE cl_device_id *		eve::ocl::Engine::get_devices(void)				{ EVE_ASSERT(m_p_instance); return m_p_instance->m_pDevices;			}


//=================================================================================================
EVE_FORCE_INLINE cl_device_id		eve::ocl::Engine::get_max_flops_device(void)	{ EVE_ASSERT(m_p_instance); return m_p_instance->m_deviceMaxFlops;		}
EVE_FORCE_INLINE cl_int				eve::ocl::Engine::get_max_compute_units(void)	{ EVE_ASSERT(m_p_instance); return m_p_instance->m_maxComputeUnits;		}
EVE_FORCE_INLINE cl_int				eve::ocl::Engine::get_max_clock_frequency(void)	{ EVE_ASSERT(m_p_instance); return m_p_instance->m_maxClockFrequency;	}
EVE_FORCE_INLINE cl_int				eve::ocl::Engine::get_flops(void)				{ EVE_ASSERT(m_p_instance); return m_p_instance->m_flops;				}

#endif // __EVE_OPENCL_ENGINE_H__
