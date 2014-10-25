
#pragma once
#ifndef __EVE_MATH_MATH_H__
#define __EVE_MATH_MATH_H__

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

#define QUASI_ZEROD 0.000000000000000000001
#define QUASI_ZEROF 0.000000001f


#define EVE_DIVIDE_3D	0.333333333333333333333
#define EVE_DIVIDE_3F	0.333333333f

#define EVE_DIVIDE_45D	0.022222222222222222222
#define EVE_DIVIDE_45F	0.022222222f

#define EVE_DIVIDE_90D	0.011111111111111111111
#define EVE_DIVIDE_90F	0.011111111f

#define EVE_DIVIDE_180D	0.005555555555555555555
#define EVE_DIVIDE_180F	0.005555555f

#define EVE_PI_180F 0.017453292f
#define EVE_PI_180D 0.017453292519943295769

#define EVE_180_PIF 57.29577951f
#define EVE_180_PID 57.295779513082321


namespace eve
{
	namespace math
	{
		EVE_FORCE_INLINE float  toRadians(float  x)					{ return x * EVE_PI_180F; }
		EVE_FORCE_INLINE double toRadians(double x)					{ return x * EVE_PI_180D; }
		
		EVE_FORCE_INLINE float  toDegrees(float  x)					{ return x * EVE_180_PIF; }
		EVE_FORCE_INLINE double toDegrees(double x)					{ return x * EVE_180_PID; }
		
		
		EVE_FORCE_INLINE float  lerp(const float  &a, const float  &b, float  factor)	{ return a + (b - a) * factor; }
		EVE_FORCE_INLINE double lerp(const double &a, const double &b, double factor)	{ return a + (b - a) * factor; }
		
		
		EVE_FORCE_INLINE float  lmap(float  val, float  inMin, float  inMax, float  outMin, float  outMax) { return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin)); }
		EVE_FORCE_INLINE double lmap(double val, double inMin, double inMax, double outMin, double outMax) { return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin)); }
		
		
		EVE_FORCE_INLINE float  bezierInterp(float  a, float  b, float  c, float  d, float  t)	{ float  t1(1.0f-t); return a*(t1*t1*t1) + b*(3 * t*t1*t1) + c*(3 * t*t*t1) + d*(t*t*t); }
		EVE_FORCE_INLINE float  bezierInterp(float  a, float  b, float  c, float  d, double t)	{ double t1(1.0 -t); return a*(t1*t1*t1) + b*(3 * t*t1*t1) + c*(3 * t*t*t1) + d*(t*t*t); }
		EVE_FORCE_INLINE double bezierInterp(double a, double b, double c, double d, double t)	{ double t1(1.0 -t); return a*(t1*t1*t1) + b*(3 * t*t1*t1) + c*(3 * t*t*t1) + d*(t*t*t); }
		EVE_FORCE_INLINE double bezierInterp(double a, double b, double c, double d, float  t)	{ float  t1(1.0f-t); return a*(t1*t1*t1) + b*(3 * t*t1*t1) + c*(3 * t*t*t1) + d*(t*t*t); }
		
		
		EVE_FORCE_INLINE float  constrain(float  val, float  minVal, float  maxVal) { if (val < minVal) return minVal; else if (val > maxVal) return maxVal; else return val; }
		EVE_FORCE_INLINE double constrain(double val, double minVal, double maxVal) { if (val < minVal) return minVal; else if (val > maxVal) return maxVal; else return val; }
				
		
		EVE_FORCE_INLINE float	acos(float  x)						{ return ::acosf(x);		}
		EVE_FORCE_INLINE double acos(double x)						{ return ::acos(x);			}

		EVE_FORCE_INLINE float	asin(float  x)						{ return ::asinf(x);		}
		EVE_FORCE_INLINE double asin(double x)						{ return ::asin(x);			}
		
		EVE_FORCE_INLINE float	atan(float  x)						{ return ::atanf(x);		}
		EVE_FORCE_INLINE double atan(double x)						{ return ::atan(x);			}
		
		EVE_FORCE_INLINE float	atan2(float  x, float  y)			{ return ::atan2f(y, x);	}
		EVE_FORCE_INLINE double atan2(double x, double y)			{ return ::atan2(y, x);		}
		
		EVE_FORCE_INLINE float	cos(float  x)						{ return ::cosf(x);			}
		EVE_FORCE_INLINE double cos(double x)						{ return ::cos(x);			}
		
		EVE_FORCE_INLINE float	sin(float  x)						{ return ::sinf(x);			}
		EVE_FORCE_INLINE double sin(double x)						{ return ::sin(x);			}
		
		EVE_FORCE_INLINE float	tan(float  x)						{ return ::tanf(x);			}
		EVE_FORCE_INLINE double tan(double x)						{ return ::tan(x);			}

		EVE_FORCE_INLINE float	cosh(float  x)						{ return ::coshf(x);		}
		EVE_FORCE_INLINE double cosh(double x)						{ return ::cosh(x);			}
		
		EVE_FORCE_INLINE float	sinh(float  x)						{ return ::sinhf(x);		}
		EVE_FORCE_INLINE double sinh(double x)						{ return ::sinh(x);			}
		
		EVE_FORCE_INLINE float	tanh(float  x)						{ return ::tanhf(x);		}
		EVE_FORCE_INLINE double tanh(double x)						{ return ::tanh(x);			}
		
		EVE_FORCE_INLINE float	exp(float  x)						{ return ::expf(x);			}
		EVE_FORCE_INLINE double exp(double x)						{ return ::exp(x);			}

		EVE_FORCE_INLINE float	modf(float x, float *y)				{ return ::modff(x, y);		}
		EVE_FORCE_INLINE double	modf(double x, double *y)			{ return ::modf(x, y);		}
		
		EVE_FORCE_INLINE float	log(float  x)						{ return ::logf(x);			}
		EVE_FORCE_INLINE double log(double x)						{ return ::log(x);			}
		
		EVE_FORCE_INLINE float	log10(float  x)						{ return ::log10f(x);		}
		EVE_FORCE_INLINE double log10(double x)						{ return ::log10(x);		}

		EVE_FORCE_INLINE int32_t  log2floor(int32_t  x)				{ int32_t  ret = 0; while (x >>= 1) ++ret; return ret; }
		EVE_FORCE_INLINE uint32_t log2floor(uint32_t x)				{ uint32_t ret = 0; while (x >>= 1) ++ret; return ret; }

		EVE_FORCE_INLINE int32_t  log2ceil(int32_t  x)				{ int32_t  ret = (x & (x - 1)); return (ret) ? (log2floor(x) + 1) : log2floor(x); }
		EVE_FORCE_INLINE uint32_t log2ceil(uint32_t x)				{ uint32_t ret = (x & (x - 1)); return (ret) ? (log2floor(x) + 1) : log2floor(x); }

		EVE_FORCE_INLINE int32_t  nextPowerOf2(int32_t  x)			{ x |= (x >> 1); x |= (x >> 2); x |= (x >> 4); x |= (x >> 8); x |= (x >> 16); return(x + 1); }
		EVE_FORCE_INLINE uint32_t nextPowerOf2(uint32_t x)			{ x |= (x >> 1); x |= (x >> 2); x |= (x >> 4); x |= (x >> 8); x |= (x >> 16); return(x + 1); }

		EVE_FORCE_INLINE float	pow(float x, float y)				{ return ::powf(x, y);		}
		EVE_FORCE_INLINE double	pow(double x, double y)				{ return ::pow(x, y);		}

		EVE_FORCE_INLINE float	sqrt(float x)						{ return ::sqrtf(x);		}
		EVE_FORCE_INLINE double	sqrt(double x)						{ return ::sqrt(x);			}
		
		EVE_FORCE_INLINE float	cbrt(float  x)						{ return ::cbrtf(x);		}
		EVE_FORCE_INLINE double	cbrt(double x)						{ return ::cbrt(x);			}

		EVE_FORCE_INLINE float	ceil(float  x)						{ return ::ceilf(x);		}
		EVE_FORCE_INLINE double	ceil(double x)						{ return ::ceil(x);			}

		EVE_FORCE_INLINE float	abs(float  x)						{ return ::fabsf(x);		}
		EVE_FORCE_INLINE double	abs(double x)						{ return ::fabs(x);			}

		EVE_FORCE_INLINE float	floor(float  x)						{ return ::floorf(x);		}
		EVE_FORCE_INLINE double	floor(double x)						{ return ::floor(x);		}

		EVE_FORCE_INLINE float	fmod(float  x, float  y)			{ return ::fmodf(x, y);		}
		EVE_FORCE_INLINE double	fmod(double x, double y)			{ return ::fmod(x, y);		}

		EVE_FORCE_INLINE float	hypot(float  x, float  y)			{ return ::hypotf(x, y);	}
		EVE_FORCE_INLINE double	hypot(double x, double y)			{ return ::hypot(x, y);		}

		EVE_FORCE_INLINE float  signum(float  x)					{ return (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f); }
		EVE_FORCE_INLINE double signum(double x)					{ return (x > 0.0)  ? 1.0  : ((x < 0.0)  ? -1.0  : 0.0 ); }
		
		EVE_FORCE_INLINE int32_t  min(int32_t  x, int32_t  y)		{ return (x < y) ? x : y;	}
		EVE_FORCE_INLINE uint32_t min(uint32_t x, uint32_t y)		{ return (x < y) ? x : y;	}
		EVE_FORCE_INLINE float	  min(float    x, float    y)		{ return (x < y) ? x : y;	}
		EVE_FORCE_INLINE double   min(double   x, double   y)		{ return (x < y) ? x : y;	}

		EVE_FORCE_INLINE int32_t  max(int32_t  x, int32_t  y)		{ return (x > y) ? x : y; }
		EVE_FORCE_INLINE uint32_t max(uint32_t x, uint32_t y)		{ return (x > y) ? x : y; }
		EVE_FORCE_INLINE float    max(float    x, float    y)		{ return (x > y) ? x : y; }
		EVE_FORCE_INLINE double   max(double   x, double   y)		{ return (x > y) ? x : y; }

		EVE_FORCE_INLINE int32_t  clamp(int32_t  x, int32_t  min = 0, int32_t  max = 1)	{ return (x < min) ? min : ((x > max) ? max : x); }
		EVE_FORCE_INLINE uint32_t clamp(uint32_t x, uint32_t min = 0, uint32_t max = 1)	{ return (x < min) ? min : ((x > max) ? max : x); }
		EVE_FORCE_INLINE float    clamp(float    x, float    min = 0, float    max = 1)	{ return (x < min) ? min : ((x > max) ? max : x); }
		EVE_FORCE_INLINE double   clamp(double   x, double   min = 0, double   max = 1)	{ return (x < min) ? min : ((x > max) ? max : x); }

		EVE_FORCE_INLINE float  lerp(float  start, float  stop, float  amt) { return start + (stop - start) * amt; };
		EVE_FORCE_INLINE double lerp(double start, double stop, double amt) { return start + (stop - start) * amt; };

		EVE_FORCE_INLINE bool equal(float  a, float  b, float  epsilon = std::numeric_limits<float>::epsilon())  { return (abs(a - b) < epsilon); }
		EVE_FORCE_INLINE bool equal(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) { return (abs(a - b) < epsilon); }

		EVE_FORCE_INLINE bool isfinite(float  arg)					{ return std::isfinite(arg) != 0; }
		EVE_FORCE_INLINE bool isfinite(double arg)					{ return std::isfinite(arg) != 0; }


		/*
		* To justify the following code, prove that
		*
		* ((((val_int / 2^m) - b) / 2) + b) * 2^m = ((val_int - 2^m) / 2) + ((b + 1) / 2) * 2^m)
		*
		* where
		* b = exponent bias
		* m = number of mantissa bits
		*/
		EVE_FORCE_INLINE float sqrt_approx(float x)
		{
			int32_t val_int = *(int32_t*)&x; /* Same bits, but as an int32_t */

			val_int -= 1 << 23;		/* Subtract 2^m. */
			val_int >>= 1;			/* Divide by 2. */
			val_int += 1 << 29;		/* Add ((b + 1) / 2) * 2^m. */

			return *reinterpret_cast<float*>(&val_int); /* Interpret again as float */
		}
		EVE_FORCE_INLINE double sqrt_approx(double x)
		{
			int32_t val_int = *(int32_t*)&x; /* Same bits, but as an int32_t */

			val_int -= 1 << 23;		/* Subtract 2^m. */
			val_int >>= 1;			/* Divide by 2. */
			val_int += 1 << 29;		/* Add ((b + 1) / 2) * 2^m. */

			return *reinterpret_cast<double*>(&val_int); /* Interpret again as double */
		}


		EVE_FORCE_INLINE float rsqrt(float x)
		{
			float xhalf = 0.5f*x;
			float u_x;
			int32_t u_i;

			u_x = x;
			u_i = 0x5f3759df - (u_i >> 1);
			/* The next line can be repeated any number of times to increase accuracy */
			u_x = u_x * (1.5f - xhalf * u_x * u_x);

			return u_x;
		}
		EVE_FORCE_INLINE double rsqrt(double x)
		{
			double xhalf = 0.5f*x;
			double u_x;
			int32_t u_i;

			u_x = x;
			u_i = 0x5f3759df - (u_i >> 1);
			/* The next line can be repeated any number of times to increase accuracy */
			u_x = u_x * (1.5 - xhalf * u_x * u_x);

			return u_x;
		}



		// Don Hatch's version of sin(x)/x, which is accurate for very small x.
		// Returns 1 for x == 0.
		template <class T>
		EVE_FORCE_INLINE T sinx_over_x(T x)
		{
			if (x * x < 1.19209290E-07F)
				return T(1);
			else
				return eve::math::sin(x) / x;
		}

		template<typename T>
		EVE_FORCE_INLINE int32_t solveLinear(T a, T b, T result[1])
		{
			if (a == 0) return (b == 0 ? -1 : 0);
			result[0] = -b / a;
			return 1;
		}

		template<typename T>
		EVE_FORCE_INLINE int32_t solveQuadratic(T a, T b, T c, T result[2])
		{
			if (a == 0) return eve::math::solveLinear(b, c, result);

			T radical = b * b - 4 * a * c;
			if (radical < 0) return 0;

			if (radical == 0) {
				result[0] = -b / (2 * a);
				return 1;
			}

			T srad = eve::math::sqrt(radical);
			result[0] = (-b - srad) / (2 * a);
			result[1] = (-b + srad) / (2 * a);
			if (a < 0) std::swap(result[0], result[1]);
			return 2;
		}


		template<typename T>
		int32_t solveCubic(T a, T b, T c, T d, T result[3])
		{
			if (a == 0)
				return eve::math::solveQuadratic(b, c, d, result);

			T f = ((3 * c / a) - ((b * b) / (a * a))) / 3;
			T g = ((2 * b * b * b) / (a * a * a) - (9 * b * c) / (a * a) + (27 * d) / (a)) / 27;
			T h = g * g / 4 + f * f * f / 27;

			if (f == 0 && g == 0 && h == 0) {
				result[0] = -eve::math::cbrt(d / a);
				return 1;
			}
			else if (h > 0) {
				// 1 root
				T r = -(g / 2) + eve::math::sqrt(h);
				T s = eve::math::cbrt(r);
				T t = -(g / 2) - eve::math::sqrt(h);
				T u = eve::math::cbrt(t);

				result[0] = (s + u) - (b / (3 * a));
				return 1;
			}
			else { // 3 roots
				T i = eve::math::sqrt((g * g / 4) - h);
				T j = eve::math::cbrt(i);
				T k = eve::math::acos(-(g / (2 * i)));
				T l = -j;
				T m = eve::math::cos(k / 3);
				T n = eve::math::sqrt(3) * eve::math::sin(k / 3);
				T p = -b / (3 * a);
				result[0] = 2 * j * eve::math::cos(k / 3) - (b / (3 * a));
				result[1] = l * (m + n) + p;
				result[2] = l * (m - n) + p;
				return 3;
			}
		}

	} //namespace math

} // namespace eve

#endif // __EVE_MATH_MATH_H__
