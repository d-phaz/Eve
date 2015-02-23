
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
#include "eve/ui/Window.h"


//=================================================================================================
eve::ui::Window::Window(void)
	// Inheritance
	: eve::sys::View()

	// Members init
	, m_pVecView(nullptr)
	, m_pVecOutput(nullptr)
{}



//=================================================================================================
void eve::ui::Window::setup(void)
{
// 	uint32_t border		= eve::sys::Window::get_border_thickness();
// 	uint32_t titleBar	= eve::sys::Window::get_title_bar_height();
// 	uint32_t width		= eve::sys::get_work_area_width() - (border * 2);
// 	uint32_t height		= eve::sys::get_work_area_height() - (titleBar + (border * 2));
// 
// 	m_format.x			= border;
// 	m_format.y			= titleBar + border;
// 	m_format.width		= width;
// 	m_format.height		= height;

	m_format.windowType = eve::sys::WindowType_App;
}



//=================================================================================================
void eve::ui::Window::init(void)
{
	// Containers.
	m_pVecView		= new std::vector<eve::ui::View*>();
	m_pVecOutput	= new std::vector<eve::ui::Output*>();

	// Call parent class
	eve::sys::View::init();
}

//=================================================================================================
void eve::ui::Window::release(void)
{
	// Display container.
	eve::ui::Output * out = nullptr;
	while (!m_pVecOutput->empty())
	{
		out = m_pVecOutput->back();
		m_pVecOutput->pop_back();

		EVE_RELEASE_PTR(out);
	}
	EVE_RELEASE_PTR_CPP(m_pVecOutput);

	// View container.
	eve::ui::View * frame = nullptr;
	while (!m_pVecView->empty())
	{
		frame = m_pVecView->back();
		m_pVecView->pop_back();

		EVE_RELEASE_PTR(frame);
	}
	EVE_RELEASE_PTR_CPP(m_pVecView);

	// Call parent class
	eve::sys::View::release();
}



//=================================================================================================
void eve::ui::Window::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();
}

//=================================================================================================
void eve::ui::Window::releaseThreadedData(void)
{
	// Call parent class.
	eve::sys::View::releaseThreadedData();
}



//=================================================================================================
bool eve::ui::Window::releaseView(eve::ui::View * p_pView)
{
	m_pFence->lock();

	std::vector<eve::ui::View*>::iterator itr = std::find(m_pVecView->begin(), m_pVecView->end(), p_pView);
	bool breturn = (itr != m_pVecView->end());
	if (breturn)
	{
		eve::ui::View * ptr = (*itr);
		m_pVecView->erase(itr);
		EVE_RELEASE_PTR(ptr);
	}

	m_pFence->unlock();

	return breturn;
}

//=================================================================================================
bool eve::ui::Window::releaseOutput(eve::ui::Output * p_pOutput)
{
	m_pFence->lock();

	std::vector<eve::ui::Output*>::iterator itr = std::find(m_pVecOutput->begin(), m_pVecOutput->end(), p_pOutput);
	bool breturn = (itr != m_pVecOutput->end());
	if (breturn)
	{
		eve::ui::Output * ptr = (*itr);
		m_pVecOutput->erase(itr);
		EVE_RELEASE_PTR(ptr);
	}

	m_pFence->unlock();

	return breturn;
}



//=================================================================================================
void eve::ui::Window::cb_evtFileDrop(eve::evt::FileEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtFileDrop(p_args);
			return;
		}
	}
}



//=================================================================================================
void eve::ui::Window::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	if (p_args.key == eve::sys::key_Escape
	 || p_args.key == eve::sys::key_Q && eve::sys::modifier_crtl(p_args.modifier))
	{
		eve::evt::notify_application_terminate();
	}
	else
	{
		for (auto && itr : (*m_pVecView))
		{
			itr->cb_evtKeyDown(p_args);
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtKeyUp(eve::evt::KeyEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		itr->cb_evtKeyUp(p_args);
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtTextInput(eve::evt::TextEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		itr->cb_evtTextInput(p_args);
	}
}



//=================================================================================================
void eve::ui::Window::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtMouseDown(p_args);
			return;
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtMouseWheel(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtMouseWheel(p_args);
			return;
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtMouseUp(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtMouseUp(p_args);
			return;
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtMouseDoubleClick(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtMouseDoubleClick(p_args);
			return;
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtMotion(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtMotion(p_args);
			return;
		}
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtPassiveMotion(eve::evt::MouseEventArgs & p_args)
{
	for (auto && itr : (*m_pVecView))
	{
		if (itr->testHit(p_args.x, p_args.y))
		{
			itr->cb_evtPassiveMotion(p_args);
			return;
		}
	}
}



//=================================================================================================
void eve::ui::Window::cb_evtWindowResize(eve::evt::ResizeEventArgs & p_arg)
{
	int32_t w(m_format.width);
	int32_t h(m_format.height);

	int32_t deportX(p_arg.width - w);
	int32_t deportY(p_arg.height - h);

	float ratioX = 0.0f;
	float ratioY = 0.0f;

	for (auto && itr : (*m_pVecView))
	{
		ratioX = static_cast<float>(itr->getWidth())  / static_cast<float>(w);
		ratioY = static_cast<float>(itr->getHeight()) / static_cast<float>(h);

		itr->inflate(static_cast<int32_t>(static_cast<float>(deportX)* ratioX)
			       , static_cast<int32_t>(static_cast<float>(deportY) * ratioY));
	}

	m_format.width  = p_arg.width;
	m_format.height = p_arg.height;
}

//=================================================================================================
void eve::ui::Window::cb_evtWindowMove(eve::evt::MoveEventArgs & p_arg)
{
	for (auto && itr : (*m_pVecView))
	{
		itr->cb_evtWindowMove(p_arg);
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtWindowFocusGot(eve::evt::EventArgs & p_arg)
{
	for (auto && itr : (*m_pVecView))
	{
		itr->cb_evtWindowFocusGot(p_arg);
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtWindowFocusLost(eve::evt::EventArgs & p_arg)
{
	for (auto && itr : (*m_pVecView))
	{
		itr->cb_evtWindowFocusLost(p_arg);
	}
}

//=================================================================================================
void eve::ui::Window::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	eve::evt::notify_application_exit();
}
