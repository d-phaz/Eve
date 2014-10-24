
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef __EVE_CORE_SYSTEM_DEFINITION__
#define __EVE_CORE_SYSTEM_DEFINITION__


/*
 Selecting operating system, from (EVE_OS_type)

 DARWIN   - Darwin OS (same as EVE_OS_MAC)
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
#  define EVE_OS_DARWIN
#  define EVE_OS_BSD4
#  define EVE_NO_STL_SWAP
#ifndef __MACOSX_CORE__
#define __MACOSX_CORE__
#endif
#  ifdef __LP64__
#    define EVE_OS_DARWIN64
#    define EVE_OS_64 1
#  else
#    define EVE_OS_DARWIN32
#  endif
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define EVE_OS_WIN32
#  define EVE_OS_WIN64
#  define EVE_OS_64 1
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINCE) || defined(_WIN32_WCE)
#    define EVE_OS_WINCE
#  else
#    define EVE_OS_WIN32
#    define EVE_COMPILER_MANGLES_RETURN_TYPE
#  endif
#elif defined(__linux__) || defined(__linux)
#  define EVE_OS_LINUX
#if defined (__LP64__) || defined (_LP64)
#define EVE_OS_64 1
#endif
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#if defined (__LP64__) || defined (_LP64)
#define EVE_OS_64 1
#endif
#  define EVE_OS_FREEBSD
#  define EVE_OS_BSD4
#elif defined(__NetBSD__)
#if defined (__LP64__) || defined (_LP64)
#define EVE_OS_64 1
#endif
#  define EVE_OS_NETBSD
#  define EVE_OS_BSD4
#elif defined(__OpenBSD__)
#if defined (__LP64__) || defined (_LP64)
#define EVE_OS_64 1
#endif
#  define EVE_OS_OPENBSD
#  define EVE_OS_BSD4
#elif defined(__bsdi__)
#if defined (__LP64__) || defined (_LP64)
#define EVE_OS_64 1
#endif
#  define EVE_OS_BSDI
#  define EVE_OS_BSD4
#else
#  error "Not supported build plateform"
#endif

#if defined(EVE_OS_WIN32) || defined(EVE_OS_WIN64) || defined(EVE_OS_WINCE)
#  define EVE_OS_WIN
#endif


/*
   Selecting window system type (EVE_WS_type):

   MACX     - Mac OS X
   WIN32    - Windows
   X11      - X Window System
   */

#if defined(EVE_OS_MSDOS)
#  define EVE_WS_WIN16
#  error "CPGP requires Win32 and does not work with Windows 3.x"
#elif defined(_WIN32_X11_)
#  define EVE_WS_X11
#elif defined(EVE_OS_WIN32)
#  define EVE_WS_WIN32
#  if defined(EVE_OS_WIN64)
#    define EVE_WS_WIN64
#  endif
#elif defined(EVE_OS_WINCE)
#  define EVE_WS_WIN32
#  define EVE_WS_WINCE
#  if defined(EVE_OS_WINCE_WM)
#    define EVE_WS_WINCE_WM
#  endif
#elif defined(EVE_OS_UNIX)
#  if defined(EVE_OS_MAC) && !defined(__USE_WS_X11__) && !defined(EVE_WS_QWS) && !defined(EVE_WS_QPA)
#    define EVE_WS_MAC
#    define EVE_WS_MACX
#    if defined(EVE_OS_MAC64)
#      define EVE_WS_MAC64
#    elif defined(EVE_OS_MAC32)
#      define EVE_WS_MAC32
#    endif
#  elif !defined(EVE_WS_QWS) && !defined(EVE_WS_QPA)
#    define EVE_WS_X11
#  endif
#endif

#if defined(EVE_WS_WIN16) || defined(EVE_WS_WIN32) || defined(EVE_WS_WIN64) || defined(EVE_WS_WINCE) 
#  define EVE_WS_WIN
#endif



#if defined(EVE_OS_WIN)
#define EVE_FORCE_INLINE __forceinline
#else
#define EVE_FORCE_INLINE inline
#endif

#endif // __EVE_CORE_SYSTEM_DEFINITION__
