#ifndef _GLMATTRACTORUPDATE_
#define _GLMATTRACTORUPDATE_

#define GLM_FORCE_RADIANS

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif

#ifndef __EVE_MATH_CORE_TMATRIX_H__
#include "eve/math/core/TMatrix.h"
#endif

#ifndef __EVE_MATH_CORE_MATH_H__
#include "eve/math/core/Math.h"
#endif

namespace eve
{
	namespace ogl
	{

		class RayCastAttractorUpdate : public IAttractorUpdate < eve::math::TMatrix44<float>, eve::math::TVec4<float>, float >
		{
		private:
			float m_fovYRad;
			float m_nearClipDistance;
			float m_width, m_height;
			float m_hLength, m_vLength;

		public:
			RayCastAttractorUpdate(){}

			~RayCastAttractorUpdate(){}

			void initAttractor(int width, int height, float fovYDeg, float nearClipDistance)
			{
				m_width = static_cast<float>(width);
				m_height = static_cast<float>(height);
				m_nearClipDistance = nearClipDistance;
				m_fovYRad = fovYDeg * M_PI / 180.f;
				m_vLength = eve::math::tan(m_fovYRad / 2)*nearClipDistance;
				m_hLength = m_vLength * ((float)(width) / (float)(height));
			}

			/** Performs ray casting to update the attractor
			**/
			virtual void updateAttractor(AttractorModel<eve::math::TVec4<float>, float>* attModel, eve::math::TCamera<float>* camera, eve::math::TVec2<float> input){
				eve::math::TVec3<float> view, h, v, pos, dir, attractor;

				attractor = eve::math::TVec3<float>(0.0f);

				//Compute the coordinate axes
				view = eve::math::TVec3<float>(camera->getDirection());
				h = eve::math::TVec3<float>(camera->getRight());
				v = eve::math::TVec3<float>(camera->getUp());

				//Scale them
				h *= m_hLength;
				v *= m_vLength;

				float mouseX = (float)(input.x - (m_width / 2.0f) / (m_width / 2.0f)) / m_width;	//Map the coordinate to [-1, 1]
				float mouseY = (float)(input.y - (m_height / 2.0f) / (m_height / 2.0f)) / m_height; //Map the coordinate to [-1, 1]

				//Compute the intersection with the near plane
				pos = eve::math::TVec3<float>(camera->getTranslation()) + view*m_nearClipDistance + h*mouseX - v*mouseY;
				//Compute the direction of the ray
				dir = eve::math::TVec3<float>::normalize(eve::math::TVec3<float>(camera->getTranslation()) - pos);

				//Shoot attractor along the ray to the given depth
				attractor = pos + dir * (float)attModel->getDepth();

				//Update attractor
				attModel->setPosition(eve::math::TVec4<float>(attractor, 1.0f));

			}
		};

	} // namespace ogl

} // namespace eve

#endif