# Nothing here yet
#include
INCLUDE (CheckIncludeFile)
INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists)
INCLUDE (CheckFunctionExists)
INCLUDE (CheckCSourceCompiles)
INCLUDE (CheckSymbolExists)
INCLUDE (CheckTypeSize)

INCLUDE (${BASE_SOURCE_PATH}/CMake/CheckPrototypeExists.cmake)

# Check if C type exists
# Defines HAVE_${TYPE} variable
macro(__CHECK_TYPE TYPE VARIABLE) # [HEADER]
    set(HEADERS stdint.h inttypes.h sys/inttypes.h sys/types.h stddef.h)
    if (${ARGC} GREATER 2)
        set(HEADERS ${ARGV2})
    endif()
    foreach(HEADER ${HEADERS})
        set(CMAKE_EXTRA_INCLUDE_FILES ${HEADER})
        check_type_size(${TYPE} ${VARIABLE} TRUE)
        unset(CMAKE_EXTRA_INCLUDE_FILES)
        if (${VARIABLE})
            set(${VARIABLE}_HEADER ${HEADER})
            message(STATUS "${TYPE} was found in ${HEADER}")
            break()
        endif()
    endforeach()
endmacro()

# Check the char_data_model (CDM) and long_data_model (LDM) and store the data model name in data_model (DM)
macro(M__GET_DATA_MODEL DM CDM LDM)
    if(${CDM} EQUAL 122)
        if(${LDM} EQUAL 242)
            set(${DM} "IP16")
            message(STATUS "Data model: standard 16bit machine")
        elseif(${LDM} EQUAL 244)
            set(${DM} "LP32")
            message(STATUS "Data model: standard 32bit machine")
        else()
            set(${DM} "i16")
            message(STATUS "Data model: unusual int16 model")
        endif()
    elseif(${CDM} EQUAL 124)
        if (${LDM} EQUAL 444)
            set(${DM} "ILP32")
            message(STATUS "Data model: standard 32bit unixish")
        elseif(${LDM} EQUAL 488)
            set(${DM} "LP64")
            message(STATUS "Data model: standard 64bit unixish")
        elseif(${LDM} EQUAL 448)
            set(${DM} "LLP64")
            message(STATUS "Data model: unusual 64bit unixish")
        else()
            set(${DM} "i32")
            message(STATUS "Data model: unusual int32 model")
        endif()
    elseif(${CDM} EQUAL 128)
        if(${LDM} EQUAL 888)
            set(${DM} "ILP64")
            message(STATUS "Data model: unusual 64bit numeric")
        else()
            set(${DM} "i64")
            message(STATUS "Data model: unusual int64 model")
        endif()
    elseif(${CDM} EQUAL 222 AND ${LDM} MATCHES "2$")
        set(${DM} "DSP16")
        message(STATUS "Data model: strict 16bit dsptype")
    elseif(${CDM} EQUAL 333 AND ${LDM} MATCHES "3$")
        set(${DM} "DSP24")
        message(STATUS "Data model: strict 24bit dsptype")
    elseif(${CDM} EQUAL 444 AND ${LDM} MATCHES "4$")
        set(${DM} "DSP32")
        message(STATUS "Data model: strict 32bit dsptype")
    elseif(${CDM} EQUAL 666 AND ${LDM} MATCHES "6$")
        set(${DM} "DSP48")
        message(STATUS "Data model: strict 48bit dsptype")
    elseif(${CDM} EQUAL 888 AND ${LDM} MATCHES "8$")
        set(${DM} "DSP64")
        message(STATUS "Data model: strict 64bit dsptype")
    elseif(${CDM} EQUAL 222 OR ${CDM} EQUAL 333 OR ${CDM} EQUAL 444 OR ${CDM} EQUAL 666 OR ${CDM} EQUAL 888)
        set(${DM} "iDSP")
        message(STATUS "Data model: unusual dsptype")
    else()
        set(${DM} "none")
        message(STATUS "Data model: very unusual model")
    endif()
endmacro()

# Check sizes of default types
macro(M__CHECK_DATA_MODEL)
    if (NOT DATA_MODEL)
	CHECK_TYPE_SIZE(int      SIZEOF_INT)
	CHECK_TYPE_SIZE(long     SIZEOF_LONG)
	  CHECK_TYPE_SIZE("void*"  SIZEOF_VOIDP)
	  CHECK_TYPE_SIZE(char     SIZEOF_CHAR)
	  CHECK_TYPE_SIZE(short    SIZEOF_SHORT)
	  CHECK_TYPE_SIZE(float    SIZEOF_FLOAT)
	  CHECK_TYPE_SIZE(double   SIZEOF_DOUBLE)
	  CHECK_TYPE_SIZE("unsigned int" SIZEOF_UNSIGNED_INT)
	  CHECK_TYPE_SIZE("unsigned long int" SIZEOF_UNSIGNED_LONG_INT)
	  CHECK_TYPE_SIZE("unsigned short int" SIZEOF_UNSIGNED_SHORT_INT)
	  CHECK_TYPE_SIZE("long long int"            SIZEOF_LONG_LONG_INT)
	  CHECK_TYPE_SIZE("unsigned long long"       SIZEOF_UNSIGNED_LONG_LONG)
	  CHECK_TYPE_SIZE("unsigned long long int"   SIZEOF_UNSIGNED_LONG_LONG_INT)
	  CHECK_TYPE_SIZE(ssize_t     SSIZE_T)
          CHECK_TYPE_SIZE(size_t HAVE_SIZE_T)
	  SET(CHAR_DATA_MODEL "${SIZEOF_CHAR}${SIZEOF_SHORT}${SIZEOF_INT}")
	  SET(LONG_DATA_MODEL "${SIZEOF_INT}${SIZEOF_LONG}${SIZEOF_VOIDP}")
	  M__GET_DATA_MODEL(DATA_MODEL ${CHAR_DATA_MODEL} ${LONG_DATA_MODEL})
	  SET(CHAR_DATA_MODEL "${CHAR_DATA_MODEL}" CACHE INTERNAL "Char compiler data model")
	  SET(LONG_DATA_MODEL "${LONG_DATA_MODEL}" CACHE INTERNAL "Long compiler data model")
	  SET(DATA_MODEL "${DATA_MODEL}" CACHE INTERNAL "Compiler data model")
    endif()
endmacro()

# Make variable contents suitable for #define
macro(M__DEFINE VARIABLE)
    get_property(__TMPVAL VARIABLE PROPERTY "${VARIABLE}")
    string(TOUPPER "${__TMPVAL}" __TMPVAL)
    string(REGEX REPLACE " *\\*" "_P" __TMPVAL "${__TMPVAL}")
    string(REGEX REPLACE "[^A-Z0-9_]+" "_" ${VARIABLE} "${__TMPVAL}")
    unset(__TMPVAL)
endmacro()

# Make define name for define guard from some filename
macro(M__DEFINE_FILENAME FILENAME)
    get_property(__TMPNAME VARIABLE PROPERTY "${FILENAME}")
    get_filename_component(__TMPNAME ${__TMPNAME} NAME)
    M__DEFINE(__TMPNAME)
    string(RANDOM LENGTH 5 ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" __FILENAME_TMP)
    set(${FILENAME} "${__TMPNAME}_${__FILENAME_TMP}")
    unset(__FILENAME_TMP)
    unset(__TMPNAME)
endmacro()

# Create stdint.h and store its contents in FILENAME
macro(CREATE_STDINT FILENAME)
    if(NOT EXISTS ${FILENAME})
    __check_type(uintptr_t SIZEOF_UINTPTR_T) # 1997 typedefs
    __check_type(uint64_t SIZEOF_UINT64_T)
    if (NOT SIZEOF_UINTPTR_T)
        __check_type(uint32_t SIZEOF_UINT32_T) # 1995 typedefs
        __check_type(uint64_t SIZEOF_UINT64_T)
    endif()
    if (NOT SIZEOF_UINTPTR_T AND NOT SIZEOF_UINT32_T)
        __check_type(u_int32_t SIZEOF_U_INT32_T)
        __check_type(u_int64_t SIZEOF_U_INT64_T) # BSD typedefs
    endif()

        M__CHECK_DATA_MODEL()


    if (SIZEOF_UINTPTR_T)
        set(INCLUDE_HEADER "${SIZEOF_UINTPTR_T_HEADER}")
    elseif(SIZEOF_UINT32_T)
        set(INCLUDE_HEADER "${SIZEOF_UINT32_T_HEADER}")
    elseif(SIZEOF_U_INT32_T)
        set(INCLUDE_HEADER "${SIZEOF_U_INT32_T_HEADER}")
    else()
        set(INCLUDE_HEADER "stddef.h")
    endif()

    __check_type(int_least32_t SIZEOF_INT_LEAST32_T ${INCLUDE_HEADER})
    __check_type(int_fast32_t SIZEOF_INT_FAST32_T ${INCLUDE_HEADER})
    __check_type(intmax_t SIZEOF_INTMAX_T ${INCLUDE_HEADER})
    set(HEADER_GUARD "${FILENAME}")
    M__DEFINE_filename(HEADER_GUARD)
    file(WRITE "${FILENAME}" "#ifndef ${HEADER_GUARD}
#define ${HEADER_GUARD} 1
#ifndef _GENERATED_STDINT_H
#define _GENERATED_STDINT_H 1")
    if (HAVE_STDINT_H) # TODO FIXME
        file(APPEND "${FILENAME}" "
#define _STDINT_HAVE_STDINT_H 1
#include <stdint.h>
#endif
#endif")
    else()
        file(APPEND "${FILENAME}" "
#if defined HAVE_STDINT_H || defined _STDINT_HAVE_STDINT_H
#include <stdint.h>
#else
#include <stddef.h>")
        if (SIZEOF_UINTPTR_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HEADER_INTPTR \"${SIZEOF_UINTPTR_T_HEADER}\"")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HEADER_INTPTR */")
        endif()

        if (SIZEOF_UINT32_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HEADER_UINT32 \"${SIZEOF_UINT32_T_HEADER}\"")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HEADER_UINT32 */")
        endif()
        if (SIZEOF_U_INT32_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HEADER_U_INT32 \"${SIZEOF_U_INT32_T_HEADER}\"")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HEADER_U_INT32 */")
        endif()

        if (DEFINED INCLUDE_HEADER AND (NOT INCLUDE_HEADER STREQUAL "stddef.h"))
            file(APPEND "${FILENAME}" "
#include <${INCLUDE_HEADER}>")
        endif()

        if (SIZEOF_UINT64_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HAVE_UINT64_T 1")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HAVE_UINT64_T */")
        endif()
        if(SIZEOF_U_INT64_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HAVE_U_INT64_T 1")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HAVE_U_INT64_T */")
        endif()

        if (DATA_MODEL)
            file(APPEND "${FILENAME}" "
#define _STDINT_CHAR_MODEL ${CHAR_DATA_MODEL}
#define _STDINT_LONG_MODEL ${LONG_DATA_MODEL}")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_CHAR_MODEL // skipped */
/* #undef _STDINT_LONG_MODEL // skipped */")
        endif()
        
        if(SIZEOF_INT_LEAST32_T)
            file(APPEND "${FILENAME}" "
#define  _STDINT_HAVE_INT_LEAST32_T 1")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HAVE_INT_LEAST32_T */")
        endif()
        if(SIZEOF_INT_FAST32_T)
            file(APPEND "${FILENAME}" "
#define  _STDINT_HAVE_INT_FAST32_T 1")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HAVE_INT_FAST32_T */")
        endif()
        if(SIZEOF_INTMAX_T)
            file(APPEND "${FILENAME}" "
#define _STDINT_HAVE_INTMAX_T 1")
        else()
            file(APPEND "${FILENAME}" "
/* #undef _STDINT_HAVE_INTMAX_T */")
        endif()

        file(APPEND "${FILENAME}" "
/* whether we need to define bitspecific types from compiler base types */
#ifndef _STDINT_HEADER_INTPTR
#ifndef _STDINT_HEADER_UINT32
#ifndef _STDINT_HEADER_U_INT32
#define _STDINT_NEED_INT_MODEL_T
#else
#define _STDINT_HAVE_U_INT_TYPES
#endif
#endif
#endif

#ifdef _STDINT_HAVE_U_INT_TYPES
#undef _STDINT_NEED_INT_MODEL_T
#endif

#ifdef  _STDINT_CHAR_MODEL
#if     _STDINT_CHAR_MODEL+0 == 122 || _STDINT_CHAR_MODEL+0 == 124
#ifndef _STDINT_BYTE_MODEL
#define _STDINT_BYTE_MODEL 12
#endif
#endif
#endif

#ifndef _STDINT_HAVE_INT_LEAST32_T
#define _STDINT_NEED_INT_LEAST_T
#endif

#ifndef _STDINT_HAVE_INT_FAST32_T
#define _STDINT_NEED_INT_FAST_T
#endif

#ifndef _STDINT_HEADER_INTPTR
#define _STDINT_NEED_INTPTR_T
#ifndef _STDINT_HAVE_INTMAX_T
#define _STDINT_NEED_INTMAX_T
#endif
#endif


/* .................... definition part ............................ */

/* some system headers have good uint64_t */
#ifndef _HAVE_UINT64_T
#if     defined _STDINT_HAVE_UINT64_T  || defined HAVE_UINT64_T
#define _HAVE_UINT64_T
#elif   defined _STDINT_HAVE_U_INT64_T || defined HAVE_U_INT64_T
#define _HAVE_UINT64_T
typedef u_int64_t uint64_t;
#endif
#endif

#ifndef _HAVE_UINT64_T
/* .. here are some common heuristics using compiler runtime specifics */
#if defined __STDC_VERSION__ && defined __STDC_VERSION__ >= 199901L
#define _HAVE_UINT64_T
#define _HAVE_LONGLONG_UINT64_T
typedef long long int64_t;
typedef unsigned long long uint64_t;

#elif !defined __STRICT_ANSI__
#if defined _MSC_VER || defined __WATCOMC__ || defined __BORLANDC__
#define _HAVE_UINT64_T
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#elif defined __GNUC__ || defined __MWERKS__ || defined __ELF__
/* note: all ELF-systems seem to have loff-support which needs 64-bit */
#if !defined _NO_LONGLONG
#define _HAVE_UINT64_T
#define _HAVE_LONGLONG_UINT64_T
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif

#elif defined __alpha || (defined __mips && defined _ABIN32)
#if !defined _NO_LONGLONG
typedef long int64_t;
typedef unsigned long uint64_t;
#endif
  /* compiler/cpu type to define int64_t */
#endif
#endif
#endif

#if defined _STDINT_HAVE_U_INT_TYPES
/* int8_t int16_t int32_t defined by inet code, redeclare the u_intXX types */
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;

/* glibc compatibility */
#ifndef __int8_t_defined
#define __int8_t_defined
#endif
#endif

#ifdef _STDINT_NEED_INT_MODEL_T
/* we must guess all the basic types. Apart from byte-adressable system, */
/* there a few 32-bit-only dsp-systems that we guard with BYTE_MODEL 8-} */
/* (btw, those nibble-addressable systems are way off, or so we assume) */

#if defined _STDINT_BYTE_MODEL
#if _STDINT_LONG_MODEL+0 == 242
/* 2:4:2 =  IP16 = a normal 16-bit system                */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
#ifndef __int8_t_defined
#define __int8_t_defined
typedef          char    int8_t;
typedef          short   int16_t;
typedef          long    int32_t;
#endif
#elif _STDINT_LONG_MODEL+0 == 244 || _STDINT_LONG_MODEL == 444
/* 2:4:4 =  LP32 = a 32-bit system derived from a 16-bit */
/* 4:4:4 = ILP32 = a normal 32-bit system                */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
#ifndef __int8_t_defined
#define __int8_t_defined
typedef          char    int8_t;
typedef          short   int16_t;
typedef          int     int32_t;
#endif
#elif _STDINT_LONG_MODEL+0 == 484 || _STDINT_LONG_MODEL+0 == 488
/* 4:8:4 =  IP32 = a 32-bit system prepared for 64-bit    */
/* 4:8:8 =  LP64 = a normal 64-bit system                 */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
#ifndef __int8_t_defined
#define __int8_t_defined
typedef          char    int8_t;
typedef          short   int16_t;
typedef          int     int32_t;
#endif
/* this system has a \"long\" of 64bit */
#ifndef _HAVE_UINT64_T
#define _HAVE_UINT64_T
typedef unsigned long   uint64_t;
typedef          long    int64_t;
#endif
#elif _STDINT_LONG_MODEL+0 == 448
/*      LLP64   a 64-bit system derived from a 32-bit system */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
#ifndef __int8_t_defined
#define __int8_t_defined
typedef          char    int8_t;
typedef          short   int16_t;
typedef          int     int32_t;
#endif
/* assuming the system has a \"long long\" */
#ifndef _HAVE_UINT64_T
#define _HAVE_UINT64_T
#define _HAVE_LONGLONG_UINT64_T
typedef unsigned long long uint64_t;
typedef          long long  int64_t;
#endif
#else
#define _STDINT_NO_INT32_T
#endif
#else
#define _STDINT_NO_INT8_T
#define _STDINT_NO_INT32_T
#endif
#endif

/*
 * quote from SunOS-5.8 sys/inttypes.h:
 * Use at your own risk.  As of February 1996, the committee is squarely
 * behind the fixed sized types; the \"least\" and \"fast\" types are still being
 * discussed.  The probability that the \"fast\" types may be removed before
 * the standard is finalized is high enough that they are not currently
 * implemented.
 */

#if defined _STDINT_NEED_INT_LEAST_T
typedef  int8_t    int_least8_t;
typedef  int16_t   int_least16_t;
typedef  int32_t   int_least32_t;
#ifdef _HAVE_UINT64_T
typedef  int64_t   int_least64_t;
#endif

typedef uint8_t   uint_least8_t;
typedef uint16_t  uint_least16_t;
typedef uint32_t  uint_least32_t;
#ifdef _HAVE_UINT64_T
typedef uint64_t  uint_least64_t;
#endif
  /* least types */
#endif

#if defined _STDINT_NEED_INT_FAST_T
typedef  int8_t    int_fast8_t;
typedef  int       int_fast16_t;
typedef  int32_t   int_fast32_t;
#ifdef _HAVE_UINT64_T
typedef  int64_t   int_fast64_t;
#endif

typedef uint8_t   uint_fast8_t;
typedef unsigned  uint_fast16_t;
typedef uint32_t  uint_fast32_t;
#ifdef _HAVE_UINT64_T
typedef uint64_t  uint_fast64_t;
#endif
  /* fast types */
#endif

#ifdef _STDINT_NEED_INTMAX_T
#ifdef _HAVE_UINT64_T
typedef  int64_t       intmax_t;
typedef uint64_t      uintmax_t;
#else
typedef          long  intmax_t;
typedef unsigned long uintmax_t;
#endif
#endif

#ifdef _STDINT_NEED_INTPTR_T
#ifndef __intptr_t_defined
#define __intptr_t_defined
/* we encourage using \"long\" to store pointer values, never use \"int\" ! */
#if   _STDINT_LONG_MODEL+0 == 242 || _STDINT_LONG_MODEL+0 == 484
typedef  unsigned int   uintptr_t;
typedef           int    intptr_t;
#elif _STDINT_LONG_MODEL+0 == 244 || _STDINT_LONG_MODEL+0 == 444
typedef  unsigned long  uintptr_t;
typedef           long   intptr_t;
#elif _STDINT_LONG_MODEL+0 == 448 && defined _HAVE_UINT64_T
typedef        uint64_t uintptr_t;
typedef         int64_t  intptr_t;
#else /* matches typical system types ILP32 and LP64 - but not IP16 or LLP64 */
typedef  unsigned long  uintptr_t;
typedef           long   intptr_t;
#endif
#endif
#endif

/* The ISO C99 standard specifies that in C++ implementations these
   should only be defined if explicitly requested.  */
#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS
#ifndef UINT32_C

/* Signed.  */
# define INT8_C(c)      c
# define INT16_C(c)     c
# define INT32_C(c)     c
# ifdef _HAVE_LONGLONG_UINT64_T
#  define INT64_C(c)    c ## L
# else
#  define INT64_C(c)    c ## LL
# endif

/* Unsigned.  */
# define UINT8_C(c)     c ## U
# define UINT16_C(c)    c ## U
# define UINT32_C(c)    c ## U
# ifdef _HAVE_LONGLONG_UINT64_T
#  define UINT64_C(c)   c ## UL
# else
#  define UINT64_C(c)   c ## ULL
# endif

/* Maximal type.  */
# ifdef _HAVE_LONGLONG_UINT64_T
#  define INTMAX_C(c)   c ## L
#  define UINTMAX_C(c)  c ## UL
# else
#  define INTMAX_C(c)   c ## LL
#  define UINTMAX_C(c)  c ## ULL
# endif

  /* literalnumbers */
#endif
#endif

/* These limits are merily those of a two complement byte-oriented system */

/* Minimum of signed integral types.  */
# define INT8_MIN               (-128)
# define INT16_MIN              (-32767-1)
# define INT32_MIN              (-2147483647-1)
# define INT64_MIN              (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
# define INT8_MAX               (127)
# define INT16_MAX              (32767)
# define INT32_MAX              (2147483647)
# define INT64_MAX              (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX              (255)
# define UINT16_MAX             (65535)
# define UINT32_MAX             (4294967295U)
# define UINT64_MAX             (__UINT64_C(18446744073709551615))

/* Minimum of signed integral types having a minimum size.  */
# define INT_LEAST8_MIN         INT8_MIN
# define INT_LEAST16_MIN        INT16_MIN
# define INT_LEAST32_MIN        INT32_MIN
# define INT_LEAST64_MIN        INT64_MIN
/* Maximum of signed integral types having a minimum size.  */
# define INT_LEAST8_MAX         INT8_MAX
# define INT_LEAST16_MAX        INT16_MAX
# define INT_LEAST32_MAX        INT32_MAX
# define INT_LEAST64_MAX        INT64_MAX

/* Maximum of unsigned integral types having a minimum size.  */
# define UINT_LEAST8_MAX        UINT8_MAX
# define UINT_LEAST16_MAX       UINT16_MAX
# define UINT_LEAST32_MAX       UINT32_MAX
# define UINT_LEAST64_MAX       UINT64_MAX

  /* shortcircuit*/
#endif
  /* once */
#endif
#endif
")
    endif()
    file(APPEND "${FILENAME}" "\n") # Prevent compiler messages about newlines
    message(STATUS "stdint header was generated in ${FILENAME}")
else()
	message(STATUS "stdint header still generated in ${FILENAME}")
endif()
endmacro()

IF (WIN32)
  SET (HAVE_LIBM 1)
  SET (HAVE_IO_H 1)
  SET (HAVE_SETJMP_H 1)
  SET (HAVE_STDDEF_H 1)
  SET (HAVE_STRDUP 1)
  SET (HAVE_SYSTEM 1)
  SET (HAVE_DIFFTIME 1)
  SET (HAVE_LONGJMP 1)
  SET (HAVE_GETHOSTNAME 1)
  SET (HAVE_TIMEZONE 1)
  SET (HAVE_FUNCTION 1)
ENDIF (WIN32)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
 ADD_DEFINITIONS(-fPIC)
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" ) 
IF(CMAKE_GENERATOR MATCHES "Visual Studio 7")
  INCLUDE(CMakeVS7BackwardCompatibility)
  SET(CMAKE_SKIP_COMPATIBILITY_TESTS 1)
ENDIF(CMAKE_GENERATOR MATCHES "Visual Studio 7")
IF(CMAKE_GENERATOR MATCHES "Visual Studio 6")
  INCLUDE(CMakeVS6BackwardCompatibility)
  SET(CMAKE_SKIP_COMPATIBILITY_TESTS 1)
ENDIF(CMAKE_GENERATOR MATCHES "Visual Studio 6")

if (APPLE)
	SET(CMAKE_FIND_FRAMEWORK "FIRST")
endif()

CHECK_INCLUDE_FILE("bits/atomicity.h" HAVE_ATOMIC_GCC)

CHECK_INCLUDE_FILE("asm/atomic.h" HAVE_ATOMIC_LINUX)

if(WIN32)
	check_include_file(windows.h HAVE_WINDOWS_H)
	CHECK_PROTOTYPE_EXISTS(_beginthreadex "windows.h" HAVE_BEGINTHREADEX)
endif()

if(UNIX AND NOT APPLE)
	CHECK_LIBRARY_EXISTS(${PTHREAD_LIBNAME} "pthread_create" "" HAVE_POSIX_THREADS)
	CHECK_LIBRARY_EXISTS(${PTHREAD_LIBNAME} "pthread_keycreate" "" HAVE_PTHREADKEYCREATE)
	CHECK_LIBRARY_EXISTS(${PTHREAD_LIBNAME} "pthread_yield" "" HAVE_PTHREAD_YIELD)
elseif(APPLE)
	SET(HAVE_POSIX_THREADS 1) #Mac OS X has pthreads integrated into it's system librarys
endif()
	CHECK_INCLUDE_FILE("limits.h"       HAVE_LIMITS_H)
	CHECK_INCLUDE_FILE("assert.h" 		HAVE_ASSERT_H)
	CHECK_INCLUDE_FILE("inttypes.h" 	HAVE_INTTYPES_H)
	CHECK_INCLUDE_FILE("unistd.h"       HAVE_UNISTD_H)
	CHECK_INCLUDE_FILE("pthread.h"      HAVE_PTHREAD_H)
	CHECK_INCLUDE_FILE("math.h" 		HAVE_MATH_H)
	CHECK_INCLUDE_FILE("cmath.h"		HAVE_CMATH_H)
	CHECK_INCLUDE_FILE("memory.h" 		HAVE_MEMORY_H)
	CHECK_INCLUDE_FILE("stdarg.h" 		HAVE_STDARG_H)
	CHECK_INCLUDE_FILE("stdint.h" 		HAVE_STDINT_H)
	CHECK_INCLUDE_FILE("stdlib.h" 		HAVE_STDLIB_H)
	CHECK_INCLUDE_FILE("strings.h" 		HAVE_STRINGS_H)
	CHECK_INCLUDE_FILE("string.h" 		HAVE_STRING_H)
	CHECK_INCLUDE_FILE("sys/stat.h" 	HAVE_SYS_STAT_H)
	CHECK_INCLUDE_FILE("sys/types.h" 	HAVE_SYS_TYPES_H)
	CHECK_INCLUDE_FILE("sys/time.h" 	HAVE_SYS_TIME_H)
	CHECK_INCLUDE_FILE("sys/timeb.h" 	HAVE_SYS_TIMEB_H)
	CHECK_INCLUDE_FILE("time.h" 		HAVE_TIME_H)
	CHECK_INCLUDE_FILE("signal.h" 		HAVE_SIGNAL_H)
	CHECK_INCLUDE_FILE("dlfcn.h" 		HAVE_DLFCN_H)
	CHECK_INCLUDE_FILE("errno.h" 		HAVE_ERRNO_H)
	CHECK_INCLUDE_FILE("direct.h"		HAVE_DIRECT_H)
	CHECK_INCLUDE_FILE("process.h"		HAVE_PROCESS_H)
	CHECK_INCLUDE_FILE("stdio.h"		HAVE_STDIO_H)
	CHECK_INCLUDE_FILE("tchar.h"      	HAVE_TCHAR_H)
	CHECK_INCLUDE_FILES("sys/types.h;sys/prctl.h"    HAVE_SYS_PRCTL_H)
	CHECK_INCLUDE_FILES("stdlib.h;stddef.h;stdarg.h" STDC_HEADERS)

# check_include_file(argz.h HAVE_ARGZ_H)
# check_include_file(assert.h HAVE_ASSERT_H)
# check_include_file(dirent.h HAVE_DIRENT_H)
# check_include_file(dl.h HAVE_DL_H)
# check_include_file(dld.h HAVE_DLD_H)
# check_include_file(execinfo.h HAVE_EXECINFO_H)
# check_include_file(fcntl.h HAVE_FCNTL_H)
# check_include_file(link.h HAVE_LINK_H)
# check_include_file(malloc.h HAVE_MALLOC_H)
# check_include_file(malloc/malloc.h HAVE_MALLOC_MALLOC_H)
# check_include_file(ndir.h HAVE_NDIR_H)
# check_include_file(stdlib.h HAVE_STDLIB_H)
# check_include_file(sys/dir.h HAVE_SYS_DIR_H)
# check_include_file(sys/dl.h HAVE_SYS_DL_H)
# check_include_file(sys/mman.h HAVE_SYS_MMAN_H)
# check_include_file(sys/ndir.h HAVE_SYS_NDIR_H)
# check_include_file(sys/param.h HAVE_SYS_PARAM_H)
# check_include_file(sys/resource.h HAVE_SYS_RESOURCE_H)
# check_include_file(utime.h HAVE_UTIME_H)

 
  
IF (NOT HAVE_INTTYPES_H)
CREATE_STDINT(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/inttypes.h)
ELSE(NOT HAVE_INTTYPES_H)
M__CHECK_DATA_MODEL()
ENDIF (NOT HAVE_INTTYPES_H)
  
IF(NOT HAVE_SSIZE_T)
  IF("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    SET(ssize_t "int64_t")
  ELSE("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    SET(ssize_t "long")
  ENDIF("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
ENDIF(NOT HAVE_SSIZE_T)

INCLUDE (FindThreads)

SET (CMAKE_THREAD_LIBS        "${CMAKE_THREAD_LIBS_INIT}" CACHE STRING 
    "Thread library used.")
SET (CMAKE_USE_PTHREADS       "${CMAKE_USE_PTHREADS_INIT}" CACHE BOOL
     "Use the pthreads library.")

SET (CMAKE_USE_WIN32_THREADS  "${CMAKE_USE_WIN32_THREADS_INIT}" CACHE BOOL
       "Use the win32 thread library.")

IF(NOT CMAKE_SKIP_COMPATIBILITY_TESTS)

  INCLUDE (TestBigEndian)
  TEST_BIG_ENDIAN(WORDS_BIGENDIAN)
    
 IF(${WORDS_BIGENDIAN})
     ADD_DEFINITIONS(-DBIGENDIAN)
ENDIF(${WORDS_BIGENDIAN})
    
  IF("${X11_X11_INCLUDE_PATH}" MATCHES "^/usr/include$")
    SET (CMAKE_X_CFLAGS "" CACHE STRING "X11 extra flags.")
  ELSE("${X11_X11_INCLUDE_PATH}" MATCHES "^/usr/include$")
    SET (CMAKE_X_CFLAGS "-I${X11_X11_INCLUDE_PATH}" CACHE STRING
         "X11 extra flags.")
  ENDIF("${X11_X11_INCLUDE_PATH}" MATCHES "^/usr/include$")
  SET (CMAKE_X_LIBS "${X11_LIBRARIES}" CACHE STRING
       "Libraries and options used in X11 programs.")
  SET (CMAKE_HAS_X "${X11_FOUND}" CACHE INTERNAL "Is X11 around.")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-fPIC" SUPPORTS_FPIC_FLAG)

ENDIF(NOT CMAKE_SKIP_COMPATIBILITY_TESTS)

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/config.h.cmake ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Native_Config.h)

MARK_AS_ADVANCED(
CMAKE_THREAD_LIBS
CMAKE_USE_PTHREADS
CMAKE_USE_WIN32_THREADS
CMAKE_X_CFLAGS
CMAKE_X_LIBS
)
