
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
#include "eve/ui/Display.h"


//=================================================================================================
eve::ui::Display::Display(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	// Inheritance.
	: eve::ui::Layer(p_x, p_y, p_width, p_height)
	// Members init.
{}

//=================================================================================================
eve::ui::Display::Display(const eve::vec2i & p_position, const eve::vec2i & p_size)
	// Inheritance.
	: eve::ui::Layer(p_position, p_size)
	// Members init.
{}



//=================================================================================================
void eve::ui::Display::setup(void)
{
	// Call parent class.
	eve::ui::Layer::setup();

	m_format.windowType = eve::sys::WindowType_Output;
}



//=================================================================================================
void eve::ui::Display::init(void)
{
	// Call parent class.
	eve::ui::Layer::init();

}

//=================================================================================================
void eve::ui::Display::release(void)
{

	// Call parent class.
	eve::ui::Layer::release();
}



//=================================================================================================
void eve::ui::Display::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Layer::initThreadedData();

}

//=================================================================================================
void eve::ui::Display::releaseThreadedData(void)
{

	// Call parent class.
	eve::ui::Layer::releaseThreadedData();
}



//=================================================================================================
void eve::ui::Display::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	switch (p_args.button)
	{
	case eve::sys::btn_Right:
		// Display position + size parameters.
		break;

	case eve::sys::btn_Left:
	default:
		break;
	}
}

//=================================================================================================
void eve::ui::Display::cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
{

}

//=================================================================================================
void eve::ui::Display::cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
{
	if (p_args.button == eve::sys::btn_Left)
	{
		m_pWindow->toggleFullScreen();
	}
}

//=================================================================================================
void eve::ui::Display::cb_evtMotion(eve::evt::MouseEventArgs & p_args)
{

}
