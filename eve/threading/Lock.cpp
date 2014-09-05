
// Main header
#include "threading/Lock.h"

#include <windows.h>


//=============================================================================================
namespace eve
{
	namespace threading
	{
		namespace detail
		{
			class Lock
			{
			public:
				CRITICAL_SECTION cs;
				bool m_bIsLocked;


				Lock(void)
					: m_bIsLocked(false)
				{}

			}; // class Lock

		} // namespace detail
	} // namespace threading
} // namespace eve



//=============================================================================================
eve::threading::Lock::Lock(void)
	: p_pImpl ( new detail::Lock )
{
	memset(&p_pImpl->cs, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection( &p_pImpl->cs );
}
	
//=============================================================================================
eve::threading::Lock::~Lock(void)
{
	DeleteCriticalSection( &p_pImpl->cs ); 
	delete p_pImpl;
}


	
//=============================================================================================
void eve::threading::Lock::set(void)
{
	EnterCriticalSection( &p_pImpl->cs );

	p_pImpl->m_bIsLocked = true;
}
	
//=============================================================================================
void eve::threading::Lock::unset(void)
{
	LeaveCriticalSection( &p_pImpl->cs );
        
	p_pImpl->m_bIsLocked = false;
}
	
//=============================================================================================
bool eve::threading::Lock::trySet(void)
{

	return (TryEnterCriticalSection( &p_pImpl->cs )?TRUE: true, false);

}
	
//=============================================================================================
bool eve::threading::Lock::isSet(void)
{
	bool bret = true;

	if( trySet( ))
	{
		unset();
		bret = false;
	}

	return bret;
}
