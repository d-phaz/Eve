
// Main header
#include "threading/Mutex.h"

#include <Windows.h>


//=============================================================================================
eve::threading::Mutex::Mutex(void)
{
	m_mutex = CreateMutexW(NULL, false, NULL);
}

//=============================================================================================
eve::threading::Mutex::~Mutex(void)
{
	CloseHandle(m_mutex);
}



//=============================================================================================
void eve::threading::Mutex::lock(void)
{
	WaitForSingleObject(m_mutex, INFINITE);
}

//=============================================================================================
void eve::threading::Mutex::unlock(void)
{
	ReleaseMutex(m_mutex);
}
