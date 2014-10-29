#pragma once
#ifndef __EVE_DIRECTX11_DEVICE_H__
#define __EVE_DIRECTX11_DEVICE_H__

#ifndef __EVE_DIRECTX11_ENUMS_H__
	#include "Enums.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

namespace eve { namespace dx11 { class Context; } }

namespace eve 
{
	namespace dx11
	{
		/**
		* \class eve::dx11::Device
		*
		* \brief DirectX11 Device
		* Create a DirectX11 Device
		*
		*/
		class Device
		{
			friend class eve::dx11::Context;

			private:
				ID3D11Device* m_p_device; //Device pointer
				ID3D11DeviceContext* m_p_immediateContext; //Immediate context to submit commands to GPU
				eve::dx11::FeatureLevel m_featureLevel; //Real device feature level

			private:
				void Init();
				void dxRelease();

			protected:
				EVE_FORCE_INLINE ID3D11Device* GetDevice() { return this->m_p_device; }
				EVE_FORCE_INLINE ID3D11DeviceContext* GetImmediateContext() { return this->m_p_immediateContext; }
		
				~Device();


		};
	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_DEVICE_H__