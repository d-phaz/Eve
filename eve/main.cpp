
#ifndef __EVE_CORE_INCLUDES_H__
#include "core/Includes.h"
#endif


int main(int argc, char **argv)
{
	// Hide console window in release mode.
#if defined(EVE_OS_WIN) && defined(NDEBUG)
	:ShowWindow( ::GetConsoleWindow(), SW_HIDE );
#endif

	
	return 0;
}
