
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
#include "eve/ogl/core/Texture.h"


//=================================================================================================
eve::ogl::FormatTex::FormatTex(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, internalFormat(GL_RGBA)
	, format(GL_RGBA)
	, width(0)
	, height(0)
	, type(GL_UNSIGNED_BYTE)
	, filter(GL_LINEAR)
	, wrap(GL_CLAMP_TO_EDGE)
	, pixels()
{}

//=================================================================================================
eve::ogl::FormatTex::~FormatTex(void)
{}

//=================================================================================================
eve::ogl::FormatTex::FormatTex(const eve::ogl::FormatTex & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, internalFormat(p_other.internalFormat)
	, format(p_other.format)
	, width(p_other.width)
	, height(p_other.height)
	, type(p_other.type)
	, filter(p_other.filter)
	, wrap(p_other.wrap)
	, pixels(p_other.pixels)
{}

//=================================================================================================
const eve::ogl::FormatTex & eve::ogl::FormatTex::operator = (const eve::ogl::FormatTex & p_other)
{
	if (this != &p_other)
	{
		this->internalFormat	= p_other.internalFormat;
		this->format			= p_other.format;
		this->width				= p_other.width;
		this->height			= p_other.height;
		this->type				= p_other.type;
		this->filter			= p_other.filter;
		this->wrap				= p_other.wrap;
		this->pixels			= p_other.pixels;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Texture::Texture(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_internalFormat(GL_RGBA)
	, m_format(GL_RGBA)
	, m_width(0)
	, m_height(0)
	, m_type(GL_UNSIGNED_BYTE)
	, m_pPixels()
	, m_filter(GL_LINEAR)
	, m_wrap(GL_CLAMP_TO_EDGE)
	, m_bSubUpdate(false)
{}



//=================================================================================================
void eve::ogl::Texture::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatTex * format = reinterpret_cast<eve::ogl::FormatTex*>(p_format);

	m_internalFormat = format->internalFormat;
	m_format		 = format->format;
	m_width			 = format->width;
	m_height		 = format->height;
	m_type			 = format->type;
	m_filter		 = format->filter;
	m_wrap			 = format->wrap;
	m_pPixels		 = format->pixels;
}

//=================================================================================================
void eve::ogl::Texture::updateAttributes(eve::ogl::Format * p_format)
{
	this->setAttributes(p_format);
	m_bSubUpdate = false;
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::Texture::init(void)
{
	// Nothing to do for now.
}

//=================================================================================================
void eve::ogl::Texture::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::ogl::Texture::oglInit(void)
{
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//EVE_OGL_CHECK_ERROR;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);
	EVE_OGL_CHECK_ERROR;

	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, m_pPixels.get());
	EVE_OGL_CHECK_ERROR;

	glBindTexture( GL_TEXTURE_2D, 0 );
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::oglUpdate(void)
{
	if (m_bSubUpdate)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_format, m_type, m_pPixels.get());
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, m_pPixels.get());
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;
	}
}

//=================================================================================================
void eve::ogl::Texture::oglRelease(void)
{
	glDeleteTextures(1, &m_id);
	m_id = 0;
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Texture::bind(GLenum p_index)
{
	glActiveTexture(GL_TEXTURE0 + p_index);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::bindDiffuse(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_DIFFUSE);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::bindNormal(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_NORMAL);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::bindEmissive(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_EMISSIVE);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::bindOpacity(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_OPACITY);
	glBindTexture(GL_TEXTURE_2D, m_id);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Texture::unbind(GLenum p_index)
{
	glActiveTexture(GL_TEXTURE0 + p_index);
	glBindTexture(GL_TEXTURE_2D, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::unbind_diffuse(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_DIFFUSE);
	glBindTexture(GL_TEXTURE_2D, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::unbind_normal(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_NORMAL);
	glBindTexture(GL_TEXTURE_2D, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::unbind_emissive(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_EMISSIVE);
	glBindTexture(GL_TEXTURE_2D, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Texture::unbind_opacity(void)
{
	glActiveTexture(GL_TEXTURE0 + EVE_OGL_SAMPLER_OPACITY);
	glBindTexture(GL_TEXTURE_2D, 0);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Texture::setPixels(const std::shared_ptr<GLvoid> & p_pPixels)
{
	EVE_ASSERT(p_pPixels.get());
	m_pPixels = p_pPixels;

	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Texture::setPixels(const std::shared_ptr<GLvoid> && p_pPixels)
{
	EVE_ASSERT(p_pPixels.get());
	m_pPixels = p_pPixels;

	this->requestOglUpdate();
}
