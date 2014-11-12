
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
#ifndef __EVE_DIRECTX11_RESOURCEPOOL_H__
#define __EVE_DIRECTX11_RESOURCEPOOL_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

namespace eve 
{
	namespace dx11
	{
		template<typename T, typename F>
		class ResourcePoolElement
		{
			friend class ResourcePool<T, F>;

			public:
				EVE_FORCE_INLINE T* GetResource() { return this->m_pResource; }
				EVE_FORCE_INLINE F GetFormat() { return this->m_pFormat; }
				EVE_FORCE_INLINE Unlock() { this->m_bLocked = false; }
			private:
				T* m_pResource;
				F m_pFormat;
				bool m_bLocked;
		};

		template<typename T, typename F>
		class ResourcePool
		{
			public:
				ResourcePoolElement<T, F>* Lock(const F& format);
				void Unlock(T* resource);


			protected:
				T CreateResource(const T& desc);

			private:
				eve::dx11::Device* m_pDevice;
				std::vector<ResourcePoolElement<T,F>*> m_pResources;
				eve::thr::SpinLock* m_pLock;
		};


		template <typename T, typename F>
		ResourcePoolElement<T, F>* ResourcePool<T, F>::Lock(const F& format)
		{
			ResourcePoolElement<T,F>* result = NULL;

			this->m_pLock->lock();

			for (uint32_t i = 0; i < this->m_pResources.size(); i++)
			{
				ResourcePoolElement<T,F>* elem = this->m_pResources.at(i);
				if (elem->GetFormat() == format && elem->m_bLocked == false)
				{
					elem->m_bLocked = true;
					result = elem;
					break;
				}
			}

			if (!result)
			{
				result = new ResourcePoolElement<T,F>();
				result->m_pFormat = format;
				result->m_bLocked = true;
				result->m_pResource = this->CreateResource(format);

				this->m_pResources->push_back(result);
			}

			this->m_pLock->unlock();

			return result;
		}

		template <typename T, typename F>
		void ResourcePool<T, F>::Unlock(T* resource)
		{
			this->m_pLock->lock();

			for (uint32_t i = 0; i < this->m_pResources.size(); i++)
			{
				ResourcePoolElement<T,F>* elem = this->m_pResources.at(i);
				if (elem->GetResource() == resource)
				{
					elem->m_bLocked = false;
					break;
				}
			}

			this->m_pLock->unlock();
		}

	} //namespace dx11

} //namespace eve


#endif // __EVE_DIRECTX11_RESOURCEPOOL_H__