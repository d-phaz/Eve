
#pragma once
#ifndef __EVE_EVT_EVENT_H__ 
#define __EVE_EVT_EVENT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_EVT_TEVENT_H__
#include "eve/evt/TEvent.h"
#endif

#ifndef __EVE_EVT_SERVER_H__
#include "eve/evt/Server.h"
#endif


namespace eve
{
	namespace evt
	{


	} // namespace evt

} // namespace eve







namespace eve {
namespace evt{


	class EventListenner;

	/** @class eve::evt::Args
	* This is used to pass the data when notifying events.
	*/
	class Args 
	{};


	class KeyEventArgs 
		: public eve::evt::Args 
	{
	public:
		enum Type{
			Pressed,
			Released,
			TextInput
		} type;

		uint8_t		key;
	};


	class MouseEventArgs 
		: public eve::evt::Args 
	{
	public:
		enum Type{
			Pressed,
			Released,
			DoubleClick,
			Motion,
			PassiveMotion
		} type;

		int32_t		button;
		int32_t		x;
		int32_t		y;
	};


	class ResizeEventArgs 
		: public eve::evt::Args 
	{
	public:
		int32_t width;
		int32_t height;
	};


	class TouchEventArgs 
		: public eve::evt::Args 
	{
	public:
		enum Type{
			down,
			up,
			move,
			doubleTap,
			cancel
		} type;

		int32_t		id;
		int32_t		time;
		int32_t		numTouches;
		float		width;
		float		height;
		float		angle;
		float		minoraxis;
		float		majoraxis;
		float		pressure;
		float		xspeed;
		float		yspeed;
		float		xaccel;
		float		yaccel;
	};


	class CoreEvents
	{
	public:
		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyPressed;
		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		keyReleased;
		static eve::evt::TEvent<eve::evt::KeyEventArgs> 		textInput;

		static eve::evt::TEvent<eve::evt::MouseEventArgs> 	mousePassiveMotion;
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 	mouseMotion;
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 	mouseDown;
		static eve::evt::TEvent<eve::evt::MouseEventArgs>		mouseDoubleClick;
		static eve::evt::TEvent<eve::evt::MouseEventArgs> 	mouseUp;
		static eve::evt::TEvent<eve::evt::Args>				mouseEnter;
		static eve::evt::TEvent<eve::evt::Args>				mouseLeave;

		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDown;
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchUp;
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchMoved;
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchDoubleTap;
		static eve::evt::TEvent<eve::evt::TouchEventArgs>		touchCancelled;

		static eve::evt::TEvent<eve::evt::ResizeEventArgs> 	windowResized;

		static eve::evt::TEvent<void>					focusGot;
		static eve::evt::TEvent<void>					focusLost;

		static eve::evt::TEvent<void>					idle;
		static eve::evt::TEvent<void>					display;

		static eve::evt::TEvent<void>					close;

		static eve::evt::TEvent<void>					applicationExit;


		/** \! Disable core events dispatch. */
		static void disable( void );
		/** \! Enable core events dispatch. */
		static void enable( void );
	};


	///////////////////////////////////////////////////////////////////////////////////////////////
	//		REGISTER TO EVENTS
	///////////////////////////////////////////////////////////////////////////////////////////////

	//=============================================================================================
	template<class ListenerClass>
	void register_key_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::keyPressed,	listener, &ListenerClass::cb_evtKeyboardDown, prio );
		eve::evt::add_listener( CoreEvents::keyReleased,	listener, &ListenerClass::cb_evtKeyboardUp, prio );
		eve::evt::add_listener( CoreEvents::textInput,	listener, &ListenerClass::cb_evtTextInput, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_mouse_events(ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::mouseDown,			listener, &ListenerClass::cb_evtMouseDown, prio );
		eve::evt::add_listener( CoreEvents::mouseUp,				listener, &ListenerClass::cb_evtMouseUp, prio );
		eve::evt::add_listener( CoreEvents::mouseDoubleClick,	listener, &ListenerClass::cb_evtMouseDoubleClick, prio );
		eve::evt::add_listener( CoreEvents::mouseMotion,			listener, &ListenerClass::cb_evtMotion, prio );
		eve::evt::add_listener( CoreEvents::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion, prio );
	}

	////=============================================================================================
	//template<class ListenerClass>
	//void register_touch_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	//{
	//	eve::evt::add_listener( CoreEvents::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio );
	//	eve::evt::add_listener( CoreEvents::touchDown,		listener, &ListenerClass::cb_evtTouchDown, prio );
	//	eve::evt::add_listener( CoreEvents::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved, prio );
	//	eve::evt::add_listener( CoreEvents::touchUp,			listener, &ListenerClass::cb_evtTouchUp, prio );
	//}

	//=============================================================================================
	template<class ListenerClass>
	void register_window_resize_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::windowResized, listener, &ListenerClass::cb_evtReshape, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_focus_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::focusGot, listener, &ListenerClass::cb_evtFocusGot, prio );
		eve::evt::add_listener( CoreEvents::focusLost, listener, &ListenerClass::cb_evtFocusLost, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_close_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::close, listener, &ListenerClass::cb_evtClose, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_idle_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::idle, listener, &ListenerClass::cb_evtIdle, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_display_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::display, listener, &ListenerClass::cb_evtDisplay, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_application_exit_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::add_listener( CoreEvents::applicationExit, listener, &ListenerClass::cb_evtAppExit, prio );
	}



	///////////////////////////////////////////////////////////////////////////////////////////////
	//		UNREGISTER FROM EVENTS
	///////////////////////////////////////////////////////////////////////////////////////////////

	//=============================================================================================
	template<class ListenerClass>
	void unregister_key_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::keyPressed,	listener, &ListenerClass::cb_evtKeyboardDown, prio );
		eve::evt::remove_listener( CoreEvents::keyReleased,	listener, &ListenerClass::cb_evtKeyboardUp, prio );
		eve::evt::remove_listener( CoreEvents::textInput,	listener, &ListenerClass::cb_evtTextInput, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_mouse_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::mouseDown,			listener, &ListenerClass::cb_evtMouseDown, prio );
		eve::evt::remove_listener( CoreEvents::mouseUp,				listener, &ListenerClass::cb_evtMouseUp, prio );
		eve::evt::remove_listener( CoreEvents::mouseDoubleClick,		listener, &ListenerClass::cb_evtMouseDoubleClick, prio );
		eve::evt::remove_listener( CoreEvents::mouseMotion,			listener, &ListenerClass::cb_evtMotion, prio );
		eve::evt::remove_listener( CoreEvents::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion, prio );
	}

	////=============================================================================================
	//template<class ListenerClass>
	//void unregister_touch_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	//{
	//	eve::evt::remove_listener( CoreEvents::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio );
	//	eve::evt::remove_listener( CoreEvents::touchDown,		listener, &ListenerClass::cb_evtTouchDown, prio );
	//	eve::evt::remove_listener( CoreEvents::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved, prio );
	//	eve::evt::remove_listener( CoreEvents::touchUp,			listener, &ListenerClass::cb_evtTouchUp, prio );
	//}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_window_resize_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::windowResized, listener, &ListenerClass::cb_evtReshape, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_focus_events( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::focusGot, listener, &ListenerClass::cb_evtFocusGot, prio );
		eve::evt::remove_listener( CoreEvents::focusLost, listener, &ListenerClass::cb_evtFocusLost, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_close_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::close, listener, &ListenerClass::cb_evtClose, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_idle_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::idle, listener, &ListenerClass::cb_evtIdle, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_display_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::display, listener, &ListenerClass::cb_evtDisplay, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_application_exit_event( ListenerClass * listener, int32_t prio=orderAfterApp  )
	{
		eve::evt::remove_listener( CoreEvents::applicationExit, listener, &ListenerClass::cb_evtAppExit, prio );
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Event notification
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	void notify_key_pressed( uint8_t key );
	void notify_key_released( uint8_t key );
	void notify_text_input( uint8_t key );
	void notify_key_event( const eve::evt::KeyEventArgs & p_args );

	void notify_mouse_down( int32_t button, int32_t x, int32_t y );
	void notify_mouse_up( int32_t button, int32_t x, int32_t y );
	void notify_mouse_double_click( int32_t button, int32_t x, int32_t y );
	void notify_mouse_motion( int32_t x, int32_t y );
	void notify_mouse_passive_motion( int32_t x, int32_t y );
	void notify_mouse_event( const eve::evt::MouseEventArgs & p_args );

	void notify_window_resize( uint32_t p_width, uint32_t p_height );
	void notify_window_resize_event( const eve::evt::ResizeEventArgs & p_args );

	void notify_focus_got( void );
	void notify_focus_lost( void );

	void notify_idle( void );

	void notify_display( void );

	void notify_close( void );

	void notify_app_exit( void );


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		controlEventType enum
	///////////////////////////////////////////////////////////////////////////////////////////////////

	enum controlEventType
	{
		undefinedEventType = 0,

		// Scene
		add_sceneFromPath,
		add_defaultLightArea,
		add_defaultLightDirectional,
		add_defaultLightPoint,
		add_defaultLightSpot,
		add_defaultCamera,
		add_meshFromPath,

		scene_activate,
		scene_release,

		// Texture properties
		addTextureEmptyEvent,
		addTextureFromPathEvent,
		addTextureVideoEvent,
		addTextureBitmapEvent,
		addTextureDecklinkEvent,
		addTextureSyphonEvent,
		removeTextureEvent,
		changeTextureRatioEvent,
		changeTextureRatioGlobalEvent,
		changeTextureRenderWidthEvent,
		changeTextureRenderHeightEvent,
		changeTextureScaleXEvent,
		changeTextureScaleYEvent,
		changeTextureTranslationXEvent,
		changeTextureTranslationYEvent,
		changeTextureRotationEvent,
		// video management
		changeVideoPause,
		changeVideoPauseAll,
		changeVideoPlayAll,
		changeVideoStop,
		changeVideoStopAll,
		changeVideoLoopState,
		changeVideoMute,
		changeVideoMuteAll,
		changeVideoFramePercent,
		changeVideoFrameFirstPercent,
		changeVideoFrameLastPercent,

		// DISPLAY OBJECT //
		changeObjectTranslationX,
		changeObjectTranslationY,
		changeObjectTranslationZ,
		changeObjectRotationX,
		changeObjectRotationY,
		changeObjectRotationZ,
		changeObjectScaleX,
		changeObjectScaleY,
		changeObjectScaleZ,
		changeObjectNormalsFlat,
		changeObjectNormalsSmooth,
		changeObjectVisibleState,

		// Material 
		changeMaterialDiffuse,
		changeMaterialSpecular,
		changeMaterialShininess,
		changeMaterialFresnelExponent,

		// Lighting properties
		changeHDRExposureEvent,
		changeHDRMaxBrightnessEvent,
		changeBlendModeEvent,

		// PROJECTOR //
		// Translation
		changeEventCameraPositionX,
		changeEventCameraPositionY,
		changeEventCameraPositionZ,
		// Rotation
		changeEventCameraRotationX,
		changeEventCameraRotationY,
		changeEventCameraRotationZ,
		// FOV
		changeEventCameraFOV,
		// Zoom
		changeEventCameraZoom,
		// AOV
		changeEventCameraAOV,
		// BSC
		changeEventCameraBrightness,
		changeEventCameraSaturation,
		changeEventCameraContrast,
		// Gamma
		changeEventCameraGamma,
		// Calibration
		changeEventCameraCalibrationTangeantDistortion,
		changeEventCameraCalibrationRadialDistortion,
		changeEventCameraCalibrationLensShift,
		changeEventCameraCalibrationSquarePixels,
		changeEventCameraCalibrationReset,
		// Warping
		changeEventCameraWarpSetSubdivisionActiveAxisBoth,
		changeEventCameraWarpSetSubdivisionActiveAxisHorizontal,
		changeEventCameraWarpSetSubdivisionActiveAxisVertical,
		changeEventCameraWarpGrid,
		changeEventCameraWarpReset,
		changeEventCameraWarpSetRealTimeMeshEditActiveState,
		// Blending
		changeEventCameraBlendReset,
		changeEventCameraBlendActiveStateTrue,
		changeEventCameraBlendActiveStateFalse,
		// Masking
		changeEventCameraMaskAddQuad,
		changeEventCameraMaskAddTriangle,
		changeEventCameraMaskRemove,
		changeEventCameraMaskReset,

		// LIGHTING //
		// Color
		changeEventLightColorRed,
		changeEventLightColorGreen,
		changeEventLightColorBlue,
		// Intensity
		changeEventLightIntensity,
		// Attenuation
		changeEventLightAttenuationConstant,
		changeEventLightAttenuationLinear,
		changeEventLightAttenuationQuadratic,
		// Shadow casting
		changeEventLightCastShadow,
		// Ambiant factor
		changeEventLightAmbiantFactor,
		changeEventLightAmbiantColor,
		changeEventLightAmbiantColorRed,
		changeEventLightAmbiantColorGreen,
		changeEventLightAmbiantColorBlue,
		// Exponent
		changeEventLightExponent,
		// Cut off (outer)
		changeEventLightCutOff,
		// Area size
		changeEventLightAreaWidth,
		changeEventLightAreaHeight,

		// POST PROD //

		// SSAO properties
		changeSSAOSampleRadiusEvent,
		changeSSAOIntensityEvent,
		changeSSAOScaleEvent,
		changeSSAOBiasEvent,
		changeSSAOJitterEvent,
		changeSSAOSelfOcclusionEvent,
		// SSAO Active
		changeSSAOActive,

		// DOF
		changeDofFocusEvent,
		changeDofAspectEvent,
		changeDofApertureEvent,
		changeDofMaxBlurEvent,
		// DOF active
		changeDofActive,

		// Blur
		changeHorizontalBlurAmountEvent,
		changeVerticalBlurAmountEvent,
		// Blur active
		changeBlurActive,


		// Windows Management
		createOutput
	};

} // namespace evt
}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		controlEventArgs class
	///////////////////////////////////////////////////////////////////////////////////////////////////

	class VideoPlayer;
	namespace gl { class TextureData; }

namespace eve {
namespace evt
{

	/**
	* @class controlEventArgs
	*
	* @brief base UIControl event args class
	*
	* @note extends eve::evt::Args
	*/
	class controlEventArgs : public eve::evt::Args
	{
	public:
		controlEventType	m_eventType;

		uint32_t			m_objectID;
		uint32_t			m_textureIndex;

		bool				m_status;

		float				m_valueFloat32;
		int32_t				m_valueSint32;

		uint32_t			m_valueUint32First;
		uint32_t			m_valueUint32Second;

		size_t				m_valueSize_t;

		// Windows args
		uint32_t			m_windowPositionX;
		uint32_t			m_windowPositionY;
		uint32_t			m_windowWidth;
		uint32_t			m_windowHeight;
	};

	typedef eve::evt::TEvent<controlEventArgs> controlEvent;



	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		EventListenner class
	///////////////////////////////////////////////////////////////////////////////////////////////////

	class EventListenner
	{
	public:
		EventListenner( void );
		virtual ~EventListenner( void );

		virtual void newControlEventMessage( eve::evt::controlEventArgs & p_eventArgs );
	};


} // namespace evt
}
#endif // __EVE_EVT_EVENT_H__
