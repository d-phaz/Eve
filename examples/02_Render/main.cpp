
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
#include "eve/math/Includes.h"
#include "eve/io/Image.h"
#include "eve/ogl/core/Renderer.h"


class RenderGL final
	: public eve::ogl::Renderer
{
	friend class eve::mem::Pointer;

	//////////////////////////////////////
	//				DATA				//
	//////////////////////////////////////

private:
	eve::math::Cameraf *	m_pCamera;

	eve::ogl::Shader *		m_pShader;
	eve::ogl::Uniform *		m_pUniform;
	eve::ogl::Texture *		m_pTexture;
	eve::ogl::Vao *			m_pVao;


	//////////////////////////////////////
	//				METHOD				//
	//////////////////////////////////////

	EVE_DISABLE_COPY(RenderGL);
	EVE_PROTECT_DESTRUCTOR(RenderGL);

private:
	explicit RenderGL(void);


protected:
	/** \brief Alloc and init class members. (pure virtual) */
	virtual void init(void) override;
	/** \brief Release and delete class members. (pure virtual) */
	virtual void release(void) override;

public:
	/** \brief Draw on screen callback. (pure virtual) */
	virtual void cb_display(void) override;

public:
	/** \brief Set render size. */
	virtual void setSize(uint32_t p_width, uint32_t p_height);

};

//=================================================================================================
RenderGL::RenderGL(void)
	// Inheritance
	: eve::ogl::Renderer()
	// Members init
	, m_pCamera(nullptr)
	, m_pShader(nullptr)
	, m_pUniform(nullptr)
	, m_pTexture(nullptr)
	, m_pVao(nullptr)
{}

//=================================================================================================
void RenderGL::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	m_width   = 800;
	m_height  = 600;
	m_pCamera = eve::math::Cameraf::create_ptr(m_width, m_height);

	eve::ogl::FormatShader fmtShader;
	fmtShader.vert = eve::io::load_program(eve::io::resource_path_glsl("Textured3D.vert"));
	fmtShader.frag = eve::io::load_program(eve::io::resource_path_glsl("Textured3D.frag"));
	m_pShader = this->create(fmtShader);

	eve::ogl::FormatUniform fmtUniform;
	fmtUniform.blockSize	= EVE_OGL_SIZEOF_MAT4;
	fmtUniform.dynamic		= false;
	fmtUniform.data			= m_pCamera->getMatrixModelViewProjection().data();
	m_pUniform = this->create(fmtUniform);

	eve::ogl::FormatTex fmtTex;
	std::string path("C:\\Users\\aleister_doe\\Desktop\\import\\1.jpg");
	if (!eve::io::load_image(path, &fmtTex))
	{
		EVE_LOG_ERROR("Unable to load file %s", path.c_str());
		EVE_ASSERT_FAILURE;
	}
	m_pTexture = this->create(fmtTex);

	eve::ogl::FormatVao fmtVao  = eve::geom::create_cube_textured(eve::vec3f::zero(), eve::vec3f::one() * 5.0f);
	m_pVao = this->create(fmtVao);
}

//=================================================================================================
void RenderGL::release(void)
{
	m_pVao->requestRelease();
	m_pTexture->requestRelease();
	m_pUniform->requestRelease();
	m_pShader->requestRelease();

	EVE_RELEASE_PTR(m_pCamera);

	// Call parent class.
	eve::ogl::Renderer::release();
}

//=================================================================================================
void RenderGL::cb_display(void)
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, m_width, m_height);

	m_pShader->bind();
	m_pUniform->bind(1);

	m_pTexture->bind(1);

	m_pVao->draw();

	m_pTexture->unbind(1);

	m_pUniform->unbind(1);
	m_pShader->unbind();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
}

//=================================================================================================
void RenderGL::setSize(uint32_t p_width, uint32_t p_height)
{
	// Call parent class.
	eve::ogl::Renderer::setSize(p_width, p_height);

	m_pCamera->setDisplaySize(p_width, p_height);
}




class Example final
	: public eve::ui::View
{
	friend class eve::mem::Pointer;

private:
	RenderGL * m_pRender;


	EVE_DISABLE_COPY(Example);
	EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Example);

public:
	/** \brief Setup format properties. (pure virtual) */
	virtual void setup(void);

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

void Example::setup(void)
{
	m_format.x			= 50;
	m_format.y			= 50;
	m_format.width		= 800;
	m_format.height		= 600;
	m_format.windowType = eve::sys::WindowType_App;
}

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::ui::View::initThreadedData();

	// Register new RenderGL.
	m_pRender = EVE_CREATE_PTR(RenderGL);
	this->registerRenderer(m_pRender);
}

void Example::releaseThreadedData(void)
{
	// Call parent class.
	eve::ui::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	m_pWindow->toggleFullScreen();
	m_pRender->setSize(m_pWindow->getWidth(), m_pWindow->getHeight());
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
