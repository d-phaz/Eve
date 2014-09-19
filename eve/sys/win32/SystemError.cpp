
// Main header
#include "SystemError.h"

// System headers
//#include "SystemUtils.h"


//=================================================================================================
std::string native_system::getErrorMsg( void ) 
{ 
	return native_system::getErrorMsg( GetLastError() ); 
}



//=================================================================================================
std::string native_system::getErrorMsg( DWORD p_error )
{
    LPVOID msgBuf = 0;
    try
    {
        if( !FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				p_error,
				0,
				(LPSTR) &msgBuf,
				0, NULL
				) )
        {
			return "FormatMessage failed with error code: "; // + NATIVESYSTEM::numericalToString<DWORD>( GetLastError() );
        }

		std::string msg( reinterpret_cast<const char*>(msgBuf) );
        ::LocalFree( msgBuf );
        return msg;
    } 
	catch(...)
    {
        ::LocalFree( msgBuf );
        return "Can't get Win32 error message";
    }
}
