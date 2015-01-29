
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
#include "eve/ogl/core/Uniform.h"


//=================================================================================================
eve::ogl::FormatUniform::FormatUniform(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, blockSize(0)
	, dynamic(false)
{}

//=================================================================================================
eve::ogl::FormatUniform::~FormatUniform(void)
{}

//=================================================================================================
eve::ogl::FormatUniform::FormatUniform(const eve::ogl::FormatUniform & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, blockSize(p_other.blockSize)
	, dynamic(p_other.dynamic)
{}

//=================================================================================================
const eve::ogl::FormatUniform & eve::ogl::FormatUniform::operator = (const eve::ogl::FormatUniform & p_other)
{
	if (this != &p_other)
	{
		this->blockSize = p_other.blockSize;
		this->dynamic	= p_other.dynamic;
	}
	return *this;
}



//=================================================================================================
int32_t	eve::ogl::Uniform::m_max_vertex_uniform_blocks			= 0;
int32_t	eve::ogl::Uniform::m_max_control_uniform_blocks			= 0;
int32_t	eve::ogl::Uniform::m_max_evaluation_uniform_blocks		= 0;
int32_t	eve::ogl::Uniform::m_max_geometry_uniform_blocks		= 0;
int32_t	eve::ogl::Uniform::m_max_fragment_uniform_blocks		= 0;

int32_t eve::ogl::Uniform::m_max_uniform_buffer_binding			= 0;
int32_t eve::ogl::Uniform::m_max_uniform_block_size				= 0;

int32_t eve::ogl::Uniform::m_uniform_buffer_offset_alignment	= 0;

//=================================================================================================
eve::ogl::Uniform::Uniform(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_blockSize(0)
	, m_usage(0)
	, m_bDynamic(false)
	, m_pData(nullptr)
	, m_pOglData(nullptr)
{}



//=================================================================================================
void eve::ogl::Uniform::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatUniform * format = reinterpret_cast<eve::ogl::FormatUniform*>(p_format);

	m_blockSize = format->blockSize;
	m_bDynamic	= format->dynamic;

	EVE_ASSERT(m_blockSize);
}



//=================================================================================================
void eve::ogl::Uniform::init(void)
{
	m_pData = (float*)eve::mem::align_malloc(16, m_blockSize);
	eve::mem::align_memset_16(m_pData, 0, m_blockSize);

	m_usage = m_bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}

//=================================================================================================
void eve::ogl::Uniform::release(void)
{
	eve::mem::align_free(m_pData);
}



//=================================================================================================
void eve::ogl::Uniform::oglInit(void)
{
	// Initialize global buffer data.
	static bool gb_init = true;
	if (gb_init)
	{
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS,				&m_max_vertex_uniform_blocks);
		glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS,		&m_max_control_uniform_blocks);
		glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS,	&m_max_evaluation_uniform_blocks);
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS,			&m_max_geometry_uniform_blocks);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS,			&m_max_fragment_uniform_blocks);
		EVE_OGL_CHECK_ERROR;

		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,			&m_max_uniform_buffer_binding);
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE,				&m_max_uniform_block_size);
		EVE_OGL_CHECK_ERROR;

		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,		&m_uniform_buffer_offset_alignment);
		EVE_OGL_CHECK_ERROR;

		gb_init = false;
	}

	// Initialize buffer.
	glGenBuffers(1, &m_id);
	EVE_OGL_CHECK_ERROR;

// 	glGetActiveUniformBlockiv(m_prgmId, m_binding, GL_UNIFORM_BLOCK_DATA_SIZE, &m_blockSize);
// 	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_pData, m_usage);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

}

//=================================================================================================
void eve::ogl::Uniform::oglUpdate(void)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);

	m_pOglData = reinterpret_cast<float*>(glMapBufferRange(GL_UNIFORM_BUFFER, 0, m_blockSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
	eve::mem::memcpy(m_pOglData, m_pData, m_blockSize);

	glUnmapBuffer(GL_UNIFORM_BUFFER); 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::oglRelease(void)
{
	glDeleteBuffers(1, &m_id);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Uniform::oglUpdateData(float * p_data)
{
	EVE_ASSERT(p_data);
#if !defined(NDEBUG)
	if (!m_bDynamic)
	{
		EVE_LOG_WARNING("Uniform buffer data updated at draw time but buffer declared as static: performance issue.");
	}
#endif

	m_pData = p_data;
	this->oglUpdate();
}



//=================================================================================================
void eve::ogl::Uniform::pushData(float * p_data, size_t p_size, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data, p_size);
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TVec2<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_VEC2);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TVec3<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_VEC3);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TVec4<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_VEC4);
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TMatrix22<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_MAT2);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TMatrix33<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_MAT3);
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Uniform::pushData(const eve::math::TMatrix44<float> & p_data, size_t p_padding)
{
	eve::mem::memcpy(m_pData + p_padding, p_data.ptr(), EVE_OGL_SIZEOF_MAT4);
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::Uniform::bind(GLuint p_binding)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, p_binding, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::bindCamera(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_CAMERA, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::bindModel(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_MODEL, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::bindSkeleton(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_SKELETON, m_id);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Uniform::unbind(GLuint p_binding)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, p_binding, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::unbind_camera(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_CAMERA, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::unbind_model(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_MODEL, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::unbind_skeleton(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, EVE_OGL_TRANSFORM_SKELETON, 0);
	EVE_OGL_CHECK_ERROR;
}
