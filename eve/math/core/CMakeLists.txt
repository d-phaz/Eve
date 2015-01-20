
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/Math.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/Simd.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TMatrix.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TMatrix22.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TMatrix33.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TMatrix44.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TQuaternion.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TVector.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TVector2.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TVector3.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/TVector4.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/math/core/Types.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Math\\Core" FILES ${SRCS} )
