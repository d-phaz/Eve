
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Flags.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Macro.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Renderer.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Renderer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/SystemDefinition.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Core" FILES ${SRCS} )
