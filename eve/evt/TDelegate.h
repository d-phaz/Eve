
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


#include <Poco/Foundation.h>
#include <Poco/AbstractPriorityDelegate.h>
#include <Poco/PriorityExpire.h>
#include <Poco/FunctionPriorityDelegate.h>
#include <Poco/Mutex.h>

namespace eve
{
	namespace evt
	{
		template <class TObj, class TArgs, bool useSender = true>
		class TDelegate : public Poco::AbstractPriorityDelegate<TArgs>
		{

		public:
			typedef void (TObj::*NotifyMethod)(const void*, TArgs&);

		protected:
			TObj*        _receiverObject;
			NotifyMethod _receiverMethod;
			Poco::Mutex _mutex;

		private:
			TDelegate(void);

		public:
			TDelegate(TObj* obj, NotifyMethod method, int prio);

			TDelegate(const TDelegate& p_other);

			TDelegate& operator = (const TDelegate& p_other);

			virtual ~TDelegate(void);

			virtual bool notify(const void* sender, TArgs& arguments) override;

			virtual bool equals(const Poco::AbstractDelegate<TArgs>& p_other) const override;

			virtual Poco::AbstractPriorityDelegate<TArgs>* clone() const;

			virtual void disable() override;

		}; // class TDelegate



		template <class TObj, class TArgs>
		class TDelegate<TObj, TArgs, false> : public Poco::AbstractPriorityDelegate<TArgs>
		{

		public:
			typedef void (TObj::*NotifyMethod)(TArgs&);

		protected:
			TObj*        _receiverObject;
			NotifyMethod _receiverMethod;
			Poco::Mutex _mutex;

		private:
			TDelegate(void);

		public:
			TDelegate(TObj* obj, NotifyMethod method, int prio);

			TDelegate(const TDelegate& p_other);

			TDelegate& operator = (const TDelegate& p_other);

			virtual ~TDelegate(void);

			virtual bool notify(const void* sender, TArgs& arguments) override;

			virtual bool equals(const Poco::AbstractDelegate<TArgs>& p_other) const override;

			virtual Poco::AbstractPriorityDelegate<TArgs>* clone() const override;

			virtual void disable() override;

		}; // class TDelegate



		template <class TObj>
		class TDelegate<TObj, void, true> : public Poco::AbstractPriorityDelegate<void>
		{

		public:
			typedef void (TObj::*NotifyMethod)(const void*);

		protected:
			TObj*        _receiverObject;
			NotifyMethod _receiverMethod;
			Poco::Mutex _mutex;

		private:
			TDelegate(void);

		public:
			TDelegate(TObj* obj, NotifyMethod method, int prio);

			TDelegate(const TDelegate& p_other);

			TDelegate& operator = (const TDelegate& p_other);

			virtual ~TDelegate(void);

			virtual bool notify(const void* sender) override;

			virtual bool equals(const Poco::AbstractDelegate<void>& p_other) const override;

			virtual Poco::AbstractPriorityDelegate<void>* clone() const override;

			virtual void disable() override;

		}; // class TDelegate



		template <class TObj>
		class TDelegate<TObj, void, false> : public Poco::AbstractPriorityDelegate<void>
		{

		public:
			typedef void (TObj::*NotifyMethod)(void);

		protected:
			TObj*        _receiverObject;
			NotifyMethod _receiverMethod;
			Poco::Mutex _mutex;

		private:
			TDelegate(void);

		public:
			TDelegate(TObj* obj, NotifyMethod method, int prio);

			TDelegate(const TDelegate& p_other);

			TDelegate& operator = (const TDelegate& p_other);

			virtual ~TDelegate(void);

			virtual bool notify(const void* sender) override;

			virtual bool equals(const Poco::AbstractDelegate<void>& p_other) const override;

			virtual Poco::AbstractPriorityDelegate<void>* clone() const override;

			virtual void disable() override;

		}; // class TDelegate


		template <class TObj, class TArgs>
		static TDelegate<TObj, TArgs, true> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int prio)
		{
			return TDelegate<TObj, TArgs, true>(pObj, NotifyMethod, prio);
		}


		template <class TObj, class TArgs>
		static TDelegate<TObj, TArgs, false> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int prio)
		{
			return TDelegate<TObj, TArgs, false>(pObj, NotifyMethod, prio);
		}


		template <class TObj, class TArgs>
		static Poco::PriorityExpire<TArgs> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<TArgs>(TDelegate<TObj, TArgs, true>(pObj, NotifyMethod, prio), expireMilliSec);
		}


		template <class TObj, class TArgs>
		static Poco::PriorityExpire<TArgs> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<TArgs>(TDelegate<TObj, TArgs, false>(pObj, NotifyMethod, prio), expireMilliSec);
		}


		template <class TArgs>
		static Poco::PriorityExpire<TArgs> priorityDelegate(void(*NotifyMethod)(const void*, TArgs&), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<TArgs>(FunctionPriorityDelegate<TArgs, true, true>(NotifyMethod, prio), expireMilliSec);
		}


		template <class TArgs>
		static Poco::PriorityExpire<TArgs> priorityDelegate(void(*NotifyMethod)(void*, TArgs&), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return PriorityExpire<TArgs>(FunctionPriorityDelegate<TArgs, true, false>(NotifyMethod, prio), expireMilliSec);
		}


		template <class TArgs>
		static Poco::PriorityExpire<TArgs> priorityDelegate(void(*NotifyMethod)(TArgs&), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<TArgs>(FunctionPriorityDelegate<TArgs, false>(NotifyMethod, prio), expireMilliSec);
		}


		template <class TArgs>
		static Poco::FunctionPriorityDelegate<TArgs, true, true> priorityDelegate(void(*NotifyMethod)(const void*, TArgs&), int prio)
		{
			return Poco::FunctionPriorityDelegate<TArgs, true, true>(NotifyMethod, prio);
		}


		template <class TArgs>
		static Poco::FunctionPriorityDelegate<TArgs, true, false> priorityDelegate(void(*NotifyMethod)(void*, TArgs&), int prio)
		{
			return Poco::FunctionPriorityDelegate<TArgs, true, false>(NotifyMethod, prio);
		}


		template <class TArgs>
		static Poco::FunctionPriorityDelegate<TArgs, false> priorityDelegate(void(*NotifyMethod)(TArgs&), int prio)
		{
			return Poco::FunctionPriorityDelegate<TArgs, false>(NotifyMethod, prio);
		}





		template <class TObj>
		static TDelegate<TObj, void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*), int prio)
		{
			return TDelegate<TObj, void>(pObj, NotifyMethod, prio);
		}


		template <class TObj>
		static TDelegate<TObj, void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(), int prio)
		{
			return TDelegate<TObj, void>(pObj, NotifyMethod, prio);
		}


		template <class TObj>
		static Poco::PriorityExpire<void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<void>(TDelegate<TObj, void, true>(pObj, NotifyMethod, prio), expireMilliSec);
		}


		template <class TObj>
		static Poco::PriorityExpire<void> priorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<void>(TDelegate<TObj, void, false>(pObj, NotifyMethod, prio), expireMilliSec);
		}


		inline Poco::PriorityExpire<void> priorityDelegate(void(*NotifyMethod)(const void*), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<void>(Poco::FunctionPriorityDelegate<void, true, true>(NotifyMethod, prio), expireMilliSec);
		}


		inline Poco::PriorityExpire<void> priorityDelegate(void(*NotifyMethod)(void*), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<void>(Poco::FunctionPriorityDelegate<void, true, false>(NotifyMethod, prio), expireMilliSec);
		}


		inline Poco::PriorityExpire<void> priorityDelegate(void(*NotifyMethod)(), int prio, Poco::Timestamp::TimeDiff expireMilliSec)
		{
			return Poco::PriorityExpire<void>(Poco::FunctionPriorityDelegate<void, false>(NotifyMethod, prio), expireMilliSec);
		}


		inline Poco::FunctionPriorityDelegate<void, true, true> priorityDelegate(void(*NotifyMethod)(const void*), int prio)
		{
			return Poco::FunctionPriorityDelegate<void, true, true>(NotifyMethod, prio);
		}


		inline Poco::FunctionPriorityDelegate<void, true, false> priorityDelegate(void(*NotifyMethod)(void*), int prio)
		{
			return Poco::FunctionPriorityDelegate<void, true, false>(NotifyMethod, prio);
		}


		inline Poco::FunctionPriorityDelegate<void, false> priorityDelegate(void(*NotifyMethod)(), int prio)
		{
			return Poco::FunctionPriorityDelegate<void, false>(NotifyMethod, prio);
		}

	} // namespace evt

} // namespace eve

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(void)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(TObj* obj, NotifyMethod method, int prio)
	// Inheritance
	: Poco::AbstractPriorityDelegate<TArgs>(prio)
	// Members init
	, _receiverObject(obj)
	, _receiverMethod(method)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::TDelegate(const TDelegate<TObj, TArgs, useSender> & p_other)
	// Inheritance
	: Poco::AbstractPriorityDelegate<TArgs>(p_other)
	// Members init
	, _receiverObject(p_other._receiverObject),
	, _receiverMethod(p_other._receiverMethod)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender> & eve::evt::TDelegate<TObj, TArgs, useSender>::operator = (const eve::evt::TDelegate<TObj, TArgs, useSender> & p_other)
{
	if (&p_other != this)
	{
		this->_pTarget			= p_other._pTarget;
		this->_receiverObject	= p_other._receiverObject;
		this->_receiverMethod	= p_other._receiverMethod;
		this->_priority			= p_other._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
eve::evt::TDelegate<TObj, TArgs, useSender>::~TDelegate(void)
{}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool eve::evt::TDelegate<TObj, TArgs, useSender>::notify(const void* sender, TArgs& arguments)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		(_receiverObject->*_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
bool eve::evt::TDelegate<TObj, TArgs, useSender>::equals(const Poco::AbstractDelegate<TArgs>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
Poco::AbstractPriorityDelegate<TArgs>* eve::evt::TDelegate<TObj, TArgs, useSender>::clone() const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj, class TArgs, bool useSender>
void eve::evt::TDelegate<TObj, TArgs, useSender>::disable()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}


//-----------------------------------------------


//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(void)
{}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(TObj* obj, NotifyMethod method, int prio)
	// Inheritance
	: Poco::AbstractPriorityDelegate<TArgs>(prio)
	// Members init
	, _receiverObject(obj)
	, _receiverMethod(method)
{}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::TDelegate(const TDelegate<TObj, TArgs, false> & p_other)
	// Inheritance
	: Poco::AbstractPriorityDelegate<TArgs>(p_other)
	// Members init
	, _receiverObject(p_other._receiverObject)
	, _receiverMethod(p_other._receiverMethod)
{}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false> & eve::evt::TDelegate<TObj, TArgs, false>::operator = (const eve::evt::TDelegate<TObj, TArgs, false> & p_other)
{
	if (&p_other != this)
	{
		this->_pTarget			= p_other._pTarget;
		this->_receiverObject	= p_other._receiverObject;
		this->_receiverMethod	= p_other._receiverMethod;
		this->_priority			= p_other._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj, class TArgs>
eve::evt::TDelegate<TObj, TArgs, false>::~TDelegate(void)
{}

//=================================================================================================
template <class TObj, class TArgs>
bool eve::evt::TDelegate<TObj, TArgs, false>::notify(const void* sender, TArgs& arguments)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		(_receiverObject->*_receiverMethod)(arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj, class TArgs>
bool eve::evt::TDelegate<TObj, TArgs, false>::equals(const Poco::AbstractDelegate<TArgs>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
}

//=================================================================================================
template <class TObj, class TArgs>
Poco::AbstractPriorityDelegate<TArgs>* eve::evt::TDelegate<TObj, TArgs, false>::clone() const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj, class TArgs>
void eve::evt::TDelegate<TObj, TArgs, false>::disable()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}


//-----------------------------------------------


//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(void)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(TObj* obj, NotifyMethod method, int prio)
	// Inheritance
	: Poco::AbstractPriorityDelegate<void>(prio)
	// Members init
	, _receiverObject(obj)
	, _receiverMethod(method)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::TDelegate(const TDelegate<TObj, void, true> & p_other)
	// Inheritance
	: Poco::AbstractPriorityDelegate<void>(p_other)
	// Members init
	, _receiverObject(p_other._receiverObject),
	, _receiverMethod(p_other._receiverMethod)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true> & eve::evt::TDelegate<TObj, void, true>::operator = (const eve::evt::TDelegate<TObj, void, true> & p_other)
{
	if (&p_other != this)
	{
		this->_pTarget = p_other._pTarget;
		this->_receiverObject = p_other._receiverObject;
		this->_receiverMethod = p_other._receiverMethod;
		this->_priority = p_other._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, true>::~TDelegate(void)
{}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, true>::notify(const void* sender)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		(_receiverObject->*_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, true>::equals(const Poco::AbstractDelegate<void>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
}

//=================================================================================================
template <class TObj>
Poco::AbstractPriorityDelegate<void>* eve::evt::TDelegate<TObj, void, true>::clone() const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj>
void eve::evt::TDelegate<TObj, void, true>::disable()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}


//-----------------------------------------------


//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(void)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(TObj* obj, NotifyMethod method, int prio)
	// Inheritance
	: Poco::AbstractPriorityDelegate<void>(prio)
	// Members init
	, _receiverObject(obj)
	, _receiverMethod(method)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::TDelegate(const TDelegate<TObj, void, false> & p_other)
	// Inheritance
	: Poco::AbstractPriorityDelegate<void>(p_other)
	// Members init
	, _receiverObject(p_other._receiverObject),
	, _receiverMethod(p_other._receiverMethod)
{}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false> & eve::evt::TDelegate<TObj, void, false>::operator = (const eve::evt::TDelegate<TObj, void, false> & p_other)
{
	if (&p_other != this)
	{
		this->_pTarget = p_other._pTarget;
		this->_receiverObject = p_other._receiverObject;
		this->_receiverMethod = p_other._receiverMethod;
		this->_priority = p_other._priority;
	}
	return *this;
}

//=================================================================================================
template <class TObj>
eve::evt::TDelegate<TObj, void, false>::~TDelegate(void)
{}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, false>::notify(const void* sender)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_receiverObject)
	{
		(_receiverObject->*_receiverMethod)(sender, arguments);
		return true;
	}
	else return false;
}

//=================================================================================================
template <class TObj>
bool eve::evt::TDelegate<TObj, void, false>::equals(const Poco::AbstractDelegate<void>& other) const
{
	const TDelegate* pOtherDelegate = dynamic_cast<const TDelegate*>(other.unwrap());
	return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
}

//=================================================================================================
template <class TObj>
Poco::AbstractPriorityDelegate<void>* eve::evt::TDelegate<TObj, void, false>::clone() const
{
	return new TDelegate(*this);
}

//=================================================================================================
template <class TObj>
void eve::evt::TDelegate<TObj, void, false>::disable()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_receiverObject = 0;
}

#endif // __EVE_EVT_TDELEGATE_H__
