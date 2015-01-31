
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
include( ${CMAKE_CURRENT_SOURCE_DIR}/math/core/CMakeLists.txt )

set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/MatrixDecompose.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/MatrixDecompose.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/TBox.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/TCamera.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/TLight.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/TMesh.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/TRay.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/Types.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Math" FILES ${SRCS} )
