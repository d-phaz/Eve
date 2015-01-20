
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/xml/rapidxml.hpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/xml/rapidxml_iterators.hpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/xml/rapidxml_print.hpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/xml/rapidxml_utils.hpp )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "XML" FILES ${SRCS} )
