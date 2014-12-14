
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
#ifndef __EVE_MATH_CORE_TMATRIX_H__
#define __EVE_MATH_CORE_TMATRIX_H__

#ifndef __EVE_MATH_CORE_TMATRIX_22_H__
#include "eve/math/core/TMatrix22.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_33_H__
#include "eve/math/core/TMatrix33.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_44_H__
#include "eve/math/core/TMatrix44.h"
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Transport Frames
//
//  These methods compute a set of reference frames, defined by their
//  transformation matrix, along a curve. It is designed so that the 
//  array of points and the array of matrices used to fetch these routines 
//  don't need to be ordered as the curve.
//  
//  A typical usage would be :
//
//      m[0] = Imath::firstFrame( p[0], p[1], p[2] );
//      for( int i = 1; i < n - 1; i++ )
//      {
//          m[i] = Imath::nextFrame( m[i-1], p[i-1], p[i], t[i-1], t[i] );
//      }
//      m[n-1] = Imath::lastFrame( m[n-2], p[n-2], p[n-1] );
//
//  See Graphics Gems I for the underlying algorithm.
//  These are also called Parallel Transport Frames
//    see Game Programming Gems 2, Section 2.5

// TVec3
// template< typename T >
// TMatrix44<T> firstFrame( 
// 	const TVec3<T> &firstPoint,
// 	const TVec3<T> &secondPoint, 
// 	const TVec3<T> &thirdPoint
// );
// 
// template< typename T >
// TMatrix44<T> nextFrame( 
// 	const TMatrix44<T> &prevMatrix, 
// 	const TVec3<T> &prevPoint,
// 	const TVec3<T> &curPoint,
// 	TVec3<T> &prevTangent, 
// 	TVec3<T> &curTangent 
// );
// 			
// template< typename T >
// TMatrix44<T> lastFrame( 
// 	const TMatrix44<T> &prevMatrix, 
// 	const TVec3<T> &prevPoint, 
// 	const TVec3<T> &lastPoint 
// );
// 
// // TVec4
// template< typename T >
// TMatrix44<T> firstFrame( 
// 	const TVec4<T> &firstPoint,
// 	const TVec4<T> &secondPoint, 
// 	const TVec4<T> &thirdPoint
// )
// {
// 	return firstFrame( firstPoint.xyz(), secondPoint.xyz(), thirdPoint.xyz() );
// }
// 
// template< typename T >
// TMatrix44<T> nextFrame( 
// 	const TMatrix44<T> &prevMatrix, 
// 	const TVec4<T> &prevPoint,
// 	const TVec4<T> &curPoint,
// 	TVec4<T> &prevTangent, 
// 	TVec4<T> &curTangent 
// )
// {
// 	TVec3<T> aPrevTangent = prevTangent.xyz();
// 	TVec3<T> aCurTangent = curTangent.xyz();
// 	return nextFrame( prevMatrix, prevPoint.xyz(), curPoint.xyz(), aPrevTangent, aCurTangent );
// }
// 			
// template< typename T >
// TMatrix44<T> lastFrame( 
// 	const TMatrix44<T> &prevMatrix, 
// 	const TVec4<T> &prevPoint, 
// 	const TVec4<T> &lastPoint 
// )
// {
// 	return lastFrame( prevMatrix, prevPoint.xyz(), lastPoint.xyz() );
// }

#endif // __EVE_MATH_CORE_TMATRIX_H__
