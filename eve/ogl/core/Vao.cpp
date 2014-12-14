
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

// Main header
#include "eve/ogl/core/Vao.h"


//=================================================================================================
eve::ogl::FormatVao::FormatVao(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, numVertices(0)
	, numIndices(0)
	, perVertexNumPosition(0)
	, perVertexNumDiffuse(0)
	, perVertexNumNormal(0)
	, vertices()
	, indices()
{}

//=================================================================================================
eve::ogl::FormatVao::~FormatVao(void)
{}

//=================================================================================================
eve::ogl::FormatVao::FormatVao(const eve::ogl::FormatVao & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, numVertices(p_other.numVertices)
	, numIndices(p_other.numIndices)
	, perVertexNumPosition(p_other.perVertexNumPosition)
	, perVertexNumDiffuse(p_other.perVertexNumDiffuse)
	, perVertexNumNormal(p_other.perVertexNumNormal)
	, vertices(p_other.vertices)
	, indices(p_other.indices)
{}

//=================================================================================================
const eve::ogl::FormatVao & eve::ogl::FormatVao::operator = (const eve::ogl::FormatVao & p_other)
{
	if (this != &p_other)
	{
		this->numVertices			= p_other.numVertices;
		this->numIndices			= p_other.numIndices;
		this->perVertexNumPosition	= p_other.perVertexNumPosition;
		this->perVertexNumDiffuse	= p_other.perVertexNumDiffuse;
		this->perVertexNumNormal	= p_other.perVertexNumNormal;
		this->vertices				= p_other.vertices;
		this->indices				= p_other.indices;
	}
	return *this;
}



//=================================================================================================
eve::ogl::Vao::Vao(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	, m_arrayBufferId(0)
	, m_elementBufferId(0)
	, m_numVertices(0)
	, m_numIndices(0)
	, m_perVertexNumPosition(0)
	, m_perVertexNumDiffuse(0)
	, m_perVertexNumNormal(0)
	, m_pVertices()
	, m_pIndices()
	, m_pOglData(nullptr)
	, m_offsetPosition(0)
	, m_offsetDiffuse(0)
	, m_offsetNormals(0)
	, m_verticesStrideUnit(0)
	, m_verticesStride(0)
	, m_verticesSize(0)
	, m_indicesSize(0)
{}



//=================================================================================================
void eve::ogl::Vao::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatVao * format = reinterpret_cast<eve::ogl::FormatVao*>(p_format);

	this->m_numVertices				= format->numVertices;
	this->m_numIndices				= format->numIndices;
	this->m_perVertexNumPosition	= format->perVertexNumPosition;
	this->m_perVertexNumDiffuse		= format->perVertexNumDiffuse;
	this->m_perVertexNumNormal		= format->perVertexNumNormal;
	this->m_pVertices				= format->vertices;
	this->m_pIndices				= format->indices;

	EVE_ASSERT(m_numVertices != 0);
	EVE_ASSERT(m_numIndices != 0);
	EVE_ASSERT(m_perVertexNumPosition != 0);
	EVE_ASSERT(m_perVertexNumDiffuse != 0);
}



//=================================================================================================
void eve::ogl::Vao::init(void)
{
	m_offsetPosition		= 0;
	m_offsetDiffuse			= sizeof(float) * m_perVertexNumPosition;
	m_offsetNormals			= sizeof(float) * (m_perVertexNumPosition + m_perVertexNumDiffuse);

	m_verticesStrideUnit	= (m_perVertexNumPosition + m_perVertexNumDiffuse + m_perVertexNumNormal);
	m_verticesStride		= GLsizei(m_verticesStrideUnit * sizeof(float));

	m_verticesSize			= GLsizeiptr(m_numVertices * m_verticesStride);
	m_indicesSize			= GLsizeiptr(m_numIndices * sizeof(GLuint));
}

//=================================================================================================
void eve::ogl::Vao::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::ogl::Vao::oglInit(void)
{
	glGenBuffers(1, &m_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize, m_pIndices.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;


	glGenBuffers(1, &m_arrayBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize, m_pVertices.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;


	glGenVertexArrays(1, &m_id);

	glBindVertexArray(m_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId);

	glVertexAttribPointer(EVE_OGL_ATTRIBUTE_POSITION, m_perVertexNumPosition, GL_FLOAT, GL_FALSE, m_verticesStride, EVE_OGL_BUFFER_OFFSET(m_offsetPosition));
	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_POSITION);

	glVertexAttribPointer(EVE_OGL_ATTRIBUTE_DIFFUSE, m_perVertexNumDiffuse, GL_FLOAT, GL_FALSE, m_verticesStride, EVE_OGL_BUFFER_OFFSET(m_offsetDiffuse));
	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_DIFFUSE);

	if (m_perVertexNumNormal > 0) {
		glVertexAttribPointer(EVE_OGL_ATTRIBUTE_NORMAL, m_perVertexNumNormal, GL_FLOAT, GL_FALSE, m_verticesStride, EVE_OGL_BUFFER_OFFSET(m_offsetNormals));
		glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_NORMAL);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	EVE_OGL_CHECK_ERROR;

// 	// Vertex attrib binding -> to bench
// 	glBindVertexArray(m_id);
// 
// 	glVertexAttribBinding(EVE_OGL_ATTRIBUTE_POSITION, 0);
// 	glVertexAttribFormat(EVE_OGL_ATTRIBUTE_POSITION, m_perVertexNumPosition, GL_FLOAT, GL_FALSE, m_offsetPosition);
// 	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_POSITION);
// 
// 	glVertexAttribBinding(EVE_OGL_ATTRIBUTE_DIFFUSE, 0);
// 	glVertexAttribFormat(EVE_OGL_ATTRIBUTE_DIFFUSE, m_perVertexNumDiffuse, GL_FLOAT, GL_FALSE, m_offsetDiffuse);
// 	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_DIFFUSE);
// 
// 	if (m_perVertexNumNormal > 0)
// 	{
// 		glVertexAttribBinding(EVE_OGL_ATTRIBUTE_NORMAL, 0);
// 		glVertexAttribFormat(EVE_OGL_ATTRIBUTE_NORMAL, m_perVertexNumNormal, GL_FLOAT, GL_FALSE, m_offsetNormals);
// 		glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_NORMAL);
// 	}
// 
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
// 
// 	glBindVertexArray(0);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
// 	EVE_OGL_CHECK_ERROR;

}

//=================================================================================================
void eve::ogl::Vao::oglUpdate(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId);

	m_pOglData = reinterpret_cast<float*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, m_verticesSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
	memcpy(m_pOglData, m_pVertices.get(), m_verticesSize);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::Vao::oglRelease(void)
{
	glDeleteVertexArrays(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	glDeleteBuffers(1, &m_arrayBufferId);
	glDeleteBuffers(1, &m_elementBufferId);
	EVE_OGL_CHECK_ERROR;

	this->release();
}



//=================================================================================================
void eve::ogl::Vao::draw(void)
{
	glBindVertexArray(m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);

	glDrawElementsInstancedBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL, 1, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	EVE_OGL_CHECK_ERROR;


// 	// Vertex attrib binding -> to bench
// 	glBindVertexArray(m_id);
// 	glBindVertexBuffer(0, m_arrayBufferId, 0, m_verticesStride);
// 
// 	glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 1, 0, 0);
// 	
// 	//glBindVertexArray(0);
// 	EVE_OGL_CHECK_ERROR;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::Vao::setVertices(const std::shared_ptr<float> & p_data)
{
	m_pVertices = p_data;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::Vao::setIndices(const std::shared_ptr<GLuint> & p_data)
{
	m_pIndices = p_data;
	this->requestOglUpdate();
}
