
#pragma once
#ifndef __EVE_MATH_TYPES_H__
#define __EVE_MATH_TYPES_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif


namespace eve
{
	namespace __math_internal
	{
		typedef EVE_ALIGNED16(int32_t)		__vec4i[4];
		typedef EVE_ALIGNED16(uint32_t)		__vec4ui[4];
		typedef EVE_ALIGNED16(float)		__vec4f[4];
		typedef EVE_ALIGNED16(double)		__vec4d[4];

	} // namespace __math_internal

	typedef eve::__math_internal::__vec4i		vec4i_t;
	typedef eve::__math_internal::__vec4ui		vec4iu_t;
	typedef eve::__math_internal::__vec4f		vec4f_t;
	typedef eve::__math_internal::__vec4d		vec4d_t;

	typedef __m128								simd_float4_t;

} // namespace eve

#endif // __EVE_MATH_TYPES_H__
