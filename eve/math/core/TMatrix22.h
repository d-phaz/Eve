
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

#if !defined(__EVE_MATH_CORE_TMATRIX_H__)
#error "Do not include this header directly, include eve/math/TMatrix.h instead"
#endif

#pragma once
#ifndef __EVE_MATH_CORE_TMATRIX_22_H__
#define __EVE_MATH_CORE_TMATRIX_22_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif


namespace eve
{
	namespace math
	{
		/**
		* \class eve::math::TMatrix22
		*
		* \brief Template 2x2 components matrix.
		*/
		template< class T >
		class TMatrix22
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			static const size_t DIM		= 2;
			static const size_t DIM_SQ  = DIM*DIM;
			static const size_t MEM_LEN = sizeof(T)*DIM_SQ;

			//
			// This class is OpenGL friendly and stores the m as how OpenGL would expect it.
			// m[i,j]:
			// | m[0,0] m[0,1] |
			// | m[1,0] m[1,1] |
			//
			// m[idx]
			// | m[0] m[2] |
			// | m[1] m[3] |
			//
			union {
				T m[4];
				struct {
					// This looks like it's transposed from the above, but it's really not.
					// It just has to be written this way so it follows the right ordering
					// in the memory layout as well as being mathematically correct.
					T m00, m10;
					T m01, m11;
				};
			};


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			/** \brief Class default constructor, construct identity matrix. */
			TMatrix22(void);
			/** \brief Class constructor. */
			TMatrix22(T s);

			// OpenGL layout - unless srcIsRowMajor is true
			TMatrix22(const T * dt, bool srcIsRowMajor = false);

			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2, m[3]=d3 - unless srcIsRowMajor is true
			TMatrix22(T d0, T d1, T d2, T d3, bool srcIsRowMajor = false);

			// Creates matrix with column vectors vx and vy
			TMatrix22(const eve::math::TVec2<T> & vx, const eve::math::TVec2<T> & vy);

			template< class FromT >
			TMatrix22(const TMatrix22<FromT> & src);

			TMatrix22(const TMatrix22<T> & src);

			operator T*() { return reinterpret_cast<T*>(m); }
			operator const T*() const { return const_cast<T*>(m); }

			TMatrix22<T>&		operator=(const TMatrix22<T>& rhs);
			TMatrix22<T>&		operator=(const T &rhs);

			template< class FromT >
			TMatrix22<T>&		operator=(const TMatrix22<FromT>& rhs);

			bool				equalCompare(const TMatrix22<T>& rhs, T epsilon) const;
			bool				operator==(const TMatrix22<T> &rhs) const { return equalCompare(rhs, (T)EVE_MATH_EPSILON); }
			bool				operator!=(const TMatrix22<T> &rhs) const { return !(*this == rhs); }

			TMatrix22<T>&		operator*=(const TMatrix22<T> &rhs);
			TMatrix22<T>&		operator+=(const TMatrix22<T> &rhs);
			TMatrix22<T>&		operator-=(const TMatrix22<T> &rhs);

			TMatrix22<T>&		operator*=(T s);
			TMatrix22<T>&		operator/=(T s);
			TMatrix22<T>&		operator+=(T s);
			TMatrix22<T>&		operator-=(T s);

			const TMatrix22<T>	operator*(const TMatrix22<T> & rhs) const;
			const TMatrix22<T>	operator+(const TMatrix22<T> & rhs) const;
			const TMatrix22<T>	operator-(const TMatrix22<T> & rhs) const;

			// post-multiplies column vector [rhs.x rhs.y]
			const TVec2<T>		operator*(const TVec2<T> &rhs) const;

			const TMatrix22<T>	operator*(T rhs) const;
			const TMatrix22<T>	operator/(T rhs) const;
			const TMatrix22<T>	operator+(T rhs) const;
			const TMatrix22<T>	operator-(T rhs) const;

			// Accessors
			T&					at(int32_t row, int32_t col);
			const T&			at(int32_t row, int32_t col) const;

			// OpenGL layout - unless srcIsRowMajor is true
			void				set(const T * dt, bool srcIsRowMajor = false);
			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2, m[3]=d3 - unless srcIsRowMajor is true
			void				set(T d0, T d1, T d2, T d3, bool srcIsRowMajor = false);

			TVec2<T>			getColumn(int32_t col) const;
			void				setColumn(int32_t col, const eve::math::TVec2<T> &v);

			TVec2<T>			getRow(int32_t row) const;
			void				setRow(int32_t row, const eve::math::TVec2<T> &v);

			void				getColumns(eve::math::TVec2<T> *c0, eve::math::TVec2<T> *c1) const;
			void				setColumns(const eve::math::TVec2<T> &c0, const eve::math::TVec2<T> &c1);

			void				getRows(eve::math::TVec2<T> * r0, eve::math::TVec2<T> * r1) const;
			void				setRows(const eve::math::TVec2<T> & r0, const eve::math::TVec2<T> & r1);

			void				setToNull(void);
			void				setToIdentity(void);

			T					determinant(void) const;
			T					trace(void) const;

			TMatrix22<T>        diagonal(void) const;

			TMatrix22<T>		lowerTriangular(void) const;
			TMatrix22<T>		upperTriangular(void) const;

			void				transpose(void);
			TMatrix22<T>		transposed(void) const;

			void				invert(T epsilon = EVE_MATH_EPSILON) { *this = inverted(epsilon); }
			TMatrix22<T>		inverted(T epsilon = EVE_MATH_EPSILON) const;

			// pre-multiplies row vector v - no divide by w
			eve::math::TVec2<T>	preMultiply(const eve::math::TVec2<T> &v) const;

			// post-multiplies column vector v - no divide by w
			eve::math::TVec2<T>	postMultiply(const eve::math::TVec2<T> &v) const;

			// post-multiplies column vector [rhs.x rhs.y]
			eve::math::TVec2<T>	transformVec(const eve::math::TVec2<T> &v) const { return postMultiply(v); }

			// rotate by radians (conceptually, rotate is before 'this')
			void				rotate(T radians) { TMatrix22 rot = createRotation(radians); TMatrix22 mat = *this; *this = rot*mat; }

			// concatenate scale (conceptually, scale is before 'this')
			void				scale(T s) { TMatrix22 sc = createScale(s); TMatrix22 mat = *this; *this = sc*mat; }
			void				scale(const eve::math::TVec2<T> & v) { TMatrix22 sc = createScale(v); TMatrix22 mat = *this; *this = sc*mat; }

			// transposes rotation sub-matrix and inverts translation
			TMatrix22<T>		invertTransform(void) const;

			// returns an identity matrix
			static TMatrix22<T>	identity(void) { return TMatrix22(1, 0, 0, 1); }
			// returns 1 filled matrix
			static TMatrix22<T> one(void) { return TMatrix22((T)1); }
			// returns 0 filled matrix
			static TMatrix22<T> zero(void) { return TMatrix22((T)0); }

			// creates rotation matrix
			static TMatrix22<T>	createRotation(T radians);

			// creates scale matrix
			static TMatrix22<T>	createScale(T s);
			static TMatrix22<T>	createScale(const eve::math::TVec2<T> & v);

		}; // class TMatrix22

	} // namespace math

} // namespace eve


//=================================================================================================
template< class T >
eve::math::TMatrix22<T>::TMatrix22(void)
{
	setToIdentity();
}

template< class T >
eve::math::TMatrix22<T>::TMatrix22(T s)
{
	for (int32_t i = 0; i < DIM_SQ; ++i) {
		m[i] = s;
	}
}

template< class T >
eve::math::TMatrix22<T>::TMatrix22(const T *dt, bool srcIsRowMajor)
{
	set( dt, srcIsRowMajor );
}

template< class T >
eve::math::TMatrix22<T>::TMatrix22(T d0, T d1, T d2, T d3, bool srcIsRowMajor)
{
	set( d0, d1, d2, d3, srcIsRowMajor );
}

template< class T >
eve::math::TMatrix22<T>::TMatrix22(const eve::math::TVec2<T> & vx, const eve::math::TVec2<T> & vy)
{
	m00 = vx.x; m01 = vy.x;
	m10 = vx.y; m11 = vy.y;
}

template< class T >
template< class FromT >
eve::math::TMatrix22<T>::TMatrix22(const eve::math::TMatrix22<FromT>& src)
{
// 	for( int32_t i = 0; i < DIM_SQ; ++i ) {
// 		m[i] = static_cast<T>( src.m[i] );
// 	}
	m00 = static_cast<T>(src.m00); m01 = static_cast<T>(src.m01);
	m10 = static_cast<T>(src.m10); m11 = static_cast<T>(src.m11);
}

template< class T >
eve::math::TMatrix22<T>::TMatrix22(const eve::math::TMatrix22<T> & src)
{
	std::memcpy( m, src.m, MEM_LEN );
}



//=================================================================================================
template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator=(const eve::math::TMatrix22<T>& rhs)
{
	std::memcpy( m, rhs.m, MEM_LEN );
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator=(const T & rhs)
{
	//for( int32_t i = 0; i < DIM_SQ; ++i ) {
	//	m[i] = rhs;
	//}
	std::memset(m, rhs, MEM_LEN);
	return *this;
}

template< class T >
template< class FromT >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator=(const eve::math::TMatrix22<FromT> & rhs)
{
	//for( int32_t i = 0; i < DIM_SQ; i++ ) {
	//	m[i] = static_cast<T>(rhs.m[i]);
	//}
	m00 = static_cast<T>(rhs.m00); m01 = static_cast<T>(rhs.m01);
	m10 = static_cast<T>(rhs.m10); m11 = static_cast<T>(rhs.m11);
	return *this;
}



//=================================================================================================
template< class T >
bool eve::math::TMatrix22<T>::equalCompare(const eve::math::TMatrix22<T> & rhs, T epsilon) const
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		T diff = eve::math::abs(m[i] - rhs.m[i]);
		if( diff >= epsilon )
			return false;
	}
	return true;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator*=(const eve::math::TMatrix22<T> & rhs)
{
	TMatrix22<T> mat;

	mat.m[0] = m[0]*rhs.m[0] + m[2]*rhs.m[1];
	mat.m[1] = m[1]*rhs.m[0] + m[3]*rhs.m[1];

	mat.m[2] = m[0]*rhs.m[2] + m[2]*rhs.m[3];
	mat.m[3] = m[1]*rhs.m[2] + m[3]*rhs.m[3];

	*this = mat;

	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator+=(const eve::math::TMatrix22<T> & rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += rhs.m[i];
	}
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator-=(const eve::math::TMatrix22<T> &rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= rhs.m[i];
	}
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator*=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= s;
	}
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator/=(T s)
{
	T invS = (T)1/s;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= invS;
	}
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator+=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += s;
	}
	return *this;
}

template< class T >
eve::math::TMatrix22<T> & eve::math::TMatrix22<T>::operator-=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= s;
	}
	return *this;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator*(const eve::math::TMatrix22<T> & rhs) const
{
	eve::math::TMatrix22<T> ret;

	ret.m[0] = m[0]*rhs.m[0] + m[2]*rhs.m[1];
	ret.m[1] = m[1]*rhs.m[0] + m[3]*rhs.m[1];

	ret.m[2] = m[0]*rhs.m[2] + m[2]*rhs.m[3];
	ret.m[3] = m[1]*rhs.m[2] + m[3]*rhs.m[3];

	return ret;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator+(const eve::math::TMatrix22<T> & rhs) const
{
	eve::math::TMatrix22<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs.m[i];
	}
	return ret;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator-(const eve::math::TMatrix22<T> & rhs) const
{
	eve::math::TMatrix22<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs.m[i];
	}
	return ret;
}

template< class T >
const eve::math::TVec2<T> eve::math::TMatrix22<T>::operator*(const eve::math::TVec2<T> & rhs) const
{
	return eve::math::TVec2<T>(m[0] * rhs.x + m[2] * rhs.y,
							   m[1] * rhs.x + m[3] * rhs.y );
}


template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator*(T rhs) const
{
	eve::math::TMatrix22<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*rhs;
	}
	return ret;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator/(T rhs) const
{
	eve::math::TMatrix22<T> ret;
	T s = (T)1/rhs;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*s;
	}
	return ret;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator+(T rhs) const
{
	eve::math::TMatrix22<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs;
	}
	return ret;
}

template< class T >
const eve::math::TMatrix22<T> eve::math::TMatrix22<T>::operator-(T rhs) const
{
	eve::math::TMatrix22<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs;
	}
	return ret;
}

template< class T >
T & eve::math::TMatrix22<T>::at(int32_t row, int32_t col)
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}

template< class T >
const T & eve::math::TMatrix22<T>::at(int32_t row, int32_t col) const
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}

template< class T >
void eve::math::TMatrix22<T>::set(const T *dt, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m00 = dt[0]; m01 = dt[2];
		m10 = dt[1]; m11 = dt[3];
	}
	else {
		std::memcpy( m, dt, MEM_LEN );
	}
}

template< class T >
void eve::math::TMatrix22<T>::set(T d0, T d1, T d2, T d3, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m[0] = d0; m[2] = d1;
		m[1] = d2; m[3] = d3;
	} 
	else {
		m[0] = d0; m[2] = d2;
		m[1] = d1; m[3] = d3;
	}
}

template< class T >
eve::math::TVec2<T> eve::math::TMatrix22<T>::getColumn(int32_t col) const
{
	size_t i = col*DIM;
	return eve::math::TVec2<T>(m[i + 0], m[i + 1]);
}

template< class T >
void eve::math::TMatrix22<T>::setColumn(int32_t col, const eve::math::TVec2<T> &v)
{
	size_t i = col*DIM;
	m[i + 0] = v.x;
	m[i + 1] = v.y;
}

template< class T >
eve::math::TVec2<T> eve::math::TMatrix22<T>::getRow(int32_t row) const
{ 
	return TVec2<T>(m[row + 0], m[row + 2]); 
}

template< class T >
void eve::math::TMatrix22<T>::setRow(int32_t row, const eve::math::TVec2<T> &v)
{ 
	m[row + 0] = v.x; 
	m[row + 2] = v.y;
}

template< class T >
void eve::math::TMatrix22<T>::getColumns(eve::math::TVec2<T> *c0, eve::math::TVec2<T> *c1) const
{
	*c0 = getColumn( 0 );
	*c1 = getColumn( 1 );
}

template< class T >
void eve::math::TMatrix22<T>::setColumns(const eve::math::TVec2<T> &c0, const eve::math::TVec2<T> &c1)
{
	setColumn( 0, c0 );
	setColumn( 1, c1 );
}

template< class T >
void eve::math::TMatrix22<T>::getRows(eve::math::TVec2<T> *r0, eve::math::TVec2<T> *r1) const
{
	*r0 = getRow( 0 );
	*r1 = getRow( 1 );
}

template< class T >
void eve::math::TMatrix22<T>::setRows(const eve::math::TVec2<T> &r0, const eve::math::TVec2<T> &r1)
{
	setRow( 0, r0 );
	setRow( 1, r1 );
}

template< class T >
void eve::math::TMatrix22<T>::setToNull(void)
{
	std::memset( m, 0, MEM_LEN );
}

template< class T >
void eve::math::TMatrix22<T>::setToIdentity(void)
{
	m00 = 1; m01 = 0;
	m10 = 0; m11 = 1;
}

template< class T >
T eve::math::TMatrix22<T>::determinant(void) const
{
	T det  = m[0]*m[3] - m[1]*m[2];
	return det;
}

template< class T >
T eve::math::TMatrix22<T>::trace(void) const
{
	return m00 + m11;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::diagonal(void) const
{
	eve::math::TMatrix22 ret;
	ret.m00 = m00; ret.m01 =   0;
	ret.m10 =   0; ret.m11 = m11;
	return ret;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::lowerTriangular(void) const
{
	eve::math::TMatrix22 ret;
	ret.m00 = m00; ret.m01 =   0;
	ret.m10 = m10; ret.m11 = m11;	
	return ret;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::upperTriangular(void) const
{
	eve::math::TMatrix22 ret;
	ret.m00 = m00; ret.m01 = m01;
	ret.m10 =   0; ret.m11 = m11;
	return ret;
}

template< class T >
void eve::math::TMatrix22<T>::transpose(void)
{
	T t;
	t = m01; m01 = m10; m10 = t;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::transposed(void) const
{
	return eve::math::TMatrix22<T>(m[ 0], m[ 2],
								   m[ 1], m[ 3]);
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::inverted(T epsilon) const
{
	eve::math::TMatrix22<T> inv((T)0);

	T det = m[0]*m[3] - m[1]*m[2];

	if (eve::math::abs(det) > epsilon) {
		T invDet = static_cast<T>(1)/det;
		inv.m[0] =  m[3]*invDet;
		inv.m[1] = -m[1]*invDet;
		inv.m[2] = -m[2]*invDet;
		inv.m[3] =  m[0]*invDet;
	}

	return inv;
}

template< class T >
eve::math::TVec2<T> eve::math::TMatrix22<T>::preMultiply(const eve::math::TVec2<T> &v) const
{
	return eve::math::TVec2<T>(v.x*m00 + v.y*m10,
							   v.x*m01 + v.y*m11);
}

template< class T >
eve::math::TVec2<T> eve::math::TMatrix22<T>::postMultiply(const eve::math::TVec2<T> &v) const
{
	return eve::math::TVec2<T>(m00*v.x + m01*v.y,
							   m10*v.x + m11*v.y);
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::invertTransform(void) const
{
	eve::math::TMatrix22<T> ret;

	// transpose rotation part
	for( int32_t i = 0; i < DIM; i++ ) {
		for( int32_t j = 0; j < DIM; j++ ) {
			ret.at( j, i ) = at( i, j );
		}
	}

	return ret;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::createRotation(T radians)
{
	eve::math::TMatrix22<T> ret;
	T ac = eve::math::cos(radians);
	T as = eve::math::sin(radians);
	ret.m00 =  ac; ret.m01 = as;
	ret.m10 = -as; ret.m11 = ac;
	return ret;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::createScale(T s)
{
	eve::math::TMatrix22<T> ret;
	ret.m00 = s; ret.m01 = 0;
	ret.m10 = 0; ret.m11 = s;
	return ret;
}

template< class T >
eve::math::TMatrix22<T> eve::math::TMatrix22<T>::createScale(const eve::math::TVec2<T> &v)
{
	eve::math::TMatrix22<T> ret;
	ret.m00 = v.x; ret.m01 =   0;
	ret.m10 =   0; ret.m11 = v.y;
	return ret;
}

#endif // __EVE_MATH_CORE_TMATRIX_22_H__
