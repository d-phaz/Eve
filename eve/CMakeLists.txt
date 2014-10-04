
###################################################################################################
# NOTE:
# 	BASE_SOURCE_PATH is defined in ROOT\CMakeLists.txt
# 	PATH_TO_EXTERNAL is defined in ROOT\CMakeLists.txt
#	OPTION_BUILD_USE_VLD is defined in ROOT\CMakeLists.txt
###################################################################################################


###################################################################################################
# NOTE:
#	These are set in root/PRODUCT_INFO.cmake
#
#  		PRODUCT_VENDOR_NAME
#  		PRODUCT_PRODUCT_NAME
#		PRODUCT_ICON_INSTALL_NAME
#		PRODUCT_ICON_UNINSTALL_NAME
#  		PRODUCT_VERSION_MAJOR
#  		PRODUCT_VERSION_MINOR
#  		PRODUCT_VERSION_PATCH
#  		PRODUCT_VERSION
#		PRODUCT_WEBSITE
#  		PRODUCT_SUPPORT_EMAIL
###################################################################################################


# Project.
###################################################################################################
project( ${PRODUCT_PRODUCT_NAME} )
	 
	
# CMake Configuration.
###################################################################################################
# Find includes in corresponding build directories
set( CMAKE_INCLUDE_CURRENT_DIR ON )
# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC TRUE )
set( CMAKE_AUTOMOC_RELAXED_MODE TRUE )


# Parse files in project.
###################################################################################################
set( SOURCE_FILES )
set( LIBS )


# App.
#################################################
set( APP_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/App.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/app/App.h )

set( SOURCE_FILES ${SOURCE_FILES} ${APP_SRCS} )
source_group( "Application" FILES ${APP_SRCS} )


# Core.
#################################################
set( CORE_SRCS 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Flags.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Macro.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Renderer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/SystemDefinition.h )

set( SOURCE_FILES ${SOURCE_FILES} ${CORE_SRCS} )
source_group( "Core" FILES ${CORE_SRCS} )


# Event.
#################################################
set( EVENT_SRCS  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Event.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Event.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Includes.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TCallback.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TCallbackAuto.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TDelegate.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TDelegateAbstract.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TEvent.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TEventAbstract.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TQueue.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/TStrategy.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/evt/Server.h  )

set( SOURCE_FILES ${SOURCE_FILES} ${EVENT_SRCS} )
source_group( "Event" FILES ${EVENT_SRCS} )


# Files.
#################################################
set( FILES_SRCS 
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Utils.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/files/Utils.h  )

set( SOURCE_FILES ${SOURCE_FILES} ${FILES_SRCS} )
source_group( "Files" FILES ${FILES_SRCS} )


# OpenGL.
#################################################
set( OPENGL_SRCS 
	 ${CMAKE_CURRENT_SOURCE_DIR}/gl/win32/Context.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/gl/win32/Context.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/gl/win32/PixelFormat.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/gl/win32/PixelFormat.h  )

set( SOURCE_FILES ${SOURCE_FILES} ${OPENGL_SRCS} )
source_group( "OpenGL" FILES ${OPENGL_SRCS} )


# Memory.
#################################################
set( MEMORY_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Pointer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Pointer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mem/Scoped.h )

set( SOURCE_FILES ${SOURCE_FILES} ${MEMORY_SRCS} )
source_group( "Memory" FILES ${MEMORY_SRCS} )


# Messaging.
#################################################
set( MESSAGING_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Error.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Error.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Server.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/mess/Server.cpp )

set( SOURCE_FILES ${SOURCE_FILES} ${MESSAGING_SRCS} )
source_group( "Messaging" FILES ${MESSAGING_SRCS} )


# System.
#################################################
set( SYSTEM_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/Includes.h )
	 
set( SYSTEM_SRCS	
	 ${SYSTEM_SRCS}  
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Event.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Event.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Mouse.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Render.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/Render.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/View.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/sys/shared/View.h )
	 
set( SYSTEM_SRCS
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

set( SOURCE_FILES ${SOURCE_FILES} ${SYSTEM_SRCS} )
source_group( "System" FILES ${SYSTEM_SRCS} )


# Thread.
#################################################
set( THREADING_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Barrier.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Barrier.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Condition.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Condition.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Fence.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Fence.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Lock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Lock.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Mutex.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Mutex.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ScopedFence.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/SpinLock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/SpinLock.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Thread.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Thread.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadedWork.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadedWork.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadedWorkIO.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadedWorkIO.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadPool.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/ThreadPool.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Utils.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Utils.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Worker.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/thr/Worker.h )

set( SOURCE_FILES ${SOURCE_FILES} ${THREADING_SRCS} )
source_group( "Threading" FILES ${THREADING_SRCS} )

	
# Visual Leak Detector.
#################################################
if( WIN32 AND OPTION_BUILD_USE_VLD )
	include("${BASE_SOURCE_PATH}/CMake/FindVLD.cmake")
	if( VLD_FOUND )
		include_directories( ${VLD_INCLUDE_DIRS} )
		set(LIBS ${LIBS} ${VLD_LIBRARIES})
	endif()
endif()


# Version.h
#################################################
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/generated/Version.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/generated/Version.h )
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/generated/Version.h )
set_source_files_properties( ${CMAKE_CURRENT_SOURCE_DIR}/generated/Version.h PROPERTIES GENERATED true )
			
# External.h
#################################################
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/generated/External.h.in
				${CMAKE_CURRENT_SOURCE_DIR}/generated/External.h )
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/generated/External.h )
set_source_files_properties( ${CMAKE_CURRENT_SOURCE_DIR}/generated/External.h PROPERTIES GENERATED true )


# Include directories.
###################################################################################################	
include_directories( ${BASE_SOURCE_PATH} )
include_directories( ${BASE_SOURCE_PATH}/external/include )	


# Libraries.
###################################################################################################	 
link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

# Windows 
#################################################
if( WIN32 )
	set( LIBS
		 ${LIBS}
		 kernel32.lib ) 	 

	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR} )
	endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		
	if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR} )
	endif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
endif( WIN32 )


# OSX 
#################################################
if( APPLE )		 
	# External library directory
	if( OPTION_BUILD_TYPE_DEBUG )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_osx/Debug )
	endif( OPTION_BUILD_TYPE_DEBUG )	 

	if( OPTION_BUILD_TYPE_RELEASE )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_osx/Release )
	endif( OPTION_BUILD_TYPE_RELEASE )

	macro( find_required_library TARGET_LIB )
        find_library( FOUND_LIB ${TARGET_LIB} )

        if( NOT FOUND_LIB )
            message( FATAL_ERROR "${TARGET_LIB} not found" )
        else()
            message( "\n ${TARGET_LIB} found at ${FOUND_LIB} \n adding ${TARGET_LIB} to link. \n")
        endif()
        mark_as_advanced( FOUND_LIB )
        
        set( LIBS ${LIBS} ${FOUND_LIB} )
    endmacro()

    find_required_library( AppKit )
    find_required_library( CFNetwork )
    find_required_library( CoreFoundation )
    find_required_library( CoreServices )
    find_required_library( Security )
endif()


# # POCO
# #################################################
# add_definitions( -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS )
# if( WIN32 )
	# if( OPTION_BUILD_TYPE_DEBUG )
		# set( LIBS ${LIBS} PocoFoundationmdd.lib ) 
	# else()
		# set( LIBS ${LIBS} PocoFoundationmd.lib )
	# endif()
# endif()

# if( APPLE )
	# if( OPTION_BUILD_TYPE_DEBUG )
		# set( LIBS ${LIBS} libPocoFoundationmdd.a ) 
	# else()
		# set( LIBS ${LIBS} libPocoFoundationmd.a )
	# endif()
# endif()


# Windows Resource file.
###################################################################################################
if( WIN32 )
	# Generate rc files
	configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/${PRODUCT_PRODUCT_NAME}.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc @ONLY )
	# Set properties to generated files
	set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc PROPERTIES GENERATED TRUE )	
	set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc )
endif()


# Create main library.
###################################################################################################
set( lib_name "${PRODUCT_PRODUCT_NAME}" )
add_library( ${lib_name} STATIC ${SOURCE_FILES} )

if( WIN32 )
	if( ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
		set_target_properties( ${lib_name} PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
	elseif( ${CMAKE_SIZEOF_VOID_P} EQUAL 4)
		set_target_properties( ${lib_name} PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x86")
	endif()	
	
	configure_file( ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_ICON_INSTALL_NAME}.ico COPYONLY )	
	# install( FILES  ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico DESTINATION . COMPONENT ${PRODUCT_NAME} )
endif()

# Link packages to library.
if( APPLE )
	# Set executable properties.
	set_target_properties( ${lib_name} PROPERTIES MACOSX_RPATH 0 )
	set_target_properties( ${lib_name} PROPERTIES LINK_FLAGS " -framework AppKit  -framework ApplicationServices -framework CoreFoundation -framework CoreServices -framework DiskArbitration -framework Security" )
endif()	
	
target_link_libraries( ${lib_name} ${LIBS} )














 
