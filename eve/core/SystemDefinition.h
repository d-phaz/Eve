
#pragma once
#ifndef __EVE_CORE_SYSTEM_DEFINITION__
#define __EVE_CORE_SYSTEM_DEFINITION__


/*
 Selecting operating system, from (TOS_OS_type)

 DARWIN   - Darwin OS (same as TOS_OS_MAC)
 WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
 LINUX    - Linux
 FREEBSD  - FreeBSD
 NETBSD   - NetBSD
 OPENBSD  - OpenBSD
 BSDI     - BSD/OS
 BSD4     - Various BSD 4.4 system
 UNIX     - Various UNIX BSD/SYSV system
 */

#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  define TOS_OS_DARWIN
#  define TOS_OS_BSD4
#  define TOS_NO_STL_SWAP
#ifndef __MACOSX_CORE__
#define __MACOSX_CORE__
#endif
#  ifdef __LP64__
#    define TOS_OS_DARWIN64
#    define TOS_OS_64 1
#  else
#    define TOS_OS_DARWIN32
#  endif
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define TOS_OS_WIN32
#  define TOS_OS_WIN64
#  define TOS_OS_64 1
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINCE) || defined(_WIN32_WCE)
#    define TOS_OS_WINCE
#  else
#    define TOS_OS_WIN32
#    define TOS_COMPILER_MANGLES_RETURN_TYPE
#  endif
#elif defined(__linux__) || defined(__linux)
#  define TOS_OS_LINUX
#if defined (__LP64__) || defined (_LP64)
#define TOS_OS_64 1
#endif
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#if defined (__LP64__) || defined (_LP64)
#define TOS_OS_64 1
#endif
#  define TOS_OS_FREEBSD
#  define TOS_OS_BSD4
#elif defined(__NetBSD__)
#if defined (__LP64__) || defined (_LP64)
#define TOS_OS_64 1
#endif
#  define TOS_OS_NETBSD
#  define TOS_OS_BSD4
#elif defined(__OpenBSD__)
#if defined (__LP64__) || defined (_LP64)
#define TOS_OS_64 1
#endif
#  define TOS_OS_OPENBSD
#  define TOS_OS_BSD4
#elif defined(__bsdi__)
#if defined (__LP64__) || defined (_LP64)
#define TOS_OS_64 1
#endif
#  define TOS_OS_BSDI
#  define TOS_OS_BSD4
#else
#  error "Not supported build plateform"
#endif

#if defined(TOS_OS_WIN32) || defined(TOS_OS_WIN64) || defined(TOS_OS_WINCE)
#  define TOS_OS_WIN
#endif


/*
   Selecting window system type (TOS_WS_type):

   MACX     - Mac OS X
   WIN32    - Windows
   X11      - X Window System
   */

#if defined(TOS_OS_MSDOS)
#  define TOS_WS_WIN16
#  error "CPGP requires Win32 and does not work with Windows 3.x"
#elif defined(_WIN32_X11_)
#  define TOS_WS_X11
#elif defined(TOS_OS_WIN32)
#  define TOS_WS_WIN32
#  if defined(TOS_OS_WIN64)
#    define TOS_WS_WIN64
#  endif
#elif defined(TOS_OS_WINCE)
#  define TOS_WS_WIN32
#  define TOS_WS_WINCE
#  if defined(TOS_OS_WINCE_WM)
#    define TOS_WS_WINCE_WM
#  endif
#elif defined(TOS_OS_UNIX)
#  if defined(TOS_OS_MAC) && !defined(__USE_WS_X11__) && !defined(TOS_WS_QWS) && !defined(TOS_WS_QPA)
#    define TOS_WS_MAC
#    define TOS_WS_MACX
#    if defined(TOS_OS_MAC64)
#      define TOS_WS_MAC64
#    elif defined(TOS_OS_MAC32)
#      define TOS_WS_MAC32
#    endif
#  elif !defined(TOS_WS_QWS) && !defined(TOS_WS_QPA)
#    define TOS_WS_X11
#  endif
#endif

#if defined(TOS_WS_WIN16) || defined(TOS_WS_WIN32) || defined(TOS_WS_WIN64) || defined(TOS_WS_WINCE) 
#  define TOS_WS_WIN
#endif


#endif // __EVE_CORE_SYSTEM_DEFINITION__
