
#pragma once
#ifndef __TMATH_H__
#define __TMATH_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif


#ifndef M_E
#define M_E        2.71828182845904523536
#endif

#ifndef M_LOG2E
#define M_LOG2E    1.44269504088896340736
#endif

#ifndef M_LOG10E
#define M_LOG10E   0.434294481903251827651
#endif

#ifndef M_LN2
#define M_LN2      0.693147180559945309417
#endif

#ifndef M_LN10
#define M_LN10     2.30258509299404568402
#endif

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

#ifndef M_1_PI
#define M_1_PI     0.318309886183790671538
#endif

#ifndef M_2_PI
#define M_2_PI     0.636619772367581343076
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257390
#endif

#ifndef M_SQRT2
#define M_SQRT2    1.41421356237309504880
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2  0.707106781186547524401
#endif


#define EVE_MATH_EPSILON		FLT_EPSILON
#define EVE_MATH_INFINITY		FLT_MAX

#define FLOAT_QUASI_ZERO  0.000001f
#define DOUBLE_QUASI_ZERO 0.000000000000000000001


#define DIVIDE_3D	0.333333333333333333333
#define DIVIDE_3F	0.333333f

#define DIVIDE_45D	0.022222222222222222222
#define DIVIDE_45F	0.022222f

#define DIVIDE_90D	0.011111111111111111111
#define DIVIDE_90F	0.011111f

#define DIVIDE_180D	0.005555555555555555555
#define DIVIDE_180F	0.005555f



template<typename T>
struct tmath
{
	static T	acos  ( T x )			{ return ::acos		( double(x) );				}
	static T	asin  ( T x )			{ return ::asin		( double(x) );				}
	static T	atan  ( T x )			{ return ::atan		( double(x) );				}
	static T	atan2 ( T x, T y )		{ return ::atan2	( double(y), double(x) );	}
	static T	cos   ( T x )			{ return ::cos		( double(x) );				}
	static T	sin   ( T x )			{ return ::sin		( double(x) );				}
	static T	tan   ( T x )			{ return ::tan		( double(x) );				}
	static T	cosh  ( T x )			{ return ::cosh		( double(x) );				}
	static T	sinh  ( T x )			{ return ::sinh		( double(x) );				}
	static T	tanh  ( T x )			{ return ::tanh		( double(x) );				}
	static T	exp   ( T x )			{ return ::exp		( double(x) );				}
	static T	log   ( T x )			{ return ::log		( double(x) );				}
	static T	log10 ( T x )			{ return ::log10	( double(x) );				}
	static T	modf  ( T x, T *iptr )
	{
		double ival;
		T rval( ::modf (double(x),&ival));
		*iptr = ival;
		return rval;
	}
	static T	pow   (T x, T y)	{ return ::pow (double(x), double(y)); }
	static T	sqrt  (T x)			{ return ::sqrt (double(x)); }

	static T	sqrt_approx(T x)
	{
		int val_int = *(int*)&x; /* Same bits, but as an int */
		/*
		 * To justify the following code, prove that
		 *
		 * ((((val_int / 2^m) - b) / 2) + b) * 2^m = ((val_int - 2^m) / 2) + ((b + 1) / 2) * 2^m)
		 *
		 * where
		 * b = exponent bias
		 * m = number of mantissa bits
		 */
 
		val_int -= 1 << 23;		/* Subtract 2^m. */
		val_int >>= 1;			/* Divide by 2. */
		val_int += 1 << 29;		/* Add ((b + 1) / 2) * 2^m. */
 
		return *(T*)&val_int; /* Interpret again as float */
	}

	static T	rsqrt (T x)
	{
		float xhalf = 0.5f*x;
		float u_x;
		int u_i;

		u_x = x;
		u_i = 0x5f3759df - (u_i >> 1);
		/* The next line can be repeated any number of times to increase accuracy */
		u_x = u_x * (1.5f - xhalf * u_x * u_x);

		return T(u_x);
	}

#if defined( _MSC_VER )
	static T	cbrt( T x )						{ return ( x > 0 ) ? (::pow( x, 1.0 * DIVIDE_3D )) : (- ::pow( -x, 1.0 * DIVIDE_3D ) ); }
#else
	static T	cbrt( T x )						{ return ::cbrt( x ); }
#endif
	static T	ceil  (T x)						{ return ::ceil (double(x));}
	static T	abs  (T x)						{ return ::fabs (double(x));}
	static T	floor (T x)						{ return ::floor (double(x));}
	static T	fmod  (T x, T y)				{ return ::fmod (double(x), double(y));}
	static T	hypot (T x, T y)				{ return ::hypot (double(x), double(y));}
	static T	signum (T x)					{ return ( x >0.0 ) ? 1.0 : ( ( x < 0.0 ) ? -1.0 : 0.0 ); }
	static T	min(T x, T y)					{ return ( x < y ) ? x : y; }
	static T	max(T x, T y)					{ return ( x > y ) ? x : y; }
	static T	clamp(T x, T min=0, T max=1)	{ return ( x < min ) ? min : ( ( x > max ) ? max : x );}
	
	static T	lerp( T start, T stop, T amt)	{ return start + (stop-start) * amt; }; 
	
	static bool equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) { return (abs(a - b) < epsilon); }
};


template<>
struct tmath<float>
{
	static float	acos  ( float x )				{ return ::acosf	( x );		}
	static float	asin  ( float x )				{ return ::asinf	( x );		}
	static float	atan  ( float x )				{ return ::atanf	( x );		}
	static float	atan2 ( float x, float y )		{ return ::atan2f	( y, x );	}
	static float	cos   ( float x )				{ return ::cosf		( x );		}
	static float	sin   ( float x )				{ return ::sinf		( x );		}
	static float	tan   ( float x )				{ return ::tanf		( x );		}
	static float	cosh  ( float x )				{ return ::coshf	( x );		}
	static float	sinh  ( float x )				{ return ::sinhf	( x );		}
	static float	tanh  ( float x )				{ return ::tanhf	( x );		}
	static float	exp   ( float x )				{ return ::expf		( x );		}
	static float	log   ( float x )				{ return ::logf		( x );		}
	static float	log10 ( float x )				{ return ::log10f	( x );		}
	static float	modf  ( float x, float *y )		{ return ::modff	( x, y );	}
	static float	pow   ( float x, float y )		{ return ::powf		( x, y );	}
	static float	sqrt  ( float x )				{ return ::sqrtf	( x );		}

	static float	sqrt_approx(float x)
	{
		int val_int = *(int*)&x; /* Same bits, but as an int */
		/*
		 * To justify the following code, prove that
		 *
		 * ((((val_int / 2^m) - b) / 2) + b) * 2^m = ((val_int - 2^m) / 2) + ((b + 1) / 2) * 2^m)
		 *
		 * where
		 * b = exponent bias
		 * m = number of mantissa bits
		 */
 
		val_int -= 1 << 23;		/* Subtract 2^m. */
		val_int >>= 1;			/* Divide by 2. */
		val_int += 1 << 29;		/* Add ((b + 1) / 2) * 2^m. */
 
		return *(float*)&val_int; /* Interpret again as float */
	}

	static float	rsqrt (float x)
	{
		float xhalf = 0.5f*x;
		float u_x;
		int u_i;

		u_x = x;
		u_i = 0x5f3759df - (u_i >> 1);
		/* The next line can be repeated any number of times to increase accuracy */
		u_x = u_x * (1.5f - xhalf * u_x * u_x);

		return u_x;
	}

#if defined( _MSC_VER )
	static float	cbrt( float x )		{ return ( x > 0 ) ? (::powf( x, 1.0f * DIVIDE_3F )) : (- ::powf( -x, 1.0f * DIVIDE_3F ) ); }
#else
	static float	cbrt  (float x)			{ return ::cbrtf( x ); }	
#endif
	static float	ceil  (float x)			{return ::ceilf (x);}
	static float	abs   (float x)			{return ::fabsf (x);}
	static float	floor (float x)			{return ::floorf (x);}
	static float	fmod  (float x, float y)	{return ::fmodf (x, y);}
	#if !defined(_MSC_VER)
	static float	hypot (float x, float y)	{return ::hypotf (x, y);}
	#else
	static float hypot (float x, float y)	{return ::sqrtf(x*x + y*y);}
	#endif
	static float signum (float x)		{return ( x > 0.0f ) ? 1.0f : ( ( x < 0.0f ) ? -1.0f : 0.0f ); }
	static float min(float x, float y)					{return ( x < y ) ? x : y; }
	static float max(float x, float y)					{return ( x > y ) ? x : y; }
	static float clamp(float x, float min=0, float max=1)	{return ( x < min ) ? min : ( ( x > max ) ? max : x );}

	static float lerp( float start, float stop, float amt) { return start + (stop-start) * amt; };

	static bool equal(float a, float b, float epsilon = std::numeric_limits<float>::epsilon()) { return (abs(a - b) < epsilon); }

	inline static float quasi_zero( void )		{ return  0.000001f; }
	inline static float quasi_zero_neg( void )	{ return -0.000001f; }
};



inline float toRadians( float x )
{
	return x * 0.017453292519943295769f; // ( x * PI / 180 )
}

inline double toRadians( double x )
{
	return x * 0.017453292519943295769; // ( x * PI / 180 )
}

inline float toDegrees( float x )
{
	return x * 57.295779513082321f; // ( x * 180 / PI )
}

inline double toDegrees( double x )
{
	return x * 57.295779513082321; // ( x * 180 / PI )
}

template<typename T, typename L>
T lerp( const T &a, const T &b, L factor )
{
	return a + ( b - a ) * factor;
}

template<typename T>
T lmap(T val, T inMin, T inMax, T outMin, T outMax)
{
	return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
}

template<typename T, typename L>
T bezierInterp( T a, T b, T c, T d, L t)
{
    L t1 = static_cast<L>(1.0) - t;
    return a*(t1*t1*t1) + b*(3*t*t1*t1) + c*(3*t*t*t1) + d*(t*t*t);
}

template<typename T, typename L>
T bezierInterpRef( const T &a, const T &b, const T &c, const T &d, L t)
{
    L t1 = static_cast<L>(1.0) - t;
    return a*(t1*t1*t1) + b*(3*t*t1*t1) + c*(3*t*t*t1) + d*(t*t*t);
}

template<typename T>
T constrain( T val, T minVal, T maxVal )
{
	if( val < minVal ) return minVal;
	else if( val > maxVal ) return maxVal;
	else return val;
}

// Don Hatch's version of sin(x)/x, which is accurate for very small x.
// Returns 1 for x == 0.
template <class T>
T sinx_over_x( T x )
{
    if( x * x < 1.19209290E-07F )
	return T( 1 );
    else
	return tmath<T>::sin( x ) / x;
}

// There are faster techniques for this, but this is portable
inline uint32_t log2floor( uint32_t x )
{
    uint32_t result = 0;
    while( x >>= 1 )
        ++result;

    return result;
}

inline uint32_t log2ceil( uint32_t x )
{
	uint32_t isNotPowerOf2 = (x & (x - 1));
	return ( isNotPowerOf2 ) ? (log2floor( x ) + 1) : log2floor( x );
}

inline uint32_t nextPowerOf2( uint32_t x )
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return(x+1);
}

template<typename T>
inline int solveLinear( T a, T b, T result[1] )
{
	if( a == 0 ) return (b == 0 ? -1 : 0 );
	result[0] = -b / a;
	return 1;
}

template<typename T>
inline int solveQuadratic( T a, T b, T c, T result[2] )
{
	if( a == 0 ) return solveLinear( b, c, result );

	T radical = b * b - 4 * a * c;
	if( radical < 0 ) return 0;

	if( radical == 0 ) {
		result[0] = -b / (2 * a);
		return 1;
	}

	T srad = tmath<T>::sqrt( radical );
	result[0] = ( -b - srad ) / (2 * a);
	result[1] = ( -b + srad ) / (2 * a);
	if( a < 0 ) std::swap( result[0], result[1] );
	return 2;
}

template<typename T>
int solveCubic( T a, T b, T c, T d, T result[3] );


#if defined( NATIVE_OS_WIN32 )
namespace std {
	inline bool isfinite( float arg ) { return _finite( arg ) != 0; }
	inline bool isfinite( double arg ) { return _finite( arg ) != 0; }
}
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//		Typedefs
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef tmath<int32_t>		mathi;
typedef tmath<uint32_t>		mathui;
typedef tmath<float>		mathf;
typedef tmath<double>		mathd;


#endif // __TMATH_H__
