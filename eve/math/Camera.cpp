
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
#include "eve/math/Camera.h"


//=================================================================================================
eve::math::Camera * eve::math::Camera::create_ptr(float p_width, float p_height, float p_near, float p_far, float p_fov)
{
	eve::math::Camera * ptr = new eve::math::Camera(p_width, p_height, p_near, p_far, p_fov);
	ptr->initDefault();
	return ptr;
}

//=================================================================================================
eve::math::Camera * eve::math::Camera::create_ptr(const Camera & p_parent)
{
	eve::math::Camera * ptr = new eve::math::Camera(p_parent);
	return ptr;
}



//=================================================================================================
eve::math::Camera::Camera(float p_width, float p_height, float p_near, float p_far, float p_fov)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_width(p_width)
	, m_height(p_height)

	, m_eyePoint(eve::vec3f::zero())
	, m_target(eve::vec3f::zero())
	, m_worldUp(eve::vec3f::zero())

	, m_viewDirection(eve::vec3f::zero())
	, m_orientation(eve::quatf::identity())
	, m_centerOfInterest(0.0f)

	, m_fov(p_fov)
	, m_aspectRatio(0.0f)
	, m_nearClip(p_near)
	, m_farClip(p_far)
	, m_frustumDepth(0.0f)
	, m_lensShift(eve::vec2f::zero())

	, m_U(eve::vec3f::xAxis())
	, m_V(eve::vec3f::yAxis())
	, m_W(eve::vec3f::zero())

	, m_matrixProjection(eve::mat44f::zero())
	, m_matrixProjectionInverse(eve::mat44f::zero())
	, m_matrixModelView(eve::mat44f::zero())
	, m_matrixModelViewInverse(eve::mat44f::zero())
	, m_matrixModelViewProjection(eve::mat44f::zero())
	, m_matrixViewport(eve::mat44f::zero())

	, m_frustumLeft(0.0f)
	, m_frustumRight(0.0f)
	, m_frustumTop(0.0f)
	, m_frustumBottom(0.0f)
{}

//=================================================================================================
eve::math::Camera::Camera(const Camera & p_parent)
	// Inheritance
	: eve::mem::Pointer()

	// Members init
	, m_width(p_parent.m_width)
	, m_height(p_parent.m_height)

	, m_eyePoint(p_parent.m_eyePoint)
	, m_target(p_parent.m_target)
	, m_worldUp(p_parent.m_worldUp)

	, m_viewDirection(p_parent.m_viewDirection)
	, m_orientation(p_parent.m_orientation)
	, m_centerOfInterest(p_parent.m_centerOfInterest)

	, m_fov(p_parent.m_fov)
	, m_aspectRatio(p_parent.m_aspectRatio)
	, m_nearClip(p_parent.m_nearClip)
	, m_farClip(p_parent.m_farClip)
	, m_frustumDepth(p_parent.m_frustumDepth)
	, m_lensShift(p_parent.m_lensShift)

	, m_U(p_parent.m_U)
	, m_V(p_parent.m_V)
	, m_W(p_parent.m_W)

	, m_matrixProjection(p_parent.m_matrixProjection)
	, m_matrixProjectionInverse(p_parent.m_matrixProjectionInverse)
	, m_matrixModelView(p_parent.m_matrixModelView)
	, m_matrixModelViewInverse(p_parent.m_matrixModelViewInverse)
	, m_matrixModelViewProjection(p_parent.m_matrixModelViewProjection)
	, m_matrixViewport(p_parent.m_matrixViewport)

	, m_frustumLeft(p_parent.m_frustumLeft)
	, m_frustumRight(p_parent.m_frustumRight)
	, m_frustumTop(p_parent.m_frustumTop)
	, m_frustumBottom(p_parent.m_frustumBottom)
{}



//=================================================================================================
void eve::math::Camera::initDefault(void)
{
	// Default values.
	m_aspectRatio		= m_width/m_height;
	m_frustumDepth		= m_farClip - m_nearClip;

	m_eyePoint.x		= 10.0f;
	m_eyePoint.y		= 10.0f;
	m_eyePoint.z		= 10.0f;

	m_worldUp.x			= 0.0f;
	m_worldUp.y			= 1.0f;
	m_worldUp.z			= 0.0f;	

	m_target.x			= 0.0f;
	m_target.y			= 0.0f;
	m_target.z			= 0.0f;

	m_viewDirection		= (m_target - m_eyePoint).normalized();
	m_orientation		= eve::quatf( eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp) ).normalized();
	m_centerOfInterest	= m_eyePoint.distance( m_target );

	// Members init.
	this->init();
}



//=================================================================================================
void eve::math::Camera::init(void)
{
// 	// Test values.
// 	if (m_aspectRatio < 0.000001f) {
// 		m_aspectRatio = m_width / m_height;
// 	}

// 	// Init matrices.
// 	m_matrixProjection.setToNull();
// 	m_matrixProjectionInverse.setToNull();
// 	m_matrixModelView.setToNull();
// 	m_matrixModelViewInverse.setToNull();
// 	m_matrixModelViewProjection.setToNull();
// 	m_matrixViewport.setToIdentity();


	// Compute matrices.
	this->calcMatrices();
	this->calcViewportMatrix();
}

//=================================================================================================
void eve::math::Camera::release(void)
{
	// Nothing to do for now.
}



//=================================================================================================
void eve::math::Camera::calcMatrices(void) const
{
	this->calcProjection();
	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::calcModelView(void) const
{
	m_W = -m_viewDirection.normalized();
	m_U = m_orientation * eve::vec3f::xAxis();
	m_V = m_orientation * eve::vec3f::yAxis();

	eve::vec3f d(-m_eyePoint.dot(m_U), -m_eyePoint.dot(m_V), -m_eyePoint.dot(m_W));
	float * m = m_matrixModelView.m;
	m[0] = m_U.x;		m[4] = m_U.y;		m[8] = m_U.z;		m[12] = d.x;
	m[1] = m_V.x;		m[5] = m_V.y;		m[9] = m_V.z;		m[13] = d.y;
	m[2] = m_W.x;		m[6] = m_W.y;		m[10] = m_W.z;		m[14] = d.z;
	/*m[ 3] = 0.0f;		m[ 7] = 0.0f;		m[11] = 0.0f;*/		m[15] = 1.0f;

	// Update inverse model view matrix
	m_matrixModelViewInverse = m_matrixModelView.inverted();

	// Update MVP
	m_matrixModelViewProjection = m_matrixProjection * m_matrixModelView;
}

//=================================================================================================
void eve::math::Camera::calcProjection(void) const
{
	m_frustumTop = m_nearClip * eve::math::tan((float)M_PI / 180.0f * m_fov * 0.5f);
	m_frustumBottom = -m_frustumTop;
	m_frustumRight = m_frustumTop * m_aspectRatio;
	m_frustumLeft = -m_frustumRight;

	// Perform lens shift
	if (m_lensShift.x != 0.0f)
	{
		m_frustumRight = eve::math::lerp(2.0f * m_frustumRight, 0.0f, 0.5f - 0.5f * m_lensShift.x);
		m_frustumRight = eve::math::lerp(0.0f, 2.0f * m_frustumLeft, 0.5f - 0.5f * m_lensShift.x);
	}
	if (m_lensShift.y != 0.0f)
	{
		m_frustumTop	= eve::math::lerp(0.0f, 2.0f * m_frustumTop, 0.5f + 0.5f * m_lensShift.y);
		m_frustumBottom = eve::math::lerp(2.0f * m_frustumBottom, 0.0f, 0.5f + 0.5f * m_lensShift.y);
	}

	float *m = m_matrixProjection.m;
	m[0] = 2.0f * m_nearClip / (m_frustumRight - m_frustumLeft);
	//m[ 4] =  0.0f;
	m[8] = (m_frustumRight + m_frustumLeft) / (m_frustumRight - m_frustumLeft);
	//m[12] =  0.0f;

	//m[ 1] =  0.0f;
	m[5] = 2.0f * m_nearClip / (m_frustumTop - m_frustumBottom);
	m[9] = (m_frustumTop + m_frustumBottom) / (m_frustumTop - m_frustumBottom);
	//m[13] =  0.0f;

	//m[ 2] =  0.0f;
	//m[ 6] =  0.0f;
	m[10] = -(m_farClip + m_nearClip) / (m_farClip - m_nearClip);
	m[14] = -(2.0f * m_farClip * m_nearClip) / (m_farClip - m_nearClip);

	//m[ 3] =  0.0f;
	//m[ 7] =  0.0f;
	m[11] = -1.0f;
	//m[15] =  0.0f;


	m = m_matrixProjectionInverse.m;
	m[0] = (m_frustumRight - m_frustumLeft) / (2.0f * m_nearClip);
	//m[ 4] =  0.0f;
	//m[ 8] =  0.0f;
	m[12] = (m_frustumRight + m_frustumLeft) / (2.0f * m_nearClip);

	//m[ 1] =  0.0f;
	m[5] = (m_frustumTop - m_frustumBottom) / (2.0f * m_nearClip);
	//m[ 9] =  0.0f;
	m[13] = (m_frustumTop + m_frustumBottom) / (2.0f * m_nearClip);

	//m[ 2] =  0.0f;
	//m[ 6] =  0.0f;
	//m[10] =  0.0f;
	m[14] = -1.0f;

	//m[ 3] =  0.0f;
	//m[ 7] =  0.0f;
	m[11] = -(m_farClip - m_nearClip) / (2.0f * m_farClip*m_nearClip);
	m[15] = (m_farClip + m_nearClip) / (2.0f * m_farClip*m_nearClip);
}

//=================================================================================================
void eve::math::Camera::calcViewportMatrix(void)
{
	//float halfWidth  = m_width / 2.0f;
	//float halfHeight = m_height / 2.0f;

	//eve::mat44f * m = &m_matrixViewport;
	////m[ 0] = halfWidth;	m[ 4] = 0.0f;			m[ 8] = 0.0f;		m[12] = 0.0f;
	////m[ 1] = 0.0f;			m[ 5] = halfHeight;		m[ 9] = 0.0f;		m[13] = 0.0f;
	////m[ 2] = 0.0f;			m[ 6] = 0.0f;			m[10] = 1.0f;		m[14] = 0.0f;
	////m[ 3] = halfWidth;	m[ 7] = halfHeight;		m[11] = 0.0f;		m[15] = 1.0f;

	//m[ 0] = halfWidth;		
	//m[ 5] = halfHeight;
	//m[ 3] = halfWidth;		
	//m[ 7] = halfHeight;

	m_matrixViewport = eve::mat44f::ortho(0.0f, m_width, m_height, 0.0f);
}



//=================================================================================================
void eve::math::Camera::lookAt(const eve::vec3f & p_target)
{
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::quatf(eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::lookAt(const eve::vec3f & p_eyePoint, const eve::vec3f & p_target)
{
	m_eyePoint		= p_eyePoint;
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::quatf(eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::lookAt(const eve::vec3f & p_eyePoint, const eve::vec3f & p_target, const eve::vec3f & p_up)
{
	m_eyePoint		= p_eyePoint;
	m_worldUp		= p_up.normalized();
	m_viewDirection = (p_target - m_eyePoint).normalized();
	m_orientation	= eve::quatf(eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}



//=================================================================================================
void eve::math::Camera::calibrateCamera(const eve::mat44f & p_matrixProjection, const eve::mat44f & p_matrixModelView)
{
	m_matrixProjection			= p_matrixProjection;
	m_matrixProjectionInverse	= m_matrixProjection.inverted();

	m_matrixModelView			= p_matrixModelView;
	m_matrixModelViewInverse	= m_matrixModelView.inverted();

	m_matrixModelViewProjection = m_matrixProjection * m_matrixModelView;
}

//=================================================================================================
void eve::math::Camera::releaseCalibration(void)
{
	this->calcMatrices();
}



//=================================================================================================
eve::rayf eve::math::Camera::generateRay(float p_uPos, float p_vPos, float p_imagePlaneAspectRatio) const
{
	float s = (p_uPos - 0.5f) * p_imagePlaneAspectRatio;
	float t = (p_vPos - 0.5f);
	float viewDistance = p_imagePlaneAspectRatio / eve::math::abs(m_frustumRight - m_frustumLeft) * m_nearClip;

	return eve::rayf(m_eyePoint, (m_U * s + m_V * t - (m_W * viewDistance)).normalized());
}

//=================================================================================================
eve::rayf eve::math::Camera::generateRay(float p_uPos, float p_vPos, float p_imagePlaneWidth, float p_imagePlaneHeight) const
{
	return this->generateRay(p_uPos, p_vPos, p_imagePlaneWidth / p_imagePlaneHeight);
}

//=================================================================================================
eve::rayf eve::math::Camera::generateRay(eve::vec2f p_pos, float p_imagePlaneWidth, float p_imagePlaneHeight) const
{
	return this->generateRay(p_pos.x, p_pos.y, p_imagePlaneWidth / p_imagePlaneHeight);
}



//=================================================================================================
eve::vec2f eve::math::Camera::worldToScreen(const eve::vec3f & p_worldCoord, float p_screenWidth, float p_screenHeight) const
{
	eve::vec3f eyeCoord = m_matrixModelView.transformPointAffine(p_worldCoord);
	eve::vec3f ndc		= m_matrixProjection.transformPoint(eyeCoord);

	return eve::vec2f((ndc.x + 1.0f) / 2.0f * p_screenWidth, (1.0f - (ndc.y + 1.0f) / 2.0f)*p_screenHeight);
}

//=================================================================================================
eve::vec3f eve::math::Camera::worldToEye(const eve::vec3f & p_worldCoord)
{
	return m_matrixModelView.transformPointAffine(p_worldCoord);
}

//=================================================================================================
float eve::math::Camera::worldToEyeDepth(const eve::vec3f & p_worldCoord) const
{
	return (m_matrixModelView.m[2] * p_worldCoord.x + m_matrixModelView.m[6] * p_worldCoord.y + m_matrixModelView.m[10] * p_worldCoord.z + m_matrixModelView.m[14]);
}

//=================================================================================================
eve::vec3f eve::math::Camera::worldToNdc(const eve::vec3f & p_worldCoord)
{
	eve::vec3f eye = m_matrixModelView.transformPointAffine(p_worldCoord);

	return m_matrixProjection.transformPoint(eye);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		MATRIX
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::math::Camera::translate(const eve::vec3f & p_translation)
{
	this->setEyePoint(m_eyePoint + p_translation);
}

//=================================================================================================
void eve::math::Camera::translateX(float p_translationX)
{
	this->setEyePointX(m_eyePoint.x + p_translationX);
}

//=================================================================================================
void eve::math::Camera::translateY(float p_translationY)
{
	this->setEyePointY(m_eyePoint.y + p_translationY);
}

//=================================================================================================
void eve::math::Camera::translateZ(float p_translationZ)
{
	this->setEyePointZ(m_eyePoint.z + p_translationZ);
}



//=================================================================================================
void eve::math::Camera::rotate(const eve::vec3f & p_rotation)
{
	eve::vec3f coi = getCenterOfInterestPoint() + p_rotation;
	this->lookAt(coi);
}

//=================================================================================================
void eve::math::Camera::rotateX(float p_rotationX)
{
	eve::vec3f coi = getCenterOfInterestPoint();
	coi.x += p_rotationX;
	this->lookAt(coi);
}

//=================================================================================================
void eve::math::Camera::rotateY(float p_rotationY)
{
	eve::vec3f coi = getCenterOfInterestPoint();
	coi.y += p_rotationY;
	this->lookAt(coi);
}

//=================================================================================================
void eve::math::Camera::rotateZ(float p_rotationZ)
{
	eve::vec3f coi = getCenterOfInterestPoint();
	coi.z += p_rotationZ;
	this->lookAt(coi);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		GET / SET
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
void eve::math::Camera::setEyePoint(const eve::vec3f & p_eyePoint)
{
	m_eyePoint = p_eyePoint;
	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setEyePointX(float p_eyePointX)
{
	m_eyePoint.x = p_eyePointX;
	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setEyePointY(float p_eyePointY)
{
	m_eyePoint.y = p_eyePointY;
	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setEyePointZ(float p_eyePointZ)
{
	m_eyePoint.z = p_eyePointZ;
	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setCenterOfInterest(float p_centerOfInterest)
{
	m_centerOfInterest = p_centerOfInterest;
}

//=================================================================================================
void eve::math::Camera::setCenterOfInterestPoint(const eve::vec3f & p_centerOfInterestPoint)
{
	m_centerOfInterest = m_eyePoint.distance(p_centerOfInterestPoint);
	this->lookAt(p_centerOfInterestPoint);
}

//=================================================================================================
void eve::math::Camera::setWorldUp(const eve::vec3f & p_worldUp)
{
	m_worldUp = p_worldUp.normalized();
	m_orientation = eve::quatf(eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp)).normalized();

	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setViewDirection(const eve::vec3f & p_viewDirection)
{
	m_viewDirection = p_viewDirection.normalized();
	m_orientation = eve::quatf(eve::vec3f(0.0f, 0.0f, -1.0f), m_viewDirection);

	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setOrientation(const eve::quatf & p_orientation)
{
	m_orientation = p_orientation.normalized();
	m_viewDirection = m_orientation * eve::vec3f(0.0f, 0.0f, -1.0f);

	this->calcModelView();
}

//=================================================================================================
void eve::math::Camera::setFov(float p_fov)
{
	m_fov = p_fov;
	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setAspectRatio(float p_aspectRatio)
{
	m_aspectRatio = p_aspectRatio;
	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setNearClip(float p_nearClip)
{
	m_nearClip = p_nearClip;
	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setFarClip(float p_farClip)
{
	m_farClip = p_farClip;
	this->calcProjection();
}



//=================================================================================================
void eve::math::Camera::getNearClipCoordinates(eve::vec3f * p_pTopLeft, eve::vec3f * p_pTopRight, eve::vec3f * p_pBottomLeft, eve::vec3f * p_pBottomRight) const
{
	eve::vec3f viewDirection(m_viewDirection.normalized());

	*p_pTopLeft		= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumTop * m_V) + (m_frustumLeft * m_U);
	*p_pTopRight	= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumTop * m_V) + (m_frustumRight * m_U);
	*p_pBottomLeft	= m_eyePoint + (m_nearClip * viewDirection) + (m_frustumBottom * m_V) + (m_frustumLeft * m_U);
	*p_pBottomRight = m_eyePoint + (m_nearClip * viewDirection) + (m_frustumBottom * m_V) + (m_frustumRight * m_U);
}

//=================================================================================================
void eve::math::Camera::getFarClipCoordinates(eve::vec3f * p_pTopLeft, eve::vec3f * p_pTopRight, eve::vec3f * p_pBottomLeft, eve::vec3f * p_pBottomRight) const
{
	eve::vec3f viewDirection(m_viewDirection.normalized());

	float ratio = m_farClip / m_nearClip;

	*p_pTopLeft		= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumTop * m_V) + (ratio * m_frustumLeft * m_U);
	*p_pTopRight	= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumTop * m_V) + (ratio * m_frustumRight * m_U);
	*p_pBottomLeft	= m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumBottom * m_V) + (ratio * m_frustumLeft * m_U);
	*p_pBottomRight = m_eyePoint + (m_farClip * viewDirection) + (ratio * m_frustumBottom * m_V) + (ratio * m_frustumRight * m_U);
}



//=================================================================================================
void eve::math::Camera::getFrustum(float * p_pLeft, float * p_pTop, float * p_pRight, float * p_pBottom, float * p_pNear, float * p_pFar) const
{
	*p_pLeft	= m_frustumLeft;
	*p_pTop		= m_frustumTop;
	*p_pRight	= m_frustumRight;
	*p_pBottom	= m_frustumBottom;
	*p_pNear	= m_nearClip;
	*p_pFar		= m_farClip;
}



//=================================================================================================
void eve::math::Camera::getBillboardVectors(eve::vec3f * p_pRight, eve::vec3f * p_pUp) const
{
	p_pRight->set(m_matrixModelView.m[0], m_matrixModelView.m[4], m_matrixModelView.m[8]);
	p_pUp->set(m_matrixModelView.m[1], m_matrixModelView.m[5], m_matrixModelView.m[9]);
}



//=================================================================================================
float eve::math::Camera::getDistanceInScene(const eve::vec3f & p_target)
{
	eve::vec4f temp = m_matrixModelView * eve::vec4f(p_target.x, p_target.y, p_target.z, 1.0f);

	float distance = eve::vec3f(temp.x, temp.y, temp.z).length();

	return distance;
}



//=================================================================================================
void eve::math::Camera::setPerspective(float p_horizFovDegrees, float p_aspectRatio, float p_nearPlane, float p_farPlane)
{
	m_fov			= p_horizFovDegrees;
	m_aspectRatio	= p_aspectRatio;
	m_nearClip		= p_nearPlane;
	m_farClip		= p_farPlane;

	this->calcProjection();
}



//=================================================================================================
void eve::math::Camera::setDisplaySize(float p_width, float p_height, bool p_bUpdateAspectRatio)
{
	m_width		= p_width;
	m_height	= p_height;

	if (p_bUpdateAspectRatio) 
	{
		this->setAspectRatio(m_width / m_height);
	}

	this->calcViewportMatrix();
}



//=================================================================================================
void eve::math::Camera::getLensShift(float * p_pHorizontal, float * p_pVertical) const
{
	*p_pHorizontal	= m_lensShift.x;
	*p_pVertical	= m_lensShift.y;
}

//=================================================================================================
void eve::math::Camera::setLensShift(float p_horizontal, float p_vertical)
{
	m_lensShift.x = p_horizontal;
	m_lensShift.y = p_vertical;

	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setLensShift(const eve::vec2f & p_shift)
{
	m_lensShift.x = p_shift.x;
	m_lensShift.y = p_shift.y;

	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setLensShiftHorizontal(float p_horizontal)
{
	m_lensShift.x = p_horizontal;
	this->calcProjection();
}

//=================================================================================================
void eve::math::Camera::setLensShiftVertical(float p_vertical)
{
	m_lensShift.y = p_vertical;
	this->calcProjection();
}




//=================================================================================================
// bool eve::math::Camera::initFromAssimpCamera( const aiCamera * pCamera, const aiScene * pScene, const eve::vec3f & p_upAxis )
// {
// #ifndef NDEBUG
// 	NATIVE_ASSERT( (pCamera!=NULL)	);
// 	NATIVE_ASSERT( (pScene!=NULL)	);
// #endif
// 
// 	// Create return value.
// 	bool breturn = (pCamera!=NULL) && (pScene!=NULL);
// 
// 	if( breturn )
// 	{
// 		// Stock item type.
// 		m_itemType		= Item_Camera;
// 		m_itemSubType	= Item_Camera_Simple;
// 
// 		// Stock ASSIMP pointer.
// 		m_pAiScene	= pScene;
// 		m_pAiCamera = pCamera;
// 
// 		// Loaded camera data copy.
// 		m_name				= std::string( m_pAiCamera->mName.data );
// 
// 		m_aspectRatio		= m_pAiCamera->mAspect;
// 		m_nearClip			= m_pAiCamera->mClipPlaneNear;
// 		m_farClip			= m_pAiCamera->mClipPlaneFar;
// 		m_frustumDepth		= m_farClip - m_nearClip;
// 		m_fov				= toDegrees( m_pAiCamera->mHorizontalFOV );
// 
// 		m_eyePoint.x		= m_pAiCamera->mPosition.x;
// 		m_eyePoint.y		= m_pAiCamera->mPosition.y;
// 		m_eyePoint.z		= m_pAiCamera->mPosition.z;
// 
// 		m_target.x			= m_pAiCamera->mLookAt.x;
// 		m_target.y			= m_pAiCamera->mLookAt.y;
// 		m_target.z			= m_pAiCamera->mLookAt.z;
// 
// 		m_worldUp.x			= m_pAiCamera->mUp.x;
// 		m_worldUp.y			= m_pAiCamera->mUp.y;
// 		m_worldUp.z			= m_pAiCamera->mUp.z;
// 
// 		// Find scene node 
// 		aiNode * pRoot = m_pAiScene->mRootNode;
// 		aiNode * pNode = pRoot->FindNode( m_name.c_str() );
// 		breturn = pNode!=NULL;
// 
// #ifndef NDEBUG
// 		NATIVE_ASSERT( breturn );
// #else
// 		if( breturn )
// #endif
// 		{
// 			// Compute scene node matrix 
// 			aiMatrix4x4 mat;
// 			while( pNode != pRoot )
// 			{
// 				mat = pNode->mTransformation * mat;
// 				pNode = pNode->mParent;
// 			}
// 
// 			//if( p_upAxis.z > 0.0f )
// 			//{
// 			//	aiMatrix4x4 aim;
// 			//	m_pAiCamera->GetCameraMatrix(aim);
// 			//	mat = aim * mat;
// 			//}
// 
// 			eve::mat44f matrix( mat.a1, mat.b1, mat.c1, mat.d1
// 							, mat.a2, mat.b2, mat.c2, mat.d2
// 							, mat.a3, mat.b3, mat.c3, mat.d3
// 							, mat.a4, mat.b4, mat.c4, mat.d4 );
// 
// 			// Correct Up Axis if needed.
// 			if( p_upAxis.z > 0.0f )
// 			{
// 				matrix.fromZupToYup();
// 			}
// 
// 			// Invert matrix to retrieve camera view coordinates.
// 			matrix.invert();
// 			
// 			// Extract camera data from model view matrix.
// 			matrix_algo::get_look_at( matrix, m_eyePoint, m_target, m_worldUp );
// 
// 			// Compute camera matrix required data.
// 			m_viewDirection		= (m_target - m_eyePoint).normalized();
// 			m_orientation		= eve::quatf( eve::mat44f::alignZAxisWithTarget(-m_viewDirection, m_worldUp) ).normalized();
// 			m_centerOfInterest	= m_eyePoint.distance( m_target );
// 			
// 		}
// 
// 		// Init all data.
// 		this->init();
// 	}
// 
// 	return breturn;
// }
