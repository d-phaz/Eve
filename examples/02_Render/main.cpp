
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
#include "eve/ogl/core/Renderer.h"
#include "eve/sys/win32/Window.h"


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

};

//=================================================================================================
RenderGL::RenderGL(void)
	// Inheritance
	: eve::ogl::Renderer()
	// Members init
	, m_pCamera(nullptr)
	, m_pShader(nullptr)
	, m_pUniform(nullptr)
	, m_pVao(nullptr)
{}

//=================================================================================================
void RenderGL::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	m_pCamera = eve::math::Cameraf::create_ptr(800.0f, 600.0f);

	eve::ogl::FormatShader fmtShader;
	fmtShader.vert = eve::io::load_program(eve::io::resource_path_glsl("Colored3D.vert"));
	fmtShader.frag = eve::io::load_program(eve::io::resource_path_glsl("Colored3D.frag"));
	m_pShader = this->create(fmtShader);

	eve::ogl::FormatUniform fmtUniform;
	fmtUniform.blockSize	= EVE_OGL_SIZEOF_MAT4;
	fmtUniform.dynamic		= false;
	fmtUniform.data			= m_pCamera->getMatrixModelViewProjection().m;
	m_pUniform = this->create(fmtUniform);

	eve::ogl::FormatVao fmtVao = eve::geom::create_cube_colored(eve::vec3f::zero(), eve::vec3f::one()*5.0f, eve::color4f::red());
	m_pVao = this->create(fmtVao);
}

//=================================================================================================
void RenderGL::release(void)
{
	m_pVao->requestRelease();
	m_pUniform->requestRelease();
	m_pShader->requestRelease();

	EVE_RELEASE_PTR(m_pCamera);

	// Call parent class.
	eve::ogl::Renderer::release();
}

//=================================================================================================
void RenderGL::cb_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 800, 600);

	m_pShader->bind();
	m_pUniform->bind(1);

	m_pVao->draw();

	m_pUniform->unbind(1);
	m_pShader->unbind();
}


class Example final
	: public eve::sys::View
{
	friend class eve::mem::Pointer;

	EVE_DISABLE_COPY(Example);
	EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(Example);

private:
	/** \brief Alloc and init threaded data. (pure virtual) */
	virtual void initThreadedData(void) override;
	/** \brief Release and delete threaded data. (pure virtual) */
	virtual void releaseThreadedData(void) override;

public:
	virtual void cb_evtMouseDown(eve::evt::MouseEventArgs & p_args) override;
	virtual void cb_evtKeyDown(eve::evt::KeyEventArgs & p_args) override;
	virtual void cb_evtWindowClose(eve::evt::EventArgs & p_arg) override;

};

void Example::initThreadedData(void)
{
	// Call parent class.
	eve::sys::View::initThreadedData();

	// Register new RenderGL.
	this->registerRenderer(EVE_CREATE_PTR(RenderGL));
}

void Example::releaseThreadedData(void)
{
	// Call parent class.
	eve::sys::View::releaseThreadedData();
}

void Example::cb_evtMouseDown(eve::evt::MouseEventArgs & p_args)
{
	
}

void Example::cb_evtKeyDown(eve::evt::KeyEventArgs & p_args)
{
	if (p_args.key == eve::sys::key_Escape)
	{
		eve::evt::notify_application_exit();
	}
}

void Example::cb_evtWindowClose(eve::evt::EventArgs & p_arg)
{
	eve::evt::notify_application_exit();
}


// Launch application for view "Example".
EVE_APPLICATION(Example);
