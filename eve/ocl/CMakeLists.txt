
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
#	OPENCL_FOUND is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
if(${OPENCL_FOUND})
	include( ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/CMakeLists.txt )
endif()
