
###################################################################################################
# CPack installer 
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
include( ${BASE_SOURCE_PATH}/PRODUCT_INFO.cmake )


# CPACK RULES
###################################################################################################

configure_file( ${BASE_SOURCE_PATH}/License.txt ${PROJECT_BINARY_DIR}/CPack.GenericLicense.txt @ONLY )
configure_file( ${BASE_SOURCE_PATH}/Readme.txt ${PROJECT_BINARY_DIR}/Readme.txt @ONLY )

set( CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION . )

if( OPTION_BUILD_TYPE_DEBUG )
	set( CMAKE_INSTALL_DEBUG_LIBRARIES TRUE )
endif( OPTION_BUILD_TYPE_DEBUG )


include( InstallRequiredSystemLibraries )
set( CPACK_SET_DESTDIR "ON" )
set( CPACK_PACKAGE_RELOCATABLE "FALSE" )
set( CPACK_CMAKE_GENERATOR ${CMAKE_GENERATOR} )

set( CPACK_PACKAGE_NAME ${PRODUCT_PRODUCT_NAME} )
set( CPACK_PACKAGE_VENDOR ${PRODUCT_VENDOR_NAME} )

set( CPACK_PACKAGE_VERSION ${PRODUCT_VERSION} )
set( CPACK_PACKAGE_VERSION_MAJOR ${BUILDVERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR ${BUILDVERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH ${BUILDVERSION_PATCH} )

set( CPACK_PACKAGE_INSTALL_DIRECTORY ${PRODUCT_PRODUCT_NAME} )
set( CPACK_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackConfig.cmake" )
set( CPACK_PACKAGE_DESCRIPTION_FILE "${BASE_SOURCE_PATH}/Readme.txt" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PRODUCT_PRODUCT_NAME} )
set( CPACK_RESOURCE_FILE_WELCOME "${BASE_SOURCE_PATH}/Readme.txt" )


# Binary distribution
###################################################################################################
set( CPACK_PACKAGE_CONTACT ${PRODUCT_SUPPORT_EMAIL} )
set( CPACK_INSTALL_CMAKE_PROJECTS "${PROJECT_BINARY_DIR};FTOPIA_CLIENT;ALL;/" )
set( CPACK_SOURCE_PACKAGE_FILE_NAME "${FTOPIA_CLIENT-CPACK_PACKAGE_VERSION}")
set( CPACK_IGNORE_FILES "/CMake/;/CMakeFiles/;/_CPack_Packages/;/src/;/install_manifest_/;.*~;/www/;/CVS//;/.svn/;.cdtprojects;.project;/.settings/" )
set( CPACK_STRIP_FILES "" )
set( CPACK_RESOURCE_FILE_LICENSE "${PROJECT_BINARY_DIR}/CPack.GenericLicense.txt" )
set( CPACK_RESOURCE_FILE_README "${PROJECT_BINARY_DIR}/Readme.txt" )


# # Disable source generator enabled by default -> kept for future use
# ###################################################################################################
# set( CPACK_SOURCE_TBZ2 OFF CACHE BOOL "Enable to build TBZ2 source packages" FORCE )
# set( CPACK_SOURCE_TGZ OFF CACHE BOOL "Enable to build TGZ source packages" FORCE )
# set( CPACK_SOURCE_TZ OFF CACHE BOOL "Enable to build TZ source packages" FORCE )



# OS dedicated installer
###################################################################################################
if( WIN32 )
	include( ${BASE_SOURCE_PATH}/CPack/win/CPack_win_nsis.cmake )
endif()

if( APPLE )
	include( ${BASE_SOURCE_PATH}/CPack/osx/CPack_osx.cmake )
endif()





