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
#ifndef __EVE_OPENGL_PARTICULE_ATTRACTOR_H__
#define __EVE_OPENGL_PARTICULE_ATTRACTOR_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_EXTERNAL_H__
#include "eve/ogl/core/External.h"
#endif

#ifndef __EVE_OPENGL_CORE_EXTERNAL_H__
#include "eve/ogl/core/External.h"
#endif

#ifndef __EVE_OPENGL_PARTICULE_ATTRACTOR_MODEL_H__
#include "eve/ogl/particule/AttractorModel.h"
#endif

#ifndef __EVE_OPENGL_PARTICULE_IATTRACTOR_UPDATE_H__
#include "eve/ogl/particule/IAttractorUpdate.h"
#endif

namespace eve
{
	namespace ogl
	{

		template <class Matrix, class Vector, class Value>
		class Attractor{
		private:
			IAttractorUpdate<Matrix, Vector, Value> *	m_updateStrategy;
			AttractorModel<Vector, Value> *				m_attModel;

		public:
			Attractor(void)
				: m_updateStrategy(nullptr)
				, m_attModel(new AttractorModel<Vector, Value>())
			{

			}

			Attractor(IAttractorUpdate<Matrix, Vector, Value>* attUpdate)
				: m_updateStrategy(attUpdate)
				, m_attModel(new AttractorModel<Vector, Value>())
			{

			}

			Attractor(IAttractorUpdate<Matrix, Vector, Value>* attUpdate, Value x, Value y, Value z)
				: m_updateStrategy(attUpdate)
				, m_attModel(new AttractorModel<Vector, Value>(x, y, z))
			{

			}

			Attractor(IAttractorUpdate<Matrix, Vector, Value>* attUpdate, Vector position)
				: m_updateStrategy(attUpdate)
				, m_attModel(new AttractorModel<Vector, Value>(position))
			{

			}

			~Attractor()
			{
			}

			void updateAttractor(eve::math::TCamera<float>* camera, eve::math::TVec2<float> input)
			{
				m_updateStrategy->updateAttractor(m_attModel, camera, input);
			}

			void setUpdateStrategy(IAttractorUpdate<Matrix, Vector, Value> * attUpdate)
			{
				m_updateStrategy = attUpdate;
			}

			Vector getAttractorPos()
			{
				return m_attModel->getPosition();
			}

			void incrementDepth(float inc)
			{
				m_attModel->incrementDepth(inc);
			}

			float getDepth()
			{
				return m_attModel->getDepth();
			}

			void setStrategy(IAttractorUpdate<Matrix, Vector, Value>* p_attUpdate)
			{
				m_updateStrategy = p_attUpdate;
			}

			IAttractorUpdate<Matrix, Vector, Value>* getStrategy(void)
			{
				return m_updateStrategy;
			}

		};

	} // namespace ogl

} // namespace eve


#endif