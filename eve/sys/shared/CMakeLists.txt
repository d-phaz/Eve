
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS	
	 ${SYSTEM_SRCS}  
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Event.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Event.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Mouse.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Render.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Render.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/View.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/View.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "System\\shared" FILES ${SRCS} )
