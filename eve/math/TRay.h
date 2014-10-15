
#pragma once
#ifndef __TRAY_H__
#define __TRAY_H__


#ifndef __TVECTOR_H__
#include "math/TVector.h"
#endif

#define PICKING_EPSILON   0.00000000001f

template< typename T >
class TRay 
{

protected:
	TVec3<T>			m_origin;
	TVec3<T>			m_direction;
	TVec3<T> 			m_invDirection;

	// These are helpful to certain ray intersection algorithms
	char				m_signX;
	char				m_signY;
	char				m_signZ;


 public:
	TRay( const TVec3<T>  &aOrigin=TVec3<T>::zero(), const TVec3<T>  &aDirection=TVec3<T>::zero() );
	virtual ~TRay( void );

	TVec3<T>  calcPosition( T t ) const;

	bool calcTriangleIntersection( const TVec3<T>  &vert0, const TVec3<T>  &vert1, const TVec3<T>  &vert2, TVec3<T> * intersectionPoint ) const;
	bool calcTriangleIntersection( const TVec3<T>  &vert0, const TVec3<T>  &vert1, const TVec3<T>  &vert2, T *result ) const;
	bool calcPlaneIntersection( const TVec3<T>  &origin, const TVec3<T>  &normal, T *result ) const;

	void			setOrigin( const TVec3<T>  &aOrigin );
	const TVec3<T> &	getOrigin( void ) const;
	
	void setDirection( const TVec3<T>  &aDirection );

	const TVec3<T> &	getDirection( void ) const;
	const TVec3<T> &	getInverseDirection( void ) const;
	
	const char getSignX( void ) const;
	const char getSignY( void ) const;
	const char getSignZ( void ) const;		
};


//=================================================================================================
template< typename T >
TRay<T>::TRay( const TVec3<T>  &aOrigin, const TVec3<T>  &aDirection )
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
TRay<T>::~TRay( void )
{}	



//=================================================================================================
template< typename T >
TVec3<T> TRay<T>::calcPosition( T t ) const 
{ 
	return m_origin + m_direction * t; 
}



//=================================================================================================
template< typename T >
bool TRay<T>::calcTriangleIntersection( const TVec3<T>  &vert0, const TVec3<T>  &vert1, const TVec3<T>  &vert2, TVec3<T> * intersectionPoint ) const
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
	if( tmath<T>::fabs(b) < PICKING_EPSILON ) { // ray is parallel to triangle plane
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
bool TRay<T>::calcTriangleIntersection( const TVec3<T> & vert0, const TVec3<T> & vert1, const TVec3<T> & vert2, T * result ) const
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
bool TRay<T>::calcPlaneIntersection( const TVec3<T>  &origin, const TVec3<T>  &normal, T *result ) const
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
void TRay<T>::setOrigin( const TVec3<T>  &aOrigin ) 
{ 
	m_origin = aOrigin; 
}

//=================================================================================================
template< typename T >
const TVec3<T> &	TRay<T>::getOrigin( void ) const 
{ 
	return m_origin; 
}



//=================================================================================================
template< typename T >
void TRay<T>::setDirection( const TVec3<T>  &aDirection ) 
{
	m_direction = aDirection;
	m_invDirection = TVec3<T> ( 1.0f / m_direction.x, 1.0f / m_direction.y, 1.0f / m_direction.z );
	m_signX = ( m_direction.x < 0.0f ) ? 1 : 0;
	m_signY = ( m_direction.y < 0.0f ) ? 1 : 0;
	m_signZ = ( m_direction.z < 0.0f ) ? 1 : 0;		
}

//=================================================================================================
template< typename T >
const TVec3<T> &	TRay<T>::getDirection( void ) const 
{ 
	return m_direction; 
}

//=================================================================================================
template< typename T >
const TVec3<T> &	TRay<T>::getInverseDirection( void ) const 
{ 
	return m_invDirection; 
}



//=================================================================================================
template< typename T >
const char TRay<T>::getSignX( void ) const 
{ 
	return m_signX; 
}

//=================================================================================================
template< typename T >
const char TRay<T>::getSignY( void ) const 
{ 
	return m_signY; 
}

//=================================================================================================
template< typename T >
const char TRay<T>::getSignZ( void ) const 
{ 
	return m_signZ; 
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef TRay<float>	 Rayf;
typedef TRay<double> Rayd;

#endif // __TRAY_H__
