
// Main header
#include "eve/ogl/Fbo.h"


//=================================================================================================
eve::ogl::FormatFBO::FormatFBO(void)
	// Inheritance
	: eve::ogl::Format()
	// members init
	, m_width(0)
	, m_height(0)
	, m_texNum(1)
	, m_texDataType(GL_UNSIGNED_BYTE)
	, m_depthDataType(GL_UNSIGNED_BYTE)
	, m_bHasDepth(false)
{}

//=================================================================================================
eve::ogl::FormatFBO::~FormatFBO(void)
{}

//=================================================================================================
eve::ogl::FormatFBO::FormatFBO(const eve::ogl::FormatFBO & p_other)
	// Inheritance
	: eve::ogl::Format()
	// members init
	, m_width(p_other.m_width)
	, m_height(p_other.m_height)
	, m_texDataType(p_other.m_texDataType)
	, m_depthDataType(p_other.m_depthDataType)
	, m_texNum(p_other.m_texNum)
	, m_bHasDepth(p_other.m_bHasDepth)
{}

//=================================================================================================
const eve::ogl::FormatFBO & eve::ogl::FormatFBO::operator = (const eve::ogl::FormatFBO & p_other)
{
	if (this != &p_other)
	{
		this->m_width			= p_other.m_width;
		this->m_height			= p_other.m_height;
		this->m_texDataType		= p_other.m_texDataType;
		this->m_depthDataType	= p_other.m_depthDataType;
		this->m_texNum			= p_other.m_texNum;
		this->m_bHasDepth		= p_other.m_bHasDepth;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Fbo::Fbo(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_glFramebufferId(0)
	, m_width(0)
	, m_height(0)
	, m_texDataType(GL_UNSIGNED_BYTE)
	, m_depthDataType(GL_UNSIGNED_BYTE)
	, m_pSlotTextureIds(0)
	, m_slotNum(0)
	, m_texNum(0)
	, m_bHasDepth(false)
{}



//=================================================================================================
void eve::ogl::Fbo::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatFBO * format = reinterpret_cast<eve::ogl::FormatFBO*>(p_format);

	m_width				= format->m_width;
	m_height			= format->m_height;
	m_texDataType		= format->m_texDataType;
	m_depthDataType		= format->m_depthDataType;
	m_texNum			= format->m_texNum;
	m_bHasDepth			= format->m_bHasDepth;
}



//=================================================================================================
void eve::ogl::Fbo::init(void)
{
	m_slotNum = m_texNum;
	if (m_bHasDepth) {
		m_slotNum += 1;
	}

	m_pSlotTextureIds = (GLuint*)malloc(sizeof(GLuint)* m_slotNum);
}

//=================================================================================================
void eve::ogl::Fbo::release(void)
{
	EVE_RELEASE_PTR_C(m_pSlotTextureIds);
}



//=================================================================================================
void eve::ogl::Fbo::oglInit(void)
{
	// Generate FBO
	glGenFramebuffers(1, &m_glFramebufferId);
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
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
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
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum], 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		EVE_OGL_CHECK_ERROR;
	}

	// Attach FBO.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
	// Test FBO state.
	EVE_OGL_CHECK_FBO(m_glFramebufferId);
	// Clear empty textures to avoid memory corruption
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Detach FBO.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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
	glDeleteFramebuffers(1, &m_glFramebufferId);
	m_glFramebufferId = 0;
	EVE_OGL_CHECK_ERROR;

	glDeleteTextures(static_cast<GLsizei>(m_slotNum), m_pSlotTextureIds);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Fbo::bind(void)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
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
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
	EVE_OGL_CHECK_ERROR;

	glDrawBuffers(p_slotsAmount, p_pTargetSlots);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::bindAndWrite(GLenum p_targetSlot)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_glFramebufferId);
	EVE_OGL_CHECK_ERROR;

	glDrawBuffer(GL_COLOR_ATTACHMENT0 + p_targetSlot);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::Fbo::bindTexture(GLenum p_activeIndex, GLuint p_targetSlot)
{
	glActiveTexture(GL_TEXTURE0 + p_activeIndex);
	glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[p_targetSlot]);
	glActiveTexture(GL_TEXTURE0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::bindDepthTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, m_pSlotTextureIds[m_texNum]);
	glActiveTexture(GL_TEXTURE0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Fbo::unbindTexture(GLenum p_activeIndex)
{
	glActiveTexture(GL_TEXTURE0 + p_activeIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
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
