
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
#include "eve/ui/View.h"


//=================================================================================================
eve::ui::View::View(void)
	// Inheritance
	: eve::sys::View()

	// Members init
	, m_pVecFrame(nullptr)
	, m_pVecDisplay(nullptr)
{}



//=================================================================================================
void eve::ui::View::setup(void)
{
	uint32_t border		= eve::sys::Window::get_border_thickness();
	uint32_t titleBar	= eve::sys::Window::get_title_bar_height();
	uint32_t width		= eve::sys::get_work_area_width() - (border * 2);
	uint32_t height		= eve::sys::get_work_area_height() - (titleBar + (border * 2));

	m_format.x			= border;
	m_format.y			= titleBar + border;
	m_format.width		= width;
	m_format.height		= height;
	m_format.windowType = eve::sys::WindowType_App;
}



//=================================================================================================
void eve::ui::View::init(void)
{
	// Containers.
	m_pVecFrame		= new std::vector<eve::ui::Frame*>();
	m_pVecDisplay	= new std::vector<eve::ui::Display*>();

	// Call parent class
	eve::sys::Node::init();
}

//=================================================================================================
void eve::ui::View::release(void)
{
	// Display container.
	eve::ui::Display * dis = nullptr;
	while (!m_pVecDisplay->empty())
	{
		dis = m_pVecDisplay->back();
		m_pVecDisplay->pop_back();

		EVE_RELEASE_PTR(dis);
	}
	EVE_RELEASE_PTR_CPP(m_pVecDisplay);

	// Frame container.
	eve::ui::Frame * frame = nullptr;
	while (!m_pVecFrame->empty())
	{
		frame = m_pVecFrame->back();
		m_pVecFrame->pop_back();

		EVE_RELEASE_PTR(frame);
	}
	EVE_RELEASE_PTR_CPP(m_pVecFrame);

	// Call parent class
	eve::sys::Node::release();
}



//=================================================================================================
void eve::ui::View::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

}

//=================================================================================================
void eve::ui::View::releaseThreadedData(void)
{

	// Call parent class.
	eve::sys::View::releaseThreadedData();
}



//=================================================================================================
bool eve::ui::View::removeFrame(eve::ui::Frame * p_pFrame)
{
	m_pFence->lock();

	std::vector<eve::ui::Frame*>::iterator itr = std::find(m_pVecFrame->begin(), m_pVecFrame->end(), p_pFrame);
	bool breturn = (itr != m_pVecFrame->end());
	if (breturn)
	{
		m_pVecFrame->erase(itr);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::ui::View::releaseFrame(eve::ui::Frame * p_pFrame)
{
	m_pFence->lock();

	std::vector<eve::ui::Frame*>::iterator itr = std::find(m_pVecFrame->begin(), m_pVecFrame->end(), p_pFrame);
	bool breturn = (itr != m_pVecFrame->end());
	if (breturn)
	{
		eve::ui::Frame * ptr = (*itr);
		m_pVecFrame->erase(itr);
		EVE_RELEASE_PTR(ptr);
	}

	m_pFence->unlock();

	return breturn;
}



//=================================================================================================
bool eve::ui::View::removeDiaplay(eve::ui::Display * p_pDisplay)
{
	m_pFence->lock();

	std::vector<eve::ui::Display*>::iterator itr = std::find(m_pVecDisplay->begin(), m_pVecDisplay->end(), p_pDisplay);
	bool breturn = (itr != m_pVecDisplay->end());
	if (breturn)
	{
		m_pVecDisplay->erase(itr);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::ui::View::releaseDisplay(eve::ui::Display * p_pDisplay)
{
	m_pFence->lock();

	std::vector<eve::ui::Display*>::iterator itr = std::find(m_pVecDisplay->begin(), m_pVecDisplay->end(), p_pDisplay);
	bool breturn = (itr != m_pVecDisplay->end());
	if (breturn)
	{
		eve::ui::Display * ptr = (*itr);
		m_pVecDisplay->erase(itr);
		EVE_RELEASE_PTR(ptr);
	}

	m_pFence->unlock();

	return breturn;
}
