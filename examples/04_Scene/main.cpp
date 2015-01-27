
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

#include "eve/app/App.h"
#include "eve/sys/win32/Window.h"

#include "eve/scene/Scene.h"

static eve::scene::Scene * m_pScene = nullptr;

class ExampleDisplay final
	: public eve::ui::Display
{
	EVE_DISABLE_COPY(ExampleDisplay);
	EVE_PUBLIC_DESTRUCTOR(ExampleDisplay);

public:
	/** \brief class constructor. */
	explicit ExampleDisplay(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

};

ExampleDisplay::ExampleDisplay(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	: eve::ui::Display(p_x, p_y, p_width, p_height)
{}

void ExampleDisplay::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Display::initThreadedData();

	this->registerRenderer(m_pScene);
}

void ExampleDisplay::releaseThreadedData(void)
{
	this->unregisterRenderer(m_pScene);
	
	// Call parent class.
	eve::ui::Display::releaseThreadedData();
}



class ExampleFrame final
	: public eve::ui::Frame
{
	EVE_DISABLE_COPY(ExampleFrame);
	EVE_PUBLIC_DESTRUCTOR(ExampleFrame);

public:
	/** \brief class constructor. */
	explicit ExampleFrame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

};

ExampleFrame::ExampleFrame(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	: eve::ui::Frame(p_x, p_y, p_width, p_height)
{}

void ExampleFrame::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Frame::initThreadedData();

	this->registerRenderer(m_pScene);
}

void ExampleFrame::releaseThreadedData(void)
{
	this->unregisterRenderer(m_pScene);

	// Call parent class.
	eve::ui::Frame::releaseThreadedData();
}




class Example final
	: public eve::ui::View
{

private:
	//eve::scene::Scene * m_pScene;


	EVE_DISABLE_COPY(Example);
	EVE_PUBLIC_DESTRUCTOR(Example);

public:
	/** \brief class constructor. */
	explicit Example(void);
	
public:
	/** \brief Setup format properties. (pure virtual) */
	virtual void setup(void) override;

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;
	virtual void cb_evtTextInput(eve::evt::TextEventArgs & p_args) override;
	virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override;

};

Example::Example(void)
	: eve::ui::View()
{}

void Example::setup(void)
{
	// Call parent class.
	eve::ui::View::setup();

	m_format.x		= 50;
	m_format.y		= 50;
	m_format.width  = 800;
	m_format.height = 600;
}

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::ui::View::initThreadedData();

	// Register new RenderGL.
	m_pScene = EVE_CREATE_PTR(eve::scene::Scene);
	this->registerRenderer(m_pScene);

	//for (size_t i = 0; i < 6; i++)
	{
		//ExampleDisplay * test = this->addDisplay<ExampleDisplay>(50, 50, 800, 600);
	}
	
	//ExampleFrame * test = this->addFrame<ExampleFrame>(0, 0, 400, 300);
}

void Example::releaseThreadedData(void)
{
	//this->releaseRenderer(m_pScene);

	// Call parent class.
	eve::ui::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	//m_pWindow->toggleFullScreen();
	//m_pRender->setSize(m_pWindow->getWidth(), m_pWindow->getHeight());
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	EVE_LOG_INFO("Pressed key: %d ctrl: %d   alt: %d   shift: %d"
				, p_args.key
				, eve::sys::modifier_crtl(p_args.modifier)
				, eve::sys::modifier_alt(p_args.modifier)
				, eve::sys::modifier_shift(p_args.modifier));

	if (p_args.key == eve::sys::key_Escape
	 || p_args.key == eve::sys::key_Q && eve::sys::modifier_crtl(p_args.modifier))
	{
		eve::evt::notify_application_exit();
	}
	else if (p_args.key == eve::sys::key_Return)
	{
		std::wstring path(EVE_TXT("C:\\Users\\aleister_doe\\Desktop\\import\\untitled_spot.dae"));
		m_pScene->load(path);
	}

}

void Example::cb_evtTextInput(eve::evt::TextEventArgs & p_args)
{
	wchar_t txt[2];
	txt[0] = p_args.text;
	txt[1] = EVE_TXT('\0');
	EVE_LOG_INFO("Pressed key: %s", txt);
}

void Example::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	eve::evt::notify_application_exit();
}


// Launch application for view "Example".
EVE_APPLICATION(Example);
