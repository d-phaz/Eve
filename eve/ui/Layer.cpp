
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

// Main class header
#include "eve/ui/Layer.h"

#ifndef __EVE_UI_RENDERER_H__
#include "eve/ui/Renderer.h"
#endif


//=================================================================================================
eve::ui::Layer::Layer(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	// Inheritance
	: eve::sys::View()
	, eve::ui::Widget(p_x, p_y, p_width, p_height)
	// Members init
	, m_pRenderer(nullptr)
{}

//=================================================================================================
eve::ui::Layer::Layer(const eve::vec2i & p_position, const eve::vec2i & p_size)
	// Inheritance
	: eve::sys::View()
	, eve::ui::Widget(p_position, p_size)
	// Members init
	, m_pRenderer(nullptr)
{}



//=================================================================================================
void eve::ui::Layer::setup(void)
{
	m_format.x			= m_x;
	m_format.y			= m_y;
	m_format.width		= m_width;
	m_format.height		= m_height;
}



//=================================================================================================
void eve::ui::Layer::init(void)
{
	// Call parent class
	eve::sys::View::init();
	eve::ui::Widget::init();
}

//=================================================================================================
void eve::ui::Layer::release(void)
{	
	// Call parent class
	eve::sys::View::release();
	eve::ui::Widget::release();
}



//=================================================================================================
void eve::ui::Layer::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

	// Render engine.
	m_pRenderer = eve::ui::Renderer::create_ptr(this, m_width, m_height);
	this->registerRenderer(m_pRenderer);
}

//=================================================================================================
void eve::ui::Layer::releaseThreadedData(void)
{
	// Call parent class.
	eve::sys::View::releaseThreadedData();
}



//=================================================================================================
bool eve::ui::Layer::registerRenderer(eve::core::Renderer * p_pRenderer)
{
	return m_pRender->registerRendererFront(p_pRenderer);
}
