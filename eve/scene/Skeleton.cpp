
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

// Main header
#include "eve/scene/Skeleton.h"


//=================================================================================================
eve::scene::Skeleton * eve::scene::Skeleton::create_ptr(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis)
{
	EVE_ASSERT(p_pMesh);
	EVE_ASSERT(p_pScene);

	eve::scene::Skeleton * ptr = new eve::scene::Skeleton();
	ptr->init(p_pMesh, p_pScene, p_upAxis);
	return ptr;
}



//=================================================================================================
eve::scene::Skeleton::Skeleton(void)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_pAiMesh(nullptr)

	, m_numBones(0)
	, m_pBoneIndices(nullptr)
	, m_pWeights(nullptr)
{}



//=================================================================================================
bool eve::scene::Skeleton::init(const aiMesh * p_pMesh, const aiScene * p_pScene, eve::Axis p_upAxis)
{
// 	// Grab scene node. 
// 	const aiNode * pRoot = p_pScene->mRootNode;
// 	const aiNode * pNode = pRoot->FindNode(m_name.c_str());
// 
// 	// Test scene node.
// 	bool ret = pNode != NULL;
// 	EVE_ASSERT(ret);

	bool ret = true;

	// Stock mesh pointer.
	m_pAiMesh = p_pMesh;

	// Test mesh bones exist.
	if (!m_pAiMesh->HasBones())
	{
		EVE_LOG_INFO("Loaded mesh contains no skeleton animation.");
		ret = false;
	}
	else
	{
		uint32_t numVertices = m_pAiMesh->mNumVertices;
		int32_t numBones	 = m_pAiMesh->mNumBones;
		m_numBones			 = numBones;

		// Allocate arrays memory.
		m_pBoneIndices = (eve::vec4ui*)eve::mem::malloc(sizeof(eve::vec4ui) * numVertices);
		m_pWeights	   = (eve::vec4f*)eve::mem::malloc(sizeof(eve::vec4f) * numVertices);

		// Read bone indices and weights for bone animation.
		std::vector<aiVertexWeight> * vTempWeightsPerVertex = new std::vector<aiVertexWeight>[numVertices];

		const aiBone * Bone = nullptr;
		for (int32_t j = 0; j < numBones; j++)
		{
			Bone = m_pAiMesh->mBones[j];

			for (uint32_t b = 0; b < Bone->mNumWeights; b++) {
				vTempWeightsPerVertex[Bone->mWeights[b].mVertexId].push_back(aiVertexWeight(j, Bone->mWeights[b].mWeight));
			}
		}

		for (uint32_t j = 0; j<numVertices; j++)
		{
			m_pBoneIndices[j] = eve::vec4ui::zero();
			m_pWeights[j]	  = eve::vec4f::zero();

			if (vTempWeightsPerVertex[j].size() > 4) {
				EVE_LOG_ERROR("Mesh has invalid bone weights, no animation loaded.");
			}
			for (uint32_t k = 0; k < vTempWeightsPerVertex[j].size(); k++)
			{
				m_pBoneIndices[j][k] = vTempWeightsPerVertex[j][k].mVertexId;
				m_pWeights[j][k]	 = vTempWeightsPerVertex[j][k].mWeight;
			}
		}

		if (vTempWeightsPerVertex)
		{
			delete[] vTempWeightsPerVertex;
		}

		this->init();
	}

	return ret;
}



//=================================================================================================
void eve::scene::Skeleton::init(void)
{
	// Nothing to do for now.
}

//=================================================================================================
void eve::scene::Skeleton::release(void)
{
	// Do not delete -> shared pointer.
	m_pAiMesh = nullptr;

	EVE_RELEASE_PTR_C_SAFE(m_pBoneIndices);
	EVE_RELEASE_PTR_C_SAFE(m_pWeights);
}
