
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS 
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Utils.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Utils.h  )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Files" FILES ${SRCS} )
