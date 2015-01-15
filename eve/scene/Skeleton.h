
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
#ifndef __EVE_SCENE_SKELETON_H__
#define __EVE_SCENE_SKELETON_H__


#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif

#include <assimp/scene.h>


namespace eve
{
	namespace scene
	{

		/** 
		* \class eve::scene::Skeleton
		* \brief Bones rigging skeleton used in mesh animation.
		* \note extends eve::mem::Pointer.
		*/
		class Skeleton
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATAS				//
			//////////////////////////////////////

		protected:
			const aiMesh *			m_pAiMesh;				//<! Specifies Assimp mesh (shared pointer).

			int32_t					m_numBones;				//<! Specifies the number of bones in mesh.
			eve::vec4ui *			m_pBoneIndices;			//<! Specifies bone indices array.
			eve::vec4f *			m_pWeights;				//<! Specifies bones weights array.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Skeleton);
			EVE_PROTECT_DESTRUCTOR(Skeleton);

		public:
			/** \brief Create, init and return new pointer based on ASSIMP aiMesh \a pMesh. */
			static eve::scene::Skeleton * create_ptr(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis);


		protected:
			/** \brief Class constructor. */
			explicit Skeleton(void);


		protected:
			/** \! Allocate and init class members based on ASSIMP aiMesh \a pMesh. */
			bool initFromAssimpMesh(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis);


		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;

		}; // class Skeleton		

	} // namespace scene

} // namespace eve

#endif // __EVE_SCENE_SKELETON_H__
