
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS  
	 ${CMAKE_CURRENT_SOURCE_DIR}/io/Image.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/io/Image.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/io/Utils.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/io/Utils.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Input / Output" FILES ${SRCS} )
