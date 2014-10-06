
// Main header
#include "eve/ogl/Format.h"


//=================================================================================================
eve::ogl::FormatFBO::FormatFBO(void)
	// Inheritance
	: eve::ogl::Format()
	// members init
	, m_width(0)
	, m_height(0)
	, m_texNum(0)
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
	, m_texNum(p_other.m_texNum)
	, m_bHasDepth(p_other.m_bHasDepth)
{}

//=================================================================================================
const eve::ogl::FormatFBO & eve::ogl::FormatFBO::operator = (const eve::ogl::FormatFBO & p_other)
{
	if (this != &p_other)
	{
		this->m_width		= p_other.m_width;
		this->m_height		= p_other.m_height;
		this->m_texNum		= p_other.m_texNum;
		this->m_bHasDepth	= p_other.m_bHasDepth;
	}
	return *this;
}
