#pragma once
#ifndef __EVE_DIRECTX11_FORMATS_H__
#define __EVE_DIRECTX11_FORMATS_H__

#ifndef __EVE_DIRECTX11_DEVICE_H__
	#include "Device.h"
#endif

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif


namespace eve 
{
	namespace dx11
	{
		D3D11_CPU_ACCESS_FLAG GetCpuAccessFlag(eve::dx11::ResourceUsage format);
		D3D11_BIND_FLAG GetExcludeBindFlag(eve::dx11::ResourceUsage format); //Returns a list of bind flags to remove from usage
		
		bool AllowResourceView(eve::dx11::ResourceUsage format);
		bool AllowUnorderedView(eve::dx11::ResourceUsage format);
		
		/**
		* \class eve::dx11::ResourceUsageFormat
		*
		* \brief Contains presets for resource usage, and allows to set description accordingly
		*
		*/
		class ResourceUsageFormat
		{
			public:
				eve::dx11::ResourceUsage Usage;
			public:
				void SetBufferDesc(D3D11_BUFFER_DESC* bufferDesc);
				void SetTexture1DDesc(D3D11_TEXTURE1D_DESC* texture1dDesc);
				void SetTexture2DDesc(D3D11_TEXTURE2D_DESC* texture2dDesc);
				void SetTexture3DDesc(D3D11_TEXTURE3D_DESC* texture3dDesc);
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_FORMATS_H__