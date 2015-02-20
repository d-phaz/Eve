
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
#ifndef __EVE_MATH_CORE_TQUATERNION_H__
#define __EVE_MATH_CORE_TQUATERNION_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif


namespace eve
{
	namespace math
	{

		/**
		* \class eve::math::TQuaternion
		*
		* \brief Template quaternion.
		*/
		template<typename T>
		class TQuaternion
		{

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		public:
			eve::math::TVec3<T>		v; // axisOfRotation.normalized() * sin( angleOfRotation / 2 )
			T						w; // cos( angleOfRotation / 2 )


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		public:
			TQuaternion(void) : w(1), v(0, 0, 0){} // default constructor is identity quat
			template<typename FromT>
			TQuaternion(const TQuaternion<FromT>& q) : w(static_cast<T>(q.w)), v(q.v) {}

			TQuaternion(T aW, T x, T y, T z) : w(aW), v(x, y, z) {}
			// construct from axis-angle
			TQuaternion(const eve::math::TVec3<T> &axis, T radians) { set(axis, radians); }
			TQuaternion(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to) { set(from, to); }
			// create from Euler angles in radians expressed in ZYX rotation order
			TQuaternion(T xRotation, T yRotation, T zRotation) { set(xRotation, yRotation, zRotation); }
			TQuaternion(const eve::math::TMatrix33<T> &m) { set(m); }
			TQuaternion(const eve::math::TMatrix44<T> &m) { set(m); }

			// get axis-angle representation's axis
			EVE_FORCE_INLINE eve::math::TVec3<T> getAxis(void) const
			{
				T cos_angle = w;
				T invLen = static_cast<T>(1.0) / eve::math::sqrt(static_cast<T>(1.0) - cos_angle * cos_angle);

				return v * invLen;
			}

			// get axis-angle representation's angle in radians
			EVE_FORCE_INLINE T getAngle(void) const
			{
				T cos_angle = w;
				return eve::math::acos(cos_angle) * 2;
			}

			EVE_FORCE_INLINE T getPitch(void) const
			{
				return eve::math::atan2(w * w - v.x * v.x - v.y * v.y + v.z * v.z, static_cast<T>(2) * (v.y * v.z + w * v.x));
			}

			EVE_FORCE_INLINE T getYaw(void) const
			{
				return eve::math::sin(static_cast<T>(-2) * (v.x * v.z - w * v.y));
			}

			EVE_FORCE_INLINE T getRoll(void) const
			{
				return eve::math::atan2(w * w + v.x * v.x - v.y * v.y - v.z * v.z, static_cast<T>(2) * (v.x * v.y + w * v.z));
			}

			EVE_FORCE_INLINE eve::math::TVec3<T> toVec3(void)
			{
				return eve::math::TVec3<T>(getPitch(), getYaw(), getRoll());
			}

			EVE_FORCE_INLINE T dot(const eve::math::TQuaternion<T> &quat) const
			{
				return w * quat.w + v.dot(quat.v);
			}

			EVE_FORCE_INLINE T length(void) const
			{
				return eve::math::sqrt(w*w + v.lengthSquared());
			}

			EVE_FORCE_INLINE T lengthSquared(void) const
			{
				return w * w + v.lengthSquared();
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> inverse(void) const
			{
				T norm = w * w + v.x * v.x + v.y * v.y + v.z * v.z;
				// if we're the zero quaternion, just return identity
				/*if( ! ( eve::math::abs( norm ) < EPSILON_VALUE ) ) {
				return identity();
				}*/

				T normRecip = static_cast<T>(1.0) / norm;
				return eve::math::TQuaternion<T>(normRecip * w, -normRecip * v.x, -normRecip * v.y, -normRecip * v.z);
			}

			EVE_FORCE_INLINE void normalize(void)
			{
				if (T len = length()) {
					w /= len;
					v /= len;
				}
				else {
					w = static_cast<T>(1.0);
					v = eve::math::TVec3<T>(0, 0, 0);
				}
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> normalized(void) const
			{
				eve::math::TQuaternion<T> result = *this;

				if (T len = length()) {
					result.w /= len;
					result.v /= len;
				}
				else {
					result.w = static_cast<T>(1.0);
					result.v = eve::math::TVec3<T>(0, 0, 0);
				}

				return result;
			}

			// For unit quaternion, from Advanced Animation and 
			// Rendering Techniques by Watt and Watt, Page 366:
			EVE_FORCE_INLINE eve::math::TQuaternion<T> log(void) const
			{
				T theta = eve::math::acos(eve::math::min(w, static_cast<T>(1.0)));

				if (theta == 0)
					return eve::math::TQuaternion<T>(v, 0);

				T sintheta = eve::math::sin(theta);

				T k;
				if (eve::math::abs(sintheta) < 1 && eve::math::abs(theta) >= 3.402823466e+38F * eve::math::abs(sintheta))
					k = static_cast<T>(1);
				else
					k = theta / sintheta;

				return eve::math::TQuaternion<T>(static_cast<T>(0), v.x * k, v.y * k, v.z * k);
			}

			// For pure quaternion (zero scalar part):
			// from Advanced Animation and Rendering
			// Techniques by Watt and Watt, Page 366:
			EVE_FORCE_INLINE eve::math::TQuaternion<T> exp(void) const
			{
				T theta = v.length();
				T sintheta = eve::math::sin(theta);

				T k;
				if (eve::math::abs(theta) < 1 && eve::math::abs(sintheta) >= 3.402823466e+38F * eve::math::abs(theta))
					k = 1;
				else
					k = sintheta / theta;

				T costheta = eve::math::cos(theta);

				return eve::math::TQuaternion<T>(costheta, v.x * k, v.y * k, v.z * k);
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> inverted(void) const
			{
				T qdot = this->dot(*this);
				return eve::math::TQuaternion(-v / qdot, w / qdot);
			}

			EVE_FORCE_INLINE void invert(void)
			{
				T qdot = this->dot(*this);
				set(-v / qdot, w / qdot);
			}

			EVE_FORCE_INLINE void set(T aW, T x, T y, T z)
			{
				w = aW;
				v = eve::math::TVec3<T>(x, y, z);
			}

			EVE_FORCE_INLINE void set(const eve::math::TVec3<T> &from, const eve::math::TVec3<T> &to)
			{
				eve::math::TVec3<T> axis = from.cross(to);

				set(from.dot(to), axis.x, axis.y, axis.z);
				normalize();

				w += static_cast<T>(1.0);

				if (w <= static_cast<T>(EVE_MATH_EPSILON)) 
				{
					if (from.z * from.z > from.x * from.x) 
					{
						set(static_cast<T>(0.0), static_cast<T>(0.0), from.z, -from.y);
					}
					else 
					{
						set(static_cast<T>(0.0), from.y, -from.x, static_cast<T>(0.0));
					}
				}

				normalize();
			}

			EVE_FORCE_INLINE void set(const eve::math::TVec3<T> &axis, T radians)
			{
				w = eve::math::cos(radians / static_cast<T>(2));
				v = axis.normalized() * eve::math::sin(radians / static_cast<T>(2));
			}

			// assumes ZYX rotation order and radians
			EVE_FORCE_INLINE void set(T xRotation, T yRotation, T zRotation)
			{
				zRotation *= static_cast<T>(0.5);
				yRotation *= static_cast<T>(0.5);
				xRotation *= static_cast<T>(0.5);

				// get sines and cosines of half angles
				T Cx = eve::math::cos(xRotation);
				T Sx = eve::math::sin(xRotation);

				T Cy = eve::math::cos(yRotation);
				T Sy = eve::math::sin(yRotation);

				T Cz = eve::math::cos(zRotation);
				T Sz = eve::math::sin(zRotation);

				// multiply it out
				w   = Cx*Cy*Cz - Sx*Sy*Sz;
				v.x = Sx*Cy*Cz + Cx*Sy*Sz;
				v.y = Cx*Sy*Cz - Sx*Cy*Sz;
				v.z = Cx*Cy*Sz + Sx*Sy*Cx;
			}

			EVE_FORCE_INLINE void getAxisAngle(eve::math::TVec3<T> *axis, T *radians) const
			{
				T cos_angle = w;
				*radians = eve::math::acos(cos_angle) * static_cast<T>(2);
				T invLen = static_cast<T>(1.0) / eve::math::sqrt(static_cast<T>(1.0) - cos_angle * cos_angle);

				axis->x = v.x * invLen;
				axis->y = v.y * invLen;
				axis->z = v.z * invLen;
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> lerp(T t, const eve::math::TQuaternion<T> &end) const
			{
				// get cos of "angle" between quaternions
				float cosTheta = dot(end);

				// initialize result
				eve::math::TQuaternion<T> result = end * t;

				// if "angle" between quaternions is less than 90 degrees
				if (cosTheta >= static_cast<T>(EVE_MATH_EPSILON)) 
				{
					// use standard interpolation
					result += *this * (static_cast<T>(1.0) - t);
				}
				else 
				{
					// otherwise, take the shorter path
					result += *this * (t - static_cast<T>(1.0));
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
			EVE_FORCE_INLINE eve::math::TQuaternion<T> slerpShortestUnenforced(T t, const eve::math::TQuaternion<T> &end) const
			{
				eve::math::TQuaternion<T> d = *this - end;
				T lengthD = eve::math::sqrt(this->dot(end));

				eve::math::TQuaternion<T> st = *this + end;
				T lengthS = eve::math::sqrt(st.dot(st));

				T a = 2 * eve::math::atan2(lengthS, lengthD);
				T s = 1 - t;

				eve::math::TQuaternion<T> q(*this * (eve::math::sinx_over_x(s * a) / eve::math::sinx_over_x(a) * s) + end * (eve::math::sinx_over_x(t * a) / eve::math::sinx_over_x(a) * t));

				return q.normalized();
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> slerp(T t, const eve::math::TQuaternion<T> &end) const
			{
				// get cosine of "angle" between quaternions
				T cosTheta = this->dot(end);
				T startInterp, endInterp;

				// if "angle" between quaternions is less than 90 degrees
				if (cosTheta >= static_cast<T>(EVE_MATH_EPSILON)) {
					// if angle is greater than zero
					if ((static_cast<T>(1.0) - cosTheta) > static_cast<T>(EVE_MATH_EPSILON))
					{
						// use standard slerp
						T theta = eve::math::acos(cosTheta);
						T recipSinTheta = static_cast<T>(1.0) / eve::math::sin(theta);

						startInterp = eve::math::sin((static_cast<T>(1.0) - t) * theta) * recipSinTheta;
						endInterp = eve::math::sin(t * theta) * recipSinTheta;
					}
					// angle is close to zero
					else 
					{
						// use linear interpolation
						startInterp = static_cast<T>(1.0) - t;
						endInterp = t;
					}
				}
				// otherwise, take the shorter route
				else 
				{
					// if angle is less than 180 degrees
					if ((static_cast<T>(1.0) + cosTheta) > static_cast<T>(EVE_MATH_EPSILON)) {
						// use slerp w/negation of start quaternion
						T theta = eve::math::acos(-cosTheta);
						T recipSinTheta = static_cast<T>(1.0) / eve::math::sin(theta);

						startInterp = eve::math::sin((t - static_cast<T>(1.0)) * theta) * recipSinTheta;
						endInterp = eve::math::sin(t * theta) * recipSinTheta;
					}
					// angle is close to 180 degrees
					else 
					{
						// use lerp w/negation of start quaternion
						startInterp = t - static_cast<T>(1.0);
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
			EVE_FORCE_INLINE eve::math::TQuaternion<T> squadShortestEnforced(T t, const eve::math::TQuaternion<T> &qa, const eve::math::TQuaternion<T> &qb, const eve::math::TQuaternion<T> &q2) const
			{
				eve::math::TQuaternion<T> r1;
				if (this->dot(q2) >= 0)
					r1 = this->slerpShortestUnenforced(t, q2);
				else
					r1 = this->slerpShortestUnenforced(t, q2.inverted());

				eve::math::TQuaternion<T> r2;
				if (qa.dot(qb) >= 0)
					r2 = qa.slerpShortestUnenforced(t, qb);
				else
					r2 = qa.slerpShortestUnenforced(t, qb.inverted());

				if (r1.dot(r2) >= 0)
					return r1.slerpShortestUnenforced(2 * t * (1 - t), r2);
				else
					return r1.slerpShortestUnenforced(2 * t * (1 - t), r2.inverted());
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T> squad(T t, const eve::math::TQuaternion<T> &qa, const eve::math::TQuaternion<T> &qb, const eve::math::TQuaternion<T> &q2) const
			{
				eve::math::TQuaternion<T> r1 = this->slerp(t, q2);
				eve::math::TQuaternion<T> r2 = qa.slerp(t, qb);
				return r1.slerp(static_cast<T>(2) * t * (static_cast<T>(1) - t), r2);
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
			EVE_FORCE_INLINE eve::math::TQuaternion<T> spline(T t, const eve::math::TQuaternion<T> &q1, const eve::math::TQuaternion<T> &q2, const eve::math::TQuaternion<T> &q3) const
			{
				eve::math::TQuaternion<T> qa = splineIntermediate(*this, q1, q2);
				eve::math::TQuaternion<T> qb = splineIntermediate(q1, q2, q3);
				eve::math::TQuaternion<T> result = q1.squadShortestEnforced(t, qa, qb, q2);

				return result;
			}

			EVE_FORCE_INLINE void set(const eve::math::TMatrix33<T> &m)
			{
				//T trace = m.m[0] + m.m[4] + m.m[8];
				T trace = m.trace();
				if (trace > static_cast<T>(0.0))
				{
					T s = eve::math::sqrt(trace + static_cast<T>(1.0));
					w = s * static_cast<T>(0.5);
					T recip = static_cast<T>(0.5) / s;
					v.x = (m.at(2, 1) - m.at(1, 2)) * recip;
					v.y = (m.at(0, 2) - m.at(2, 0)) * recip;
					v.z = (m.at(1, 0) - m.at(0, 1)) * recip;
				}
				else
				{
					uint32_t i = 0;
					if (m.at(1, 1) > m.at(0, 0))
						i = 1;
					if (m.at(2, 2) > m.at(i, i))
						i = 2;
					uint32_t j = (i + 1) % 3;
					uint32_t k = (j + 1) % 3;
					T s = eve::math::sqrt(m.at(i, i) - m.at(j, j) - m.at(k, k) + static_cast<T>(1.0));
					(*this)[i] = static_cast<T>(0.5) * s;
					T recip = static_cast<T>(0.5) / s;
					w = (m.at(k, j) - m.at(j, k)) * recip;
					(*this)[j] = (m.at(j, i) + m.at(i, j)) * recip;
					(*this)[k] = (m.at(k, i) + m.at(i, k)) * recip;
				}
			}

			EVE_FORCE_INLINE void set(const eve::math::TMatrix44<T> &m)
			{
				//T trace = m.m[0] + m.m[5] + m.m[10];
				T trace = m.trace();
				if (trace > static_cast<T>(0.0))
				{
					T s = eve::math::sqrt(trace + static_cast<T>(1.0));
					w = s * static_cast<T>(0.5);
					T recip = static_cast<T>(0.5) / s;
					v.x = (m.at(2, 1) - m.at(1, 2)) * recip;
					v.y = (m.at(0, 2) - m.at(2, 0)) * recip;
					v.z = (m.at(1, 0) - m.at(0, 1)) * recip;
				}
				else
				{
					uint32_t i = 0;
					if (m.at(1, 1) > m.at(0, 0))
						i = 1;
					if (m.at(2, 2) > m.at(i, i))
						i = 2;
					uint32_t j = (i + 1) % 3;
					uint32_t k = (j + 1) % 3;
					T s = eve::math::sqrt(m.at(i, i) - m.at(j, j) - m.at(k, k) + static_cast<T>(1.0));
					(*this)[i] = static_cast<T>(0.5) * s;
					T recip = static_cast<T>(0.5) / s;
					w = (m.at(k, j) - m.at(j, k)) * recip;
					(*this)[j] = (m.at(j, i) + m.at(i, j)) * recip;
					(*this)[k] = (m.at(k, i) + m.at(i, k)) * recip;
				}
			}


			/** Performs a spherical interpolation between two quaternions and writes the result into the third.
			* @param pOut Target object to received the interpolated rotation.
			* @param pStart Start rotation of the interpolation at factor == 0.
			* @param pEnd End rotation, factor == 1.
			* @param pFactor Interpolation factor between 0 and 1. Values outside of this range yield undefined results.
			*/
			static void Interpolate(eve::math::TQuaternion<T>& pOut, const eve::math::TQuaternion<T>& pStart, const eve::math::TQuaternion<T>& pEnd, T pFactor);


			// Operators
			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator=(const eve::math::TQuaternion<T> &rhs)
			{
				v = rhs.v;
				w = rhs.w;
				return *this;
			}

			template<typename FromT>
			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator=(const eve::math::TQuaternion<FromT> &rhs)
			{
				v = rhs.v;
				w = static_cast<T>(rhs.w);
				return *this;
			}

			EVE_FORCE_INLINE const eve::math::TQuaternion<T> operator+(const eve::math::TQuaternion<T> &rhs) const
			{
				const eve::math::TQuaternion<T>& lhs = *this;
				return eve::math::TQuaternion<T>(lhs.w + rhs.w, lhs.v.x + rhs.v.x, lhs.v.y + rhs.v.y, lhs.v.z + rhs.v.z);
			}

			// post-multiply operator, similar to matrices, but different from Shoemake
			// Concatenates 'rhs' onto 'this'
			EVE_FORCE_INLINE const eve::math::TQuaternion<T> operator*(const eve::math::TQuaternion<T> &rhs) const
			{
				return eve::math::TQuaternion<T>(rhs.w*w - rhs.v.x*v.x - rhs.v.y*v.y - rhs.v.z*v.z,
												 rhs.w*v.x + rhs.v.x*w + rhs.v.y*v.z - rhs.v.z*v.y,
												 rhs.w*v.y + rhs.v.y*w + rhs.v.z*v.x - rhs.v.x*v.z,
												 rhs.w*v.z + rhs.v.z*w + rhs.v.x*v.y - rhs.v.y*v.x);
			}

			EVE_FORCE_INLINE const eve::math::TQuaternion<T> operator*(T rhs) const
			{
				return eve::math::TQuaternion<T>(w * rhs, v.x * rhs, v.y * rhs, v.z * rhs);
			}

			// transform a vector by the quaternion
			EVE_FORCE_INLINE const eve::math::TVec3<T> operator*(const eve::math::TVec3<T> &vec) const
			{
				T vMult		= static_cast<T>(2) * (v.x * vec.x + v.y * vec.y + v.z * vec.z);
				T crossMult = static_cast<T>(2) * w;
				T pMult		= crossMult * w - static_cast<T>(1);

				return eve::math::TVec3<T>(pMult * vec.x + vMult * v.x + crossMult * (v.y * vec.z - v.z * vec.y),
										   pMult * vec.y + vMult * v.y + crossMult * (v.z * vec.x - v.x * vec.z),
										   pMult * vec.z + vMult * v.z + crossMult * (v.x * vec.y - v.y * vec.x));
			}

			EVE_FORCE_INLINE const eve::math::TQuaternion<T> operator-(const eve::math::TQuaternion<T> &rhs) const
			{
				const eve::math::TQuaternion<T>& lhs = *this;
				return eve::math::TQuaternion<T>(lhs.w - rhs.w, lhs.v.x - rhs.v.x, lhs.v.y - rhs.v.y, lhs.v.z - rhs.v.z);
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator+=(const eve::math::TQuaternion<T> &rhs)
			{
				w += rhs.w;
				v += rhs.v;
				return *this;
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator-=(const eve::math::TQuaternion<T>& rhs)
			{
				w -= rhs.w;
				v -= rhs.v;
				return *this;
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator*=(const eve::math::TQuaternion<T> &rhs)
			{
				eve::math::TQuaternion q = (*this) * rhs;
				v = q.v;
				w = q.w;
				return *this;
			}

			EVE_FORCE_INLINE eve::math::TQuaternion<T>& operator*=(T rhs)
			{
				w *= rhs;
				v *= rhs;
				return *this;
			}

			bool operator==(const eve::math::TQuaternion<T> &rhs) const
			{
				const eve::math::TQuaternion<T>& lhs = *this;
				return (eve::math::abs(lhs.w - rhs.w) < static_cast<T>(EVE_MATH_EPSILON)) && lhs.v == rhs.v;
			}

			bool operator!=(const eve::math::TQuaternion<T> &rhs) const
			{
				return !(*this == rhs);
			}

			inline T& operator[](uint32_t i) { return (&v.x)[i]; }
			inline const T& operator[](uint32_t i) const { return (&v.x)[i]; }

			EVE_FORCE_INLINE static eve::math::TQuaternion<T> identity(void)
			{
				return eve::math::TQuaternion<T>();
			}

			EVE_FORCE_INLINE eve::math::TMatrix33<T> toMatrix33(void) const
			{
				eve::math::TMatrix33<T> mV;
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

				mV[0] = static_cast<T>(1) - (yy + zz);
				mV[3] = xy - wz;
				mV[6] = xz + wy;

				mV[1] = xy + wz;
				mV[4] = static_cast<T>(1) - (xx + zz);
				mV[7] = yz - wx;

				mV[2] = xz - wy;
				mV[5] = yz + wx;
				mV[8] = static_cast<T>(1) - (xx + yy);

				return mV;
			}

			EVE_FORCE_INLINE eve::math::TMatrix44<T> toMatrix44(void) const
			{
				eve::math::TMatrix44<T> mV;
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

				mV[0] = static_cast<T>(1) - (yy + zz);
				mV[4] = xy - wz;
				mV[8] = xz + wy;
				mV[12] = static_cast<T>(0);

				mV[1] = xy + wz;
				mV[5] = static_cast<T>(1) - (xx + zz);
				mV[9] = yz - wx;
				mV[13] = static_cast<T>(0);

				mV[2] = xz - wy;
				mV[6] = yz + wx;
				mV[10] = static_cast<T>(1) - (xx + yy);
				mV[14] = static_cast<T>(0);

				mV[3] = static_cast<T>(0);
				mV[7] = static_cast<T>(0);
				mV[11] = static_cast<T>(0);
				mV[15] = T(1);

				return mV;
			}

			operator eve::math::TMatrix44<T>() const { return toMatrix44(); }

		private:
			// From advanced Animation and Rendering Techniques by Watt and Watt, Page 366:
			// computing the inner quadrangle points (qa and qb) to guarantee tangent continuity.
			EVE_FORCE_INLINE static eve::math::TQuaternion<T> splineIntermediate(const eve::math::TQuaternion<T> &q0, const eve::math::TQuaternion<T> &q1, const eve::math::TQuaternion<T> &q2)
			{
				eve::math::TQuaternion<T> q1inv = q1.inverted();
				eve::math::TQuaternion<T> c1 = q1inv * q2;
				eve::math::TQuaternion<T> c2 = q1inv * q0;
				eve::math::TQuaternion<T> c3 = (c2.log() + c1.log()) * static_cast<T>(-0.25);
				eve::math::TQuaternion<T> qa = q1 * c3.exp();
				return qa.normalized();
			}


		public:
			T & x(void);
			T & y(void);
			T & z(void);

			void setX(float p_x);
			void setY(float p_y);
			void setZ(float p_z);
			void setW(float p_w);
		};

	} // namespace math

} // namespace eve


template<typename T>
EVE_FORCE_INLINE T & eve::math::TQuaternion<T>::x(void)				{ return v.x;	}

template<typename T>
EVE_FORCE_INLINE T & eve::math::TQuaternion<T>::y(void)				{ return v.y;	}

template<typename T>
EVE_FORCE_INLINE T & eve::math::TQuaternion<T>::z(void)				{ return v.z;	}

template<typename T>
EVE_FORCE_INLINE void eve::math::TQuaternion<T>::setX(float p_x)	{ v.x = p_x;	}

template<typename T>
EVE_FORCE_INLINE void eve::math::TQuaternion<T>::setY(float p_y)	{ v.y = p_y;	}

template<typename T>
EVE_FORCE_INLINE void eve::math::TQuaternion<T>::setZ(float p_z)	{ v.z = p_z;	}

template<typename T>
EVE_FORCE_INLINE void eve::math::TQuaternion<T>::setW(float p_w)	{ w = p_w;		}



// ---------------------------------------------------------------------------
// Performs a spherical interpolation between two quaternions 
// Implementation adopted from the gmtl project. All others I found on the net fail in some cases.
// Congrats, gmtl!
template<typename T>
EVE_FORCE_INLINE void eve::math::TQuaternion<T>::Interpolate(eve::math::TQuaternion<T>& pOut, const eve::math::TQuaternion<T>& pStart, const eve::math::TQuaternion<T>& pEnd, T pFactor)
{
	// calc cosine theta
	T cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

	// adjust signs (if necessary)
	eve::math::TQuaternion<T> end = pEnd;
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
		omega = eve::math::acos( cosom); // extract theta from dot product's cos theta
		sinom = eve::math::sin( omega);
		sclp  = eve::math::sin( (static_cast<T>(1.0) - pFactor) * omega) / sinom;
		sclq  = eve::math::sin( pFactor * omega) / sinom;
	} 
	else
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
EVE_FORCE_INLINE eve::math::TVec3<T> operator*(const eve::math::TVec3<T> & vec, const eve::math::TQuaternion<T> & q)
{
    T vMult		= static_cast<T>(2) * ( q.v.x * vec.x + q.v.y * vec.y + q.v.z * vec.z );
	T crossMult = static_cast<T>(2) * q.w;
	T pMult		= crossMult * q.w - static_cast<T>(1);

	return eve::math::TVec3<T>(pMult * vec.x + vMult * q.v.x + crossMult * (q.v.y * vec.z - q.v.z * vec.y),
							   pMult * vec.y + vMult * q.v.y + crossMult * (q.v.z * vec.x - q.v.x * vec.z),
							   pMult * vec.z + vMult * q.v.z + crossMult * (q.v.x * vec.y - q.v.y * vec.x) );
}

#endif // __EVE_MATH_CORE_TQUATERNION_H__
