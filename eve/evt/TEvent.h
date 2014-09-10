
#pragma once
#ifndef __EVE_EVT_TEVENT_H__
#define __EVE_EVT_TEVENT_H__


#include <Poco/PriorityEvent.h>

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace evt
	{
		/**
		* \class eve::evt::TEvent
		* \brief POCO FIFO event template.
		* To create your own events use: eve::evt::TEvent<argType> myEvent
		* \note extends Poco::PriorityEvent<>
		*/
		template <class T>
		class TEvent
			: public Poco::PriorityEvent<T>
		{
		public:
			/** \brief Class constructor. */
			TEvent(void);
			/** \brief Class destructor. */
			virtual ~TEvent(void);

			/** 
			* \brief Copy constructor.
			* Allow copy of events, by copying everything except the mutex. 
			*/
			TEvent(const TEvent<T> & p_ref);

			/**
			* \brief Assignation operator.
			* Allow copy of events, by copying everything except the mutex.
			*/
			TEvent<T> & operator=(const TEvent<T> & p_ref);

		}; // class TEvent

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class T>
eve::evt::TEvent<T>::TEvent(void)
	// Inheritance
	: Poco::PriorityEvent<T>()
{}

//=================================================================================================
template <class T>
eve::evt::TEvent<T>::~TEvent(void)
{}

//=================================================================================================
template <class T>
eve::evt::TEvent<T>::TEvent(const TEvent<T> & p_ref)
	// Inheritance
	: Poco::PriorityEvent<T>()
{
	p_ref._mutex.lock();
	this->_mutex.lock();
	this->_strategy = p_ref._strategy;
	this->_mutex.unlock();
	p_ref._mutex.unlock();

	this->_enabled = p_ref._enabled;
}

//=================================================================================================
template <class T>
eve::evt::TEvent<T> & eve::evt::TEvent<T>::operator=(const TEvent<T> & p_ref)
{
	if (&p_ref != this)
	{
		p_ref._mutex.lock();
		this->_mutex.lock();
		this->_strategy = p_ref._strategy;
		this->_mutex.unlock();
		p_ref._mutex.unlock();

		this->_enabled = p_ref._enabled;
	}

	return *this;
}

#endif // __EVE_EVT_TEVENT_H__
