
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
#ifndef __EVE_THREADING_INCLUDES_H__
#define __EVE_THREADING_INCLUDES_H__


#ifndef __EVE_THREADING_CONDITION_H__
#include "eve/thr/Condition.h"
#endif

#ifndef __EVE_THREADING_LOCK_H__
#include "eve/thr/Lock.h"
#endif 

#ifndef __EVE_THREADING_MUTEX_H__
#include "eve/thr/Mutex.h"
#endif

#ifndef __EVE_THREADING_SCOPED_FENCE_H__
#include "eve/thr/ScopedFence.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/thr/SpinLock.h"
#endif 

#ifndef __EVE_THREADING_THREAD_H__
#include "eve/thr/Thread.h"
#endif 

#ifndef __EVE_THREADING_UTILS_H__
#include "eve/thr/Utils.h"
#endif

#ifndef __EVE_THREADING_WORKER_H__
#include "eve/thr/Worker.h"
#endif


#endif // __EVE_THREADING_INCLUDES_H__
