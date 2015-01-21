
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 # ${CMAKE_CURRENT_SOURCE_DIR}/mem/Allocator.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Allocator.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Pointer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Pointer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Scoped.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Memory" FILES ${SRCS} )
