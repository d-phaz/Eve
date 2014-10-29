#pragma once
#ifndef __EVE_DIRECTX11_CONSTANTBUFFER_H__
#define __EVE_DIRECTX11_CONSTANTBUFFER_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_CONTEXT_H__
	#include "Context.h"
#endif

namespace eve 
{
	namespace dx11
	{
		class ConstantBuffer
		{
			public:
				ConstantBuffer();

				template <typename T> 
				void Update(eve::dx11::Context* context, T& value);
			private:
				void Init(eve::dx11::Device* device, uint32_t size);
				void Release();
				ID3D11Buffer* m_p_buffer;
		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_CONSTANTBUFFER_H__