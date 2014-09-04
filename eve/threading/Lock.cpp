
#include "Native_Lock.h"

#include <string.h>


#include <windows.h>


namespace NativeT
{
	//=============================================================================================
	namespace detail
	{
		class Lock
		{
		public:
			CRITICAL_SECTION cs; 
			bool m_bIsLocked;


			Lock( void )
				: m_bIsLocked	( false )
			{}
		};
	} // namespace detail


	//=============================================================================================
	Lock::Lock( void )
		: p_pImpl ( new detail::Lock )
	{

		memset(&p_pImpl->cs, 0, sizeof(CRITICAL_SECTION));
		InitializeCriticalSection( &p_pImpl->cs );

	}
	
	//=============================================================================================
	Lock::~Lock( void )
	{

		DeleteCriticalSection( &p_pImpl->cs ); 

		delete p_pImpl;
	}


	
	//=============================================================================================
	void Lock::set( void )
	{
		EnterCriticalSection( &p_pImpl->cs );

		p_pImpl->m_bIsLocked = true;
	}
	
	//=============================================================================================
	void Lock::unset( void )
	{
		LeaveCriticalSection( &p_pImpl->cs );
        
		p_pImpl->m_bIsLocked = false;
	}
	
	//=============================================================================================
	bool Lock::trySet( void )
	{

		return (TryEnterCriticalSection( &p_pImpl->cs )?TRUE: true, false);

	}
	
	//=============================================================================================
	bool Lock::isSet( void )
	{
		if( trySet( ))
		{
			unset();
			return false;
		}
		return true;
	}

} //namespace NativeT
