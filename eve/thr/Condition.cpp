
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

//  Main header
#include "eve/thr/Condition.h"


//=================================================================================================
eve::thr::Condition::Condition(void)
	
	// Inheritance
	: eve::thr::Mutex()
	
	// Members init
	, m_isValid(true)
	, m_conditionnedVar(0)
{}



//=================================================================================================
void eve::thr::Condition::init(void)
{
	// Call parent class
	eve::thr::Mutex::init();

	// set all conditions to be broadcast
	// unfortunately in Win32 you have to know at creation
	// whether the signal is broadcast or not.
	m_condition = ::CreateEventW(NULL, true, false, NULL);
}

//=================================================================================================
void eve::thr::Condition::release(void)
{
	::CloseHandle(m_condition);

	// Call parent class
	eve::thr::Mutex::release();
}



//=================================================================================================
void eve::thr::Condition::wait(void)
{
	::SignalObjectAndWait(m_mutex, m_condition, INFINITE, false);
	::WaitForSingleObject(m_mutex, INFINITE);
}

//=================================================================================================
void eve::thr::Condition::timedWait(time_t p_inSeconds)
{
	::SignalObjectAndWait(m_mutex, m_condition, (DWORD)(p_inSeconds * 1000), false);
	::WaitForSingleObject(m_mutex, INFINITE);
}

//=================================================================================================
void eve::thr::Condition::timedWaitMili(time_t p_inMiliSeconds)
{
	::SignalObjectAndWait(m_mutex, m_condition, (DWORD)(p_inMiliSeconds), false);
	::WaitForSingleObject(m_mutex, INFINITE);
}



//=================================================================================================
bool eve::thr::Condition::waitAndRetain(int32_t p_value)
{
	lock();

	while (m_conditionnedVar != p_value && m_isValid)
	{
		unlock();
		::WaitForSingleObject(m_condition, INFINITE);
		lock();
	}

	bool B_Return = false;
	if (m_isValid) {
		B_Return = true;
	}
	else {
		unlock();
	}

	return B_Return;
}

//=================================================================================================
bool eve::thr::Condition::waitAndLock(int32_t p_awaitedValue, bool p_autorelease)
{
	bool B_Return = this->waitAndRetain(p_awaitedValue);

	if (p_autorelease) {
		this->release(p_awaitedValue);
	}

	return B_Return;
}



//=================================================================================================
void eve::thr::Condition::signal(void)
{
	::PulseEvent(m_condition);
}

//=================================================================================================
void eve::thr::Condition::broadcast(void)
{
	::PulseEvent(m_condition);
}



//=================================================================================================
void eve::thr::Condition::release(int32_t p_value)
{
	m_conditionnedVar = p_value;
	unlock();
	this->signal();
}



//=================================================================================================
int32_t eve::thr::Condition::operator=(int32_t p_value)
{
	this->setValue(p_value);
	return p_value;
}



//=================================================================================================
void eve::thr::Condition::invalidate(void)
{
	if (m_isValid)
	{
		m_isValid = false;
		this->signal();
	}
}


//=================================================================================================
void eve::thr::Condition::restore(void)
{
	if( !m_isValid ) 
	{
		m_isValid = true;
	}
}



//=================================================================================================
void eve::thr::Condition::setValue(int32_t p_value)
{
	lock();
	m_conditionnedVar = p_value;
	unlock();

	this->signal();
}
