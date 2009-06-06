
#ifndef __A_VIDEO_FORMATS_ENUM_H
#define __A_VIDEO_FORMATS_ENUM_H

#include <string>
using namespace std;

class AGrabberCameraFeatureVals
{

	public:

		AGrabberCameraFeatureVals()
		{
			name = ""; feature = 0; currVal = 0.0f; currVal2 = 0.0f; minVal = 0.0f; maxVal = 0.0f;
			isPresent = false; isReadable = false; hasAbsoluteMode = false; hasManualMode = false; hasManualActive = false; absoluteModeActive = false;
			isOn = false; isOnOffSwitchable = false; hasOnePush = false; hasOnePushActive = false; hasAutoMode = false; hasAutoModeActive = false;

		}

		string name;

		int feature;

		float currVal;
		float currVal2;

		float minVal;
		float maxVal;

		bool isPresent;
		bool isReadable;

		bool hasAbsoluteMode;
		bool absoluteModeActive;

		bool hasManualMode;
		bool hasManualActive;

		bool isOn;
		bool isOnOffSwitchable;

		bool hasOnePush;
		bool hasOnePushActive;

		bool hasAutoMode;
		bool hasAutoModeActive;

};


enum CAMERA_FEATURES
{
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
};

#define FEATURE_FIRST FEATURE_BRIGHTNESS
#define FEATURE_LAST  FEATURE_CAPTURE_QUALITY

/*
also add loop modes, etc for movies ?
*/

enum CAMERA_FEATURE_MODES
{
	FEATURE_MODE_MANUAL			= 0,
	FEATURE_MODE_AUTO			= 1,
	FEATURE_MODE_ONE_PUSH_AUTO	= 2
};

enum CAMERA_FEATURE_SWITCHABLE_MODES
{
	FEATURE_AUTO_MODE		= 0,
	FEATURE_ONESHOT_MODE	= 1,
	FEATURE_IS_ON			= 2,
};


enum CAMERA_FEATURE_SWITCH_STATES
{
	FEATURE_ON  = 0,
	FEATURE_OFF = 1,
};


#define CAMERA_FEATURE_AMOUNT 22

enum VID_FORMATS
{
	VID_FORMAT_GREYSCALE  =	0,
	VID_FORMAT_BGR		  =	1,

	VID_FORMAT_YUV411	  =	2,
	VID_FORMAT_YUV422	  = 3,
	VID_FORMAT_YUV444	  =	4,

	VID_FORMAT_RGB		  =	5,

	VID_FORMAT_Y8		  = 6,
	VID_FORMAT_Y16		  = 7,

	VID_FORMAT_BGRA		  = 8, // alpha channel formats for movies
	VID_FORMAT_ARGB		  = 9,

	VID_FORMAT_ABGR		  = 10,
	VID_FORMAT_RGBA		  = 11
};

enum VID_LOOP_MODES
{
	VID_LOOP_MODE_OFF		= 0,
	VID_LOOP_MODE_ON		= 1,
	VID_LOOP_MODE_PING_PONG	= 2,
};

int stringToVidFormat( string _formatString );
string vidFormatToString( int _format );
string cameraFeatureToTitle( int _feature );


#endif

