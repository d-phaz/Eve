
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/App.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/App.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Application" FILES ${SRCS} )
