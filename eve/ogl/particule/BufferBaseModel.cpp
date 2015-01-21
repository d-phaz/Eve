
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
#include "eve/ogl/particule/BufferBaseModel.h"

eve::ogl::BufferBaseModel::BufferBaseModel()
	: m_buffer(std::map<std::string, GLuint>())
{
}

/*Returns bufferID with the associated Key. Returns 0 if Key does not exist. */
const GLuint eve::ogl::BufferBaseModel::getBufferID(std::string p_bufferKey) const
{
	std::map<std::string, GLuint>::const_iterator it = m_buffer.find(p_bufferKey);

	if (it == m_buffer.end())
	{
		return 0;
	}
	else
	{
		const GLuint idReturn = it->second;
		return idReturn;
	}

}

/*Returns false, if element with the same key already exists, otherwise returns true */
bool eve::ogl::BufferBaseModel::saveBuffer(std::string bufferKey, GLuint bufferID)
{
	return m_buffer.insert(std::pair<std::string, GLuint>(bufferKey, bufferID)).second;
}

void eve::ogl::BufferBaseModel::deleteBuffer(std::string ShaderKey)
{
	m_buffer.erase(ShaderKey);
}

GLuint eve::ogl::BufferBaseModel::removeHead()
{
	if (!m_buffer.empty())
	{
		GLuint ID = m_buffer.begin()->second;
		m_buffer.erase(m_buffer.begin());
		return ID;
	}
	else {
		return 0;
	}
}
