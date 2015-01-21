
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${SYSTEM_SRCS} 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Cursor.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Cursor.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Display.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Display.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Info.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Info.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Keyboard.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Keyboard.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/MessagePump.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/MessagePump.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Notification.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Notification.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Node.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Node.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Window.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/win32/Window.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "System\\win32" FILES ${SRCS} )
