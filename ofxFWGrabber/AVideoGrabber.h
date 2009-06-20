#ifndef __A_VIDEO_GRABBER_H
#define __A_VIDEO_GRABBER_H


// one of these need to be set in the project properties
//#define A_VIDEO_CAPTURE_POINTGREY
//#define A_VIDEO_CAPTURE_LIB_DC1394        // MEMO. put this in project settings

#ifdef A_VIDEO_CAPTURE_POINTGREY
	#pragma comment (lib, "pgrflycapture.lib")
	#include "PointGreyCameraGrabber/APointGreyGrabber.h"
#endif

#ifdef A_VIDEO_CAPTURE_LIB_DC1394
	#include "Libdc1394Grabber/ALibdc1394Grabber.h"
#endif


#include "AVideoGrabberTypesAndEnums.h"

// MEMO add 006 base classes
class AVideoGrabber : public ofBaseVideo
{
	public:

		AVideoGrabber();

		int initGrabber( int _width = 320,
				  int _height = 240,
				  int _format = VID_FORMAT_RGB,
				  int _targetFormat = VID_FORMAT_RGB,
				  int _frameRate = 15 );

		bool isFrameNew();
		unsigned char* getPixels();
		void grabFrame();
		void draw(float x, float y, float w, float h);
		void draw(float x, float y);
        void update();
        void doneWithCurrentFrame();
        void close();

		// camera feature functions
		bool UICapable();
		void setFeaturesOnePushMode();
		void updateAllFeatureVals();

		void setFeatureMode( int _val, int _feature );
		void setFeatureStateOnOff( bool _val, int _feature, int _featureMode );
		void setFeatureAbsoluteVal( float _val, int _feature );
		void setFeatureVal( float _val, int _feature );
		void setFeatureWhiteBalance(float _val1, float _val2);

		#ifdef A_VIDEO_CAPTURE_POINTGREY
			APointGreyGrabber videoGrabber;
		#elif A_VIDEO_CAPTURE_LIB_DC1394        // MEMO
			ALibdc1394Grabber videoGrabber;
        #endif                                  // MEMO

// MEMO. ptgreygrabber wasn't returning correct width / height in first frame, so instead read from it directly when needed
 //       int width;
 //       int height;
        float getWidth() {
            return (float)videoGrabber.width;
        }

        float getHeight() {
            return (float)videoGrabber.height;
        }

        void setUseTexture(bool b) {
            bUseTexture = b;
        }


        ofTexture &getTextureReference() {
            return tex;
        }


	protected:
        bool bGrabberInited;
        bool bUseTexture;
        bool isRGB;            // MEMO. bit hackish, but
        ofTexture tex;
        bool bIsFrameNew;
        unsigned char* pixels;

};


#endif
