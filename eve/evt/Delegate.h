
#pragma once
#ifndef __EVT_DELEGATE_H__ 
#define __EVT_DELEGATE_H__

// External header
#include <cstdint>

// POCO header
#include "Poco/AbstractPriorityDelegate.h"


// Native header
#ifndef __NATIVE_GLOBAL_MACRO_H__
#include "Native_GlobalMacro.h"
#endif


namespace evt
{

	template <class TObj, class TArgs, bool useSender=true>
	class Delegate
		: public Poco::AbstractPriorityDelegate<TArgs>
	{

	public:
		typedef bool (TObj::*NotifyMethod)(const void*, TArgs&);

	protected:
		TObj *			_receiverObject;
		NotifyMethod	_receiverMethod;
		Poco::Mutex		_mutex;

	private:
		Delegate( void );

	public:
		Delegate( TObj* obj, NotifyMethod method, int32_t prio );

		Delegate( const Delegate & p_delegate );

		Delegate& operator = ( const Delegate & p_delegate );

		~Delegate( void );

		bool notify( const void * sender, TArgs & arguments );

		bool equals( const Poco::AbstractDelegate<TArgs> & other ) const;

		Poco::AbstractDelegate<TArgs>* clone( void ) const;

		void disable( void );
	};



	template <class TObj, class TArgs>
	class Delegate<TObj, TArgs, false>
		: public Poco::AbstractPriorityDelegate<TArgs>
	{

	public:
		typedef bool (TObj::*NotifyMethod)(TArgs&);

	protected:
		TObj*        _receiverObject;
		NotifyMethod _receiverMethod;
		Poco::Mutex _mutex;

	private:
		Delegate( void );

	public:
		Delegate( TObj* obj, NotifyMethod method, int32_t prio );

		Delegate( const Delegate & p_delegate );

		Delegate& operator = ( const Delegate & p_delegate );

		~Delegate( void );

		bool notify( const void * sender, TArgs & arguments );

		bool equals( const Poco::AbstractDelegate<TArgs> & other ) const;

		Poco::AbstractDelegate<TArgs>* clone( void ) const;

		void disable( void );
	};



	template <class TObj>
	class Delegate<TObj, void, true>
		: public Poco::AbstractPriorityDelegate<void>
	{

	public:
		typedef bool (TObj::*NotifyMethod)(const void*);

	protected:
		TObj *			_receiverObject;
		NotifyMethod	_receiverMethod;
		Poco::Mutex		_mutex;

	private:
		Delegate( void );

	public:
		Delegate( TObj* obj, NotifyMethod method, int32_t prio );

		Delegate( const Delegate & p_delegate );

		Delegate& operator = ( const Delegate & p_delegate );

		~Delegate(void );

		bool notify( const void * sender );

		bool equals( const Poco::AbstractDelegate<void> & other ) const;

		Poco::AbstractDelegate<void>* clone( void ) const;

		void disable( void );
	};



	template <class TObj>
	class Delegate<TObj, void, false>
		: public Poco::AbstractPriorityDelegate<void>
	{

	public:
		typedef void (TObj::*NotifyMethod)();

	protected:
		TObj *			_receiverObject;
		NotifyMethod	_receiverMethod;
		Poco::Mutex		_mutex;

	private:
		Delegate( void );

	public:
		Delegate( TObj* obj, NotifyMethod method, int32_t prio );

		Delegate( const Delegate & p_delegate );

		Delegate& operator = ( const Delegate & p_delegate );

		~Delegate( void );

		bool notify( const void * sender );

		bool equals( const Poco::AbstractDelegate<void> & other ) const;

		Poco::AbstractDelegate<void> * clone( void ) const;

		void disable( void );
	};

} // namespace evt



//=================================================================================================
template <class TObj, class TArgs, bool useSender>
evt::Delegate<TObj, TArgs, useSender>::Delegate( void )
	: Poco::AbstractPriorityDelegate<TArgs>()
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
evt::Delegate<TObj, TArgs, useSender>::Delegate( TObj* obj, NotifyMethod method, int32_t prio )
	: Poco::AbstractPriorityDelegate<TArgs>(prio)

	, _receiverObject(obj)
	, _receiverMethod(method)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
evt::Delegate<TObj, TArgs, useSender>::Delegate( const evt::Delegate<TObj, TArgs, useSender> & p_delegate )
	: Poco::AbstractPriorityDelegate<TArgs>(p_delegate)

	, _receiverObject(p_delegate._receiverObject)
	, _receiverMethod(p_delegate._receiverMethod)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
evt::Delegate<TObj, TArgs, useSender> & evt::Delegate<TObj, TArgs, useSender>::operator=( const evt::Delegate<TObj, TArgs, useSender> & p_delegate )
{
	if (&p_delegate != this)
	{
		this->_pTarget        = p_delegate._pTarget;
		this->_receiverObject = p_delegate._receiverObject;
		this->_receiverMethod = p_delegate._receiverMethod;
		this->_priority       = p_delegate._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
evt::Delegate<TObj, TArgs, useSender>::~Delegate( void )
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool evt::Delegate<TObj, TArgs, useSender>::notify( const void * sender, TArgs & arguments )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		if(	!(_receiverObject->*_receiverMethod)(sender, arguments) ) 
		{
			return true;
		}
#ifndef NDEBUG
		else {
			// Receiver class does not hold the target event method !!!
			NATIVE_ASSERT( 0 );
		}
#endif
	}

	return false;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool evt::Delegate<TObj, TArgs, useSender>::equals( const Poco::AbstractDelegate<TArgs> & other ) const
{
	const evt::Delegate* pOtherDelegate = dynamic_cast<const evt::Delegate*>( other.unwrap() );
	return ( pOtherDelegate 
		&& this->priority() == pOtherDelegate->priority() 
		&& _receiverObject == pOtherDelegate->_receiverObject 
		&& _receiverMethod == pOtherDelegate->_receiverMethod );
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
Poco::AbstractDelegate<TArgs>* evt::Delegate<TObj, TArgs, useSender>::clone( void ) const
{
	return new evt::Delegate<TObj, TArgs, useSender>(*this);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
void evt::Delegate<TObj, TArgs, useSender>::disable( void )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}





//=================================================================================================
template <class TObj, class TArgs>
evt::Delegate<TObj, TArgs, false>::Delegate( void )
	: Poco::AbstractPriorityDelegate<TArgs>()
{}

//=================================================================================================
template <class TObj, class TArgs>
evt::Delegate<TObj, TArgs, false>::Delegate( TObj* obj, NotifyMethod method, int32_t prio )
	: Poco::AbstractPriorityDelegate<TArgs>(prio)

	, _receiverObject		( obj )
	, _receiverMethod		( method )
{}

//=================================================================================================
template <class TObj, class TArgs>
evt::Delegate<TObj, TArgs, false>::Delegate( const evt::Delegate<TObj, TArgs, false> & p_delegate )
	: Poco::AbstractPriorityDelegate<TArgs>( p_delegate )

	, _receiverObject(p_delegate._receiverObject)
	, _receiverMethod(p_delegate._receiverMethod)
{}

//=================================================================================================
template <class TObj, class TArgs>
evt::Delegate<TObj, TArgs, false> & evt::Delegate<TObj, TArgs, false>::operator=( const evt::Delegate<TObj, TArgs, false> & p_delegate )
{
	if (&p_delegate != this)
	{
		this->_pTarget        = p_delegate._pTarget;
		this->_receiverObject = p_delegate._receiverObject;
		this->_receiverMethod = p_delegate._receiverMethod;
		this->_priority       = p_delegate._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs>
evt::Delegate<TObj, TArgs, false>::~Delegate( void )
{}

//=================================================================================================
template <class TObj, class TArgs>
bool evt::Delegate<TObj, TArgs, false>::notify( const void * sender, TArgs & arguments )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		if(	!(_receiverObject->*_receiverMethod)(arguments) )
		{
			return true;
		}
#ifndef NDEBUG
		else {
			// Receiver class does not hold the target event method !!!
			NATIVE_ASSERT( 0 );
		}
#endif
	}

	return false;
}

//=================================================================================================
template <class TObj, class TArgs>
bool evt::Delegate<TObj, TArgs, false>::equals( const Poco::AbstractDelegate<TArgs> & other ) const
{
	const evt::Delegate* pOtherDelegate = dynamic_cast<const evt::Delegate*>( other.unwrap() );
	return ( pOtherDelegate 
		&& this->priority() == pOtherDelegate->priority() 
		&& _receiverObject == pOtherDelegate->_receiverObject 
		&& _receiverMethod == pOtherDelegate->_receiverMethod );
}

//=================================================================================================
template <class TObj, class TArgs>
Poco::AbstractDelegate<TArgs>* evt::Delegate<TObj, TArgs, false>::clone( void ) const
{
	return new evt::Delegate<TObj, TArgs, false>(*this);
}

//=================================================================================================
template <class TObj, class TArgs>
void evt::Delegate<TObj, TArgs, false>::disable( void )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}




//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, true>::Delegate( void )
	: Poco::AbstractPriorityDelegate<void>()
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, true>::Delegate( TObj* obj, NotifyMethod method, int32_t prio )
	: Poco::AbstractPriorityDelegate<void>( prio )

	, _receiverObject		( obj )
	, _receiverMethod		( method )
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, true>::Delegate( const evt::Delegate<TObj, void, true> & p_delegate )
	: Poco::AbstractPriorityDelegate<void>( p_delegate )

	, _receiverObject	( p_delegate._receiverObject )
	, _receiverMethod	( p_delegate._receiverMethod )
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, true> & evt::Delegate<TObj, void, true>::operator=( const evt::Delegate<TObj, void, true> & p_delegate )
{
	if (&p_delegate != this)
	{
		this->_pTarget        = p_delegate._pTarget;
		this->_receiverObject = p_delegate._receiverObject;
		this->_receiverMethod = p_delegate._receiverMethod;
		this->_priority       = p_delegate._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, true>::~Delegate(void )
{}

//=================================================================================================
template <class TObj>
bool evt::Delegate<TObj, void, true>::notify( const void * sender )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		if(	!(_receiverObject->*_receiverMethod)(sender))
		{
			return true;
		}
#ifndef NDEBUG
		else {
			// Receiver class does not hold the target event method !!!
			NATIVE_ASSERT( 0 );
		}
#endif
	}

	return false;
}

//=================================================================================================
template <class TObj>
bool evt::Delegate<TObj, void, true>::equals( const Poco::AbstractDelegate<void> & other ) const
{
	const evt::Delegate* pOtherDelegate = dynamic_cast<const evt::Delegate*>( other.unwrap() );
	return ( pOtherDelegate 
		&& this->priority() == pOtherDelegate->priority() 
		&& _receiverObject == pOtherDelegate->_receiverObject 
		&& _receiverMethod == pOtherDelegate->_receiverMethod );
}

//=================================================================================================
template <class TObj>
Poco::AbstractDelegate<void>* evt::Delegate<TObj, void, true>::clone( void ) const
{
	return new evt::Delegate<TObj, void, true>(*this);
}

//=================================================================================================
template <class TObj>
void evt::Delegate<TObj, void, true>::disable( void )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}




//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, false>::Delegate( void )
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, false>::Delegate( TObj* obj, NotifyMethod method, int32_t prio )
	: Poco::AbstractPriorityDelegate<void>( prio )

	, _receiverObject	( obj )
	, _receiverMethod	( method )
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, false>::Delegate( const evt::Delegate<TObj, void, false> & p_delegate )
	: Poco::AbstractPriorityDelegate<void>( p_delegate )

	, _receiverObject( p_delegate._receiverObject )
	, _receiverMethod( p_delegate._receiverMethod )
{}

//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, false> & evt::Delegate<TObj, void, false>::operator=( const evt::Delegate<TObj, void, false> & p_delegate )
{
	if (&p_delegate != this)
	{
		this->_pTarget        = p_delegate._pTarget;
		this->_receiverObject = p_delegate._receiverObject;
		this->_receiverMethod = p_delegate._receiverMethod;
		this->_priority       = p_delegate._priority;
	}
	return *this;
}


//=================================================================================================
template <class TObj>
evt::Delegate<TObj, void, false>::~Delegate( void )
{}


//=================================================================================================
template <class TObj>
bool evt::Delegate<TObj, void, false>::notify( const void * sender )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		if(	!(_receiverObject->*_receiverMethod)())
		{
			return true;
		}
#ifndef NDEBUG
		else {
			// Receiver class does not hold the target event method !!!
			NATIVE_ASSERT( 0 );
		}
#endif
	}
	return false;
}


//=================================================================================================
template <class TObj>
bool evt::Delegate<TObj, void, false>::equals( const Poco::AbstractDelegate<void> & other ) const
{
	const evt::Delegate<TObj, void, false>* pOtherDelegate = dynamic_cast<const evt::Delegate<TObj, void, false>*>(other.unwrap());
	return ( pOtherDelegate 
		&& this->priority() == pOtherDelegate->priority() 
		&& _receiverObject == pOtherDelegate->_receiverObject 
		&& _receiverMethod == pOtherDelegate->_receiverMethod );
}


//=================================================================================================
template <class TObj>
Poco::AbstractDelegate<void> * evt::Delegate<TObj, void, false>::clone( void ) const
{
	return new evt::Delegate<TObj, void, false>::evt::Delegate(*this);
}


//=================================================================================================
template <class TObj>
void evt::Delegate<TObj, void, false>::disable( void )
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}


#endif	// __EVT_DELEGATE_H__
