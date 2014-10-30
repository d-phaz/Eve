#pragma once
#ifndef __EVE_DIRECTX11_ENUMS_H__
#define __EVE_DIRECTX11_ENUMS_H__

#ifndef __EVE_DIRECTX11_MACROS_H__
	#include "Macros.h"
#endif

#ifndef __EVE_DIRECTX11_INCLUDES_H__
	#include "Includes.h"
#endif


namespace eve 
{
	namespace dx11
	{
		/**
		* \def eve::dx11::FeatureLevel
		* \brief DirectX Device Feature Level
		*
		* \note Feature level 9 is mostly for mobile devices (or really old machines)
		*/
		enum class FeatureLevel : uint32_t
		{
			f11_1 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
			f11 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
			f10_1 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1,
			f10 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0,
			f09_3 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_3,
			f09_2 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_2,
			f09_1 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_1
		};

		/**
		* \def eve::dx11::FeatureLevel
		* \brief DirectX shader stages
		*/
		enum class ShaderStage : uint32_t
		{
			Vertex = 1,
			Hull = 2,
			Domain = 4,
			Geometry = 8,
			Pixel = 16,
			Compute = 32
		};

		/**
		* \def eve::dx11::DepthFormatDepthView
		* \brief Depth buffer format enumeration
		* Use to create depth stencil view, use DepthFormatResource to create Texture
		*/
		enum class DepthFormatDepthView : uint32_t
		{
			d16 = DXGI_FORMAT::DXGI_FORMAT_D16_UNORM, 
			d24s8 = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT,
			d32 = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT,
			d32s8 = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT_S8X24_UINT
		};

		/**
		* \def eve::dx11::DepthFormatResource
		* \brief Depth buffer format enumeration for Texture creation
		* This forces resource format as typeless to allow depth/stencil reads after render
		*/
		enum class DepthFormatResource : uint32_t
		{
			d16 = DXGI_FORMAT::DXGI_FORMAT_R16_TYPELESS,
			d24s8 = DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS,
			d32 = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS,
			d32s8 = DXGI_FORMAT::DXGI_FORMAT_R32G8X24_TYPELESS
		};

		/**
		* \def eve::dx11::DepthFormatShaderView
		* \brief Depth buffer format enumeration for ShaderResourceView creation
		*/
		enum class DepthFormatShaderView : uint32_t
		{
			d16 = DXGI_FORMAT::DXGI_FORMAT_R16_UNORM,
			d24s8 = DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			d32 = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,
			d32s8 = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS
		};

		/**
		* \def eve::dx11::StencilFormatShaderView
		* \brief Stencil buffer format enumeration for ShaderResourceView creation
		*
		* \note Since not all Depth formats have a stencil flag, this may return DXGI_FORMAT_UNKNOWN (0)
		*/
		enum class StencilFormatShaderView : uint32_t
		{
			d16 = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN,
			d24s8 = DXGI_FORMAT::DXGI_FORMAT_X24_TYPELESS_G8_UINT,
			d32 = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN,
			d32s8 = DXGI_FORMAT::DXGI_FORMAT_X32_TYPELESS_G8X24_UINT
		};

		/**
		* \def eve::dx11::StructuredBufferMode
		* \brief Structured Buffer mode for Unordered access view
		*/
		enum class StructuredBufferMode : uint32_t
		{
			Default = 0, 
			Append = D3D11_BUFFER_UAV_FLAG::D3D11_BUFFER_UAV_FLAG_APPEND,
			Counter = D3D11_BUFFER_UAV_FLAG::D3D11_BUFFER_UAV_FLAG_COUNTER
		};

		/**
		* \def eve::dx11::RawBufferWriteMode
		* \brief Write mode for raw buffer
		*/
		enum class RawBufferWriteMode : uint32_t
		{
			None = 0,
			StreamOut = 1,
			UnorderedAccess = 2
		};

		/**
		* \def eve::dx11::IndexBufferFormat
		* \brief format for index buffer (either uint16 or uint32)
		*/
		enum class IndexBufferFormat : uint32_t
		{
			Short = DXGI_FORMAT::DXGI_FORMAT_R16_UINT,
			Int = DXGI_FORMAT::DXGI_FORMAT_R32_UINT
		};

		/**
		* \def eve::dx11::ResourceUsageFormat
		* \brief Preset for resource format usages
		*/
		enum class ResourceUsage : uint32_t
		{
			Default = D3D11_USAGE::D3D11_USAGE_DEFAULT, //Writeable bu gpu
			Immutable = D3D11_USAGE::D3D11_USAGE_IMMUTABLE, //Immutable, can't be modified, initial data must be provided
			Dynamic = D3D11_USAGE::D3D11_USAGE_DYNAMIC, //Dynamic , writeable by CPU
			Staging = D3D11_USAGE::D3D11_USAGE_STAGING //Staging, readable by CPU (to retrieve data for debug)
		};

	} //namespace dx11

} //namespace eve

#endif // __EVE_DIRECTX11_ENUMS_H__