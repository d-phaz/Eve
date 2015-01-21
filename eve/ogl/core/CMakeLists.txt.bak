
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Debug.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Debug.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/External.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Fbo.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Fbo.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Macro.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Object.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Object.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Pbo.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Pbo.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Renderer.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Renderer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Shader.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Shader.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Texture.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Texture.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Uniform.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Uniform.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Vao.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/Vao.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "OpenGL\\core" FILES ${SRCS} )
	 
if(WIN32)
	set( SRCS 
		${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/win32/Context.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/win32/Context.h 
		${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/win32/PixelFormat.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ogl/core/win32/PixelFormat.h  )

	set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
	source_group( "OpenGL\\core\\win32" FILES ${SRCS} )
endif()
