
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Display.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Display.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Frame.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Frame.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Layer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Layer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Renderer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Renderer.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Widget.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Widget.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "UI" FILES ${SRCS} )
