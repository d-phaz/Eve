
#pragma once
#ifndef __MATRIX_DECOMPOSE_H__
#define __MATRIX_DECOMPOSE_H__

#ifndef __NATIVE_SYSTEM_H__
#include "Native_System.h"
#endif

#ifndef __TMATH_H__
#include "math/TMath.h"
#endif

#ifndef __TMATRIX_44_H__
#include "math/TMatrix44.h"
#endif

#ifndef __TVECTOR_H__
#include "math/TVector.h"
#endif

#ifndef __TQUATERNION_H__
#include "math/TQuaternion.h"
#endif

namespace matrix_algo
{
	// Decompose matrix to extract translation, rotation and scale
	void decompose_matrix44( const Matrix44f & mat, Vec3f & t, Quatf & r, Vec3f & s, Quatf & so );
	void decompose_matrix44( const Matrix44f & mat, Vec3f & t, Quatf & r );


	// Extract Camera view look at properties (eye, target, world up)
	void get_look_at( const Matrix44f & mat, Vec3f & eye, Vec3f & center, Vec3f & up, float lookDistance=1.0f );
	// Extract camera eye position from model view matrix (that will work with stereo camera as well).
	void get_eye_point( const Matrix44f & mat, Vec3f & eye );

} // namespace algo

#endif // __MATRIX_DECOMPOSE_H__
