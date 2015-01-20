
###################################################################################################
# NOTE:
# 	SOURCE_FILES is defined in ROOT/eve/CMakeLists.txt
###################################################################################################

# Files listing.
#################################################
set( SRCS
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/CommandQueue.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/CommandQueue.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Context.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Context.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Debug.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Debug.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/External.h
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Engine.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Engine.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Kernel.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Kernel.h 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Program.cpp 
	 ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Program.h )

# Generate Configuration.h
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Configuration.h.in ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Configuration.h @ONLY )
set_source_files_properties( ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Configuration.h PROPERTIES GENERATED TRUE )	
set( SRCS ${SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/ocl/core/Configuration.h )

set( SOURCE_FILES ${SOURCE_FILES} ${SRCS} )
source_group( "OpenCL\\core" FILES ${SRCS} )
