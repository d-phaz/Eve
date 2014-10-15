
#pragma once
#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#ifndef __NATIVE_SYSTEM_H__
#include "Native_System.h"
#endif


#ifndef __TMATH_H__
#include "math/TMath.h"
#endif

#ifndef __TMATRIX_22_H__
#include "math/TMatrix22.h"
#endif

#ifndef __TMATRIX_33_H__
#include "math/TMatrix33.h"
#endif

#ifndef __TMATRIX_44_H__
#include "math/TMatrix44.h"
#endif

#ifndef __TMATRIX_AFFINE_22_H__
#include "math/TMatrixAffine2.h"
#endif

#ifndef __TMATRIX_ALGO_H__
#include "math/TMatrixAlgo.h"
#endif

#ifndef __TQUATERNION_H__
#include "math/TQuaternion.h"
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
template< typename T >
TMatrix44<T> firstFrame( 
	const TVec3<T> &firstPoint,
	const TVec3<T> &secondPoint, 
	const TVec3<T> &thirdPoint
);

template< typename T >
TMatrix44<T> nextFrame( 
	const TMatrix44<T> &prevMatrix, 
	const TVec3<T> &prevPoint,
	const TVec3<T> &curPoint,
	TVec3<T> &prevTangent, 
	TVec3<T> &curTangent 
);
			
template< typename T >
TMatrix44<T> lastFrame( 
	const TMatrix44<T> &prevMatrix, 
	const TVec3<T> &prevPoint, 
	const TVec3<T> &lastPoint 
);

// TVec4
template< typename T >
TMatrix44<T> firstFrame( 
	const TVec4<T> &firstPoint,
	const TVec4<T> &secondPoint, 
	const TVec4<T> &thirdPoint
)
{
	return firstFrame( firstPoint.xyz(), secondPoint.xyz(), thirdPoint.xyz() );
}

template< typename T >
TMatrix44<T> nextFrame( 
	const TMatrix44<T> &prevMatrix, 
	const TVec4<T> &prevPoint,
	const TVec4<T> &curPoint,
	TVec4<T> &prevTangent, 
	TVec4<T> &curTangent 
)
{
	TVec3<T> aPrevTangent = prevTangent.xyz();
	TVec3<T> aCurTangent = curTangent.xyz();
	return nextFrame( prevMatrix, prevPoint.xyz(), curPoint.xyz(), aPrevTangent, aCurTangent );
}
			
template< typename T >
TMatrix44<T> lastFrame( 
	const TMatrix44<T> &prevMatrix, 
	const TVec4<T> &prevPoint, 
	const TVec4<T> &lastPoint 
)
{
	return lastFrame( prevMatrix, prevPoint.xyz(), lastPoint.xyz() );
}

#endif // __TMATRIX_H__
