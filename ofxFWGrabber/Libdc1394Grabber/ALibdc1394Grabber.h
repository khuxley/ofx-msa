#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394


#ifndef __A_LIB_DC1394_GRABBER_H
#define __A_LIB_DC1394_GRABBER_H


#include "ofConstants.h"
#include "ofAppRunner.h"
#include "ofxThread.h"

#include <dc1394/dc1394.h>
#include <inttypes.h>

#include <string>
#include <iostream>
using namespace std;

#include "ALibdc1394GrabberHelpers.h"
#include "ALibdc1394GrabberFramerateHelper.h"
#include "ALibdc1394GrabberVideoFormatHelper.h"
#include "Alibdc1394GrabberFeatureHelper.h"
#include "AVideoGrabberTypesAndEnums.h"
#include "AVideoGrabber.h"

class AVideoGrabber;

class ALibdc1394Grabber : public ofxThread
{
	public:


		ALibdc1394Grabber();
		~ALibdc1394Grabber();

		int init( int _width = 320, int _height = 240, int _format = VID_FORMAT_GREYSCALE, int _targetFormat = VID_FORMAT_BGR , int _frameRate = 30 );
		int initCam( dc1394video_mode_t _videoMode, dc1394framerate_t _frameRateMode );
		void close();
		void threadedFunction();
		void captureFrame();
		unsigned char* getPixels();
		bool haveNewFrame();
		void doneWithCurrentFrame();
		void processCameraImageData( unsigned char* _cameraImageData );


		/* Features */
		void initFeatures();
		void setFeaturesOnePushMode();

		void updateAllFeatureVals();
		void updateFeatureVals( AGrabberCameraFeatureVals* _feature );

		void setFeatureMode( int _val, int _feature );
		void setFeatureStateOnOff( bool _val, int _feature, int _featureMode );
		void setFeatureAbsoluteVal( float _val, int _feature );
		void setFeatureVal( float _val, int _feature );
        void setFeatureWhiteBalance( float u_b_value, float v_r_value);

		int stringToFeature( string _featureName );

        /* Frame pixels */
		int finalImageDataBufferLength;
		unsigned char* pixels;

		unsigned int tmpCount;

		unsigned int width, height;

		int outputImageWidth;
		int outputImageHeight;

		dc1394color_coding_t sourceFormatLibDC;
		//uint32_t targetFormatLibDC;

		int sourceFormat;
		int targetFormat;

		bool hasNewImage;
		bool grabbedFirstImage;

		bool conversionNeeded;

		dc1394color_filter_t bayerPattern;
		dc1394bayer_method_t bayerMethod;

		int availableFeatureAmount;
		AGrabberCameraFeatureVals* featureVals;



	private:

		void setBayerPatternIfNeeded();

        static int g_cameraIndex;
        static dc1394_t* d;

		dc1394camera_t* camera;
		dc1394video_frame_t* frame;

		dc1394framerate_t framerate;
		dc1394video_mode_t video_mode;

		dc1394featureset_t features;
		dc1394framerates_t framerates;
		dc1394video_modes_t video_modes;

		//dc1394color_filter_t
		dc1394color_coding_t coding;

		dc1394speed_t ISO_SPEED;

		int YUV_BYTE_ORDER;

		void initInternalBuffers();
		void cleanupCamera();


};


#endif

#endif
