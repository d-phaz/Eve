
# Find Qt modules.
###################################################################################################	
set( CMAKE_PREFIX_PATH 
	 ${CMAKE_PREFIX_PATH}
	 ${PATH_TO_QT} )
	 
if( USING_WINDOWS_MSVC )	
	include( ${BASE_SOURCE_PATH}/CMake/modules/FindWindowsSDK.cmake )

	set( WINSDK_LIB_PATH )
	if( "${WINDOWSSDK_LATEST_NAME}" STREQUAL "Windows SDK v8.0" )
		if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			set( WINSDK_LIB_PATH "${WINDOWSSDK_LATEST_DIR}/Lib/win8/um/x64" )
		else()
			set( WINSDK_LIB_PATH "${WINDOWSSDK_LATEST_DIR}/Lib/win8/um/x86" )
		endif()
	endif()
	
	if( "${WINDOWSSDK_LATEST_NAME}" STREQUAL "Windows SDK v8.1" )
		if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			set( WINSDK_LIB_PATH "${WINDOWSSDK_LATEST_DIR}/Lib/winv6.3/um/x64" )
		else()
			set( WINSDK_LIB_PATH "${WINDOWSSDK_LATEST_DIR}/Lib/winv6.3/um/x86" )
		endif()
	endif()
	
	if( NOT "${WINSDK_LIB_PATH}" STREQUAL "" )
		message( "using ${WINDOWSSDK_LATEST_NAME}" )
		set( CMAKE_LIBRARY_PATH 
			 ${CMAKE_LIBRARY_PATH} 
			 "${WINSDK_LIB_PATH}" )
	else()	
		message( FATAL_ERROR "Windows SDK library folder not found, please install SDK v8.0 or v8.1 or update file FindWindowsSDK.cmake." )
	endif()	 
endif( USING_WINDOWS_MSVC )

# Find packages
if( WIN32 )
	find_package( Qt5Core 	 REQUIRED )
	find_package( Qt5Gui 	 REQUIRED )
	find_package( Qt5Network REQUIRED )
	find_package( Qt5Widgets REQUIRED )
endif()

if( APPLE )
	find_package( Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED )
	# include_directories( ${QT_INCLUDE_DIR} )
	include( ${QT_USE_FILE} )
	add_definitions( ${QT_DEFINITIONS} )
endif()

# if( APPLE )
# 	find_package( Qt5PrintSupport REQUIRED )
# endif()



macro( add_qt_libs LIBS )
	# set( LIBS ${LIBS} ${Qt5Core_LIBRARIES} )
	# set( LIBS ${LIBS} ${Qt5Gui_LIBRARIES} )
	# set( LIBS ${LIBS} ${Qt5Network_LIBRARIES} )
	# set( LIBS ${LIBS} ${Qt5Widgets_LIBRARIES} )

	# set( LIBS ${LIBS} ${Qt5PrintSupport_LIBRARIES} )
	# set( LIBS ${LIBS} libqcocoa.dylib )
	set( LIBS ${LIBS} ${QT_LIBRARIES} )

	# install( TARGETS "${PATH_TO_QT}/lib/QtCore.framework" BUNDLE DESTINATION . COMPONENT ${PRODUCT_NAME} 
	# 						 	 		  				  RUNTIME DESTINATION . COMPONENT ${PRODUCT_NAME} )
	# SET_SOURCE_FILES_PROPERTIES(  ${Qt5Core_LIBRARIES} 
	# 							  ${Qt5Gui_LIBRARIES} 
	# 							  ${Qt5Network_LIBRARIES} 
	# 							  ${Qt5Widgets_LIBRARIES}
	# 							  PROPERTIES
	# 							  MACOSX_PACKAGE_LOCATION MacOSX )

endmacro()












