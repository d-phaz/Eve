
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

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/thr/Includes.h"
#endif

#ifndef __EVE_THREADING_THREAD_DUMMY_H__
#include "eve/thr/ThreadDummy.h"
#endif 

#ifndef __EVE_EVT_INCLUDES_H__
#include "eve/evt/Includes.h"
#endif

#ifndef __EVE_SYSTEM_INCLUDES_H__
#include "eve/sys/Includes.h"
#endif


class Example
{
	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	EVE_DISABLE_COPY(Example);

public:
	Example(void)
	{
		eve::mess::Server::create_instance();
		eve::evt::register_events_mouse(this);
		eve::evt::register_events_window(this);
	}
	virtual ~Example(void)
	{
		eve::evt::unregister_events_window(this);
		eve::evt::unregister_events_mouse(this);
		eve::mess::Server::release_instance();
	}

public:
	void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
	{
		EVE_LOG_INFO("Mouse Event, button is %i, X is %i, Y is %i.", p_args.button, p_args.x, p_args.y);
	}

	void cb_evtMouseUp(eve::evt::MouseEventArgs & p_args){}
	void cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args){}
	void cb_evtMotion(eve::evt::MouseEventArgs & p_args){}
	void cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args){}

	void cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg){}
	void cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg){}
	void cb_evtWindowFocusGot(void){}
	void cb_evtWindowFocusLost(void){}
	void cb_evtWindowClose(void){}

};



int main(int argc, char **argv)
{
	// Hide console window in release mode.
#if defined(NDEBUG)
	: ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif	


	//-------------------------------------------


	// Messaging example //

	eve::mess::Server::create_instance();
	EVE_LOG_INFO("eve Version: %s", EVE_VERSIONNAME);
	EVE_LOG_WARNING("Warning level %i.", 3);
	EVE_LOG_PROGRESS("App execution in progress.");
	EVE_LOG_DEBUG("Woups... debug log info.");
	EVE_LOG_ERROR("Any error occurred?");
	//eve::mess::Server::release_instance();


	//-------------------------------------------


	// Thread Pointer example //

	//// Create thread pointer.
	//eve::thr::ThreadDummy * thr = EVE_CREATE_PTR(eve::thr::ThreadDummy);
	//// Start thread.
	//thr->start();
	//// Sleep using microseconds.
	//eve::thr::sleep_micro(1000ULL * 1000ULL);
	//// Release pointer.
	//EVE_RELEASE_PTR(thr);


	//-------------------------------------------


	// Thread Scoped pointer example //

	// Create scoped thread pointer.
	eve::mem::Scoped<eve::thr::ThreadDummy> scThr;
	// Start thread.
	scThr->start();

	// Sleep using milliseconds.
	eve::thr::sleep_milli(1000);


	//-------------------------------------------


	// Event example //

	Example ex;
	eve::evt::notify_mouse_down(0, 10, 20);


	//-------------------------------------------


	// Window example //

	//eve::sys::Window * win = eve::sys::Window::create_ptr(50, 50, 800, 600);
	//eve::sys::MessagePump * pump = eve::sys::MessagePump::create_ptr(win->getHandle());

	//while (true);

	//EVE_RELEASE_PTR(win);

	return 0;
}
