
#pragma once
#ifndef __EVT_EVENT_H__ 
#define __EVT_EVENT_H__


// External header
#include <cstdint>

// Event header
#ifndef __EVT_UTILS_H__
#include "evt/Utils.h"
#endif


namespace evt
{


	class EventListenner;

	/** @class evt::Args
	* This is used to pass the data when notifying events.
	*/
	class Args 
	{};


	class KeyEventArgs 
		: public evt::Args 
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
		: public evt::Args 
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
		: public evt::Args 
	{
	public:
		int32_t width;
		int32_t height;
	};


	class TouchEventArgs 
		: public evt::Args 
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
		static evt::TEvent<evt::KeyEventArgs> 		keyPressed;
		static evt::TEvent<evt::KeyEventArgs> 		keyReleased;
		static evt::TEvent<evt::KeyEventArgs> 		textInput;

		static evt::TEvent<evt::MouseEventArgs> 	mousePassiveMotion;
		static evt::TEvent<evt::MouseEventArgs> 	mouseMotion;
		static evt::TEvent<evt::MouseEventArgs> 	mouseDown;
		static evt::TEvent<evt::MouseEventArgs>		mouseDoubleClick;
		static evt::TEvent<evt::MouseEventArgs> 	mouseUp;
		static evt::TEvent<evt::Args>				mouseEnter;
		static evt::TEvent<evt::Args>				mouseLeave;

		static evt::TEvent<evt::TouchEventArgs>		touchDown;
		static evt::TEvent<evt::TouchEventArgs>		touchUp;
		static evt::TEvent<evt::TouchEventArgs>		touchMoved;
		static evt::TEvent<evt::TouchEventArgs>		touchDoubleTap;
		static evt::TEvent<evt::TouchEventArgs>		touchCancelled;

		static evt::TEvent<evt::ResizeEventArgs> 	windowResized;

		static evt::TEvent<void>					focusGot;
		static evt::TEvent<void>					focusLost;

		static evt::TEvent<void>					idle;
		static evt::TEvent<void>					display;

		static evt::TEvent<void>					close;

		static evt::TEvent<void>					applicationExit;


		static evt::TEvent<evt::ResizeEventArgs> 	pluginResized;
		static evt::TEvent<evt::ResizeEventArgs> 	setSizeDashboard;


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
	void register_key_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::keyPressed,	listener, &ListenerClass::cb_evtKeyboardDown, prio );
		evt::add_listener( CoreEvents::keyReleased,	listener, &ListenerClass::cb_evtKeyboardUp, prio );
		evt::add_listener( CoreEvents::textInput,	listener, &ListenerClass::cb_evtTextInput, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_mouse_events(ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::mouseDown,			listener, &ListenerClass::cb_evtMouseDown, prio );
		evt::add_listener( CoreEvents::mouseUp,				listener, &ListenerClass::cb_evtMouseUp, prio );
		evt::add_listener( CoreEvents::mouseDoubleClick,	listener, &ListenerClass::cb_evtMouseDoubleClick, prio );
		evt::add_listener( CoreEvents::mouseMotion,			listener, &ListenerClass::cb_evtMotion, prio );
		evt::add_listener( CoreEvents::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion, prio );
	}

	////=============================================================================================
	//template<class ListenerClass>
	//void register_touch_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	//{
	//	evt::add_listener( CoreEvents::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio );
	//	evt::add_listener( CoreEvents::touchDown,		listener, &ListenerClass::cb_evtTouchDown, prio );
	//	evt::add_listener( CoreEvents::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved, prio );
	//	evt::add_listener( CoreEvents::touchUp,			listener, &ListenerClass::cb_evtTouchUp, prio );
	//}

	//=============================================================================================
	template<class ListenerClass>
	void register_window_resize_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::windowResized, listener, &ListenerClass::cb_evtReshape, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_focus_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::focusGot, listener, &ListenerClass::cb_evtFocusGot, prio );
		evt::add_listener( CoreEvents::focusLost, listener, &ListenerClass::cb_evtFocusLost, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_close_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::close, listener, &ListenerClass::cb_evtClose, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_idle_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::idle, listener, &ListenerClass::cb_evtIdle, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_display_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::display, listener, &ListenerClass::cb_evtDisplay, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void register_application_exit_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::applicationExit, listener, &ListenerClass::cb_evtAppExit, prio );
	}




	//=============================================================================================
	template<class ListenerClass>
	void register_plugin_resize_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::pluginResized, listener, &ListenerClass::cb_evtResizePlugin, prio );
	}
	//=============================================================================================
	template<class ListenerClass>
	void register_set_size_dashboard_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::add_listener( CoreEvents::setSizeDashboard, listener, &ListenerClass::cb_evtSetSize, prio );
	}



	///////////////////////////////////////////////////////////////////////////////////////////////
	//		UNREGISTER FROM EVENTS
	///////////////////////////////////////////////////////////////////////////////////////////////

	//=============================================================================================
	template<class ListenerClass>
	void unregister_key_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::keyPressed,	listener, &ListenerClass::cb_evtKeyboardDown, prio );
		evt::remove_listener( CoreEvents::keyReleased,	listener, &ListenerClass::cb_evtKeyboardUp, prio );
		evt::remove_listener( CoreEvents::textInput,	listener, &ListenerClass::cb_evtTextInput, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_mouse_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::mouseDown,			listener, &ListenerClass::cb_evtMouseDown, prio );
		evt::remove_listener( CoreEvents::mouseUp,				listener, &ListenerClass::cb_evtMouseUp, prio );
		evt::remove_listener( CoreEvents::mouseDoubleClick,		listener, &ListenerClass::cb_evtMouseDoubleClick, prio );
		evt::remove_listener( CoreEvents::mouseMotion,			listener, &ListenerClass::cb_evtMotion, prio );
		evt::remove_listener( CoreEvents::mousePassiveMotion,	listener, &ListenerClass::cb_evtPassiveMotion, prio );
	}

	////=============================================================================================
	//template<class ListenerClass>
	//void unregister_touch_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	//{
	//	evt::remove_listener( CoreEvents::touchDoubleTap,	listener, &ListenerClass::cb_evtTouchDoubleTap, prio );
	//	evt::remove_listener( CoreEvents::touchDown,		listener, &ListenerClass::cb_evtTouchDown, prio );
	//	evt::remove_listener( CoreEvents::touchMoved,		listener, &ListenerClass::cb_evtTouchMoved, prio );
	//	evt::remove_listener( CoreEvents::touchUp,			listener, &ListenerClass::cb_evtTouchUp, prio );
	//}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_window_resize_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::windowResized, listener, &ListenerClass::cb_evtReshape, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_focus_events( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::focusGot, listener, &ListenerClass::cb_evtFocusGot, prio );
		evt::remove_listener( CoreEvents::focusLost, listener, &ListenerClass::cb_evtFocusLost, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_close_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::close, listener, &ListenerClass::cb_evtClose, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_idle_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::idle, listener, &ListenerClass::cb_evtIdle, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_display_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::display, listener, &ListenerClass::cb_evtDisplay, prio );
	}

	//=============================================================================================
	template<class ListenerClass>
	void unregister_application_exit_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::applicationExit, listener, &ListenerClass::cb_evtAppExit, prio );
	}




	//=============================================================================================
	template<class ListenerClass>
	void unregister_plugin_resize_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::pluginResized, listener, &ListenerClass::cb_evtResizePlugin, prio );
	}
	//=============================================================================================
	template<class ListenerClass>
	void unregister_set_size_dashboard_event( ListenerClass * listener, int32_t prio=EVENT_ORDER_AFTER_APP  )
	{
		evt::remove_listener( CoreEvents::setSizeDashboard, listener, &ListenerClass::cb_evtSetSize, prio );
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		Event notification
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	void notify_key_pressed( uint8_t key );
	void notify_key_released( uint8_t key );
	void notify_text_input( uint8_t key );
	void notify_key_event( const evt::KeyEventArgs & p_args );

	void notify_mouse_down( int32_t button, int32_t x, int32_t y );
	void notify_mouse_up( int32_t button, int32_t x, int32_t y );
	void notify_mouse_double_click( int32_t button, int32_t x, int32_t y );
	void notify_mouse_motion( int32_t x, int32_t y );
	void notify_mouse_passive_motion( int32_t x, int32_t y );
	void notify_mouse_event( const evt::MouseEventArgs & p_args );

	void notify_window_resize( uint32_t p_width, uint32_t p_height );
	void notify_window_resize_event( const evt::ResizeEventArgs & p_args );

	void notify_focus_got( void );
	void notify_focus_lost( void );

	void notify_idle( void );

	void notify_display( void );

	void notify_close( void );

	void notify_app_exit( void );



	void notify_plugin_resize( int32_t p_width, int32_t p_height );
	void notify_plugin_resize_event( const evt::ResizeEventArgs & p_args );

	void notify_set_size_dashboard( int32_t p_width, int32_t p_height );
	void notify_set_size_dashboard_event( const evt::ResizeEventArgs & p_args );


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


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		controlEventArgs class
	///////////////////////////////////////////////////////////////////////////////////////////////////

	class VideoPlayer;
	namespace gl { class TextureData; }

namespace evt
{

	/**
	* @class controlEventArgs
	*
	* @brief base UIControl event args class
	*
	* @note extends evt::Args
	*/
	class controlEventArgs : public evt::Args
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

		// Texture args
		std::string			m_path;
		std::string			m_pathSecond;
		VideoPlayer *		m_pPlayer;
		gl::TextureData *		m_pTextureData;
	};

	typedef evt::TEvent<controlEventArgs> controlEvent;


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		VideoEventArgs class
	///////////////////////////////////////////////////////////////////////////////////////////////////

	class VideoEventArgs 
		: public evt::Args 
	{
	public:
		int64_t		Numframe;
		int64_t		TotalNumframe;
	};



	///////////////////////////////////////////////////////////////////////////////////////////////////
	//		EventListenner class
	///////////////////////////////////////////////////////////////////////////////////////////////////

	class EventListenner
	{
	public:
		EventListenner( void );
		virtual ~EventListenner( void );

		virtual void newVideoEventMessage( evt::VideoEventArgs & p_eventArgs );
		virtual void newControlEventMessage( evt::controlEventArgs & p_eventArgs );
	};


} // namespace evt

#endif // __EVT_EVENT_H__
