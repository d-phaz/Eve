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

#pragma once
#ifndef __EVE_OPENGL_PARTICULE_ATTRACTOR_MODEL_H__
#define __EVE_OPENGL_PARTICULE_ATTRACTOR_MODEL_H__

namespace eve
{
	namespace ogl
	{

		template <class Vector, class Value>
		class AttractorModel
		{
		private:
			Vector	m_position;
			float 	m_attDepth; //The z-Coordinate of the attractor

		public:
			AttractorModel()
				: m_position()
				, m_attDepth(100.0f)
			{
			}

			~AttractorModel()
			{
			}

			AttractorModel(Vector position)
			{
				m_position = position;
			}

			Vector	getPosition()
			{
				return m_position;
			}

			//Override me
			virtual void setPosition(Vector p_position)
			{
				m_position = p_position;
			}

			void incrementDepth(float p_inc)
			{
				m_attDepth += p_inc;
				if (m_attDepth < 0)
					m_attDepth = 0;
				else if (m_attDepth > 10000)
					m_attDepth = 10000;
			}

			float getDepth()
			{
				return m_attDepth;
			}

		};

	} // namespace ogl

} // namespace eve

#endif