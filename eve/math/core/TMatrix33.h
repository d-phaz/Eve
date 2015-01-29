
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
#ifndef __EVE_MATH_CORE_TMATRIX_33_H__
#define __EVE_MATH_CORE_TMATRIX_33_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_22_H__
#include "eve/math/core/TMatrix22.h"
#endif


namespace eve
{
	namespace math
	{
		/**
		* \class eve::math::TMatrix33
		*
		* \brief Template 3x3 components matrix.
		*/

		template< typename T >
		class TMatrix33
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			static const size_t DIM = 3;
			static const size_t DIM_SQ = DIM*DIM;
			static const size_t MEM_LEN = sizeof(T)*DIM_SQ;

			//
			// This class is OpenGL friendly and stores the m as how OpenGL would expect it.
			// m[i,j]:
			// | m[0,0] m[0,1] m[0,2] |
			// | m[1,0] m[1,1] m[1,2] |
			// | m[2,0] m[2,1] m[2,2] |
			//
			// m[idx]
			// | m[0] m[3] m[6] |
			// | m[1] m[4] m[7] |
			// | m[2] m[5] m[8] |
			//
			union {
				T m[9];
				struct {
					// This looks like it's transposed from the above, but it's really not.
					// It just has to be written this way so it follows the right ordering
					// in the memory layout as well as being mathematically correct.
					T m00, m10, m20;
					T m01, m11, m21;
					T m02, m12, m22;
				};
				// [Cols][Rows]
				T mcols[3][3];
			};


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TMatrix33(void);

			TMatrix33(T s);

			// OpenGL layout - unless srcIsRowMajor is true
			TMatrix33(const T *dt, bool srcIsRowMajor = false);

			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2 ... m[6]=d6, m[7]=d7, m[8]=d8 - unless srcIsRowMajor is true
			TMatrix33(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, bool srcIsRowMajor = false);

			// Creates matrix with column vectors vx, vy and z
			TMatrix33(const eve::math::TVec3<T> & vx, const eve::math::TVec3<T> & vy, const eve::math::TVec3<T> & vz);

			template< typename FromT >
			TMatrix33(const TMatrix33<FromT>& src);

			TMatrix33(const TMatrix22<T>& src);

			TMatrix33(const TMatrix33<T>& src);

			operator T*() { return (T*)m; }
			operator const T*() const { return (const T*)m; }
			T * ptr(void) const;

			TMatrix33<T>&		operator=(const TMatrix33<T>& rhs);
			TMatrix33<T>&		operator=(T rhs);

			template< typename FromT >
			TMatrix33<T>&		operator=(const TMatrix33<FromT>& rhs);

			// remaining columns and rows will be filled with identity values
			TMatrix33<T>&		operator=(const TMatrix22<T>& rhs);

			bool				equalCompare(const TMatrix33<T>& rhs, T epsilon) const;
			bool				operator==(const TMatrix33<T> &rhs) const { return equalCompare(rhs, static_cast<T>(EVE_MATH_EPSILON)); }
			bool				operator!=(const TMatrix33<T> &rhs) const { return !(*this == rhs); }

			TMatrix33<T>&		operator*=(const TMatrix33<T> &rhs);
			TMatrix33<T>&		operator+=(const TMatrix33<T> &rhs);
			TMatrix33<T>&		operator-=(const TMatrix33<T> &rhs);

			TMatrix33<T>&		operator*=(T s);
			TMatrix33<T>&		operator/=(T s);
			TMatrix33<T>&		operator+=(T s);
			TMatrix33<T>&		operator-=(T s);

			const TMatrix33<T>	operator*(const TMatrix33<T> &rhs) const;
			const TMatrix33<T>	operator+(const TMatrix33<T> &rhs) const;
			const TMatrix33<T>	operator-(const TMatrix33<T> &rhs) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z]
			const TVec3<T>		operator*(const TVec3<T> &rhs) const;

			const TMatrix33<T>	operator*(T rhs) const;
			const TMatrix33<T>	operator/(T rhs) const;
			const TMatrix33<T>	operator+(T rhs) const;
			const TMatrix33<T>	operator-(T rhs) const;

			// Accessors
			T&					at(int32_t row, int32_t col);
			const T&			at(int32_t row, int32_t col) const;

			// OpenGL layout - unless srcIsRowMajor is true
			void				set(const T *dt, bool srcIsRowMajor = false);
			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2 ... m[6]=d6, m[7]=d7, m[8]=d8 - unless srcIsRowMajor is true
			void				set(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, bool srcIsRowMajor = false);

			eve::math::TVec3<T>	getColumn(int32_t col) const;
			void				setColumn(int32_t col, const TVec3<T> &v);

			eve::math::TVec3<T>	getRow(int32_t row) const;
			void				setRow(int32_t row, const TVec3<T> &v);

			void				getColumns(eve::math::TVec3<T> *c0, eve::math::TVec3<T> *c1, eve::math::TVec3<T> *c2) const;
			void				setColumns(const eve::math::TVec3<T> &c0, const eve::math::TVec3<T> &c1, const eve::math::TVec3<T> &c2);

			void				getRows(eve::math::TVec3<T> *r0, eve::math::TVec3<T> *r1, eve::math::TVec3<T> *r2) const;
			void				setRows(const eve::math::TVec3<T> &r0, const eve::math::TVec3<T> &r1, const eve::math::TVec3<T> &r2);

			// returns a sub-matrix starting at row, col
			inline TMatrix22<T>	subMatrix22(int32_t row, int32_t col) const;

			void				setToNull(void);
			void				setToIdentity(void);

			T					determinant(void) const;
			T					trace(void) const;

			TMatrix33<T>         diagonal(void) const;

			TMatrix33<T>		lowerTriangular(void) const;
			TMatrix33<T>		upperTriangular(void) const;

			void				transpose(void);
			TMatrix33<T>		transposed(void) const;

			void				invert(T epsilon = static_cast<T>(EVE_MATH_EPSILON)) { *this = inverted(epsilon); }
			TMatrix33<T>		inverted(T epsilon = static_cast<T>(EVE_MATH_EPSILON)) const;

			// pre-multiplies row vector v - no divide by w
			eve::math::TVec3<T>	preMultiply(const eve::math::TVec3<T> &v) const;

			// post-multiplies column vector v - no divide by w
			eve::math::TVec3<T>	postMultiply(const eve::math::TVec3<T> &v) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z]
			eve::math::TVec3<T>	transformVec(const eve::math::TVec3<T> &v) const { return postMultiply(v); }

			// rotate by radians on axis (conceptually, rotate is before 'this')
			template <template <typename> class VecT>
			void				rotate(const VecT<T> &axis, T radians) { *this *= TMatrix33<T>::createRotation(axis, radians); }
			// rotate by eulerRadians - Euler angles in radians (conceptually, rotate is before 'this')
			template <template <typename> class VecT>
			void				rotate(const VecT<T> &eulerRadians) { *this *= TMatrix33<T>::createRotation(eulerRadians); }
			// rotate by matrix derives rotation matrix using from, to, worldUp	(conceptually, rotate is before 'this')
			template <template <typename> class VecT>
			void				rotate(const VecT<T> &from, const VecT<T> &to, const VecT<T> &worldUp) { *this *= TMatrix33<T>::createRotation(from, to, worldUp); }

			// transposes rotation sub-matrix and inverts translation
			TMatrix33<T>		invertTransform(void) const;

			// returns an identity matrix
			static TMatrix33<T>	identity(void) { return TMatrix33(1, 0, 0, 0, 1, 0, 0, 0, 1); }
			// returns 1 filled matrix
			static TMatrix33<T> one(void) { return TMatrix33((T)1); }
			// returns 0 filled matrix
			static TMatrix33<T>  zero(void) { return TMatrix33((T)0); }

			// creates rotation matrix
			static TMatrix33<T>	createRotation(const eve::math::TVec3<T> &axis, T radians);
			static TMatrix33<T>	createRotation(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to, const eve::math::TVec3<T> &worldUp);
			// equivalent to rotate( zAxis, z ), then rotate( yAxis, y ) then rotate( xAxis, x )
			static TMatrix33<T>	createRotation(const eve::math::TVec3<T> &eulerRadians);

			// creates scale matrix
			static TMatrix33<T>	createScale(T s);
			static TMatrix33<T>	createScale(const eve::math::TVec2<T> &v);
			static TMatrix33<T>	createScale(const eve::math::TVec3<T> &v);

			// creates a rotation matrix with z-axis aligned to targetDir	
			static TMatrix33<T>	alignZAxisWithTarget(eve::math::TVec3<T> targetDir, eve::math::TVec3<T> upDir);
		
		}; // class TMatrix33

	} // namespace math

} // namespace eve


//=================================================================================================
template< typename T >
eve::math::TMatrix33<T>::TMatrix33(void)
{
	setToIdentity();
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = s;
	}
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(const T *dt, bool srcIsRowMajor)
{
	set( dt, srcIsRowMajor );
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, bool srcIsRowMajor)
{
	set( d0, d1, d2, 
		d3, d4, d5, 
		d6, d7, d8, srcIsRowMajor );
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(const eve::math::TVec3<T> &vx, const eve::math::TVec3<T> &vy, const eve::math::TVec3<T> &vz)
{
	m00 = vx.x; m01 = vy.x; m02 = vz.x;
	m10 = vx.y; m11 = vy.y; m12 = vz.y;
	m20 = vx.z; m21 = vy.z; m22 = vz.z;
}

template< typename T >
template< typename FromT >
eve::math::TMatrix33<T>::TMatrix33(const eve::math::TMatrix33<FromT>& src)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = static_cast<T>( src.m[i] );
	}
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(const eve::math::TMatrix22<T>& src)
{
	setToIdentity();
	m00 = src.m00; m01 = src.m01;
	m10 = src.m10; m11 = src.m11;
}

template< typename T >
eve::math::TMatrix33<T>::TMatrix33(const eve::math::TMatrix33<T>& src)
{
	eve::mem::memcpy(m, src.m, MEM_LEN);
}



//=================================================================================================
template< typename T > EVE_FORCE_INLINE T * eve::math::TMatrix33<T>::ptr(void) const { return const_cast<T*>(m); }



template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator=(const eve::math::TMatrix33<T>& rhs)
{
	eve::mem::memcpy(m, rhs.m, MEM_LEN);
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator=(T rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = rhs;
	}
	return *this;
}

template< typename T >
template< typename FromT >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator=(const eve::math::TMatrix33<FromT> & rhs)
{
	for( int32_t i = 0; i < DIM_SQ; i++ ) {
		m[i] = static_cast<T>(rhs.m[i]);
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator=(const eve::math::TMatrix22<T>& rhs)
{
	setToIdentity();
	m00 = rhs.m00; m01 = rhs.m01;
	m10 = rhs.m10; m11 = rhs.m11;
	return *this;
}

template< typename T >
bool eve::math::TMatrix33<T>::equalCompare(const eve::math::TMatrix33<T> & rhs, T epsilon) const
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		if (eve::math::abs(m[i] - rhs.m[i]) >= epsilon)
			return false;
	}
	return true;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator*=(const eve::math::TMatrix33<T> &rhs)
{
	eve::math::TMatrix33<T> mat;

	mat.m[0] = m[0]*rhs.m[0] + m[3]*rhs.m[1] + m[6]*rhs.m[2];
	mat.m[1] = m[1]*rhs.m[0] + m[4]*rhs.m[1] + m[7]*rhs.m[2];
	mat.m[2] = m[2]*rhs.m[0] + m[5]*rhs.m[1] + m[8]*rhs.m[2];

	mat.m[3] = m[0]*rhs.m[3] + m[3]*rhs.m[4] + m[6]*rhs.m[5];
	mat.m[4] = m[1]*rhs.m[3] + m[4]*rhs.m[4] + m[7]*rhs.m[5];
	mat.m[5] = m[2]*rhs.m[3] + m[5]*rhs.m[4] + m[8]*rhs.m[5];

	mat.m[6] = m[0]*rhs.m[6] + m[3]*rhs.m[7] + m[6]*rhs.m[8];
	mat.m[7] = m[1]*rhs.m[6] + m[4]*rhs.m[7] + m[7]*rhs.m[8];
	mat.m[8] = m[2]*rhs.m[6] + m[5]*rhs.m[7] + m[8]*rhs.m[8];

	*this = mat;

	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator+=(const eve::math::TMatrix33<T> &rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += rhs.m[i];
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator-=(const eve::math::TMatrix33<T> &rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= rhs.m[i];
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator*=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= s;
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator/=(T s)
{
	T invS = (T)1/s;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= invS;
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator+=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += s;
	}
	return *this;
}

template< typename T >
eve::math::TMatrix33<T> & eve::math::TMatrix33<T>::operator-=(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= s;
	}
	return *this;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator*(const eve::math::TMatrix33<T> &rhs) const
{
	eve::math::TMatrix33<T> ret;

	ret.m[0] = m[0]*rhs.m[0] + m[3]*rhs.m[1] + m[6]*rhs.m[2];
	ret.m[1] = m[1]*rhs.m[0] + m[4]*rhs.m[1] + m[7]*rhs.m[2];
	ret.m[2] = m[2]*rhs.m[0] + m[5]*rhs.m[1] + m[8]*rhs.m[2];

	ret.m[3] = m[0]*rhs.m[3] + m[3]*rhs.m[4] + m[6]*rhs.m[5];
	ret.m[4] = m[1]*rhs.m[3] + m[4]*rhs.m[4] + m[7]*rhs.m[5];
	ret.m[5] = m[2]*rhs.m[3] + m[5]*rhs.m[4] + m[8]*rhs.m[5];

	ret.m[6] = m[0]*rhs.m[6] + m[3]*rhs.m[7] + m[6]*rhs.m[8];
	ret.m[7] = m[1]*rhs.m[6] + m[4]*rhs.m[7] + m[7]*rhs.m[8];
	ret.m[8] = m[2]*rhs.m[6] + m[5]*rhs.m[7] + m[8]*rhs.m[8];

	return ret;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator+(const eve::math::TMatrix33<T> & rhs) const
{
	eve::math::TMatrix33<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs.m[i];
	}
	return ret;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator-(const eve::math::TMatrix33<T> & rhs) const
{
	eve::math::TMatrix33<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs.m[i];
	}
	return ret;
}

template< typename T >
const eve::math::TVec3<T> eve::math::TMatrix33<T>::operator*(const eve::math::TVec3<T> &rhs) const
{
	return eve::math::TVec3<T>(
		m[0]*rhs.x + m[3]*rhs.y + m[6]*rhs.z,
		m[1]*rhs.x + m[4]*rhs.y + m[7]*rhs.z,
		m[2]*rhs.x + m[5]*rhs.y + m[8]*rhs.z
		);
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator*(T rhs) const
{
	eve::math::TMatrix33<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*rhs;
	}
	return ret;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator/(T rhs) const
{
	eve::math::TMatrix33<T> ret;
	T s = static_cast<T>(1)/rhs;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*s;
	}
	return ret;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator+(T rhs) const
{
	eve::math::TMatrix33<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs;
	}
	return ret;
}

template< typename T >
const eve::math::TMatrix33<T> eve::math::TMatrix33<T>::operator-(T rhs) const
{
	eve::math::TMatrix33<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs;
	}
	return ret;
}

template< typename T >
T& eve::math::TMatrix33<T>::at(int32_t row, int32_t col)
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}

template< typename T >
const T& eve::math::TMatrix33<T>::at(int32_t row, int32_t col) const
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}

template< typename T >
void eve::math::TMatrix33<T>::set(const T *dt, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m[0] = dt[0]; m[3] = dt[1]; m[6] = dt[2];
		m[1] = dt[3]; m[4] = dt[4]; m[7] = dt[5];
		m[2] = dt[6]; m[5] = dt[7]; m[8] = dt[8];
	}
	else {
		eve::mem::memcpy(m, dt, MEM_LEN);
	}
}

template< typename T >
void eve::math::TMatrix33<T>::set(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m[0] = d0; m[3] = d1; m[6] = d2;
		m[1] = d3; m[4] = d4; m[7] = d5;
		m[2] = d6; m[5] = d7; m[8] = d8;
	}
	else {
		m[0] = d0; m[3] = d3; m[6] = d6;
		m[1] = d1; m[4] = d4; m[7] = d7;
		m[2] = d2; m[5] = d5; m[8] = d8;
	}
}

template< typename T >
eve::math::TVec3<T> eve::math::TMatrix33<T>::getColumn(int32_t col) const
{
	size_t i = col*DIM;
	return eve::math::TVec3<T>(
		m[i + 0], 
		m[i + 1], 
		m[i + 2]
	);
}

template< typename T >
void eve::math::TMatrix33<T>::setColumn(int32_t col, const TVec3<T> &v)
{
	size_t i = col*DIM;
	m[i + 0] = v.x;
	m[i + 1] = v.y;
	m[i + 2] = v.z;
}

template< typename T >
eve::math::TVec3<T> eve::math::TMatrix33<T>::getRow(int32_t row) const
{ 
	return eve::math::TVec3<T>(
		m[row +  0],
		m[row +  3],
		m[row +  6]
	); 
}

template< typename T >
void eve::math::TMatrix33<T>::setRow(int32_t row, const TVec3<T> &v)
{ 
	m[row +  0] = v.x; 
	m[row +  3] = v.y; 
	m[row +  6] = v.z; 
}

template< typename T >
void eve::math::TMatrix33<T>::getColumns(eve::math::TVec3<T> *c0, eve::math::TVec3<T> *c1, eve::math::TVec3<T> *c2) const
{
	*c0 = getColumn( 0 );
	*c1 = getColumn( 1 );
	*c2 = getColumn( 2 );
}

template< typename T >
void eve::math::TMatrix33<T>::setColumns(const eve::math::TVec3<T> &c0, const eve::math::TVec3<T> &c1, const eve::math::TVec3<T> &c2)
{
	setColumn( 0, c0 );
	setColumn( 1, c1 );
	setColumn( 2, c2 );
}

template< typename T >
void eve::math::TMatrix33<T>::getRows(eve::math::TVec3<T> *r0, eve::math::TVec3<T> *r1, eve::math::TVec3<T> *r2) const
{
	*r0 = getRow( 0 );
	*r1 = getRow( 1 );
	*r2 = getRow( 2 );
}

template< typename T >
void eve::math::TMatrix33<T>::setRows(const eve::math::TVec3<T> &r0, const eve::math::TVec3<T> &r1, const eve::math::TVec3<T> &r2)
{
	setRow( 0, r0 );
	setRow( 1, r1 );
	setRow( 2, r2 );
}

template< typename T >
eve::math::TMatrix22<T> eve::math::TMatrix33<T>::subMatrix22(int32_t row, int32_t col) const
{
	eve::math::TMatrix22<T> ret;
	ret.setToNull();

	for( int32_t i = 0; i < 2; ++i ) {
		int32_t r = row + i;
		if( r >= 3 ) {
			continue;
		}
		for( int32_t j = 0; j < 2; ++j ) {
			int32_t c = col + j;
			if( c >= 3 ) {
				continue;
			}
			ret.at( i, j ) = at( r, c );
		}
	}

	return ret;
}

template< typename T >
void eve::math::TMatrix33<T>::setToNull(void)
{
	eve::mem::memset(m, 0, MEM_LEN);
}

template< typename T >
void eve::math::TMatrix33<T>::setToIdentity(void)
{
	m00 = 1; m01 = 0; m02 = 0;
	m10 = 0; m11 = 1; m12 = 0;
	m20 = 0; m21 = 0; m22 = 1;
}

template< typename T >
T eve::math::TMatrix33<T>::determinant(void) const
{
	T co00 = m[4]*m[8] - m[5]*m[7];
	T co10 = m[5]*m[6] - m[3]*m[8];
	T co20 = m[3]*m[7] - m[4]*m[6];

	T det  = m[0]*co00 + m[1]*co10 + m[2]*co20;

	return det;
}

template< typename T >
T eve::math::TMatrix33<T>::trace(void) const
{
	return m00 + m11 + m22;
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::diagonal(void) const
{
	eve::math::TMatrix33 ret;
	ret.m00 = m00; ret.m01 =   0; ret.m02 =   0;
	ret.m10 =   0; ret.m11 = m11; ret.m12 =   0;
	ret.m20 =   0; ret.m21 =   0; ret.m22 = m22;
	return ret;
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::lowerTriangular(void) const
{
	eve::math::TMatrix33 ret;
	ret.m00 = m00; ret.m01 =   0; ret.m02 =   0;
	ret.m10 = m10; ret.m11 = m11; ret.m12 =   0;
	ret.m20 = m20; ret.m21 = m21; ret.m22 = m22;
	return ret;
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::upperTriangular(void) const
{
	eve::math::TMatrix33 ret;
	ret.m00 = m00; ret.m01 = m01; ret.m02 = m02;
	ret.m10 =   0; ret.m11 = m11; ret.m12 = m12;
	ret.m20 =   0; ret.m21 =   0; ret.m22 = m22;
	return ret;
}

template< typename T >
void eve::math::TMatrix33<T>::transpose(void)
{
	T t;
	t = m01; m01 = m10; m10 = t;
	t = m02; m02 = m20; m20 = t;
	t = m12; m12 = m21; m21 = t;
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::transposed(void) const
{
	return eve::math::TMatrix33<T>(
		m[ 0], m[ 3], m[6],
		m[ 1], m[ 4], m[7],
		m[ 2], m[ 5], m[8]
	);
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::inverted(T epsilon) const
{
	eve::math::TMatrix33<T> inv(static_cast<T>(0));

	// Compute the adjoint.
	inv.m[0] = m[4]*m[8] - m[5]*m[7];
	inv.m[1] = m[2]*m[7] - m[1]*m[8];
	inv.m[2] = m[1]*m[5] - m[2]*m[4];
	inv.m[3] = m[5]*m[6] - m[3]*m[8];
	inv.m[4] = m[0]*m[8] - m[2]*m[6];
	inv.m[5] = m[2]*m[3] - m[0]*m[5];
	inv.m[6] = m[3]*m[7] - m[4]*m[6];
	inv.m[7] = m[1]*m[6] - m[0]*m[7];
	inv.m[8] = m[0]*m[4] - m[1]*m[3];

	T det = m[0]*inv.m[0] + m[1]*inv.m[3] + m[2]*inv.m[6];

	if (eve::math::abs(det) > epsilon) {
		T invDet = (T)1/det;
		inv.m[0] *= invDet;
		inv.m[1] *= invDet;
		inv.m[2] *= invDet;
		inv.m[3] *= invDet;
		inv.m[4] *= invDet;
		inv.m[5] *= invDet;
		inv.m[6] *= invDet;
		inv.m[7] *= invDet;
		inv.m[8] *= invDet;
	}

	return inv;
}

template< typename T >
eve::math::TVec3<T> eve::math::TMatrix33<T>::preMultiply(const eve::math::TVec3<T> &v) const
{
	return eve::math::TVec3<T>(
		v.x*m00 + v.y*m10 + v.z*m20,
		v.x*m01 + v.y*m11 + v.z*m21,
		v.x*m02 + v.y*m12 + v.z*m22
		);
}

template< typename T >
eve::math::TVec3<T> eve::math::TMatrix33<T>::postMultiply(const eve::math::TVec3<T> &v) const
{
	return eve::math::TVec3<T>(
		m00*v.x + m01*v.y + m02*v.z,
		m10*v.x + m11*v.y + m12*v.z,
		m20*v.x + m21*v.y + m22*v.z
		);
}

template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::invertTransform(void) const
{
	eve::math::TMatrix33<T> ret;

	// transpose rotation part
	for( int32_t i = 0; i < DIM; i++ ) {
		for( int32_t j = 0; j < DIM; j++ ) {
			ret.at( j, i ) = at( i, j );
		}
	}

	return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createRotation(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to, const eve::math::TVec3<T> &worldUp)
{
    // The goal is to obtain a rotation matrix that takes 
    // "fromDir" to "toDir".  We do this in two steps and 
    // compose the resulting rotation matrices; 
    //    (a) rotate "fromDir" into the z-axis
    //    (b) rotate the z-axis into "toDir"
 
    // The from direction must be non-zero; but we allow zero to and up dirs.
    if( from.lengthSquared() == 0 ) {
		return eve::math::TMatrix33<T>();
	}
    else {
		eve::math::TMatrix33<T> zAxis2FromDir	= alignZAxisWithTarget(from, TVec3<T>::yAxis());
		eve::math::TMatrix33<T> fromDir2zAxis	= zAxis2FromDir.transposed();
		eve::math::TMatrix33<T> zAxis2ToDir		= alignZAxisWithTarget(to, worldUp);
		return fromDir2zAxis * zAxis2ToDir;
    }
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createRotation(const eve::math::TVec3<T> &axis, T angle)
{
	eve::math::TVec3<T> unit(axis.normalized());
	T sine   = eve::math::sin( angle );
	T cosine = eve::math::cos(angle);

	eve::math::TMatrix33<T> ret;

	ret.m[0] = unit.x * unit.x * (1 - cosine) + cosine;
	ret.m[1] = unit.x * unit.y * (1 - cosine) + unit.z * sine;
	ret.m[2] = unit.x * unit.z * (1 - cosine) - unit.y * sine;

	ret.m[3] = unit.x * unit.y * (1 - cosine) - unit.z * sine;
	ret.m[4] = unit.y * unit.y * (1 - cosine) + cosine;
	ret.m[5] = unit.y * unit.z * (1 - cosine) + unit.x * sine;

	ret.m[6] = unit.x * unit.z * (1 - cosine) + unit.y * sine;
	ret.m[7] = unit.y * unit.z * (1 - cosine) - unit.x * sine;
	ret.m[8] = unit.z * unit.z * (1 - cosine) + cosine;

    return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createRotation(const eve::math::TVec3<T> &eulerRadians)
{
	// The ordering for this is XYZ. In OpenGL, the ordering
	// is the same, but the operations needs to happen in
	// reverse: 
	//
	//     glRotatef( eulerRadians.z, 0.0f, 0.0f 1.0f );
	//     glRotatef( eulerRadians.y, 0.0f, 1.0f 0.0f );
	//     glRotatef( eulerRadians.x, 1.0f, 0.0f 0.0f );
	//

	eve::math::TMatrix33<T> ret;
	T cos_rz, sin_rz, cos_ry, sin_ry, cos_rx, sin_rx;

	cos_rx = eve::math::cos(eulerRadians.x);
	cos_ry = eve::math::cos(eulerRadians.y);
	cos_rz = eve::math::cos(eulerRadians.z);

	sin_rx = eve::math::sin(eulerRadians.x);
	sin_ry = eve::math::sin(eulerRadians.y);
	sin_rz = eve::math::sin(eulerRadians.z);

	ret.m[0] =  cos_rz*cos_ry;
	ret.m[1] =  sin_rz*cos_ry;
	ret.m[2] = -sin_ry;

	ret.m[3] = -sin_rz*cos_rx + cos_rz*sin_ry*sin_rx;
	ret.m[4] =  cos_rz*cos_rx + sin_rz*sin_ry*sin_rx;
	ret.m[5] =  cos_ry*sin_rx;

	ret.m[6] =  sin_rz*sin_rx + cos_rz*sin_ry*cos_rx;
	ret.m[7] = -cos_rz*sin_rx + sin_rz*sin_ry*cos_rx;
	ret.m[8] =  cos_ry*cos_rx;

	return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createScale(T s)
{
	eve::math::TMatrix33<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = s;
	ret.at(1,1) = s;
	ret.at(2,2) = s;
	return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createScale(const eve::math::TVec2<T> &v)
{
	eve::math::TMatrix33<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = v.x;
	ret.at(1,1) = v.y;
	ret.at(2,2) = 1;
	return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::createScale(const eve::math::TVec3<T> &v)
{
	eve::math::TMatrix33<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = v.x;
	ret.at(1,1) = v.y;
	ret.at(2,2) = v.z;
	return ret;
}

template<typename T>
eve::math::TMatrix33<T> eve::math::TMatrix33<T>::alignZAxisWithTarget(eve::math::TVec3<T> targetDir, eve::math::TVec3<T> upDir)
{

	// Ensure that the target direction is non-zero.
	if (targetDir.lengthSquared() < static_cast<T>(EVE_MATH_EPSILON)) {
		// We want to look down the negative z-axis since to match OpenGL.
		targetDir = -eve::math::TVec3<T>::zAxis();
	}

	// Ensure that the up direction is non-zero.
	if (upDir.lengthSquared() < static_cast<T>(EVE_MATH_EPSILON))
	{
		upDir = eve::math::TVec3<T>::yAxis();
	}

	// Check for degeneracies.  If the upDir and targetDir are parallel 
	// or opposite, then compute a new, arbitrary up direction that is
	// not parallel or opposite to the targetDir.
	if( upDir.cross( targetDir ).lengthSquared() == 0 ) 
	{
		upDir = targetDir.cross(eve::math::TVec3<T>::xAxis());
		if( upDir.lengthSquared() == 0 ) 
		{
			upDir = targetDir.cross(eve::math::TVec3<T>::zAxis());
		}
	}

	// Compute the x-, y-, and z-axis vectors of the new coordinate system.
	eve::math::TVec3<T> targetPerpDir	= targetDir.cross(upDir);
	eve::math::TVec3<T> targetUpDir		= targetPerpDir.cross(targetDir);


	// Rotate the x-axis into targetPerpDir (row 0),
	// rotate the y-axis into targetUpDir   (row 1),
	// rotate the z-axis into targetDir     (row 2).
	eve::math::TVec3<T> row[3];
	row[0] = targetPerpDir.normalized();
	row[1] = targetUpDir.normalized();
	row[2] = targetDir.normalized();

	eve::math::TMatrix33<T> mat(
		row[0].x,  row[0].y,  row[0].z,
		row[1].x,  row[1].y,  row[1].z,
		row[2].x,  row[2].y,  row[2].z
	);

	return mat;
}

#endif // __TMATRIX_CORE_33_H__
