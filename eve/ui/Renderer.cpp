
// Main header
#include "eve/ui/Renderer.h"

#ifndef __EVE_UI_LAYER_H__
#include "eve/ui/Layer.h"
#endif


//=================================================================================================
eve::ui::Renderer * eve::ui::Renderer::create_ptr(eve::ui::Layer * p_pLayer, int32_t p_width, int32_t p_height)
{
	EVE_ASSERT(p_pLayer);

	eve::ui::Renderer * ptr = new eve::ui::Renderer(p_pLayer, p_width, p_height);
	ptr->init();
	return ptr;
}

//=================================================================================================
eve::ui::Renderer * eve::ui::Renderer::create_ptr(eve::ui::Layer * p_pLayer, const eve::vec2i & p_size)
{
	EVE_ASSERT(p_pLayer);

	eve::ui::Renderer * ptr = new eve::ui::Renderer(p_pLayer, p_size);
	ptr->init();
	return ptr;
}



//=================================================================================================
eve::ui::Renderer::Renderer(eve::ui::Layer * p_pLayer, int32_t p_width, int32_t p_height)
	// Inheritance.
	: eve::ogl::Renderer()
	// Members init
	, m_viewX(0)
	, m_viewY(0)
	, m_viewWidth(p_width)
	, m_viewHeight(p_height)
	, m_matrixProjection()
	, m_pLayer(p_pLayer)
	, m_pShaderColored(nullptr)
	, m_pShaderTextured(nullptr)
	, m_pUniformMatrices(nullptr)
{}

//=================================================================================================
eve::ui::Renderer::Renderer(eve::ui::Layer * p_pLayer, const eve::vec2i & p_size)
	// Inheritance.
	: eve::ogl::Renderer()
	// Members init
	, m_viewX(0)
	, m_viewY(0)
	, m_viewWidth(p_size.x)
	, m_viewHeight(p_size.y)
	, m_matrixProjection()
	, m_pLayer(p_pLayer)
	, m_pShaderColored(nullptr)
	, m_pShaderTextured(nullptr)
	, m_pUniformMatrices(nullptr)
{}



//=================================================================================================
void eve::ui::Renderer::init(void)
{
	// Call parent class.
	eve::ogl::Renderer::init();

	// Colored shader.
	eve::ogl::FormatShader fmtShaderCol;
	fmtShaderCol.vert = eve::io::load_program(eve::io::resource_path_glsl("Colored2D.vert"));
	fmtShaderCol.frag = eve::io::load_program(eve::io::resource_path_glsl("Colored2D.frag"));
	m_pShaderColored = this->create(fmtShaderCol);

	// Textured shader.
	eve::ogl::FormatShader fmtShaderTex;
	fmtShaderTex.vert = eve::io::load_program(eve::io::resource_path_glsl("Textured2D.vert"));
	fmtShaderTex.frag = eve::io::load_program(eve::io::resource_path_glsl("Textured2D.frag"));
	m_pShaderTextured = this->create(fmtShaderTex);
	
	// Uniform buffer.
	eve::ogl::FormatUniform fmtUniform;
	fmtUniform.blockSize = EVE_OGL_SIZEOF_MAT4;
	fmtUniform.dynamic	 = false;
	fmtUniform.data		 = m_matrixProjection.data();
	m_pUniformMatrices	 = this->create(fmtUniform);

	// Orthographic matrix.
	this->calcMatrices();
}

//=================================================================================================
void eve::ui::Renderer::release(void)
{
	m_pShaderColored->requestRelease();
	m_pShaderColored = nullptr;
	m_pShaderTextured->requestRelease();
	m_pShaderTextured = nullptr;

	m_pUniformMatrices->requestRelease();
	m_pUniformMatrices = nullptr;

	// Call parent class.
	eve::ogl::Renderer::release();
}



//=================================================================================================
void eve::ui::Renderer::calcMatrices(void)
{
	// Orthographic matrix.
	m_matrixProjection = eve::math::TMatrix44<float>::ortho(static_cast<float>(m_viewX)
														  , static_cast<float>(m_viewWidth)
														  , static_cast<float>(m_viewHeight)
														  , static_cast<float>(m_viewY));
	m_pUniformMatrices->setData(m_matrixProjection.data());
}



//=================================================================================================
void eve::ui::Renderer::viewTranslate(int32_t p_x, int32_t p_y)
{
	m_viewX -= p_x;
	m_viewY -= p_y;
	this->calcMatrices();
}

//=================================================================================================
void eve::ui::Renderer::viewTranslate(const eve::vec2i & p_value)
{
	this->viewTranslate(p_value.x, p_value.y);
}

//=================================================================================================
void eve::ui::Renderer::viewTranslateX(int32_t p_value)
{
	m_viewX -= p_value;
	this->calcMatrices();
}

//=================================================================================================
void eve::ui::Renderer::viewTranslateY(int32_t p_value)
{
	m_viewY -= p_value;
	this->calcMatrices();
}



//=================================================================================================
void eve::ui::Renderer::cb_display(void)
{
	glViewport(m_viewX, m_viewY, m_viewWidth, m_viewHeight);
	m_pUniformMatrices->bindCamera();

	m_pShaderColored->bind();
	m_pLayer->oglDrawColored();

	m_pShaderTextured->bind();
	m_pLayer->oglDrawTextured();

	eve::ogl::Shader::unbind();
}






