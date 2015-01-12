
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
#  		PROJECT_NAME
#		PRODUCT_ICON_INSTALL_NAME
#		PRODUCT_ICON_UNINSTALL_NAME
#  		PRODUCT_VERSION_MAJOR
#  		PRODUCT_VERSION_MINOR
#  		PRODUCT_VERSION_PATCH
#  		PRODUCT_VERSION
#		PRODUCT_WEBSITE
#  		PRODUCT_SUPPORT_EMAIL
###################################################################################################

macro( add_project PROJECT_NAME_IN )
		
	# CMake Configuration.
	###################################################################################################
	# Find includes in corresponding build directories
	set( CMAKE_INCLUDE_CURRENT_DIR ON )
	# Instruct CMake to run moc automatically when needed.
	set( CMAKE_AUTOMOC TRUE )
	set( CMAKE_AUTOMOC_RELAXED_MODE TRUE )


	# Project.
	###################################################################################################

	# Project name.
	set( PROJECT_NAME ${PRODUCT_PRODUCT_NAME}_${PROJECT_NAME_IN} )
	project( ${PROJECT_NAME} )

	# Source files.
	set( SOURCE_FILES 
		 ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_IN}/main.cpp )
		 
	set_source_files_properties( ${SOURCE_FILES} PROPERTIES GENERATED true )

	# Include directories
	###################################################################################################	
	SET(${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES  
	${BASE_SOURCE_PATH}
	${CMAKE_INCLUDE_OUTPUT_DIRECTORY}
	${BASE_SOURCE_PATH}/external/include
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_IN}
	)

	# Create executable
	set( exe_name "${PROJECT_NAME}_exe" )
	
	if( WIN32 )
		if( OPTION_BUILD_SECURE_SCL )
			add_definitions( -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0 )
		endif()
	
		# Generate rc files
		configure_file( ${BASE_SOURCE_PATH}/${PRODUCT_PRODUCT_NAME}/${PRODUCT_PRODUCT_NAME}.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc @ONLY )
		# Set properties to generated files
		set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc PROPERTIES GENERATED TRUE )	
		set( SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc )
		
		add_executable( ${exe_name} WIN32 ${SOURCE_FILES} )
	endif()

	if( APPLE )
		# Info.plist content ----------
		set( MACOSX_BUNDLE TRUE )
		set( MACOSX_BUNDLE_INFO_STRING 			"${PROJECT_NAME}" )
		set( MACOSX_BUNDLE_ICON_FILE 			"${PRODUCT_ICON_INSTALL_NAME}.icns" )
		set( MACOSX_BUNDLE_GUI_IDENTIFIER 		"com.${PRODUCT_VENDOR_NAME}.${PROJECT_NAME}" )
		set( MACOSX_BUNDLE_BUNDLE_NAME 			"${PROJECT_NAME}" )
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
		set( APP_ICNS "${PRODUCT_PRODUCT_NAME}.icns" )
		configure_file( ${BASE_SOURCE_PATH}/CPack/osx/Info.plist.in ${PROJECT_BINARY_DIR}/Info.plist @ONLY )
		set_target_properties( ${exe_name} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist )
	endif()	

	# Libraries.
	###################################################################################################	 
	link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
	set( LIBS )

	# Windows 
	#################################################
	if( WIN32 )
		set( LIBS
			 ${LIBS}
			 kernel32.lib
			 OpenGL32.lib 
			 glu32.lib 
			 User32.lib 
			 Winmm.lib 
			 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${PRODUCT_PRODUCT_NAME}.lib ) 
			 
		if( OPTION_BUILD_ENABLE_DX11 )
			set( LIBS
				 ${LIBS}
				 dxgi.lib
				 d3dcompiler.lib
				 d3d11.lib )
		endif()

		if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			link_directories( ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR} )
		elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
			link_directories( ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR} )
		endif()
	endif( WIN32 )
	
	# OSX 
	#################################################
	if( APPLE )	
		set( LIBS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${PRODUCT_PRODUCT_NAME}.a )
		
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
			if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
				set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/assimpd.lib )
			elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
				set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/assimpd.lib )
			endif()
		elseif( OPTION_BUILD_TYPE_RELEASE ) 
			if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
				set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/assimp.lib )
			elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
				set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/assimp.lib )
			endif()
		endif()
	endif()
	add_definitions( -DASSIMP_BUILD_BOOST_WORKAROUND )
	
	# GLEW.
	#################################################
	if( WIN32 )
		if( OPTION_BUILD_TYPE_DEBUG )
			if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
				set( GLEW_LIBS 
					 ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/glewd.lib
					 ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/glewmxsd.lib )
			elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
				set( GLEW_LIBS 
					 ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/glewd.lib
					 ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/glewmxsd.lib )
			endif()			
		elseif( OPTION_BUILD_TYPE_RELEASE ) 
			if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
				set( GLEW_LIBS 
					 ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/glew.lib
					 ${BASE_SOURCE_PATH}/external/lib_x64/${CMAKE_CFG_INTDIR}/glewmxs.lib )
			elseif( CMAKE_SIZEOF_VOID_P EQUAL 4 )
				set( GLEW_LIBS 
					 ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/glew.lib
					 ${BASE_SOURCE_PATH}/external/lib_x86/${CMAKE_CFG_INTDIR}/glewmxs.lib )
			endif()	
		endif()
		add_definitions( -DGLEW_STATIC=1 )
		set( LIBS ${LIBS} ${GLEW_LIBS})
	endif()

	
	# OpenCL.
	#################################################
	if(OPTION_BUILD_ENABLE_OPENCL)
		set(CMAKE_MODULE_PATH_OLD "${CMAKE_MODULE_PATH}" )
		set(CMAKE_MODULE_PATH "${BASE_SOURCE_PATH}/CMake")
		find_package( OpenCL REQUIRED )
		if(${OPENCL_FOUND})
			LIST(APPEND ${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES ${OPENCL_INCLUDE_DIR})
			set( LIBS ${LIBS} ${OPENCL_LIBRARY})
		else()
			message(FATAL_ERROR "OpenCL not found on this platform.")
		endif()
		set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH_OLD}")
	endif()

	# # POCO
	# #################################################
	# add_definitions( -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS )
	# if( WIN32 )
		# if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			# if( OPTION_BUILD_TYPE_DEBUG )
				# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x64/Debug/PocoFoundationmdd.lib )
			# else()
				# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x64/Debug/PocoFoundationmd.lib )
			# endif()
		# endif()
		
		# if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
			# if( OPTION_BUILD_TYPE_DEBUG )
				# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x86/Release/PocoFoundationmdd.lib )
			# else()
				# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_x86/Release/PocoFoundationmd.lib )
			# endif()
		# endif()
	# endif()

	# if( APPLE )
		# if( OPTION_BUILD_TYPE_DEBUG )
			# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_osx/Debug/libPocoFoundationmdd.a ) 
		# else()
			# set( LIBS ${LIBS} ${BASE_SOURCE_PATH}/external/lib_osx/Release/libPocoFoundationmd.a )
		# endif()
	# endif()
	
	include_directories( ${${PRODUCT_PRODUCT_NAME}_INCLUDE_DIRECTORIES} )
	
	target_link_libraries( ${exe_name} ${LIBS} )

	# Executable properties
	add_dependencies( ${exe_name} ${PRODUCT_PRODUCT_NAME} )
	set_target_properties( ${exe_name} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )

	# Executable install target
	install( TARGETS ${exe_name} BUNDLE DESTINATION . COMPONENT ${PROJECT_NAME} 
								 RUNTIME DESTINATION . COMPONENT ${PROJECT_NAME} )

	# Windows icon file.
	if( WIN32 )
		configure_file( ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico ${CMAKE_CURRENT_BINARY_DIR}/${PRODUCT_ICON_INSTALL_NAME}.ico COPYONLY )	
		install( FILES  ${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.ico DESTINATION . COMPONENT ${PROJECT_NAME} )
		
		if( OPTION_BUILD_TYPE_DEBUG )  
			install( FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${exe_name}.pdb DESTINATION . COMPONENT ${PROJECT_NAME} )
		endif() 
	endif()

endmacro()













 
