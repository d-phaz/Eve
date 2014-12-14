
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
#ifndef __EVE_MATH_CORE_SIMD_H__
#define __EVE_MATH_CORE_SIMD_H__

#ifndef __EVE_MATH_CORE_TYPES_H__
#include "eve/math/core/Types.h"
#endif

namespace eve
{
	namespace __math_internal
	{
		//Matrix transpose, assumes memory is already allocated
		EVE_FORCE_INLINE void transpose(simd_float4_t* input, simd_float4_t* output)
		{
			__m128 t1,t2,t3,t4;

			t1 = _mm_shuffle_ps(input[0],input[1],_MM_SHUFFLE(1,0,1,0));
			t2 =_mm_shuffle_ps(input[0],input[1],_MM_SHUFFLE(3,2,3,2));
			t3 = _mm_shuffle_ps(input[2],input[3],_MM_SHUFFLE(1,0,1,0));
			t4 = _mm_shuffle_ps(input[2],input[3],_MM_SHUFFLE(3,2,3,2));
		
			output[0] = _mm_shuffle_ps(t1,t3,_MM_SHUFFLE(2,0,2,0));
			output[1] =_mm_shuffle_ps(t1,t3,_MM_SHUFFLE(3,1,3,1));
			output[2] = _mm_shuffle_ps(t2,t4,_MM_SHUFFLE(2,0,2,0));
			output[3] = _mm_shuffle_ps(t2,t4,_MM_SHUFFLE(3,1,3,1));
		}

		//In place transpose
		EVE_FORCE_INLINE void transposeInPlace(simd_float4_t* data)
		{
			__m128 t1,t2,t3,t4;

			t1 = _mm_shuffle_ps(data[0],data[1],_MM_SHUFFLE(1,0,1,0));
			t2 =_mm_shuffle_ps(data[0],data[1],_MM_SHUFFLE(3,2,3,2));
			t3 = _mm_shuffle_ps(data[2],data[3],_MM_SHUFFLE(1,0,1,0));
			t4 = _mm_shuffle_ps(data[2],data[3],_MM_SHUFFLE(3,2,3,2));
		
			data[0] = _mm_shuffle_ps(t1,t3,_MM_SHUFFLE(2,0,2,0));
			data[1] =_mm_shuffle_ps(t1,t3,_MM_SHUFFLE(3,1,3,1));
			data[2] = _mm_shuffle_ps(t2,t4,_MM_SHUFFLE(2,0,2,0));
			data[3] = _mm_shuffle_ps(t2,t4,_MM_SHUFFLE(3,1,3,1));
		}

		//multiply two transforms
		EVE_FORCE_INLINE void multiply(simd_float4_t* left, simd_float4_t* right, simd_float4_t* result)
		{
			__m128 r0 = left[0];
			__m128 r1 = left[1];
			__m128 r2 = left[2];
			__m128 r3 = left[3];

			__m128 mr0 = right[0];
			__m128 mr1 = right[1];
			__m128 mr2 = right[2];
			__m128 mr3 = right[3];

			__m128 t0,t1,t2,t3;	
			__m128 c0,c1,c2,c3;

			//Row 1		
			c0 = _mm_shuffle_ps(mr0,mr0,_MM_SHUFFLE(0,0,0,0));
			c1 = _mm_shuffle_ps(mr0,mr0,_MM_SHUFFLE(1,1,1,1));
			c2 = _mm_shuffle_ps(mr0,mr0,_MM_SHUFFLE(2,2,2,2));
			c3 = _mm_shuffle_ps(mr0,mr0,_MM_SHUFFLE(3,3,3,3));

			t0 = _mm_mul_ps(r0,c0);
			t1 = _mm_mul_ps(r1,c1);
			t2 = _mm_mul_ps(r2,c2);
			t3 = _mm_mul_ps(r3,c3);

			t0 = _mm_add_ps(t0,t1);
			t2 = _mm_add_ps(t2,t3);

			t0 = _mm_add_ps(t0,t2);

			result[0] = t0;

			//Row 2
			c0 = _mm_shuffle_ps(mr1,mr1,_MM_SHUFFLE(0,0,0,0));
			c1 = _mm_shuffle_ps(mr1,mr1,_MM_SHUFFLE(1,1,1,1));
			c2 = _mm_shuffle_ps(mr1,mr1,_MM_SHUFFLE(2,2,2,2));
			c3 = _mm_shuffle_ps(mr1,mr1,_MM_SHUFFLE(3,3,3,3));

			t0 = _mm_mul_ps(r0,c0);
			t1 = _mm_mul_ps(r1,c1);
			t2 = _mm_mul_ps(r2,c2);
			t3 = _mm_mul_ps(r3,c3);

			t0 = _mm_add_ps(t0,t1);
			t2 = _mm_add_ps(t2,t3);

			t0 = _mm_add_ps(t0,t2);

			result[1] = t0;

			//Row 3
			c0 = _mm_shuffle_ps(mr2,mr2,_MM_SHUFFLE(0,0,0,0));
			c1 = _mm_shuffle_ps(mr2,mr2,_MM_SHUFFLE(1,1,1,1));
			c2 = _mm_shuffle_ps(mr2,mr2,_MM_SHUFFLE(2,2,2,2));
			c3 = _mm_shuffle_ps(mr2,mr2,_MM_SHUFFLE(3,3,3,3));

			t0 = _mm_mul_ps(r0,c0);
			t1 = _mm_mul_ps(r1,c1);
			t2 = _mm_mul_ps(r2,c2);
			t3 = _mm_mul_ps(r3,c3);

			t0 = _mm_add_ps(t0,t1);
			t2 = _mm_add_ps(t2,t3);

			t0 = _mm_add_ps(t0,t2);

			result[2] = t0;

			//Row 4
			c0 = _mm_shuffle_ps(mr3,mr3,_MM_SHUFFLE(0,0,0,0));
			c1 = _mm_shuffle_ps(mr3,mr3,_MM_SHUFFLE(1,1,1,1));
			c2 = _mm_shuffle_ps(mr3,mr3,_MM_SHUFFLE(2,2,2,2));
			c3 = _mm_shuffle_ps(mr3,mr3,_MM_SHUFFLE(3,3,3,3));

			t0 = _mm_mul_ps(r0,c0);
			t1 = _mm_mul_ps(r1,c1);
			t2 = _mm_mul_ps(r2,c2);
			t3 = _mm_mul_ps(r3,c3);

			t0 = _mm_add_ps(t0,t1);
			t2 = _mm_add_ps(t2,t3);

			t0 = _mm_add_ps(t0,t2);

			result[3] = t0;
		}

	} // namespace __math_internal

} // namespace eve

#endif // __EVE_MATH_CORE_SIMD_H__
