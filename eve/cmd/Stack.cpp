
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
#include "eve/cmd/Stack.h"


//=================================================================================================
eve::cmd::CommandStack::CommandStack(void)
	// Inheritance.
	: eve::mem::Pointer()
	// Members init.
	, _cursor(-1)
	, _p_commands(nullptr)
	, _max_size(40)
{}



//=================================================================================================
void eve::cmd::CommandStack::init(void)
{
	_p_commands = new std::list<Command*>();
}

//=================================================================================================
void eve::cmd::CommandStack::release(void)
{
	eve::cmd::Command * tmp = nullptr;
	while (!_p_commands->empty())
	{
		tmp = _p_commands->back();
		_p_commands->pop_back();
		EVE_RELEASE_PTR(tmp);
	}
	EVE_RELEASE_PTR_CPP(_p_commands);
}



//=================================================================================================
void eve::cmd::CommandStack::add(eve::evt::CallbackAuto * p_undo, eve::evt::CallbackAuto * p_redo)
{
	eve::cmd::Command * cmd = nullptr;
	if (_p_commands->size() > _max_size - 1)
	{
		cmd = _p_commands->front();
		_p_commands->pop_front();
		EVE_RELEASE_PTR(cmd);
	}

	// TODO:
	// insert after cursor position
	// remove after inserted contained commands
	cmd = new eve::cmd::Command();
	cmd->init(p_undo, p_redo);
	_p_commands->push_back(cmd);
 
	_cursor = _p_commands->size() - 1;
}



//=================================================================================================
void eve::cmd::CommandStack::undo(void)
{

}

//=================================================================================================
void eve::cmd::CommandStack::redo(void)
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::cmd::CommandStack::set_max_size(uint32_t p_size)
{
	if (p_size < _max_size)
	{
		eve::cmd::Command * tmp = nullptr;
		while (_p_commands->size() > p_size)
		{
			tmp = _p_commands->front();
			_p_commands->pop_front();
			EVE_RELEASE_PTR(tmp);
		}
	}
	_max_size = p_size;
}
