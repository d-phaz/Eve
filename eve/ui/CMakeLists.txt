
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "UI" FILES ${SRCS} )
