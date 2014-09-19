
#pragma once
#ifndef __SYSTEM_ERROR_H__
#define __SYSTEM_ERROR_H__

// External headers
#include <string>

#ifndef _WINDOWS_
	#include <windows.h>
#endif


namespace native_system
{
    std::string getErrorMsg( DWORD p_error );
    std::string getErrorMsg( void );
}

#endif // __SYSTEM_ERROR_H__
