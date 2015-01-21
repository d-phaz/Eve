
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
#ifndef __EVE_SYSTEM_INCLUDES_H__
#define __EVE_SYSTEM_INCLUDES_H__


#ifndef __EVE_CORE_SYSTEM_DEFINITION__
#include "eve/core/SystemDefinition.h"
#endif


#if defined(EVE_OS_WIN)
	#ifndef __EVE_SYSTEM_CURSOR_H__
	#include "eve/sys/win32/Cursor.h"
	#endif

	#ifndef __EVE_SYSTEM_DISPLAY_H__
	#include "eve/sys/win32/Display.h"
	#endif

	#ifndef __EVE_SYSTEM_KEYBOARD_H__
	#include "eve/sys/win32/Keyboard.h"
	#endif

	#ifndef __EVE_SYSTEM_MOUSE_H__
	#include "eve/sys/shared/Mouse.h"
	#endif

	#ifndef __EVE_SYSTEM_MESSAGE_PUMP_H__
	#include "eve/sys/win32/MessagePump.h"
	#endif

	#ifndef __EVE_SYSTEM_NOTIFICATION_H__
	#include "eve/sys/win32/Notification.h"
	#endif

	#ifndef __EVE_SYSTEM_WINDOW_H__
	#include "eve/sys/win32/Window.h"
	#endif
#endif


#endif // __EVE_SYSTEM_INCLUDES_H__
