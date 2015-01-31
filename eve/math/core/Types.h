
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
#ifndef __EVE_MATH_CORE_TYPES_H__
#define __EVE_MATH_CORE_TYPES_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_TQUATERNION_H__
#include "eve/math/core/TQuaternion.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif


/** \typedef eve_real_t \brief Floating point type based on double precision activation. */
#if defined(EVE_PRECISION_DOUBLE)
typedef	double		eve_real_t;
#else
typedef float		eve_real_t;
#endif


namespace eve
{
	namespace math
	{
		typedef EVE_ALIGNED16(int32_t)		__vec4i[4];
		typedef EVE_ALIGNED16(uint32_t)		__vec4ui[4];
		typedef EVE_ALIGNED16(float)		__vec4f[4];
		typedef EVE_ALIGNED16(double)		__vec4d[4];
		typedef EVE_ALIGNED16(eve_real_t)	__vec4r[4];

	} // namespace math


	typedef eve::math::__vec4i					vec4i_t;
	typedef eve::math::__vec4ui					vec4ui_t;
	typedef eve::math::__vec4f					vec4f_t;
	typedef eve::math::__vec4d					vec4d_t;
	typedef eve::math::__vec4r					vec4r_t;

	
	typedef __m128								simd_float4_t;


	typedef eve::math::TVec2<int32_t>			vec2i;
	typedef eve::math::TVec2<uint32_t>			vec2ui;
	typedef eve::math::TVec2<float>				vec2f;
	typedef eve::math::TVec2<double>			vec2d;
	typedef eve::math::TVec2<eve_real_t>		vec2r;

	typedef eve::math::TVec3<int32_t>			vec3i;
	typedef eve::math::TVec3<uint32_t>			vec3ui;
	typedef eve::math::TVec3<float>				vec3f;
	typedef eve::math::TVec3<double>			vec3d;
	typedef eve::math::TVec3<eve_real_t>		vec3r;

	typedef eve::math::TVec4<int32_t>			vec4i;
	typedef eve::math::TVec4<uint32_t>			vec4ui;
	typedef eve::math::TVec4<float>				vec4f;
	typedef eve::math::TVec4<double>			vec4d;
	typedef eve::math::TVec4<eve_real_t>		vec4r;

	typedef eve::math::TVec4<int32_t>			color4i;
	typedef eve::math::TVec4<uint32_t>			color4ui;
	typedef eve::math::TVec4<float>				color4f;
	typedef eve::math::TVec4<double>			color4d;
	typedef eve::math::TVec4<eve_real_t>		color4r;
		

	typedef eve::math::TMatrix22<float>			mat22f;
	typedef eve::math::TMatrix22<double>		mat22d;
	typedef eve::math::TMatrix22<eve_real_t>	mat22r;

	typedef eve::math::TMatrix33<float>			mat33f;
	typedef eve::math::TMatrix33<double>		mat33d;
	typedef eve::math::TMatrix33<eve_real_t>	mat33r;

	typedef eve::math::TMatrix44<float>			mat44f;
	typedef eve::math::TMatrix44<double>		mat44d;
	typedef eve::math::TMatrix44<eve_real_t>	mat44r;
	

	typedef eve::math::TQuaternion<float>		quatf;
	typedef eve::math::TQuaternion<double>		quatd;
	typedef eve::math::TQuaternion<eve_real_t>	quatr;

} // namespace eve

#endif // __EVE_MATH_CORE_TYPES_H__
