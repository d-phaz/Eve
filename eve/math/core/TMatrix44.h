
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
#ifndef __EVE_MATH_CORE_TMATRIX_44_H__
#define __EVE_MATH_CORE_TMATRIX_44_H__

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

#ifndef __EVE_MATH_CORE_TMATRIX_33_H__
#include "eve/math/core/TMatrix33.h"
#endif


namespace eve
{
	namespace math
	{
		/**
		* \class eve::math::TMatrix44
		*
		* \brief Template 4x4 components matrix.
		*/
		template< typename T >
		class TMatrix44
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			static const size_t DIM = 4;
			static const size_t DIM_SQ = DIM*DIM;
			static const size_t MEM_LEN = sizeof(T)*DIM_SQ;

			//
			// This class is OpenGL friendly and stores the m as how OpenGL would expect it.
			// m[i,j]:
			// | m[0,0] m[0,1] m[0,2] m[0,2] |
			// | m[1,0] m[1,1] m[1,2] m[1,2] |
			// | m[2,0] m[2,1] m[2,2] m[2,2] |
			// | m[3,0] m[3,1] m[3,2] m[3,2] |
			//
			// m[idx]
			// | m[ 0] m[ 4] m[ 8] m[12] |
			// | m[ 1] m[ 5] m[ 9] m[13] |
			// | m[ 2] m[ 6] m[10] m[14] |
			// | m[ 3] m[ 7] m[11] m[15] |
			//
			union {
				T m[16];
				struct {
					// This looks like it's transposed from the above, but it's really not.
					// It just has to be written this way so it follows the right ordering
					// in the memory layout as well as being mathematically correct.
					T m00, m10, m20, m30;
					T m01, m11, m21, m31;
					T m02, m12, m22, m32;
					T m03, m13, m23, m33;
				};
				// [Cols][Rows]
				T mcols[4][4];
			};


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TMatrix44(void);

			TMatrix44(T s);

			// OpenGL layout - unless srcIsRowMajor is true
			TMatrix44(const T *dt, bool srcIsRowMajor = false);

			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2 ... m[13]=d13, m[14]=d14, m[15]=d15 - unless srcIsRowMajor is true
			TMatrix44(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, T d9, T d10, T d11, T d12, T d13, T d14, T d15, bool srcIsRowMajor = false);

			// Creates matrix with column vectors vx, vy, vz and vw
			TMatrix44(const eve::math::TVec3<T> &vx, const eve::math::TVec3<T> &vy, const eve::math::TVec3<T> &vz);
			TMatrix44(const eve::math::TVec4<T> &vx, const eve::math::TVec4<T> &vy, const eve::math::TVec4<T> &vz, const eve::math::TVec4<T> &vw = eve::math::TVec4<T>(0, 0, 0, 1));

			template< typename FromT >
			TMatrix44(const TMatrix44<FromT>& src);

			TMatrix44(const TMatrix22<T>& src);
			TMatrix44(const TMatrix33<T>& src);

			TMatrix44(const TMatrix44<T>& src);


			// Accesses
			operator T*() { return (T*)m; }
			operator const T*() const { return (const T*)m; }
			T * ptr(void) const;

			TMatrix44<T>&		operator=(const TMatrix44<T>& rhs);
			TMatrix44<T>&		operator=(T rhs);

			template< typename FromT >
			TMatrix44<T>&		operator=(const TMatrix44<FromT>& rhs);

			// remaining columns and rows will be filled with identity values
			TMatrix44<T>&		operator=(const TMatrix22<T>& rhs);
			TMatrix44<T>&		operator=(const TMatrix33<T>& rhs);

			bool				equalCompare(const TMatrix44<T>& rhs, T epsilon) const;
			bool				operator==(const TMatrix44<T> &rhs) const { return equalCompare(rhs, (T)EVE_MATH_EPSILON); }
			bool				operator!=(const TMatrix44<T> &rhs) const { return !(*this == rhs); }

			TMatrix44<T>&		operator*=(const TMatrix44<T> &rhs);
			TMatrix44<T>&		operator+=(const TMatrix44<T> &rhs);
			TMatrix44<T>&		operator-=(const TMatrix44<T> &rhs);

			TMatrix44<T>&		operator*=(T rhs);
			TMatrix44<T>&		operator/=(T rhs);
			TMatrix44<T>&		operator+=(T rhs);
			TMatrix44<T>&		operator-=(T rhs);

			const TMatrix44<T>	operator*(const TMatrix44<T> &rhs) const;
			const TMatrix44<T>	operator+(const TMatrix44<T> &rhs) const;
			const TMatrix44<T>	operator-(const TMatrix44<T> &rhs) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z 1] and divides by w
			const eve::math::TVec3<T>		operator*(const eve::math::TVec3<T> &rhs) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z rhs.w]
			const eve::math::TVec4<T>		operator*(const eve::math::TVec4<T> &rhs) const;

			const TMatrix44<T>	operator*(T rhs) const;
			const TMatrix44<T>	operator/(T rhs) const;
			const TMatrix44<T>	operator+(T rhs) const;
			const TMatrix44<T>	operator-(T rhs) const;

			// Accessors
			T&					at(int32_t row, int32_t col);
			const T&			at(int32_t row, int32_t col) const;

			// OpenGL layout - unless srcIsRowMajor is true
			void				set(const T *dt, bool srcIsRowMajor = false);
			// OpenGL layout: m[0]=d0, m[1]=d1, m[2]=d2 ... m[13]=d13, m[14]=d14, m[15]=d15 - unless srcIsRowMajor is true
			void				set(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, T d9, T d10, T d11, T d12, T d13, T d14, T d15, bool srcIsRowMajor = false);

			eve::math::TVec4<T>	getColumn(int32_t col) const;
			void				setColumn(int32_t col, const eve::math::TVec4<T> &v);

			eve::math::TVec4<T>	getRow(int32_t row) const;
			void				setRow(int32_t row, const eve::math::TVec4<T> &v);

			void				getColumns(eve::math::TVec4<T> *c0, eve::math::TVec4<T> *c1, eve::math::TVec4<T> *c2, eve::math::TVec4<T> *c3) const;
			void				setColumns(const eve::math::TVec4<T> &c0, const eve::math::TVec4<T> &c1, const eve::math::TVec4<T> &c2, const eve::math::TVec4<T> &c3);

			void				getRows(eve::math::TVec4<T> *r0, eve::math::TVec4<T> *r1, eve::math::TVec4<T> *r2, eve::math::TVec4<T> *r3) const;
			void				setRows(const eve::math::TVec4<T> &r0, const eve::math::TVec4<T> &r1, const eve::math::TVec4<T> &r2, const eve::math::TVec4<T> &r3);

			// returns a sub-matrix starting at row, col
			TMatrix22<T>		subMatrix22(int32_t row, int32_t col) const;
			TMatrix33<T>		subMatrix33(int32_t row, int32_t col) const;

			void				setToNull(void);
			void				setToIdentity(void);

			T					determinant(void) const;
			// returns trace of 3x3 submatrix if fullTrace == false, otherwise returns trace of full 4x4 matrix
			T					trace(bool fullTrace = false) const;

			TMatrix44<T>        diagonal(void) const;

			TMatrix44<T>		lowerTriangular(void) const;
			TMatrix44<T>		upperTriangular(void) const;

			////////////////////////////////////////////////////////////////////////////////
			//Transpose:	[ a b c ]T    [ a d g ]                                       //
			//				[ d e f ]  =  [ b e h ]                                       //
			//				[ g h i ]     [ c f i ]                                       //
			////////////////////////////////////////////////////////////////////////////////
			void				transpose(void);
			TMatrix44<T>		transposed(void) const;

			void				invert(T epsilon = EVE_MATH_EPSILON) { *this = inverted(epsilon); }
			TMatrix44<T>		inverted(T epsilon = EVE_MATH_EPSILON) const;

			// pre-multiplies row vector v - no divide by w
			eve::math::TVec3<T>	preMultiply(const eve::math::TVec3<T> &v) const;
			eve::math::TVec4<T>	preMultiply(const eve::math::TVec4<T> &v) const;

			// post-multiplies column vector v - no divide by w
			eve::math::TVec3<T>	postMultiply(const eve::math::TVec3<T> &v) const;
			eve::math::TVec4<T>	postMultiply(const eve::math::TVec4<T> &v) const;

			//! Computes inverse; assumes the matrix is affine, i.e. the bottom row is [0 0 0 1]
			void				affineInvert(void){ *this = affineInverted(); }
			TMatrix44<T>		affineInverted(void) const;

			//! Computes inverse; assumes the matrix is orthonormal
			void				orthonormalInvert(void);
			TMatrix44<T>		orthonormalInverted(void) const { TMatrix44<T> result(*this); result.orthonormalInvert(); return result; }

			// post-multiplies column vector [rhs.x rhs.y rhs.z 1] and divides by w - same as operator*( const TVec3<T>& )
			eve::math::TVec3<T>	transformPoint(const eve::math::TVec3<T> &rhs) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z 1] but omits divide by w
			eve::math::TVec3<T>	transformPointAffine(const eve::math::TVec3<T> &rhs) const;

			// post-multiplies column vector [rhs.x rhs.y rhs.z 0]
			eve::math::TVec3<T>	transformVec(const eve::math::TVec3<T> &rhs) const;
			eve::math::TVec4<T>	transformVec(const eve::math::TVec4<T> &rhs) const { return transformVec(rhs.xyz()); }

			// returns the translation values from the last column
			eve::math::TVec4<T>	getTranslate() const { return eve::math::TVec4<T>(m03, m13, m23, m33); }
			// sets the translation values in the last column
			void				setTranslate(const eve::math::TVec3<T>& v) { m03 = v.x; m13 = v.y; m23 = v.z; }
			void				setTranslate(const eve::math::TVec4<T>& v) { setTranslate(v.xyz()); }

			// multiplies the current matrix by a translation matrix derived from tr
			void				translate(const eve::math::TVec3<T> &tr) { *this *= createTranslation(tr); }
			void				translate(const eve::math::TVec4<T> &tr) { *this *= createTranslation(tr); }

			// multiplies the current matrix by the rotation matrix derived using axis and radians
			void				rotate(const eve::math::TVec3<T> &axis, T radians) { *this *= createRotation(axis, radians); }
			void				rotate(const eve::math::TVec4<T> &axis, T radians) { *this *= createRotation(axis, radians); }
			// multiplies the current matrix by the rotation matrix derived using eulerRadians
			void				rotate(const eve::math::TVec3<T> &eulerRadians) { *this *= createRotation(eulerRadians); }
			void				rotate(const eve::math::TVec4<T> &eulerRadians) { *this *= createRotation(eulerRadians); }
			// multiplies the current matrix by the rotation matrix derived using from, to, worldUp
			void				rotate(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to, const eve::math::TVec3<T> &worldUp) { *this *= createRotation(from, to, worldUp); }
			void				rotate(const eve::math::TVec4<T> &from, const eve::math::TVec4<T> &to, const eve::math::TVec4<T> &worldUp) { *this *= createRotation(from, to, worldUp); }

			// multiplies the current matrix by the scale matrix derived from supplies parameters
			void				scale(T s) { TMatrix44 op = createScale(s); TMatrix44 mat = *this; *this = op*mat; }
			void				scale(const eve::math::TVec2<T> &v) { *this *= createScale(v); }
			void				scale(const eve::math::TVec3<T> &v) { *this *= createScale(v); }
			void				scale(const eve::math::TVec4<T> &v) { *this *= createScale(v); }

			// transposes rotation sub-matrix and inverts translation
			TMatrix44<T>		invertTransform(void) const;

			// Convert to Z up axis to Y up axis.
			void				fromZupToYup(void);


			///////////////////////////////////////////////////////////////////////////////////////////////
			//		STATIC
			///////////////////////////////////////////////////////////////////////////////////////////////

			// returns an identity matrix
			static TMatrix44<T>	identity(void)	{ return TMatrix44(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }
			// returns 1 filled matrix
			static TMatrix44<T>  one(void)		{ return TMatrix44(static_cast<T>(1)); }
			// returns 0 filled matrix
			static TMatrix44<T>  zero(void)		{ return TMatrix44(static_cast<T>(0)); }

			// creates translation matrix
			static TMatrix44<T>	createTranslation(const eve::math::TVec3<T> &v, T w = static_cast<T>(1));
			static TMatrix44<T>	createTranslation(const eve::math::TVec4<T> &v) { return createTranslation(v.xyz(), v.w); }

			// creates rotation matrix
			static TMatrix44<T>	createRotation(const eve::math::TVec3<T> &axis, T radians);
			static TMatrix44<T>	createRotation(const eve::math::TVec4<T> &axis, T radians) { return createRotation(axis.xyz(), radians); }
			static TMatrix44<T>	createRotation(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to, const eve::math::TVec3<T> &worldUp);
			static TMatrix44<T>	createRotation(const eve::math::TVec4<T> &from, const eve::math::TVec4<T> &to, const eve::math::TVec4<T> &worldUp) { return createRotation(from.xyz(), to.xyz(), worldUp.xyz()); }
			// equivalent to rotate( zAxis, z ), then rotate( yAxis, y ) then rotate( xAxis, x )
			static TMatrix44<T>	createRotation(const eve::math::TVec3<T> &eulerRadians);
			static TMatrix44<T>	createRotation(const eve::math::TVec4<T> &eulerRadians) { return createRotation(eulerRadians.xyz()); }
			// creates rotation matrix from ortho normal basis (u, v, n)
			static TMatrix44<T>	createRotationOnb(const eve::math::TVec3<T>& u, const eve::math::TVec3<T>& v, const eve::math::TVec3<T>& w);
			static TMatrix44<T>	createRotationOnb(const eve::math::TVec4<T>& u, const eve::math::TVec4<T>& v, const eve::math::TVec4<T>& w) { return createRotationOnb(u.xyz(), v.xyz(), w.xyz()); }

			// creates scale matrix
			static TMatrix44<T>	createScale(T s);
			static TMatrix44<T>	createScale(const eve::math::TVec2<T> &v);
			static TMatrix44<T>	createScale(const eve::math::TVec3<T> &v);
			static TMatrix44<T>	createScale(const eve::math::TVec4<T> &v);

			// creates a rotation matrix with z-axis aligned to targetDir	
			static TMatrix44<T>	alignZAxisWithTarget(eve::math::TVec3<T> targetDir, eve::math::TVec3<T> upDir);
			static TMatrix44<T>	alignZAxisWithTarget(eve::math::TVec4<T> targetDir, eve::math::TVec4<T> upDir) { return alignZAxisWithTarget(targetDir.xyz(), upDir.xyz()); }


			static TMatrix44<T> look_at(eve::math::TVec3<T> const & eye, eve::math::TVec3<T> const & center, eve::math::TVec3<T> const & up);

			/// Creates a frustum matrix.
			/// 
			/// @param left 
			/// @param right 
			/// @param bottom 
			/// @param top 
			/// @param nearVal 
			/// @param farVal 
			/// @tparam T Value type used to build the matrix. Currently supported: half (not recommended), float or double.
			static TMatrix44<T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal);

			/// Creates a perspective matrix.
			/// 
			/// @param fovy 
			/// @param aspect 
			/// @param zNear 
			/// @param zFar
			/// @tparam T Value type used to build the matrix. Currently supported: half (not recommended), float or double.
			static TMatrix44<T> perspective(T fovy, T aspect, T zNear, T zFar);

			/// Creates a matrix for an orthographic parallel viewing volume.
			/// 
			/// @param left 
			/// @param right 
			/// @param bottom 
			/// @param top 
			/// @param zNear 
			/// @param zFar 
			/// @tparam T Value type used to build the matrix. Currently supported: half (not recommended), float or double.
			static TMatrix44<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);

			/// Creates a matrix for projecting two-dimensional coordinates onto the screen.
			/// 
			/// @param left 
			/// @param right 
			/// @param bottom 
			/// @param top 
			/// @tparam T Value type used to build the matrix. Currently supported: half (not recommended), float or double.
			static TMatrix44<T> ortho(T left, T right, T bottom, T top);

		}; // TMatrix44


	} // namespace math

} // namespace eve


//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(void)
{
	setToIdentity();
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(T s)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = s;
	}
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const T *dt, bool srcIsRowMajor)
{
	set( dt, srcIsRowMajor );
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, T d9, T d10, T d11, T d12, T d13, T d14, T d15, bool srcIsRowMajor)
{
	set(d0,  d1,  d2,  d3, 
		d4,  d5,  d6,  d7, 
		d8,  d9, d10, d11, 
		d12, d13, d14, d15, srcIsRowMajor );
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TVec3<T> &vx, const eve::math::TVec3<T> &vy, const eve::math::TVec3<T> &vz)
{
	m[0] = vx.x; m[4] = vy.x; m[ 8] = vz.x; m[12] = 0;
	m[1] = vx.y; m[5] = vy.y; m[ 9] = vz.y; m[13] = 0;
	m[2] = vx.z; m[6] = vy.z; m[10] = vz.z; m[14] = 0;
	m[3] =    0; m[7] =    0; m[11] =    0; m[15] = 1;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TVec4<T> &vx, const eve::math::TVec4<T> &vy, const eve::math::TVec4<T> &vz, const eve::math::TVec4<T> &vw)
{
	m[0] = vx.x; m[4] = vy.x; m[ 8] = vz.x; m[12] = vw.x;
	m[1] = vx.y; m[5] = vy.y; m[ 9] = vz.y; m[13] = vw.y;
	m[2] = vx.z; m[6] = vy.z; m[10] = vz.z; m[14] = vw.z;
	m[3] = vx.w; m[7] = vy.w; m[11] = vz.w; m[15] = vw.w;
}

//=================================================================================================
template< typename T >
template< typename FromT >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TMatrix44<FromT>& src)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = static_cast<T>( src.m[i] );
	}
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TMatrix22<T>& src)
{
	setToIdentity();
	m00 = src.m00; m01 = src.m01;
	m10 = src.m10; m11 = src.m11;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TMatrix33<T>& src)
{
	setToIdentity();
	m00 = src.m00; m01 = src.m01; m02 = src.m02;
	m10 = src.m10; m11 = src.m11; m12 = src.m12;
	m20 = src.m20; m21 = src.m21; m22 = src.m22;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>::TMatrix44(const eve::math::TMatrix44<T>& src)
{
	eve::mem::memcpy(m, src.m, MEM_LEN);
}



//=================================================================================================
template< typename T > EVE_FORCE_INLINE T * eve::math::TMatrix44<T>::ptr(void) const { return const_cast<T*>(m); }



//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator=(const eve::math::TMatrix44<T>& rhs)
{
	eve::mem::memcpy(m, rhs.m, MEM_LEN);
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator=(T rhs)
{
	for( int32_t i = 0; i < DIM_SQ; i++ ) {
		m[i] = rhs;
	}
	return *this;
}

//=================================================================================================
template< typename T >
template< typename FromT >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator=(const eve::math::TMatrix44<FromT>& rhs)
{
	for( int32_t i = 0; i < DIM_SQ; i++ ) {
		m[i] = static_cast<T>(rhs.m[i]);
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator=(const eve::math::TMatrix22<T>& rhs)
{
	setToIdentity();
	m00 = rhs.m00; m01 = rhs.m01;
	m10 = rhs.m10; m11 = rhs.m11;
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator=(const eve::math::TMatrix33<T>& rhs)
{
	setToIdentity();
	m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02;
	m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12;
	m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22;
	return *this;
}

//=================================================================================================
template< typename T >
bool eve::math::TMatrix44<T>::equalCompare(const eve::math::TMatrix44<T>& rhs, T epsilon) const
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		if (eve::math::abs(m[i] - rhs.m[i]) >= epsilon)
			return false;
	}
	return true;
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator*=(const eve::math::TMatrix44<T> &rhs)
{
	eve::math::TMatrix44<T> ret;

	ret.m[ 0] = m[ 0]*rhs.m[ 0] + m[ 4]*rhs.m[ 1] + m[ 8]*rhs.m[ 2] + m[12]*rhs.m[ 3];
	ret.m[ 1] = m[ 1]*rhs.m[ 0] + m[ 5]*rhs.m[ 1] + m[ 9]*rhs.m[ 2] + m[13]*rhs.m[ 3];
	ret.m[ 2] = m[ 2]*rhs.m[ 0] + m[ 6]*rhs.m[ 1] + m[10]*rhs.m[ 2] + m[14]*rhs.m[ 3];
	ret.m[ 3] = m[ 3]*rhs.m[ 0] + m[ 7]*rhs.m[ 1] + m[11]*rhs.m[ 2] + m[15]*rhs.m[ 3];

	ret.m[ 4] = m[ 0]*rhs.m[ 4] + m[ 4]*rhs.m[ 5] + m[ 8]*rhs.m[ 6] + m[12]*rhs.m[ 7];
	ret.m[ 5] = m[ 1]*rhs.m[ 4] + m[ 5]*rhs.m[ 5] + m[ 9]*rhs.m[ 6] + m[13]*rhs.m[ 7];
	ret.m[ 6] = m[ 2]*rhs.m[ 4] + m[ 6]*rhs.m[ 5] + m[10]*rhs.m[ 6] + m[14]*rhs.m[ 7];
	ret.m[ 7] = m[ 3]*rhs.m[ 4] + m[ 7]*rhs.m[ 5] + m[11]*rhs.m[ 6] + m[15]*rhs.m[ 7];

	ret.m[ 8] = m[ 0]*rhs.m[ 8] + m[ 4]*rhs.m[ 9] + m[ 8]*rhs.m[10] + m[12]*rhs.m[11];
	ret.m[ 9] = m[ 1]*rhs.m[ 8] + m[ 5]*rhs.m[ 9] + m[ 9]*rhs.m[10] + m[13]*rhs.m[11];
	ret.m[10] = m[ 2]*rhs.m[ 8] + m[ 6]*rhs.m[ 9] + m[10]*rhs.m[10] + m[14]*rhs.m[11];
	ret.m[11] = m[ 3]*rhs.m[ 8] + m[ 7]*rhs.m[ 9] + m[11]*rhs.m[10] + m[15]*rhs.m[11];

	ret.m[12] = m[ 0]*rhs.m[12] + m[ 4]*rhs.m[13] + m[ 8]*rhs.m[14] + m[12]*rhs.m[15];
	ret.m[13] = m[ 1]*rhs.m[12] + m[ 5]*rhs.m[13] + m[ 9]*rhs.m[14] + m[13]*rhs.m[15];
	ret.m[14] = m[ 2]*rhs.m[12] + m[ 6]*rhs.m[13] + m[10]*rhs.m[14] + m[14]*rhs.m[15];
	ret.m[15] = m[ 3]*rhs.m[12] + m[ 7]*rhs.m[13] + m[11]*rhs.m[14] + m[15]*rhs.m[15];

	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] = ret.m[i];
	}

	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator+=(const eve::math::TMatrix44<T> &rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += rhs.m[i];
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator-=(const eve::math::TMatrix44<T> &rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= rhs.m[i];
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator*=(T rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= rhs;
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T>& eve::math::TMatrix44<T>::operator/=(T rhs)
{
	T invS = static_cast<T>(1)/rhs;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] *= invS;
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator+=(T rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] += rhs;
	}
	return *this;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> & eve::math::TMatrix44<T>::operator-=(T rhs)
{
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		m[i] -= rhs;
	}
	return *this;
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator*(const eve::math::TMatrix44<T> &rhs) const
{
	eve::math::TMatrix44<T> ret;

	ret.m[ 0] = m[ 0]*rhs.m[ 0] + m[ 4]*rhs.m[ 1] + m[ 8]*rhs.m[ 2] + m[12]*rhs.m[ 3];
	ret.m[ 1] = m[ 1]*rhs.m[ 0] + m[ 5]*rhs.m[ 1] + m[ 9]*rhs.m[ 2] + m[13]*rhs.m[ 3];
	ret.m[ 2] = m[ 2]*rhs.m[ 0] + m[ 6]*rhs.m[ 1] + m[10]*rhs.m[ 2] + m[14]*rhs.m[ 3];
	ret.m[ 3] = m[ 3]*rhs.m[ 0] + m[ 7]*rhs.m[ 1] + m[11]*rhs.m[ 2] + m[15]*rhs.m[ 3];

	ret.m[ 4] = m[ 0]*rhs.m[ 4] + m[ 4]*rhs.m[ 5] + m[ 8]*rhs.m[ 6] + m[12]*rhs.m[ 7];
	ret.m[ 5] = m[ 1]*rhs.m[ 4] + m[ 5]*rhs.m[ 5] + m[ 9]*rhs.m[ 6] + m[13]*rhs.m[ 7];
	ret.m[ 6] = m[ 2]*rhs.m[ 4] + m[ 6]*rhs.m[ 5] + m[10]*rhs.m[ 6] + m[14]*rhs.m[ 7];
	ret.m[ 7] = m[ 3]*rhs.m[ 4] + m[ 7]*rhs.m[ 5] + m[11]*rhs.m[ 6] + m[15]*rhs.m[ 7];

	ret.m[ 8] = m[ 0]*rhs.m[ 8] + m[ 4]*rhs.m[ 9] + m[ 8]*rhs.m[10] + m[12]*rhs.m[11];
	ret.m[ 9] = m[ 1]*rhs.m[ 8] + m[ 5]*rhs.m[ 9] + m[ 9]*rhs.m[10] + m[13]*rhs.m[11];
	ret.m[10] = m[ 2]*rhs.m[ 8] + m[ 6]*rhs.m[ 9] + m[10]*rhs.m[10] + m[14]*rhs.m[11];
	ret.m[11] = m[ 3]*rhs.m[ 8] + m[ 7]*rhs.m[ 9] + m[11]*rhs.m[10] + m[15]*rhs.m[11];

	ret.m[12] = m[ 0]*rhs.m[12] + m[ 4]*rhs.m[13] + m[ 8]*rhs.m[14] + m[12]*rhs.m[15];
	ret.m[13] = m[ 1]*rhs.m[12] + m[ 5]*rhs.m[13] + m[ 9]*rhs.m[14] + m[13]*rhs.m[15];
	ret.m[14] = m[ 2]*rhs.m[12] + m[ 6]*rhs.m[13] + m[10]*rhs.m[14] + m[14]*rhs.m[15];
	ret.m[15] = m[ 3]*rhs.m[12] + m[ 7]*rhs.m[13] + m[11]*rhs.m[14] + m[15]*rhs.m[15];

	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator+(const eve::math::TMatrix44<T> &rhs) const
{
	eve::math::TMatrix44<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs.m[i];
	}
	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator-(const eve::math::TMatrix44<T> &rhs) const
{
	eve::math::TMatrix44<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs.m[i];
	}
	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TVec3<T> eve::math::TMatrix44<T>::operator*(const eve::math::TVec3<T> &rhs) const
{
	T x = m[ 0]*rhs.x + m[ 4]*rhs.y + m[ 8]*rhs.z + m[12];
	T y = m[ 1]*rhs.x + m[ 5]*rhs.y + m[ 9]*rhs.z + m[13];
	T z = m[ 2]*rhs.x + m[ 6]*rhs.y + m[10]*rhs.z + m[14];
	T w = m[ 3]*rhs.x + m[ 7]*rhs.y + m[11]*rhs.z + m[15];

	return eve::math::TVec3<T>(x / w, y / w, z / w);
}

//=================================================================================================
template< typename T >
const eve::math::TVec4<T> eve::math::TMatrix44<T>::operator*(const eve::math::TVec4<T> &rhs) const
{
	return eve::math::TVec4<T>(
		m[ 0]*rhs.x + m[ 4]*rhs.y + m[ 8]*rhs.z + m[12]*rhs.w,
		m[ 1]*rhs.x + m[ 5]*rhs.y + m[ 9]*rhs.z + m[13]*rhs.w,
		m[ 2]*rhs.x + m[ 6]*rhs.y + m[10]*rhs.z + m[14]*rhs.w,
		m[ 3]*rhs.x + m[ 7]*rhs.y + m[11]*rhs.z + m[15]*rhs.w
		);
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator*(T rhs) const
{
	eve::math::TMatrix44<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*rhs;
	}
	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator/(T rhs) const
{
	eve::math::TMatrix44<T> ret;
	T s = (T)1/rhs;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i]*s;
	}
	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator+(T rhs) const
{
	eve::math::TMatrix44<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] + rhs;
	}
	return ret;
}

//=================================================================================================
template< typename T >
const eve::math::TMatrix44<T> eve::math::TMatrix44<T>::operator-(T rhs) const
{
	eve::math::TMatrix44<T> ret;
	for( int32_t i = 0; i < DIM_SQ; ++i ) {
		ret.m[i] = m[i] - rhs;
	}
	return ret;
}



//=================================================================================================
template< typename T >
T& eve::math::TMatrix44<T>::at(int32_t row, int32_t col)
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}

//=================================================================================================
template< typename T >
const T& eve::math::TMatrix44<T>::at(int32_t row, int32_t col) const
{
	EVE_ASSERT(row >= 0 && row < DIM);
	EVE_ASSERT(col >= 0 && col < DIM);
	return m[col*DIM + row];
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::set(const T *dt, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m[0] = dt[ 0]; m[4] = dt[ 1]; m[ 8] = dt[ 2]; m[12] = dt[ 3];
		m[1] = dt[ 4]; m[5] = dt[ 5]; m[ 9] = dt[ 6]; m[13] = dt[ 7];
		m[2] = dt[ 8]; m[6] = dt[ 9]; m[10] = dt[10]; m[14] = dt[11];
		m[3] = dt[12]; m[7] = dt[13]; m[11] = dt[14]; m[15] = dt[15];
	}
	else {
		eve::mem::memcpy(m, dt, MEM_LEN);
	}
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::set(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, T d9, T d10, T d11, T d12, T d13, T d14, T d15, bool srcIsRowMajor)
{
	if( srcIsRowMajor ) {
		m[0] =  d0; m[4] =  d1; m[ 8] =  d2; m[12] =  d3;
		m[1] =  d4; m[5] =  d5; m[ 9] =  d6; m[13] =  d7;
		m[2] =  d8; m[6] =  d9; m[10] = d10; m[14] = d11;
		m[3] = d12; m[7] = d13; m[11] = d14; m[15] = d15;
	}
	else {
		m[0] =  d0; m[4] =  d4; m[ 8] =  d8; m[12] = d12;
		m[1] =  d1; m[5] =  d5; m[ 9] =  d9; m[13] = d13;
		m[2] =  d2; m[6] =  d6; m[10] = d10; m[14] = d14;
		m[3] =  d3; m[7] =  d7; m[11] = d11; m[15] = d15;
	}
}



//=================================================================================================
template< typename T >
eve::math::TVec4<T> eve::math::TMatrix44<T>::getColumn(int32_t col) const
{
	size_t i = col*DIM;
	return eve::math::TVec4<T>(
		m[i + 0], 
		m[i + 1], 
		m[i + 2], 
		m[i + 3]
	);
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setColumn(int32_t col, const eve::math::TVec4<T> &v)
{
	size_t i = col*DIM;
	m[i + 0] = v.x;
	m[i + 1] = v.y;
	m[i + 2] = v.z;
	m[i + 3] = v.w;
}



//=================================================================================================
template< typename T >
eve::math::TVec4<T> eve::math::TMatrix44<T>::getRow(int32_t row) const
{ 
	return eve::math::TVec4<T>(
		m[row +  0], 
		m[row +  4], 
		m[row +  8], 
		m[row + 12] 
	); 
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setRow(int32_t row, const eve::math::TVec4<T> &v)
{ 
	m[row +  0] = v.x; 
	m[row +  4] = v.y; 
	m[row +  8] = v.z; 
	m[row + 12] = v.w; 
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::getColumns(eve::math::TVec4<T> *c0, eve::math::TVec4<T> *c1, eve::math::TVec4<T> *c2, eve::math::TVec4<T> *c3) const
{
	*c0 = getColumn( 0 );
	*c1 = getColumn( 1 );
	*c2 = getColumn( 2 );
	*c3 = getColumn( 3 );
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setColumns(const eve::math::TVec4<T> &c0, const eve::math::TVec4<T> &c1, const eve::math::TVec4<T> &c2, const eve::math::TVec4<T> &c3)
{
	setColumn( 0, c0 );
	setColumn( 1, c1 );
	setColumn( 2, c2 );
	setColumn( 3, c3 );
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::getRows(eve::math::TVec4<T> *r0, eve::math::TVec4<T> *r1, eve::math::TVec4<T> *r2, eve::math::TVec4<T> *r3) const
{
	*r0 = getRow( 0 );
	*r1 = getRow( 1 );
	*r2 = getRow( 2 );
	*r3 = getRow( 3 );
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setRows(const eve::math::TVec4<T> &r0, const eve::math::TVec4<T> &r1, const eve::math::TVec4<T> &r2, const eve::math::TVec4<T> &r3)
{
	setRow( 0, r0 );
	setRow( 1, r1 );
	setRow( 2, r2 );
	setRow( 3, r3 );
}



//=================================================================================================
template< typename T >
eve::math::TMatrix22<T> eve::math::TMatrix44<T>::subMatrix22(int32_t row, int32_t col) const
{
	eve::math::TMatrix22<T> ret;
	ret.setToNull();

	for( int32_t i = 0; i < 2; ++i ) {
		int32_t r = row + i;
		if( r >= 4 ) {
			continue;
		}
		for( int32_t j = 0; j < 2; ++j ) {
			int32_t c = col + j;
			if( c >= 4 ) {
				continue;
			}
			ret.at( i, j ) = at( r, c );
		}
	}

	return ret;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix33<T> eve::math::TMatrix44<T>::subMatrix33(int32_t row, int32_t col) const
{
	eve::math::TMatrix33<T> ret;
	ret.setToNull();

	for( int32_t i = 0; i < 3; ++i ) {
		int32_t r = row + i;
		if( r >= 4 ) {
			continue;
		}
		for( int32_t j = 0; j < 3; ++j ) {
			int32_t c = col + j;
			if( c >= 4 ) {
				continue;
			}
			ret.at( i, j ) = at( r, c );
		}
	}

	return ret;
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setToNull()
{
	eve::mem::memset( m, 0, MEM_LEN );
// 	m[ 0] = 0; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
// 	m[ 1] = 0; m[ 5] = 0; m[ 9] = 0; m[13] = 0;
// 	m[ 2] = 0; m[ 6] = 0; m[10] = 0; m[14] = 0;
// 	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 0;
}

//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::setToIdentity()
{
	m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
	m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = 0;
	m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
}



//=================================================================================================
template< typename T >
T eve::math::TMatrix44<T>::determinant() const
{
	T a0 = m[ 0]*m[ 5] - m[ 1]*m[ 4];
	T a1 = m[ 0]*m[ 6] - m[ 2]*m[ 4];
	T a2 = m[ 0]*m[ 7] - m[ 3]*m[ 4];
	T a3 = m[ 1]*m[ 6] - m[ 2]*m[ 5];
	T a4 = m[ 1]*m[ 7] - m[ 3]*m[ 5];
	T a5 = m[ 2]*m[ 7] - m[ 3]*m[ 6];
	T b0 = m[ 8]*m[13] - m[ 9]*m[12];
	T b1 = m[ 8]*m[14] - m[10]*m[12];
	T b2 = m[ 8]*m[15] - m[11]*m[12];
	T b3 = m[ 9]*m[14] - m[10]*m[13];
	T b4 = m[ 9]*m[15] - m[11]*m[13];
	T b5 = m[10]*m[15] - m[11]*m[14];

	T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

	return det;
}



//=================================================================================================
template< typename T >
T eve::math::TMatrix44<T>::trace(bool fullTrace) const
{
	if( fullTrace ) {
		return m00 + m11 + m22 + m33;
	}

	return m00 + m11 + m22;
}



//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::diagonal() const
{
	eve::math::TMatrix44 ret;
	ret.m00 = m00; ret.m01 =   0; ret.m02 =   0; ret.m03 =   0;
	ret.m10 =   0; ret.m11 = m11; ret.m12 =   0; ret.m13 =   0;
	ret.m20 =   0; ret.m21 =   0; ret.m22 = m22; ret.m23 =   0;
	ret.m30 =   0; ret.m31 =   0; ret.m32 =   0; ret.m33 = m33;
	return ret;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::lowerTriangular() const
{
	eve::math::TMatrix44 ret;
	ret.m00 = m00; ret.m01 =   0; ret.m02 =   0; ret.m03 =   0;
	ret.m10 = m10; ret.m11 = m11; ret.m12 =   0; ret.m13 =   0;
	ret.m20 = m20; ret.m21 = m21; ret.m22 = m22; ret.m23 =   0;
	ret.m30 = m30; ret.m31 = m31; ret.m32 = m32; ret.m33 = m33;
	return ret;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::upperTriangular() const
{
	eve::math::TMatrix44 ret;
	ret.m00 = m00; ret.m01 = m01; ret.m02 = m02; ret.m03 = m03;
	ret.m10 =   0; ret.m11 = m11; ret.m12 = m12; ret.m13 = m13;
	ret.m20 =   0; ret.m21 =   0; ret.m22 = m22; ret.m23 = m23;
	ret.m30 =   0; ret.m31 =   0; ret.m32 =   0; ret.m33 = m33;
	return ret;
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::transpose()
{
	T t;
	t = m01; m01 = m10; m10 = t;
	t = m02; m02 = m20; m20 = t;
	t = m03; m03 = m30; m30 = t;
	t = m12; m12 = m21; m21 = t;
	t = m13; m13 = m31; m31 = t;
	t = m23; m23 = m32; m32 = t;
}

//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::transposed() const
{
	return eve::math::TMatrix44<T>(
		m[ 0], m[ 4], m[ 8], m[12],
		m[ 1], m[ 5], m[ 9], m[13],
		m[ 2], m[ 6], m[10], m[14],
		m[ 3], m[ 7], m[11], m[15] 
	);
}



//=================================================================================================
template< typename T >
inline eve::math::TMatrix44<T> eve::math::TMatrix44<T>::inverted(T epsilon) const
{
	eve::math::TMatrix44<T> inv(static_cast<T>(0.0));

	T a0 = m[ 0]*m[ 5] - m[ 1]*m[ 4];
	T a1 = m[ 0]*m[ 6] - m[ 2]*m[ 4];
	T a2 = m[ 0]*m[ 7] - m[ 3]*m[ 4];
	T a3 = m[ 1]*m[ 6] - m[ 2]*m[ 5];
	T a4 = m[ 1]*m[ 7] - m[ 3]*m[ 5];
	T a5 = m[ 2]*m[ 7] - m[ 3]*m[ 6];
	T b0 = m[ 8]*m[13] - m[ 9]*m[12];
	T b1 = m[ 8]*m[14] - m[10]*m[12];
	T b2 = m[ 8]*m[15] - m[11]*m[12];
	T b3 = m[ 9]*m[14] - m[10]*m[13];
	T b4 = m[ 9]*m[15] - m[11]*m[13];
	T b5 = m[10]*m[15] - m[11]*m[14];

	T det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

	if (eve::math::abs(det) > epsilon) {
		inv.m[ 0] = + m[ 5]*b5 - m[ 6]*b4 + m[ 7]*b3;
		inv.m[ 4] = - m[ 4]*b5 + m[ 6]*b2 - m[ 7]*b1;
		inv.m[ 8] = + m[ 4]*b4 - m[ 5]*b2 + m[ 7]*b0;
		inv.m[12] = - m[ 4]*b3 + m[ 5]*b1 - m[ 6]*b0;
		inv.m[ 1] = - m[ 1]*b5 + m[ 2]*b4 - m[ 3]*b3;
		inv.m[ 5] = + m[ 0]*b5 - m[ 2]*b2 + m[ 3]*b1;
		inv.m[ 9] = - m[ 0]*b4 + m[ 1]*b2 - m[ 3]*b0;
		inv.m[13] = + m[ 0]*b3 - m[ 1]*b1 + m[ 2]*b0;
		inv.m[ 2] = + m[13]*a5 - m[14]*a4 + m[15]*a3;
		inv.m[ 6] = - m[12]*a5 + m[14]*a2 - m[15]*a1;
		inv.m[10] = + m[12]*a4 - m[13]*a2 + m[15]*a0;
		inv.m[14] = - m[12]*a3 + m[13]*a1 - m[14]*a0;
		inv.m[ 3] = - m[ 9]*a5 + m[10]*a4 - m[11]*a3;
		inv.m[ 7] = + m[ 8]*a5 - m[10]*a2 + m[11]*a1;
		inv.m[11] = - m[ 8]*a4 + m[ 9]*a2 - m[11]*a0;
		inv.m[15] = + m[ 8]*a3 - m[ 9]*a1 + m[10]*a0;

		T invDet = ((T)1)/det;
		inv.m[ 0] *= invDet;
		inv.m[ 1] *= invDet;
		inv.m[ 2] *= invDet;
		inv.m[ 3] *= invDet;
		inv.m[ 4] *= invDet;
		inv.m[ 5] *= invDet;
		inv.m[ 6] *= invDet;
		inv.m[ 7] *= invDet;
		inv.m[ 8] *= invDet;
		inv.m[ 9] *= invDet;
		inv.m[10] *= invDet;
		inv.m[11] *= invDet;
		inv.m[12] *= invDet;
		inv.m[13] *= invDet;
		inv.m[14] *= invDet;
		inv.m[15] *= invDet;
	}

	return inv;
}



//=================================================================================================
template< typename T >
eve::math::TVec3<T> eve::math::TMatrix44<T>::preMultiply(const eve::math::TVec3<T> &v) const
{
	return eve::math::TVec3<T>(
		v.x*m00 + v.y*m10 + v.z*m20,
		v.x*m01 + v.y*m11 + v.z*m21,
		v.x*m02 + v.y*m12 + v.z*m22
		);
}

//=================================================================================================
template< typename T >
eve::math::TVec4<T> eve::math::TMatrix44<T>::preMultiply(const eve::math::TVec4<T> &v) const
{
	return eve::math::TVec4<T>(
		v.x*m00 + v.y*m10 + v.z*m20 + v.w*m30,
		v.x*m01 + v.y*m11 + v.z*m21 + v.w*m31,
		v.x*m02 + v.y*m12 + v.z*m22 + v.w*m32,
		v.x*m03 + v.y*m13 + v.z*m23 + v.w*m33
		);
}

//=================================================================================================
template< typename T >
eve::math::TVec3<T> eve::math::TMatrix44<T>::postMultiply(const eve::math::TVec3<T> &v) const
{
	return eve::math::TVec3<T>(
		m00*v.x + m01*v.y + m02*v.z,
		m10*v.x + m11*v.y + m12*v.z,
		m20*v.x + m21*v.y + m22*v.z
		);
}

//=================================================================================================
template< typename T >
eve::math::TVec4<T> eve::math::TMatrix44<T>::postMultiply(const eve::math::TVec4<T> &v) const
{
	return eve::math::TVec4<T>(
		m00*v.x + m01*v.y + m02*v.z + m03*v.w,
		m10*v.x + m11*v.y + m12*v.z + m13*v.w,
		m20*v.x + m21*v.y + m22*v.z + m23*v.w,
		m30*v.x + m31*v.y + m32*v.z + m33*v.w
		);
}



//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::affineInverted() const
{
	eve::math::TMatrix44<T> ret;

	// compute upper left 3x3 matrix determinant
	T cofactor0 = m[ 5]*m[10] - m[6]*m[ 9];
	T cofactor4 = m[ 2]*m[ 9] - m[1]*m[10];
	T cofactor8 = m[ 1]*m[ 6] - m[2]*m[ 5];
	T det = m[0]*cofactor0 + m[4]*cofactor4 + m[8]*cofactor8;
	if (eve::math::abs(det) <= EVE_MATH_EPSILON) {
		return ret;
	}

	// create adjunct matrix and multiply by 1/det to get upper 3x3
	T invDet = ((T)1.0) / det;
	ret.m[ 0] = invDet*cofactor0;
	ret.m[ 1] = invDet*cofactor4;
	ret.m[ 2] = invDet*cofactor8;

	ret.m[ 4] = invDet*(m[ 6]*m[ 8] - m[ 4]*m[10]);
	ret.m[ 5] = invDet*(m[ 0]*m[10] - m[ 2]*m[ 8]);
	ret.m[ 6] = invDet*(m[ 2]*m[ 4] - m[ 0]*m[ 6]);

	ret.m[ 8] = invDet*(m[ 4]*m[ 9] - m[ 5]*m[ 8]);
	ret.m[ 9] = invDet*(m[ 1]*m[ 8] - m[ 0]*m[ 9]);
	ret.m[10] = invDet*(m[ 0]*m[ 5] - m[ 1]*m[ 4]);

	// multiply -translation by inverted 3x3 to get its inverse	    
	ret.m[12] = -ret.m[ 0]*m[12] - ret.m[ 4]*m[13] - ret.m[ 8]*m[14];
	ret.m[13] = -ret.m[ 1]*m[12] - ret.m[ 5]*m[13] - ret.m[ 9]*m[14];
	ret.m[14] = -ret.m[ 2]*m[12] - ret.m[ 6]*m[13] - ret.m[10]*m[14];

	return ret;
}



//=================================================================================================
template< typename T >
eve::math::TVec3<T> eve::math::TMatrix44<T>::transformPoint(const eve::math::TVec3<T> &rhs) const
{
	T x = m00*rhs.x + m01*rhs.y + m02*rhs.z + m03;
	T y = m10*rhs.x + m11*rhs.y + m12*rhs.z + m13;
	T z = m20*rhs.x + m21*rhs.y + m22*rhs.z + m23;
	T w = m30*rhs.x + m31*rhs.y + m32*rhs.z + m33;

	return eve::math::TVec3<T>(x / w, y / w, z / w);
}

//=================================================================================================
template< typename T >
eve::math::TVec3<T> eve::math::TMatrix44<T>::transformPointAffine(const eve::math::TVec3<T> &rhs) const
{
	T x = m00*rhs.x + m01*rhs.y + m02*rhs.z + m03;
	T y = m10*rhs.x + m11*rhs.y + m12*rhs.z + m13;
	T z = m20*rhs.x + m21*rhs.y + m22*rhs.z + m23;

	return eve::math::TVec3<T>(x, y, z);
}



//=================================================================================================
template< typename T >
eve::math::TVec3<T> eve::math::TMatrix44<T>::transformVec(const eve::math::TVec3<T> &rhs) const
{
	T x = m00*rhs.x + m01*rhs.y + m02*rhs.z;
	T y = m10*rhs.x + m11*rhs.y + m12*rhs.z;
	T z = m20*rhs.x + m21*rhs.y + m22*rhs.z;

	return eve::math::TVec3<T>(x, y, z);
}



//=================================================================================================
template< typename T >
void eve::math::TMatrix44<T>::orthonormalInvert()
{
	// transpose upper 3x3 (R->R^t)
	std::swap( at(0,1), at(1,0) );
	std::swap( at(0,2), at(2,0) );
	std::swap( at(1,2), at(2,1) );

	// replace translation (T) with R^t(-T).
	eve::math::TVec3<T> newT(transformVec(eve::math::TVec3<T>(-at(0, 3), -at(1, 3), -at(2, 3))));
	at(0,3) = newT.x;
	at(1,3) = newT.y;
	at(2,3) = newT.z;
}



//=================================================================================================
template< typename T >
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::invertTransform() const
{
	eve::math::TMatrix44<T> ret;

	// transpose rotation part
	for( int32_t i = 0; i < DIM; i++ ) {
		for( int32_t j = 0; j < DIM; j++ ) {
			ret.at( j, i ) = at( i, j );
		}
	}

	return ret;
}


//=================================================================================================
template<typename T>
void eve::math::TMatrix44<T>::fromZupToYup(void)
{
	static eve::math::TMatrix44<T> matMirror(1.0, 0.0, 0.0, 0.0
										   , 0.0, 0.0,-1.0, 0.0
										   , 0.0, 1.0, 0.0, 0.0 
										   , 0.0, 0.0, 0.0, 1.0 );

// 	static eve::math::TMatrix44<T> matMirror(1.0, 0.0, 0.0, 0.0
// 										   , 0.0, 0.0, 1.0, 0.0
// 										   , 0.0, 1.0, 0.0, 0.0 
// 										   , 0.0, 0.0, 0.0, 1.0 );

// 	static eve::math::TMatrix44<T> matMirror(1.0, 0.0, 0.0, 0.0
// 										   , 0.0, 0.0, 1.0, 0.0
// 										   , 0.0,-1.0, 0.0, 0.0 
// 										   , 0.0, 0.0, 0.0, 1.0 );

	*this = matMirror * (*this);
	*this = eve::math::TMatrix44<T>::createRotation(eve::math::TVec3<T>::yAxis(), static_cast<T>(M_PI)) * (*this);
	//*this = *this * matMirror;
}



//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createTranslation(const eve::math::TVec3<T> &v, T w)
{
	eve::math::TMatrix44<T> ret;
	ret.m[12] = v.x;
	ret.m[13] = v.y;
	ret.m[14] = v.z;
	ret.m[15] = w;

	return ret;
}



//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createRotation(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to, const eve::math::TVec3<T> &worldUp)
{
    // The goal is to obtain a rotation matrix that takes 
    // "fromDir" to "toDir".  We do this in two steps and 
    // compose the resulting rotation matrices; 
    //    (a) rotate "fromDir" into the z-axis
    //    (b) rotate the z-axis into "toDir"
 
    // The from direction must be non-zero; but we allow zero to and up dirs.
    if( from.lengthSquared() == 0 ) {
		return eve::math::TMatrix44<T>();
	}
    else {
		eve::math::TMatrix44<T> zAxis2FromDir	= alignZAxisWithTarget(from, TVec3<T>::yAxis());
		eve::math::TMatrix44<T> fromDir2zAxis	= zAxis2FromDir.transposed();
		eve::math::TMatrix44<T> zAxis2ToDir		= alignZAxisWithTarget(to, worldUp);
		return fromDir2zAxis * zAxis2ToDir;
    }
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createRotation(const eve::math::TVec3<T> &axis, T angle)
{
	eve::math::TVec3<T> unit(axis.normalized());
	T sine   = eve::math::sin( angle );
	T cosine = eve::math::cos(angle);

	eve::math::TMatrix44<T> ret;

	ret.m[ 0] = unit.x * unit.x * (1 - cosine) + cosine;
	ret.m[ 1] = unit.x * unit.y * (1 - cosine) + unit.z * sine;
	ret.m[ 2] = unit.x * unit.z * (1 - cosine) - unit.y * sine;
	ret.m[ 3] = 0;

	ret.m[ 4] = unit.x * unit.y * (1 - cosine) - unit.z * sine;
	ret.m[ 5] = unit.y * unit.y * (1 - cosine) + cosine;
	ret.m[ 6] = unit.y * unit.z * (1 - cosine) + unit.x * sine;
	ret.m[ 7] = 0;

	ret.m[ 8] = unit.x * unit.z * (1 - cosine) + unit.y * sine;
	ret.m[ 9] = unit.y * unit.z * (1 - cosine) - unit.x * sine;
	ret.m[10] = unit.z * unit.z * (1 - cosine) + cosine;
	ret.m[11] = 0;

	ret.m[12] = 0;
	ret.m[13] = 0;
	ret.m[14] = 0;
	ret.m[15] = 1;

    return ret;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createRotation(const eve::math::TVec3<T> &eulerRadians)
{
	// The ordering for this is XYZ. In OpenGL, the ordering
	// is the same, but the operations needs to happen in
	// reverse: 
	//
	//     glRotatef( eulerRadians.z, 0.0f, 0.0f 1.0f );
	//     glRotatef( eulerRadians.y, 0.0f, 1.0f 0.0f );
	//     glRotatef( eulerRadians.x, 1.0f, 0.0f 0.0f );
	//

	eve::math:: TMatrix44<T> ret;
	T cos_rz, sin_rz, cos_ry, sin_ry, cos_rx, sin_rx;

	cos_rx = eve::math::cos(eulerRadians.x);
	cos_ry = eve::math::cos(eulerRadians.y);
	cos_rz = eve::math::cos(eulerRadians.z);

	sin_rx = eve::math::sin(eulerRadians.x);
	sin_ry = eve::math::sin(eulerRadians.y);
	sin_rz = eve::math::sin(eulerRadians.z);

	ret.m[ 0] =  cos_rz*cos_ry;
	ret.m[ 1] =  sin_rz*cos_ry;
	ret.m[ 2] = -sin_ry;
	ret.m[ 3] =  0;

	ret.m[ 4] = -sin_rz*cos_rx + cos_rz*sin_ry*sin_rx;
	ret.m[ 5] =  cos_rz*cos_rx + sin_rz*sin_ry*sin_rx;
	ret.m[ 6] =  cos_ry*sin_rx;
	ret.m[ 7] =  0;

	ret.m[ 8] =  sin_rz*sin_rx + cos_rz*sin_ry*cos_rx;
	ret.m[ 9] = -cos_rz*sin_rx + sin_rz*sin_ry*cos_rx;
	ret.m[10] =  cos_ry*cos_rx;
	ret.m[11] =  0;

	ret.m[12] =  0;
	ret.m[13] =  0;
	ret.m[14] =  0;
	ret.m[15] =  1;

	return ret;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T>	eve::math::TMatrix44<T>::createRotationOnb(const eve::math::TVec3<T>& u, const eve::math::TVec3<T>& v, const eve::math::TVec3<T>& w)
{
	return eve::math::TMatrix44<T>(
		u.x,  u.y, u.z, 0,
		v.x,  v.y, v.z, 0,
		w.x,  w.y, w.z, 0,
		0,    0,   0, 1
		);
}



//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createScale(T s)
{
	eve::math::TMatrix44<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = s;
	ret.at(1,1) = s;
	ret.at(2,2) = s;
	ret.at(3,3) = s;
	return ret;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createScale(const eve::math::TVec2<T> &v)
{
	eve::math::TMatrix44<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = v.x;
	ret.at(1,1) = v.y;
	ret.at(2,2) = 1;
	ret.at(3,3) = 1;
	return ret;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createScale(const eve::math::TVec3<T> &v)
{
	eve::math::TMatrix44<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = v.x;
	ret.at(1,1) = v.y;
	ret.at(2,2) = v.z;
	ret.at(3,3) = 1;
	return ret;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::createScale(const eve::math::TVec4<T> &v)
{
	eve::math::TMatrix44<T> ret;
	ret.setToIdentity();
	ret.at(0,0) = v.x;
	ret.at(1,1) = v.y;
	ret.at(2,2) = v.z;
	ret.at(3,3) = v.w;
	return ret;
}



//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::alignZAxisWithTarget(eve::math::TVec3<T> targetDir, eve::math::TVec3<T> upDir)
{
    // Ensure that the target direction is non-zero.
    if( targetDir.lengthSquared() == 0 )
		targetDir = eve::math::TVec3<T>::zAxis();

    // Ensure that the up direction is non-zero.
    if( upDir.lengthSquared() == 0 )
		upDir = eve::math::TVec3<T>::yAxis();

    // Check for degeneracies.  If the upDir and targetDir are parallel 
    // or opposite, then compute a new, arbitrary up direction that is
    // not parallel or opposite to the targetDir.
    if( upDir.cross( targetDir ).lengthSquared() == 0 ) {
		upDir = targetDir.cross(eve::math::TVec3<T>::xAxis());
	if( upDir.lengthSquared() == 0 )
		upDir = targetDir.cross(eve::math::TVec3<T>::zAxis());
    }

    // Compute the x-, y-, and z-axis vectors of the new coordinate system.
	eve::math::TVec3<T> targetPerpDir	= upDir.cross(targetDir);
	eve::math::TVec3<T> targetUpDir		= targetDir.cross(targetPerpDir);
    

    // Rotate the x-axis into targetPerpDir (row 0),
    // rotate the y-axis into targetUpDir   (row 1),
    // rotate the z-axis into targetDir     (row 2).
	eve::math::TVec3<T> row[3];
    row[0] = targetPerpDir.normalized();
    row[1] = targetUpDir.normalized();
    row[2] = targetDir.normalized();
    
	eve::math::TMatrix44<T> mat(row[0].x,  row[0].y,  row[0].z,  0,
								row[1].x,  row[1].y,  row[1].z,  0,
								row[2].x,  row[2].y,  row[2].z,  0,
								       0,         0,         0,  1 );
    
    return mat;
}



//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::look_at(eve::math::TVec3<T> const & eye, eve::math::TVec3<T> const & center, eve::math::TVec3<T> const & up)
{
	eve::math::TVec3<T> f = (center - eye).normalized();
	eve::math::TVec3<T> u = up.normalized();
	eve::math::TVec3<T> s = f.cross(u).normalized();
	u = s.cross(f);

	eve::math::TMatrix44<T> Result;
	Result.setToIdentity();

	Result.m[ 0] = s.x;
	Result.m[ 4] = s.y;
	Result.m[ 8] = s.z;

	Result.m[ 1] = u.x;
	Result.m[ 5] = u.y;
	Result.m[ 9] = u.z;

	Result.m[ 2] =-f.x;
	Result.m[ 6] =-f.y;
	Result.m[10] =-f.z;

	Result.m[12] =-s.dot(eye);
	Result.m[13] =-u.dot(eye);
	Result.m[14] = f.dot(eye);

	return Result;
}

//=================================================================================================
template<typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	eve::math::TMatrix44<T> Result;
	Result.setToIdentity();

	Result.m[ 0] =  (T(2) * nearVal) / (right - left);
	Result.m[ 5] =  (T(2) * nearVal) / (top - bottom);
	Result.m[ 8] =  (right + left) / (right - left);
	Result.m[ 9] =  (top + bottom) / (top - bottom);
	Result.m[10] = -(farVal + nearVal) / (farVal - nearVal);
	Result.m[11] = -T(1);
	Result.m[14] = -(T(2) * farVal * nearVal) / (farVal - nearVal);

	return Result;
}

//=================================================================================================
template <typename T> 
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::perspective(T fovy, T aspect, T zNear, T zFar)
{
	T const rad = toRadians(fovy);
	T tanHalfFovy = tan(rad / T(2));

	eve::math::TMatrix44<T> Result;
	Result.setToNull();

	Result.m[ 0] = T(1) / (aspect * tanHalfFovy);
	Result.m[ 5] = T(1) / (tanHalfFovy);
	Result.m[10] = - (zFar + zNear) / (zFar - zNear);
	Result.m[11] = - T(1);
	Result.m[14] = - (T(2) * zFar * zNear) / (zFar - zNear);

	return Result;
}

//=================================================================================================
template <typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::ortho(T left, T right, T bottom, T top, T zNear, T zFar)
{
	eve::math::TMatrix44<T>  Result;
	Result.setToIdentity();

	Result.m[ 0] =  T(2) / (right - left);
	Result.m[ 5] =  T(2) / (top - bottom);
	Result.m[10] = -T(2) / (zFar - zNear);
	Result.m[12] = -(right + left) / (right - left);
	Result.m[13] = -(top + bottom) / (top - bottom);
	Result.m[14] = -(zFar + zNear) / (zFar - zNear);

	return Result;
}

//=================================================================================================
template <typename T>
eve::math::TMatrix44<T> eve::math::TMatrix44<T>::ortho(T left, T right, T bottom, T top)
{
	eve::math::TMatrix44<T>  Result;
	Result.setToIdentity();

	Result.m[ 0] =  T(2) / (right - left);
	Result.m[ 5] =  T(2) / (top - bottom);
	Result.m[10] = -T(1);
	Result.m[12] = -(right + left) / (right - left);
	Result.m[13] = -(top + bottom) / (top - bottom);

	return Result;
}

//=================================================================================================
template <typename T>
eve::math::TMatrix44<T> rotate(eve::math::TMatrix44<T> const & m, T const & angle, eve::math::TVec3<T> const & v)
{
	T a = toRadians(angle);
	T c = cos(a);
	T s = sin(a);

	eve::math::TVec3<T> axis = normalize(v);

	eve::math::TVec3<T> temp = (T(1) - c) * axis;

	eve::math::TMatrix44<T> Rotate(static_cast<T>(0));
	Rotate[0][0] = c + temp[0] * axis[0];
	Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
	Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

	Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
	Rotate[1][1] = c + temp[1] * axis[1];
	Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

	Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
	Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
	Rotate[2][2] = c + temp[2] * axis[2];

	eve::math::TMatrix44<T> Result(static_cast<T>(0));
	Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
	Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
	Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
	Result[3] = m[3];
	return Result;
}


/// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
/// 
/// @param obj 
/// @param model 
/// @param proj
/// @param viewport 
/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
/// @tparam U Currently supported: Floating-point types and integer types.
template <typename T, typename U>
static EVE_FORCE_INLINE eve::math::TVec3<T> project(const eve::math::TVec3<T> & obj, const eve::math::TMatrix44<T> & model, const eve::math::TMatrix44<T> & proj, const eve::math::TVec4<U> & viewport)
{
	eve::math::TVec4<T> tmp(obj, static_cast<T>(1));
	tmp = model * tmp;
	tmp = proj * tmp;

	tmp /= tmp.w;
	tmp = tmp * T(0.5) + T(0.5);
	tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
	tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

	return eve::math::TVec3<T>(tmp.xyz());
}

/// Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
/// 
/// @param win 
/// @param model 
/// @param proj
/// @param viewport 
/// @tparam T Native type used for the computation. Currently supported: float or double.
/// @tparam U Currently supported: Floating-point types and integer types.
template <typename T, typename U>
static EVE_FORCE_INLINE eve::math::TVec3<T> un_project(const eve::math::TVec3<T> & win, const eve::math::TMatrix44<T> & model, const eve::math::TMatrix44<T> & proj, const eve::math::TVec4<U> & viewport)
{
	eve::math::TMatrix44<T> invMat = proj * model;		//glm::inverse(proj * model);
	invMat.invert();

	eve::math::TVec4<T> tmp(win, static_cast<T>(1));
	tmp.x = (tmp.x - static_cast<T>(viewport[0])) / static_cast<T>(viewport[2]);
	tmp.y = (tmp.y - static_cast<T>(viewport[1])) / static_cast<T>(viewport[3]);
	tmp = tmp * static_cast<T>(2) - static_cast<T>(1);

	eve::math::TVec4<T> obj = invMat * tmp;
	obj /= obj.w;

	return eve::math::TVec3<T>(obj.xyz());
}

#endif // __EVE_MATH_CORE_TMATRIX_44_H__
