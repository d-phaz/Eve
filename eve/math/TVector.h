
#pragma once
#ifndef __EVE_MATH_TVECTOR_H__
#define __EVE_MATH_TVECTOR_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_TVECTOR_2_H__
#include "eve/math/TVector2.h"
#endif

#ifndef __EVE_MATH_TVECTOR_3_H__
#include "eve/math/TVector3.h"
#endif

#ifndef __EVE_MATH_TVECTOR_4_H__
#include "eve/math/TVector4.h"
#endif


namespace eve
{
	namespace math
	{

		/** \brief Convert coordinate from rectangular (Cartesian) coordinates to polar coordinates of the form (radius, theta). */
		template<typename T>
		TVec2<T> toPolar(TVec2<T> car);

		/** \brief Convert coordinate from polar coordinates of the form (radius, theta) to rectangular coordinates. */
		template<typename T>
		TVec2<T> fromPolar(TVec2<T> pol);
		

	} // namespace math
	

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Typedefs
	///////////////////////////////////////////////////////////////////////////////////////////////////

	typedef eve::math::TVec2<float>			vec2f;
	typedef eve::math::TVec2<double>		vec2d;

	typedef eve::math::TVec3<float>			vec3f;
	typedef eve::math::TVec3<double>		vec3d;

	typedef eve::math::TVec4<float>			vec4f;
	typedef eve::math::TVec4<double>		vec4d;

} // namespace eve

//=================================================================================================
template<typename T>
eve::math::TVec2<T> eve::math::toPolar(eve::math::TVec2<T> car)
{
	const T epsilon = static_cast<T>(0.0000001);
	T theta;
	if (eve::math::abs(car.x) < epsilon) // x == 0
	{ 
		if (eve::math::abs(car.y) < epsilon) theta = 0;
		else if (car.y > 0) theta = (T)M_PI / 2;
		else theta = ((T)M_PI * 3) / 2;
	}
	else if (car.x > 0) 
	{
		if (car.y < 0) theta = eve::math::atan(car.y / car.x) + 2 * (T)M_PI;
		else theta = eve::math::atan(car.y / car.x);
	}
	else // car.x < 0
	{
		theta = (eve::math::atan(car.y / car.x) + M_PI);
	}

	return eve::math::TVec2<T>(car.length(), theta);
}

template<typename T>
eve::math::TVec2<T> eve::math::fromPolar(TVec2<T> pol)
{
	return eve::math::TVec2<T>(eve::math::cos(pol.y) *  pol.x, eve::math::sin(pol.y) *  pol.x);
}



//=================================================================================================
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator * (Y s, const eve::math::TVec2<T> &v) { return eve::math::TVec2<T>(v.x * s, v.y * s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator * (const eve::math::TVec2<T> &v, Y s) { return eve::math::TVec2<T>(v.x * s, v.y * s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator * (Y s, const eve::math::TVec3<T> &v) { return eve::math::TVec3<T>(v.x * s, v.y * s, v.z * s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator * (const eve::math::TVec3<T> &v, Y s) { return eve::math::TVec3<T>(v.x * s, v.y * s, v.z * s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator * (Y s, const eve::math::TVec4<T> &v) { return eve::math::TVec4<T>(v.x * s, v.y * s, v.z * s, v.w * s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator * (const eve::math::TVec4<T> &v, Y s) { return eve::math::TVec4<T>(v.x * s, v.y * s, v.z * s, v.w * s); }


//=================================================================================================
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator / (Y s, const eve::math::TVec2<T> &v) { return eve::math::TVec2<T>(v.x / s, v.y / s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec2<T> operator / (const eve::math::TVec2<T> &v, Y s) { return eve::math::TVec2<T>(v.x / s, v.y / s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator / (Y s, const eve::math::TVec3<T> &v) { return eve::math::TVec3<T>(v.x / s, v.y / s, v.z / s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec3<T> operator / (const eve::math::TVec3<T> &v, Y s) { return eve::math::TVec3<T>(v.x / s, v.y / s, v.z / s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator / (Y s, const eve::math::TVec4<T> &v) { return eve::math::TVec4<T>(v.x / s, v.y / s, v.z / s, v.w / s); }
template<typename T, typename Y> EVE_FORCE_INLINE eve::math::TVec4<T> operator / (const eve::math::TVec4<T> &v, Y s) { return eve::math::TVec4<T>(v.x / s, v.y / s, v.z / s, v.w / s); }


//=================================================================================================
template <typename T> EVE_FORCE_INLINE T dot(const eve::math::TVec2<T> & a, const eve::math::TVec2<T> & b) { return a.dot(b); }
template <typename T> EVE_FORCE_INLINE T dot(const eve::math::TVec3<T> & a, const eve::math::TVec3<T> & b) { return a.dot(b); }
template <typename T> EVE_FORCE_INLINE T dot(const eve::math::TVec4<T> & a, const eve::math::TVec4<T> & b) { return a.dot(b); }


//=================================================================================================
template <typename T> EVE_FORCE_INLINE eve::math::TVec3<T> cross(const eve::math::TVec3<T> & a, const eve::math::TVec3<T> & b) { return a.cross(b); }
template <typename T> EVE_FORCE_INLINE eve::math::TVec4<T> cross(const eve::math::TVec4<T> & a, const eve::math::TVec4<T> & b) { return a.cross(b); }


//=================================================================================================
template <typename T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec2<T> & a) { return std::isnan(a.x) || std::isnan(a.y); }
template <typename T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec3<T> & a) { return std::isnan(a.x) || std::isnan(a.y) || std::isnan(a.z); }
template <typename T> EVE_FORCE_INLINE bool isNaN(const eve::math::TVec4<T> & a) { return std::isnan(a.x) || std::isnan(a.y) || std::isnan(a.z) || std::isnan(a.w); }


#endif // __TVECTOR_H__
