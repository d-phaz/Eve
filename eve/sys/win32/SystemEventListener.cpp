
// Main header
#include "SystemEventListener.h"

// Thread header
#ifndef __NATIVE_MUTEX_H__
#include "Native_Mutex.h"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//		SystemEventListener class
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
SystemEventListener * SystemEventListener::create_ptr( void )
{
	SystemEventListener * Ptr_Return = new SystemEventListener();

	Ptr_Return->init();

	return Ptr_Return;
}



//=================================================================================================
SystemEventListener::SystemEventListener( void )

	// Members init
    : m_dequeFirst			( NULL )
	, m_dequeSecond			( NULL )
	, m_dequeFront			( NULL )
    , m_dequeBack			( NULL )

    , m_pMutex				( NULL )

    , m_bSwapped			( false )
{}

//=================================================================================================
SystemEventListener::~SystemEventListener( void )
{
	if( m_dequeFirst != NULL )
	{
		m_dequeFirst->clear();
		delete m_dequeFirst;
		m_dequeFirst = NULL;
	}

	if( m_dequeSecond != NULL )
	{
		m_dequeSecond->clear();
		delete m_dequeSecond;
		m_dequeSecond = NULL;
	}


	if( m_pMutex != NULL )
	{
		delete m_pMutex;
		m_pMutex = NULL;
	}


	// Do not delete -> shared pointers
	m_dequeFront = NULL;
	m_dequeBack = NULL;
}



//=================================================================================================
void SystemEventListener::init( void )
{
	// Deques
	m_dequeFirst = new std::deque<evt::Event>();
	m_dequeSecond = new std::deque<evt::Event>();

	m_dequeFront = m_dequeFirst;
	m_dequeBack = m_dequeSecond;

	// Mutex
	m_pMutex = new NativeT::Mutex();
}



//=================================================================================================
void SystemEventListener::eventSwap( void )
{
	m_pMutex->Lock();

	if( m_bSwapped )
	{
		m_dequeFront = m_dequeFirst;
		m_dequeBack = m_dequeSecond;

		m_bSwapped = false;
	}
	else
	{
		m_dequeFront = m_dequeSecond;
		m_dequeBack = m_dequeFirst;

		m_bSwapped = true;
	}

	m_pMutex->Unlock();
}



//=================================================================================================
void SystemEventListener::eventPushBack( evt::Event p_event )
{
	m_dequeBack->push_back( p_event );
}

//=================================================================================================
evt::Event SystemEventListener::eventGet( void )
{
	evt::Event Evt_Return = m_dequeFront->front();
	m_dequeFront->pop_front();

	return Evt_Return;
}

//=================================================================================================
bool SystemEventListener::eventEmpty( void )
{
	return m_dequeFront->empty();
}
