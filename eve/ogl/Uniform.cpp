
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
#include "eve/ogl/Uniform.h"


//=================================================================================================
eve::ogl::FormatUniform::FormatUniform(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, prgmId(0)
	, binding(0)
	, dynamic(false)
	, data()
{}

//=================================================================================================
eve::ogl::FormatUniform::~FormatUniform(void)
{}

//=================================================================================================
eve::ogl::FormatUniform::FormatUniform(const eve::ogl::FormatUniform & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, prgmId(p_other.prgmId)
	, binding(p_other.binding)
	, dynamic(p_other.dynamic)
	, data(p_other.data)
{}

//=================================================================================================
const eve::ogl::FormatUniform & eve::ogl::FormatUniform::operator = (const eve::ogl::FormatUniform & p_other)
{
	if (this != &p_other)
	{
		this->prgmId	= p_other.prgmId;
		this->binding	= p_other.binding;
		this->dynamic	= p_other.dynamic;
		this->data		= p_other.data;
	}
	return *this;
}



//=================================================================================================
int32_t	eve::ogl::Uniform::m_max_vertex_uniform_blocks			= 0;
int32_t	eve::ogl::Uniform::m_max_geometry_uniform_blocks		= 0;
int32_t	eve::ogl::Uniform::m_max_fragment_uniform_blocks		= 0;

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
	, m_prgmId(0)
	, m_binding(0)
	, m_bDynamic(false)
	, m_pData()
	, m_pOglData(nullptr)
{}



//=================================================================================================
void eve::ogl::Uniform::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatUniform * format = reinterpret_cast<eve::ogl::FormatUniform*>(p_format);

	m_prgmId	= format->prgmId;	
	m_binding	= format->binding;
	m_bDynamic	= format->dynamic;
	m_pData		= format->data;

	EVE_ASSERT(m_prgmId != 0);
}



//=================================================================================================
void eve::ogl::Uniform::init(void)
{
	m_usage = m_bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}

//=================================================================================================
void eve::ogl::Uniform::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::ogl::Uniform::oglInit(void)
{
	// Initialize global buffer data.
	static bool gb_init = true;
	if (gb_init)
	{
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &m_max_vertex_uniform_blocks);
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &m_max_geometry_uniform_blocks);
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &m_max_fragment_uniform_blocks);
		EVE_OGL_CHECK_ERROR;

		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &m_max_uniform_block_size);
		EVE_OGL_CHECK_ERROR;

		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &m_uniform_buffer_offset_alignment);
		EVE_OGL_CHECK_ERROR;

		gb_init = false;
	}

	// Initialize buffer.
	glGenBuffers(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	glGetActiveUniformBlockiv(m_prgmId, m_binding, GL_UNIFORM_BLOCK_DATA_SIZE, &m_blockSize);
	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_pData.get(), m_usage);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

}

//=================================================================================================
void eve::ogl::Uniform::oglUpdate(void)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_pData.get(), m_usage);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Uniform::oglRelease(void)
{
	glDeleteBuffers(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	this->release();
}



//=================================================================================================
void eve::ogl::Uniform::bind(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, m_id);
}

//=================================================================================================
void eve::ogl::Uniform::unbind(void)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, 0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::Uniform::setData(const std::shared_ptr<float> & p_data)
{
	m_pData = p_data;
	this->requestOglUpdate();
}
