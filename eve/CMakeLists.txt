
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
	 ${CMAKE_CURRENT_SOURCE_DIR}/memory/Pointer.h )

set( SOURCE_FILES ${SOURCE_FILES} ${MEMORY_SRCS} )
source_group( "Memory" FILES ${MEMORY_SRCS} )


# Thread.
#################################################
set( THREADING_SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Condition.cpp
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Condition.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Lock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Lock.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Mutex.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Mutex.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/SpinLock.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/SpinLock.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Thread.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/threading/Thread.h )

set( SOURCE_FILES ${SOURCE_FILES} ${THREADING_SRCS} )
source_group( "Threading" FILES ${THREADING_SRCS} )


# Entry point
#################################################
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )


# link source files for generation.
###################################################################################################
set_source_files_properties( ${SOURCE_FILES} PROPERTIES GENERATED true )


# Include directories.
###################################################################################################		
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )	


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
if( USING_WINDOWS_MSVC )
	# A custom target that is always built
	# add_custom_target( ${PRODUCT_PRODUCT_NAME}_version ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ftopia.rc )
	
	# Generate rc files
	configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/${PRODUCT_PRODUCT_NAME}.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc @ONLY )
	# Set properties to generated files
	set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc PROPERTIES GENERATED TRUE )	
	set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_PRODUCT_NAME}.rc )
endif()


# Create main executables.
###################################################################################################
set( exe_name "${PRODUCT_PRODUCT_NAME}_exe" )
if( WIN32 )
	add_executable( ${exe_name} WIN32 ${SOURCE_FILES} )
endif()

if( APPLE )
	# Info.plist content ----------
	set( MACOSX_BUNDLE TRUE )
	set( MACOSX_BUNDLE_INFO_STRING 			"${PRODUCT_PRODUCT_NAME}" )
	set( MACOSX_BUNDLE_ICON_FILE 			"${PRODUCT_ICON_INSTALL_NAME}.icns" )
	set( MACOSX_BUNDLE_GUI_IDENTIFIER 		"com.${PRODUCT_VENDOR_NAME}.${PRODUCT_PRODUCT_NAME}" )
	set( MACOSX_BUNDLE_BUNDLE_NAME 			"${PRODUCT_PRODUCT_NAME}" )
	set( MACOSX_BUNDLE_LONG_VERSION_STRING 	"${PRODUCT_VERSION}" )
	set( MACOSX_BUNDLE_SHORT_VERSION_STRING "${PRODUCT_VERSION_MAJOR}" )
	set( MACOSX_BUNDLE_BUNDLE_VERSION 		"${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}" )
	set( MACOSX_BUNDLE_COPYRIGHT 			"Copyright 2014 ${PRODUCT_VENDOR_NAME}. All rights reserved." )

	# RPATH ---------- do not force RPATH in OSX 10.8 and above ---- RC
	set( CMAKE_SKIP_BUILD_RPATH FALSE )
	set( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
	set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )
	set( CMAKE_INSTALL_RPATH "Contents/MacOSX" )
	set( INSTALL_NAME_DIR @rpath )

	# Icone ----------
	set( APP_ICNS_FILE "${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.icns" )
	set_source_files_properties( "${APP_ICNS_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	set( SOURCE_FILES ${SOURCE_FILES} ${APP_ICNS_FILE} )

	# CURL crt ----------
	set( CURL_CRT_FILE "${BASE_SOURCE_PATH}/asset/data/curl-ca-bundle.crt" )
	set_source_files_properties( "${CURL_CRT_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	set( SOURCE_FILES ${SOURCE_FILES} ${CURL_CRT_FILE} )

	# qt.conf file ----------
	set( QT_CONF_FILE "${BASE_SOURCE_PATH}/CPack/osx/qt.conf" )
	set_source_files_properties( "${QT_CONF_FILE}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
	set( SOURCE_FILES ${SOURCE_FILES} ${QT_CONF_FILE} )

	add_executable( ${exe_name} MACOSX_BUNDLE ${SOURCE_FILES} )
endif()

# Link packages to executable.
if( APPLE )
	# Set executable properties.
	set_target_properties( ${exe_name} PROPERTIES MACOSX_RPATH 0 )
	set_target_properties( ${exe_name} PROPERTIES SKIP_BUILD_RPATH 1 INSTALL_RPATH "@executable_path" )
	set_target_properties( ${exe_name} PROPERTIES LINK_FLAGS " -framework AppKit  -framework ApplicationServices -framework CoreFoundation -framework CoreServices -framework DiskArbitration -framework Security" )

	# Info.plist
	set( APP_ICNS "ftopia.icns" )
	configure_file( ${BASE_SOURCE_PATH}/CPack/osx/Info.plist.in ${PROJECT_BINARY_DIR}/Info.plist @ONLY )
	set_target_properties( ${exe_name} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist )
endif()	

set_target_properties( ${exe_name} PROPERTIES OUTPUT_NAME ${PRODUCT_PRODUCT_NAME} )

# Link executable to libraries.
target_link_libraries( ${exe_name} ${LIBS} )

# Executable install target
install( TARGETS ${exe_name} BUNDLE DESTINATION . COMPONENT ${PRODUCT_PRODUCT_NAME} 
							 RUNTIME DESTINATION . COMPONENT ${PRODUCT_PRODUCT_NAME} )

# Windows icon file.
if( WIN32 )
	configure_file( ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_ICON_INSTALL_NAME}.ico COPYONLY )	
	install( FILES  ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico DESTINATION . COMPONENT ${PRODUCT_PRODUCT_NAME} )
	
	if( OPTION_BUILD_TYPE_DEBUG )  
		install( FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${exe_name}.pdb DESTINATION . COMPONENT ${PRODUCT_PRODUCT_NAME} )
	endif() 
endif()















 
