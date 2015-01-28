
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
#include "eve/ui/Frame.h"

#ifndef __EVE_UI_RENDERER_H__
#include "eve/ui/Renderer.h"
#endif


//=================================================================================================
eve::ui::Frame::Frame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	// Inheritance.
	: eve::ui::Layer(p_x, p_y, p_width, p_height)
	// Members init.
{}

//=================================================================================================
eve::ui::Frame::Frame(const eve::vec2i & p_position, const eve::vec2i & p_size)
	// Inheritance.
	: eve::ui::Layer(p_position, p_size)
	// Members init.
{}



//=================================================================================================
void eve::ui::Frame::setup(void)
{
	// Call parent class.
	eve::ui::Layer::setup();

	m_format.windowType = eve::sys::WindowType_Child;
}



//=================================================================================================
void eve::ui::Frame::init(void)
{
	// Call parent class
	eve::ui::Layer::init();

}

//=================================================================================================
void eve::ui::Frame::release(void)
{	

	// Call parent class
	eve::ui::Layer::release();
}



//=================================================================================================
void eve::ui::Frame::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Layer::initThreadedData();

}

//=================================================================================================
void eve::ui::Frame::releaseThreadedData(void)
{
	
	// Call parent class.
	eve::ui::Layer::releaseThreadedData();
}



//=================================================================================================
void eve::ui::Frame::inflate(int32_t p_width, int32_t p_height)
{
	m_pWindow->setSize(m_pWindow->getWidth() + p_width, m_pWindow->getHeight() + p_height);
	m_width  += p_width;
	m_height += p_height;
}

//=================================================================================================
void eve::ui::Frame::inflateX(int32_t p_value)
{
	m_pWindow->setWidth(m_pWindow->getWidth() + p_value);
	m_width += p_value;
}

//=================================================================================================
void eve::ui::Frame::inflateY(int32_t p_value)
{
	m_pWindow->setHeight(m_pWindow->getHeight() + p_value);
	m_height += p_value;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ui::Frame::setPosition(int32_t p_x, int32_t p_y)
{
	m_pWindow->setPosition(p_x, p_y);
	m_x = p_x;
	m_y = p_y;
}

//=================================================================================================
void eve::ui::Frame::setPositionX(int32_t p_value)
{
	m_pWindow->setPositionX(p_value);
	m_x = p_value;
}

//=================================================================================================
void eve::ui::Frame::setPositionY(int32_t p_value)
{
	m_pWindow->setPositionY(p_value);
	m_y = p_value;
}



//=================================================================================================
void eve::ui::Frame::setSize(int32_t p_width, int32_t p_height)
{
	m_pWindow->setSize(p_width, p_height);

	// Call parent class.
	eve::ui::Widget::setSize(p_width, p_height);
}

//=================================================================================================
void eve::ui::Frame::setWidth(int32_t p_value)
{
	m_pWindow->setWidth(p_value);

	// Call parent class.
	eve::ui::Widget::setWidth(p_value);
}

//=================================================================================================
void eve::ui::Frame::setHeight(int32_t p_value)
{
	m_pWindow->setHeight(p_value);

	// Call parent class.
	eve::ui::Widget::setHeight(p_value);
}
