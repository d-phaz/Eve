
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

#include "eve/app/App.h"
#include "eve/sys/Includes.h"


class Example final
	: public eve::sys::View
{
	friend class eve::mem::Pointer;

	EVE_DISABLE_COPY(Example);
	EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Example);

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;

};

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	switch (p_args.button)
	{
	case eve::sys::btn_Left: 
		eve::sys::notify_prompt_user(EVE_TXT("Notification Example"), EVE_TXT("Launch notification example?")); 
		break;

	case eve::sys::btn_Middle:
		eve::sys::notify_warning(EVE_TXT("Warning"), EVE_TXT("Be careful this is a WARNING!!!"));
		break;

	case eve::sys::btn_Right:
		eve::sys::notify_error(EVE_TXT("Error"), EVE_TXT("Woups an ERROR occurred."));
		break;

	case eve::sys::btn_X:
		eve::sys::notify_fatal_error(EVE_TXT("Fatal error occurred, exiting application."));
		break;
	}
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	if (p_args.key == eve::sys::key_Escape)
	{
		eve::evt::notify_application_exit();
	}
}

// Launch application for view "Example".
EVE_APPLICATION(Example);
