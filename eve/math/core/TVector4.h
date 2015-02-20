
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

#if !defined(__EVE_MATH_CORE_TVECTOR_H__)
#error "Do not include this header directly, include eve/math/Tvector.h instead"
#endif

#pragma once
#ifndef __EVE_MATH_CORE_TVECTOR_4_H__
#define __EVE_MATH_CORE_TVECTOR_4_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif


namespace eve
{
	namespace math
	{
		template<class T> class TVec2;
		template<class T> class TVec3;

		/**
		* \class eve::math::TVec4
		*
		* \brief Template 4 components vector.
		*/
		template <class T>
		class TVec4
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			T x;
			T y;
			T z;
			T w;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TVec4(void);
			TVec4(T nx, T ny, T nz, T nw = 0);
			TVec4(const TVec3<T>& src, T aW = 0);
			TVec4(const TVec4<T>& src);

			template<typename FromT>
			TVec4(const TVec4<FromT>& src);

			explicit TVec4(const T *d);
			explicit TVec4(const T d);


			void set(T ax, T ay, T az, T aw);
			void set(const TVec4<T> &rhs);

			TVec4<T>& operator=(const TVec4<T>& rhs);
			template<typename FromT>
			TVec4<T>& operator=(const TVec4<FromT>& rhs);


			T& operator[](int32_t n);
			const T& operator[](int32_t n)  const;
			T*	ptr(void) const;


			const TVec4<T>	operator+(const TVec4<T>& rhs) const;
			const TVec4<T>	operator-(const TVec4<T>& rhs) const;
			const TVec4<T>	operator*(const TVec4<T>& rhs) const;
			const TVec4<T>	operator/(const TVec4<T>& rhs) const;
			TVec4<T>&		operator+=(const TVec4<T>& rhs);
			TVec4<T>&		operator-=(const TVec4<T>& rhs);
			TVec4<T>&		operator*=(const TVec4<T>& rhs);
			TVec4<T>&		operator/=(const TVec4<T>& rhs);

			const TVec4<T>	operator+(T rhs) const;
			const TVec4<T>	operator-(T rhs) const;
			const TVec4<T>	operator*(T rhs) const;
			const TVec4<T>	operator/(T rhs) const;
			TVec4<T>&		operator+=(T rhs);
			TVec4<T>&		operator-=(T rhs);
			TVec4<T>&		operator*=(T rhs);
			TVec4<T>&		operator/=(T rhs);

			TVec4<T>			operator-() const;

			bool operator==(const TVec4<T>& rhs) const;
			bool operator!=(const TVec4<T>& rhs) const;


			T dot(const TVec4<T> &rhs) const;
			TVec4<T> cross(const TVec4<T> &rhs) const;


			static bool equal(TVec4<T> const & x, TVec4<T> const & y);
			static bool equal(TVec4<T> const & x, TVec4<T> const & y, T epsilon);
			bool equal(TVec4<T> const & other);
			bool equal(TVec4<T> const & other, T epsilon);

			T distance(const TVec4<T> &rhs) const;
			T distanceSquared(const TVec4<T> &rhs) const;

			T length(void) const;
			T lengthSquared(void) const;

			void normalize(void);
			eve::math::TVec4<T> normalize(const eve::math::TVec4<T> & p_v);
			TVec4<T> normalized(void) const;

			// Tests for zero-length
			void safeNormalize(void);

			//! Limits the length of a TVec4 to \a maxLength, scaling it proportionally if necessary.
			void limit(T maxLength);
			//! Returns a copy of the TVec4 with its length limited to \a maxLength, scaling it proportionally if necessary.
			TVec4<T> limited(T maxLength) const;

			void invert(void);
			TVec4<T> inverted(void) const;


			TVec4<T> lerp(T fact, const TVec4<T>& r) const;
			void lerpEq(T fact, const TVec4<T> &rhs);


			static TVec4<T> max(void);
			static TVec4<T> zero(void);
			static TVec4<T> one(void);
			

			static TVec4<T> white(void);
			static TVec4<T> black(void);

			static TVec4<T> red(void);
			static TVec4<T> green(void);
			static TVec4<T> blue(void);


			TVec4<T> slerp(T fact, const TVec3<T> &r) const;

			// derived from but not equivalent to Quaternion::squad
			TVec4<T> squad(T t, const TVec4<T> &tangentA, const TVec4<T> &tangentB, const TVec4<T> &end) const;


			// GLSL inspired swizzling functions.
			TVec2<T> xx(void) const;
			TVec2<T> xy(void) const;
			TVec2<T> xz(void) const;
			TVec2<T> xw(void) const;
			TVec2<T> yx(void) const;
			TVec2<T> yy(void) const;
			TVec2<T> yz(void) const;
			TVec2<T> yw(void) const;
			TVec2<T> zx(void) const;
			TVec2<T> zy(void) const;
			TVec2<T> zz(void) const;
			TVec2<T> zw(void) const;
			TVec2<T> wx(void) const;
			TVec2<T> wy(void) const;
			TVec2<T> wz(void) const;
			TVec2<T> ww(void) const;

			TVec3<T> xxx(void) const;
			TVec3<T> xxy(void) const;
			TVec3<T> xxz(void) const;
			TVec3<T> xyx(void) const;
			TVec3<T> xyy(void) const;
			TVec3<T> xyz(void) const;
			TVec3<T> xzx(void) const;
			TVec3<T> xzy(void) const;
			TVec3<T> xzz(void) const;
			TVec3<T> yxx(void) const;
			TVec3<T> yxy(void) const;
			TVec3<T> yxz(void) const;
			TVec3<T> yyx(void) const;
			TVec3<T> yyy(void) const;
			TVec3<T> yyz(void) const;
			TVec3<T> yzx(void) const;
			TVec3<T> yzy(void) const;
			TVec3<T> yzz(void) const;
			TVec3<T> zxx(void) const;
			TVec3<T> zxy(void) const;
			TVec3<T> zxz(void) const;
			TVec3<T> zyx(void) const;
			TVec3<T> zyy(void) const;
			TVec3<T> zyz(void) const;
			TVec3<T> zzx(void) const;
			TVec3<T> zzy(void) const;
			TVec3<T> zzz(void) const;

			TVec4<T> xxxx(void) const;
			TVec4<T> xxxy(void) const;
			TVec4<T> xxxz(void) const;
			TVec4<T> xxxw(void) const;
			TVec4<T> xxyx(void) const;
			TVec4<T> xxyy(void) const;
			TVec4<T> xxyz(void) const;
			TVec4<T> xxyw(void) const;
			TVec4<T> xxzx(void) const;
			TVec4<T> xxzy(void) const;
			TVec4<T> xxzz(void) const;
			TVec4<T> xxzw(void) const;
			TVec4<T> xxwx(void) const;
			TVec4<T> xxwy(void) const;
			TVec4<T> xxwz(void) const;
			TVec4<T> xxww(void) const;
			TVec4<T> xyxx(void) const;
			TVec4<T> xyxy(void) const;
			TVec4<T> xyxz(void) const;
			TVec4<T> xyxw(void) const;
			TVec4<T> xyyx(void) const;
			TVec4<T> xyyy(void) const;
			TVec4<T> xyyz(void) const;
			TVec4<T> xyyw(void) const;
			TVec4<T> xyzx(void) const;
			TVec4<T> xyzy(void) const;
			TVec4<T> xyzz(void) const;
			TVec4<T> xyzw(void) const;
			TVec4<T> xywx(void) const;
			TVec4<T> xywy(void) const;
			TVec4<T> xywz(void) const;
			TVec4<T> xyww(void) const;
			TVec4<T> xzxx(void) const;
			TVec4<T> xzxy(void) const;
			TVec4<T> xzxz(void) const;
			TVec4<T> xzxw(void) const;
			TVec4<T> xzyx(void) const;
			TVec4<T> xzyy(void) const;
			TVec4<T> xzyz(void) const;
			TVec4<T> xzyw(void) const;
			TVec4<T> xzzx(void) const;
			TVec4<T> xzzy(void) const;
			TVec4<T> xzzz(void) const;
			TVec4<T> xzzw(void) const;
			TVec4<T> xzwx(void) const;
			TVec4<T> xzwy(void) const;
			TVec4<T> xzwz(void) const;
			TVec4<T> xzww(void) const;
			TVec4<T> xwxx(void) const;
			TVec4<T> xwxy(void) const;
			TVec4<T> xwxz(void) const;
			TVec4<T> xwxw(void) const;
			TVec4<T> xwyx(void) const;
			TVec4<T> xwyy(void) const;
			TVec4<T> xwyz(void) const;
			TVec4<T> xwyw(void) const;
			TVec4<T> xwzx(void) const;
			TVec4<T> xwzy(void) const;
			TVec4<T> xwzz(void) const;
			TVec4<T> xwzw(void) const;
			TVec4<T> xwwx(void) const;
			TVec4<T> xwwy(void) const;
			TVec4<T> xwwz(void) const;
			TVec4<T> xwww(void) const;
			TVec4<T> yxxx(void) const;
			TVec4<T> yxxy(void) const;
			TVec4<T> yxxz(void) const;
			TVec4<T> yxxw(void) const;
			TVec4<T> yxyx(void) const;
			TVec4<T> yxyy(void) const;
			TVec4<T> yxyz(void) const;
			TVec4<T> yxyw(void) const;
			TVec4<T> yxzx(void) const;
			TVec4<T> yxzy(void) const;
			TVec4<T> yxzz(void) const;
			TVec4<T> yxzw(void) const;
			TVec4<T> yxwx(void) const;
			TVec4<T> yxwy(void) const;
			TVec4<T> yxwz(void) const;
			TVec4<T> yxww(void) const;
			TVec4<T> yyxx(void) const;
			TVec4<T> yyxy(void) const;
			TVec4<T> yyxz(void) const;
			TVec4<T> yyxw(void) const;
			TVec4<T> yyyx(void) const;
			TVec4<T> yyyy(void) const;
			TVec4<T> yyyz(void) const;
			TVec4<T> yyyw(void) const;
			TVec4<T> yyzx(void) const;
			TVec4<T> yyzy(void) const;
			TVec4<T> yyzz(void) const;
			TVec4<T> yyzw(void) const;
			TVec4<T> yywx(void) const;
			TVec4<T> yywy(void) const;
			TVec4<T> yywz(void) const;
			TVec4<T> yyww(void) const;
			TVec4<T> yzxx(void) const;
			TVec4<T> yzxy(void) const;
			TVec4<T> yzxz(void) const;
			TVec4<T> yzxw(void) const;
			TVec4<T> yzyx(void) const;
			TVec4<T> yzyy(void) const;
			TVec4<T> yzyz(void) const;
			TVec4<T> yzyw(void) const;
			TVec4<T> yzzx(void) const;
			TVec4<T> yzzy(void) const;
			TVec4<T> yzzz(void) const;
			TVec4<T> yzzw(void) const;
			TVec4<T> yzwx(void) const;
			TVec4<T> yzwy(void) const;
			TVec4<T> yzwz(void) const;
			TVec4<T> yzww(void) const;
			TVec4<T> ywxx(void) const;
			TVec4<T> ywxy(void) const;
			TVec4<T> ywxz(void) const;
			TVec4<T> ywxw(void) const;
			TVec4<T> ywyx(void) const;
			TVec4<T> ywyy(void) const;
			TVec4<T> ywyz(void) const;
			TVec4<T> ywyw(void) const;
			TVec4<T> ywzx(void) const;
			TVec4<T> ywzy(void) const;
			TVec4<T> ywzz(void) const;
			TVec4<T> ywzw(void) const;
			TVec4<T> ywwx(void) const;
			TVec4<T> ywwy(void) const;
			TVec4<T> ywwz(void) const;
			TVec4<T> ywww(void) const;
			TVec4<T> zxxx(void) const;
			TVec4<T> zxxy(void) const;
			TVec4<T> zxxz(void) const;
			TVec4<T> zxxw(void) const;
			TVec4<T> zxyx(void) const;
			TVec4<T> zxyy(void) const;
			TVec4<T> zxyz(void) const;
			TVec4<T> zxyw(void) const;
			TVec4<T> zxzx(void) const;
			TVec4<T> zxzy(void) const;
			TVec4<T> zxzz(void) const;
			TVec4<T> zxzw(void) const;
			TVec4<T> zxwx(void) const;
			TVec4<T> zxwy(void) const;
			TVec4<T> zxwz(void) const;
			TVec4<T> zxww(void) const;
			TVec4<T> zyxx(void) const;
			TVec4<T> zyxy(void) const;
			TVec4<T> zyxz(void) const;
			TVec4<T> zyxw(void) const;
			TVec4<T> zyyx(void) const;
			TVec4<T> zyyy(void) const;
			TVec4<T> zyyz(void) const;
			TVec4<T> zyyw(void) const;
			TVec4<T> zyzx(void) const;
			TVec4<T> zyzy(void) const;
			TVec4<T> zyzz(void) const;
			TVec4<T> zyzw(void) const;
			TVec4<T> zywx(void) const;
			TVec4<T> zywy(void) const;
			TVec4<T> zywz(void) const;
			TVec4<T> zyww(void) const;
			TVec4<T> zzxx(void) const;
			TVec4<T> zzxy(void) const;
			TVec4<T> zzxz(void) const;
			TVec4<T> zzxw(void) const;
			TVec4<T> zzyx(void) const;
			TVec4<T> zzyy(void) const;
			TVec4<T> zzyz(void) const;
			TVec4<T> zzyw(void) const;
			TVec4<T> zzzx(void) const;
			TVec4<T> zzzy(void) const;
			TVec4<T> zzzz(void) const;
			TVec4<T> zzzw(void) const;
			TVec4<T> zzwx(void) const;
			TVec4<T> zzwy(void) const;
			TVec4<T> zzwz(void) const;
			TVec4<T> zzww(void) const;
			TVec4<T> zwxx(void) const;
			TVec4<T> zwxy(void) const;
			TVec4<T> zwxz(void) const;
			TVec4<T> zwxw(void) const;
			TVec4<T> zwyx(void) const;
			TVec4<T> zwyy(void) const;
			TVec4<T> zwyz(void) const;
			TVec4<T> zwyw(void) const;
			TVec4<T> zwzx(void) const;
			TVec4<T> zwzy(void) const;
			TVec4<T> zwzz(void) const;
			TVec4<T> zwzw(void) const;
			TVec4<T> zwwx(void) const;
			TVec4<T> zwwy(void) const;
			TVec4<T> zwwz(void) const;
			TVec4<T> zwww(void) const;
			TVec4<T> wxxx(void) const;
			TVec4<T> wxxy(void) const;
			TVec4<T> wxxz(void) const;
			TVec4<T> wxxw(void) const;
			TVec4<T> wxyx(void) const;
			TVec4<T> wxyy(void) const;
			TVec4<T> wxyz(void) const;
			TVec4<T> wxyw(void) const;
			TVec4<T> wxzx(void) const;
			TVec4<T> wxzy(void) const;
			TVec4<T> wxzz(void) const;
			TVec4<T> wxzw(void) const;
			TVec4<T> wxwx(void) const;
			TVec4<T> wxwy(void) const;
			TVec4<T> wxwz(void) const;
			TVec4<T> wxww(void) const;
			TVec4<T> wyxx(void) const;
			TVec4<T> wyxy(void) const;
			TVec4<T> wyxz(void) const;
			TVec4<T> wyxw(void) const;
			TVec4<T> wyyx(void) const;
			TVec4<T> wyyy(void) const;
			TVec4<T> wyyz(void) const;
			TVec4<T> wyyw(void) const;
			TVec4<T> wyzx(void) const;
			TVec4<T> wyzy(void) const;
			TVec4<T> wyzz(void) const;
			TVec4<T> wyzw(void) const;
			TVec4<T> wywx(void) const;
			TVec4<T> wywy(void) const;
			TVec4<T> wywz(void) const;
			TVec4<T> wyww(void) const;
			TVec4<T> wzxx(void) const;
			TVec4<T> wzxy(void) const;
			TVec4<T> wzxz(void) const;
			TVec4<T> wzxw(void) const;
			TVec4<T> wzyx(void) const;
			TVec4<T> wzyy(void) const;
			TVec4<T> wzyz(void) const;
			TVec4<T> wzyw(void) const;
			TVec4<T> wzzx(void) const;
			TVec4<T> wzzy(void) const;
			TVec4<T> wzzz(void) const;
			TVec4<T> wzzw(void) const;
			TVec4<T> wzwx(void) const;
			TVec4<T> wzwy(void) const;
			TVec4<T> wzwz(void) const;
			TVec4<T> wzww(void) const;
			TVec4<T> wwxx(void) const;
			TVec4<T> wwxy(void) const;
			TVec4<T> wwxz(void) const;
			TVec4<T> wwxw(void) const;
			TVec4<T> wwyx(void) const;
			TVec4<T> wwyy(void) const;
			TVec4<T> wwyz(void) const;
			TVec4<T> wwyw(void) const;
			TVec4<T> wwzx(void) const;
			TVec4<T> wwzy(void) const;
			TVec4<T> wwzz(void) const;
			TVec4<T> wwzw(void) const;
			TVec4<T> wwwx(void) const;
			TVec4<T> wwwy(void) const;
			TVec4<T> wwwz(void) const;
			TVec4<T> wwww(void) const;

			static TVec4<T> xAxis(void);
			static TVec4<T> yAxis(void);
			static TVec4<T> zAxis(void);
			static TVec4<T> wAxis(void);

			static TVec4<T> xAxisNeg(void);
			static TVec4<T> yAxisNeg(void);
			static TVec4<T> zAxisNeg(void);
			static TVec4<T> wAxisNeg(void);

			static TVec4<T> NaN(void);
		
		}; // class TVec4		

	} // namespace math

} // namespace eve


//=================================================================================================
template <class T>
eve::math::TVec4<T>::TVec4(void)
	: x(0)
	, y(0)
	, z(0)
	, w(0)
{}

template <class T>
eve::math::TVec4<T>::TVec4(T nx, T ny, T nz, T nw = 0)
	: x(nx)
	, y(ny)
	, z(nz)
	, w(nw)
{}

template <class T>
eve::math::TVec4<T>::TVec4(const eve::math::TVec3<T>& src, T aW = 0)
	: x(src.x)
	, y(src.y)
	, z(src.z)
	, w(aW)
{}

template <class T>
eve::math::TVec4<T>::TVec4(const eve::math::TVec4<T>& src)
	: x(src.x)
	, y(src.y)
	, z(src.z)
	, w(src.w)
{}


template <class T>
template<typename FromT>
eve::math::TVec4<T>::TVec4(const eve::math::TVec4<FromT>& src)
	: x(static_cast<T>(src.x))
	, y(static_cast<T>(src.y))
	, z(static_cast<T>(src.z))
	, w(static_cast<T>(src.w))
{}

template <class T>
eve::math::TVec4<T>::TVec4(const T *d)
	: x(d[0])
	, y(d[1])
	, z(d[2])
	, w(d[3])
{}

template <class T>
eve::math::TVec4<T>::TVec4(const T d)
	: x(d)
	, y(d)
	, z(d)
	, w(d)
{}



//=================================================================================================
template <class T>
EVE_FORCE_INLINE void eve::math::TVec4<T>::set(T ax, T ay, T az, T aw)
{
	x = ax; y = ay; z = az; w = aw;
}

template <class T>
EVE_FORCE_INLINE void eve::math::TVec4<T>::set(const eve::math::TVec4<T> &rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
}



//=================================================================================================
template <class T>
EVE_FORCE_INLINE eve::math::TVec4<T> & eve::math::TVec4<T>::operator=(const eve::math::TVec4<T> & rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
	return *this;
}

template <class T>
template<typename FromT>
EVE_FORCE_INLINE eve::math::TVec4<T> & eve::math::TVec4<T>::operator=(const eve::math::TVec4<FromT> & rhs)
{
	x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = static_cast<T>(rhs.z); w = static_cast<T>(rhs.w);
	return *this;
}

template <class T>
EVE_FORCE_INLINE T & eve::math::TVec4<T>::operator[](int32_t n)
{
	EVE_ASSERT(n >= 0 && n <= 3);
	return (&x)[n];
}

template <class T>
EVE_FORCE_INLINE const T & eve::math::TVec4<T>::operator[](int32_t n)  const
{
	EVE_ASSERT(n >= 0 && n <= 3);
	return (&x)[n];
}

template <class T>
EVE_FORCE_INLINE T * eve::math::TVec4<T>::ptr(void) const
{ 
	return &(const_cast<eve::math::TVec4<T>*>(this)->x);
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator+(const eve::math::TVec4<T>& rhs) const { return eve::math::TVec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator-(const eve::math::TVec4<T>& rhs) const { return eve::math::TVec4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator*(const eve::math::TVec4<T>& rhs) const { return eve::math::TVec4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator/(const eve::math::TVec4<T>& rhs) const { return eve::math::TVec4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator+=(const eve::math::TVec4<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator-=(const eve::math::TVec4<T>& rhs) { x -= rhs.x;	y -= rhs.y;	z -= rhs.z;	w -= rhs.w;	return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator*=(const eve::math::TVec4<T>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z;	w *= rhs.w;	return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator/=(const eve::math::TVec4<T>& rhs) { x /= rhs.x;	y /= rhs.y;	z /= rhs.z;	w /= rhs.w;	return *this; }

template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator+(T rhs) const { return eve::math::TVec4<T>(x + rhs, y + rhs, z + rhs, w + rhs); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator-(T rhs) const { return eve::math::TVec4<T>(x - rhs, y - rhs, z - rhs, w - rhs); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator*(T rhs) const { return eve::math::TVec4<T>(x * rhs, y * rhs, z * rhs, w * rhs); }
template <class T> EVE_FORCE_INLINE const eve::math::TVec4<T>	eve::math::TVec4<T>::operator/(T rhs) const { return eve::math::TVec4<T>(x / rhs, y / rhs, z / rhs, w / rhs); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator+=(T rhs) { x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator-=(T rhs) { x -= rhs; y -= rhs; z -= rhs; w -= rhs;	return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator*=(T rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>&		eve::math::TVec4<T>::operator/=(T rhs) { x /= rhs; y /= rhs; z /= rhs; w /= rhs;	return *this; }

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T>		eve::math::TVec4<T>::operator-() const { return eve::math::TVec4<T>(-x, -y, -z, -w); } // unary negation

template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::operator==(const eve::math::TVec4<T>& rhs) const { return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w); }
template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::operator!=(const eve::math::TVec4<T>& rhs) const { return !(*this == rhs); }



//=================================================================================================
template <class T> EVE_FORCE_INLINE T eve::math::TVec4<T>::dot(const eve::math::TVec4<T> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::cross(const TVec4<T> &rhs) const
{
	return TVec4<T>(y*rhs.z - rhs.y*z, z*rhs.x - rhs.z*x, x*rhs.y - rhs.x*y);
}

template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::equal(eve::math::TVec4<T> const & x, eve::math::TVec4<T> const & y)
{
	return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y) && eve::math::equal(x.z, y.z) && eve::math::equal(x.w, y.w));
}

template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::equal(eve::math::TVec4<T> const & x, eve::math::TVec4<T> const & y, T epsilon)
{
	return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon) && eve::math::equal(x.z, y.z, epsilon) && eve::math::equal(x.w, y.w, epsilon));
}

template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::equal(eve::math::TVec4<T> const & other)
{
	return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y) && eve::math::equal(z, other.z) && eve::math::equal(w, other.w));
}

template <class T> EVE_FORCE_INLINE bool eve::math::TVec4<T>::equal(eve::math::TVec4<T> const & other, T epsilon)
{
	return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon) && eve::math::equal(z, other.z, epsilon) && eve::math::equal(w, other.w, epsilon));
}

template <class T> EVE_FORCE_INLINE T eve::math::TVec4<T>::distance(const eve::math::TVec4<T> &rhs) const
{
	return (*this - rhs).length();
}

template <class T> EVE_FORCE_INLINE T eve::math::TVec4<T>::distanceSquared(const eve::math::TVec4<T> &rhs) const
{
	return (*this - rhs).lengthSquared();
}

template <class T> EVE_FORCE_INLINE T eve::math::TVec4<T>::length(void) const
{
	// For most vector operations, this assumes w to be zero.
	return eve::math::sqrt(x*x + y*y + z*z + w*w);
}

template <class T> EVE_FORCE_INLINE T eve::math::TVec4<T>::lengthSquared(void) const
{
	// For most vector operations, this assumes w to be zero.
	return x*x + y*y + z*z + w*w;
}

template <class T> EVE_FORCE_INLINE void eve::math::TVec4<T>::normalize(void)
{
	T invS = static_cast<T>(1) / length();
	x *= invS;
	y *= invS;
	z *= invS;
	w *= invS;
}

template<class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::normalize(const eve::math::TVec4<T> & p_v)
{
	T invS = static_cast<T>(1.0) / p_v.length();
	return eve::math::TVec4<T>(p_v.x * invS, p_v.y * invS, p_v.z * invS, , p_v.w * invS);
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::normalized(void) const
{
	T invS = static_cast<T>(1.0) / length();
	return eve::math::TVec4<T>(x*invS, y*invS, z*invS, w*invS);
}

// Tests for zero-length
template <class T> EVE_FORCE_INLINE void eve::math::TVec4<T>::safeNormalize(void)
{
	T s = lengthSquared();
	if (s > 0) 
	{
		T invS = static_cast<T>(1) / eve::math::sqrt(s);
		x *= invS;
		y *= invS;
		z *= invS;
		w = (T)0;
	}
}

//! Limits the length of a TVec4 to \a maxLength, scaling it proportionally if necessary.
template <class T> EVE_FORCE_INLINE void eve::math::TVec4<T>::limit(T maxLength)
{
	T lenSq = lengthSquared();

	if ((lenSq > maxLength * maxLength) && (lenSq > 0)) 
	{
		T ratio = maxLength / eve::math::sqrt(lenSq);
		x *= ratio;
		y *= ratio;
		z *= ratio;
		w *= ratio;
	}
}

//! Returns a copy of the TVec4 with its length limited to \a maxLength, scaling it proportionally if necessary.
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::limited(T maxLength) const
{
	T lenSq = lengthSquared();

	if ((lenSq > maxLength * maxLength) && (lenSq > 0)) 
	{
		T ratio = maxLength / eve::math::sqrt(lenSq);
		return eve::math::TVec4<T>(x * ratio, y * ratio, z * ratio, w * ratio);
	}
	else
	{
		return *this;
	}
}

template <class T> EVE_FORCE_INLINE void eve::math::TVec4<T>::invert(void)
{
	x = -x; y = -y; z = -z; w = -w;
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::inverted(void) const
{
	return eve::math::TVec4<T>(-x, -y, -z, -w);
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::lerp(T fact, const eve::math::TVec4<T>& r) const
{
	return (*this) + (r - (*this)) * fact;
}

template <class T> EVE_FORCE_INLINE void eve::math::TVec4<T>::lerpEq(T fact, const eve::math::TVec4<T> &rhs)
{
	x = x + (rhs.x - x) * fact; y = y + (rhs.y - y) * fact; z = z + (rhs.z - z) * fact; w = w + (rhs.w - w) * fact;
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::max(void)
{
	return eve::math::TVec4<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zero(void)
{
	return eve::math::TVec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
}

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::one(void)
{
	return eve::math::TVec4<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::white(void)
{
	return eve::math::TVec4<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
}
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::black(void)
{
	return eve::math::TVec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::red(void)
{
	return eve::math::TVec4<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::green(void)
{
	return eve::math::TVec4<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(1));
}
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::blue(void)
{
	return eve::math::TVec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(1));
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::slerp(T fact, const eve::math::TVec3<T> & r) const
{
	T cosAlpha, alpha, sinAlpha;
	T t1, t2;
	eve::math::TVec4<T> result;

	// get cosine of angle between vectors (-1 -> 1)
	cosAlpha = this->dot(r);

	// get angle (0 -> pi)
	alpha = eve::math::acos(cosAlpha);

	// get sine of angle between vectors (0 -> 1)
	sinAlpha = eve::math::sin(alpha);

	// this breaks down when sinAlpha = 0, i.e. alpha = 0 or pi
	t1 = eve::math::sin(((T)1 - fact) * alpha) / sinAlpha;
	t2 = eve::math::sin(fact * alpha) / sinAlpha;

	// interpolate src vectors
	return *this * t1 + r * t2;
}

// derived from but not equivalent to Quaternion::squad
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::squad(T t, const eve::math::TVec4<T> &tangentA, const eve::math::TVec4<T> &tangentB, const eve::math::TVec4<T> &end) const
{
	eve::math::TVec4<T> r1 = this->slerp(t, end);
	eve::math::TVec4<T> r2 = tangentA.slerp(t, tangentB);
	return r1.slerp(2 * t * (1 - t), r2);
}



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::xx(void) const { return eve::math::TVec2<T>(x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::xy(void) const { return eve::math::TVec2<T>(x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::xz(void) const { return eve::math::TVec2<T>(x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::xw(void) const { return eve::math::TVec2<T>(x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::yx(void) const { return eve::math::TVec2<T>(y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::yy(void) const { return eve::math::TVec2<T>(y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::yz(void) const { return eve::math::TVec2<T>(y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::yw(void) const { return eve::math::TVec2<T>(y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::zx(void) const { return eve::math::TVec2<T>(z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::zy(void) const { return eve::math::TVec2<T>(z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::zz(void) const { return eve::math::TVec2<T>(z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::zw(void) const { return eve::math::TVec2<T>(z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::wx(void) const { return eve::math::TVec2<T>(w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::wy(void) const { return eve::math::TVec2<T>(w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::wz(void) const { return eve::math::TVec2<T>(w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec4<T>::ww(void) const { return eve::math::TVec2<T>(w, w); }

template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xxx(void) const { return eve::math::TVec3<T>(x, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xxy(void) const { return eve::math::TVec3<T>(x, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xxz(void) const { return eve::math::TVec3<T>(x, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xyx(void) const { return eve::math::TVec3<T>(x, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xyy(void) const { return eve::math::TVec3<T>(x, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xyz(void) const { return eve::math::TVec3<T>(x, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xzx(void) const { return eve::math::TVec3<T>(x, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xzy(void) const { return eve::math::TVec3<T>(x, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::xzz(void) const { return eve::math::TVec3<T>(x, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yxx(void) const { return eve::math::TVec3<T>(y, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yxy(void) const { return eve::math::TVec3<T>(y, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yxz(void) const { return eve::math::TVec3<T>(y, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yyx(void) const { return eve::math::TVec3<T>(y, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yyy(void) const { return eve::math::TVec3<T>(y, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yyz(void) const { return eve::math::TVec3<T>(y, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yzx(void) const { return eve::math::TVec3<T>(y, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yzy(void) const { return eve::math::TVec3<T>(y, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::yzz(void) const { return eve::math::TVec3<T>(y, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zxx(void) const { return eve::math::TVec3<T>(z, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zxy(void) const { return eve::math::TVec3<T>(z, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zxz(void) const { return eve::math::TVec3<T>(z, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zyx(void) const { return eve::math::TVec3<T>(z, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zyy(void) const { return eve::math::TVec3<T>(z, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zyz(void) const { return eve::math::TVec3<T>(z, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zzx(void) const { return eve::math::TVec3<T>(z, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zzy(void) const { return eve::math::TVec3<T>(z, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec4<T>::zzz(void) const { return eve::math::TVec3<T>(z, z, z); }

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxxx(void) const { return eve::math::TVec4<T>(x, x, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxxy(void) const { return eve::math::TVec4<T>(x, x, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxxz(void) const { return eve::math::TVec4<T>(x, x, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxxw(void) const { return eve::math::TVec4<T>(x, x, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxyx(void) const { return eve::math::TVec4<T>(x, x, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxyy(void) const { return eve::math::TVec4<T>(x, x, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxyz(void) const { return eve::math::TVec4<T>(x, x, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxyw(void) const { return eve::math::TVec4<T>(x, x, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxzx(void) const { return eve::math::TVec4<T>(x, x, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxzy(void) const { return eve::math::TVec4<T>(x, x, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxzz(void) const { return eve::math::TVec4<T>(x, x, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxzw(void) const { return eve::math::TVec4<T>(x, x, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxwx(void) const { return eve::math::TVec4<T>(x, x, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxwy(void) const { return eve::math::TVec4<T>(x, x, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxwz(void) const { return eve::math::TVec4<T>(x, x, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xxww(void) const { return eve::math::TVec4<T>(x, x, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyxx(void) const { return eve::math::TVec4<T>(x, y, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyxy(void) const { return eve::math::TVec4<T>(x, y, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyxz(void) const { return eve::math::TVec4<T>(x, y, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyxw(void) const { return eve::math::TVec4<T>(x, y, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyyx(void) const { return eve::math::TVec4<T>(x, y, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyyy(void) const { return eve::math::TVec4<T>(x, y, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyyz(void) const { return eve::math::TVec4<T>(x, y, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyyw(void) const { return eve::math::TVec4<T>(x, y, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyzx(void) const { return eve::math::TVec4<T>(x, y, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyzy(void) const { return eve::math::TVec4<T>(x, y, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyzz(void) const { return eve::math::TVec4<T>(x, y, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyzw(void) const { return eve::math::TVec4<T>(x, y, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xywx(void) const { return eve::math::TVec4<T>(x, y, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xywy(void) const { return eve::math::TVec4<T>(x, y, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xywz(void) const { return eve::math::TVec4<T>(x, y, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xyww(void) const { return eve::math::TVec4<T>(x, y, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzxx(void) const { return eve::math::TVec4<T>(x, z, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzxy(void) const { return eve::math::TVec4<T>(x, z, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzxz(void) const { return eve::math::TVec4<T>(x, z, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzxw(void) const { return eve::math::TVec4<T>(x, z, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzyx(void) const { return eve::math::TVec4<T>(x, z, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzyy(void) const { return eve::math::TVec4<T>(x, z, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzyz(void) const { return eve::math::TVec4<T>(x, z, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzyw(void) const { return eve::math::TVec4<T>(x, z, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzzx(void) const { return eve::math::TVec4<T>(x, z, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzzy(void) const { return eve::math::TVec4<T>(x, z, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzzz(void) const { return eve::math::TVec4<T>(x, z, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzzw(void) const { return eve::math::TVec4<T>(x, z, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzwx(void) const { return eve::math::TVec4<T>(x, z, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzwy(void) const { return eve::math::TVec4<T>(x, z, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzwz(void) const { return eve::math::TVec4<T>(x, z, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xzww(void) const { return eve::math::TVec4<T>(x, z, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwxx(void) const { return eve::math::TVec4<T>(x, w, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwxy(void) const { return eve::math::TVec4<T>(x, w, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwxz(void) const { return eve::math::TVec4<T>(x, w, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwxw(void) const { return eve::math::TVec4<T>(x, w, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwyx(void) const { return eve::math::TVec4<T>(x, w, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwyy(void) const { return eve::math::TVec4<T>(x, w, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwyz(void) const { return eve::math::TVec4<T>(x, w, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwyw(void) const { return eve::math::TVec4<T>(x, w, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwzx(void) const { return eve::math::TVec4<T>(x, w, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwzy(void) const { return eve::math::TVec4<T>(x, w, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwzz(void) const { return eve::math::TVec4<T>(x, w, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwzw(void) const { return eve::math::TVec4<T>(x, w, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwwx(void) const { return eve::math::TVec4<T>(x, w, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwwy(void) const { return eve::math::TVec4<T>(x, w, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwwz(void) const { return eve::math::TVec4<T>(x, w, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xwww(void) const { return eve::math::TVec4<T>(x, w, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxxx(void) const { return eve::math::TVec4<T>(y, x, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxxy(void) const { return eve::math::TVec4<T>(y, x, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxxz(void) const { return eve::math::TVec4<T>(y, x, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxxw(void) const { return eve::math::TVec4<T>(y, x, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxyx(void) const { return eve::math::TVec4<T>(y, x, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxyy(void) const { return eve::math::TVec4<T>(y, x, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxyz(void) const { return eve::math::TVec4<T>(y, x, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxyw(void) const { return eve::math::TVec4<T>(y, x, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxzx(void) const { return eve::math::TVec4<T>(y, x, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxzy(void) const { return eve::math::TVec4<T>(y, x, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxzz(void) const { return eve::math::TVec4<T>(y, x, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxzw(void) const { return eve::math::TVec4<T>(y, x, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxwx(void) const { return eve::math::TVec4<T>(y, x, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxwy(void) const { return eve::math::TVec4<T>(y, x, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxwz(void) const { return eve::math::TVec4<T>(y, x, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yxww(void) const { return eve::math::TVec4<T>(y, x, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyxx(void) const { return eve::math::TVec4<T>(y, y, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyxy(void) const { return eve::math::TVec4<T>(y, y, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyxz(void) const { return eve::math::TVec4<T>(y, y, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyxw(void) const { return eve::math::TVec4<T>(y, y, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyyx(void) const { return eve::math::TVec4<T>(y, y, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyyy(void) const { return eve::math::TVec4<T>(y, y, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyyz(void) const { return eve::math::TVec4<T>(y, y, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyyw(void) const { return eve::math::TVec4<T>(y, y, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyzx(void) const { return eve::math::TVec4<T>(y, y, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyzy(void) const { return eve::math::TVec4<T>(y, y, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyzz(void) const { return eve::math::TVec4<T>(y, y, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyzw(void) const { return eve::math::TVec4<T>(y, y, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yywx(void) const { return eve::math::TVec4<T>(y, y, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yywy(void) const { return eve::math::TVec4<T>(y, y, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yywz(void) const { return eve::math::TVec4<T>(y, y, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yyww(void) const { return eve::math::TVec4<T>(y, y, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzxx(void) const { return eve::math::TVec4<T>(y, z, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzxy(void) const { return eve::math::TVec4<T>(y, z, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzxz(void) const { return eve::math::TVec4<T>(y, z, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzxw(void) const { return eve::math::TVec4<T>(y, z, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzyx(void) const { return eve::math::TVec4<T>(y, z, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzyy(void) const { return eve::math::TVec4<T>(y, z, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzyz(void) const { return eve::math::TVec4<T>(y, z, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzyw(void) const { return eve::math::TVec4<T>(y, z, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzzx(void) const { return eve::math::TVec4<T>(y, z, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzzy(void) const { return eve::math::TVec4<T>(y, z, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzzz(void) const { return eve::math::TVec4<T>(y, z, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzzw(void) const { return eve::math::TVec4<T>(y, z, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzwx(void) const { return eve::math::TVec4<T>(y, z, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzwy(void) const { return eve::math::TVec4<T>(y, z, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzwz(void) const { return eve::math::TVec4<T>(y, z, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yzww(void) const { return eve::math::TVec4<T>(y, z, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywxx(void) const { return eve::math::TVec4<T>(y, w, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywxy(void) const { return eve::math::TVec4<T>(y, w, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywxz(void) const { return eve::math::TVec4<T>(y, w, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywxw(void) const { return eve::math::TVec4<T>(y, w, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywyx(void) const { return eve::math::TVec4<T>(y, w, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywyy(void) const { return eve::math::TVec4<T>(y, w, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywyz(void) const { return eve::math::TVec4<T>(y, w, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywyw(void) const { return eve::math::TVec4<T>(y, w, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywzx(void) const { return eve::math::TVec4<T>(y, w, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywzy(void) const { return eve::math::TVec4<T>(y, w, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywzz(void) const { return eve::math::TVec4<T>(y, w, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywzw(void) const { return eve::math::TVec4<T>(y, w, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywwx(void) const { return eve::math::TVec4<T>(y, w, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywwy(void) const { return eve::math::TVec4<T>(y, w, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywwz(void) const { return eve::math::TVec4<T>(y, w, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::ywww(void) const { return eve::math::TVec4<T>(y, w, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxxx(void) const { return eve::math::TVec4<T>(z, x, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxxy(void) const { return eve::math::TVec4<T>(z, x, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxxz(void) const { return eve::math::TVec4<T>(z, x, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxxw(void) const { return eve::math::TVec4<T>(z, x, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxyx(void) const { return eve::math::TVec4<T>(z, x, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxyy(void) const { return eve::math::TVec4<T>(z, x, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxyz(void) const { return eve::math::TVec4<T>(z, x, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxyw(void) const { return eve::math::TVec4<T>(z, x, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxzx(void) const { return eve::math::TVec4<T>(z, x, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxzy(void) const { return eve::math::TVec4<T>(z, x, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxzz(void) const { return eve::math::TVec4<T>(z, x, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxzw(void) const { return eve::math::TVec4<T>(z, x, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxwx(void) const { return eve::math::TVec4<T>(z, x, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxwy(void) const { return eve::math::TVec4<T>(z, x, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxwz(void) const { return eve::math::TVec4<T>(z, x, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zxww(void) const { return eve::math::TVec4<T>(z, x, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyxx(void) const { return eve::math::TVec4<T>(z, y, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyxy(void) const { return eve::math::TVec4<T>(z, y, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyxz(void) const { return eve::math::TVec4<T>(z, y, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyxw(void) const { return eve::math::TVec4<T>(z, y, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyyx(void) const { return eve::math::TVec4<T>(z, y, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyyy(void) const { return eve::math::TVec4<T>(z, y, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyyz(void) const { return eve::math::TVec4<T>(z, y, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyyw(void) const { return eve::math::TVec4<T>(z, y, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyzx(void) const { return eve::math::TVec4<T>(z, y, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyzy(void) const { return eve::math::TVec4<T>(z, y, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyzz(void) const { return eve::math::TVec4<T>(z, y, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyzw(void) const { return eve::math::TVec4<T>(z, y, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zywx(void) const { return eve::math::TVec4<T>(z, y, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zywy(void) const { return eve::math::TVec4<T>(z, y, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zywz(void) const { return eve::math::TVec4<T>(z, y, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zyww(void) const { return eve::math::TVec4<T>(z, y, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzxx(void) const { return eve::math::TVec4<T>(z, z, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzxy(void) const { return eve::math::TVec4<T>(z, z, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzxz(void) const { return eve::math::TVec4<T>(z, z, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzxw(void) const { return eve::math::TVec4<T>(z, z, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzyx(void) const { return eve::math::TVec4<T>(z, z, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzyy(void) const { return eve::math::TVec4<T>(z, z, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzyz(void) const { return eve::math::TVec4<T>(z, z, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzyw(void) const { return eve::math::TVec4<T>(z, z, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzzx(void) const { return eve::math::TVec4<T>(z, z, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzzy(void) const { return eve::math::TVec4<T>(z, z, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzzz(void) const { return eve::math::TVec4<T>(z, z, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzzw(void) const { return eve::math::TVec4<T>(z, z, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzwx(void) const { return eve::math::TVec4<T>(z, z, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzwy(void) const { return eve::math::TVec4<T>(z, z, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzwz(void) const { return eve::math::TVec4<T>(z, z, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zzww(void) const { return eve::math::TVec4<T>(z, z, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwxx(void) const { return eve::math::TVec4<T>(z, w, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwxy(void) const { return eve::math::TVec4<T>(z, w, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwxz(void) const { return eve::math::TVec4<T>(z, w, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwxw(void) const { return eve::math::TVec4<T>(z, w, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwyx(void) const { return eve::math::TVec4<T>(z, w, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwyy(void) const { return eve::math::TVec4<T>(z, w, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwyz(void) const { return eve::math::TVec4<T>(z, w, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwyw(void) const { return eve::math::TVec4<T>(z, w, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwzx(void) const { return eve::math::TVec4<T>(z, w, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwzy(void) const { return eve::math::TVec4<T>(z, w, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwzz(void) const { return eve::math::TVec4<T>(z, w, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwzw(void) const { return eve::math::TVec4<T>(z, w, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwwx(void) const { return eve::math::TVec4<T>(z, w, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwwy(void) const { return eve::math::TVec4<T>(z, w, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwwz(void) const { return eve::math::TVec4<T>(z, w, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zwww(void) const { return eve::math::TVec4<T>(z, w, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxxx(void) const { return eve::math::TVec4<T>(w, x, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxxy(void) const { return eve::math::TVec4<T>(w, x, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxxz(void) const { return eve::math::TVec4<T>(w, x, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxxw(void) const { return eve::math::TVec4<T>(w, x, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxyx(void) const { return eve::math::TVec4<T>(w, x, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxyy(void) const { return eve::math::TVec4<T>(w, x, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxyz(void) const { return eve::math::TVec4<T>(w, x, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxyw(void) const { return eve::math::TVec4<T>(w, x, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxzx(void) const { return eve::math::TVec4<T>(w, x, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxzy(void) const { return eve::math::TVec4<T>(w, x, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxzz(void) const { return eve::math::TVec4<T>(w, x, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxzw(void) const { return eve::math::TVec4<T>(w, x, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxwx(void) const { return eve::math::TVec4<T>(w, x, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxwy(void) const { return eve::math::TVec4<T>(w, x, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxwz(void) const { return eve::math::TVec4<T>(w, x, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wxww(void) const { return eve::math::TVec4<T>(w, x, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyxx(void) const { return eve::math::TVec4<T>(w, y, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyxy(void) const { return eve::math::TVec4<T>(w, y, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyxz(void) const { return eve::math::TVec4<T>(w, y, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyxw(void) const { return eve::math::TVec4<T>(w, y, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyyx(void) const { return eve::math::TVec4<T>(w, y, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyyy(void) const { return eve::math::TVec4<T>(w, y, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyyz(void) const { return eve::math::TVec4<T>(w, y, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyyw(void) const { return eve::math::TVec4<T>(w, y, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyzx(void) const { return eve::math::TVec4<T>(w, y, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyzy(void) const { return eve::math::TVec4<T>(w, y, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyzz(void) const { return eve::math::TVec4<T>(w, y, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyzw(void) const { return eve::math::TVec4<T>(w, y, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wywx(void) const { return eve::math::TVec4<T>(w, y, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wywy(void) const { return eve::math::TVec4<T>(w, y, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wywz(void) const { return eve::math::TVec4<T>(w, y, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wyww(void) const { return eve::math::TVec4<T>(w, y, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzxx(void) const { return eve::math::TVec4<T>(w, z, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzxy(void) const { return eve::math::TVec4<T>(w, z, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzxz(void) const { return eve::math::TVec4<T>(w, z, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzxw(void) const { return eve::math::TVec4<T>(w, z, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzyx(void) const { return eve::math::TVec4<T>(w, z, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzyy(void) const { return eve::math::TVec4<T>(w, z, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzyz(void) const { return eve::math::TVec4<T>(w, z, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzyw(void) const { return eve::math::TVec4<T>(w, z, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzzx(void) const { return eve::math::TVec4<T>(w, z, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzzy(void) const { return eve::math::TVec4<T>(w, z, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzzz(void) const { return eve::math::TVec4<T>(w, z, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzzw(void) const { return eve::math::TVec4<T>(w, z, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzwx(void) const { return eve::math::TVec4<T>(w, z, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzwy(void) const { return eve::math::TVec4<T>(w, z, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzwz(void) const { return eve::math::TVec4<T>(w, z, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wzww(void) const { return eve::math::TVec4<T>(w, z, w, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwxx(void) const { return eve::math::TVec4<T>(w, w, x, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwxy(void) const { return eve::math::TVec4<T>(w, w, x, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwxz(void) const { return eve::math::TVec4<T>(w, w, x, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwxw(void) const { return eve::math::TVec4<T>(w, w, x, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwyx(void) const { return eve::math::TVec4<T>(w, w, y, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwyy(void) const { return eve::math::TVec4<T>(w, w, y, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwyz(void) const { return eve::math::TVec4<T>(w, w, y, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwyw(void) const { return eve::math::TVec4<T>(w, w, y, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwzx(void) const { return eve::math::TVec4<T>(w, w, z, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwzy(void) const { return eve::math::TVec4<T>(w, w, z, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwzz(void) const { return eve::math::TVec4<T>(w, w, z, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwzw(void) const { return eve::math::TVec4<T>(w, w, z, w); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwwx(void) const { return eve::math::TVec4<T>(w, w, w, x); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwwy(void) const { return eve::math::TVec4<T>(w, w, w, y); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwwz(void) const { return eve::math::TVec4<T>(w, w, w, z); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wwww(void) const { return eve::math::TVec4<T>(w, w, w, w); }



//=================================================================================================
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xAxis(void) { return eve::math::TVec4<T>(1, 0, 0, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yAxis(void) { return eve::math::TVec4<T>(0, 1, 0, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zAxis(void) { return eve::math::TVec4<T>(0, 0, 1, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wAxis(void) { return eve::math::TVec4<T>(0, 0, 0, 1); }

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::xAxisNeg(void) { return eve::math::TVec4<T>(-1, 0, 0, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::yAxisNeg(void) { return eve::math::TVec4<T>(0, -1, 0, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::zAxisNeg(void) { return eve::math::TVec4<T>(0, 0, -1, 0); }
template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::wAxisNeg(void) { return eve::math::TVec4<T>(0, 0, 0, -1); }

template <class T> EVE_FORCE_INLINE eve::math::TVec4<T> eve::math::TVec4<T>::NaN(void)   { return eve::math::TVec4<T>(eve::math::NaN(), eve::math::NaN(), eve::math::NaN(), eve::math::NaN()); }


#endif // __EVE_MATH_CORE_TVECTOR_4_H__
