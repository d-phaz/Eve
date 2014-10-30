#include "eve/dx11/core/SwapChain.h"

eve::dx11::SwapChain::SwapChain()
{
	this->m_pDevice = NULL;
	this->m_p_texture = NULL;
	this->m_p_renderView = NULL;
	this->m_p_swapChain = NULL;
	this->m_bEnableVSync = false;
}

eve::dx11::SwapChain::~SwapChain()
{
	EVE_SAFE_RELEASE(this->m_p_texture);
	EVE_SAFE_RELEASE(this->m_p_renderView);
	EVE_SAFE_RELEASE(this->m_p_swapChain);
}

void eve::dx11::SwapChain::Init(eve::dx11::Device* device, HWND windowHandle)
{
	if (this->m_p_swapChain)
	{
		return; //Already initialized
	}

	this->m_pDevice = device;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc,sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	HRESULT hr = device->GetFactory()->CreateSwapChain(device->GetDevice(), &swapChainDesc, &this->m_p_swapChain);

	this->InitTextureAndView();
}

void eve::dx11::SwapChain::InitTextureAndView()
{
	ID3D11Texture2D* texture;
	this->m_p_swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)(&texture));
	ULONG res = texture->Release();
	this->m_p_texture = texture;
	this->m_pDevice->GetDevice()->CreateRenderTargetView(texture, NULL, &this->m_p_renderView);
}

void eve::dx11::SwapChain::Resize()
{
	EVE_SAFE_RELEASE(this->m_p_renderView);
	EVE_SAFE_RELEASE(this->m_p_texture);

	this->m_p_swapChain->ResizeBuffers(0,0,0,DXGI_FORMAT::DXGI_FORMAT_UNKNOWN,0);

	this->InitTextureAndView();
}

void eve::dx11::SwapChain::Present()
{
	this->m_p_swapChain->Present(this->m_bEnableVSync ? 1 : 0, 0);
}