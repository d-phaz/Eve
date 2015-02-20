
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
#include "eve/ogl/core/VaoStaged.h"


//=================================================================================================
eve::ogl::FormatVaoStaged::FormatVaoStaged(void)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, numVertices(0)
	, numIndices(0)
	, perVertexNumPosition(0)
	, perVertexNumDiffuse(0)
	, perVertexNumNormal(0)
	, positions()
	, diffuses()
	, normals()
	, indices()
{}

//=================================================================================================
eve::ogl::FormatVaoStaged::~FormatVaoStaged(void)
{}

//=================================================================================================
eve::ogl::FormatVaoStaged::FormatVaoStaged(const eve::ogl::FormatVaoStaged & p_other)
	// Inheritance
	: eve::ogl::Format()
	// Members init
	, numVertices(p_other.numVertices)
	, numIndices(p_other.numIndices)
	, perVertexNumPosition(p_other.perVertexNumPosition)
	, perVertexNumDiffuse(p_other.perVertexNumDiffuse)
	, perVertexNumNormal(p_other.perVertexNumNormal)
	, positions(p_other.positions)
	, diffuses(p_other.diffuses)
	, normals(p_other.normals)
	, indices(p_other.indices)
{}

//=================================================================================================
const eve::ogl::FormatVaoStaged & eve::ogl::FormatVaoStaged::operator = (const eve::ogl::FormatVaoStaged & p_other)
{
	if (this != &p_other)
	{
		this->numVertices			= p_other.numVertices;
		this->numIndices			= p_other.numIndices;
		this->perVertexNumPosition	= p_other.perVertexNumPosition;
		this->perVertexNumDiffuse	= p_other.perVertexNumDiffuse;
		this->perVertexNumNormal	= p_other.perVertexNumNormal;
		this->positions				= p_other.positions;
		this->diffuses				= p_other.diffuses;
		this->normals				= p_other.normals;
		this->indices				= p_other.indices;
	}
	return *this;
}



//=================================================================================================
eve::ogl::VaoStaged::VaoStaged(void)
	// Inheritance
	: eve::ogl::Object()
	// Members init
	, m_id(0)
	
	, m_arrayBufferId(nullptr)
	, m_elementBufferId(0)
	
	, m_numVertices(0)
	, m_numIndices(0)
	
	, m_perVertexNumPosition(0)
	, m_perVertexNumDiffuse(0)
	, m_perVertexNumNormal(0)

	, m_pPositionsData(nullptr)
	, m_pPositions()
	, m_bPositionsUpdate(false)
	, m_pDiffusesData(nullptr)
	, m_pDiffuses()
	, m_bDiffusesUpdate(false)
	, m_pNormalsData(nullptr)
	, m_pNormals()
	, m_bNormalsUpdate(false)
	, m_pIndicesData(nullptr)
	, m_pIndices()
	, m_bIndicesUpdate(false)

	, m_positionStride(0)
	, m_positionSize(0)
	, m_diffuseStride(0)
	, m_diffuseSize(0)
	, m_normalStride(0)
	, m_normalSize(0)
	, m_indicesSize(0)
{}



//=================================================================================================
void eve::ogl::VaoStaged::setAttributes(eve::ogl::Format * p_format)
{
	eve::ogl::FormatVaoStaged * format = reinterpret_cast<eve::ogl::FormatVaoStaged*>(p_format);

	this->m_numVertices				= format->numVertices;
	this->m_numIndices				= format->numIndices;

	this->m_perVertexNumPosition	= format->perVertexNumPosition;
	this->m_perVertexNumDiffuse		= format->perVertexNumDiffuse;
	this->m_perVertexNumNormal		= format->perVertexNumNormal;

	this->m_pPositions				= format->positions;
	this->m_pDiffuses				= format->diffuses;
	this->m_pNormals				= format->normals;
	this->m_pIndices				= format->indices;

	EVE_ASSERT(m_numVertices != 0);
	EVE_ASSERT(m_numIndices != 0);
	EVE_ASSERT(m_perVertexNumPosition != 0);
	EVE_ASSERT(m_perVertexNumDiffuse != 0);
}



//=================================================================================================
void eve::ogl::VaoStaged::init(void)
{
	m_arrayBufferId = (GLuint *)eve::mem::malloc(3 * sizeof(GLuint));

	GLsizei flt_size = sizeof(float);

	m_positionStride	= m_perVertexNumPosition * flt_size;
	m_positionSize		= GLsizeiptr(m_numVertices * m_positionStride);

	m_diffuseStride		= m_perVertexNumDiffuse * flt_size;
	m_diffuseSize		= GLsizeiptr(m_numVertices * m_diffuseStride);

	m_normalStride		= m_perVertexNumNormal * flt_size;
	m_normalSize		= GLsizeiptr(m_numVertices * m_normalStride);

	m_indicesSize		= GLsizeiptr(m_numIndices * sizeof(GLuint));
}

//=================================================================================================
void eve::ogl::VaoStaged::release(void)
{
	EVE_RELEASE_PTR_C(m_arrayBufferId);
}



//=================================================================================================
void eve::ogl::VaoStaged::oglInit(void)
{
	glGenBuffers(1, &m_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize, m_pIndices.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;


	glGenBuffers(3, m_arrayBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Position]);
	glBufferData(GL_ARRAY_BUFFER, m_positionSize, m_pPositions.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Diffuse]);
	glBufferData(GL_ARRAY_BUFFER, m_diffuseSize, m_pDiffuses.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Normal]);
	glBufferData(GL_ARRAY_BUFFER, m_normalSize, m_pNormals.get(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;


	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Position]);
	glVertexAttribPointer(EVE_OGL_ATTRIBUTE_POSITION, m_perVertexNumPosition, GL_FLOAT, GL_FALSE, m_positionStride, 0);
	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Diffuse]);
	glVertexAttribPointer(EVE_OGL_ATTRIBUTE_DIFFUSE, m_perVertexNumDiffuse, GL_FLOAT, GL_FALSE, m_diffuseStride, 0);
	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_DIFFUSE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Normal]);
	glVertexAttribPointer(EVE_OGL_ATTRIBUTE_NORMAL, m_perVertexNumNormal, GL_FLOAT, GL_FALSE, m_normalStride, 0);
	glEnableVertexAttribArray(EVE_OGL_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EVE_OGL_CHECK_ERROR;
	
	glBindVertexArray(0);
	EVE_OGL_CHECK_ERROR;
}

//=================================================================================================
void eve::ogl::VaoStaged::oglUpdate(void)
{
	if (m_bPositionsUpdate)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Position]);

		m_pPositionsData = reinterpret_cast<float*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, m_positionSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
		eve::mem::memcpy(m_pPositionsData, m_pPositions.get(), m_positionSize);

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		EVE_OGL_CHECK_ERROR;

		m_bPositionsUpdate = false;
	}

	if (m_bDiffusesUpdate)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Diffuse]);

		m_pDiffusesData = reinterpret_cast<float*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, m_diffuseSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
		eve::mem::memcpy(m_pDiffusesData, m_pDiffuses.get(), m_diffuseSize);

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		EVE_OGL_CHECK_ERROR;

		m_bDiffusesUpdate = false;
	}

	if (m_bNormalsUpdate)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferId[Vao_Stage_Normal]);

		m_pNormalsData = reinterpret_cast<float*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, m_normalSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
		eve::mem::memcpy(m_pNormalsData, m_pNormals.get(), m_normalSize);

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		EVE_OGL_CHECK_ERROR;

		m_bNormalsUpdate = false;
	}

	if (m_bIndicesUpdate)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);

		m_pIndicesData = reinterpret_cast<GLuint*>(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, m_indicesSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
		eve::mem::memcpy(m_pIndicesData, m_pIndices.get(), m_indicesSize);

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		EVE_OGL_CHECK_ERROR;

		m_bIndicesUpdate = false;
	}
}

//=================================================================================================
void eve::ogl::VaoStaged::oglRelease(void)
{
	glDeleteVertexArrays(1, &m_id);
	EVE_OGL_CHECK_ERROR;

	glDeleteBuffers(3, m_arrayBufferId);
	glDeleteBuffers(1, &m_elementBufferId);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::VaoStaged::draw(void)
{
	glBindVertexArray(m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);

	glDrawElementsInstancedBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL, 1, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	EVE_OGL_CHECK_ERROR;
}



//=================================================================================================
void eve::ogl::VaoStaged::add(eve::ogl::VaoStaged * p_pVao)
{
	// Avoid empty and self copying.
	EVE_ASSERT(p_pVao);
	EVE_ASSERT(p_pVao != this);

	// Test data structures compatibility.
	EVE_ASSERT(p_pVao->getPerVertexNumPosition() == m_perVertexNumPosition);
	EVE_ASSERT(p_pVao->getPerVertexNumDiffuse()  == m_perVertexNumDiffuse);
	EVE_ASSERT(p_pVao->getPerVertexNumNormal()   == m_perVertexNumNormal);


	// Grab number of added data.
	GLint addedVerts = p_pVao->getNumVertices();
	GLint addedInds  = p_pVao->getNumIndices();


	// Copy original positions.
	float * positions = (float*)eve::mem::malloc((m_numVertices + addedVerts) * m_positionStride);
	eve::mem::memcpy(positions, m_pPositions.get(), m_numVertices * m_positionStride);
	// Add new positions.
	float * pos = positions + (m_numVertices * m_perVertexNumPosition);
	eve::mem::memcpy(pos, p_pVao->getPositions().get(), addedVerts * m_positionStride);
	// Update shared pointer.
	m_pPositions.reset(positions);


	// Copy original diffuse coordinates.
	float * diffuses = (float*)eve::mem::malloc((m_numVertices + addedVerts) * m_diffuseStride);
	eve::mem::memcpy(diffuses, m_pDiffuses.get(), m_numVertices * m_diffuseStride);
	// Add new diffuse coordinates.
	float * dif = diffuses + (m_numVertices * m_perVertexNumDiffuse);
	eve::mem::memcpy(dif, p_pVao->getDiffuses().get(), addedVerts * m_diffuseStride);
	// Update shared pointer.
	m_pPositions.reset(dif);


	// Copy original normals.
	float * normals = (float*)eve::mem::malloc((m_numVertices + addedVerts) * m_normalStride);
	eve::mem::memcpy(normals, m_pNormals.get(), m_numVertices * m_normalStride);
	// Add new normals.
	float * nor = normals + (m_numVertices * m_perVertexNumNormal);
	eve::mem::memcpy(nor, p_pVao->getNormals().get(), addedVerts * m_normalStride);
	// Update shared pointer.
	m_pPositions.reset(nor);


	// Copy original indices.
	GLuint * indices = (GLuint*)eve::mem::malloc((m_numIndices + addedInds) * sizeof(GLuint));
	eve::mem::memcpy(indices, m_pIndices.get(), (m_numIndices * sizeof(GLuint)));
	// Add new indices, incremented of original vertices number.
	GLuint * inds	 = indices + m_numIndices - 1;
	GLuint * newInds = p_pVao->getIndices().get() - 1;
	for (GLint i = 0; i < addedInds; i++)
	{
		*++inds = *++newInds + m_numVertices;
	}
	// Update shared pointer.
	m_pIndices.reset(indices);


	// Update parsing data.
	m_numVertices += addedVerts;
	m_numIndices  += addedInds;
	m_positionSize = static_cast<GLsizeiptr>(m_numVertices * m_positionStride);
	m_diffuseSize  = static_cast<GLsizeiptr>(m_numVertices * m_diffuseStride);
	m_normalSize   = static_cast<GLsizeiptr>(m_numVertices * m_normalStride);
	m_indicesSize  = static_cast<GLsizeiptr>(m_numIndices * sizeof(GLuint));


	// Request full update.
	m_bPositionsUpdate	= true;
	m_bDiffusesUpdate	= true;
	m_bNormalsUpdate	= true;
	m_bIndicesUpdate	= true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::merge(eve::ogl::VaoStaged * p_pVao)
{
	this->add(p_pVao);
	p_pVao->requestRelease();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::ogl::VaoStaged::setPositions(const std::shared_ptr<float> & p_data)
{
	m_pPositions = p_data;
	m_bPositionsUpdate = true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::setPositions(const std::shared_ptr<float> && p_data)
{
	m_pPositions = p_data;
	m_bPositionsUpdate = true;
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::VaoStaged::setDiffuses(const std::shared_ptr<float> & p_data)
{
	m_pDiffuses = p_data;
	m_bDiffusesUpdate = true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::setDiffuses(const std::shared_ptr<float> && p_data)
{
	m_pDiffuses = p_data;
	m_bDiffusesUpdate = true;
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::VaoStaged::setNormals(const std::shared_ptr<float> & p_data)
{
	m_pNormals = p_data;
	m_bNormalsUpdate = true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::setNormals(const std::shared_ptr<float> && p_data)
{
	m_pNormals = p_data;
	m_bNormalsUpdate = true;
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::VaoStaged::setVertices(const std::shared_ptr<float> & p_positions
									, const std::shared_ptr<float> & p_diffuses
									, const std::shared_ptr<float> & p_normals)
{
	m_pPositions		= p_positions;
	m_bPositionsUpdate	= true;
	m_pDiffuses			= p_diffuses;
	m_bDiffusesUpdate	= true;
	m_pNormals			= p_normals;
	m_bNormalsUpdate	= true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::setVertices(const std::shared_ptr<float> && p_positions
									, const std::shared_ptr<float> && p_diffuses
									, const std::shared_ptr<float> && p_normals)
{
	m_pPositions		= p_positions;
	m_bPositionsUpdate	= true;
	m_pDiffuses			= p_diffuses;
	m_bDiffusesUpdate	= true;
	m_pNormals			= p_normals;
	m_bNormalsUpdate	= true;
	this->requestOglUpdate();
}



//=================================================================================================
void eve::ogl::VaoStaged::setIndices(const std::shared_ptr<GLuint> & p_data)
{
	m_pIndices = p_data;
	m_bIndicesUpdate = true;
	this->requestOglUpdate();
}

//=================================================================================================
void eve::ogl::VaoStaged::setIndices(const std::shared_ptr<GLuint> && p_data)
{
	m_pIndices = p_data;
	m_bIndicesUpdate = true;
	this->requestOglUpdate();
}
