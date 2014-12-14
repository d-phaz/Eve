
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
#ifndef __EVE_MATH_TRAY_H__
#define __EVE_MATH_TRAY_H__

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif


namespace eve
{
	namespace math
	{
		/**
		* \class eve::math::TRay
		*
		* \brief Template ray composed of origin and direction.
		*/
		template< typename T >
		class TRay
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		protected:
			TVec3<T>			m_origin;
			TVec3<T>			m_direction;
			TVec3<T> 			m_invDirection;

			// These are helpful to some ray intersection algorithms.
			char				m_signX;
			char				m_signY;
			char				m_signZ;


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TRay(const TVec3<T>  &aOrigin = TVec3<T>::zero(), const TVec3<T>  &aDirection = TVec3<T>::zero());
			virtual ~TRay(void);

			TVec3<T>  calcPosition(T t) const;

			bool calcTriangleIntersection(const TVec3<T>  &vert0, const TVec3<T>  &vert1, const TVec3<T>  &vert2, TVec3<T> * intersectionPoint) const;
			bool calcTriangleIntersection(const TVec3<T>  &vert0, const TVec3<T>  &vert1, const TVec3<T>  &vert2, T *result) const;
			bool calcPlaneIntersection(const TVec3<T>  &origin, const TVec3<T>  &normal, T *result) const;

			void			setOrigin(const TVec3<T>  &aOrigin);
			const TVec3<T> &	getOrigin(void) const;

			void setDirection(const TVec3<T>  &aDirection);

			const TVec3<T> &	getDirection(void) const;
			const TVec3<T> &	getInverseDirection(void) const;

			const char getSignX(void) const;
			const char getSignY(void) const;
			const char getSignZ(void) const;

		}; // class TRay

	} // namespace math

} // namespace eve

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TRay<T>::TRay(const TVec3<T>  &aOrigin, const TVec3<T>  &aDirection)
	: m_origin			( aOrigin )
	, m_direction		( TVec3<T>::zero() )
	, m_invDirection	( TVec3<T>::zero() )

	, m_signX			( 0 )
	, m_signY			( 0 )
	, m_signZ			( 0 )
{
	this->setDirection( aDirection );
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TRay<T>::~TRay(void)
{}	



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE eve::math::TVec3<T> eve::math::TRay<T>::calcPosition(T t) const
{ 
	return m_origin + m_direction * t; 
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE bool eve::math::TRay<T>::calcTriangleIntersection(const eve::math::TVec3<T> & vert0, const eve::math::TVec3<T> & vert1, const eve::math::TVec3<T> & vert2, eve::math::TVec3<T> * intersectionPoint) const
{
	// Triangle vectors
	Vec3f	I, u, v, n;  
	// Ray vectors
	Vec3f	dir, w0, w;
	// Params to calc ray-plane intersect
	float   r, a, b;             

	// Get triangle edge vectors and plane normal
	u = vert1 - vert0;
	v = vert2 - vert0;
	n = u.cross( v );

	// Ray direction vector
	dir = m_direction - m_origin;             
	w0 = m_origin - vert0;
	a = -n.dot( w0 );
	b =  n.dot( dir );
	if( tmath<T>::fabs(b) < EVE_PICKING_EPSILON ) { // ray is parallel to triangle plane
		return false;          
	}

	// Get intersection point of ray with triangle plane
	// for a segment, also test if (r > 1.0) => no intersect
	r = a / b;
	if( r < 0.0F )	{	// ray goes away from triangle
		return false;    // => no intersect
	}


	// Intersect point of ray and plane
	*intersectionPoint = m_origin + r * dir; 

	// is I inside T?
	float uu, uv, vv, wu, wv, D;
	uu = u.dot( u );
	uv = u.dot( v );
	vv = v.dot( v );
	w = *intersectionPoint - vert0;
	wu = w.dot( u );
	wv = w.dot( v );
	D = uv * uv - uu * vv;

	// Get and test barycentric coordinates
	float s, t;

	s = (uv * wv - vv * wu) / D;
	if (s < 0.0F || s > 1.0F) {			// I is outside T
		return false;
	}

	t = (uv * wu - uu * wv) / D;
	if (t < 0.0F || (s + t) > 1.0F) {	// I is outside T
		return false;
	}

	return true;						// I is in T
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE bool eve::math::TRay<T>::calcTriangleIntersection(const eve::math::TVec3<T> & vert0, const eve::math::TVec3<T> & vert1, const eve::math::TVec3<T> & vert2, T * result) const
{
	Vec3f edge1, edge2, tvec, pvec, qvec;
	T det;
	T u, v;
	const T RAY_EPSILON = T(0.000001);

	edge1 = vert1 - vert0;
	edge2 = vert2 - vert0;

	pvec = m_direction.cross( edge2 );
	det = edge1.dot( pvec );

#if 0 // we don't want to back face cull
	if ( det < RAY_EPSILON )
		return false;
	tvec = m_origin - vert0;

	u = tvec.dot( pvec );
	if ( ( u < 0.0f ) || ( u > det ) )
		return false;

	qvec = tvec.cross( edge1 );
	v = m_direction.dot( qvec );
	if ( v < 0.0f || u + v > det )
		return false;

	*result = edge2.dot( qvec ) / det;
	return true;
#else
	if( det > -RAY_EPSILON && det < RAY_EPSILON )
		return false;

	T inv_det = 1.0f / det;
	tvec = m_origin - vert0;
	u = tvec.dot( pvec ) * inv_det;
	if( u < 0.0f || u > 1.0f )
		return false;

	qvec = tvec.cross( edge1 );

	v = m_direction.dot( qvec ) * inv_det;
	if( v < 0.0f || u + v > 1.0f )
		return false;

	*result = edge2.dot( qvec ) * inv_det;
	return true;
#endif
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE bool eve::math::TRay<T>::calcPlaneIntersection(const eve::math::TVec3<T> & origin, const eve::math::TVec3<T> & normal, T * result) const
{
	bool breturn = false;

	T denom = normal.dot( m_direction );

	if( denom != 0.0f )
	{
		*result = normal.dot( origin - m_origin ) / denom;
		breturn = true;
	}

	return breturn;
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE void eve::math::TRay<T>::setOrigin(const eve::math::TVec3<T> & aOrigin)
{ 
	m_origin = aOrigin; 
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TRay<T>::getOrigin(void) const
{ 
	return m_origin; 
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE void eve::math::TRay<T>::setDirection(const eve::math::TVec3<T> & aDirection)
{
	m_direction = aDirection;
	m_invDirection = eve::math::TVec3<T>(static_cast<T>(1) / m_direction.x, static_cast<T>(1) / m_direction.y, static_cast<T>(1) / m_direction.z);
	m_signX = (m_direction.x < static_cast<T>(0)) ? 1 : 0;
	m_signY = (m_direction.y < static_cast<T>(0)) ? 1 : 0;
	m_signZ = (m_direction.z < static_cast<T>(0)) ? 1 : 0;
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TRay<T>::getDirection(void) const
{ 
	return m_direction; 
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const eve::math::TVec3<T> & eve::math::TRay<T>::getInverseDirection(void) const
{ 
	return m_invDirection; 
}



//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const char eve::math::TRay<T>::getSignX(void) const
{ 
	return m_signX; 
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const char eve::math::TRay<T>::getSignY(void) const
{ 
	return m_signY; 
}

//=================================================================================================
template< typename T >
EVE_FORCE_INLINE const char eve::math::TRay<T>::getSignZ(void) const
{ 
	return m_signZ; 
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef eve::math::TRay<float>	Rayf;
typedef eve::math::TRay<double>	Rayd;

#endif // __EVE_MATH_TRAY_H__
