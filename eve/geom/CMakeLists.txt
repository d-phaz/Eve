
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS  
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Cube.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Cube.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Includes.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Plane.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Plane.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Sphere.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/geom/Sphere.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Geometry" FILES ${SRCS} )
