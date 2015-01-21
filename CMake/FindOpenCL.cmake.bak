# ===========================================================================
#  
# FindOpenCL.cmake
#
# Tries to find a valid installed OpenCL-Library (AMD, INTEL, NVIDIA). 
# Sets the following variables:
#
# OPENCL_FOUND
# OPENCL_INCLUDE_DIR
# OPENCL_LIBRARY
#
# ===========================================================================




if(WIN32)
     # =======================================================================
	 #
     # First try to find something for a windows-environment. This is the most
	 #
     # tricky part. ATI defines AMDAPPSDKROOT, on NVIDIA cards I created an environment variable 
	 #
	 # named "CUDA_PATH" that points to the CUDA SDK install dir, in my case "C:\CUDA".	
	 #
	 # So, at first, we test for these two environment-variable cases.
	 #
     # =======================================================================

     find_path(	AMD_OPENCL_BASEDIR
                "include/CL/cl.h"
                PATH $ENV{AMDAPPSDKROOT} )

     find_path( NVIDIA_OPENCL_BASEDIR
				"include/CL/cl.h"
				PATH $ENV{CUDA_PATH} 
				$ENV{CUDA_HOME} )
				
	 find_path( INTEL_OPENCL_BASEDIR
				"include/CL/cl.h"
				PATH $ENV{INTELOCLSDKROOT} )
				
				
	# Setup for INTEL SDK
	if( INTEL_OPENCL_BASEDIR )
		find_path( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
                    PATHS $ENV{INTELOCLSDKROOT}include )
		 message( STATUS "INTEL-OpenCL-Include path : " ${OPENCL_INCLUDE_DIR} )
		 
		 if( CMAKE_CL_64 )
             find_library( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{INTELOCLSDKROOT}lib/x64 )
         else()
             find_library( OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{INTELOCLSDKROOT}lib/x86 )
         endif()
    else()
        message( "INTEL-OpenCL-Implementation: NOT_FOUND" )
    endif()
			
     # Setup for AMD/ATI Stream-SDK
     if( AMD_OPENCL_BASEDIR )
         find_path( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
                    PATHS $ENV{AMDAPPSDKROOT}include )
         
		 message( STATUS "AMD-OpenCL-Include path : " ${OPENCL_INCLUDE_DIR} )
         
		 if( CMAKE_CL_64 )
             find_library( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{AMDAPPSDKROOT}lib/x86_64 )
         else()
             find_library( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{AMDAPPSDKROOT}lib/x86 )
         endif()
		 
		 if( OPENCL_LIBRARY )
			message( STATUS "AMD-OpenCL-Library path : " ${OPENCL_LIBRARY} )
		 endif()
		 
     else()
         message( "AMD/ATI-Stream-OpenCL-Implementation: NOT_FOUND" )
     endif()
	 
	 
	 # Setup for NVIDIA SDK
     if( NVIDIA_OPENCL_BASEDIR )
         find_path( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
					PATHS ${NVIDIA_OPENCL_BASEDIR}/include )
					
         message( STATUS "NVidia-CUDA-OpenCL-Includepath : " ${OPENCL_INCLUDE_DIR})

         if( CMAKE_CL_64 )
             find_library( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS ${NVIDIA_OPENCL_BASEDIR}/lib/x64 )
         else()
             find_library( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS ${NVIDIA_OPENCL_BASEDIR}/lib/Win32 )
         endif()
		 
		 if( OPENCL_LIBRARY )
			message( STATUS "NVidia-CUDA-OpenCL-Library path : " ${OPENCL_LIBRARY} )
		 endif()
		 
     else()
         message( "NVIDIA-Cuda-OpenCL-Implementation: NOT_FOUND" )
     endif()

endif()	# --------- WIN32




if( LINUX )
     find_path(	OPENCL_INCLUDE_DIR
                NAMES CL/cl.h OpenCL/cl.h
                HINTS ENV OPENCL_DIR

                 PATHS   /include

                         /usr/include

                         /usr/local/include

                         ~/include )

     message( STATUS "Found OpenCL-include-path is :" ${OPENCL_INCLUDE_DIR} )

     find_library(   OPENCL_LIBRARY

                     NAMES OpenCL

                     HINTS ENV OPENCL_DIR

                     PATHS   /lib

                             /usr/lib

                             /usr/local/lib

                             ~/lib )

     message( STATUS "Found OpenCL-library-path is :" ${OPENCL_LIBRARY} )
endif()


if( APPLE )
  find_library(OPENCL_LIBRARY OpenCL DOC "OpenCL lib for OSX")
  find_path(OPENCL_INCLUDE_DIR OpenCL/cl.h DOC "Include for OpenCL on OSX")
  find_path(_OPENCL_CPP_INCLUDE_DIRS OpenCL/cl.hpp DOC "Include for OpenCL CPP bindings on OSX")
endif(APPLE)


SET( OPENCL_FOUND "NO" )
if(OPENCL_LIBRARY )
	SET( OPENCL_FOUND "YES" )
endif(OPENCL_LIBRARY)

mark_as_advanced(
  OPENCL_INCLUDE_DIR
  OPENCL_LIBRARY
)

