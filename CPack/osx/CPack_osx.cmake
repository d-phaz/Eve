
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

###################################################################################################
# Mac OSX-specific installation setup.
###################################################################################################

install( FILES "${BASE_SOURCE_PATH}/Readme.txt" DESTINATION ${PRODUCT_PRODUCT_NAME}.app/Contents/Resources/about COMPONENT ${PRODUCT_PRODUCT_NAME} )
install( FILES "${BASE_SOURCE_PATH}/License.txt" DESTINATION ${PRODUCT_PRODUCT_NAME}.app/Contents/Resources/about COMPONENT ${PRODUCT_PRODUCT_NAME} )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )


# Package configuration
#################################################
set( CPACK_MONOLITHIC_INSTALL ON )

if( CMAKE_SIZEOF_VOID_P MATCHES 8 )
  	set( CPACK_PACKAGE_FILE_NAME "${PRODUCT_PRODUCT_NAME}-${CPACK_PACKAGE_VERSION}-x64-Mac" )
  	set( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PRODUCT_PRODUCT_NAME}-${CPACK_PACKAGE_VERSION}-x64-Mac" )
else()
	set( CPACK_PACKAGE_FILE_NAME "${PRODUCT_PRODUCT_NAME}-${CPACK_PACKAGE_VERSION}-x86-Mac" )
	set( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PRODUCT_PRODUCT_NAME}-${CPACK_PACKAGE_VERSION}-x86-Mac" )
endif()

set( CPACK_PACKAGE_ICON "${BASE_SOURCE_PATH}/CPack/${PRODUCT_ICON_INSTALL_NAME}.icns" )


# Install 
#################################################
set( CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} )


# Bundle Fixup 
#################################################
if( OPTION_BUILD_TYPE_DEBUG )
	set( CONF_NAME "Debug" )
else()
	set( CONF_NAME "Release" )
endif()

# App
set( APPS "${CMAKE_INSTALL_PREFIX}/bin/${CONF_NAME}/${PRODUCT_PRODUCT_NAME}.app")

# Libs
set( LIBS "" ) 

# Dir
set( DIRS "" )

# Fixup
install( CODE "
		include(BundleUtilities)
		fixup_bundle( \"${APPS}\" \"${LIBS}\" \"${DIRS}\" )
    	" COMPONENT ${PRODUCT_PRODUCT_NAME} ) 

