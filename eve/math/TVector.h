
#pragma once
#ifndef __EVE_MATH_TVECTOR_H__
#define __EVE_MATH_TVECTOR_H__

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


	} // namespace math

} // namespace eve





template<typename T> class TVec3;

template<typename T>
class TVec2
{
 public:
	T x,y;

	TVec2() :x(0), y(0) {}
	TVec2( T nx, T ny ) : x( nx ), y( ny ) {}
	TVec2(T n ) : x( n ), y( n ) {}
	TVec2( const TVec2<T>& src ) : x( src.x ), y( src.y ) {}
	explicit TVec2( const T *d ) : x( d[0] ), y( d[1] ) {}

	template<typename FromT>
	TVec2( const TVec2<FromT>& src )
		: x( static_cast<T>( src.x ) ),y( static_cast<T>( src.y ) )
	{}

	void set( T ax, T ay )
	{
		x = ax; y = ay;
	}

	void set( const TVec2<T> &rhs )
	{
		x = rhs.x; y = rhs.y;
	}

	// Operators
	template<typename FromT>
	TVec2<T>& operator=( const TVec2<FromT>& rhs )
	{
		x = static_cast<T>( rhs.x );
		y = static_cast<T>( rhs.y );
		return * this;
	}

	TVec2<T>& operator=( const TVec2<T>& rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return * this;
	}

	T& operator[]( int32_t n )
	{
#ifndef NDEBUG
		NATIVE_ASSERT( n >= 0 && n <= 1 );
#endif
		return (&x)[n];
	}

	const T& operator[]( int32_t n ) const
	{
#ifndef NDEBUG
		NATIVE_ASSERT( n >= 0 && n <= 1 );
#endif
		return (&x)[n];
	}

	T*	ptr() const { return &(const_cast<TVec2*>( this )->x); }

	const TVec2<T>	operator+( const TVec2<T>& rhs ) const { return TVec2<T>( x + rhs.x, y + rhs.y ); }
	const TVec2<T>	operator-( const TVec2<T>& rhs ) const { return TVec2<T>( x - rhs.x, y - rhs.y ); }
	const TVec2<T>	operator*( const TVec2<T>& rhs ) const { return TVec2<T>( x * rhs.x, y * rhs.y ); }
	const TVec2<T>	operator/( const TVec2<T>& rhs ) const { return TVec2<T>( x / rhs.x, y / rhs.y ); }
	TVec2<T>&	operator+=( const TVec2<T>& rhs ) { x += rhs.x; y += rhs.y; return *this; }
	TVec2<T>&	operator-=( const TVec2<T>& rhs ) { x -= rhs.x; y -= rhs.y; return *this; }
	TVec2<T>&	operator*=( const TVec2<T>& rhs ) { x *= rhs.x; y *= rhs.y; return *this; }
	TVec2<T>&	operator/=( const TVec2<T>& rhs ) { x /= rhs.x; y /= rhs.y; return *this; }

	const TVec2<T>	operator+( T rhs ) const { return TVec2<T>( x + rhs, y + rhs ); }
	const TVec2<T>	operator-( T rhs ) const { return TVec2<T>( x - rhs, y - rhs ); }
	const TVec2<T>	operator*( T rhs ) const { return TVec2<T>( x * rhs, y * rhs ); }
	const TVec2<T>	operator/( T rhs ) const { return TVec2<T>( x / rhs, y / rhs ); }
	TVec2<T>&	operator+=( T rhs )	{ x += rhs;	y += rhs; return *this; }
	TVec2<T>&	operator-=( T rhs ) { x -= rhs; y -= rhs; return *this; }
	TVec2<T>&	operator*=( T rhs ) { x *= rhs; y *= rhs; return *this; }
	TVec2<T>&	operator/=( T rhs ) { x /= rhs; y /= rhs; return *this; }

	TVec2<T>		operator-() const { return TVec2<T>( -x, -y ); } // unary negation

	bool operator==( const TVec2<T> &rhs ) const
	{
		return ( x == rhs.x ) && ( y == rhs.y );
	}

	bool operator!=( const TVec2<T> &rhs ) const
	{
		return ! ( *this == rhs );
	}

	T dot( const TVec2<T> &rhs ) const
	{
		return x * rhs.x + y * rhs.y;
	}

	//! Returns the z component of the cross if the two operands were TVec3's on the XY plane, the equivalent of TVec3(*this).cross( TVec3(rhs) ).z
	T cross( const TVec2<T> &rhs ) const
	{
		return x * rhs.y - y * rhs.x;
	}

	T distance( const TVec2<T> &rhs ) const
	{
		return ( *this - rhs ).length();
	}

	T distanceSquared( const TVec2<T> &rhs ) const
	{
		return ( *this - rhs ).lengthSquared();
	}

	T length() const
	{
		return eve::math::sqrt( x*x + y*y );
	}

	void normalize()
	{
		T invS = static_cast<T>(1) / length();
		x *= invS;
		y *= invS;
	}

	TVec2<T> normalized() const
	{
		T invS = static_cast<T>(1) / length();
		return TVec2<T>( x * invS, y * invS );
	}

	// tests for zero-length
	void safeNormalize()
	{
		T s = lengthSquared();
		if( s > 0 ) {
			T invL = static_cast<T>(1) / eve::math::sqrt( s );
			x *= invL;
			y *= invL;
		}
	}

	TVec2<T> safeNormalized() const
	{
		T s = lengthSquared();
		if( s > 0 ) {
			T invL = static_cast<T>(1) / eve::math::sqrt( s );
			return TVec2<T>( x * invL, y * invL );
		}
		else
			return TVec2<T>::zero();
	}

	void rotate( T radians )
	{
		T cosa = eve::math::cos( radians );
		T sina = eve::math::sin( radians );
		T rx = x * cosa - y * sina;
		y = x * sina + y * cosa;
		x = rx;
	}

	T lengthSquared() const
	{
		return x * x + y * y;
	}

	//! Limits the length of a TVec2 to \a maxLength, scaling it proportionally if necessary.
	void limit( T maxLength )
	{
		T lengthSquared = x * x + y * y;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			x *= ratio;
			y *= ratio;
		}
	}

	//! Returns a copy of the TVec2 with its length limited to \a maxLength, scaling it proportionally if necessary.
	TVec2<T> limited( T maxLength ) const
	{
		T lengthSquared = x * x + y * y;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			return TVec2<T>( x * ratio, y * ratio );
		}
		else
			return *this;
	}

	void invert()
	{
		x = -x;
		y = -y;
	}

	TVec2<T> inverted() const
	{
		return TVec2<T>( -x, -y );
	}

	TVec2<T> lerp( T fact, const TVec2<T>& r ) const
	{
		return (*this) + ( r - (*this) ) * fact;
	}

	void lerpEq( T fact, const TVec2<T> &rhs )
	{
		x = x + ( rhs.x - x ) * fact; y = y + ( rhs.y - y ) * fact;
	}

	EVE_FORCE_INLINE static bool equal( TVec2<T> const & x, TVec2<T> const & y )
	{
		return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y));
	}

	EVE_FORCE_INLINE static bool equal( TVec2<T> const & x, TVec2<T> const & y, T epsilon )
	{
		return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon));
	}

	inline bool equal( TVec2<T> const & other )
	{
		return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y));
	}

	inline bool equal( TVec2<T> const & other, T epsilon )
	{
		return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon));
	}

	// GLSL inspired swizzling functions.
	TVec2<T> xx() const { return TVec2<T>(x, x); }
	TVec2<T> xy() const { return TVec2<T>(x, y); }
	TVec2<T> yx() const { return TVec2<T>(y, x); }
	TVec2<T> yy() const { return TVec2<T>(y, y); }

	TVec3<T> xxx() const { return TVec3<T>(x, x, x); }
	TVec3<T> xxy() const { return TVec3<T>(x, x, y); }
	TVec3<T> xyx() const { return TVec3<T>(x, y, x); }
	TVec3<T> xyy() const { return TVec3<T>(x, y, y); }
	TVec3<T> yxx() const { return TVec3<T>(y, x, x); }
	TVec3<T> yxy() const { return TVec3<T>(y, x, y); }
	TVec3<T> yyx() const { return TVec3<T>(y, y, x); }
	TVec3<T> yyy() const { return TVec3<T>(y, y, y); }

	EVE_FORCE_INLINE static TVec2<T> max()
	{
		return TVec2<T>( std::numeric_limits<T>::max(), std::numeric_limits<T>::max() );
	}

	EVE_FORCE_INLINE static TVec2<T> zero()
	{
		return TVec2<T>( 0, 0 );
	}

	EVE_FORCE_INLINE static TVec2<T> one()
	{
		return TVec2<T>( 1, 1 );
	}

	EVE_FORCE_INLINE static TVec2<T> xAxis( void ) { return TVec2<T>( 1, 0 ); }
	EVE_FORCE_INLINE static TVec2<T> yAxis( void ) { return TVec2<T>( 0, 1 ); }

	EVE_FORCE_INLINE static TVec2<T> xAxisNeg( void ) { return TVec2<T>(-1, 0 ); }
	EVE_FORCE_INLINE static TVec2<T> yAxisNeg( void ) { return TVec2<T>( 0,-1 ); }

	EVE_FORCE_INLINE static TVec2<T> NaN()   { return TVec2<T>( eve::math::NaN(), eve::math::NaN() ); }
};



template<typename T>
class TVec3
{
public:
	T x,y,z;

	TVec3() :x(0), y(0), z(0) {}
	TVec3( T nx, T ny, T nz )
		: x( nx ), y( ny ), z( nz )
	{}
	TVec3( const TVec3<T> &src )
		: x( src.x ), y( src.y ), z( src.z )
	{}
	TVec3( const TVec2<T> &v2, T aZ )
		: x( v2.x ), y( v2.y ), z( aZ )
	{}
	explicit TVec3( const TVec2<T> &v2 )
		: x( v2.x ), y( v2.y ), z( 0 )
	{}
	explicit TVec3( const T *d ) : x( d[0] ), y( d[1] ), z( d[2] ) {}
	template<typename FromT>
	TVec3( const TVec3<FromT> &src )
		: x( static_cast<T>( src.x ) ), y( static_cast<T>( src.y ) ), z( static_cast<T>( src.z ) )
	{}

	void set( T ax, T ay, T az )
	{
		x = ax; y = ay; z = az;
	}

	void set( const TVec3<T> &rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z;
	}

	TVec3<T>& operator=( const TVec3<T> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return * this;
	}

	template<typename FromT>
	TVec3<T>& operator=( const TVec3<FromT> &rhs )
	{
		x = static_cast<T>( rhs.x );
		y = static_cast<T>( rhs.y );
		z = static_cast<T>( rhs.z );
		return * this;
	}

	T& operator[]( int32_t n )
	{
		EVE_ASSERT( n >= 0 && n <= 2 );
		return (&x)[n];
	}

	const T& operator[]( int32_t n ) const
	{
		EVE_ASSERT(n >= 0 && n <= 2);
		return (&x)[n];
	}

	T*	ptr() const { return &(const_cast<TVec3*>( this )->x); }

	const TVec3<T>	operator+( const TVec3<T>& rhs ) const { return TVec3<T>( x + rhs.x, y + rhs.y, z + rhs.z ); }
	const TVec3<T>	operator-( const TVec3<T>& rhs ) const { return TVec3<T>( x - rhs.x, y - rhs.y, z - rhs.z ); }
	const TVec3<T>	operator*( const TVec3<T>& rhs ) const { return TVec3<T>( x * rhs.x, y * rhs.y, z * rhs.z ); }
	const TVec3<T>	operator/( const TVec3<T>& rhs ) const { return TVec3<T>( x / rhs.x, y / rhs.y, z / rhs.z ); }
	TVec3<T>&	operator+=( const TVec3<T>& rhs ) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	TVec3<T>&	operator-=( const TVec3<T>& rhs ) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	TVec3<T>&	operator*=( const TVec3<T>& rhs ) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
	TVec3<T>&	operator/=( const TVec3<T>& rhs ) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

	const TVec3<T>	operator+( T rhs ) const { return TVec3<T>( x + rhs, y + rhs, z + rhs ); }
	const TVec3<T>	operator-( T rhs ) const { return TVec3<T>( x - rhs, y - rhs, z - rhs ); }
	const TVec3<T>	operator*( T rhs ) const { return TVec3<T>( x * rhs, y * rhs, z * rhs ); }
	const TVec3<T>	operator/( T rhs ) const { return TVec3<T>( x / rhs, y / rhs, z / rhs ); }
	TVec3<T>&	operator+=( T rhs ) { x += rhs; y += rhs; z += rhs; return *this; }
	TVec3<T>&	operator-=( T rhs ) { x -= rhs; y -= rhs; z -= rhs; return *this; }
	TVec3<T>&	operator*=( T rhs ) { x *= rhs; y *= rhs; z *= rhs; return *this; }
	TVec3<T>&	operator/=( T rhs ) { x /= rhs; y /= rhs; z /= rhs; return *this; }

	TVec3<T>		operator-() const { return TVec3<T>( -x, -y, -z ); } // unary negation

	bool operator==( const TVec3<T>& rhs ) const
	{
		return ( x == rhs.x ) && ( y == rhs.y ) && ( z == rhs.z );
	}

	bool operator!=( const TVec3<T>& rhs ) const
	{
		return !( *this == rhs );
	}

	T dot( const TVec3<T> &rhs ) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	EVE_FORCE_INLINE static T dot(TVec3<T> const & x, TVec3<T> const & y)
	{
		return x.x * y.x + x.y * y.y;
	}

	TVec3<T> cross( const TVec3<T> &rhs ) const
	{
		return TVec3<T>( y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y );
	}

	EVE_FORCE_INLINE static TVec3<T> cross
		(
		TVec3<T> const & x,
		TVec3<T> const & y
		)
	{
		return TVec3<T>(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y);
	}

	EVE_FORCE_INLINE static bool equal(TVec3<T> const & x, TVec3<T> const & y)
	{
		return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y) && eve::math::equal(x.z, y.z));
	}

	EVE_FORCE_INLINE static bool equal(TVec3<T> const & x, TVec3<T> const & y, T epsilon)
	{
		return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon) && eve::math::equal(x.z, y.z, epsilon));
	}

	inline bool equal(TVec3<T> const & other)
	{
		return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y) && eve::math::equal(z, other.z));
	}

	inline bool equal(TVec3<T> const & other, T epsilon)
	{
		return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon) && eve::math::equal(z, other.z, epsilon));
	}

	EVE_FORCE_INLINE static TVec3<T> normalize(const TVec3<T> & p_v)
	{
		T length = eve::math::sqrt(p_v.x*p_v.x + p_v.y*p_v.y + p_v.z*p_v.z);

		T invS = 1.0f / length;

		return TVec3<T>(p_v.x * invS, p_v.y * invS, p_v.z * invS);
	}

	T distance( const TVec3<T> &rhs ) const
	{
		return ( *this - rhs ).length();
	}

	T distanceSquared( const TVec3<T> &rhs ) const
	{
		return ( *this - rhs ).lengthSquared();
	}

	T length( void ) const
	{
		return eve::math::sqrt( x*x + y*y + z*z );
	}

	T lengthSquared( void ) const
	{
		return x*x + y*y + z*z;
	}

	//! Limits the length of a TVec3 to \a maxLength, scaling it proportionally if necessary.
	void limit( T maxLength )
	{
		T lengthSquared = x * x + y * y + z * z;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			x *= ratio;
			y *= ratio;
			z *= ratio;
		}
	}

	//! Returns a copy of the TVec3 with its length limited to \a maxLength, scaling it proportionally if necessary.
	TVec3<T> limited( T maxLength ) const
	{
		T lengthSquared = x * x + y * y + z * z;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			return TVec3<T>( x * ratio, y * ratio, z * ratio );
		}
		else
			return *this;
	}

	void invert( void )
	{
		x = -x; y = -y; z = -z;
	}

	TVec3<T> inverted( void ) const
	{
		return TVec3<T>( -x, -y, -z );
	}

	void normalize( void )
	{
		T invS = ((T)1) / length();
		x *= invS;
		y *= invS;
		z *= invS;
	}

	TVec3<T> normalized( void ) const
	{
		T invS = ((T)1) / length();
		return TVec3<T>( x * invS, y * invS, z * invS );
	}

	// tests for zero-length
	void safeNormalize( void )
	{
		T s = lengthSquared();
		if( s > 0 ) {
			T invS = static_cast<T>(1) / eve::math::sqrt( s );
			x *= invS;
			y *= invS;
			z *= invS;
		}
	}

	TVec3<T> safeNormalized( void ) const
	{
		T s = lengthSquared();
		if( s > 0 ) {
			float invS = static_cast<T>(1) / eve::math::sqrt(s);
			return TVec3<T>( x * invS, y * invS, z * invS );
		}
		else
			return *this;
	}

	//! Returns a vector which is orthogonal to \a this
	TVec3<T> getOrthogonal( void ) const
	{
		if (eve::math::abs(y) < static_cast<T>(0.99)) // abs(dot(u, Y)), somewhat arbitrary epsilon
			return TVec3<T>( -z, 0, x ); // cross( this, Y )
		else
			return TVec3<T>( 0, z, -y ); // cross( this, X )
	}

	void rotateX( T angle )
	{
		T sina = eve::math::sin(angle);
		T cosa = eve::math::cos(angle);
		T ry = y * cosa - z * sina;
		T rz = y * sina + z * cosa;
		y = ry;
		z = rz;
	}

	void rotateY( T angle )
	{
		T sina = eve::math::sin(angle);
		T cosa = eve::math::cos(angle);
		T rx = x * cosa - z * sina;
		T rz = x * sina + z * cosa;
		x = rx;
		z = rz;
	}

	void rotateZ( T angle )
	{
		T sina = eve::math::sin(angle);
		T cosa = eve::math::cos(angle);
		T rx = x * cosa - y * sina;
		T ry = x * sina + y * cosa;
		x = rx;
		y = ry;
	}

	void rotate( TVec3<T> axis, T angle )
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

	TVec3<T> lerp( T fact, const TVec3<T> &rhs ) const
	{
		return (*this) + (rhs - (*this)) * fact;
	}

	void lerpEq( T fact, const TVec3<T> &rhs )
	{
		x = x + ( rhs.x - x ) * fact; y = y + ( rhs.y - y ) * fact; z = z + ( rhs.z - z ) * fact;
	}

	void rotateAroundAxis( const TVec3<T> & axis, T angle )
	{
		TVec3<T> vec( x, y, z );
		vec = TVec3<T>::rotate_around_axis( vec, axis, angle );

		x = vec.x;
		y = vec.y;
		z = vec.z; 
	}

	//--------------------------------------------------------------------------------------------

	//Rotate vector v around arbitrary axis, axis for angle radians
	//It can only rotate around an axis through our object, to rotate around another axis:
	//first translate the object to the axis, then use this function, then translate back in the new direction.
	EVE_FORCE_INLINE static TVec3<T> rotate_around_axis( const TVec3<T> & v, const TVec3<T> & axis, T angle )
	{
		if( (v.x == 0.0) && (v.y == 0.0) && (v.z == 0.0) ) { return TVec3<T>(); }

		TVec3<T> w;
		T c, s, t;

		TVec3<T> naxis = axis.normalized();

		// Calculate parameters of the rotation matrix.
		c = eve::math::cos( angle );
		s = eve::math::sin( angle );
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

	//<! Gives the angle between two 3D vectors (in radians)
	EVE_FORCE_INLINE static T angle( const TVec3<T> & v, const TVec3<T> & w )
	{
		// dot product(v,w) = length(v)*length(w)*cos(angle) ==> angle = acos(dot/(length(v)*length(w))) = acos(dot(norm(v)*norm(w)));
		T cosineOfAngle = v.normalized().dot( w.normalized() );
		// for acos, the value has to be between -1.0 and 1.0, but due to numerical imprecisions it sometimes comes outside this range
		if( cosineOfAngle > 1.0 ) { cosineOfAngle =  1.0; }
		if( cosineOfAngle < -1.0) { cosineOfAngle = -1.0; }

		return -eve::math::acos( cosineOfAngle );
	}

	EVE_FORCE_INLINE static T LengthSquared(const TVec3<T> &rhs)
	{
		return rhs.x*rhs.x + rhs.y*rhs.y + rhs.z*rhs.z;
	}

	EVE_FORCE_INLINE static TVec3<T> max(void)
	{
		return TVec3<T>( std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() );
	}

	EVE_FORCE_INLINE static TVec3<T> zero(void)
	{
		return TVec3<T>( static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( 0 ) );
	}

	EVE_FORCE_INLINE static TVec3<T> one( void )
	{
		return TVec3<T>( static_cast<T>( 1 ), static_cast<T>( 1 ), static_cast<T>( 1 ) );
	}

	EVE_FORCE_INLINE static TVec3<T> view_direction( void )
	{
		return TVec3<T>( static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( -1 ) );
	}

	EVE_FORCE_INLINE static TVec3<T> world_up( void )
	{
		return TVec3<T>( static_cast<T>( 0 ), static_cast<T>( 1 ), static_cast<T>( 0 ) );
	}

	TVec3<T> slerp( T fact, const TVec3<T> &r ) const
	{
		T cosAlpha, alpha, sinAlpha;
		T t1, t2;
		TVec3<T> result;

		// get cosine of angle between vectors (-1 -> 1)
		cosAlpha = this->dot( r );

		// get angle (0 -> pi)
		alpha = eve::math::acos( cosAlpha );

		// get sine of angle between vectors (0 -> 1)
		sinAlpha = eve::math::sin( alpha );

		// this breaks down when sinAlpha = 0, i.e. alpha = 0 or pi
		t1 = eve::math::sin( ((T)1 - fact) * alpha) / sinAlpha;
		t2 = eve::math::sin( fact * alpha ) / sinAlpha;

		// interpolate src vectors
		return *this * t1 + r * t2;
	}

	// derived from but not equivalent to Quaternion::squad
	TVec3<T> squad( T t, const TVec3<T> &tangentA, const TVec3<T> &tangentB, const TVec3<T> &end ) const
	{
		TVec3<T> r1 = this->slerp( t, end );
		TVec3<T> r2 = tangentA.slerp( t, tangentB );
		return r1.slerp( 2 * t * (1-t), r2 );
	}

	// GLSL inspired swizzling functions.
	EVE_FORCE_INLINE TVec2<T> xx() const { return TVec2<T>(x, x); }
	EVE_FORCE_INLINE TVec2<T> xy() const { return TVec2<T>(x, y); }
	EVE_FORCE_INLINE TVec2<T> xz() const { return TVec2<T>(x, z); }
	EVE_FORCE_INLINE TVec2<T> yx() const { return TVec2<T>(y, x); }
	EVE_FORCE_INLINE TVec2<T> yy() const { return TVec2<T>(y, y); }
	EVE_FORCE_INLINE TVec2<T> yz() const { return TVec2<T>(y, z); }
	EVE_FORCE_INLINE TVec2<T> zx() const { return TVec2<T>(z, x); }
	EVE_FORCE_INLINE TVec2<T> zy() const { return TVec2<T>(z, y); }
	EVE_FORCE_INLINE TVec2<T> zz() const { return TVec2<T>(z, z); }

	EVE_FORCE_INLINE TVec3<T> xxx() const { return TVec3<T>(x, x, x); }
	EVE_FORCE_INLINE TVec3<T> xxy() const { return TVec3<T>(x, x, y); }
	EVE_FORCE_INLINE TVec3<T> xxz() const { return TVec3<T>(x, x, z); }
	EVE_FORCE_INLINE TVec3<T> xyx() const { return TVec3<T>(x, y, x); }
	EVE_FORCE_INLINE TVec3<T> xyy() const { return TVec3<T>(x, y, y); }
	EVE_FORCE_INLINE TVec3<T> xyz() const { return TVec3<T>(x, y, z); }
	EVE_FORCE_INLINE TVec3<T> xzx() const { return TVec3<T>(x, z, x); }
	EVE_FORCE_INLINE TVec3<T> xzy() const { return TVec3<T>(x, z, y); }
	EVE_FORCE_INLINE TVec3<T> xzz() const { return TVec3<T>(x, z, z); }
	EVE_FORCE_INLINE TVec3<T> yxx() const { return TVec3<T>(y, x, x); }
	EVE_FORCE_INLINE TVec3<T> yxy() const { return TVec3<T>(y, x, y); }
	EVE_FORCE_INLINE TVec3<T> yxz() const { return TVec3<T>(y, x, z); }
	EVE_FORCE_INLINE TVec3<T> yyx() const { return TVec3<T>(y, y, x); }
	EVE_FORCE_INLINE TVec3<T> yyy() const { return TVec3<T>(y, y, y); }
	EVE_FORCE_INLINE TVec3<T> yyz() const { return TVec3<T>(y, y, z); }
	EVE_FORCE_INLINE TVec3<T> yzx() const { return TVec3<T>(y, z, x); }
	EVE_FORCE_INLINE TVec3<T> yzy() const { return TVec3<T>(y, z, y); }
	EVE_FORCE_INLINE TVec3<T> yzz() const { return TVec3<T>(y, z, z); }
	EVE_FORCE_INLINE TVec3<T> zxx() const { return TVec3<T>(z, x, x); }
	EVE_FORCE_INLINE TVec3<T> zxy() const { return TVec3<T>(z, x, y); }
	EVE_FORCE_INLINE TVec3<T> zxz() const { return TVec3<T>(z, x, z); }
	EVE_FORCE_INLINE TVec3<T> zyx() const { return TVec3<T>(z, y, x); }
	EVE_FORCE_INLINE TVec3<T> zyy() const { return TVec3<T>(z, y, y); }
	EVE_FORCE_INLINE TVec3<T> zyz() const { return TVec3<T>(z, y, z); }
	EVE_FORCE_INLINE TVec3<T> zzx() const { return TVec3<T>(z, z, x); }
	EVE_FORCE_INLINE TVec3<T> zzy() const { return TVec3<T>(z, z, y); }
	EVE_FORCE_INLINE TVec3<T> zzz() const { return TVec3<T>(z, z, z); }

	EVE_FORCE_INLINE static TVec3<T> xAxis(void) { return TVec3<T>(1, 0, 0); }
	EVE_FORCE_INLINE static TVec3<T> yAxis(void) { return TVec3<T>(0, 1, 0); }
	EVE_FORCE_INLINE static TVec3<T> zAxis(void) { return TVec3<T>(0, 0, 1); }

	EVE_FORCE_INLINE static TVec3<T> xAxisNeg(void) { return TVec3<T>(-1, 0, 0); }
	EVE_FORCE_INLINE static TVec3<T> yAxisNeg(void) { return TVec3<T>(0, -1, 0); }
	EVE_FORCE_INLINE static TVec3<T> zAxisNeg(void) { return TVec3<T>(0, 0, -1); }

	EVE_FORCE_INLINE static TVec3<T> NaN()   { return TVec3<T>(eve::math::NaN(), eve::math::NaN(), eve::math::NaN()); }
};



template <class T>
class TVec4
{
 public:
	T x,y,z,w;

	TVec4()
		: x( 0 ), y( 0 ), z( 0 ), w( 0 )
	{}
	TVec4( T nx, T ny, T nz, T nw = 0 )
		: x( nx ), y( ny ), z( nz ), w( nw )
	{}
	TVec4( const TVec3<T>& src, T aW = 0 )
		: x( src.x ), y( src.y ), z( src.z ), w( aW )
	{}
	TVec4( const TVec4<T>& src )
		: x( src.x ), y( src.y ), z( src.z ), w( src.w )
	{}
	template<typename FromT>
	TVec4( const TVec4<FromT>& src )
		: x( static_cast<T>( src.x ) ), y( static_cast<T>( src.y ) ), z( static_cast<T>( src.z ) ),w( static_cast<T>( src.w ) )
	{}
	explicit TVec4( const T *d ) : x( d[0] ), y( d[1] ), z( d[2] ), w( d[3] ) {}

	explicit TVec4(const T d) : x(d), y(d), z(d), w(d) {}
	
	void set( T ax, T ay, T az, T aw )
	{
		x = ax; y = ay; z = az; w = aw;
	}
	
	void set( const TVec4<T> &rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
	}
	
	TVec4<T>& operator=( const TVec4<T>& rhs )
	{
		x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w;
		return *this;
	}

	template<typename FromT>
	TVec4<T>& operator=( const TVec4<FromT>& rhs )
	{
		x = static_cast<T>(rhs.x); y = static_cast<T>(rhs.y); z = static_cast<T>(rhs.z); w = static_cast<T>(rhs.w);
		return *this;
	}

	T& operator[]( int32_t n )
	{
#ifndef NDEBUG
		NATIVE_ASSERT( n >= 0 && n <= 3 );
#endif
		return (&x)[n];
	}

	const T& operator[]( int32_t n )  const
	{
#ifndef NDEBUG
		NATIVE_ASSERT( n >= 0 && n <= 3 );
#endif
		return (&x)[n];
	}

	T*	ptr() const { return &(const_cast<TVec4*>( this )->x); }

	const TVec4<T>	operator+( const TVec4<T>& rhs ) const { return TVec4<T>( x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w ); }
	const TVec4<T>	operator-( const TVec4<T>& rhs ) const { return TVec4<T>( x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w ); }
	const TVec4<T>	operator*( const TVec4<T>& rhs ) const { return TVec4<T>( x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w ); }
	const TVec4<T>	operator/( const TVec4<T>& rhs ) const { return TVec4<T>( x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w ); }
	TVec4<T>&		operator+=( const TVec4<T>& rhs ) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
	TVec4<T>&		operator-=( const TVec4<T>& rhs ) {	x -= rhs.x;	y -= rhs.y;	z -= rhs.z;	w -= rhs.w;	return *this; }
	TVec4<T>&		operator*=( const TVec4<T>& rhs ) { x *= rhs.x; y *= rhs.y; z *= rhs.z;	w *= rhs.w;	return *this; }
	TVec4<T>&		operator/=( const TVec4<T>& rhs ) {	x /= rhs.x;	y /= rhs.y;	z /= rhs.z;	w /= rhs.w;	return *this; }

	const TVec4<T>	operator+( T rhs ) const { return TVec4<T>( x + rhs, y + rhs, z + rhs, w + rhs ); }
	const TVec4<T>	operator-( T rhs ) const { return TVec4<T>( x - rhs, y - rhs, z - rhs, w - rhs ); }
	const TVec4<T>	operator*( T rhs ) const { return TVec4<T>( x * rhs, y * rhs, z * rhs, w * rhs ); }
	const TVec4<T>	operator/( T rhs ) const { return TVec4<T>( x / rhs, y / rhs, z / rhs, w / rhs ); }
	TVec4<T>&		operator+=( T rhs ) {	x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
	TVec4<T>&		operator-=( T rhs ) {	x -= rhs; y -= rhs; z -= rhs; w -= rhs;	return * this; }
	TVec4<T>&		operator*=( T rhs ) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return * this; }
	TVec4<T>&		operator/=( T rhs ) { x /= rhs; y /= rhs; z /= rhs; w /= rhs;	return * this; }

	TVec4<T>			operator-() const { return TVec4<T>( -x, -y, -z, -w ); } // unary negation

	bool operator==( const TVec4<T>& rhs ) const
	{
		return ( x == rhs.x ) && ( y == rhs.y ) && ( z == rhs.z ) && ( w == rhs.w );
	}

	bool operator!=( const TVec4<T>& rhs ) const 
	{ 
		return ! (*this == rhs); 
	}

	T dot( const TVec4<T> &rhs ) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	TVec4<T> cross( const TVec4<T> &rhs ) const
	{
		return TVec4<T>( y*rhs.z - rhs.y*z, z*rhs.x - rhs.z*x, x*rhs.y - rhs.x*y );
	}

	EVE_FORCE_INLINE static bool equal(TVec4<T> const & x, TVec4<T> const & y)
	{
		return (eve::math::equal(x.x, y.x) && eve::math::equal(x.y, y.y) && eve::math::equal(x.z, y.z) && eve::math::equal(x.w, y.w));
	}

	EVE_FORCE_INLINE static bool equal( TVec4<T> const & x, TVec4<T> const & y, T epsilon )
	{
		return (eve::math::equal(x.x, y.x, epsilon) && eve::math::equal(x.y, y.y, epsilon) && eve::math::equal(x.z, y.z, epsilon) && eve::math::equal(x.w, y.w, epsilon));
	}

	inline bool equal( TVec4<T> const & other )
	{
		return (eve::math::equal(x, other.x) && eve::math::equal(y, other.y) && eve::math::equal(z, other.z) && eve::math::equal(w, other.w));
	}

	inline bool equal( TVec4<T> const & other, T epsilon )
	{
		return (eve::math::equal(x, other.x, epsilon) && eve::math::equal(y, other.y, epsilon) && eve::math::equal(z, other.z, epsilon) && eve::math::equal(w, other.w, epsilon));
	}

	T distance( const TVec4<T> &rhs ) const
	{
		return ( *this - rhs ).length();
	}

	T distanceSquared( const TVec4<T> &rhs ) const
	{
		return ( *this - rhs ).lengthSquared();
	}

	T length() const
	{
		// For most vector operations, this assumes w to be zero.
		return eve::math::sqrt( x*x + y*y + z*z + w*w );
	}

	T lengthSquared( void ) const
	{
		// For most vector operations, this assumes w to be zero.
		return x*x + y*y + z*z + w*w;
	}

	void normalize( void )
	{
		T invS = static_cast<T>(1) / length();
		x *= invS;
		y *= invS;
		z *= invS;
		w *= invS;
	}
	
	TVec4<T> normalized() const 
	{
		T invS = static_cast<T>(1) / length();
		return TVec4<T>( x*invS, y*invS, z*invS, w*invS );
	}

	// Tests for zero-length
	void safeNormalize()
	{
		T s = lengthSquared();
		if( s > 0 ) {
			T invS = static_cast<T>(1) / eve::math::sqrt(s);
			x *= invS;
			y *= invS;
			z *= invS;
			w  = (T)0;
		}
	}

	//! Limits the length of a TVec4 to \a maxLength, scaling it proportionally if necessary.
	void limit( T maxLength )
	{
		T lenSq = lengthSquared();

		if( ( lenSq > maxLength * maxLength ) && ( lenSq > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lenSq );
			x *= ratio;
			y *= ratio;
			z *= ratio;
			w *= ratio;
		}
	
		/*
		T lengthSquared = x * x + y * y + z * z + w * w;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			x *= ratio;
			y *= ratio;
			z *= ratio;
			w *= ratio;
		}
		*/
	}

	//! Returns a copy of the TVec4 with its length limited to \a maxLength, scaling it proportionally if necessary.
	TVec4<T> limited( T maxLength ) const
	{
		T lenSq = lengthSquared();

		if( ( lenSq > maxLength * maxLength ) && ( lenSq > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lenSq );
			return TVec4<T>( x * ratio, y * ratio, z * ratio, w * ratio );
		}
		else
			return *this;

		/*
		T lengthSquared = x * x + y * y + z * z + w * w;

		if( ( lengthSquared > maxLength * maxLength ) && ( lengthSquared > 0 ) ) {
			T ratio = maxLength / eve::math::sqrt( lengthSquared );
			return TVec4<T>( x * ratio, y * ratio, z * ratio, w * ratio );
		}
		else
			return *this;
		*/
	}

	void invert( void )
	{
		x = -x; y = -y; z = -z; w = -w;
	}

	TVec4<T> inveerted( void ) const
	{
		return TVec4<T>( -x, -y, -z, -w );
	}

	TVec4<T> lerp( T fact, const TVec4<T>& r ) const
	{
		return (*this) + ( r - (*this) ) * fact;
	}

	void lerpEq( T fact, const TVec4<T> &rhs )
	{
		x = x + ( rhs.x - x ) * fact; y = y + ( rhs.y - y ) * fact; z = z + ( rhs.z - z ) * fact; w = w + ( rhs.w - w ) * fact;
	}

	EVE_FORCE_INLINE static TVec4<T> max()
	{
		return TVec4<T>( std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() );
	}

	EVE_FORCE_INLINE static TVec4<T> zero()
	{
		return TVec4<T>( static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( 0 ) );
	}

	EVE_FORCE_INLINE static TVec4<T> one()
	{
		return TVec4<T>( static_cast<T>( 1 ), static_cast<T>( 1 ), static_cast<T>( 1 ), static_cast<T>( 1 ) );
	}

	TVec4<T> slerp( T fact, const TVec3<T> &r ) const
	{
		T cosAlpha, alpha, sinAlpha;
		T t1, t2;
		TVec4<T> result;

		// get cosine of angle between vectors (-1 -> 1)
		cosAlpha = this->dot( r );

		// get angle (0 -> pi)
		alpha = eve::math::acos( cosAlpha );

		// get sine of angle between vectors (0 -> 1)
		sinAlpha = eve::math::sin( alpha );

		// this breaks down when sinAlpha = 0, i.e. alpha = 0 or pi
		t1 = eve::math::sin( ((T)1 - fact) * alpha) / sinAlpha;
		t2 = eve::math::sin( fact * alpha ) / sinAlpha;

		// interpolate src vectors
		return *this * t1 + r * t2;
	}

	// derived from but not equivalent to Quaternion::squad
	TVec4<T> squad( T t, const TVec4<T> &tangentA, const TVec4<T> &tangentB, const TVec4<T> &end ) const
	{
		TVec4<T> r1 = this->slerp( t, end );
		TVec4<T> r2 = tangentA.slerp( t, tangentB );
		return r1.slerp( 2 * t * (1-t), r2 );
	}

	// GLSL inspired swizzling functions.
	TVec2<T> xx() const { return TVec2<T>(x, x); }
	TVec2<T> xy() const { return TVec2<T>(x, y); }
	TVec2<T> xz() const { return TVec2<T>(x, z); }
	TVec2<T> xw() const { return TVec2<T>(x, w); }
	TVec2<T> yx() const { return TVec2<T>(y, x); }
	TVec2<T> yy() const { return TVec2<T>(y, y); }
	TVec2<T> yz() const { return TVec2<T>(y, z); }
	TVec2<T> yw() const { return TVec2<T>(y, w); }
	TVec2<T> zx() const { return TVec2<T>(z, x); }
	TVec2<T> zy() const { return TVec2<T>(z, y); }
	TVec2<T> zz() const { return TVec2<T>(z, z); }
	TVec2<T> zw() const { return TVec2<T>(z, w); }
	TVec2<T> wx() const { return TVec2<T>(w, x); }
	TVec2<T> wy() const { return TVec2<T>(w, y); }
	TVec2<T> wz() const { return TVec2<T>(w, z); }
	TVec2<T> ww() const { return TVec2<T>(w, w); }

	TVec3<T> xxx() const { return TVec3<T>(x, x, x); }
	TVec3<T> xxy() const { return TVec3<T>(x, x, y); }
	TVec3<T> xxz() const { return TVec3<T>(x, x, z); }
	TVec3<T> xyx() const { return TVec3<T>(x, y, x); }
	TVec3<T> xyy() const { return TVec3<T>(x, y, y); }
	TVec3<T> xyz() const { return TVec3<T>(x, y, z); }
	TVec3<T> xzx() const { return TVec3<T>(x, z, x); }
	TVec3<T> xzy() const { return TVec3<T>(x, z, y); }
	TVec3<T> xzz() const { return TVec3<T>(x, z, z); }
	TVec3<T> yxx() const { return TVec3<T>(y, x, x); }
	TVec3<T> yxy() const { return TVec3<T>(y, x, y); }
	TVec3<T> yxz() const { return TVec3<T>(y, x, z); }
	TVec3<T> yyx() const { return TVec3<T>(y, y, x); }
	TVec3<T> yyy() const { return TVec3<T>(y, y, y); }
	TVec3<T> yyz() const { return TVec3<T>(y, y, z); }
	TVec3<T> yzx() const { return TVec3<T>(y, z, x); }
	TVec3<T> yzy() const { return TVec3<T>(y, z, y); }
	TVec3<T> yzz() const { return TVec3<T>(y, z, z); }
	TVec3<T> zxx() const { return TVec3<T>(z, x, x); }
	TVec3<T> zxy() const { return TVec3<T>(z, x, y); }
	TVec3<T> zxz() const { return TVec3<T>(z, x, z); }
	TVec3<T> zyx() const { return TVec3<T>(z, y, x); }
	TVec3<T> zyy() const { return TVec3<T>(z, y, y); }
	TVec3<T> zyz() const { return TVec3<T>(z, y, z); }
	TVec3<T> zzx() const { return TVec3<T>(z, z, x); }
	TVec3<T> zzy() const { return TVec3<T>(z, z, y); }
	TVec3<T> zzz() const { return TVec3<T>(z, z, z); }

	TVec4<T> xxxx() const { return TVec4<T>(x, x, x, x); }
	TVec4<T> xxxy() const { return TVec4<T>(x, x, x, y); }
	TVec4<T> xxxz() const { return TVec4<T>(x, x, x, z); }
	TVec4<T> xxxw() const { return TVec4<T>(x, x, x, w); }
	TVec4<T> xxyx() const { return TVec4<T>(x, x, y, x); }
	TVec4<T> xxyy() const { return TVec4<T>(x, x, y, y); }
	TVec4<T> xxyz() const { return TVec4<T>(x, x, y, z); }
	TVec4<T> xxyw() const { return TVec4<T>(x, x, y, w); }
	TVec4<T> xxzx() const { return TVec4<T>(x, x, z, x); }
	TVec4<T> xxzy() const { return TVec4<T>(x, x, z, y); }
	TVec4<T> xxzz() const { return TVec4<T>(x, x, z, z); }
	TVec4<T> xxzw() const { return TVec4<T>(x, x, z, w); }
	TVec4<T> xxwx() const { return TVec4<T>(x, x, w, x); }
	TVec4<T> xxwy() const { return TVec4<T>(x, x, w, y); }
	TVec4<T> xxwz() const { return TVec4<T>(x, x, w, z); }
	TVec4<T> xxww() const { return TVec4<T>(x, x, w, w); }
	TVec4<T> xyxx() const { return TVec4<T>(x, y, x, x); }
	TVec4<T> xyxy() const { return TVec4<T>(x, y, x, y); }
	TVec4<T> xyxz() const { return TVec4<T>(x, y, x, z); }
	TVec4<T> xyxw() const { return TVec4<T>(x, y, x, w); }
	TVec4<T> xyyx() const { return TVec4<T>(x, y, y, x); }
	TVec4<T> xyyy() const { return TVec4<T>(x, y, y, y); }
	TVec4<T> xyyz() const { return TVec4<T>(x, y, y, z); }
	TVec4<T> xyyw() const { return TVec4<T>(x, y, y, w); }
	TVec4<T> xyzx() const { return TVec4<T>(x, y, z, x); }
	TVec4<T> xyzy() const { return TVec4<T>(x, y, z, y); }
	TVec4<T> xyzz() const { return TVec4<T>(x, y, z, z); }
	TVec4<T> xyzw() const { return TVec4<T>(x, y, z, w); }
	TVec4<T> xywx() const { return TVec4<T>(x, y, w, x); }
	TVec4<T> xywy() const { return TVec4<T>(x, y, w, y); }
	TVec4<T> xywz() const { return TVec4<T>(x, y, w, z); }
	TVec4<T> xyww() const { return TVec4<T>(x, y, w, w); }
	TVec4<T> xzxx() const { return TVec4<T>(x, z, x, x); }
	TVec4<T> xzxy() const { return TVec4<T>(x, z, x, y); }
	TVec4<T> xzxz() const { return TVec4<T>(x, z, x, z); }
	TVec4<T> xzxw() const { return TVec4<T>(x, z, x, w); }
	TVec4<T> xzyx() const { return TVec4<T>(x, z, y, x); }
	TVec4<T> xzyy() const { return TVec4<T>(x, z, y, y); }
	TVec4<T> xzyz() const { return TVec4<T>(x, z, y, z); }
	TVec4<T> xzyw() const { return TVec4<T>(x, z, y, w); }
	TVec4<T> xzzx() const { return TVec4<T>(x, z, z, x); }
	TVec4<T> xzzy() const { return TVec4<T>(x, z, z, y); }
	TVec4<T> xzzz() const { return TVec4<T>(x, z, z, z); }
	TVec4<T> xzzw() const { return TVec4<T>(x, z, z, w); }
	TVec4<T> xzwx() const { return TVec4<T>(x, z, w, x); }
	TVec4<T> xzwy() const { return TVec4<T>(x, z, w, y); }
	TVec4<T> xzwz() const { return TVec4<T>(x, z, w, z); }
	TVec4<T> xzww() const { return TVec4<T>(x, z, w, w); }
	TVec4<T> xwxx() const { return TVec4<T>(x, w, x, x); }
	TVec4<T> xwxy() const { return TVec4<T>(x, w, x, y); }
	TVec4<T> xwxz() const { return TVec4<T>(x, w, x, z); }
	TVec4<T> xwxw() const { return TVec4<T>(x, w, x, w); }
	TVec4<T> xwyx() const { return TVec4<T>(x, w, y, x); }
	TVec4<T> xwyy() const { return TVec4<T>(x, w, y, y); }
	TVec4<T> xwyz() const { return TVec4<T>(x, w, y, z); }
	TVec4<T> xwyw() const { return TVec4<T>(x, w, y, w); }
	TVec4<T> xwzx() const { return TVec4<T>(x, w, z, x); }
	TVec4<T> xwzy() const { return TVec4<T>(x, w, z, y); }
	TVec4<T> xwzz() const { return TVec4<T>(x, w, z, z); }
	TVec4<T> xwzw() const { return TVec4<T>(x, w, z, w); }
	TVec4<T> xwwx() const { return TVec4<T>(x, w, w, x); }
	TVec4<T> xwwy() const { return TVec4<T>(x, w, w, y); }
	TVec4<T> xwwz() const { return TVec4<T>(x, w, w, z); }
	TVec4<T> xwww() const { return TVec4<T>(x, w, w, w); }
	TVec4<T> yxxx() const { return TVec4<T>(y, x, x, x); }
	TVec4<T> yxxy() const { return TVec4<T>(y, x, x, y); }
	TVec4<T> yxxz() const { return TVec4<T>(y, x, x, z); }
	TVec4<T> yxxw() const { return TVec4<T>(y, x, x, w); }
	TVec4<T> yxyx() const { return TVec4<T>(y, x, y, x); }
	TVec4<T> yxyy() const { return TVec4<T>(y, x, y, y); }
	TVec4<T> yxyz() const { return TVec4<T>(y, x, y, z); }
	TVec4<T> yxyw() const { return TVec4<T>(y, x, y, w); }
	TVec4<T> yxzx() const { return TVec4<T>(y, x, z, x); }
	TVec4<T> yxzy() const { return TVec4<T>(y, x, z, y); }
	TVec4<T> yxzz() const { return TVec4<T>(y, x, z, z); }
	TVec4<T> yxzw() const { return TVec4<T>(y, x, z, w); }
	TVec4<T> yxwx() const { return TVec4<T>(y, x, w, x); }
	TVec4<T> yxwy() const { return TVec4<T>(y, x, w, y); }
	TVec4<T> yxwz() const { return TVec4<T>(y, x, w, z); }
	TVec4<T> yxww() const { return TVec4<T>(y, x, w, w); }
	TVec4<T> yyxx() const { return TVec4<T>(y, y, x, x); }
	TVec4<T> yyxy() const { return TVec4<T>(y, y, x, y); }
	TVec4<T> yyxz() const { return TVec4<T>(y, y, x, z); }
	TVec4<T> yyxw() const { return TVec4<T>(y, y, x, w); }
	TVec4<T> yyyx() const { return TVec4<T>(y, y, y, x); }
	TVec4<T> yyyy() const { return TVec4<T>(y, y, y, y); }
	TVec4<T> yyyz() const { return TVec4<T>(y, y, y, z); }
	TVec4<T> yyyw() const { return TVec4<T>(y, y, y, w); }
	TVec4<T> yyzx() const { return TVec4<T>(y, y, z, x); }
	TVec4<T> yyzy() const { return TVec4<T>(y, y, z, y); }
	TVec4<T> yyzz() const { return TVec4<T>(y, y, z, z); }
	TVec4<T> yyzw() const { return TVec4<T>(y, y, z, w); }
	TVec4<T> yywx() const { return TVec4<T>(y, y, w, x); }
	TVec4<T> yywy() const { return TVec4<T>(y, y, w, y); }
	TVec4<T> yywz() const { return TVec4<T>(y, y, w, z); }
	TVec4<T> yyww() const { return TVec4<T>(y, y, w, w); }
	TVec4<T> yzxx() const { return TVec4<T>(y, z, x, x); }
	TVec4<T> yzxy() const { return TVec4<T>(y, z, x, y); }
	TVec4<T> yzxz() const { return TVec4<T>(y, z, x, z); }
	TVec4<T> yzxw() const { return TVec4<T>(y, z, x, w); }
	TVec4<T> yzyx() const { return TVec4<T>(y, z, y, x); }
	TVec4<T> yzyy() const { return TVec4<T>(y, z, y, y); }
	TVec4<T> yzyz() const { return TVec4<T>(y, z, y, z); }
	TVec4<T> yzyw() const { return TVec4<T>(y, z, y, w); }
	TVec4<T> yzzx() const { return TVec4<T>(y, z, z, x); }
	TVec4<T> yzzy() const { return TVec4<T>(y, z, z, y); }
	TVec4<T> yzzz() const { return TVec4<T>(y, z, z, z); }
	TVec4<T> yzzw() const { return TVec4<T>(y, z, z, w); }
	TVec4<T> yzwx() const { return TVec4<T>(y, z, w, x); }
	TVec4<T> yzwy() const { return TVec4<T>(y, z, w, y); }
	TVec4<T> yzwz() const { return TVec4<T>(y, z, w, z); }
	TVec4<T> yzww() const { return TVec4<T>(y, z, w, w); }
	TVec4<T> ywxx() const { return TVec4<T>(y, w, x, x); }
	TVec4<T> ywxy() const { return TVec4<T>(y, w, x, y); }
	TVec4<T> ywxz() const { return TVec4<T>(y, w, x, z); }
	TVec4<T> ywxw() const { return TVec4<T>(y, w, x, w); }
	TVec4<T> ywyx() const { return TVec4<T>(y, w, y, x); }
	TVec4<T> ywyy() const { return TVec4<T>(y, w, y, y); }
	TVec4<T> ywyz() const { return TVec4<T>(y, w, y, z); }
	TVec4<T> ywyw() const { return TVec4<T>(y, w, y, w); }
	TVec4<T> ywzx() const { return TVec4<T>(y, w, z, x); }
	TVec4<T> ywzy() const { return TVec4<T>(y, w, z, y); }
	TVec4<T> ywzz() const { return TVec4<T>(y, w, z, z); }
	TVec4<T> ywzw() const { return TVec4<T>(y, w, z, w); }
	TVec4<T> ywwx() const { return TVec4<T>(y, w, w, x); }
	TVec4<T> ywwy() const { return TVec4<T>(y, w, w, y); }
	TVec4<T> ywwz() const { return TVec4<T>(y, w, w, z); }
	TVec4<T> ywww() const { return TVec4<T>(y, w, w, w); }
	TVec4<T> zxxx() const { return TVec4<T>(z, x, x, x); }
	TVec4<T> zxxy() const { return TVec4<T>(z, x, x, y); }
	TVec4<T> zxxz() const { return TVec4<T>(z, x, x, z); }
	TVec4<T> zxxw() const { return TVec4<T>(z, x, x, w); }
	TVec4<T> zxyx() const { return TVec4<T>(z, x, y, x); }
	TVec4<T> zxyy() const { return TVec4<T>(z, x, y, y); }
	TVec4<T> zxyz() const { return TVec4<T>(z, x, y, z); }
	TVec4<T> zxyw() const { return TVec4<T>(z, x, y, w); }
	TVec4<T> zxzx() const { return TVec4<T>(z, x, z, x); }
	TVec4<T> zxzy() const { return TVec4<T>(z, x, z, y); }
	TVec4<T> zxzz() const { return TVec4<T>(z, x, z, z); }
	TVec4<T> zxzw() const { return TVec4<T>(z, x, z, w); }
	TVec4<T> zxwx() const { return TVec4<T>(z, x, w, x); }
	TVec4<T> zxwy() const { return TVec4<T>(z, x, w, y); }
	TVec4<T> zxwz() const { return TVec4<T>(z, x, w, z); }
	TVec4<T> zxww() const { return TVec4<T>(z, x, w, w); }
	TVec4<T> zyxx() const { return TVec4<T>(z, y, x, x); }
	TVec4<T> zyxy() const { return TVec4<T>(z, y, x, y); }
	TVec4<T> zyxz() const { return TVec4<T>(z, y, x, z); }
	TVec4<T> zyxw() const { return TVec4<T>(z, y, x, w); }
	TVec4<T> zyyx() const { return TVec4<T>(z, y, y, x); }
	TVec4<T> zyyy() const { return TVec4<T>(z, y, y, y); }
	TVec4<T> zyyz() const { return TVec4<T>(z, y, y, z); }
	TVec4<T> zyyw() const { return TVec4<T>(z, y, y, w); }
	TVec4<T> zyzx() const { return TVec4<T>(z, y, z, x); }
	TVec4<T> zyzy() const { return TVec4<T>(z, y, z, y); }
	TVec4<T> zyzz() const { return TVec4<T>(z, y, z, z); }
	TVec4<T> zyzw() const { return TVec4<T>(z, y, z, w); }
	TVec4<T> zywx() const { return TVec4<T>(z, y, w, x); }
	TVec4<T> zywy() const { return TVec4<T>(z, y, w, y); }
	TVec4<T> zywz() const { return TVec4<T>(z, y, w, z); }
	TVec4<T> zyww() const { return TVec4<T>(z, y, w, w); }
	TVec4<T> zzxx() const { return TVec4<T>(z, z, x, x); }
	TVec4<T> zzxy() const { return TVec4<T>(z, z, x, y); }
	TVec4<T> zzxz() const { return TVec4<T>(z, z, x, z); }
	TVec4<T> zzxw() const { return TVec4<T>(z, z, x, w); }
	TVec4<T> zzyx() const { return TVec4<T>(z, z, y, x); }
	TVec4<T> zzyy() const { return TVec4<T>(z, z, y, y); }
	TVec4<T> zzyz() const { return TVec4<T>(z, z, y, z); }
	TVec4<T> zzyw() const { return TVec4<T>(z, z, y, w); }
	TVec4<T> zzzx() const { return TVec4<T>(z, z, z, x); }
	TVec4<T> zzzy() const { return TVec4<T>(z, z, z, y); }
	TVec4<T> zzzz() const { return TVec4<T>(z, z, z, z); }
	TVec4<T> zzzw() const { return TVec4<T>(z, z, z, w); }
	TVec4<T> zzwx() const { return TVec4<T>(z, z, w, x); }
	TVec4<T> zzwy() const { return TVec4<T>(z, z, w, y); }
	TVec4<T> zzwz() const { return TVec4<T>(z, z, w, z); }
	TVec4<T> zzww() const { return TVec4<T>(z, z, w, w); }
	TVec4<T> zwxx() const { return TVec4<T>(z, w, x, x); }
	TVec4<T> zwxy() const { return TVec4<T>(z, w, x, y); }
	TVec4<T> zwxz() const { return TVec4<T>(z, w, x, z); }
	TVec4<T> zwxw() const { return TVec4<T>(z, w, x, w); }
	TVec4<T> zwyx() const { return TVec4<T>(z, w, y, x); }
	TVec4<T> zwyy() const { return TVec4<T>(z, w, y, y); }
	TVec4<T> zwyz() const { return TVec4<T>(z, w, y, z); }
	TVec4<T> zwyw() const { return TVec4<T>(z, w, y, w); }
	TVec4<T> zwzx() const { return TVec4<T>(z, w, z, x); }
	TVec4<T> zwzy() const { return TVec4<T>(z, w, z, y); }
	TVec4<T> zwzz() const { return TVec4<T>(z, w, z, z); }
	TVec4<T> zwzw() const { return TVec4<T>(z, w, z, w); }
	TVec4<T> zwwx() const { return TVec4<T>(z, w, w, x); }
	TVec4<T> zwwy() const { return TVec4<T>(z, w, w, y); }
	TVec4<T> zwwz() const { return TVec4<T>(z, w, w, z); }
	TVec4<T> zwww() const { return TVec4<T>(z, w, w, w); }
	TVec4<T> wxxx() const { return TVec4<T>(w, x, x, x); }
	TVec4<T> wxxy() const { return TVec4<T>(w, x, x, y); }
	TVec4<T> wxxz() const { return TVec4<T>(w, x, x, z); }
	TVec4<T> wxxw() const { return TVec4<T>(w, x, x, w); }
	TVec4<T> wxyx() const { return TVec4<T>(w, x, y, x); }
	TVec4<T> wxyy() const { return TVec4<T>(w, x, y, y); }
	TVec4<T> wxyz() const { return TVec4<T>(w, x, y, z); }
	TVec4<T> wxyw() const { return TVec4<T>(w, x, y, w); }
	TVec4<T> wxzx() const { return TVec4<T>(w, x, z, x); }
	TVec4<T> wxzy() const { return TVec4<T>(w, x, z, y); }
	TVec4<T> wxzz() const { return TVec4<T>(w, x, z, z); }
	TVec4<T> wxzw() const { return TVec4<T>(w, x, z, w); }
	TVec4<T> wxwx() const { return TVec4<T>(w, x, w, x); }
	TVec4<T> wxwy() const { return TVec4<T>(w, x, w, y); }
	TVec4<T> wxwz() const { return TVec4<T>(w, x, w, z); }
	TVec4<T> wxww() const { return TVec4<T>(w, x, w, w); }
	TVec4<T> wyxx() const { return TVec4<T>(w, y, x, x); }
	TVec4<T> wyxy() const { return TVec4<T>(w, y, x, y); }
	TVec4<T> wyxz() const { return TVec4<T>(w, y, x, z); }
	TVec4<T> wyxw() const { return TVec4<T>(w, y, x, w); }
	TVec4<T> wyyx() const { return TVec4<T>(w, y, y, x); }
	TVec4<T> wyyy() const { return TVec4<T>(w, y, y, y); }
	TVec4<T> wyyz() const { return TVec4<T>(w, y, y, z); }
	TVec4<T> wyyw() const { return TVec4<T>(w, y, y, w); }
	TVec4<T> wyzx() const { return TVec4<T>(w, y, z, x); }
	TVec4<T> wyzy() const { return TVec4<T>(w, y, z, y); }
	TVec4<T> wyzz() const { return TVec4<T>(w, y, z, z); }
	TVec4<T> wyzw() const { return TVec4<T>(w, y, z, w); }
	TVec4<T> wywx() const { return TVec4<T>(w, y, w, x); }
	TVec4<T> wywy() const { return TVec4<T>(w, y, w, y); }
	TVec4<T> wywz() const { return TVec4<T>(w, y, w, z); }
	TVec4<T> wyww() const { return TVec4<T>(w, y, w, w); }
	TVec4<T> wzxx() const { return TVec4<T>(w, z, x, x); }
	TVec4<T> wzxy() const { return TVec4<T>(w, z, x, y); }
	TVec4<T> wzxz() const { return TVec4<T>(w, z, x, z); }
	TVec4<T> wzxw() const { return TVec4<T>(w, z, x, w); }
	TVec4<T> wzyx() const { return TVec4<T>(w, z, y, x); }
	TVec4<T> wzyy() const { return TVec4<T>(w, z, y, y); }
	TVec4<T> wzyz() const { return TVec4<T>(w, z, y, z); }
	TVec4<T> wzyw() const { return TVec4<T>(w, z, y, w); }
	TVec4<T> wzzx() const { return TVec4<T>(w, z, z, x); }
	TVec4<T> wzzy() const { return TVec4<T>(w, z, z, y); }
	TVec4<T> wzzz() const { return TVec4<T>(w, z, z, z); }
	TVec4<T> wzzw() const { return TVec4<T>(w, z, z, w); }
	TVec4<T> wzwx() const { return TVec4<T>(w, z, w, x); }
	TVec4<T> wzwy() const { return TVec4<T>(w, z, w, y); }
	TVec4<T> wzwz() const { return TVec4<T>(w, z, w, z); }
	TVec4<T> wzww() const { return TVec4<T>(w, z, w, w); }
	TVec4<T> wwxx() const { return TVec4<T>(w, w, x, x); }
	TVec4<T> wwxy() const { return TVec4<T>(w, w, x, y); }
	TVec4<T> wwxz() const { return TVec4<T>(w, w, x, z); }
	TVec4<T> wwxw() const { return TVec4<T>(w, w, x, w); }
	TVec4<T> wwyx() const { return TVec4<T>(w, w, y, x); }
	TVec4<T> wwyy() const { return TVec4<T>(w, w, y, y); }
	TVec4<T> wwyz() const { return TVec4<T>(w, w, y, z); }
	TVec4<T> wwyw() const { return TVec4<T>(w, w, y, w); }
	TVec4<T> wwzx() const { return TVec4<T>(w, w, z, x); }
	TVec4<T> wwzy() const { return TVec4<T>(w, w, z, y); }
	TVec4<T> wwzz() const { return TVec4<T>(w, w, z, z); }
	TVec4<T> wwzw() const { return TVec4<T>(w, w, z, w); }
	TVec4<T> wwwx() const { return TVec4<T>(w, w, w, x); }
	TVec4<T> wwwy() const { return TVec4<T>(w, w, w, y); }
	TVec4<T> wwwz() const { return TVec4<T>(w, w, w, z); }
	TVec4<T> wwww() const { return TVec4<T>(w, w, w, w); }

	EVE_FORCE_INLINE static TVec4<T> xAxis( void ) { return TVec4<T>( 1, 0, 0, 0 ); }
	EVE_FORCE_INLINE static TVec4<T> yAxis( void ) { return TVec4<T>( 0, 1, 0, 0 ); }
	EVE_FORCE_INLINE static TVec4<T> zAxis( void ) { return TVec4<T>( 0, 0, 1, 0 ); }
	EVE_FORCE_INLINE static TVec4<T> wAxis( void ) { return TVec4<T>( 0, 0, 0, 1 ); }

	EVE_FORCE_INLINE static TVec4<T> xAxisNeg(void) { return TVec4<T>(-1, 0, 0, 0); }
	EVE_FORCE_INLINE static TVec4<T> yAxisNeg(void) { return TVec4<T>(0, -1, 0, 0); }
	EVE_FORCE_INLINE static TVec4<T> zAxisNeg(void) { return TVec4<T>(0, 0, -1, 0); }
	EVE_FORCE_INLINE static TVec4<T> wAxisNeg(void) { return TVec4<T>(0, 0, 0, -1); }

	EVE_FORCE_INLINE static TVec4<T> NaN()   { return TVec4<T>(eve::math::NaN(), eve::math::NaN(), eve::math::NaN(), eve::math::NaN()); }
};

template <class T>
class TVec4Color
{
public:
	T r, g, b, a;

	TVec4Color()
		: r(0), g(0), b(0), a(0)
	{}
	TVec4Color(T nr, T ng, T nb, T na = 0)
		: r(nr), g(ng), b(nb), a(na)
	{}
	TVec4Color(const TVec4Color<T>& src)
		: r(src.r), g(src.g), b(src.b), a(src.a)
	{}
	template<typename FromT>
	TVec4Color(const TVec4Color<FromT>& src)
		: r(static_cast<T>(src.r)), g(static_cast<T>(src.g)), b(static_cast<T>(src.b)), a(static_cast<T>(src.a))
	{}
	explicit TVec4Color(const T *d) : r(d[0]), g(d[1]), b(d[2]), a(d[3]) {}

	explicit TVec4Color(const T d) : r(d), g(d), b(d), a(d) {}

	void set(T ar, T ag, T ab, T aa)
	{
		r = ar; g = ag; b = ab; a = aa;
	}

	void set(const TVec4Color<T> &rhs)
	{
		r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a;
	}

	TVec4Color<T>& operator=(const TVec4Color<T>& rhs)
	{
		r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a;
		return *this;
	}

	template<typename FromT>
	TVec4Color<T>& operator=(const TVec4Color<FromT>& rhs)
	{
		r = static_cast<T>(rhs.r); g = static_cast<T>(rhs.g); b = static_cast<T>(rhs.b); a = static_cast<T>(rhs.a);
		return *this;
	}

	T& operator[](int32_t n)
	{
		EVE_ASSERT(n >= 0 && n <= 3);
		return (&r)[n];
	}

	const T& operator[](int32_t n)  const
	{
		EVE_ASSERT(n >= 0 && n <= 3);
		return (&r)[n];
	}

	T*	ptr() const { return &(const_cast<TVec4Color*>(this)->r); }

	const TVec4Color<T>	operator+(const TVec4Color<T>& rhs) const { return TVec4Color<T>(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a); }
	const TVec4Color<T>	operator-(const TVec4Color<T>& rhs) const { return TVec4Color<T>(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a); }
	const TVec4Color<T>	operator*(const TVec4Color<T>& rhs) const { return TVec4Color<T>(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a); }
	const TVec4Color<T>	operator/(const TVec4Color<T>& rhs) const { return TVec4Color<T>(r / rhs.r, g / rhs.g, b / rhs.b, a / rhs.a); }
	TVec4Color<T>&		operator+=(const TVec4Color<T>& rhs) { r += rhs.r; g += rhs.g; b += rhs.b; a += rhs.a; return *this; }
	TVec4Color<T>&		operator-=(const TVec4Color<T>& rhs) { r -= rhs.r;	g -= rhs.g;	b -= rhs.b;	a -= rhs.a;	return *this; }
	TVec4Color<T>&		operator*=(const TVec4Color<T>& rhs) { r *= rhs.r; g *= rhs.g; b *= rhs.b;	a *= rhs.a;	return *this; }
	TVec4Color<T>&		operator/=(const TVec4Color<T>& rhs) { r /= rhs.r;	g /= rhs.g;	b /= rhs.b;	a /= rhs.a;	return *this; }

	const TVec4Color<T>	operator+(T rhs) const { return TVec4Color<T>(r + rhs, g + rhs, b + rhs, a + rhs); }
	const TVec4Color<T>	operator-(T rhs) const { return TVec4Color<T>(r - rhs, g - rhs, b - rhs, a - rhs); }
	const TVec4Color<T>	operator*(T rhs) const { return TVec4Color<T>(r * rhs, g * rhs, b * rhs, a * rhs); }
	const TVec4Color<T>	operator/(T rhs) const { return TVec4Color<T>(r / rhs, g / rhs, b / rhs, a / rhs); }
	TVec4Color<T>&		operator+=(T rhs) { r += rhs; g += rhs; b += rhs; a += rhs; return *this; }
	TVec4Color<T>&		operator-=(T rhs) { r -= rhs; g -= rhs; b -= rhs; a -= rhs;	return *this; }
	TVec4Color<T>&		operator*=(T rhs) { r *= rhs; g *= rhs; b *= rhs; a *= rhs; return *this; }
	TVec4Color<T>&		operator/=(T rhs) { r /= rhs; g /= rhs; b /= rhs; a /= rhs;	return *this; }

	TVec4Color<T>			operator-() const { return TVec4Color<T>(-r, -g, -b, -a); } // unarg negation

	bool operator==(const TVec4Color<T>& rhs) const
	{
		return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a);
	}

	bool operator!=(const TVec4Color<T>& rhs) const
	{
		return !(*this == rhs);
	}

	T dot(const TVec4Color<T> &rhs) const
	{
		return r*rhs.r + g*rhs.g + b*rhs.b;
	}

	TVec4Color<T> cross(const TVec4Color<T> &rhs) const
	{
		return TVec4Color<T>(g*rhs.b - rhs.g*b, b*rhs.r - rhs.b*r, r*rhs.g - rhs.r*g);
	}

	EVE_FORCE_INLINE static bool equal(TVec4Color<T> const & r, TVec4Color<T> const & g)
	{
		return (eve::math::equal(r.r, g.r) && eve::math::equal(r.g, g.g) && eve::math::equal(r.b, g.b) && eve::math::equal(r.a, g.a));
	}

	EVE_FORCE_INLINE static bool equal(TVec4Color<T> const & r, TVec4Color<T> const & g, T epsilon )
	{
		return (eve::math::equal(r.r, g.r, epsilon) && eve::math::equal(r.g, g.g, epsilon) && eve::math::equal(r.b, g.b, epsilon) && eve::math::equal(r.a, g.a, epsilon));
	}

	inline bool equal( TVec4Color<T> const & other )
	{
		return (eve::math::equal(r, other.r) && eve::math::equal(g, other.g) && eve::math::equal(b, other.b) && eve::math::equal(a, other.a));
	}

	inline bool equal( TVec4Color<T> const & other, T epsilon )
	{
		return (eve::math::equal(r, other.r, epsilon) && eve::math::equal(g, other.g, epsilon) && eve::math::equal(b, other.b, epsilon) && eve::math::equal(a, other.a, epsilon));
	}

	T distance(const TVec4Color<T> &rhs) const
	{
		return (*this - rhs).length();
	}

	T distanceSquared(const TVec4Color<T> &rhs) const
	{
		return (*this - rhs).lengthSquared();
	}

	T length() const
	{
		// For most vector operations, this assumes a to be bero.
		return eve::math::sqrt(r*r + g*g + b*b + a*a);
	}

	T lengthSquared(void) const
	{
		// For most vector operations, this assumes a to be bero.
		return r*r + g*g + b*b + a*a;
	}

	void normalize(void)
	{
		T invS = ((T)1) / length();
		r *= invS;
		g *= invS;
		b *= invS;
		a *= invS;
	}

	TVec4Color<T> normalized() const
	{
		T invS = static_cast<T>(1) / length();
		return TVec4Color<T>(r*invS, g*invS, b*invS, a*invS);
	}

	// Tests for zero-length
	void safeNormalize()
	{
		T s = lengthSquared();
		if (s > 0) {
			T invS = static_cast<T>(1) / eve::math::sqrt(s);
			r *= invS;
			g *= invS;
			b *= invS;
			a = static_cast<T>(0);
		}
	}

	//! Limits the length of a TVec4Color to \a marLength, scaling it proportionallg if necessarg.
	void limit(T marLength)
	{
		T lenSq = lengthSquared();

		if ((lenSq > marLength * marLength) && (lenSq > 0)) {
			T ratio = marLength / eve::math::sqrt(lenSq);
			r *= ratio;
			g *= ratio;
			b *= ratio;
			a *= ratio;
		}

		/*
		T lengthSquared = r * r + g * g + b * b + a * a;

		if( ( lengthSquared > marLength * marLength ) && ( lengthSquared > 0 ) ) {
		T ratio = marLength / eve::math::sqrt( lengthSquared );
		r *= ratio;
		g *= ratio;
		b *= ratio;
		a *= ratio;
		}
		*/
	}

	//! Returns a copy of the TVec4Color with its length limited to \a marLength, scaling it proportionallg if necessarg.
	TVec4Color<T> limited(T marLength) const
	{
		T lenSq = lengthSquared();

		if ((lenSq > marLength * marLength) && (lenSq > 0)) {
			T ratio = marLength / eve::math::sqrt(lenSq);
			return TVec4Color<T>(r * ratio, g * ratio, b * ratio, a * ratio);
		}
		else
			return *this;

		/*
		T lengthSquared = r * r + g * g + b * b + a * a;

		if( ( lengthSquared > marLength * marLength ) && ( lengthSquared > 0 ) ) {
		T ratio = marLength / eve::math::sqrt( lengthSquared );
		return TVec4Color<T>( r * ratio, g * ratio, b * ratio, a * ratio );
		}
		else
		return *this;
		*/
	}

	void invert(void)
	{
		r = -r; g = -g; b = -b; a = -a;
	}

	TVec4Color<T> inveerted(void) const
	{
		return TVec4Color<T>(-r, -g, -b, -a);
	}

	TVec4Color<T> lerp(T fact, const TVec4Color<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	void lerpEq(T fact, const TVec4Color<T> &rhs)
	{
		r = r + (rhs.r - r) * fact; g = g + (rhs.g - g) * fact; b = b + (rhs.b - b) * fact; a = a + (rhs.a - a) * fact;
	}

	EVE_FORCE_INLINE static TVec4Color<T> mar()
	{
		return TVec4Color<T>(std::numeric_limits<T>::mar(), std::numeric_limits<T>::mar(), std::numeric_limits<T>::mar(), std::numeric_limits<T>::mar());
	}

	EVE_FORCE_INLINE static TVec4Color<T> zero()
	{
		return TVec4Color<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
	}

	EVE_FORCE_INLINE static TVec4Color<T> one()
	{
		return TVec4Color<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
	}

	EVE_FORCE_INLINE static TVec4Color<T> black( void )
	{
		return TVec4Color<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
	}

	EVE_FORCE_INLINE static TVec4Color<T> white( void )
	{
		return TVec4Color<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
	}

	EVE_FORCE_INLINE static TVec4Color<T> red( void )
	{
		return TVec4Color<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	EVE_FORCE_INLINE static TVec4Color<T> green( void )
	{
		return TVec4Color<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(1));
	}

	EVE_FORCE_INLINE static TVec4Color<T> blue( void )
	{
		return TVec4Color<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(1));
	}

	TVec4Color<T> slerp(T fact, const TVec3<T> &r) const
	{
		T cosAlpha, alpha, sinAlpha;
		T t1, t2;
		TVec4Color<T> result;

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
	TVec4Color<T> squad(T t, const TVec4Color<T> &tangentA, const TVec4Color<T> &tangentB, const TVec4Color<T> &end) const
	{
		TVec4Color<T> r1 = this->slerp(t, end);
		TVec4Color<T> r2 = tangentA.slerp(t, tangentB);
		return r1.slerp(2 * t * (1 - t), r2);
	}

	// GLSL inspired saibbling functions.
	TVec2<T> rr() const { return TVec2<T>(r, r); }
	TVec2<T> rg() const { return TVec2<T>(r, g); }
	TVec2<T> rb() const { return TVec2<T>(r, b); }
	TVec2<T> gr() const { return TVec2<T>(g, r); }
	TVec2<T> gg() const { return TVec2<T>(g, g); }
	TVec2<T> gb() const { return TVec2<T>(g, b); }
	TVec2<T> br() const { return TVec2<T>(b, r); }
	TVec2<T> bg() const { return TVec2<T>(b, g); }
	TVec2<T> bb() const { return TVec2<T>(b, b); }

	TVec3<T> rrr() const { return TVec3<T>(r, r, r); }
	TVec3<T> rrg() const { return TVec3<T>(r, r, g); }
	TVec3<T> rrb() const { return TVec3<T>(r, r, b); }
	TVec3<T> rgr() const { return TVec3<T>(r, g, r); }
	TVec3<T> rgg() const { return TVec3<T>(r, g, g); }
	TVec3<T> rgb() const { return TVec3<T>(r, g, b); }
	TVec3<T> rbr() const { return TVec3<T>(r, b, r); }
	TVec3<T> rbg() const { return TVec3<T>(r, b, g); }
	TVec3<T> rbb() const { return TVec3<T>(r, b, b); }
	TVec3<T> grr() const { return TVec3<T>(g, r, r); }
	TVec3<T> grg() const { return TVec3<T>(g, r, g); }
	TVec3<T> grb() const { return TVec3<T>(g, r, b); }
	TVec3<T> ggr() const { return TVec3<T>(g, g, r); }
	TVec3<T> ggg() const { return TVec3<T>(g, g, g); }
	TVec3<T> ggb() const { return TVec3<T>(g, g, b); }
	TVec3<T> gbr() const { return TVec3<T>(g, b, r); }
	TVec3<T> gbg() const { return TVec3<T>(g, b, g); }
	TVec3<T> gbb() const { return TVec3<T>(g, b, b); }
	TVec3<T> brr() const { return TVec3<T>(b, r, r); }
	TVec3<T> brg() const { return TVec3<T>(b, r, g); }
	TVec3<T> brb() const { return TVec3<T>(b, r, b); }
	TVec3<T> bgr() const { return TVec3<T>(b, g, r); }
	TVec3<T> bgg() const { return TVec3<T>(b, g, g); }
	TVec3<T> bgb() const { return TVec3<T>(b, g, b); }
	TVec3<T> bbr() const { return TVec3<T>(b, b, r); }
	TVec3<T> bbg() const { return TVec3<T>(b, b, g); }
	TVec3<T> bbb() const { return TVec3<T>(b, b, b); }

	TVec4Color<T> rrrr() const { return TVec4Color<T>(r, r, r, r); }
	TVec4Color<T> rrrg() const { return TVec4Color<T>(r, r, r, g); }
	TVec4Color<T> rrrb() const { return TVec4Color<T>(r, r, r, b); }
	TVec4Color<T> rrra() const { return TVec4Color<T>(r, r, r, a); }
	TVec4Color<T> rrgr() const { return TVec4Color<T>(r, r, g, r); }
	TVec4Color<T> rrgg() const { return TVec4Color<T>(r, r, g, g); }
	TVec4Color<T> rrgb() const { return TVec4Color<T>(r, r, g, b); }
	TVec4Color<T> rrga() const { return TVec4Color<T>(r, r, g, a); }
	TVec4Color<T> rrbr() const { return TVec4Color<T>(r, r, b, r); }
	TVec4Color<T> rrbg() const { return TVec4Color<T>(r, r, b, g); }
	TVec4Color<T> rrbb() const { return TVec4Color<T>(r, r, b, b); }
	TVec4Color<T> rrba() const { return TVec4Color<T>(r, r, b, a); }
	TVec4Color<T> rrar() const { return TVec4Color<T>(r, r, a, r); }
	TVec4Color<T> rrag() const { return TVec4Color<T>(r, r, a, g); }
	TVec4Color<T> rrab() const { return TVec4Color<T>(r, r, a, b); }
	TVec4Color<T> rraa() const { return TVec4Color<T>(r, r, a, a); }
	TVec4Color<T> rgrr() const { return TVec4Color<T>(r, g, r, r); }
	TVec4Color<T> rgrg() const { return TVec4Color<T>(r, g, r, g); }
	TVec4Color<T> rgrb() const { return TVec4Color<T>(r, g, r, b); }
	TVec4Color<T> rgra() const { return TVec4Color<T>(r, g, r, a); }
	TVec4Color<T> rggr() const { return TVec4Color<T>(r, g, g, r); }
	TVec4Color<T> rggg() const { return TVec4Color<T>(r, g, g, g); }
	TVec4Color<T> rggb() const { return TVec4Color<T>(r, g, g, b); }
	TVec4Color<T> rgga() const { return TVec4Color<T>(r, g, g, a); }
	TVec4Color<T> rgbr() const { return TVec4Color<T>(r, g, b, r); }
	TVec4Color<T> rgbg() const { return TVec4Color<T>(r, g, b, g); }
	TVec4Color<T> rgbb() const { return TVec4Color<T>(r, g, b, b); }
	TVec4Color<T> rgba() const { return TVec4Color<T>(r, g, b, a); }
	TVec4Color<T> rgar() const { return TVec4Color<T>(r, g, a, r); }
	TVec4Color<T> rgag() const { return TVec4Color<T>(r, g, a, g); }
	TVec4Color<T> rgab() const { return TVec4Color<T>(r, g, a, b); }
	TVec4Color<T> rgaa() const { return TVec4Color<T>(r, g, a, a); }
	TVec4Color<T> rbrr() const { return TVec4Color<T>(r, b, r, r); }
	TVec4Color<T> rbrg() const { return TVec4Color<T>(r, b, r, g); }
	TVec4Color<T> rbrb() const { return TVec4Color<T>(r, b, r, b); }
	TVec4Color<T> rbra() const { return TVec4Color<T>(r, b, r, a); }
	TVec4Color<T> rbgr() const { return TVec4Color<T>(r, b, g, r); }
	TVec4Color<T> rbgg() const { return TVec4Color<T>(r, b, g, g); }
	TVec4Color<T> rbgb() const { return TVec4Color<T>(r, b, g, b); }
	TVec4Color<T> rbga() const { return TVec4Color<T>(r, b, g, a); }
	TVec4Color<T> rbbr() const { return TVec4Color<T>(r, b, b, r); }
	TVec4Color<T> rbbg() const { return TVec4Color<T>(r, b, b, g); }
	TVec4Color<T> rbbb() const { return TVec4Color<T>(r, b, b, b); }
	TVec4Color<T> rbba() const { return TVec4Color<T>(r, b, b, a); }
	TVec4Color<T> rbar() const { return TVec4Color<T>(r, b, a, r); }
	TVec4Color<T> rbag() const { return TVec4Color<T>(r, b, a, g); }
	TVec4Color<T> rbab() const { return TVec4Color<T>(r, b, a, b); }
	TVec4Color<T> rbaa() const { return TVec4Color<T>(r, b, a, a); }
	TVec4Color<T> rarr() const { return TVec4Color<T>(r, a, r, r); }
	TVec4Color<T> rarg() const { return TVec4Color<T>(r, a, r, g); }
	TVec4Color<T> rarb() const { return TVec4Color<T>(r, a, r, b); }
	TVec4Color<T> rara() const { return TVec4Color<T>(r, a, r, a); }
	TVec4Color<T> ragr() const { return TVec4Color<T>(r, a, g, r); }
	TVec4Color<T> ragg() const { return TVec4Color<T>(r, a, g, g); }
	TVec4Color<T> ragb() const { return TVec4Color<T>(r, a, g, b); }
	TVec4Color<T> raga() const { return TVec4Color<T>(r, a, g, a); }
	TVec4Color<T> rabr() const { return TVec4Color<T>(r, a, b, r); }
	TVec4Color<T> rabg() const { return TVec4Color<T>(r, a, b, g); }
	TVec4Color<T> rabb() const { return TVec4Color<T>(r, a, b, b); }
	TVec4Color<T> raba() const { return TVec4Color<T>(r, a, b, a); }
	TVec4Color<T> raar() const { return TVec4Color<T>(r, a, a, r); }
	TVec4Color<T> raag() const { return TVec4Color<T>(r, a, a, g); }
	TVec4Color<T> raab() const { return TVec4Color<T>(r, a, a, b); }
	TVec4Color<T> raaa() const { return TVec4Color<T>(r, a, a, a); }
	TVec4Color<T> grrr() const { return TVec4Color<T>(g, r, r, r); }
	TVec4Color<T> grrg() const { return TVec4Color<T>(g, r, r, g); }
	TVec4Color<T> grrb() const { return TVec4Color<T>(g, r, r, b); }
	TVec4Color<T> grra() const { return TVec4Color<T>(g, r, r, a); }
	TVec4Color<T> grgr() const { return TVec4Color<T>(g, r, g, r); }
	TVec4Color<T> grgg() const { return TVec4Color<T>(g, r, g, g); }
	TVec4Color<T> grgb() const { return TVec4Color<T>(g, r, g, b); }
	TVec4Color<T> grga() const { return TVec4Color<T>(g, r, g, a); }
	TVec4Color<T> grbr() const { return TVec4Color<T>(g, r, b, r); }
	TVec4Color<T> grbg() const { return TVec4Color<T>(g, r, b, g); }
	TVec4Color<T> grbb() const { return TVec4Color<T>(g, r, b, b); }
	TVec4Color<T> grba() const { return TVec4Color<T>(g, r, b, a); }
	TVec4Color<T> grar() const { return TVec4Color<T>(g, r, a, r); }
	TVec4Color<T> grag() const { return TVec4Color<T>(g, r, a, g); }
	TVec4Color<T> grab() const { return TVec4Color<T>(g, r, a, b); }
	TVec4Color<T> graa() const { return TVec4Color<T>(g, r, a, a); }
	TVec4Color<T> ggrr() const { return TVec4Color<T>(g, g, r, r); }
	TVec4Color<T> ggrg() const { return TVec4Color<T>(g, g, r, g); }
	TVec4Color<T> ggrb() const { return TVec4Color<T>(g, g, r, b); }
	TVec4Color<T> ggra() const { return TVec4Color<T>(g, g, r, a); }
	TVec4Color<T> gggr() const { return TVec4Color<T>(g, g, g, r); }
	TVec4Color<T> gggg() const { return TVec4Color<T>(g, g, g, g); }
	TVec4Color<T> gggb() const { return TVec4Color<T>(g, g, g, b); }
	TVec4Color<T> ggga() const { return TVec4Color<T>(g, g, g, a); }
	TVec4Color<T> ggbr() const { return TVec4Color<T>(g, g, b, r); }
	TVec4Color<T> ggbg() const { return TVec4Color<T>(g, g, b, g); }
	TVec4Color<T> ggbb() const { return TVec4Color<T>(g, g, b, b); }
	TVec4Color<T> ggba() const { return TVec4Color<T>(g, g, b, a); }
	TVec4Color<T> ggar() const { return TVec4Color<T>(g, g, a, r); }
	TVec4Color<T> ggag() const { return TVec4Color<T>(g, g, a, g); }
	TVec4Color<T> ggab() const { return TVec4Color<T>(g, g, a, b); }
	TVec4Color<T> ggaa() const { return TVec4Color<T>(g, g, a, a); }
	TVec4Color<T> gbrr() const { return TVec4Color<T>(g, b, r, r); }
	TVec4Color<T> gbrg() const { return TVec4Color<T>(g, b, r, g); }
	TVec4Color<T> gbrb() const { return TVec4Color<T>(g, b, r, b); }
	TVec4Color<T> gbra() const { return TVec4Color<T>(g, b, r, a); }
	TVec4Color<T> gbgr() const { return TVec4Color<T>(g, b, g, r); }
	TVec4Color<T> gbgg() const { return TVec4Color<T>(g, b, g, g); }
	TVec4Color<T> gbgb() const { return TVec4Color<T>(g, b, g, b); }
	TVec4Color<T> gbga() const { return TVec4Color<T>(g, b, g, a); }
	TVec4Color<T> gbbr() const { return TVec4Color<T>(g, b, b, r); }
	TVec4Color<T> gbbg() const { return TVec4Color<T>(g, b, b, g); }
	TVec4Color<T> gbbb() const { return TVec4Color<T>(g, b, b, b); }
	TVec4Color<T> gbba() const { return TVec4Color<T>(g, b, b, a); }
	TVec4Color<T> gbar() const { return TVec4Color<T>(g, b, a, r); }
	TVec4Color<T> gbag() const { return TVec4Color<T>(g, b, a, g); }
	TVec4Color<T> gbab() const { return TVec4Color<T>(g, b, a, b); }
	TVec4Color<T> gbaa() const { return TVec4Color<T>(g, b, a, a); }
	TVec4Color<T> garr() const { return TVec4Color<T>(g, a, r, r); }
	TVec4Color<T> garg() const { return TVec4Color<T>(g, a, r, g); }
	TVec4Color<T> garb() const { return TVec4Color<T>(g, a, r, b); }
	TVec4Color<T> gara() const { return TVec4Color<T>(g, a, r, a); }
	TVec4Color<T> gagr() const { return TVec4Color<T>(g, a, g, r); }
	TVec4Color<T> gagg() const { return TVec4Color<T>(g, a, g, g); }
	TVec4Color<T> gagb() const { return TVec4Color<T>(g, a, g, b); }
	TVec4Color<T> gaga() const { return TVec4Color<T>(g, a, g, a); }
	TVec4Color<T> gabr() const { return TVec4Color<T>(g, a, b, r); }
	TVec4Color<T> gabg() const { return TVec4Color<T>(g, a, b, g); }
	TVec4Color<T> gabb() const { return TVec4Color<T>(g, a, b, b); }
	TVec4Color<T> gaba() const { return TVec4Color<T>(g, a, b, a); }
	TVec4Color<T> gaar() const { return TVec4Color<T>(g, a, a, r); }
	TVec4Color<T> gaag() const { return TVec4Color<T>(g, a, a, g); }
	TVec4Color<T> gaab() const { return TVec4Color<T>(g, a, a, b); }
	TVec4Color<T> gaaa() const { return TVec4Color<T>(g, a, a, a); }
	TVec4Color<T> brrr() const { return TVec4Color<T>(b, r, r, r); }
	TVec4Color<T> brrg() const { return TVec4Color<T>(b, r, r, g); }
	TVec4Color<T> brrb() const { return TVec4Color<T>(b, r, r, b); }
	TVec4Color<T> brra() const { return TVec4Color<T>(b, r, r, a); }
	TVec4Color<T> brgr() const { return TVec4Color<T>(b, r, g, r); }
	TVec4Color<T> brgg() const { return TVec4Color<T>(b, r, g, g); }
	TVec4Color<T> brgb() const { return TVec4Color<T>(b, r, g, b); }
	TVec4Color<T> brga() const { return TVec4Color<T>(b, r, g, a); }
	TVec4Color<T> brbr() const { return TVec4Color<T>(b, r, b, r); }
	TVec4Color<T> brbg() const { return TVec4Color<T>(b, r, b, g); }
	TVec4Color<T> brbb() const { return TVec4Color<T>(b, r, b, b); }
	TVec4Color<T> brba() const { return TVec4Color<T>(b, r, b, a); }
	TVec4Color<T> brar() const { return TVec4Color<T>(b, r, a, r); }
	TVec4Color<T> brag() const { return TVec4Color<T>(b, r, a, g); }
	TVec4Color<T> brab() const { return TVec4Color<T>(b, r, a, b); }
	TVec4Color<T> braa() const { return TVec4Color<T>(b, r, a, a); }
	TVec4Color<T> bgrr() const { return TVec4Color<T>(b, g, r, r); }
	TVec4Color<T> bgrg() const { return TVec4Color<T>(b, g, r, g); }
	TVec4Color<T> bgrb() const { return TVec4Color<T>(b, g, r, b); }
	TVec4Color<T> bgra() const { return TVec4Color<T>(b, g, r, a); }
	TVec4Color<T> bggr() const { return TVec4Color<T>(b, g, g, r); }
	TVec4Color<T> bggg() const { return TVec4Color<T>(b, g, g, g); }
	TVec4Color<T> bggb() const { return TVec4Color<T>(b, g, g, b); }
	TVec4Color<T> bgga() const { return TVec4Color<T>(b, g, g, a); }
	TVec4Color<T> bgbr() const { return TVec4Color<T>(b, g, b, r); }
	TVec4Color<T> bgbg() const { return TVec4Color<T>(b, g, b, g); }
	TVec4Color<T> bgbb() const { return TVec4Color<T>(b, g, b, b); }
	TVec4Color<T> bgba() const { return TVec4Color<T>(b, g, b, a); }
	TVec4Color<T> bgar() const { return TVec4Color<T>(b, g, a, r); }
	TVec4Color<T> bgag() const { return TVec4Color<T>(b, g, a, g); }
	TVec4Color<T> bgab() const { return TVec4Color<T>(b, g, a, b); }
	TVec4Color<T> bgaa() const { return TVec4Color<T>(b, g, a, a); }
	TVec4Color<T> bbrr() const { return TVec4Color<T>(b, b, r, r); }
	TVec4Color<T> bbrg() const { return TVec4Color<T>(b, b, r, g); }
	TVec4Color<T> bbrb() const { return TVec4Color<T>(b, b, r, b); }
	TVec4Color<T> bbra() const { return TVec4Color<T>(b, b, r, a); }
	TVec4Color<T> bbgr() const { return TVec4Color<T>(b, b, g, r); }
	TVec4Color<T> bbgg() const { return TVec4Color<T>(b, b, g, g); }
	TVec4Color<T> bbgb() const { return TVec4Color<T>(b, b, g, b); }
	TVec4Color<T> bbga() const { return TVec4Color<T>(b, b, g, a); }
	TVec4Color<T> bbbr() const { return TVec4Color<T>(b, b, b, r); }
	TVec4Color<T> bbbg() const { return TVec4Color<T>(b, b, b, g); }
	TVec4Color<T> bbbb() const { return TVec4Color<T>(b, b, b, b); }
	TVec4Color<T> bbba() const { return TVec4Color<T>(b, b, b, a); }
	TVec4Color<T> bbar() const { return TVec4Color<T>(b, b, a, r); }
	TVec4Color<T> bbag() const { return TVec4Color<T>(b, b, a, g); }
	TVec4Color<T> bbab() const { return TVec4Color<T>(b, b, a, b); }
	TVec4Color<T> bbaa() const { return TVec4Color<T>(b, b, a, a); }
	TVec4Color<T> barr() const { return TVec4Color<T>(b, a, r, r); }
	TVec4Color<T> barg() const { return TVec4Color<T>(b, a, r, g); }
	TVec4Color<T> barb() const { return TVec4Color<T>(b, a, r, b); }
	TVec4Color<T> bara() const { return TVec4Color<T>(b, a, r, a); }
	TVec4Color<T> bagr() const { return TVec4Color<T>(b, a, g, r); }
	TVec4Color<T> bagg() const { return TVec4Color<T>(b, a, g, g); }
	TVec4Color<T> bagb() const { return TVec4Color<T>(b, a, g, b); }
	TVec4Color<T> baga() const { return TVec4Color<T>(b, a, g, a); }
	TVec4Color<T> babr() const { return TVec4Color<T>(b, a, b, r); }
	TVec4Color<T> babg() const { return TVec4Color<T>(b, a, b, g); }
	TVec4Color<T> babb() const { return TVec4Color<T>(b, a, b, b); }
	TVec4Color<T> baba() const { return TVec4Color<T>(b, a, b, a); }
	TVec4Color<T> baar() const { return TVec4Color<T>(b, a, a, r); }
	TVec4Color<T> baag() const { return TVec4Color<T>(b, a, a, g); }
	TVec4Color<T> baab() const { return TVec4Color<T>(b, a, a, b); }
	TVec4Color<T> baaa() const { return TVec4Color<T>(b, a, a, a); }
	TVec4Color<T> arrr() const { return TVec4Color<T>(a, r, r, r); }
	TVec4Color<T> arrg() const { return TVec4Color<T>(a, r, r, g); }
	TVec4Color<T> arrb() const { return TVec4Color<T>(a, r, r, b); }
	TVec4Color<T> arra() const { return TVec4Color<T>(a, r, r, a); }
	TVec4Color<T> argr() const { return TVec4Color<T>(a, r, g, r); }
	TVec4Color<T> argg() const { return TVec4Color<T>(a, r, g, g); }
	TVec4Color<T> argb() const { return TVec4Color<T>(a, r, g, b); }
	TVec4Color<T> arga() const { return TVec4Color<T>(a, r, g, a); }
	TVec4Color<T> arbr() const { return TVec4Color<T>(a, r, b, r); }
	TVec4Color<T> arbg() const { return TVec4Color<T>(a, r, b, g); }
	TVec4Color<T> arbb() const { return TVec4Color<T>(a, r, b, b); }
	TVec4Color<T> arba() const { return TVec4Color<T>(a, r, b, a); }
	TVec4Color<T> arar() const { return TVec4Color<T>(a, r, a, r); }
	TVec4Color<T> arag() const { return TVec4Color<T>(a, r, a, g); }
	TVec4Color<T> arab() const { return TVec4Color<T>(a, r, a, b); }
	TVec4Color<T> araa() const { return TVec4Color<T>(a, r, a, a); }
	TVec4Color<T> agrr() const { return TVec4Color<T>(a, g, r, r); }
	TVec4Color<T> agrg() const { return TVec4Color<T>(a, g, r, g); }
	TVec4Color<T> agrb() const { return TVec4Color<T>(a, g, r, b); }
	TVec4Color<T> agra() const { return TVec4Color<T>(a, g, r, a); }
	TVec4Color<T> aggr() const { return TVec4Color<T>(a, g, g, r); }
	TVec4Color<T> aggg() const { return TVec4Color<T>(a, g, g, g); }
	TVec4Color<T> aggb() const { return TVec4Color<T>(a, g, g, b); }
	TVec4Color<T> agga() const { return TVec4Color<T>(a, g, g, a); }
	TVec4Color<T> agbr() const { return TVec4Color<T>(a, g, b, r); }
	TVec4Color<T> agbg() const { return TVec4Color<T>(a, g, b, g); }
	TVec4Color<T> agbb() const { return TVec4Color<T>(a, g, b, b); }
	TVec4Color<T> agba() const { return TVec4Color<T>(a, g, b, a); }
	TVec4Color<T> agar() const { return TVec4Color<T>(a, g, a, r); }
	TVec4Color<T> agag() const { return TVec4Color<T>(a, g, a, g); }
	TVec4Color<T> agab() const { return TVec4Color<T>(a, g, a, b); }
	TVec4Color<T> agaa() const { return TVec4Color<T>(a, g, a, a); }
	TVec4Color<T> abrr() const { return TVec4Color<T>(a, b, r, r); }
	TVec4Color<T> abrg() const { return TVec4Color<T>(a, b, r, g); }
	TVec4Color<T> abrb() const { return TVec4Color<T>(a, b, r, b); }
	TVec4Color<T> abra() const { return TVec4Color<T>(a, b, r, a); }
	TVec4Color<T> abgr() const { return TVec4Color<T>(a, b, g, r); }
	TVec4Color<T> abgg() const { return TVec4Color<T>(a, b, g, g); }
	TVec4Color<T> abgb() const { return TVec4Color<T>(a, b, g, b); }
	TVec4Color<T> abga() const { return TVec4Color<T>(a, b, g, a); }
	TVec4Color<T> abbr() const { return TVec4Color<T>(a, b, b, r); }
	TVec4Color<T> abbg() const { return TVec4Color<T>(a, b, b, g); }
	TVec4Color<T> abbb() const { return TVec4Color<T>(a, b, b, b); }
	TVec4Color<T> abba() const { return TVec4Color<T>(a, b, b, a); }
	TVec4Color<T> abar() const { return TVec4Color<T>(a, b, a, r); }
	TVec4Color<T> abag() const { return TVec4Color<T>(a, b, a, g); }
	TVec4Color<T> abab() const { return TVec4Color<T>(a, b, a, b); }
	TVec4Color<T> abaa() const { return TVec4Color<T>(a, b, a, a); }
	TVec4Color<T> aarr() const { return TVec4Color<T>(a, a, r, r); }
	TVec4Color<T> aarg() const { return TVec4Color<T>(a, a, r, g); }
	TVec4Color<T> aarb() const { return TVec4Color<T>(a, a, r, b); }
	TVec4Color<T> aara() const { return TVec4Color<T>(a, a, r, a); }
	TVec4Color<T> aagr() const { return TVec4Color<T>(a, a, g, r); }
	TVec4Color<T> aagg() const { return TVec4Color<T>(a, a, g, g); }
	TVec4Color<T> aagb() const { return TVec4Color<T>(a, a, g, b); }
	TVec4Color<T> aaga() const { return TVec4Color<T>(a, a, g, a); }
	TVec4Color<T> aabr() const { return TVec4Color<T>(a, a, b, r); }
	TVec4Color<T> aabg() const { return TVec4Color<T>(a, a, b, g); }
	TVec4Color<T> aabb() const { return TVec4Color<T>(a, a, b, b); }
	TVec4Color<T> aaba() const { return TVec4Color<T>(a, a, b, a); }
	TVec4Color<T> aaar() const { return TVec4Color<T>(a, a, a, r); }
	TVec4Color<T> aaag() const { return TVec4Color<T>(a, a, a, g); }
	TVec4Color<T> aaab() const { return TVec4Color<T>(a, a, a, b); }
	TVec4Color<T> aaaa() const { return TVec4Color<T>(a, a, a, a); }

	EVE_FORCE_INLINE static TVec4Color<T> rAxis() { return TVec4Color<T>(1, 0, 0, 0); }
	EVE_FORCE_INLINE static TVec4Color<T> gAxis() { return TVec4Color<T>(0, 1, 0, 0); }
	EVE_FORCE_INLINE static TVec4Color<T> bAxis() { return TVec4Color<T>(0, 0, 1, 0); }
	EVE_FORCE_INLINE static TVec4Color<T> aAxis() { return TVec4Color<T>(0, 0, 0, 1); }

	EVE_FORCE_INLINE static TVec4Color<T> NaN()   { return TVec4Color<T>(eve::math::NaN(), eve::math::NaN(), eve::math::NaN(), eve::math::NaN()); }
};

//! Converts a coordinate from rectangular (Cartesian) coordinates to polar coordinates of the form (radius, theta)
template<typename T>
TVec2<T> toPolar( TVec2<T> car )
{
	const T epsilon = static_cast<T>(0.0000001);
	T theta;
	if( eve::math::abs( car.x ) < epsilon ) { // x == 0
		if( eve::math::abs( car.y ) < epsilon ) theta = 0;
		else if( car.y > 0 ) theta = (T)M_PI / 2;
		else theta = ( (T)M_PI * 3 ) / 2;
	}
	else if ( car.x > 0 ) {
		if( car.y < 0 ) theta = eve::math::atan( car.y / car.x ) + 2 * (T)M_PI;
		else theta = eve::math::atan( car.y / car.x );
	}
	else // car.x < 0
		theta = (eve::math::atan( car.y / car.x ) + M_PI );

	return TVec2<T>( car.length(), theta );
}

//! Converts a coordinate from polar coordinates of the form (radius, theta) to rectangular coordinates
template<typename T>
TVec2<T> fromPolar( TVec2<T> pol )
{
	return TVec2<T>( eve::math::cos( pol.y ) *  pol.x , eve::math::sin( pol.y ) *  pol.x );
}

template<typename T,typename Y> inline TVec2<T> operator *( Y s, const TVec2<T> &v ) { return TVec2<T>( v.x * s, v.y * s ); }
template<typename T,typename Y> inline TVec2<T> operator *( const TVec2<T> &v, Y s ) { return TVec2<T>( v.x * s, v.y * s ); }
template<typename T,typename Y> inline TVec3<T> operator *( Y s, const TVec3<T> &v ) { return TVec3<T>( v.x * s, v.y * s, v.z * s ); }
template<typename T,typename Y> inline TVec3<T> operator *( const TVec3<T> &v, Y s ) { return TVec3<T>( v.x * s, v.y * s, v.z * s ); }
template<typename T,typename Y> inline TVec4<T> operator *( Y s, const TVec4<T> &v ) { return TVec4<T>( v.x * s, v.y * s, v.z * s, v.w * s ); }
template<typename T,typename Y> inline TVec4<T> operator *( const TVec4<T> &v, Y s ) { return TVec4<T>( v.x * s, v.y * s, v.z * s, v.w * s ); }

template <typename T> T dot( const TVec2<T>& a, const TVec2<T>& b ) { return a.dot( b ); }
template <typename T> T dot( const TVec3<T>& a, const TVec3<T>& b ) { return a.dot( b ); }
template <typename T> T dot( const TVec4<T>& a, const TVec4<T>& b ) { return a.dot( b ); }

template <typename T> TVec3<T> cross( const TVec3<T>& a, const TVec3<T>& b ) { return a.cross( b ); }
template <typename T> TVec4<T> cross( const TVec4<T>& a, const TVec4<T>& b ) { return a.cross( b ); }

template <typename T> bool isNaN( const TVec2<T>& a ) { return std::isnan( a.x ) || std::isnan( a.y ); }
template <typename T> bool isNaN( const TVec3<T>& a ) { return std::isnan( a.x ) || std::isnan( a.y ) || std::isnan( a.z ); }
template <typename T> bool isNaN( const TVec4<T>& a ) { return std::isnan( a.x ) || std::isnan( a.y ) || std::isnan( a.z ) || std::isnan( a.w ); }



///////////////////////////////////////////////////////////////////////////////////////////////////
//		Typedefs
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef TVec2<float>			Vec2f;
typedef TVec2<double>			Vec2d;

typedef TVec3<float>			Vec3f;
typedef TVec3<double>			Vec3d;

typedef TVec4<float>			Vec4f;
typedef TVec4<double>			Vec4d;

typedef TVec4Color<float>		Color4f;
typedef TVec4Color<double>		Color4d;


#endif // __TVECTOR_H__
