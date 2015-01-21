
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Event.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Event.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Includes.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Listener.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Server.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TCallback.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TCallbackAuto.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TDelegate.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TDelegateAbstract.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TEvent.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TEventAbstract.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TQueue.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TStrategy.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Event" FILES ${SRCS} )
