
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Event.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Event.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/EventListener.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/EventListener.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/EventSender.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/EventSender.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Material.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Material.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Mesh.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Mesh.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Object.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Object.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Skeleton.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/scene/Skeleton.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "Scene" FILES ${SRCS} )
