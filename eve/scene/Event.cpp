
// Main header
#include "eve/scene/Event.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::EventArgsScene::EventArgsScene(void)
	: eve::evt::EventArgs()
	, type(SceneEventType_UNDEFINED)
	, path()
{}

//=================================================================================================
eve::scene::EventArgsScene::EventArgsScene(const eve::scene::EventArgsScene & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, path(p_other.path)
{}

//=================================================================================================
eve::scene::EventArgsScene & eve::scene::EventArgsScene::operator = (const eve::scene::EventArgsScene & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->path  = p_other.path;
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE OBJECT EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::EventArgsSceneObject::EventArgsSceneObject(void)
	: eve::evt::EventArgs()
	, type(SceneObjectEventType_UNDEFINED)
	, value()
{}

//=================================================================================================
eve::scene::EventArgsSceneObject::EventArgsSceneObject(const eve::scene::EventArgsSceneObject & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, value(p_other.value)
{}

//=================================================================================================
eve::scene::EventArgsSceneObject & eve::scene::EventArgsSceneObject::operator = (const eve::scene::EventArgsSceneObject & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->value = p_other.value;
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE CAMERA EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::EventArgsSceneCamera::EventArgsSceneCamera(void)
	: eve::evt::EventArgs()
	, type(SceneCameraEventType_UNDEFINED)
	, value()
{}

//=================================================================================================
eve::scene::EventArgsSceneCamera::EventArgsSceneCamera(const eve::scene::EventArgsSceneCamera & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, value(p_other.value)
{}

//=================================================================================================
eve::scene::EventArgsSceneCamera & eve::scene::EventArgsSceneCamera::operator = (const eve::scene::EventArgsSceneCamera & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->value = p_other.value;
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE LIGHT EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::EventArgsSceneLight::EventArgsSceneLight(void)
	: eve::evt::EventArgs()
	, type(SceneLightEventType_UNDEFINED)
	, valueFloat(0.0f)
	, valueBool(false)
{}

//=================================================================================================
eve::scene::EventArgsSceneLight::EventArgsSceneLight(const eve::scene::EventArgsSceneLight & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, valueFloat(p_other.valueFloat)
	, valueBool(p_other.valueBool)
{}

//=================================================================================================
eve::scene::EventArgsSceneLight & eve::scene::EventArgsSceneLight::operator = (const eve::scene::EventArgsSceneLight & p_other)
{
	this->time		 = p_other.time;
	this->type		 = p_other.type;
	this->valueFloat = p_other.valueFloat;
	this->valueBool  = p_other.valueBool;
	return *this;
}
