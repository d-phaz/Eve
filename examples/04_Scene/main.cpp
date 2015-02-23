
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

class ExampleOutput final
	: public eve::ui::Output
{
	EVE_DISABLE_COPY(ExampleOutput);
	EVE_PUBLIC_DESTRUCTOR(ExampleOutput);

public:
	/** \brief class constructor. */
	explicit ExampleOutput(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

};

ExampleOutput::ExampleOutput(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	: eve::ui::Output(p_x, p_y, p_width, p_height)
{}

void ExampleOutput::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Output::initThreadedData();
}

void ExampleOutput::releaseThreadedData(void)
{	
	// Call parent class.
	eve::ui::Output::releaseThreadedData();
}



class ExampleView final
	: public eve::ui::View
{

public:
	eve::scene::Scene * m_pScene;


	EVE_DISABLE_COPY(ExampleView);
	EVE_PUBLIC_DESTRUCTOR(ExampleView);

public:
	/** \brief class constructor. */
	explicit ExampleView(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;
	virtual void cb_evtTextInput(eve::evt::TextEventArgs & p_args) override;

};

ExampleView::ExampleView(int32_t p_x, int32_t p_y, int32_t p_width, int32_t p_height)
	: eve::ui::View(p_x, p_y, p_width, p_height)
{}

void ExampleView::initThreadedData(void)
{
	// Call parent class.
	eve::ui::View::initThreadedData();
	
	// Register new RenderGL.
	m_pScene = EVE_CREATE_PTR(eve::scene::Scene);
	this->registerRenderer(m_pScene);
}

void ExampleView::releaseThreadedData(void)
{
	this->releaseRenderer(m_pScene);

	// Call parent class.
	eve::ui::View::releaseThreadedData();
}

void ExampleView::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	// Propagate to scene.
}

void ExampleView::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	EVE_LOG_INFO("Pressed key: %d ctrl: %d   alt: %d   shift: %d"
				, p_args.key
				, eve::sys::modifier_crtl(p_args.modifier)
				, eve::sys::modifier_alt(p_args.modifier)
				, eve::sys::modifier_shift(p_args.modifier));

	if (p_args.key == eve::sys::key_Return)
	{
		std::wstring path(EVE_TXT("C:\\Users\\aleister_doe\\Desktop\\import\\untitled_spot.dae"));
		m_pScene->load(path);
	}
}

void ExampleView::cb_evtTextInput(eve::evt::TextEventArgs & p_args)
{
	// Propagate to scene.
}




class Example final
	: public eve::ui::Window
{
private:
	ExampleView * view;


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

};

Example::Example(void)
	: eve::ui::Window()
{}

void Example::setup(void)
{
	// Call parent class.
	eve::ui::Window::setup();

	m_format.x		= 50;
	m_format.y		= 50;
	m_format.width  = 800;
	m_format.height = 600;
}

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::ui::Window::initThreadedData();
	
	view = this->addView<ExampleView>(0, 0, 800, 600);
}

void Example::releaseThreadedData(void)
{
	// Call parent class.
	eve::ui::Window::releaseThreadedData();
}



// Create entry point.
void entry_point(void)
{
	EveApp->addWindow<Example>();
}

// Launch application entry point method.
EVE_APPLICATION(entry_point);
