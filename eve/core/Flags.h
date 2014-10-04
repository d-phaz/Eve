
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
#ifndef __EVE_CORE_FLAGS_H__
#define __EVE_CORE_FLAGS_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


namespace eve
{
	namespace core
	{


		class CustomFlag
		{
		public:
			int32_t i;

		public:
			inline CustomFlag(int32_t ai) : i(ai) {}
			inline operator int32_t() const { return i; }

		}; // class CustomFlag


		class  IncompatibleCustomFlag
		{
		public:
			int32_t i;

		public:
			inline explicit IncompatibleCustomFlag(int32_t ai) : i(ai) {}
			inline operator int32_t() const { return i; }

		}; // class IncompatibleCustomFlag


		template<typename Enum>
		class CustomFlags
		{
		public:
			typedef void **Zero;
			int32_t i;

		public:
			typedef Enum enum_type;
			inline CustomFlags(const CustomFlags &f) : i(f.i) {}
			inline CustomFlags(Enum f) : i(f) {}
			inline CustomFlags(Zero = 0) : i(0) {}
			inline CustomFlags(CustomFlag f) : i(f) {}

			inline CustomFlags &operator=(const CustomFlags &f) { i = f.i; return *this; }
			inline CustomFlags &operator&=(int32_t mask) { i &= mask; return *this; }
			inline CustomFlags &operator&=(uint32_t mask) { i &= mask; return *this; }
			inline CustomFlags &operator|=(CustomFlags f) { i |= f.i; return *this; }
			inline CustomFlags &operator|=(Enum f) { i |= f; return *this; }
			inline CustomFlags &operator^=(CustomFlags f) { i ^= f.i; return *this; }
			inline CustomFlags &operator^=(Enum f) { i ^= f; return *this; }

			inline operator int32_t() const { return i; }

			inline CustomFlags operator|(CustomFlags f) const { return CustomFlags(Enum(i | f.i)); }
			inline CustomFlags operator|(Enum f) const { return CustomFlags(Enum(i | f)); }
			inline CustomFlags operator^(CustomFlags f) const { return CustomFlags(Enum(i ^ f.i)); }
			inline CustomFlags operator^(Enum f) const { return CustomFlags(Enum(i ^ f)); }
			inline CustomFlags operator&(int32_t mask) const { return CustomFlags(Enum(i & mask)); }
			inline CustomFlags operator&(uint32_t mask) const { return CustomFlags(Enum(i & mask)); }
			inline CustomFlags operator&(Enum f) const { return CustomFlags(Enum(i & f)); }
			inline CustomFlags operator~() const { return CustomFlags(Enum(~i)); }

			inline bool operator!() const { return !i; }

			inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f)); }

		}; // class CustomFlags

	} // namespace core

} // namespace eve

#define EVE_DECLARE_FLAGS(Flags, Enum)\
	typedef eve::core::CustomFlags<Enum> Flags;

#define EVE_DECLARE_INCOMPATIBLE_FLAGS(Flags) \
	inline eve::core::IncompatibleCustomFlag operator|(Flags::enum_type f1, int32_t f2) \
	{ return eve::core::IncompatibleCustomFlag(int32_t(f1) | f2); }

#define EVE_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
	inline eve::core::CustomFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) \
	{ return eve::core::CustomFlags<Flags::enum_type>(f1) | f2; } \
	inline eve::core::CustomFlags<Flags::enum_type> operator|(Flags::enum_type f1, eve::core::CustomFlags<Flags::enum_type> f2) \
	{ return f2 | f1; } EVE_DECLARE_INCOMPATIBLE_FLAGS(Flags)

#endif //__EVE_CORE_FLAGS_H__