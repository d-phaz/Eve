
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/Attractor.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/AttractorModel.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/BufferBaseModel.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/BufferBaseModel.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/IAttractorUpdate.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/ParticleManager.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/ParticleManager.h   
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/particule/RayCastAttractorUpdate.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "OpenGL\\particule" FILES ${SRCS} )
	
