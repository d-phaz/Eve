
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
#	OPENCL_FOUND is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
include( ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/CMakeLists.txt )

set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/Includes.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "System" FILES ${SRCS} )
