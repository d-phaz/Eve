#include "eve/dx11/core/Formats.h"

D3D11_CPU_ACCESS_FLAG eve::dx11::GetCpuAccessFlag(eve::dx11::ResourceUsage format)
{
	switch (format)
	{
		case eve::dx11::ResourceUsage::Default:
			return (D3D11_CPU_ACCESS_FLAG)0;
		case eve::dx11::ResourceUsage::Immutable:
			return (D3D11_CPU_ACCESS_FLAG)0;		
		case eve::dx11::ResourceUsage::Dynamic:
			return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		case eve::dx11::ResourceUsage::Staging:
			return D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
		default:
			return (D3D11_CPU_ACCESS_FLAG)0;
	}
}

D3D11_BIND_FLAG eve::dx11::GetExcludeBindFlag(eve::dx11::ResourceUsage format)
{
	switch (format)
	{
		case eve::dx11::ResourceUsage::Default:
			return (D3D11_BIND_FLAG)0;
		case eve::dx11::ResourceUsage::Immutable:
			return (D3D11_BIND_FLAG)(D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS); //No gpu write on immutables		
		case eve::dx11::ResourceUsage::Dynamic:
			return (D3D11_BIND_FLAG)(D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS);
		case eve::dx11::ResourceUsage::Staging:
			return (D3D11_BIND_FLAG)0xFFFFFFFF; //Staging can't be bound anywhere
		default:
			return (D3D11_BIND_FLAG)0;
	}
}

bool eve::dx11::AllowResourceView(eve::dx11::ResourceUsage format)
{
	return format != eve::dx11::ResourceUsage::Staging;
}

bool eve::dx11::AllowUnorderedView(eve::dx11::ResourceUsage format)
{
	return format == eve::dx11::ResourceUsage::Default;
}

void eve::dx11::ResourceUsageFormat::SetBufferDesc(D3D11_BUFFER_DESC* bufferDesc)
{
	bufferDesc->Usage = (D3D11_USAGE)this->Usage;
	bufferDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	bufferDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture1DDesc(D3D11_TEXTURE1D_DESC* texture1dDesc)
{
	texture1dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture1dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture1dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture2DDesc(D3D11_TEXTURE2D_DESC* texture2dDesc)
{
	texture2dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture2dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture2dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}

void eve::dx11::ResourceUsageFormat::SetTexture3DDesc(D3D11_TEXTURE3D_DESC* texture3dDesc)
{
	texture3dDesc->Usage = (D3D11_USAGE)this->Usage;
	texture3dDesc->CPUAccessFlags = eve::dx11::GetCpuAccessFlag(this->Usage);
	texture3dDesc->BindFlags &= ~eve::dx11::GetExcludeBindFlag(this->Usage);
}