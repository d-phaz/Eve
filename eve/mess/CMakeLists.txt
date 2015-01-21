
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Error.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Error.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Server.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Server.cpp )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Messaging" FILES ${SRCS} )
