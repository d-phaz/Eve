
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
#ifndef __EVE_CORE_INCLUDES_H__
#define __EVE_CORE_INCLUDES_H__


#ifndef __EVE_CORE_SYSTEM_DEFINITION__
#include "eve/core/SystemDefinition.h"
#endif


// C++ standard lib
#include <stdlib.h>
// C++ standard definitions
#include <stddef.h>
// standard input/output stream objects
#include <stdio.h>
#include <iostream>
#include <locale>
#include <sstream>
#include <fstream>
// x64 compliant integers
#include <stdint.h>
// math
#include <float.h>
#include <math.h>
#include <climits>
// algorithm
#include <algorithm>
// pointers and memory
#include <malloc.h>
#include <memory>
// assertion
#include <cassert>
// standard string
#include <string>
// container types
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <vector>
#include <map>
#include <hash_map>
#include <stack>
// utility
#include <utility>
// type utility
#include <type_traits>
// time
#if defined(EVE_OS_WIN)
#include <sys\timeb.h>
#elif defined(EVE_OS_DARWIN)
#include <mach/mach_time.h>
#elif defined(EVE_OS_LINUX)
#include <time.h>
#endif
//random
#include <random>
// STD exception
#include <stdexcept>


#if defined(EVE_OS_WIN)

	#include <Windows.h>
	#include <Shtypes.h>

#endif // defined(EVE_OS_WIN)


#ifndef __EVE_EXTERNAL_H__
#include "eve/generated/External.h"
#endif

#ifndef __EVE_VERSION_H__
#include "eve/generated/Version.h"
#endif

#ifndef __EVE_CORE_MACRO_H__
#include "eve/core/Macro.h"
#endif

#endif // __EVE_CORE_INCLUDES_H__
