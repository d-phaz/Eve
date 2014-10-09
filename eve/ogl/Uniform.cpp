
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
{}

//=================================================================================================
eve::ogl::FormatUniform::~FormatUniform(void)
{}

//=================================================================================================
eve::ogl::FormatUniform::FormatUniform(const eve::ogl::FormatUniform & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
{}

//=================================================================================================
const eve::ogl::FormatUniform & eve::ogl::FormatUniform::operator = (const eve::ogl::FormatUniform & p_other)
{
	if (this != &p_other)
	{

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
{}



//=================================================================================================
void eve::ogl::Uniform::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatUniform * format = reinterpret_cast<eve::ogl::FormatUniform*>(p_format);


}



//=================================================================================================
void eve::ogl::Uniform::init(void)
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
}

//=================================================================================================
void eve::ogl::Uniform::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::ogl::Uniform::oglInit(void)
{
	
}

//=================================================================================================
void eve::ogl::Uniform::oglUpdate(void)
{
	
}

//=================================================================================================
void eve::ogl::Uniform::oglRelease(void)
{
	

	this->release();
}



//=================================================================================================
void eve::ogl::Uniform::bind(GLenum p_index)
{
	
}

//=================================================================================================
void eve::ogl::Uniform::unbind(GLenum p_index)
{
	
}
