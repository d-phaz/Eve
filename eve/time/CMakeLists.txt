
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Absolute.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Absolute.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Clock.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Clock.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Relative.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Relative.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Timer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Timer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Utils.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/time/Utils.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Time" FILES ${SRCS} )
