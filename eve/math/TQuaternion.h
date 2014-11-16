
#pragma once
#ifndef __TQUATERNION_H__
#define __TQUATERNION_H__

#ifndef __NATIVE_SYSTEM_H__
#include "Native_System.h"
#endif

#ifndef __TMATH_H__
#include "math/TMath.h"
#endif

#ifndef __TVECTOR_H__
#include "math/TVector.h"
#endif

#ifndef __TMATRIX_H__
#include "math/TMatrix.h"
#endif


template<typename T, typename Y>
struct QUATCONV {
	typedef typename T::TYPE F;
	static F	getW( const Y &v ) { return static_cast<F>( v.w ); }
	static F	getX( const Y &v ) { return static_cast<F>( v.x ); }
	static F	getY( const Y &v ) { return static_cast<F>( v.y ); }
	static F	getZ( const Y &v ) { return static_cast<F>( v.z ); }
};

template<typename T>
class TQuaternion 
{
public:
	typedef T	TYPE;
	typedef T	value_type;
 
	TVec3<T>		v; // axisOfRotation.normalized() * sin( angleOfRotation / 2 )
	T				w; // cos( angleOfRotation / 2 )

	TQuaternion(): w( 1 ), v( 0, 0, 0 ){} // default constructor is identity quat
	template<typename FromT>
	TQuaternion( const TQuaternion<FromT>& q ) : w( static_cast<T>( q.w ) ), v( q.v ) {}

	TQuaternion( T aW, T x, T y, T z ): w( aW ), v( x, y, z ) {}	
	// construct from axis-angle
	TQuaternion( const TVec3<T> &axis, T radians ) { set( axis, radians ); } 
	TQuaternion( const TVec3<T> &from, const TVec3<T> &to ) { set( from, to ); }
	// create from Euler angles in radians expressed in ZYX rotation order
	TQuaternion( T xRotation, T yRotation, T zRotation ) { set( xRotation, yRotation, zRotation ); }
	TQuaternion( const TMatrix33<T> &m ) { set( m ); }
	TQuaternion( const TMatrix44<T> &m ) { set( m ); }
	template<typename Y>
	explicit TQuaternion( const Y &v )
		: w( QUATCONV<TQuaternion<typename TQuaternion::TYPE>,Y>::getW( v ) )
		, v( QUATCONV<typename TQuaternion::TYPE,Y>::getX( v )
		   , QUATCONV<typename TQuaternion::TYPE,Y>::getY( v )
		   , QUATCONV<typename TQuaternion::TYPE,Y>::getZ( v ) )
	{}
	
	// get axis-angle representation's axis
	TVec3<T> getAxis() const
	{
		T cos_angle = w;
		T invLen = static_cast<T>( 1.0 ) / tmath<T>::sqrt( static_cast<T>( 1.0 ) - cos_angle * cos_angle );

		return v * invLen;
	}
	
	// get axis-angle representation's angle in radians
	T getAngle() const
	{
		T cos_angle = w;
		return tmath<T>::acos( cos_angle ) * 2;
	}

	T getPitch() const
	{
		return tmath<T>::atan2( w * w - v.x * v.x - v.y * v.y + v.z * v.z, (T)2 * ( v.y * v.z + w * v.x ) );
	}

	T getYaw() const
	{
		return tmath<T>::sin( (T)-2 * ( v.x * v.z - w * v.y ) );
	}

	T getRoll() const
	{
		return tmath<T>::atan2( w * w + v.x * v.x - v.y * v.y - v.z * v.z, (T)2 * ( v.x * v.y + w * v.z) );
	}
	
	T dot( const TQuaternion<T> &quat ) const
	{
		return w * quat.w + v.dot( quat.v );
	}
	
	T length() const
	{
		return (T)std::sqrt( w*w + v.lengthSquared() );	
	}

	T lengthSquared() const
	{
		return w * w + v.lengthSquared();	
	}

	TQuaternion<T> inverse() const
	{
		T norm = w * w + v.x * v.x + v.y * v.y + v.z * v.z;
		// if we're the zero quaternion, just return identity
		/*if( ! ( tmath<T>::abs( norm ) < EPSILON_VALUE ) ) {
			return identity();
		}*/

		T normRecip = static_cast<T>( 1.0f ) / norm;
		return TQuaternion<T>( normRecip * w, -normRecip * v.x, -normRecip * v.y, -normRecip * v.z );
	}

	void normalize()
	{
		if( T len = length() ) {
			w /= len;
			v /= len;
		}
		else {
			w = static_cast<T>( 1.0 );
			v = TVec3<T>( 0, 0, 0 );
		}
	}

	TQuaternion<T> normalized() const
	{
		TQuaternion<T> result = *this;
	
		if( T len = length() ) {
			result.w /= len;
			result.v /= len;
		}
		else {
			result.w = static_cast<T>( 1.0 );
			result.v = TVec3<T>( 0, 0, 0 );
		}
		
		return result;
	}

	// For unit quaternion, from Advanced Animation and 
	// Rendering Techniques by Watt and Watt, Page 366:
	TQuaternion<T> log() const
	{
		T theta = tmath<T>::acos( std::min( w, (T) 1.0 ) );

		if( theta == 0 )
			return TQuaternion<T>( v, 0 );
	    
		T sintheta = tmath<T>::sin( theta );
	    
		T k;
		if ( abs( sintheta ) < 1 && abs( theta ) >= 3.402823466e+38F * abs( sintheta ) )
			k = 1;
		else
			k = theta / sintheta;

		return TQuaternion<T>( (T)0, v.x * k, v.y * k, v.z * k );
	}

	// For pure quaternion (zero scalar part):
	// from Advanced Animation and Rendering
	// Techniques by Watt and Watt, Page 366:
	TQuaternion<T> exp() const
	{
		T theta = v.length();
		T sintheta = tmath<T>::sin( theta );
	    
		T k;
		if( abs( theta ) < 1 && abs( sintheta ) >= 3.402823466e+38F * abs( theta ) )
			k = 1;
		else
			k = sintheta / theta;

		T costheta = tmath<T>::cos( theta );

		return TQuaternion<T>( costheta, v.x * k, v.y * k, v.z * k );
	}

	TQuaternion<T> inverted() const
	{
	    T qdot = this->dot( *this );
		return TQuaternion( -v / qdot, w / qdot );
	}

	void invert()
	{
	    T qdot = this->dot( *this );
		set( -v / qdot, w / qdot );		
	}

	void set( T aW, T x, T y, T z )
	{
		w = aW;
		v = TVec3<T>( x, y, z );
	}

#if 1
	void set( const TVec3<T> &from, const TVec3<T> &to )
	{
		TVec3<T> axis = from.cross( to );
		
		set( from.dot( to ), axis.x, axis.y, axis.z );
		normalize();

		w += static_cast<T>( 1.0 );

		if( w <= EPSILON ) {
			if ( from.z * from.z > from.x * from.x ) {
				set( static_cast<T>( 0.0 ), static_cast<T>( 0.0 ), from.z, -from.y );
			}
			else {
				set( static_cast<T>( 0.0 ), from.y, -from.x, static_cast<T>( 0.0 ) );
			}
		}
		
		normalize();
	}
#else
	void set( const TVec3<T> &from, const TVec3<T> &to )
	{
	    TVec3<T> f0 = from.normalized();
		TVec3<T> t0 = to.normalized();

		if( f0.dot( t0 ) >= 0 ) { // The rotation angle is less than or equal to pi/2.
			setRotationInternal (f0, t0, *this);
		}
		else {
			// The angle is greater than pi/2.  After computing h0,
			// which is halfway between f0 and t0, we rotate first
			// from f0 to h0, then from h0 to t0.

			TVec3<T> h0 = (f0 + t0).normalized();

			if( h0.dot( h0 ) != 0 ) {
				setRotationInternal( f0, h0, *this );
				TQuaternion<T> q;
				setRotationInternal( h0, t0, q );
				
				set( q.w*w - q.v.x*v.x - q.v.y*v.y - q.v.z*v.z,
					q.w*v.x + q.v.x*w + q.v.y*v.z - q.v.z*v.y,
					q.w*v.y + q.v.y*w + q.v.z*v.x - q.v.x*v.z,
					q.w*v.z + q.v.z*w + q.v.x*v.y - q.v.y*v.x );
				
				//*this *= q;
			}
			else {
				// f0 and t0 point in exactly opposite directions.
				// Pick an arbitrary axis that is orthogonal to f0,
				// and rotate by pi.

				w = T( 0 );

				TVec3<T> f02 = f0 * f0;

				if( ( f02.x <= f02.y ) && ( f02.x <= f02.z ) )
					v = f0.cross( TVec3<T>( 1, 0, 0 ) ).normalized();
				else if( f02.y <= f02.z )
					v = f0.cross( TVec3<T>( 0, 1, 0 ) ).normalized();
				else
					v = f0.cross( TVec3<T>( 0, 0, 1 ) ).normalized();
			}
		}
	}

	static void setRotationInternal( const TVec3<T> &f0, const TVec3<T> &t0, TQuaternion<T> &q )
	{
		//
		// The following is equivalent to setAxisAngle(n,2*phi),
		// where the rotation axis, is orthogonal to the f0 and
		// t0 vectors, and 2*phi is the angle between f0 and t0.
		//
		// This function is called by setRotation(), above; it assumes
		// that f0 and t0 are normalized and that the angle between
		// them is not much greater than pi/2.  This function becomes
		// numerically inaccurate if f0 and t0 point into nearly
		// opposite directions.
		//

		// Find a normalized vector, h0, that is half way between f0 and t0.
		// The angle between f0 and h0 is phi.
		TVec3<T> h0 = ( f0 + t0 ).normalized();

		// Store the rotation axis and rotation angle.
		q.w = f0.dot( h0 );	//  f0 ^ h0 == cos (phi)
		q.v = f0.cross( h0 );	// (f0 % h0).length() == sin (phi)
	}
#endif

	void set( const TVec3<T> &axis, T radians )
	{
		w = tmath<T>::cos( radians / 2 );
		v = axis.normalized() * tmath<T>::sin( radians / 2 );
	}

	// assumes ZYX rotation order and radians
	void set( T xRotation, T yRotation, T zRotation )
	{
		zRotation *= T( 0.5 );
		yRotation *= T( 0.5 );
		xRotation *= T( 0.5 );

		// get sines and cosines of half angles
		T Cx = tmath<T>::cos( xRotation );
		T Sx = tmath<T>::sin( xRotation );

		T Cy = tmath<T>::cos( yRotation );
		T Sy = tmath<T>::sin( yRotation );

		T Cz = tmath<T>::cos( zRotation );
		T Sz = tmath<T>::sin( zRotation );

		// multiply it out
		w = Cx*Cy*Cz - Sx*Sy*Sz;
		v.x = Sx*Cy*Cz + Cx*Sy*Sz;
		v.y = Cx*Sy*Cz - Sx*Cy*Sz;
		v.z = Cx*Cy*Sz + Sx*Sy*Cx;
	}

	void getAxisAngle( TVec3<T> *axis, T *radians ) const
	{
		T cos_angle = w;
		*radians = tmath<T>::acos( cos_angle ) * 2;
		T invLen = static_cast<T>( 1.0 ) / tmath<T>::sqrt( static_cast<T>( 1.0 ) - cos_angle * cos_angle );

		axis->x = v.x * invLen;
		axis->y = v.y * invLen;
		axis->z = v.z * invLen;
	}

	TQuaternion<T> lerp( T t, const TQuaternion<T> &end ) const
	{
		// get cos of "angle" between quaternions
		float cosTheta = dot( end );

		// initialize result
		TQuaternion<T> result = end * t;

		// if "angle" between quaternions is less than 90 degrees
		if( cosTheta >= EPSILON ) {
			// use standard interpolation
			result += *this * ( static_cast<T>( 1.0 ) - t );
		}
		else {
			// otherwise, take the shorter path
			result += *this * ( t - static_cast<T>( 1.0 ) );
		}
		
		return result;
	}

    // This method does *not* interpolate along the shortest
    // arc between q1 and q2.  If you desire interpolation
    // along the shortest arc, and q1.dot( q2 ) is negative, then
    // consider flipping the second quaternion explicitly.
    //
    // NOTE: the difference between this and slerp isn't clear, but we're using
    // the Don Hatch / ilmbase squad code which explicitly requires this impl. of slerp
    // so I'm leaving it for now
	TQuaternion<T> slerpShortestUnenforced( T t, const TQuaternion<T> &end ) const
	{
	    TQuaternion<T> d = *this - end;
		T lengthD = tmath<T>::sqrt( this->dot( end ) );

		TQuaternion<T> st = *this + end;
		T lengthS = tmath<T>::sqrt( st.dot( st ) );
	
		T a = 2 * tmath<T>::atan2( lengthS, lengthD );
		T s = 1 - t;

		TQuaternion<T> q( *this * ( sinx_over_x( s * a ) / sinx_over_x( a ) * s ) +
				end * ( sinx_over_x( t * a ) / sinx_over_x( a ) * t ) );

		return q.normalized();
	}

	TQuaternion<T> slerp( T t, const TQuaternion<T> &end ) const
	{
		// get cosine of "angle" between quaternions
		T cosTheta = this->dot( end );
		T startInterp, endInterp;

		// if "angle" between quaternions is less than 90 degrees
		if( cosTheta >= EPSILON ) {
			// if angle is greater than zero
			if( ( static_cast<T>( 1.0 ) - cosTheta ) > EPSILON ) {
				// use standard slerp
				T theta = tmath<T>::acos( cosTheta );
				T recipSinTheta = static_cast<T>( 1.0 ) / tmath<T>::sin( theta );

				startInterp = tmath<T>::sin( ( static_cast<T>( 1.0 ) - t ) * theta ) * recipSinTheta;
				endInterp = tmath<T>::sin( t * theta ) * recipSinTheta;
			}
			// angle is close to zero
			else {
				// use linear interpolation
				startInterp = static_cast<T>( 1.0 ) - t;
				endInterp = t;
			}
		}
		// otherwise, take the shorter route
		else {
			// if angle is less than 180 degrees
			if( ( static_cast<T>( 1.0 ) + cosTheta ) > EPSILON ) {
				// use slerp w/negation of start quaternion
				T theta = tmath<T>::acos( -cosTheta );
				T recipSinTheta = static_cast<T>( 1.0 ) / tmath<T>::sin( theta );

				startInterp = tmath<T>::sin( ( t - static_cast<T>( 1.0 ) ) * theta ) * recipSinTheta;
				endInterp = tmath<T>::sin( t * theta ) * recipSinTheta;
			}
			// angle is close to 180 degrees
			else {
				// use lerp w/negation of start quaternion
				startInterp = t - static_cast<T>( 1.0 );
				endInterp = t;
			}
		}
	    
		return *this * startInterp + end * endInterp;
	}

	// Spherical Quadrangle Interpolation -
	// from Advanced Animation and Rendering
	// Techniques by Watt and Watt, Page 366:
	// It constructs a spherical cubic interpolation as 
	// a series of three spherical linear interpolations 
	// of a quadrangle of unit quaternions. 
	TQuaternion<T> squadShortestEnforced( T t, const TQuaternion<T> &qa, const TQuaternion<T> &qb, const TQuaternion<T> &q2 ) const
	{
		TQuaternion<T> r1;
		if( this->dot( q2 ) >= 0 )
			r1 = this->slerpShortestUnenforced( t, q2 );
		else
			r1 = this->slerpShortestUnenforced( t, q2.inverted() );
		
		TQuaternion<T> r2;
		if( qa.dot( qb ) >= 0 )
			r2 = qa.slerpShortestUnenforced( t, qb );
		else
			r2 = qa.slerpShortestUnenforced( t, qb.inverted() );
		
		if( r1.dot( r2 ) >= 0 )
			return r1.slerpShortestUnenforced( 2 * t * (1-t), r2 );
		else
			return r1.slerpShortestUnenforced( 2 * t * (1-t), r2.inverted() );
	}

	TQuaternion<T> squad( T t, const TQuaternion<T> &qa, const TQuaternion<T> &qb, const TQuaternion<T> &q2 ) const
	{
		TQuaternion<T> r1 = this->slerp( t, q2 );	
		TQuaternion<T> r2 = qa.slerp( t, qb );
		return r1.slerp( 2 * t * (1-t), r2 );
	}

	// Spherical Cubic Spline Interpolation -
	// from Advanced Animation and Rendering
	// Techniques by Watt and Watt, Page 366:
	// A spherical curve is constructed using three
	// spherical linear interpolations of a quadrangle
	// of unit quaternions: q1, qa, qb, q2.
	// Given a set of quaternion keys: q0, q1, q2, q3,
	// this routine does the interpolation between
	// q1 and q2 by constructing two intermediate
	// quaternions: qa and qb. The qa and qb are 
	// computed by the intermediate function to 
	// guarantee the continuity of tangents across
	// adjacent cubic segments. The qa represents in-tangent
	// for q1 and the qb represents the out-tangent for q2.
	// 
	// The q1 q2 is the cubic segment being interpolated. 
	// The q0 is from the previous adjacent segment and q3 is 
	// from the next adjacent segment. The q0 and q3 are used
	// in computing qa and qb.
	TQuaternion<T> spline( T t, const TQuaternion<T> &q1,
			   const TQuaternion<T> &q2, const TQuaternion<T> &q3 ) const
	{
		TQuaternion<T> qa = splineIntermediate( *this, q1, q2 );
		TQuaternion<T> qb = splineIntermediate( q1, q2, q3 );
		TQuaternion<T> result = q1.squadShortestEnforced( t, qa, qb, q2 );

		return result;
	}

	void set( const TMatrix33<T> &m )
	{
		//T trace = m.m[0] + m.m[4] + m.m[8];
		T trace = m.trace();
		if ( trace > (T)0.0 )
		{
			T s = tmath<T>::sqrt( trace + (T)1.0 );
			w = s * (T)0.5;
			T recip = (T)0.5 / s;
			v.x = ( m.at(2,1) - m.at(1,2) ) * recip;
			v.y = ( m.at(0,2) - m.at(2,0) ) * recip;
			v.z = ( m.at(1,0) - m.at(0,1) ) * recip;
		}
		else
		{
			unsigned int i = 0;
			if( m.at(1,1) > m.at(0,0) )
				i = 1;
			if( m.at(2,2) > m.at(i,i) )
				i = 2;
			unsigned int j = ( i + 1 ) % 3;
			unsigned int k = ( j + 1 ) % 3;
			T s = tmath<T>::sqrt( m.at(i,i) - m.at(j,j) - m.at(k,k) + (T)1.0 );
			(*this)[i] = (T)0.5 * s;
			T recip = (T)0.5 / s;
			w = ( m.at(k,j) - m.at(j,k) ) * recip;
			(*this)[j] = ( m.at(j,i) + m.at(i,j) ) * recip;
			(*this)[k] = ( m.at(k,i) + m.at(i,k) ) * recip;
		}
	}

	void set( const TMatrix44<T> &m )
	{
		//T trace = m.m[0] + m.m[5] + m.m[10];
		T trace = m.trace();
		if ( trace > (T)0.0 )
		{
			T s = tmath<T>::sqrt( trace + (T)1.0 );
			w = s * (T)0.5;
			T recip = (T)0.5 / s;
			v.x = ( m.at(2,1) - m.at(1,2) ) * recip;
			v.y = ( m.at(0,2) - m.at(2,0) ) * recip;
			v.z = ( m.at(1,0) - m.at(0,1) ) * recip;
		}
		else
		{
			unsigned int i = 0;
			if( m.at(1,1) > m.at(0,0) )
				i = 1;
			if( m.at(2,2) > m.at(i,i) )
				i = 2;
			unsigned int j = ( i + 1 ) % 3;
			unsigned int k = ( j + 1 ) % 3;
			T s = tmath<T>::sqrt( m.at(i,i) - m.at(j,j) - m.at(k,k) + (T)1.0 );
			(*this)[i] = (T)0.5 * s;
			T recip = (T)0.5 / s;
			w = ( m.at(k,j) - m.at(j,k) ) * recip;
			(*this)[j] = ( m.at(j,i) + m.at(i,j) ) * recip;
			(*this)[k] = ( m.at(k,i) + m.at(i,k) ) * recip;
		}
	}


	/** Performs a spherical interpolation between two quaternions and writes the result into the third.
	 * @param pOut Target object to received the interpolated rotation.
	 * @param pStart Start rotation of the interpolation at factor == 0.
	 * @param pEnd End rotation, factor == 1.
	 * @param pFactor Interpolation factor between 0 and 1. Values outside of this range yield undefined results.
	 */
	static void Interpolate( TQuaternion<T>& pOut, const TQuaternion<T>& pStart, const TQuaternion<T>& pEnd, T pFactor);


	// Operators
	TQuaternion<T>& operator=( const TQuaternion<T> &rhs )
	{
		v = rhs.v;
		w = rhs.w;
		return *this;
	}

	template<typename FromT>
	TQuaternion<T>& operator=( const TQuaternion<FromT> &rhs )
	{
		v = rhs.v;
		w = static_cast<T>( rhs.w );
		return *this;
	}

	const TQuaternion<T> operator+( const TQuaternion<T> &rhs ) const
	{
		const TQuaternion<T>& lhs = *this;
		return TQuaternion<T>( lhs.w + rhs.w, lhs.v.x + rhs.v.x, lhs.v.y + rhs.v.y, lhs.v.z + rhs.v.z );  
	}

	// post-multiply operator, similar to matrices, but different from Shoemake
	// Concatenates 'rhs' onto 'this'
	const TQuaternion<T> operator*( const TQuaternion<T> &rhs ) const
	{
		return TQuaternion<T>( rhs.w*w - rhs.v.x*v.x - rhs.v.y*v.y - rhs.v.z*v.z,
                   rhs.w*v.x + rhs.v.x*w + rhs.v.y*v.z - rhs.v.z*v.y,
                   rhs.w*v.y + rhs.v.y*w + rhs.v.z*v.x - rhs.v.x*v.z,
                   rhs.w*v.z + rhs.v.z*w + rhs.v.x*v.y - rhs.v.y*v.x );
	}

	const TQuaternion<T> operator*( T rhs ) const 
	{ 
		return TQuaternion<T>( w * rhs, v.x * rhs, v.y * rhs, v.z * rhs );
	}

	// transform a vector by the quaternion
	const TVec3<T> operator*( const TVec3<T> &vec ) const
	{
		T vMult = T( 2 ) * ( v.x * vec.x + v.y * vec.y + v.z * vec.z );
		T crossMult = T( 2 ) * w;
		T pMult = crossMult * w - T( 1 );

		return TVec3<T>( pMult * vec.x + vMult * v.x + crossMult * ( v.y * vec.z - v.z * vec.y ),
						pMult * vec.y + vMult * v.y + crossMult * ( v.z * vec.x - v.x * vec.z ),
						pMult * vec.z + vMult * v.z + crossMult * ( v.x * vec.y - v.y * vec.x ) );
	}

	const TQuaternion<T> operator-( const TQuaternion<T> &rhs ) const
	{
		const TQuaternion<T>& lhs = *this;
		return TQuaternion<T>( lhs.w - rhs.w, lhs.v.x - rhs.v.x, lhs.v.y - rhs.v.y, lhs.v.z - rhs.v.z );
	}

	TQuaternion<T>& operator+=( const TQuaternion<T> &rhs )
	{
		w += rhs.w;
		v += rhs.v;
		return *this;
	}

	TQuaternion<T>& operator-=( const TQuaternion<T>& rhs )
	{
		w -= rhs.w;
		v -= rhs.v;
		return *this;
	}

	TQuaternion<T>& operator*=( const TQuaternion<T> &rhs )
	{
		TQuaternion q = (*this) * rhs;
		v = q.v;
		w = q.w;
		return *this;
	}

	TQuaternion<T>& operator*=( T rhs )
	{
		w *= rhs;
		v *= rhs;
		return *this;
	}

	bool operator==( const TQuaternion<T> &rhs ) const
	{
		const TQuaternion<T>& lhs = *this;
		return ( std::fabs(lhs.w - rhs.w) < EPSILON ) && lhs.v == rhs.v;
	}

	bool operator!=( const TQuaternion<T> &rhs ) const
	{
		return ! (*this == rhs);
	}

	inline T& operator[]( unsigned int i ) { return (&v.x)[i]; }
	inline const T& operator[]( unsigned int i ) const { return (&v.x)[i]; }

	static TQuaternion<T> identity()
	{
		return TQuaternion();
	}

	// Output
	friend std::ostream& operator <<( std::ostream &oss, const TQuaternion<T> &q )
	{
		oss << q.getAxis() << " @ " << q.getAngle() * ( (T)180 / M_PI ) << "deg";
		return oss;
	}

	TMatrix33<T> toMatrix33() const
	{
		TMatrix33<T> mV;
		T xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

		xs = v.x + v.x;   
		ys = v.y + v.y;
		zs = v.z + v.z;
		wx = w * xs;
		wy = w * ys;
		wz = w * zs;
		xx = v.x * xs;
		xy = v.x * ys;
		xz = v.x * zs;
		yy = v.y * ys;
		yz = v.y * zs;
		zz = v.z * zs;

		mV[0] = T( 1 ) - ( yy + zz );
		mV[3] = xy - wz;
		mV[6] = xz + wy;

		mV[1] = xy + wz;
		mV[4] = T( 1 ) - ( xx + zz );
		mV[7] = yz - wx;

		mV[2] = xz - wy;
		mV[5] = yz + wx;
		mV[8] = T( 1 ) - ( xx + yy );

		return mV;
	}

	TMatrix44<T> toMatrix44() const
	{
		TMatrix44<T> mV;
		T xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

		xs = v.x + v.x;   
		ys = v.y + v.y;
		zs = v.z + v.z;
		wx = w * xs;
		wy = w * ys;
		wz = w * zs;
		xx = v.x * xs;
		xy = v.x * ys;
		xz = v.x * zs;
		yy = v.y * ys;
		yz = v.y * zs;
		zz = v.z * zs;

		mV[0] = T( 1 ) - ( yy + zz );
		mV[4] = xy - wz;
		mV[8] = xz + wy;
		mV[12] = 0;

		mV[1] = xy + wz;
		mV[5] = T( 1 ) - ( xx + zz );
		mV[9] = yz - wx;
		mV[13] = 0;

		mV[2] = xz - wy;
		mV[6] = yz + wx;
		mV[10] = T( 1 ) - ( xx + yy );
		mV[14] = 0;

		mV[3] = 0;
		mV[7] = 0;
		mV[11] = 0;
		mV[15] = T( 1 );

		return mV;
	}

	operator TMatrix44<T>() const { return toMatrix44(); }

 private:
	// From advanced Animation and Rendering
	// Techniques by Watt and Watt, Page 366:
	// computing the inner quadrangle 
	// points (qa and qb) to guarantee tangent
	// continuity.
	static TQuaternion<T> splineIntermediate( const TQuaternion<T> &q0, const TQuaternion<T> &q1, const TQuaternion<T> &q2 )
	{
		TQuaternion<T> q1inv = q1.inverted();
		TQuaternion<T> c1 = q1inv * q2;
		TQuaternion<T> c2 = q1inv * q0;
		TQuaternion<T> c3 = ( c2.log() + c1.log() ) * (T)-0.25;
		TQuaternion<T> qa = q1 * c3.exp();
		return qa.normalized();
	}


public:
	T & x( void );
	T & y( void );
	T & z( void );
};


template<typename T>
inline T & TQuaternion<T>::x( void )		{ return v.x;	}

template<typename T>
inline T & TQuaternion<T>::y( void )		{ return v.y;	}

template<typename T>
inline T & TQuaternion<T>::z( void )		{ return v.z;	}



// ---------------------------------------------------------------------------
// Performs a spherical interpolation between two quaternions 
// Implementation adopted from the gmtl project. All others I found on the net fail in some cases.
// Congrats, gmtl!
template<typename T>
inline void TQuaternion<T>::Interpolate( TQuaternion<T>& pOut, const TQuaternion<T>& pStart, const TQuaternion<T>& pEnd, T pFactor)
{
	// calc cosine theta
	T cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

	// adjust signs (if necessary)
	TQuaternion end = pEnd;
	if( cosom < static_cast<T>(0.0))
	{
		cosom = -cosom;
		end.x = -end.x;   // Reverse all signs
		end.y = -end.y;
		end.z = -end.z;
		end.w = -end.w;
	} 

	// Calculate coefficients
	T sclp, sclq;
	if( (static_cast<T>(1.0) - cosom) > static_cast<T>(0.0001)) // 0.0001 -> some epsillon
	{
		// Standard case (slerp)
		T omega, sinom;
		omega = tmath<T>::acos( cosom); // extract theta from dot product's cos theta
		sinom = tmath<T>::sin( omega);
		sclp  = tmath<T>::sin( (static_cast<T>(1.0) - pFactor) * omega) / sinom;
		sclq  = tmath<T>::sin( pFactor * omega) / sinom;
	} else
	{
		// Very close, do linear interp (because it's faster)
		sclp = static_cast<T>(1.0) - pFactor;
		sclq = pFactor;
	}

	pOut.x = sclp * pStart.x + sclq * end.x;
	pOut.y = sclp * pStart.y + sclq * end.y;
	pOut.z = sclp * pStart.z + sclq * end.z;
	pOut.w = sclp * pStart.w + sclq * end.w;
}


template<typename T>
inline TVec3<T> operator*( const TVec3<T> &vec, const TQuaternion<T> &q )
{
    T vMult = T( 2 ) * ( q.v.x * vec.x + q.v.y * vec.y + q.v.z * vec.z );
    T crossMult = T( 2 ) * q.w;
    T pMult = crossMult * q.w - T( 1 );

    return TVec3<T>( pMult * vec.x + vMult * q.v.x + crossMult * ( q.v.y * vec.z - q.v.z * vec.y ),
                    pMult * vec.y + vMult * q.v.y + crossMult * ( q.v.z * vec.x - q.v.x * vec.z ),
                    pMult * vec.z + vMult * q.v.z + crossMult * ( q.v.x * vec.y - q.v.y * vec.x ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		Typedefs
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef TQuaternion<float>	Quatf;
typedef TQuaternion<double>	Quatd;

#endif // __TQUATERNION_H__
