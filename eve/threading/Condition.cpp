
//  Main header
#include "threading/Condition.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		eve::threading::Condition class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::threading::Condition::Condition(int32_t p_var)
	
	// Inheritance
	: threading::Mutex()
	
	// Members init
	, m_isValid(true)
	, m_conditionnedVar(p_var)
{
	// set all conditions to be broadcast
	// unfortunately in Win32 you have to know at creation
	// whether the signal is broadcast or not.
	m_condition = CreateEventA(NULL, true, false, NULL);
}

//=================================================================================================
eve::threading::Condition::~Condition(void)
{
	CloseHandle(m_condition);
}



//=================================================================================================
void eve::threading::Condition::wait(void)
{
	SignalObjectAndWait(m_mutex, m_condition, INFINITE, false);
	WaitForSingleObject(m_mutex, INFINITE);
}

//=================================================================================================
void eve::threading::Condition::timedWait(time_t p_inSeconds)
{
	SignalObjectAndWait(m_mutex, m_condition, (DWORD)(p_inSeconds * 1000), false);
	WaitForSingleObject(m_mutex, INFINITE);
}

//=================================================================================================
void eve::threading::Condition::timedWaitMili(time_t p_inMiliSeconds)
{
	SignalObjectAndWait(m_mutex, m_condition, (DWORD)(p_inMiliSeconds), false);
	WaitForSingleObject(m_mutex, INFINITE);
}



//=================================================================================================
bool eve::threading::Condition::waitAndRetain(int32_t p_value)
{
	Lock();

	while (m_conditionnedVar != p_value && m_isValid)
	{
		Unlock();
		WaitForSingleObject(m_condition, INFINITE);
		Lock();
	}

	bool B_Return = false;
	if (m_isValid) {
		B_Return = true;
	}
	else {
		Unlock();
	}

	return B_Return;
}

//=================================================================================================
bool eve::threading::Condition::waitAndLock(int32_t p_awaitedValue, bool p_autorelease = false)
{
	bool B_Return = this->waitAndRetain(p_awaitedValue);

	if (p_autorelease) {
		this->release(p_awaitedValue);
	}

	return B_Return;
}



//=================================================================================================
void eve::threading::Condition::signal(void)
{
	PulseEvent(m_condition);
}

//=================================================================================================
void eve::threading::Condition::broadcast(void)
{
	PulseEvent(m_condition);
}



//=================================================================================================
void eve::threading::Condition::release(int32_t value)
{
	m_conditionnedVar = value;
	Unlock();
	this->Signal();
}



//=================================================================================================
int32_t eve::threading::Condition::operator=(int32_t value)
{
	this->setValue(value);
	return value;
}



//=================================================================================================
void eve::threading::Condition::invalidate(void)
{
	if (m_isValid)
	{
		m_isValid = false;
		this->signal();
	}
}


//=================================================================================================
void eve::threading::Condition::restore(void)
{
	if( !m_isValid ) 
	{
		m_isValid = true;
	}
}



//=================================================================================================
void eve::threading::Condition::setValue(int32_t value)
{
	Lock();
	m_conditionnedVar = value;
	Unlock();

	this->Signal();
}
