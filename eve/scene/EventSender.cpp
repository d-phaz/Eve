
// Main header
#include "eve/scene/EventSender.h"


//=================================================================================================
eve::scene::EventSenderScene::EventSenderScene(void)
	: m_evt()
{}

//=================================================================================================
void eve::scene::EventSenderScene::addListener(eve::scene::EventListenerScene * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::add_listener(m_evt, p_pListener, &eve::scene::EventListenerScene::cb_evtScene);
}

//=================================================================================================
void eve::scene::EventSenderScene::removeListener(eve::scene::EventListenerScene * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::remove_listener(m_evt, p_pListener, &eve::scene::EventListenerScene::cb_evtScene);
}

//=================================================================================================
void eve::scene::EventSenderScene::notify(eve::scene::EventTypeScene p_type)
{
	eve::scene::EventArgsScene args;
	args.type = p_type;

	eve::evt::notify_event(m_evt, args);
}

//=================================================================================================
void eve::scene::EventSenderScene::notify(eve::scene::EventTypeScene p_type, const std::wstring & p_path)
{
	eve::scene::EventArgsScene args;
	args.type = p_type;
	args.path = p_path;

	eve::evt::notify_event(m_evt, args);
}



//=================================================================================================
eve::scene::EventSenderSceneObject::EventSenderSceneObject(void)
	: m_evt()
{}

//=================================================================================================
void eve::scene::EventSenderSceneObject::addListener(eve::scene::EventListenerSceneObject * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::add_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneObject::cb_evtSceneObject);
}

//=================================================================================================
void eve::scene::EventSenderSceneObject::removeListener(eve::scene::EventListenerSceneObject * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::remove_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneObject::cb_evtSceneObject);
}

//=================================================================================================
void eve::scene::EventSenderSceneObject::notify(eve::scene::EventTypeSceneObject p_type, float p_value)
{
	eve::scene::EventArgsSceneObject args;
	args.type  = p_type;
	args.value = p_value;

	eve::evt::notify_event(m_evt, args);
}



//=================================================================================================
eve::scene::EventSenderSceneMaterial::EventSenderSceneMaterial(void)
	: m_evt()
{}

//=================================================================================================
void eve::scene::EventSenderSceneMaterial::addListener(eve::scene::EventListenerSceneMaterial * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::add_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneMaterial::cb_evtSceneMaterial);
}

//=================================================================================================
void eve::scene::EventSenderSceneMaterial::removeListener(eve::scene::EventListenerSceneMaterial * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::remove_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneMaterial::cb_evtSceneMaterial);
}

//=================================================================================================
void eve::scene::EventSenderSceneMaterial::notify(eve::scene::EventTypeSceneMaterial p_type, float p_value)
{
	eve::scene::EventArgsSceneMaterial args;
	args.type  = p_type;
	args.value = p_value;

	eve::evt::notify_event(m_evt, args);
}



//=================================================================================================
eve::scene::EventSenderSceneCamera::EventSenderSceneCamera(void)
	: m_evt()
{}

//=================================================================================================
void eve::scene::EventSenderSceneCamera::addListener(eve::scene::EventListenerSceneCamera * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::add_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneCamera::cb_evtSceneCamera);
}

//=================================================================================================
void eve::scene::EventSenderSceneCamera::removeListener(eve::scene::EventListenerSceneCamera * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::remove_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneCamera::cb_evtSceneCamera);
}

//=================================================================================================
void eve::scene::EventSenderSceneCamera::notify(eve::scene::EventTypeSceneCamera p_type, float p_value)
{
	eve::scene::EventArgsSceneCamera args;
	args.type  = p_type;
	args.value = p_value;

	eve::evt::notify_event(m_evt, args);
}



//=================================================================================================
eve::scene::EventSenderSceneLight::EventSenderSceneLight(void)
	: m_evt()
{}

//=================================================================================================
void eve::scene::EventSenderSceneLight::addListener(eve::scene::EventListenerSceneLight * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::add_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneLight::cb_evtSceneLight);
}

//=================================================================================================
void eve::scene::EventSenderSceneLight::removeListener(eve::scene::EventListenerSceneLight * p_pListener)
{
	EVE_ASSERT(p_pListener);
	eve::evt::remove_listener(m_evt, p_pListener, &eve::scene::EventListenerSceneLight::cb_evtSceneLight);
}

//=================================================================================================
void eve::scene::EventSenderSceneLight::notify(eve::scene::EventTypeSceneLight p_type, float p_value)
{
	eve::scene::EventArgsSceneLight args;
	args.type		= p_type;
	args.valueFloat = p_value;

	eve::evt::notify_event(m_evt, args);
}

//=================================================================================================
void eve::scene::EventSenderSceneLight::notify(eve::scene::EventTypeSceneLight p_type, bool p_value)
{
	eve::scene::EventArgsSceneLight args;
	args.type		= p_type;
	args.valueBool	= p_value;

	eve::evt::notify_event(m_evt, args);
}

//=================================================================================================
void eve::scene::EventSenderSceneLight::notify(eve::scene::EventTypeSceneLight p_type, float p_valueFloat, bool p_valueBool)
{
	eve::scene::EventArgsSceneLight args;
	args.type		= p_type;
	args.valueFloat = p_valueFloat;
	args.valueBool  = p_valueBool;

	eve::evt::notify_event(m_evt, args);
}
