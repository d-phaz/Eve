
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

// Main header
#include "eve/cmd/Command.h"


//=================================================================================================
eve::cmd::Command::Command(void)
	: _cb_undo(nullptr)
	, _cb_redo(nullptr)
{}

//=================================================================================================
eve::cmd::Command::~Command(void)
{}

//=================================================================================================
void eve::cmd::Command::init(eve::evt::CallbackAuto * p_undo, eve::evt::CallbackAuto * p_redo)
{
	EVE_ASSERT(p_undo);
	EVE_ASSERT(p_redo);
	_cb_undo = p_undo;
	_cb_redo = p_redo;
}

//=================================================================================================
void eve::cmd::Command::release(void)
{
	delete _cb_undo;
	delete _cb_redo;
}

//=================================================================================================
void eve::cmd::Command::undo(void) { _cb_undo->execute(); }
void eve::cmd::Command::redo(void) { _cb_redo->execute(); }
