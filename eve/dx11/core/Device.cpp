#include "eve/dx11/core/Device.h"

void eve::dx11::Device::Init()
{
	if (this->m_p_device)
	{
		return;
	}

	unsigned int flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_FEATURE_LEVEL levels[] = 
	{
		D3D_FEATURE_LEVEL_11_1, //Windows 8 only : add define to allow to choose
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_FEATURE_LEVEL level;

	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, &levels[0],ARRAYSIZE(levels), 
		D3D11_SDK_VERSION, &this->m_p_device, &level, &this->m_p_immediateContext);

	if (FAILED(hr))
	{
		EVE_LOG_ERROR("Unable to create device, error code:%d", hr);
	}

	this->m_featureLevel = (eve::dx11::FeatureLevel)level;
}

void eve::dx11::Device::dxRelease()
{
	EVE_SAFE_RELEASE(this->m_p_immediateContext);
	EVE_SAFE_RELEASE(this->m_p_device);
}

eve::dx11::Device::~Device()
{
	this->dxRelease();
}