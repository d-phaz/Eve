
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set(SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/BlendStates.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/BlendStates.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ConstantBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ConstantBuffer.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Context.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Context.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/DepthStencil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/DepthStencil.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/DepthStencilStates.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/DepthStencilStates.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Device.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Device.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Enums.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Formats.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Formats.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Includes.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/IndexBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/IndexBuffer.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Macros.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RasterizerStates.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RasterizerStates.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RawBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RawBuffer.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/Renderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RenderTarget.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RenderTarget.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RenderTargetStack.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/RenderTargetStack.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ResourceFactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ResourceFactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ResourcePool.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ResourcePool.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/SamplerStates.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/SamplerStates.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/StructuredBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/StructuredBuffer.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ShaderCompiler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ShaderCompiler.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ShaderInstance.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/ShaderInstance.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/SwapChain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/SwapChain.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/SwapChain.h
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/VertexBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/VertexBuffer.h
	)

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "DirectX11\\Core" FILES ${SRCS} )
