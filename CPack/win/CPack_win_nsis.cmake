
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
# Windows-specific installation setup using NSIS
###################################################################################################

install( FILES "${PROJECT_BINARY_DIR}/Readme.txt" DESTINATION about COMPONENT ${PRODUCT_PRODUCT_NAME} )
install( FILES "${BASE_SOURCE_PATH}/License.txt" DESTINATION about COMPONENT ${PRODUCT_PRODUCT_NAME} )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )
set( CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF FORCE )


# Select NSIS as generator
#################################################
set( CPACK_GENERATOR NSIS )


# Set destination directory
#################################################
if( ${CMAKE_SIZEOF_VOID_P} EQUAL 8 )
	set( CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64" ) 
	set( CPACK_PACKAGE_FILE_NAME "${PRODUCT_PRODUCT_NAME}-x64-Windows" )
	set( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PRODUCT_PRODUCT_NAME}-x64-Windows" )
endif()

if( ${CMAKE_SIZEOF_VOID_P} EQUAL 4 )
	set( CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES") 
	set( CPACK_PACKAGE_FILE_NAME "${PRODUCT_PRODUCT_NAME}-x86-Windows")
	set( CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PRODUCT_PRODUCT_NAME}-x86-Windows")
endif()

set( CPACK_SET_DESTDIR "OFF" )


# Set product installer informations
#################################################

# NSIS not used yet, cause of a bug with suitable ZIP programme
# There is a bug in NSI that does not handle full unix paths properly. Make
# sure there is at least one set of four (4) backslashes.
set( CPACK_NSIS_PACKAGE_NAME "${PRODUCT_PRODUCT_NAME}" )
set( CPACK_NSIS_DISPLAY_NAME "${PRODUCT_PRODUCT_NAME}" )
set( CPACK_NSIS_BRANDINGTEXT_NAME "${PRODUCT_PRODUCT_NAME} installer" )

string( REPLACE "/" "\\\\\\\\" PRODUCT_WEBSITE ${PRODUCT_WEBSITE} )
set( CPACK_NSIS_HELP_LINK "${PRODUCT_WEBSITE}" )
set( CPACK_NSIS_URL_INFO_ABOUT "${PRODUCT_WEBSITE}" )
set( CPACK_NSIS_CONTACT "${PRODUCT_SUPPORT_EMAIL}" )

# The icon to start the application.
set( CPACK_NSIS_MUI_ICON "${BASE_SOURCE_PATH}\\\\CPack\\\\${PRODUCT_ICON_INSTALL_NAME}.ico" )
# The icon to uninstall the application.
set( CPACK_NSIS_MUI_UNIICON "${BASE_SOURCE_PATH}\\\\CPack\\\\${PRODUCT_ICON_UNINSTALL_NAME}.ico" )
# The icon that appears in top of the installer dialog.
set( CPACK_PACKAGE_ICON "${BASE_SOURCE_PATH}\\\\CPack\\\\${PRODUCT_ICON_INSTALL_NAME}.ico" )
# The icon for the application in the Add/Remove programs section.
set( CPACK_NSIS_INSTALLED_ICON_NAME "${PRODUCT_ICON_INSTALL_NAME}.ico" )

# # Recommended size: 164x314 pixels
# set( CPACK_NSIS_BRANDINGIMAGE_WELCOME "${BASE_SOURCE_PATH}\\\\asset\\\\welcome.bmp" )
# # Recommended size: 150x57 pixels
# set( CPACK_NSIS_BRANDINGIMAGE_HEADER "${BASE_SOURCE_PATH}\\\\asset\\\\licence.bmp" )

set( CPACK_NSIS_MODIFY_PATH OFF )
set( CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON )

# set( CPACK_NSIS_COMPRESSOR "/SOLID zlib" )
set( CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_NSIS_INSTALL_ROOT}/${PRODUCT_PRODUCT_NAME}/${PRODUCT_PRODUCT_NAME}.exe" )


# Additional icons and short-cuts
###################################################################################################
SET(ICONPATH "$INSTDIR/${PRODUCT_ICON_INSTALL_NAME}.ico")
STRING(REPLACE "/" "\\\\" ICONPATH ${ICONPATH})


# Create the desktop link
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "CreateShortCut			\\\\
	'\$DESKTOP\\\\${PRODUCT_PRODUCT_NAME}.lnk'									\\\\
	'\$INSTDIR\\\\${PRODUCT_PRODUCT_NAME}.exe'									\\\\
	''														\\\\
	'${ICONPATH}'"
	)	
# Destroy the desktop link	
SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS " Delete '$DESKTOP\\\\${PRODUCT_PRODUCT_NAME}.lnk' " 
)


# Create Start Menu	exe
SET(CPACK_NSIS_CREATE_ICONS
	"CreateShortCut											\\\\
	 '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PRODUCT_PRODUCT_NAME}.lnk'			\\\\
	 '\$INSTDIR\\\\${PRODUCT_PRODUCT_NAME}.exe'									\\\\
	 ''														\\\\
	 '${ICONPATH}'"
)
# Destroy Start Menu exe
SET(CPACK_NSIS_DELETE_ICONS "
	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP 
	Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\${PRODUCT_PRODUCT_NAME}.lnk\\\" 
	")


# Call CPack installer generation
###################################################################################################
# set( CPACK_MODULE_PATH ${BASE_SOURCE_PATH}/CPack/win )
include( CPack )













