#include "eve/dx11/core/Device.h"

eve::dx11::Device::Device()
{
	this->m_p_device = NULL;
	this->m_p_immediateContext = NULL;
	this->m_p_factory = NULL;
}

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

	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;

	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, &levels[0],ARRAYSIZE(levels), 
		D3D11_SDK_VERSION, &device, &level, &immediateContext);

	if (FAILED(hr))
	{
		EVE_LOG_ERROR("Unable to create device, error code:%d", hr);
	}

	this->m_p_device = device;
	this->m_p_immediateContext = immediateContext;

	/*device->QueryInterface(__uuidof(ID3D11Device2),(void**)(&this->m_p_device));
	immediateContext->QueryInterface(__uuidof(ID3D11DeviceContext2),(void**)(&this->m_p_immediateContext));*/
	this->m_featureLevel = (eve::dx11::FeatureLevel)level;

	IDXGIDevice1* dxgidevice;
	device->QueryInterface(__uuidof(IDXGIDevice1),(void**)(&dxgidevice));

	IDXGIAdapter* adapter;
	dxgidevice->GetAdapter(&adapter);

	IDXGIAdapter1* adapter1 = (IDXGIAdapter1*)adapter;
	adapter1->GetParent(__uuidof(IDXGIFactory1),(void**)(&this->m_p_factory));
}

void eve::dx11::Device::dxRelease()
{
	EVE_SAFE_RELEASE(this->m_p_immediateContext);
	EVE_SAFE_RELEASE(this->m_p_device);
	EVE_SAFE_RELEASE(this->m_p_factory);
}

eve::dx11::Device::~Device()
{
	this->dxRelease();
}