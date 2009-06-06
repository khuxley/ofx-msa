
/*
*  APointGreyGrabberFeatureHelper.cpp
*  SDL OpenGL Template
*
*  Created by Andreas Muller on 16/05/2007.
*  Copyright 2007 Nanika. All rights reserved.
*
*/

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_POINTGREY

#include "APointGreyGrabberFeatureHelper.h"


static FlyCaptureProperty AVidFeatureToFlyCapFeature( int _avidFeatureEnum );

FlyCaptureProperty APointGreyGrabberFeatureHelper::AVidFeatureToFlyCapFeature( int _avidFeatureEnum )
{

	switch ( _avidFeatureEnum )
	{

	case FEATURE_BRIGHTNESS:
		return FLYCAPTURE_BRIGHTNESS;
		break;

	case FEATURE_EXPOSURE:
		return FLYCAPTURE_AUTO_EXPOSURE;
		break;

	case FEATURE_SHARPNESS:
		return FLYCAPTURE_SHARPNESS;
		break;

	case FEATURE_WHITE_BALANCE:
		return FLYCAPTURE_WHITE_BALANCE;
		break;

	case FEATURE_HUE:
		return FLYCAPTURE_HUE;
		break;

	case FEATURE_SATURATION:
		return FLYCAPTURE_SATURATION;
		break;

	case FEATURE_GAMMA:
		return FLYCAPTURE_GAMMA;
		break;

	case FEATURE_SHUTTER:
		return FLYCAPTURE_SHUTTER;
		break;

	case FEATURE_GAIN:
		return FLYCAPTURE_GAIN;
		break;

	case FEATURE_IRIS:
		return FLYCAPTURE_IRIS;
		break;

	case FEATURE_FOCUS:
		return FLYCAPTURE_FOCUS;
		break;

	case FEATURE_TEMPERATURE:
		return FLYCAPTURE_TEMPERATURE;
		break;

	case FEATURE_TRIGGER:
		return  (FlyCaptureProperty)-1; //FLYCAPTURE_TRIGGER_DELAY; // not sure we should do this here, but there is no FLYCAPTURE_TRIGGER
		break;

	case FEATURE_TRIGGER_DELAY:
		return FLYCAPTURE_TRIGGER_DELAY;
		break;

	case FEATURE_WHITE_SHADING:
		return FLYCAPTURE_SOFTWARE_WHITEBALANCE; // not sure we should do this here
		break;

	case FEATURE_FRAME_RATE:
		return FLYCAPTURE_FRAME_RATE;
		break;

	case FEATURE_ZOOM:
		return FLYCAPTURE_ZOOM;
		break;

	case FEATURE_PAN:
		return FLYCAPTURE_PAN;
		break;

	case FEATURE_TILT:
		return FLYCAPTURE_TILT;
		break;

	case FEATURE_OPTICAL_FILTER:
		return (FlyCaptureProperty)-1; //FLYCAPTURE_BRIGHTNESS; // not sure we should do this here
		break;

	case FEATURE_CAPTURE_SIZE:
		return  (FlyCaptureProperty)-1; //FLYCAPTURE_BRIGHTNESS; // not sure we should do this here
		break;

	case FEATURE_CAPTURE_QUALITY:
		return  (FlyCaptureProperty)-1; //FLYCAPTURE_BRIGHTNESS; // not sure we should do this here
		break;


	default:
		return FLYCAPTURE_BRIGHTNESS;
		break;
	}
}




int APointGreyGrabberFeatureHelper::flyCapFeatureToAVidFeature( FlyCaptureProperty _flyCapFeatureEnum )
{

	switch ( _flyCapFeatureEnum )
	{

	case FLYCAPTURE_BRIGHTNESS:
		return FEATURE_BRIGHTNESS;
		break;

	case FLYCAPTURE_AUTO_EXPOSURE:
		return FEATURE_EXPOSURE;
		break;

	case FLYCAPTURE_SHARPNESS:
		return FEATURE_SHARPNESS;
		break;

	case FLYCAPTURE_WHITE_BALANCE:
		return FEATURE_WHITE_BALANCE;
		break;

	case FLYCAPTURE_HUE:
		return FEATURE_HUE;
		break;

	case FLYCAPTURE_SATURATION:
		return FEATURE_SATURATION;
		break;

	case FLYCAPTURE_GAMMA:
		return FEATURE_GAMMA;
		break;

	case FLYCAPTURE_SHUTTER:
		return FEATURE_SHUTTER;
		break;

	case FLYCAPTURE_GAIN:
		return FEATURE_GAIN;
		break;

	case FLYCAPTURE_IRIS:
		return FEATURE_IRIS;
		break;

	case FLYCAPTURE_FOCUS:
		return FEATURE_FOCUS;
		break;

	case FLYCAPTURE_TEMPERATURE:
		return FEATURE_TEMPERATURE;
		break;

	case FLYCAPTURE_TRIGGER_DELAY:
		return FEATURE_TRIGGER;
		break;

	case FLYCAPTURE_SOFTWARE_WHITEBALANCE:
		return FEATURE_WHITE_SHADING;
		break;

	case FLYCAPTURE_FRAME_RATE:
		return FEATURE_FRAME_RATE;
		break;

	case FLYCAPTURE_ZOOM:
		return FEATURE_ZOOM;
		break;

	case FLYCAPTURE_PAN:
		return FEATURE_PAN;
		break;

	case FLYCAPTURE_TILT:
		return FEATURE_TILT;
		break;

	default:
		return -1;
		break;
	}

}



#endif //A_VIDEO_CAPTURE_POINTGREY



/*
FEATURE_BRIGHTNESS			= 0,
FEATURE_EXPOSURE			= 1,
FEATURE_SHARPNESS			= 2,
FEATURE_WHITE_BALANCE		= 3,
FEATURE_HUE					= 4,
FEATURE_SATURATION			= 5,
FEATURE_GAMMA				= 6,
FEATURE_SHUTTER				= 7,
FEATURE_GAIN				= 8,
FEATURE_IRIS				= 9,
FEATURE_FOCUS				= 10,
FEATURE_TEMPERATURE			= 11,
FEATURE_TRIGGER				= 12,
FEATURE_TRIGGER_DELAY		= 13,
FEATURE_WHITE_SHADING		= 14,
FEATURE_FRAME_RATE			= 15,
FEATURE_ZOOM				= 16,
FEATURE_PAN					= 17,
FEATURE_TILT				= 18,
FEATURE_OPTICAL_FILTER		= 19,
FEATURE_CAPTURE_SIZE		= 20,
FEATURE_CAPTURE_QUALITY		= 21
*/

/*
	typedef enum FlyCaptureProperty
	{
	// The brightness property of the camera.
	FLYCAPTURE_BRIGHTNESS,
	// The auto exposure property of the camera.
	FLYCAPTURE_AUTO_EXPOSURE,
	// The sharpness property of the camera.
	FLYCAPTURE_SHARPNESS,
	// The hardware white balance property of the camera.
	FLYCAPTURE_WHITE_BALANCE,
	// The hue property of the camera.
	FLYCAPTURE_HUE,
	// The saturation property of the camera.
	FLYCAPTURE_SATURATION,
	// The gamma property of the camera.
	FLYCAPTURE_GAMMA,
	// The iris property of the camera.
	FLYCAPTURE_IRIS,
	// The focus property of the camera.
	FLYCAPTURE_FOCUS,
	// The zoom property of the camera.
	FLYCAPTURE_ZOOM,
	// The pan property of the camera.
	FLYCAPTURE_PAN,
	// The tilt property of the camera.
	FLYCAPTURE_TILT,
	// The shutter property of the camera.
	FLYCAPTURE_SHUTTER,
	// The gain  property of the camera.
	FLYCAPTURE_GAIN,
	// The trigger delay property of the camera.
	FLYCAPTURE_TRIGGER_DELAY,
	// The frame rate property of the camera.
	FLYCAPTURE_FRAME_RATE,

	//
	// Software white balance property. Use this to manipulate the
	// values for software whitebalance.  This is only applicable to cameras
	// that do not do onboard color processing.  On these cameras, hardware
	// white balance is disabled.
	//
	FLYCAPTURE_SOFTWARE_WHITEBALANCE,
	// The temperature property of the camera
	FLYCAPTURE_TEMPERATURE,

} FlyCaptureProperty;
*/
