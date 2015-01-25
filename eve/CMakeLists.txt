
###################################################################################################
# NOTE:
# 	BASE_SOURCE_PATH is defined in ROOT\CMakeLists.txt
#	OPTION_BUILD_USE_VLD is defined in ROOT\CMakeLists.txt
###################################################################################################


###################################################################################################
# NOTE:
#	These are set in root/ProductInfo.cmake
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
set(CMAKE_MODULE_PATH_OLD "${CMAKE_MODULE_PATH}" )
set(CMAKE_MODULE_PATH "${BASE_SOURCE_PATH}/CMake")


# Parse files in project.
###################################################################################################
set( SOURCE_FILES )
set( LIBS )

# Include directories.
###################################################################################################	
SET(${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES  
${BASE_SOURCE_PATH}
${CMAKE_INCLUDE_OUTPUT_DIRECTORY}
${BASE_SOURCE_PATH}/external/include)

	
# OpenCL.
###################################################################################################
if(OPTION_BUILD_ENABLE_OPENCL)
	find_package( OpenCL REQUIRED )
	if(${OPENCL_FOUND})
		LIST(APPEND ${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES ${OPENCL_INCLUDE_DIR})
		set( LIBS ${LIBS} ${OPENCL_LIBRARY})
	else()
		message(FATAL_ERROR "OpenCL not found on this platform.")
	endif()
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH_OLD}")
endif()


# Files listing and folder creation.
#################################################
include( ${CMAKE_CURRENT_SOURCE_DIR}/app/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/core/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/dx11/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/evt/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/files/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/geom/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/io/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/math/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/mem/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/mess/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/ocl/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/ogl/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/scene/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/str/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/sys/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/thr/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/time/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/ui/CMakeLists.txt )
include( ${CMAKE_CURRENT_SOURCE_DIR}/xml/CMakeLists.txt )

	
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
				${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/Version.h )
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/Version.h )
set_source_files_properties( ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/Version.h PROPERTIES GENERATED true )
			
# External.h
#################################################
set( RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../resources" )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/generated/External.h.in
				${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/External.h )
set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/External.h )
set_source_files_properties( ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/eve/generated/External.h PROPERTIES GENERATED true )


# Include directories.
###################################################################################################	
include_directories( ${${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES} )

# Libraries.
###################################################################################################	 
link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

# Windows 
#################################################
if( WIN32 )
	set( LIBS
		 ${LIBS}
		 kernel32.lib
		 OpenGL32.lib 
		 glu32.lib 
		 User32.lib 
		 Winmm.lib ) 	 

	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR} )
	elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
		link_directories( ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR} )
	endif()
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

	
# Assimp.
#################################################
if( WIN32 )
	if( OPTION_BUILD_TYPE_DEBUG )
		set( LIBS ${LIBS} assimpd.lib)
	elseif( OPTION_BUILD_TYPE_RELEASE ) 
		set( LIBS ${LIBS} assimp.lib)	
	endif()
endif()
add_definitions( -DASSIMP_BUILD_BOOST_WORKAROUND )

	
# FreeImage.
#################################################
if( WIN32 )
	if( OPTION_BUILD_TYPE_DEBUG )
		set( FREEIMAGE_LIBS  FreeImaged.lib )
	elseif( OPTION_BUILD_TYPE_RELEASE ) 
		set( FREEIMAGE_LIBS  FreeImage.lib )		
	endif()
	set( LIBS ${LIBS} ${FREEIMAGE_LIBS})
endif()
add_definitions( -DFREEIMAGE_LIB )

	
# GLEW.
#################################################
if( WIN32 )
	if( OPTION_BUILD_TYPE_DEBUG )
		set( GLEW_LIBS  glewd.lib  glewmxsd.lib )
	elseif( OPTION_BUILD_TYPE_RELEASE ) 
		set( GLEW_LIBS  glew.lib  glewmxs.lib )		
	endif()
	add_definitions( -DGLEW_STATIC=1 )
	set( LIBS ${LIBS} ${GLEW_LIBS})
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














 
