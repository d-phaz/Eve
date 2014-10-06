
// Main header
#include "eve/ogl/Object.h"

#ifndef __EVE_OPENGL_RENDER_H__
#include "eve/ogl/Renderer.h"
#endif


//=================================================================================================
eve::ogl::Object::Object(void)
	// Inheritance
	: eve::mem::Pointer()
	// members init
	, m_pRenderer(nullptr)
{}



//=================================================================================================
void eve::ogl::Object::linkToRenderer(eve::ogl::Renderer * p_pRenderer)
{
	EVE_ASSERT(p_pRenderer);
	m_pRenderer = p_pRenderer;
}



//=================================================================================================
void eve::ogl::Object::requestOglInit(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueInit(this);
}

//=================================================================================================
void eve::ogl::Object::requestOglUpdate(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueUpdate(this);
}

//=================================================================================================
void eve::ogl::Object::requestRelease(void)
{
	EVE_ASSERT(m_pRenderer);
	m_pRenderer->putInQueueRelease(this);
}
