#pragma once
#ifndef __EVE_DIRECTX11_STRUCTUREDBUFFER_H__
#define __EVE_DIRECTX11_STRUCTUREDBUFFER_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

namespace eve 
{
	namespace dx11
	{
		class StructuredBuffer
		{
			private:
				ID3D11UnorderedAccessView* m_pUnorderedView;
				ID3D11ShaderResourceView* m_pShaderView;
				ID3D11Buffer* m_pBuffer;
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_STRUCTUREDBUFFER_H__