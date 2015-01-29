
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
#ifndef __EVE_MATH_CORE_TVECTOR_3_H__
#define __EVE_MATH_CORE_TVECTOR_3_H__

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
		template<class T> class TVec4;

		/**
		* \class eve::math::TVec3
		*
		* \brief Template 3 components vector.
		*/
		template<typename T>
		class TVec3
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			T x;
			T y;
			T z;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TVec3(void);
			TVec3(T nx, T ny, T nz);
			TVec3(const TVec3<T> &src);
			TVec3(const TVec4<T> &src);
			TVec3(const TVec2<T> &v2, T aZ);
			explicit TVec3(const TVec2<T> &v2);
			explicit TVec3(const T *d);
			template<typename FromT>
			TVec3(const TVec3<FromT> &src);


			void set(T ax, T ay, T az);
			void set(const TVec3<T> &rhs);


			TVec3<T>& operator=(const TVec3<T> &rhs);

			template<typename FromT>
			TVec3<T>& operator=(const TVec3<FromT> &rhs);

			T & operator[](int32_t n);
			const T & operator[](int32_t n) const;

			T*	ptr(void) const;


			const TVec3<T>	operator+(const TVec3<T>& rhs) const;
			const TVec3<T>	operator-(const TVec3<T>& rhs) const;
			const TVec3<T>	operator*(const TVec3<T>& rhs) const;
			const TVec3<T>	operator/(const TVec3<T>& rhs) const;
			TVec3<T>&	operator+=(const TVec3<T>& rhs);
			TVec3<T>&	operator-=(const TVec3<T>& rhs);
			TVec3<T>&	operator*=(const TVec3<T>& rhs);
			TVec3<T>&	operator/=(const TVec3<T>& rhs);

			const TVec3<T>	operator+(T rhs) const;
			const TVec3<T>	operator-(T rhs) const;
			const TVec3<T>	operator*(T rhs) const;
			const TVec3<T>	operator/(T rhs) const;
			TVec3<T>&	operator+=(T rhs);
			TVec3<T>&	operator-=(T rhs);
			TVec3<T>&	operator*=(T rhs);
			TVec3<T>&	operator/=(T rhs);

			TVec3<T>		operator-() const;


			bool operator==(const TVec3<T>& rhs) const;
			bool operator!=(const TVec3<T>& rhs) const;


			T dot(const TVec3<T> &rhs) const;
			EVE_FORCE_INLINE static T dot(TVec3<T> const & x, TVec3<T> const & y);

			TVec3<T> cross(const TVec3<T> &rhs) const;
			static TVec3<T> cross( TVec3<T> const & x, TVec3<T> const & y );

			static bool equal(TVec3<T> const & x, TVec3<T> const & y);
			static bool equal(TVec3<T> const & x, TVec3<T> const & y, T epsilon);

			inline bool equal(TVec3<T> const & other);
			inline bool equal(TVec3<T> const & other, T epsilon);


			EVE_FORCE_INLINE static TVec3<T> normalize(const TVec3<T> & p_v);


			T distance(const TVec3<T> &rhs) const;

			T distanceSquared(const TVec3<T> &rhs) const;

			T length(void) const;
			T lengthSquared(void) const;

			//! Limits the length of a TVec3 to \a maxLength, scaling it proportionally if necessary.
			void limit(T maxLength);
			//! Returns a copy of the TVec3 with its length limited to \a maxLength, scaling it proportionally if necessary.
			TVec3<T> limited(T maxLength) const;

			void invert(void);
			TVec3<T> inverted(void) const;

			void normalize(void);
			TVec3<T> normalized(void) const;

			// tests for zero-length
			void safeNormalize(void);
			TVec3<T> safeNormalized(void) const;

			//! Returns a vector which is orthogonal to \a this
			TVec3<T> getOrthogonal(void) const;

			void rotateX(T angle);
			void rotateY(T angle);
			void rotateZ(T angle);
			void rotate(TVec3<T> axis, T angle);

			TVec3<T> lerp(T fact, const TVec3<T> &rhs) const;

			void lerpEq(T fact, const TVec3<T> &rhs);

			void rotateAroundAxis(const TVec3<T> & axis, T angle);



			//Rotate vector v around arbitrary axis, axis for angle radians
			//It can only rotate around an axis through our object, to rotate around another axis:
			//first translate the object to the axis, then use this function, then translate back in the new direction.
			static TVec3<T> rotate_around_axis(const TVec3<T> & v, const TVec3<T> & axis, T angle);

			//<! Gives the angle between two 3D vectors (in radians)
			static T angle(const TVec3<T> & v, const TVec3<T> & w);

			static T LengthSquared(const TVec3<T> &rhs);

			static TVec3<T> max(void);

			static TVec3<T> zero(void);

			static TVec3<T> one(void);

			static TVec3<T> view_direction(void);

			static TVec3<T> world_up(void);


			TVec3<T> slerp(T fact, const TVec3<T> &r) const;

			// derived from but not equivalent to Quaternion::squad
			TVec3<T> squad(T t, const TVec3<T> &tangentA, const TVec3<T> &tangentB, const TVec3<T> &end) const;


			// GLSL inspired swizzling functions.
			TVec2<T> xx(void) const;
			TVec2<T> xy(void) const;
			TVec2<T> xz(void) const;
			TVec2<T> yx(void) const;
			TVec2<T> yy(void) const;
			TVec2<T> yz(void) const;
			TVec2<T> zx(void) const;
			TVec2<T> zy(void) const;
			TVec2<T> zz(void) const;

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

			static TVec3<T> xAxis(void);
			static TVec3<T> yAxis(void);
			static TVec3<T> zAxis(void);

			static TVec3<T> xAxisNeg(void);
			static TVec3<T> yAxisNeg(void);
			static TVec3<T> zAxisNeg(void);

			static TVec3<T> NaN(void);
		};

	} // namespace math

} // namespace eve


//=================================================================================================
template<typename T>
eve::math::TVec3<T>::TVec3(void) 
	: x(0)
	, y(0)
	, z(0) 
{}

template<typename T>
eve::math::TVec3<T>::TVec3(T nx, T ny, T nz)
	: x(nx)
	, y(ny)
	, z(nz)
{}

template<typename T>
eve::math::TVec3<T>::TVec3(const eve::math::TVec3<T> & src)
	: x(src.x)
	, y(src.y)
	, z(src.z)
{}

template<typename T>
eve::math::TVec3<T>::TVec3(const eve::math::TVec4<T> & src)
	: x(src.x)
	, y(src.y)
	, z(src.z)
{}

template<typename T>
eve::math::TVec3<T>::TVec3(const eve::math::TVec2<T> & v2, T aZ)
	: x(v2.x)
	, y(v2.y)
	, z(aZ)
{}

template<typename T>
eve::math::TVec3<T>::TVec3(const eve::math::TVec2<T> & v2)
	: x(v2.x)
	, y(v2.y)
	, z(0)
{}

template<typename T>
eve::math::TVec3<T>::TVec3(const T * d) 
	: x(d[0])
	, y(d[1])
	, z(d[2]) 
{}

template<typename T>
template<typename FromT>
eve::math::TVec3<T>::TVec3(const eve::math::TVec3<FromT> & src)
	: x(static_cast<T>(src.x))
	, y(static_cast<T>(src.y))
	, z(static_cast<T>(src.z))
{}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::set(T ax, T ay, T az)
{
	x = ax; y = ay; z = az;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::set(const eve::math::TVec3<T> & rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z;
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> & eve::math::TVec3<T>::operator=(const eve::math::TVec3<T> & rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

template<typename T>
template<typename FromT>
EVE_FORCE_INLINE eve::math::TVec3<T> & eve::math::TVec3<T>::operator=(const eve::math::TVec3<FromT> & rhs)
{
	x = static_cast<T>(rhs.x);
	y = static_cast<T>(rhs.y);
	z = static_cast<T>(rhs.z);
	return *this;
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE T & eve::math::TVec3<T>::operator[](int32_t n)
{
	EVE_ASSERT(n >= 0 && n <= 2);
	return (&x)[n];
}

template<typename T>
EVE_FORCE_INLINE const T & eve::math::TVec3<T>::operator[](int32_t n) const
{
	EVE_ASSERT(n >= 0 && n <= 2);
	return (&x)[n];
}

template<typename T>
EVE_FORCE_INLINE T *	eve::math::TVec3<T>::ptr(void) const
{ 
	return &(const_cast<eve::math::TVec3<T>*>(this)->x); 
}



//=================================================================================================
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator+(const eve::math::TVec3<T>& rhs) const { return eve::math::TVec3<T>(x + rhs.x, y + rhs.y, z + rhs.z); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator-(const eve::math::TVec3<T>& rhs) const { return eve::math::TVec3<T>(x - rhs.x, y - rhs.y, z - rhs.z); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator*(const eve::math::TVec3<T>& rhs) const { return eve::math::TVec3<T>(x * rhs.x, y * rhs.y, z * rhs.z); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator/(const eve::math::TVec3<T>& rhs) const { return eve::math::TVec3<T>(x / rhs.x, y / rhs.y, z / rhs.z); }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator+=(const eve::math::TVec3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator-=(const eve::math::TVec3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator*=(const eve::math::TVec3<T>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator/=(const eve::math::TVec3<T>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }


template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator+(T rhs) const { return eve::math::TVec3<T>(x + rhs, y + rhs, z + rhs); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator-(T rhs) const { return eve::math::TVec3<T>(x - rhs, y - rhs, z - rhs); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator*(T rhs) const { return eve::math::TVec3<T>(x * rhs, y * rhs, z * rhs); }
template<typename T>
EVE_FORCE_INLINE const eve::math::TVec3<T>	eve::math::TVec3<T>::operator/(T rhs) const { return eve::math::TVec3<T>(x / rhs, y / rhs, z / rhs); }

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator+=(T rhs) { x += rhs; y += rhs; z += rhs; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator-=(T rhs) { x -= rhs; y -= rhs; z -= rhs; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator*=(T rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>&	eve::math::TVec3<T>::operator/=(T rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }


template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T>		eve::math::TVec3<T>::operator-() const { return eve::math::TVec3<T>(-x, -y, -z); } // unary negation



template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::operator==(const eve::math::TVec3<T>& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::operator!=(const eve::math::TVec3<T>& rhs) const
{
	return !(*this == rhs);
}



template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::dot(const eve::math::TVec3<T> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::dot(eve::math::TVec3<T> const & x, eve::math::TVec3<T> const & y)
{
	return x.x * y.x + x.y * y.y;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::cross(const eve::math::TVec3<T> &rhs) const
{
	return TVec3<T>(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y);
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::cross(eve::math::TVec3<T> const & x, eve::math::TVec3<T> const & y)
{
	return eve::math::TVec3<T>( x.y * y.z - y.y * x.z,
								x.z * y.x - y.z * x.x,
								x.x * y.y - y.x * x.y);
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::equal(eve::math::TVec3<T> const & x, eve::math::TVec3<T> const & y)
{
	return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y) && eve::math::equal(x.z, y.z));
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::equal(eve::math::TVec3<T> const & x, eve::math::TVec3<T> const & y, T epsilon)
{
	return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon) && eve::math::equal(x.z, y.z, epsilon));
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::equal(eve::math::TVec3<T> const & other)
{
	return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y) && eve::math::equal(z, other.z));
}

template<typename T>
EVE_FORCE_INLINE bool eve::math::TVec3<T>::equal(eve::math::TVec3<T> const & other, T epsilon)
{
	return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon) && eve::math::equal(z, other.z, epsilon));
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::normalize(const eve::math::TVec3<T> & p_v)
{
	T length = eve::math::sqrt(p_v.x*p_v.x + p_v.y*p_v.y + p_v.z*p_v.z);

	T invS = 1.0f / length;

	return eve::math::TVec3<T>(p_v.x * invS, p_v.y * invS, p_v.z * invS);
}

template<typename T>
T eve::math::TVec3<T>::distance(const eve::math::TVec3<T> &rhs) const
{
	return (*this - rhs).length();
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::distanceSquared(const eve::math::TVec3<T> &rhs) const
{
	return (*this - rhs).lengthSquared();
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::length(void) const
{
	return eve::math::sqrt(x*x + y*y + z*z);
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::lengthSquared(void) const
{
	return x*x + y*y + z*z;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::limit(T maxLength)
{
	T lengthSquared = x * x + y * y + z * z;

	if ((lengthSquared > maxLength * maxLength) && (lengthSquared > 0)) {
		T ratio = maxLength / eve::math::sqrt(lengthSquared);
		x *= ratio;
		y *= ratio;
		z *= ratio;
	}
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::limited(T maxLength) const
{
	T lengthSquared = x * x + y * y + z * z;

	if ((lengthSquared > maxLength * maxLength) && (lengthSquared > 0)) {
		T ratio = maxLength / eve::math::sqrt(lengthSquared);
		return TVec3<T>(x * ratio, y * ratio, z * ratio);
	}
	else
		return *this;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::invert(void)
{
	x = -x; y = -y; z = -z;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::inverted(void) const
{
	return eve::math::TVec3<T>(-x, -y, -z);
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::normalize(void)
{
	T invS = ((T)1) / length();
	x *= invS;
	y *= invS;
	z *= invS;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::normalized(void) const
{
	T invS = ((T)1) / length();
	return eve::math::TVec3<T>(x * invS, y * invS, z * invS);
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::safeNormalize(void)
{
	T s = lengthSquared();
	if (s > 0) {
		T invS = static_cast<T>(1) / eve::math::sqrt(s);
		x *= invS;
		y *= invS;
		z *= invS;
	}
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::safeNormalized(void) const
{
	T s = lengthSquared();
	if (s > 0) 
	{
		float invS = static_cast<T>(1) / eve::math::sqrt(s);
		return eve::math::TVec3<T>(x * invS, y * invS, z * invS);
	}
	else
		return *this;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::getOrthogonal(void) const
{
	if (eve::math::abs(y) < static_cast<T>(0.99)) // abs(dot(u, Y)), somewhat arbitrary epsilon
		return eve::math::TVec3<T>(-z, 0, x); // cross( this, Y )
	else
		return eve::math::TVec3<T>(0, z, -y); // cross( this, X )
}



template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::rotateX(T angle)
{
	T sina = eve::math::sin(angle);
	T cosa = eve::math::cos(angle);
	T ry = y * cosa - z * sina;
	T rz = y * sina + z * cosa;
	y = ry;
	z = rz;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::rotateY(T angle)
{
	T sina = eve::math::sin(angle);
	T cosa = eve::math::cos(angle);
	T rx = x * cosa - z * sina;
	T rz = x * sina + z * cosa;
	x = rx;
	z = rz;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::rotateZ(T angle)
{
	T sina = eve::math::sin(angle);
	T cosa = eve::math::cos(angle);
	T rx = x * cosa - y * sina;
	T ry = x * sina + y * cosa;
	x = rx;
	y = ry;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::rotate(TVec3<T> axis, T angle)
{
	T cosa = eve::math::cos(angle);
	T sina = eve::math::sin(angle);

	T rx = (cosa + (1 - cosa) * axis.x * axis.x) * x;
	rx += ((1 - cosa) * axis.x * axis.y - axis.z * sina) * y;
	rx += ((1 - cosa) * axis.x * axis.z + axis.y * sina) * z;

	T ry = ((1 - cosa) * axis.x * axis.y + axis.z * sina) * x;
	ry += (cosa + (1 - cosa) * axis.y * axis.y) * y;
	ry += ((1 - cosa) * axis.y * axis.z - axis.x * sina) * z;

	T rz = ((1 - cosa) * axis.x * axis.z - axis.y * sina) * x;
	rz += ((1 - cosa) * axis.y * axis.z + axis.x * sina) * y;
	rz += (cosa + (1 - cosa) * axis.z * axis.z) * z;

	x = rx;
	y = ry;
	z = rz;
}



template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::lerp(T fact, const TVec3<T> &rhs) const
{
	return (*this) + (rhs - (*this)) * fact;
}

template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::lerpEq(T fact, const TVec3<T> &rhs)
{
	x = x + (rhs.x - x) * fact; y = y + (rhs.y - y) * fact; z = z + (rhs.z - z) * fact;
}



template<typename T>
EVE_FORCE_INLINE void eve::math::TVec3<T>::rotateAroundAxis(const TVec3<T> & axis, T angle)
{
	eve::math::TVec3<T> vec(x, y, z);
	vec = eve::math::TVec3<T>::rotate_around_axis(vec, axis, angle);

	x = vec.x;
	y = vec.y;
	z = vec.z;
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::rotate_around_axis(const eve::math::TVec3<T> & v, const eve::math::TVec3<T> & axis, T angle)
{
	if ((v.x == 0.0) && (v.y == 0.0) && (v.z == 0.0)) { return eve::math::TVec3<T>(); }

	eve::math::TVec3<T> w;
	T c, s, t;

	eve::math::TVec3<T> naxis = axis.normalized();

	// Calculate parameters of the rotation matrix.
	c = eve::math::cos(angle);
	s = eve::math::sin(angle);
	t = 1 - c;

	// Multiply v with rotation matrix.
	w.x = (t * naxis.x * naxis.x + c)			* v.x
		+ (t * naxis.x * naxis.y + s * naxis.z) * v.y
		+ (t * naxis.x * naxis.z - s * naxis.y) * v.z;

	w.y = (t * naxis.x * naxis.y - s * naxis.z) * v.x
		+ (t * naxis.y * naxis.y + c)			* v.y
		+ (t * naxis.y * naxis.z + s * naxis.x) * v.z;

	w.z = (t * naxis.x * naxis.z + s * naxis.y) * v.x
		+ (t * naxis.y * naxis.z - s * naxis.x) * v.y
		+ (t * naxis.z * naxis.z + c)			* v.z;

	w.normalize();
	w = w * v.length();

	return w;
}



template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::angle(const eve::math::TVec3<T> & v, const eve::math::TVec3<T> & w)
{
	// dot product(v,w) = length(v)*length(w)*cos(angle) ==> angle = acos(dot/(length(v)*length(w))) = acos(dot(norm(v)*norm(w)));
	T cosineOfAngle = v.normalized().dot(w.normalized());
	// for acos, the value has to be between -1.0 and 1.0, but due to numerical imprecisions it sometimes comes outside this range
	if (cosineOfAngle > 1.0) { cosineOfAngle = 1.0; }
	if (cosineOfAngle < -1.0) { cosineOfAngle = -1.0; }

	return -eve::math::acos(cosineOfAngle);
}

template<typename T>
EVE_FORCE_INLINE T eve::math::TVec3<T>::LengthSquared(const eve::math::TVec3<T> &rhs)
{
	return rhs.x*rhs.x + rhs.y*rhs.y + rhs.z*rhs.z;
}



template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::max(void)
{
	return eve::math::TVec3<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zero(void)
{
	return eve::math::TVec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::one(void)
{
	return eve::math::TVec3<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::view_direction(void)
{
	return eve::math::TVec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::world_up(void)
{
	return eve::math::TVec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
}

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::slerp(T fact, const eve::math::TVec3<T> &r) const
{
	T cosAlpha, alpha, sinAlpha;
	T t1, t2;
	eve::math::TVec3<T> result;

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

template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::squad(T t, const eve::math::TVec3<T> &tangentA, const eve::math::TVec3<T> &tangentB, const eve::math::TVec3<T> &end) const
{
	eve::math::TVec3<T> r1 = this->slerp(t, end);
	eve::math::TVec3<T> r2 = tangentA.slerp(t, tangentB);
	return r1.slerp(2 * t * (1 - t), r2);
}



template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::xx(void) const { return eve::math::TVec2<T>(x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::xy(void) const { return eve::math::TVec2<T>(x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::xz(void) const { return eve::math::TVec2<T>(x, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::yx(void) const { return eve::math::TVec2<T>(y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::yy(void) const { return eve::math::TVec2<T>(y, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::yz(void) const { return eve::math::TVec2<T>(y, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::zx(void) const { return eve::math::TVec2<T>(z, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::zy(void) const { return eve::math::TVec2<T>(z, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec2<T> eve::math::TVec3<T>::zz(void) const { return eve::math::TVec2<T>(z, z); }



template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xxx(void) const { return eve::math::TVec3<T>(x, x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xxy(void) const { return eve::math::TVec3<T>(x, x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xxz(void) const { return eve::math::TVec3<T>(x, x, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xyx(void) const { return eve::math::TVec3<T>(x, y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xyy(void) const { return eve::math::TVec3<T>(x, y, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xyz(void) const { return eve::math::TVec3<T>(x, y, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xzx(void) const { return eve::math::TVec3<T>(x, z, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xzy(void) const { return eve::math::TVec3<T>(x, z, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xzz(void) const { return eve::math::TVec3<T>(x, z, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yxx(void) const { return eve::math::TVec3<T>(y, x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yxy(void) const { return eve::math::TVec3<T>(y, x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yxz(void) const { return eve::math::TVec3<T>(y, x, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yyx(void) const { return eve::math::TVec3<T>(y, y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yyy(void) const { return eve::math::TVec3<T>(y, y, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yyz(void) const { return eve::math::TVec3<T>(y, y, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yzx(void) const { return eve::math::TVec3<T>(y, z, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yzy(void) const { return eve::math::TVec3<T>(y, z, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yzz(void) const { return eve::math::TVec3<T>(y, z, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zxx(void) const { return eve::math::TVec3<T>(z, x, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zxy(void) const { return eve::math::TVec3<T>(z, x, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zxz(void) const { return eve::math::TVec3<T>(z, x, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zyx(void) const { return eve::math::TVec3<T>(z, y, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zyy(void) const { return eve::math::TVec3<T>(z, y, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zyz(void) const { return eve::math::TVec3<T>(z, y, z); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zzx(void) const { return eve::math::TVec3<T>(z, z, x); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zzy(void) const { return eve::math::TVec3<T>(z, z, y); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zzz(void) const { return eve::math::TVec3<T>(z, z, z); }



template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xAxis(void)		{ return TVec3<T>(1, 0, 0); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yAxis(void)		{ return TVec3<T>(0, 1, 0); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zAxis(void)		{ return TVec3<T>(0, 0, 1); }


template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::xAxisNeg(void)		{ return eve::math::TVec3<T>(-1, 0, 0); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::yAxisNeg(void)		{ return eve::math::TVec3<T>(0, -1, 0); }
template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::zAxisNeg(void)		{ return eve::math::TVec3<T>(0, 0, -1); }


template<typename T>
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TVec3<T>::NaN(void)			{ return eve::math::TVec3<T>(eve::math::NaN(), eve::math::NaN(), eve::math::NaN()); }

#endif // __EVE_MATH_CORE_TVECTOR_3_H__
