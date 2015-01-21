
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
# 	OPTION_BUILD_ENABLE_DX11 is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

if( WIN32 AND OPTION_BUILD_ENABLE_DX11 )
	include( ${CMAKE_CURRENT_SOURCE_DIR}/dx11/core/CMakeLists.txt )

	
endif()
