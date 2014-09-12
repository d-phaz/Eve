
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef __EVE_EVT_TDELEGATE_H__
#define __EVE_EVT_TDELEGATE_H__


#ifndef __EVE_EVT_TDELEGATE_ABSTRACT_H__
#include "eve/evt/TDelegateAbstract.h"
#endif

#ifndef __EVE_THREADING_SCOPED_FENCE_H__
#include "eve/threading/ScopedFence.h"
#endif

#ifndef __EVE_THREADING_SPIN_LOCK_H__
#include "eve/threading/SpinLock.h"
#endif 

namespace eve
{
	namespace evt
	{
		/** 
		* \class eve::evt::TDelegate
		* \brief Fast thread safe delegate calling receiver object dedicated method using sender and template arguments.
		* \note extends eve::evt::TDelegateAbstract<>
		*/
		template <class TObj, class TArgs, bool useSender = true>
		class TDelegate 
			: public eve::evt::TDelegateAbstract<TArgs>
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef void (TObj::*NotifyMethod)(const void*, TArgs&);


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TObj*						m_pReceiverObject;
			NotifyMethod				m_receiverMethod;
			eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			/** \brief Default class constructor. (private) */
			TDelegate(void);

		public:
			/** \brief Class constructor. */
			TDelegate(TObj* obj, NotifyMethod method, int32_t prio);
			/** \brief Default class copy constructor. All members are copied except fence.*/
			TDelegate(const TDelegate& p_other);
			/** \brief Assignation operator. Copy all members except fence.*/
			TDelegate& operator = (const TDelegate& p_other);
			/** \brief Class destructor. */
			virtual ~TDelegate(void);


		public:
			/**
			* \brief Invokes the delegate's callback function. (pure virtual)
			* Returns true if successful, or false if the delegate has been disabled or has expired.
			*/
			virtual bool notify(const void* sender, TArgs& arguments) override;

			/** \brief Compares the AbstractDelegate with the other one for equality. (pure virtual) */
			virtual bool equals(const eve::evt::TDelegateAbstract<TArgs>& p_other) const override;

			/** \brief Returns a deep copy of the AbstractDelegate. (pure virtual) */
			virtual eve::evt::TDelegateAbstract<TArgs>* clone(void) const override;

			/** \brief Disables the delegate, which is done prior to removal. (pure virtual) */
			virtual void disable(void) override;

		}; // class TDelegate


		/**
		* \class eve::evt::TDelegate (specialized)
		* \brief Fast thread safe delegate calling receiver object dedicated method using template argument.
		* \note extends eve::evt::TDelegateAbstract<>
		*/
		template <class TObj, class TArgs>
		class TDelegate<TObj, TArgs, false> 
			: public eve::evt::TDelegateAbstract<TArgs>
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef void (TObj::*NotifyMethod)(TArgs&);


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TObj*						m_pReceiverObject;
			NotifyMethod				m_receiverMethod;
			eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			/** \brief Default class constructor. (private) */
			TDelegate(void);

		public:
			/** \brief Class constructor. */
			TDelegate(TObj* obj, NotifyMethod method, int32_t prio);
			/** \brief Default class copy constructor. All members are copied except fence.*/
			TDelegate(const TDelegate& p_other);
			/** \brief Assignation operator. Copy all members except fence.*/
			TDelegate& operator = (const TDelegate& p_other);
			/** \brief Class destructor. */
			virtual ~TDelegate(void);


		public:
			/**
			* \brief Invokes the delegate's callback function. (pure virtual)
			* Returns true if successful, or false if the delegate has been disabled or has expired.
			*/
			virtual bool notify(const void* sender, TArgs& arguments) override;

			/** \brief Compares the AbstractDelegate with the other one for equality. (pure virtual) */
			virtual bool equals(const eve::evt::TDelegateAbstract<TArgs>& p_other) const override;

			/** \brief Returns a deep copy of the AbstractDelegate. (pure virtual) */
			virtual eve::evt::TDelegateAbstract<TArgs>* clone(void) const override;

			/** \brief Disables the delegate, which is done prior to removal. (pure virtual) */
			virtual void disable(void) override;

		}; // class TDelegate


		/**
		* \class eve::evt::TDelegate (specialized)
		* \brief Fast thread safe delegate calling receiver object dedicated method using sender argument.
		* \note extends eve::evt::TDelegateAbstract<>
		*/
		template <class TObj>
		class TDelegate<TObj, void, true> 
			: public eve::evt::TDelegateAbstract<void>
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef void (TObj::*NotifyMethod)(const void*);


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TObj*						m_pReceiverObject;
			NotifyMethod				m_receiverMethod;
			eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			/** \brief Default class constructor. (private) */
			TDelegate(void);

		public:
			/** \brief Class constructor. */
			TDelegate(TObj* obj, NotifyMethod method, int32_t prio);
			/** \brief Default class copy constructor. All members are copied except fence.*/
			TDelegate(const TDelegate& p_other);
			/** \brief Assignation operator. Copy all members except fence.*/
			TDelegate& operator = (const TDelegate& p_other);
			/** \brief Class destructor. */
			virtual ~TDelegate(void);


		public:
			/**
			* \brief Invokes the delegate's callback function. (pure virtual)
			* Returns true if successful, or false if the delegate has been disabled or has expired.
			*/
			virtual bool notify(const void* sender) override;

			/** \brief Compares the AbstractDelegate with the other one for equality. (pure virtual) */
			virtual bool equals(const eve::evt::TDelegateAbstract<void>& p_other) const override;

			/** \brief Returns a deep copy of the AbstractDelegate. (pure virtual) */
			virtual eve::evt::TDelegateAbstract<void>* clone(void) const override;

			/** \brief Disables the delegate, which is done prior to removal. (pure virtual) */
			virtual void disable(void) override;

		}; // class TDelegate


		/**
		* \class eve::evt::TDelegate (specialized)
		* \brief Fast thread safe delegate calling receiver object dedicated method using no argument.
		* \note extends eve::evt::TDelegateAbstract<>
		*/
		template <class TObj>
		class TDelegate<TObj, void, false> 
			: public eve::evt::TDelegateAbstract<void>
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef void (TObj::*NotifyMethod)(void);


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TObj*						m_pReceiverObject;
			NotifyMethod				m_receiverMethod;
			eve::threading::SpinLock *	m_pFence;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		private:
			/** \brief Default class constructor. (private) */
			TDelegate(void);

		public:
			/** \brief Class constructor. */
			TDelegate(TObj* obj, NotifyMethod method, int32_t prio);
			/** \brief Default class copy constructor. All members are copied except fence.*/
			TDelegate(const TDelegate& p_other);
			/** \brief Assignation operator. Copy all members except fence.*/
			TDelegate& operator = (const TDelegate& p_other);
			/** \brief Class destructor. */
			virtual ~TDelegate(void);


		public:
			/**
			* \brief Invokes the delegate's callback function. (pure virtual)
			* Returns true if successful, or false if the delegate has been disabled or has expired.
			*/
			virtual bool notify(const void* sender) override;

			/** \brief Compares the AbstractDelegate with the other one for equality. (pure virtual) */
			virtual bool equals(const eve::evt::TDelegateAbstract<void>& p_other) const override;

			/** \brief Returns a deep copy of the AbstractDelegate. (pure virtual) */
			virtual eve::evt::TDelegateAbstract<void>* clone(void) const override;

			/** \brief Disables the delegate, which is done prior to removal. (pure virtual) */
			virtual void disable(void) override;

		}; // class TDelegate


		template <class TObj, class TArgs>
		static TDelegate<TObj, TArgs, true> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int32_t prio)
		{
			return TDelegate<TObj, TArgs, true>(pObj, NotifyMethod, prio);
		}


		template <class TObj, class TArgs>
		static TDelegate<TObj, TArgs, false> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int32_t prio)
		{
			return TDelegate<TObj, TArgs, false>(pObj, NotifyMethod, prio);
		}


		template <class TObj>
		static TDelegate<TObj, void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*), int32_t prio)
		{
			return TDelegate<TObj, void>(pObj, NotifyMethod, prio);
		}


		template <class TObj>
		static TDelegate<TObj, void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(), int32_t prio)
		{
			return TDelegate<TObj, void>(pObj, NotifyMethod, prio);
		}

	} // namespace evt

} // namespace eve

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(void)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(TObj* obj, NotifyMethod method, int32_t prio)
	// Inheritance
	: eve::evt::TDelegateAbstract<TArgs>(prio)
	// Members init
	, m_pReceiverObject(obj)
	, m_receiverMethod(method)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);	
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(const TDelegate<TObj, TArgs, useSender> & p_other)
	// Inheritance
	: eve::evt::TDelegateAbstract<TArgs>(p_other)
	// Members init
	, m_pReceiverObject(p_other.m_pReceiverObject),
	, m_receiverMethod(p_other.m_receiverMethod)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender> & eve::evt::TDelegate<TObj, TArgs, useSender>::operator = (const eve::evt::TDelegate<TObj, TArgs, useSender> & p_other)
{
	if (&p_other != this)
	{
		this->m_pReceiverObject	= p_other.m_pReceiverObject;
		this->m_receiverMethod	= p_other.m_receiverMethod;
		this->m_priority		= p_other.m_priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::~TDelegate(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool eve::evt::TDelegate<TObj, TArgs, useSender>::notify(const void* sender, TArgs& arguments)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	if (m_pReceiverObject)
	{
		(m_pReceiverObject->*m_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool eve::evt::TDelegate<TObj, TArgs, useSender>::equals(const eve::evt::TDelegateAbstract<TArgs>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && m_pReceiverObject == pOtherDelegate->m_pReceiverObject && m_receiverMethod == pOtherDelegate->m_receiverMethod;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegateAbstract<TArgs>* eve::evt::TDelegate<TObj, TArgs, useSender>::clone(void) const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
void eve::evt::TDelegate<TObj, TArgs, useSender>::disable(void)
{
	m_pFence->lock();
	m_pReceiverObject = 0;
	m_pFence->unlock();
}


//-----------------------------------------------


//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(void)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(TObj* obj, NotifyMethod method, int32_t prio)
	// Inheritance
	: eve::evt::TDelegateAbstract<TArgs>(prio)
	// Members init
	, m_pReceiverObject(obj)
	, m_receiverMethod(method)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(const TDelegate<TObj, TArgs, false> & p_other)
	// Inheritance
	: eve::evt::TDelegateAbstract<TArgs>(p_other)
	// Members init
	, m_pReceiverObject(p_other.m_pReceiverObject)
	, m_receiverMethod(p_other.m_receiverMethod)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false> & eve::evt::TDelegate<TObj, TArgs, false>::operator = (const eve::evt::TDelegate<TObj, TArgs, false> & p_other)
{
	if (&p_other != this)
	{
		this->m_pReceiverObject	= p_other.m_pReceiverObject;
		this->m_receiverMethod	= p_other.m_receiverMethod;
		this->m_priority		= p_other.m_priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::~TDelegate(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TObj, class TArgs>
bool eve::evt::TDelegate<TObj, TArgs, false>::notify(const void* sender, TArgs& arguments)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	if (m_pReceiverObject)
	{
		(m_pReceiverObject->*m_receiverMethod)(arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj, class TArgs>
bool eve::evt::TDelegate<TObj, TArgs, false>::equals(const eve::evt::TDelegateAbstract<TArgs>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && m_pReceiverObject == pOtherDelegate->m_pReceiverObject && m_receiverMethod == pOtherDelegate->m_receiverMethod;
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegateAbstract<TArgs>* eve::evt::TDelegate<TObj, TArgs, false>::clone(void) const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj, class TArgs>
void eve::evt::TDelegate<TObj, TArgs, false>::disable(void)
{
	m_pFence->lock();
	m_pReceiverObject = 0;
	m_pFence->unlock();
}


//-----------------------------------------------


//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(void)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(TObj* obj, NotifyMethod method, int32_t prio)
	// Inheritance
	: eve::evt::TDelegateAbstract<void>(prio)
	// Members init
	, m_pReceiverObject(obj)
	, m_receiverMethod(method)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(const TDelegate<TObj, void, true> & p_other)
	// Inheritance
	: eve::evt::TDelegateAbstract<void>(p_other)
	// Members init
	, m_pReceiverObject(p_other.m_pReceiverObject),
	, m_receiverMethod(p_other.m_receiverMethod)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true> & eve::evt::TDelegate<TObj, void, true>::operator = (const eve::evt::TDelegate<TObj, void, true> & p_other)
{
	if (&p_other != this)
	{
		this->m_pReceiverObject = p_other.m_pReceiverObject;
		this->m_receiverMethod	= p_other.m_receiverMethod;
		this->m_priority		= p_other.m_priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::~TDelegate(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, true>::notify(const void* sender)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	if (m_pReceiverObject)
	{
		(m_pReceiverObject->*m_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, true>::equals(const eve::evt::TDelegateAbstract<void>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && m_pReceiverObject == pOtherDelegate->m_pReceiverObject && m_receiverMethod == pOtherDelegate->m_receiverMethod;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegateAbstract<void>* eve::evt::TDelegate<TObj, void, true>::clone(void) const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj>
void eve::evt::TDelegate<TObj, void, true>::disable(void)
{
	m_pFence->lock();
	m_pReceiverObject = 0;
	m_pFence->unlock();
}


//-----------------------------------------------


//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(void)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(TObj* obj, NotifyMethod method, int32_t prio)
	// Inheritance
	: eve::evt::TDelegateAbstract<void>(prio)
	// Members init
	, m_pReceiverObject(obj)
	, m_receiverMethod(method)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(const TDelegate<TObj, void, false> & p_other)
	// Inheritance
	: eve::evt::TDelegateAbstract<void>(p_other)
	// Members init
	, m_pReceiverObject(p_other.m_pReceiverObject),
	, m_receiverMethod(p_other.m_receiverMethod)
{
	m_pFence = EVE_CREATE_PTR(eve::threading::SpinLock);
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false> & eve::evt::TDelegate<TObj, void, false>::operator = (const eve::evt::TDelegate<TObj, void, false> & p_other)
{
	if (&p_other != this)
	{
		this->m_pReceiverObject = p_other.m_pReceiverObject;
		this->m_receiverMethod	= p_other.m_receiverMethod;
		this->m_priority		= p_other.m_priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::~TDelegate(void)
{
	EVE_RELEASE_PTR(m_pFence);
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, false>::notify(const void* sender)
{
	eve::threading::ScopedFence<eve::threading::SpinLock> lock(m_pFence);
	if (m_pReceiverObject)
	{
		(m_pReceiverObject->*m_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, false>::equals(const eve::evt::TDelegateAbstract<void>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && m_pReceiverObject == pOtherDelegate->m_pReceiverObject && m_receiverMethod == pOtherDelegate->m_receiverMethod;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegateAbstract<void>* eve::evt::TDelegate<TObj, void, false>::clone(void) const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj>
void eve::evt::TDelegate<TObj, void, false>::disable(void)
{
	m_pFence->lock();
	m_pReceiverObject = 0;
	m_pFence->unlock();
}

#endif // __EVE_EVT_TDELEGATE_H__
