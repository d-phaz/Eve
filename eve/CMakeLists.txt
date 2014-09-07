
###################################################################################################
# NOTE:
# 	BASE_SOURCE_PATH is defined in ROOT\CMakeLists.txt
# 	PATH_TO_EXTERNAL is defined in ROOT\CMakeLists.txt
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

# Core.
#################################################
set( CORE_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/Macro.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/core/SystemDefinition.h )

set( SOURCE_FILES ${CORE_SRCS} )
source_group( "Core" FILES ${CORE_SRCS} )


# Memory.
#################################################
set( MEMORY_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/memory/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/memory/Pointer.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/memory/Pointer.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/memory/Scoped.h )

set( SOURCE_FILES ${SOURCE_FILES} ${MEMORY_SRCS} )
source_group( "Memory" FILES ${MEMORY_SRCS} )


# Messaging.
#################################################
set( MESSAGING_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/messaging/Server.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/messaging/Server.cpp )

set( SOURCE_FILES ${SOURCE_FILES} ${MESSAGING_SRCS} )
source_group( "Messaging" FILES ${MESSAGING_SRCS} )


# Thread.
#################################################
set( THREADING_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Condition.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Condition.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Includes.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Lock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Lock.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Mutex.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Mutex.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/SpinLock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/SpinLock.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Thread.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Thread.h  
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/ThreadDummy.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/ThreadDummy.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Utils.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Utils.h )

set( SOURCE_FILES ${SOURCE_FILES} ${THREADING_SRCS} )
source_group( "Threading" FILES ${THREADING_SRCS} )


# Version.
#################################################
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/version/Version.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/version/Version.h )
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/version/version.h )


# link source files for generation.
###################################################################################################
set_source_files_properties( ${SOURCE_FILES} PROPERTIES GENERATED true )


# Include directories.
###################################################################################################		
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../ )	


# Libraries.
###################################################################################################

# Windows 
#################################################
if( WIN32 )
	set( LIBS	
		 kernel32.lib )
endif( WIN32 )


# OSX 
#################################################
if( APPLE )		 
	link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

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














 
