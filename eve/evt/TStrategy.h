
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
#ifndef __EVE_EVT_TSTRATEGY_H__
#define __EVE_EVT_TSTRATEGY_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

namespace eve
{
	namespace evt
	{
		/** 
		* \class eve::evt::TStrategy
		* \brief Notification strategy for event.
		* Delegates are stored in a std::vector<>, ordered by their priority.
		*/
		template <class TArgs, class TDelegate>
		class TStrategy
		{

			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef std::shared_ptr<TDelegate>		DelegatePtr;
			typedef std::vector<DelegatePtr>		Delegates;
			typedef typename Delegates::iterator	Iterator;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			Delegates m_delegates;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** \brief Class constructor. */
			TStrategy(void);
			/** \brief Copy constructor. */
			TStrategy(const TStrategy & s);
			/** \brief Class destructor. */
			virtual ~TStrategy(void);


			/** \brief Assignment operator. */
			TStrategy& operator = (const TStrategy & s);


			/** \brief Notify delegates using sender and arguments. */
			void notify(const void * sender, TArgs& arguments);


			/** \brief Add a copy of the target delegate \p_delegate. */
			void add(const TDelegate & p_delegate);
			/** \brief Disable and remove delegate similar to the target one \p_delegate. */
			void remove(const TDelegate & p_delegate);
			/** \brief Disable and remove all delegates. */
			void clear(void);


			/** \brief Test if delegate std::vector is empty. */
			bool empty(void) const;

		}; // class TStrategy



		/**
		* \class eve::evt::TStrategy (specialized)
		* \brief Notification strategy for event.
		* Delegates are stored in a std::vector<>, ordered by their priority.
		*/
		template <class TDelegate>
		class TStrategy<void, TDelegate>
		{
			
			//////////////////////////////////////
			//				TYPE				//
			//////////////////////////////////////

		public:
			typedef std::shared_ptr<TDelegate>   DelegatePtr;
			typedef std::vector<DelegatePtr>     Delegates;
			typedef typename Delegates::iterator Iterator;


			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			Delegates m_delegates;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** \brief Class constructor. */
			TStrategy(void);
			/** \brief Copy constructor. */
			TStrategy(const TStrategy & s);
			/** \brief Class destructor. */
			virtual ~TStrategy(void);


			/** \brief Assignment operator. */
			TStrategy& operator = (const TStrategy & s);


			/** \brief Notify delegates using sender and arguments. */
			void notify(const void * sender);


			/** \brief Add a copy of the target delegate \p_delegate. */
			void add(const TDelegate & delegate);
			/** \brief Disable and remove delegate similar to the target one \p_delegate. */
			void remove(const TDelegate & p_delegate);
			/** \brief Disable and remove all delegates. */
			void clear(void);


			/** \brief Test if delegate std::vector is empty. */
			bool empty(void) const;

		}; // class TStrategy

	} // namespace evt

} // namespace eve


//=================================================================================================
template <class TArgs, class TDelegate>
eve::evt::TStrategy<TArgs, TDelegate>::TStrategy(void)
	: m_delegates()
{}

//=================================================================================================
template <class TArgs, class TDelegate>
eve::evt::TStrategy<TArgs, TDelegate>::TStrategy(const TStrategy & s) 
	: m_delegates(s.m_delegates)
{}

//=================================================================================================
template <class TArgs, class TDelegate>
eve::evt::TStrategy<TArgs, TDelegate>::~TStrategy(void)
{}

//=================================================================================================
template <class TArgs, class TDelegate>
eve::evt::TStrategy<TArgs, TDelegate> & eve::evt::TStrategy<TArgs, TDelegate>::operator = (const TStrategy<TArgs, TDelegate> & s)
{
	if (this != &s)
	{
		m_delegates = s.m_delegates;
	}
	return *this;
}

//=================================================================================================
template <class TArgs, class TDelegate>
void eve::evt::TStrategy<TArgs, TDelegate>::notify(const void * sender, TArgs& arguments)
{
	for (auto& it : m_delegates)
	{
		it->notify(sender, arguments);
	}
}

//=================================================================================================
template <class TArgs, class TDelegate>
void eve::evt::TStrategy<TArgs, TDelegate>::add(const TDelegate & p_delegate)
{
	for (Iterator it = m_delegates.begin(); it != m_delegates.end(); ++it)
	{
		if ((*it)->priority() > p_delegate.priority())
		{
			m_delegates.insert(it, DelegatePtr(static_cast<TDelegate*>(p_delegate.clone())));
			return;
		}
	}
	m_delegates.push_back(DelegatePtr(static_cast<TDelegate*>(p_delegate.clone())));
}

//=================================================================================================
template <class TArgs, class TDelegate>
void eve::evt::TStrategy<TArgs, TDelegate>::remove(const TDelegate & p_delegate)
{
	for (Iterator it = m_delegates.begin(); it != m_delegates.end(); ++it)
	{
		if (p_delegate.equals(**it))
		{
			(*it)->disable();
			m_delegates.erase(it);
			return;
		}
	}
}

//=================================================================================================
template <class TArgs, class TDelegate>
void eve::evt::TStrategy<TArgs, TDelegate>::clear(void)
{
	for (auto& it : m_delegates)
	{
		it->disable();
	}
	m_delegates.clear();
}

//=================================================================================================
template <class TArgs, class TDelegate>
bool eve::evt::TStrategy<TArgs, TDelegate>::empty(void) const
{
	return m_delegates.empty();
}


//-----------------------------------------------


//=================================================================================================
template <class TDelegate>
eve::evt::TStrategy<void, TDelegate>::TStrategy(void)
	: m_delegates()
{}

//=================================================================================================
template <class TDelegate>
eve::evt::TStrategy<void, TDelegate>::TStrategy(const TStrategy & s) 
	: m_delegates(s.m_delegates)
{}

//=================================================================================================
template <class TDelegate>
eve::evt::TStrategy<void, TDelegate>::~TStrategy(void)
{}

//=================================================================================================
template <class TDelegate>
eve::evt::TStrategy<void, TDelegate> & eve::evt::TStrategy<void, TDelegate>::operator = (const TStrategy<void, TDelegate> & s)
{
	if (this != &s)
	{
		m_delegates = s.m_delegates;
	}
	return *this;
}

//=================================================================================================
template <class TDelegate>
void eve::evt::TStrategy<void, TDelegate>::notify(const void * sender)
{
	for (auto& it : m_delegates)
	{
		it->notify(sender);
	}
}

//=================================================================================================
template <class TDelegate>
void eve::evt::TStrategy<void, TDelegate>::add(const TDelegate & delegate)
{
	for (Iterator it = m_delegates.begin(); it != m_delegates.end(); ++it)
	{
		if ((*it)->priority() > delegate.priority())
		{
			m_delegates.insert(it, DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
			return;
		}
	}
	m_delegates.push_back(DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
}

//=================================================================================================
template <class TDelegate>
void eve::evt::TStrategy<void, TDelegate>::remove(const TDelegate & p_delegate)
{
	for (Iterator it = m_delegates.begin(); it != m_delegates.end(); ++it)
	{
		if (p_delegate.equals(**it))
		{
			(*it)->disable();
			m_delegates.erase(it);
			return;
		}
	}
}

//=================================================================================================
template <class TDelegate>
void eve::evt::TStrategy<void, TDelegate>::clear(void)
{
	for (auto& it : m_delegates)
	{
		it->disable();
	}
	m_delegates.clear();
}

//=================================================================================================
template <class TDelegate>
bool eve::evt::TStrategy<void, TDelegate>::empty(void) const
{
	return m_delegates.empty();
}

#endif // __EVE_EVT_TSTRATEGY_H__
