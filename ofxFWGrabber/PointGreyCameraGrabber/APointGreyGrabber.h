//APointGreyGrabber.h

#ifdef A_VIDEO_CAPTURE_POINTGREY

#ifndef __A_POINT_GREY_GRABBER_H
#define __A_POINT_GREY_GRABBER_H

/*
#ifdef _WIN32
	#include <windows.h>    // included in all Windows apps
	#include <winuser.h>    // Windows constants
	#include <GL/gl.h>
	#include <GL/glu.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif
*/

#pragma comment(lib, "pgrflycapture.lib")

#include "ofConstants.h"
#include "ofAppRunner.h"
#include "ofxThread.h"

//#include "SDL.h"
//#include "SDL_thread.h"

#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include <pgrflycapture.h>
#include <pgrflycaptureplus.h>


/*
#define VID_FORMAT_GREYSCALE	0
#define VID_FORMAT_BGR			1

#define VID_FORMAT_YUV411		2
#define VID_FORMAT_YUV422		3
#define VID_FORMAT_YUV444		4

#define VID_FORMAT_RGB			5

#define VID_FORMAT_Y8			6
#define VID_FORMAT_Y16			7
*/



#include "../AVideoGrabberTypesAndEnums.h"
#include "APointGreyGrabberFramerateHelper.h"
#include "APointGreyGrabberVideoFormatHelper.h"
#include "APointGreyGrabberFeatureHelper.h"

#define _VIDEOMODE      FLYCAPTURE_VIDEOMODE_640x480Y8
//#define _VIDEOMODE      FLYCAPTURE_VIDEOMODE_640x480RGB
#define _COLS           640
#define _ROWS           480
#define _IMAGE_SIZE     _COLS * _ROWS
#define _FRAMERATE      FLYCAPTURE_FRAMERATE_30


#define _CHECK_ERROR( error, function ) \
{ \
	if( error != FLYCAPTURE_OK ) \
{ \
	printf( \
	"ERROR: %s returned \"%s\" (%d).\n", \
	function, \
	::flycaptureErrorToString( error ), \
	error ); \
	\
	::exit( 1 ); \
} \
} \



class APointGreyGrabber : public ofxThread
{
	public:


		APointGreyGrabber();
		~APointGreyGrabber();


		int init( int _width = 320, int _height = 240, int _format = VID_FORMAT_GREYSCALE, int _targetFormat = VID_FORMAT_BGR , int _frameRate = 30 );
		int initCam( int _videoMode, int _frameRateMode );

		void threadedFunction();
		void update();

		void releaseResources();
		void reportCameraInfo( const FlyCaptureInfoEx* pinfo );

		bool haveNewFrame();
		void doneWithCurrentFrame();

		// these don't do anything for camera grabbing
		void setLoopType( int _loopType );
		void play();
		void pause();
		void stop();


		// features
		void initFeatures();
		void setFeaturesOnePushMode();

		void updateAllFeatureVals();
		void updateFeatureVals( AGrabberCameraFeatureVals* _feature );

		void setFeatureMode(int _feature, int _featureMode );
		void setFeatureStateOnOff( bool _val, int _feature, int _featureMode );
		void setFeatureAbsoluteVal( float _val, int _feature );
		void setFeatureVal( float _val, int _feature );


		string pixelFormatToString( FlyCapturePixelFormat _pixelFormat );

		unsigned char* finalImageDataPointer;

		unsigned int tmpCount;
		//SDL_Thread *updateThread;

		int outputImageWidth;
		int outputImageHeight;

		int targetFormat;

		bool hasNewImage;
		bool grabbedFirstImage;

		bool incomingImageNeedsConversion;

		// capture stuff
		FlyCaptureError	error;
		FlyCaptureContext	context;

		FlyCaptureImage rawCameraImage;
		FlyCaptureImage* convertedImage;

		FlyCaptureVideoMode desiredVideoMode;
		FlyCaptureFrameRate desiredFrameRate;


		int availableFeatureAmount;
		AGrabberCameraFeatureVals* featureVals;

		// MEMO:
		int width;
		int height;

		unsigned char* getPixels() {
		    return finalImageDataPointer;
		}

		void close() {
		    stop();
		    releaseResources();
		}


	private:


};


#endif

#endif


/*

FLYCAPTURE_411YUV8 YUV 4:1:1.
FLYCAPTURE_422YUV8 YUV 4:2:2.
FLYCAPTURE_444YUV8 YUV 4:4:4.
FLYCAPTURE_BGR 24 bit BGR
FLYCAPTURE_BGRU 32 bit BGRU
FLYCAPTURE_MONO16 16 bits of mono information.
FLYCAPTURE_MONO8 8 bits of mono information.
FLYCAPTURE_RAW16 16 bit raw data output of sensor.
FLYCAPTURE_RAW8 8 bit raw data output of sensor.
FLYCAPTURE_RGB16 R=G=B=16 bits
FLYCAPTURE_RGB8 R=G=B=8 bits
FLYCAPTURE_S_MONO16 16 bits of signed mono information.
FLYCAPTURE_S_RGB16 R=G=B=16 bits signed
*/


/*
YUV444
YUV422
YUV411

RGB

Y8
Y16
*/

/*
FLYCAPTURE_NUM_VIDEOMODES Number of possible video modes

////////////// 160x120 /////////////
FLYCAPTURE_VIDEOMODE_160x120YUV444 160x120 YUV444.

////////////// 320x320 /////////////
FLYCAPTURE_VIDEOMODE_320x240YUV422 320x240 YUV422.

////////////// 640x480 /////////////
FLYCAPTURE_VIDEOMODE_640x480RGB 640x480 24-bit RGB.
FLYCAPTURE_VIDEOMODE_640x480Y16 640x480 16-bit greyscale or bayer tiledcolor image.
FLYCAPTURE_VIDEOMODE_640x480Y8 640x480 8-bit greyscale or bayer tiledcolor image.
FLYCAPTURE_VIDEOMODE_640x480YUV411 640x480 YUV411.
FLYCAPTURE_VIDEOMODE_640x480YUV422 640x480 YUV422.

////////////// 800x600 /////////////
FLYCAPTURE_VIDEOMODE_800x600RGB 800x600 RGB.
FLYCAPTURE_VIDEOMODE_800x600Y16  800x600 16-bit greyscale or bayer tiled image.
FLYCAPTURE_VIDEOMODE_800x600Y8  800x600 8-bit greyscale or bayer tiled image.
FLYCAPTURE_VIDEOMODE_800x600YUV422 800x600 YUV422.

////////////// 1024x768 /////////////
FLYCAPTURE_VIDEOMODE_1024x768RGB 1024x768 RGB.
FLYCAPTURE_VIDEOMODE_1024x768Y16 1024x768 16-bit greyscale or bayer tiled color image
FLYCAPTURE_VIDEOMODE_1024x768Y8 1024x768 8-bit greyscale or bayer tiled color image
FLYCAPTURE_VIDEOMODE_1024x768YUV422 1024x768 YUV422.

////////////// 1280x960 /////////////
FLYCAPTURE_VIDEOMODE_1280x960RGB 1280x960 RGB.
FLYCAPTURE_VIDEOMODE_1280x960Y16 1280x960 16-bit greyscale or bayer titledcolor image
FLYCAPTURE_VIDEOMODE_1280x960Y8 1280x960 8-bit greyscale or bayer titledcolor image
FLYCAPTURE_VIDEOMODE_1280x960YUV422 1280x960 YUV422.

////////////// 1600x1200 /////////////
FLYCAPTURE_VIDEOMODE_1600x1200RGB 1600x1200 RGB
FLYCAPTURE_VIDEOMODE_1600x1200Y16 1600x1200 16-bit greyscale or bayer titled colo
FLYCAPTURE_VIDEOMODE_1600x1200Y8 1600x1200 8-bit greyscale or bayer titled color image
FLYCAPTURE_VIDEOMODE_1600x1200YUV422 1600x1200 YUV422.

////////////// Misc /////////////
FLYCAPTURE_VIDEOMODE_ANY	Hook for “any usable video mode.”
FLYCAPTURE_VIDEOMODE_CUSTOM Custom video mode. Used with custom image size functionality.

*/
