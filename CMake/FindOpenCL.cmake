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




IF (WIN32)
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

     FIND_PATH(	AMD_OPENCL_BASEDIR
                "include/CL/cl.h"
                PATH $ENV{AMDAPPSDKROOT} )

     FIND_PATH( NVIDIA_OPENCL_BASEDIR
				"include/CL/cl.h"
				PATH $ENV{CUDA_PATH} 
				$ENV{CUDA_HOME} )
				
	FIND_PATH( INTEL_OPENCL_BASEDIR
				"include/CL/cl.h"
				PATH $ENV{INTELOCLSDKROOT} )
				
				
	# Setup for INTEL SDK
	IF( INTEL_OPENCL_BASEDIR )
		FIND_PATH( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
                    PATHS $ENV{INTELOCLSDKROOT}include )
		 MESSAGE( STATUS "INTEL-OpenCL-Include path : " ${OPENCL_INCLUDE_DIR} )
		 
		 IF( CMAKE_CL_64 )
             FIND_LIBRARY( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{INTELOCLSDKROOT}lib/x64 )
         ELSE()
             FIND_LIBRARY( OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{INTELOCLSDKROOT}lib/x86 )
         ENDIF()
    ELSE()
        MESSAGE( "INTEL-OpenCL-Implementation: NOT_FOUND" )
    ENDIF()
			
     # Setup for AMD/ATI Stream-SDK
     IF( AMD_OPENCL_BASEDIR )
         FIND_PATH( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
                    PATHS $ENV{AMDAPPSDKROOT}include )
         
		 MESSAGE( STATUS "AMD-OpenCL-Include path : " ${OPENCL_INCLUDE_DIR} )
         
		 IF( CMAKE_CL_64 )
             FIND_LIBRARY( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{AMDAPPSDKROOT}lib/x86_64 )
         ELSE()
             FIND_LIBRARY( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS $ENV{AMDAPPSDKROOT}lib/x86 )
         ENDIF()
		 
		 IF( OPENCL_LIBRARY )
			MESSAGE( STATUS "AMD-OpenCL-Library path : " ${OPENCL_LIBRARY} )
		 ENDIF()
		 
     ELSE()
         MESSAGE( "AMD/ATI-Stream-OpenCL-Implementation: NOT_FOUND" )
     ENDIF()
	 
	 
	 # Setup for NVIDIA SDK
     IF( NVIDIA_OPENCL_BASEDIR )
         FIND_PATH( OPENCL_INCLUDE_DIR
                    NAMES CL/cl.hpp OpenCL/cl.hpp CL/cl.h OpenCL/cl.h
					PATHS ${NVIDIA_OPENCL_BASEDIR}/include )
					
         MESSAGE( STATUS "NVidia-CUDA-OpenCL-Includepath : " ${OPENCL_INCLUDE_DIR})

         IF( CMAKE_CL_64 )
             FIND_LIBRARY( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS ${NVIDIA_OPENCL_BASEDIR}/lib/x64 )
         ELSE()
             FIND_LIBRARY( 	OPENCL_LIBRARY
							NAMES OpenCL
							PATHS ${NVIDIA_OPENCL_BASEDIR}/lib/Win32 )
         ENDIF()
		 
		 IF( OPENCL_LIBRARY )
			MESSAGE( STATUS "NVidia-CUDA-OpenCL-Library path : " ${OPENCL_LIBRARY} )
		 ENDIF()
		 
     ELSE()
         MESSAGE( "NVIDIA-Cuda-OpenCL-Implementation: NOT_FOUND" )
     ENDIF()

ENDIF()	# --------- WIN32




IF( LINUX )
     FIND_PATH(	OPENCL_INCLUDE_DIR
                NAMES CL/cl.h OpenCL/cl.h
                HINTS ENV OPENCL_DIR

                 PATHS     /include

                         /usr/include

                         /usr/local/include

                         ~/include )

     message( STATUS

              "Found OpenCL-include-path is :" ${OPENCL_INCLUDE_DIR} )

     FIND_LIBRARY(    OPENCL_LIBRARY

                     NAMES OpenCL

                     HINTS ENV OPENCL_DIR

                     PATHS   /lib

                             /usr/lib

                             /usr/local/lib

                             ~/lib )

     message( STATUS "Found OpenCL-library-path is :" ${OPENCL_LIBRARY} )
ENDIF()


IF( APPLE )
  FIND_LIBRARY(OPENCL_LIBRARY OpenCL DOC "OpenCL lib for OSX")
  FIND_PATH(OPENCL_INCLUDE_DIR OpenCL/cl.h DOC "Include for OpenCL on OSX")
  FIND_PATH(_OPENCL_CPP_INCLUDE_DIRS OpenCL/cl.hpp DOC "Include for OpenCL CPP bindings on OSX")
ENDIF(APPLE)


SET( OPENCL_FOUND "NO" )
IF(OPENCL_LIBRARY )
	SET( OPENCL_FOUND "YES" )
ENDIF(OPENCL_LIBRARY)

MARK_AS_ADVANCED(
  OPENCL_INCLUDE_DIR
  OPENCL_LIBRARY
)

