
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
#ifndef __EVE_MATH_TVECTOR_H__
#define __EVE_MATH_TVECTOR_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_TVECTOR_2_H__
#include "eve/math/TVector2.h"
#endif

#ifndef __EVE_MATH_TVECTOR_3_H__
#include "eve/math/TVector3.h"
#endif

#ifndef __EVE_MATH_TVECTOR_4_H__
#include "eve/math/TVector4.h"
#endif


namespace eve
{
	namespace math
	{

		/** \brief Convert coordinate from rectangular (Cartesian) coordinates to polar coordinates of the form (radius, theta). */
		template<class T>
		TVec2<T> toPolar(TVec2<T> car)
		{
			const T epsilon = static_cast<T>(0.0000001);
			T theta;
			if (eve::math::abs(car.x) < epsilon) // x == 0
			{
				if (eve::math::abs(car.y) < epsilon) theta = 0;
				else if (car.y > 0) theta = (T)M_PI / 2;
				else theta = ((T)M_PI * 3) / 2;
			}
			else if (car.x > 0)
			{
				if (car.y < 0) theta = eve::math::atan(car.y / car.x) + 2 * (T)M_PI;
				else theta = eve::math::atan(car.y / car.x);
			}
			else // car.x < 0
			{
				theta = (eve::math::atan(car.y / car.x) + M_PI);
			}

			return eve::math::TVec2<T>(car.length(), theta);
		}

		/** \brief Convert coordinate from polar coordinates of the form (radius, theta) to rectangular coordinates. */
		template<class T>
		TVec2<T> fromPolar(TVec2<T> pol)
		{
			return eve::math::TVec2<T>(eve::math::cos(pol.y) *  pol.x, eve::math::sin(pol.y) *  pol.x);
		}

		

		//=================================================================================================
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator * (Y s, const eve::math::TVec2<T> &v) { return eve::math::TVec2<T>(v.x * s, v.y * s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator * (const eve::math::TVec2<T> &v, Y s) { return eve::math::TVec2<T>(v.x * s, v.y * s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator * (Y s, const eve::math::TVec3<T> &v) { return eve::math::TVec3<T>(v.x * s, v.y * s, v.z * s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator * (const eve::math::TVec3<T> &v, Y s) { return eve::math::TVec3<T>(v.x * s, v.y * s, v.z * s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator * (Y s, const eve::math::TVec4<T> &v) { return eve::math::TVec4<T>(v.x * s, v.y * s, v.z * s, v.w * s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator * (const eve::math::TVec4<T> &v, Y s) { return eve::math::TVec4<T>(v.x * s, v.y * s, v.z * s, v.w * s); }


		//=================================================================================================
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator / (Y s, const eve::math::TVec2<T> &v) { return eve::math::TVec2<T>(v.x / s, v.y / s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator / (const eve::math::TVec2<T> &v, Y s) { return eve::math::TVec2<T>(v.x / s, v.y / s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator / (Y s, const eve::math::TVec3<T> &v) { return eve::math::TVec3<T>(v.x / s, v.y / s, v.z / s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator / (const eve::math::TVec3<T> &v, Y s) { return eve::math::TVec3<T>(v.x / s, v.y / s, v.z / s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator / (Y s, const eve::math::TVec4<T> &v) { return eve::math::TVec4<T>(v.x / s, v.y / s, v.z / s, v.w / s); }
		template<class T, class Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator / (const eve::math::TVec4<T> &v, Y s) { return eve::math::TVec4<T>(v.x / s, v.y / s, v.z / s, v.w / s); }


		//=================================================================================================
		template <class T> EVE_FORCE_INLINE T dot(const eve::math::TVec2<T> & a, const eve::math::TVec2<T> & b) { return a.dot(b); }
		template <class T> EVE_FORCE_INLINE T dot(const eve::math::TVec3<T> & a, const eve::math::TVec3<T> & b) { return a.dot(b); }
		template <class T> EVE_FORCE_INLINE T dot(const eve::math::TVec4<T> & a, const eve::math::TVec4<T> & b) { return a.dot(b); }


		//=================================================================================================
		template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> cross(const eve::math::TVec3<T> & a, const eve::math::TVec3<T> & b) { return a.cross(b); }
		template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> cross(const eve::math::TVec4<T> & a, const eve::math::TVec4<T> & b) { return a.cross(b); }


		//=================================================================================================
		template <class T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec2<T> & a) { return std::isnan(a.x) || std::isnan(a.y); }
		template <class T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec3<T> & a) { return std::isnan(a.x) || std::isnan(a.y) || std::isnan(a.z); }
		template <class T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec4<T> & a) { return std::isnan(a.x) || std::isnan(a.y) || std::isnan(a.z) || std::isnan(a.w); }
		

	} // namespace math

} // namespace eve

#endif // __TVECTOR_H__
