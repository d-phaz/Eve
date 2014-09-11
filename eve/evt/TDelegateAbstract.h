
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
#ifndef __EVE_EVT_TDELEGATE_ABSTRACT_H__
#define __EVE_EVT_TDELEGATE_ABSTRACT_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace evt
	{
		/// Base class for TDelegate and PriorityExpire.
		///
		/// Extends AbstractDelegate with a priority value.
		template <class TArgs>
		class TDelegateAbstract 
		{
		protected:
			int32_t _priority;

		public:
			TDelegateAbstract(int32_t prio)
				// Members init
				: _priority(prio)
			{}

			TDelegateAbstract(const TDelegateAbstract& del)
				// Members init
				: _priority(del._priority)
			{}

			virtual ~TDelegateAbstract(void)
			{}

			int32_t priority(void) const
			{
				return _priority;
			}

			/// Invokes the delegate's callback function.
			/// Returns true if successful, or false if the delegate
			/// has been disabled or has expired.
			virtual bool notify(const void* sender, TArgs& arguments) = 0;

			/// Compares the AbstractDelegate with the other one for equality.
			virtual bool equals(const TDelegateAbstract& other) const = 0;

			/// Returns a deep copy of the AbstractDelegate.
			virtual TDelegateAbstract* clone(void) const = 0;

			/// Disables the delegate, which is done prior to removal.
			virtual void disable(void) = 0;

			/// Returns the unwrapped delegate. Must be overridden by decorators
			/// like Expire.
			virtual const TDelegateAbstract* unwrap(void) const
			{
				return this;
			}
		};



		/// Base class for TDelegate and PriorityExpire.
		///
		/// Extends AbstractDelegate with a priority value.
		template <>
		class TDelegateAbstract<void>
		{

		protected:
			int32_t _priority;

		public:
			TDelegateAbstract(int32_t prio)
				// Members init
				: _priority(prio)
			{}

			TDelegateAbstract(const TDelegateAbstract& del)
				// Members init
				: _priority(del._priority)
			{}

			virtual ~TDelegateAbstract(void)
			{}

			int32_t priority(void) const
			{
				return _priority;
			}

			/// Invokes the delegate's callback function.
			/// Returns true if successful, or false if the delegate
			/// has been disabled or has expired.
			virtual bool notify(const void* sender) = 0;

			/// Compares the AbstractDelegate with the other one for equality.
			virtual bool equals(const TDelegateAbstract& other) const = 0;

			/// Returns a deep copy of the AbstractDelegate.
			virtual TDelegateAbstract* clone(void) const = 0;

			/// Disables the delegate, which is done prior to removal.
			virtual void disable(void) = 0;

			/// Returns the unwrapped delegate. Must be overridden by decorators
			/// like Expire.
			virtual const TDelegateAbstract* unwrap(void) const
			{
				return this;
			}
		};


	} // namespace evt

} // namespace eve

#endif // __EVE_EVT_TDELEGATE_ABSTRACT_H__
