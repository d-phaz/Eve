
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

#if !defined(__EVE_MATH_TVECTOR_H__)
#error "Do not include this header directly, include eve/math/Tvector.h instead"
#endif

#pragma once
#ifndef __EVE_MATH_TVECTOR_2_H__
#define __EVE_MATH_TVECTOR_2_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_MATH_H__
#include "eve/math/Math.h"
#endif


namespace eve
{
	namespace math
	{
		template<class T> class TVec3;


		/** 
		* \class eve::math::TVec2
		*
		* \brief Template 2 components vector.
		*/
		template<typename T>
		class TVec2
		{
			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			T x; 
			T y;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TVec2(void);
			TVec2(T nx, T ny);
			TVec2(T n);
			TVec2(const TVec2<T>& src);
			explicit TVec2(const T *d);

			template<typename FromT>
			TVec2(const TVec2<FromT>& src);

			void set(T ax, T ay);
			void set(const TVec2<T> &rhs);


			// Operators
			template<typename FromT>
			TVec2<T>& operator=(const TVec2<FromT>& rhs);
			TVec2<T> & operator=(const TVec2<T>& rhs);


			T& operator[](int32_t n);
			const T& operator[](int32_t n) const;

			T *	ptr(void) const;


			const TVec2<T>	operator + (const TVec2<T>& rhs) const;
			const TVec2<T>	operator - (const TVec2<T>& rhs) const;
			const TVec2<T>	operator * (const TVec2<T>& rhs) const;
			const TVec2<T>	operator / (const TVec2<T>& rhs) const;
			TVec2<T> &	operator += (const TVec2<T>& rhs);
			TVec2<T> &	operator -= (const TVec2<T>& rhs);
			TVec2<T> &	operator *= (const TVec2<T>& rhs);
			TVec2<T> &	operator /= (const TVec2<T>& rhs);

			const TVec2<T>	operator + (T rhs) const;
			const TVec2<T>	operator - (T rhs) const;
			const TVec2<T>	operator * (T rhs) const;
			const TVec2<T>	operator / (T rhs) const;
			TVec2<T> &	operator += (T rhs);
			TVec2<T> &	operator -= (T rhs);
			TVec2<T> &	operator *= (T rhs);
			TVec2<T> &	operator /= (T rhs);

			TVec2<T>		operator-() const;


			bool operator==(const TVec2<T> &rhs) const;
			bool operator!=(const TVec2<T> &rhs) const;


			T dot(const TVec2<T> &rhs) const;

			//! Returns the z component of the cross if the two operands were TVec3's on the XY plane, the equivalent of TVec3(*this).cross( TVec3(rhs) ).z
			T cross(const TVec2<T> &rhs) const;

			T distance(const TVec2<T> &rhs) const;

			T distanceSquared(const TVec2<T> &rhs) const;

			T length(void) const;


			void normalize(void);
			TVec2<T> normalized(void) const;

			// tests for zero-length
			void safeNormalize(void);
			TVec2<T> safeNormalized(void) const;

			void rotate(T radians);


			T lengthSquared(void) const;


			//! Limits the length of a TVec2 to \a maxLength, scaling it proportionally if necessary.
			void limit(T maxLength);
			//! Returns a copy of the TVec2 with its length limited to \a maxLength, scaling it proportionally if necessary.
			TVec2<T> limited(T maxLength) const;


			void invert(void);
			TVec2<T> inverted(void) const;


			TVec2<T> lerp(T fact, const TVec2<T>& r) const;
			void lerpEq(T fact, const TVec2<T> &rhs);


			bool equal(TVec2<T> const & other);
			bool equal(TVec2<T> const & other, T epsilon);

			static bool equal(TVec2<T> const & x, TVec2<T> const & y);
			static bool equal(TVec2<T> const & x, TVec2<T> const & y, T epsilon);


			// GLSL inspired swizzling functions.
			TVec2<T> xx(void) const;
			TVec2<T> xy(void) const;
			TVec2<T> yx(void) const;
			TVec2<T> yy(void) const;

			TVec3<T> xxx(void) const;
			TVec3<T> xxy(void) const;
			TVec3<T> xyx(void) const;
			TVec3<T> xyy(void) const;
			TVec3<T> yxx(void) const;
			TVec3<T> yxy(void) const;
			TVec3<T> yyx(void) const;
			TVec3<T> yyy(void) const;



			static TVec2<T> max(void);

			static TVec2<T> zero(void);
			static TVec2<T> one(void);

			static TVec2<T> xAxis(void);
			static TVec2<T> yAxis(void);

			static TVec2<T> xAxisNeg(void);
			static TVec2<T> yAxisNeg(void);

			static TVec2<T> NaN(void);

		}; // class TVector2

	} // namespace math

} // namespace eve


//=================================================================================================
template<typename T>
eve::math::TVec2<T>::TVec2(void) 
	: x(0)
	, y(0) 
{}

template<typename T>
eve::math::TVec2<T>::TVec2(T nx, T ny) 
	: x(nx)
	, y(ny) 
{}

template<typename T>
eve::math::TVec2<T>::TVec2(T n) 
	: x(n)
	, y(n) 
{}

template<typename T>
eve::math::TVec2<T>::TVec2(const eve::math::TVec2<T> & src)
	: x(src.x)
	, y(src.y) 
{}

template<typename T>
eve::math::TVec2<T>::TVec2(const T *d) 
	: x(d[0])
	, y(d[1]) 
{}

template<typename T>
template<typename FromT>
eve::math::TVec2<T>::TVec2(const eve::math::TVec2<FromT> & src)
	: x(static_cast<T>(src.x))
	, y(static_cast<T>(src.y))
{}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::set(T ax, T ay)
{
	x = ax; y = ay;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::set(const TVec2<T> & rhs)
{
	x = rhs.x; y = rhs.y;
}



//=================================================================================================
template<typename T>
template<typename FromT>
EVE_FORCE_INLINE eve::math::TVec2<T> & eve::math::TVec2<T>::operator=(const eve::math::TVec2<FromT> & rhs)
{
	x = static_cast<T>(rhs.x);
	y = static_cast<T>(rhs.y);
	return *this;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> & eve::math::TVec2<T>::operator=(const eve::math::TVec2<T> & rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE T & eve::math::TVec2<T>::operator[](int32_t n)
{
	EVE_ASSERT(n >= 0 && n <= 1);
	return (&x)[n];
}

template<typename T>
EVE_FORCE_INLINE const T & eve::math::TVec2<T>::operator[](int32_t n) const
{
	EVE_ASSERT(n >= 0 && n <= 1);
	return (&x)[n];
}

template<typename T>
EVE_FORCE_INLINE T*	eve::math::TVec2<T>::ptr(void) const
{ 
	return &(const_cast<TVec2*>(this)->x); 
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator+(const eve::math::TVec2<T> & rhs) const { return eve::math::TVec2<T>(x + rhs.x, y + rhs.y); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator-(const eve::math::TVec2<T> & rhs) const { return eve::math::TVec2<T>(x - rhs.x, y - rhs.y); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator*(const eve::math::TVec2<T> & rhs) const { return eve::math::TVec2<T>(x * rhs.x, y * rhs.y); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator/(const eve::math::TVec2<T> & rhs) const { return eve::math::TVec2<T>(x / rhs.x, y / rhs.y); }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> &	eve::math::TVec2<T>::operator+=(const eve::math::TVec2<T> & rhs) { x += rhs.x; y += rhs.y; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> &	eve::math::TVec2<T>::operator-=(const eve::math::TVec2<T> & rhs) { x -= rhs.x; y -= rhs.y; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> &	eve::math::TVec2<T>::operator*=(const eve::math::TVec2<T> & rhs) { x *= rhs.x; y *= rhs.y; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> &	eve::math::TVec2<T>::operator/=(const eve::math::TVec2<T> & rhs) { x /= rhs.x; y /= rhs.y; return *this; }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator+(T rhs) const { return eve::math::TVec2<T>(x + rhs, y + rhs); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator-(T rhs) const { return eve::math::TVec2<T>(x - rhs, y - rhs); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator*(T rhs) const { return eve::math::TVec2<T>(x * rhs, y * rhs); }

template<typename T>
EVE_FORCE_INLINE const eve::math::TVec2<T>	eve::math::TVec2<T>::operator/(T rhs) const { return eve::math::TVec2<T>(x / rhs, y / rhs); }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T>&	eve::math::TVec2<T>::operator+=(T rhs)	{ x += rhs;	y += rhs; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T>&	eve::math::TVec2<T>::operator-=(T rhs) { x -= rhs; y -= rhs; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T>&	eve::math::TVec2<T>::operator*=(T rhs) { x *= rhs; y *= rhs; return *this; }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T>&	eve::math::TVec2<T>::operator/=(T rhs) { x /= rhs; y /= rhs; return *this; }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T>	eve::math::TVec2<T>::operator-() const { return eve::math::TVec2<T>(-x, -y); }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec2<T>::operator==(const eve::math::TVec2<T> & rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec2<T>::operator!=(const eve::math::TVec2<T> & rhs) const
{
	return !(*this == rhs);
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::dot(const eve::math::TVec2<T> &rhs) const
{
	return x * rhs.x + y * rhs.y;
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::cross(const eve::math::TVec2<T> &rhs) const
{
	return x * rhs.y - y * rhs.x;
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::distance(const eve::math::TVec2<T> &rhs) const
{
	return (*this - rhs).length();
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::distanceSquared(const eve::math::TVec2<T> &rhs) const
{
	return (*this - rhs).lengthSquared();
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::length(void) const
{
	return eve::math::sqrt(x*x + y*y);
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::normalize(void)
{
	T invS = static_cast<T>(1) / length();
	x *= invS;
	y *= invS;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::normalized(void) const
{
	T invS = static_cast<T>(1) / length();
	return eve::math::TVec2<T>(x * invS, y * invS);
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::safeNormalize(void)
{
	T s = lengthSquared();
	if (s > 0) {
		T invL = static_cast<T>(1) / eve::math::sqrt(s);
		x *= invL;
		y *= invL;
	}
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::safeNormalized(void) const
{
	T s = lengthSquared();
	if (s > 0) {
		T invL = static_cast<T>(1) / eve::math::sqrt(s);
		return eve::math::TVec2<T>(x * invL, y * invL);
	}
	else
		return eve::math::TVec2<T>::zero();
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::rotate(T radians)
{
	T cosa = eve::math::cos(radians);
	T sina = eve::math::sin(radians);
	T rx = x * cosa - y * sina;
	y = x * sina + y * cosa;
	x = rx;
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec2<T>::lengthSquared(void) const
{
	return x * x + y * y;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::limit(T maxLength)
{
	T lengthSquared = x * x + y * y;

	if ((lengthSquared > maxLength * maxLength) && (lengthSquared > 0)) {
		T ratio = maxLength / eve::math::sqrt(lengthSquared);
		x *= ratio;
		y *= ratio;
	}
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::limited(T maxLength) const
{
	T lengthSquared = x * x + y * y;

	if ((lengthSquared > maxLength * maxLength) && (lengthSquared > 0)) 
	{
		T ratio = maxLength / eve::math::sqrt(lengthSquared);
		return eve::math::TVec2<T>(x * ratio, y * ratio);
	}
	else
		return *this;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::invert(void)
{
	x = -x;
	y = -y;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::inverted(void) const
{
	return eve::math::TVec2<T>(-x, -y);
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::lerp(T fact, const eve::math::TVec2<T>& r) const
{
	return (*this) + (r - (*this)) * fact;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec2<T>::lerpEq(T fact, const eve::math::TVec2<T> &rhs)
{
	x = x + (rhs.x - x) * fact; y = y + (rhs.y - y) * fact;
}

template<typename T>
EVE_FORCE_INLINE static bool eve::math::TVec2<T>::equal(eve::math::TVec2<T> const & x, eve::math::TVec2<T> const & y)
{
	return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y));
}

template<typename T>
EVE_FORCE_INLINE static bool eve::math::TVec2<T>::equal(eve::math::TVec2<T> const & x, eve::math::TVec2<T> const & y, T epsilon)
{
	return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon));
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec2<T>::equal(eve::math::TVec2<T> const & other)
{
	return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y));
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec2<T>::equal(eve::math::TVec2<T> const & other, T epsilon)
{
	return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon));
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::xx(void) const { return eve::math::TVec2<T>(x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::xy(void) const { return eve::math::TVec2<T>(x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::yx(void) const { return eve::math::TVec2<T>(y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec2<T>::yy(void) const { return eve::math::TVec2<T>(y, y); }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::xxx(void) const { return eve::math::TVec3<T>(x, x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::xxy(void) const { return eve::math::TVec3<T>(x, x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::xyx(void) const { return eve::math::TVec3<T>(x, y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::xyy(void) const { return eve::math::TVec3<T>(x, y, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::yxx(void) const { return eve::math::TVec3<T>(y, x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::yxy(void) const { return eve::math::TVec3<T>(y, x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::yyx(void) const { return eve::math::TVec3<T>(y, y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec2<T>::yyy(void) const { return eve::math::TVec3<T>(y, y, y); }



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::max(void)
{
	return eve::math::TVec2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::zero(void)
{
	return eve::math::TVec2<T>(0, 0);
}

template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::one(void)
{
	return eve::math::TVec2<T>(1, 1);
}


template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::xAxis(void)	{ return eve::math::TVec2<T>(1, 0); }
template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::yAxis(void)	{ return eve::math::TVec2<T>(0, 1); }


template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::xAxisNeg(void)	{ return eve::math::TVec2<T>(-1, 0); }
template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::yAxisNeg(void)	{ return eve::math::TVec2<T>(0, -1); }

template<typename T>
EVE_FORCE_INLINE static eve::math::TVec2<T> eve::math::TVec2<T>::NaN(void)		{ return eve::math::TVec2<T>(eve::math::NaN(), eve::math::NaN()); }

#endif // __EVE_MATH_TVECTOR_2_H__
