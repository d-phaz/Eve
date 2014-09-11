
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
		/// NotificationStrategy for PriorityEvent.
		///
		/// Delegates are kept in a std::vector<>, ordered by their priority.
		template <class TArgs, class TDelegate>
		class TStrategy
		{
		public:
			typedef std::shared_ptr<TDelegate>   DelegatePtr;
			typedef std::vector<DelegatePtr>     Delegates;
			typedef typename Delegates::iterator Iterator;

		public:
			TStrategy()
			{
			}

			TStrategy(const TStrategy& s) :
				_delegates(s._delegates)
			{
			}

			~TStrategy()
			{
			}

			void notify(const void* sender, TArgs& arguments)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					(*it)->notify(sender, arguments);
				}
			}

			void add(const TDelegate& delegate)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					if ((*it)->priority() > delegate.priority())
					{
						_delegates.insert(it, DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
						return;
					}
				}
				_delegates.push_back(DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
			}

			void remove(const TDelegate& p_delegate)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					if (p_delegate.equals(**it))
					{
						(*it)->disable();
						_delegates.erase(it);
						return;
					}
				}
			}

			TStrategy& operator = (const TStrategy& s)
			{
				if (this != &s)
				{
					_delegates = s._delegates;
				}
				return *this;
			}

			void clear()
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					(*it)->disable();
				}
				_delegates.clear();
			}

			bool empty() const
			{
				return _delegates.empty();
			}

		protected:
			Delegates _delegates;

		}; // class TStrategy



		template <class TDelegate>
		class TStrategy<void, TDelegate>
			/// NotificationStrategy for PriorityEvent.
			///
			/// Delegates are kept in a std::vector<>, ordered
			/// by their priority.
		{
		public:
			typedef std::shared_ptr<TDelegate>   DelegatePtr;
			typedef std::vector<DelegatePtr>     Delegates;
			typedef typename Delegates::iterator Iterator;

		public:

			void notify(const void* sender)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					(*it)->notify(sender);
				}
			}

			void add(const TDelegate& delegate)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					if ((*it)->priority() > delegate.priority())
					{
						_delegates.insert(it, DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
						return;
					}
				}
				_delegates.push_back(DelegatePtr(static_cast<TDelegate*>(delegate.clone())));
			}

			void remove(const TDelegate& p_delegate)
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					if (p_delegate.equals(**it))
					{
						(*it)->disable();
						_delegates.erase(it);
						return;
					}
				}
			}

			TStrategy& operator = (const TStrategy& s)
			{
				if (this != &s)
				{
					_delegates = s._delegates;
				}
				return *this;
			}

			void clear()
			{
				for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
				{
					(*it)->disable();
				}
				_delegates.clear();
			}

			bool empty() const
			{
				return _delegates.empty();
			}

		protected:
			Delegates _delegates;

		}; // class TStrategy

	} // namespace evt

} // namespace eve

#endif // __EVE_EVT_TSTRATEGY_H__
