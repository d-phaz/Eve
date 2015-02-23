
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Layer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Layer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Output.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Output.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Renderer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Renderer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/View.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Widget.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Widget.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Window.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/ui/Window.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "UI" FILES ${SRCS} )
