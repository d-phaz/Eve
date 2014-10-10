
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
#include "eve/ogl/Fbo.h"


//=================================================================================================
eve::ogl::FormatFbo::FormatFbo(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, width(0)
	, height(0)
	, texNum(1)
	, texDataType(GL_UNSIGNED_BYTE)
	, depthDataType(GL_UNSIGNED_BYTE)
	, bHasDepth(false)
{}

//=================================================================================================
eve::ogl::FormatFbo::~FormatFbo(void)
{}

//=================================================================================================
eve::ogl::FormatFbo::FormatFbo(const eve::ogl::FormatFbo & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, width(p_other.width)
	, height(p_other.height)
	, texDataType(p_other.texDataType)
	, depthDataType(p_other.depthDataType)
	, texNum(p_other.texNum)
	, bHasDepth(p_other.bHasDepth)
{}

//=================================================================================================
const eve::ogl::FormatFbo & eve::ogl::FormatFbo::operator = (const eve::ogl::FormatFbo & p_other)
{
	if (this != &p_other)
	{
		this->width				= p_other.width;
		this->height			= p_other.height;
		this->texDataType		= p_other.texDataType;
		this->depthDataType		= p_other.depthDataType;
		this->texNum			= p_other.texNum;
		this->bHasDepth			= p_other.bHasDepth;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Fbo::Fbo(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_width(0)
	, m_height(0)
	, m_texDataType(GL_UNSIGNED_BYTE)
	, m_depthDataType(GL_UNSIGNED_BYTE)
	, m_pSlotTextureIds(0)
	, m_slotNum(0)
	, m_texNum(0)
	, m_bHasDepth(false)
	, m_black(0)
	, m_layers(GL_COLOR)
{}



//=================================================================================================
void eve::ogl::Fbo::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatFbo * format = reinterpret_cast<eve::ogl::FormatFbo*>(p_format);

	m_width				= format->width;
	m_height			= format->height;
	m_texDataType		= format->texDataType;
	m_depthDataType		= format->depthDataType;
	m_texNum			= format->texNum;
	m_bHasDepth			= format->bHasDepth;
}



//=================================================================================================
void eve::ogl::Fbo::init(void)
{
	m_slotNum = m_texNum;
	if (m_bHasDepth) 
	{
		m_layers = (GL_COLOR | GL_DEPTH);
		m_slotNum += 1;
	}
	m_pSlotTextureIds	= (GLuint*)malloc(sizeof(GLuint)* m_slotNum);
	m_black				= (float*)calloc(4, sizeof(float));
}

//=================================================================================================
void eve::ogl::Fbo::release(void)
{
	EVE_RELEASE_PTR_C(m_pSlotTextureIds);
	EVE_RELEASE_PTR_C(m_black);
}



//=================================================================================================
void eve::ogl::Fbo::oglInit(void)
{
	// Generate FBO
	glGenFramebuffers(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	// Create color textures
	for (size_t i = 0; i < m_texNum; i++)
	{
		// Create texture
		glGenTextures(1, &m_pSlotTextureIds[i]);
		glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[i]);
		// Pass texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Initialize texture data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, m_texDataType, NULL);
		// Release current texture id to default
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;

		// Link texture to FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + i), GL_TEXTURE_2D, m_pSlotTextureIds[i], 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		EVE_OGL_CHECK_ERROR;
	}

	// Create depth texture
	if (m_bHasDepth)
	{
		// Create texture
		glGenTextures(1, &m_pSlotTextureIds[m_texNum]);
		glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum]);
		// Pass texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Initialize texture data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, m_depthDataType, NULL);
		// Release current texture id to default
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;

		// Link texture to FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum], 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		EVE_OGL_CHECK_ERROR;
	}

	// Attach FBO.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
	// Test FBO state.
	EVE_OGL_CHECK_FBO(m_id);
	// Clear empty textures to avoid memory corruption
	glClearBufferfv(m_layers, 0, m_black);
	// Detach FBO.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::oglUpdate(void)
{
	// Color textures
	for (uint32_t i = 0; i < m_texNum; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, m_texDataType, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;
	}

	// Depth textures
	if (m_bHasDepth)
	{
		glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, m_depthDataType, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		EVE_OGL_CHECK_ERROR;
	}
}

//=================================================================================================
void eve::ogl::Fbo::oglRelease(void)
{
	glDeleteFramebuffers(1, &m_id);
	m_id = 0;
	EVE_OGL_CHECK_ERROR;

	glDeleteTextures(static_cast<GLsizei>(m_slotNum), m_pSlotTextureIds);
	EVE_OGL_CHECK_ERROR;

	this->release();
}



//=================================================================================================
void eve::ogl::Fbo::bind(void)
{
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
	glClearBufferfv(m_layers, 0, m_black);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::unbind(void)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Fbo::write(GLsizei p_slotsAmount, GLenum * p_pTargetSlots)
{
	glDrawBuffers(p_slotsAmount, p_pTargetSlots);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::write(GLenum p_slot)
{
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + p_slot);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Fbo::bindAndWrite(GLsizei p_slotsAmount, GLenum * p_pTargetSlots)
{
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
	glClearBufferfv(m_layers, 0, m_black);
	EVE_OGL_CHECK_ERROR;

	glDrawBuffers(p_slotsAmount, p_pTargetSlots); // test if required 
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::bindAndWrite(GLenum p_targetSlot)
{
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
	glClearBufferfv(m_layers, 0, m_black);
	EVE_OGL_CHECK_ERROR;

	glDrawBuffer(GL_COLOR_ATTACHMENT0 + p_targetSlot); // test if required 
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Fbo::bindTexture(GLenum p_activeIndex, GLuint p_targetSlot)
{
	glActiveTexture(GL_TEXTURE0 + p_activeIndex);
	glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[p_targetSlot]);
	//glActiveTexture(GL_TEXTURE0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::bindDepthTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum]);
	//glActiveTexture(GL_TEXTURE0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::unbindTexture(GLenum p_activeIndex)
{
	glActiveTexture(GL_TEXTURE0 + p_activeIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glActiveTexture(GL_TEXTURE0);
	EVE_OGL_CHECK_ERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::Fbo::setSize(uint32_t p_width, uint32_t p_height)
{
	m_width		= p_width;
	m_height	= p_height;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Fbo::setWidth(uint32_t p_width)
{
	m_width		= p_width;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Fbo::setHeight(uint32_t p_height)
{
	m_height	= p_height;
	this->requestOglUpdate();
}
