
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
#include "eve/ogl/core/Pbo.h"


//=================================================================================================
eve::ogl::FormatPbo::FormatPbo(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, width(0)
	, height(0)
	, numChannels(0)
	, pixels()
{}

//=================================================================================================
eve::ogl::FormatPbo::~FormatPbo(void)
{}

//=================================================================================================
eve::ogl::FormatPbo::FormatPbo(const eve::ogl::FormatPbo & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, width(p_other.width)
	, height(p_other.height)
	, numChannels(p_other.numChannels)
	, pixels(p_other.pixels)
{}

//=================================================================================================
const eve::ogl::FormatPbo & eve::ogl::FormatPbo::operator = (const eve::ogl::FormatPbo & p_other)
{
	if (this != &p_other)
	{
		this->width				= p_other.width;
		this->height				= p_other.height;
		this->numChannels		= p_other.numChannels;
		this->pixels				= p_other.pixels;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Pbo::Pbo(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_width(0)
	, m_height(0)
	, m_numChannels(0)
	, m_size(0)
	, m_pPixels()
	, m_pOglData(nullptr)
{}



//=================================================================================================
void eve::ogl::Pbo::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatPbo * format = reinterpret_cast<eve::ogl::FormatPbo*>(p_format);

	m_width				= format->width;
	m_height			= format->height;
	m_numChannels		= format->numChannels;
	m_pPixels			= format->pixels;

	m_size				= static_cast<GLsizeiptr>((m_width * m_height) * m_numChannels);
}



//=================================================================================================
void eve::ogl::Pbo::init(void)
{
	// Nothing to do for now.
}

//=================================================================================================
void eve::ogl::Pbo::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::ogl::Pbo::oglInit(void)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_id);

	glBufferData(GL_PIXEL_UNPACK_BUFFER, m_id, m_pPixels.get(), GL_STREAM_DRAW);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Pbo::oglUpdate(void)
{
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_id);

	m_pOglData = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, m_size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT); // GL_WRITE_ONLY
	memcpy(m_pOglData, m_pPixels.get(), m_size);

	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Pbo::oglRelease(void)
{
	glDeleteBuffers(1, &m_id);
	m_id = 0;
	EVE_OGL_CHECK_ERROR;

	this->release();
}



//=================================================================================================
void eve::ogl::Pbo::bind(void)
{
	glBindBuffer(GL_DRAW_FRAMEBUFFER, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Pbo::unbind(void)
{
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	EVE_OGL_CHECK_ERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::Pbo::setPixels(std::shared_ptr<GLvoid> p_pPixels)
{
	EVE_ASSERT(p_pPixels.get());
	m_pPixels = p_pPixels;

	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Pbo::setPixels(std::shared_ptr<GLvoid> p_pPixels, uint32_t p_width, uint32_t p_height, uint32_t p_numChannel)
{
	m_width			= p_width;
	m_height		= p_height;
	m_numChannels	= p_numChannel;

	m_size			= static_cast<GLsizeiptr>((m_width * m_height) * m_numChannels);

	EVE_ASSERT(p_pPixels.get());
	m_pPixels = p_pPixels;

	this->requestOglUpdate();
}
