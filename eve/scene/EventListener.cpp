
// Main header
#include "eve/scene/EventListener.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::SceneEventArgs::SceneEventArgs(void)
	: eve::evt::EventArgs()
	, type(SceneEventType_UNDEFINED)
	, path()
{}

//=================================================================================================
eve::scene::SceneEventArgs::SceneEventArgs(const eve::scene::SceneEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, path(p_other.path)
{}

//=================================================================================================
eve::scene::SceneEventArgs & eve::scene::SceneEventArgs::operator = (const eve::scene::SceneEventArgs & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->path  = p_other.path;
	return *this;
}

//=================================================================================================
eve::scene::SceneEventListener::SceneEventListener(void)
	: eve::evt::Listener()
{}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE OBJECT EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::SceneObjectEventArgs::SceneObjectEventArgs(void)
	: eve::evt::EventArgs()
	, type(SceneObjectEventType_UNDEFINED)
	, value()
{}

//=================================================================================================
eve::scene::SceneObjectEventArgs::SceneObjectEventArgs(const eve::scene::SceneObjectEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, value(p_other.value)
{}

//=================================================================================================
eve::scene::SceneObjectEventArgs & eve::scene::SceneObjectEventArgs::operator = (const eve::scene::SceneObjectEventArgs & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->value = p_other.value;
	return *this;
}

//=================================================================================================
eve::scene::SceneObjectEventListener::SceneObjectEventListener(void)
	: eve::evt::Listener()
{}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE CAMERA EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::SceneCameraEventArgs::SceneCameraEventArgs(void)
	: eve::evt::EventArgs()
	, type(SceneCameraEventType_UNDEFINED)
	, value()
{}

//=================================================================================================
eve::scene::SceneCameraEventArgs::SceneCameraEventArgs(const eve::scene::SceneCameraEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, value(p_other.value)
{}

//=================================================================================================
eve::scene::SceneCameraEventArgs & eve::scene::SceneCameraEventArgs::operator = (const eve::scene::SceneCameraEventArgs & p_other)
{
	this->time	= p_other.time;
	this->type  = p_other.type;
	this->value = p_other.value;
	return *this;
}

//=================================================================================================
eve::scene::SceneCameraEventListener::SceneCameraEventListener(void)
	: eve::evt::Listener()
{}



///////////////////////////////////////////////////////////////////////////////////////////////////
//		SCENE LIGHT EVENT
///////////////////////////////////////////////////////////////////////////////////////////////////

//=================================================================================================
eve::scene::SceneLightEventArgs::SceneLightEventArgs(void)
	: eve::evt::EventArgs()
	, type(SceneLightEventType_UNDEFINED)
	, valueFloat(0.0f)
	, valueBool(false)
{}

//=================================================================================================
eve::scene::SceneLightEventArgs::SceneLightEventArgs(const eve::scene::SceneLightEventArgs & p_other)
	: eve::evt::EventArgs(p_other)
	, type(p_other.type)
	, valueFloat(p_other.valueFloat)
	, valueBool(p_other.valueBool)
{}

//=================================================================================================
eve::scene::SceneLightEventArgs & eve::scene::SceneLightEventArgs::operator = (const eve::scene::SceneLightEventArgs & p_other)
{
	this->time		 = p_other.time;
	this->type		 = p_other.type;
	this->valueFloat = p_other.valueFloat;
	this->valueBool  = p_other.valueBool;
	return *this;
}

//=================================================================================================
eve::scene::SceneLightEventListener::SceneLightEventListener(void)
	: eve::evt::Listener()
{}
