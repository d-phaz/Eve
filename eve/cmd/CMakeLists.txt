
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS  
	 ${CMAKE_CURRENT_SOURCE_DIR}/cmd/Command.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/cmd/Command.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/cmd/Stack.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/cmd/Stack.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Command" FILES ${SRCS} )
