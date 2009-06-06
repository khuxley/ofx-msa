
#include "AVideoGrabber.h"


//--------------------------------------------------------------------
AVideoGrabber::AVideoGrabber()
{
    bGrabberInited = false;
	bUseTexture	= true;
	bIsFrameNew = false;
}

//--------------------------------------------------------------------
int AVideoGrabber::initGrabber( int _width, int _height, int _format, int _targetFormat, int _frameRate )
{

    int initResult = videoGrabber.init( _width, _height, _format, _targetFormat, _frameRate );


//    width = videoGrabber.width;       // MEMO, use getWidth() instead
//    height = videoGrabber.height;

    if (bUseTexture){
        printf("Creating %.0f x %.0f texture \n", getWidth(), getHeight());


        // create the texture, set the pixels to black and upload them to the texture (so at least we see nothing black the callback)
        isRGB = true;          // MEMO . todo: read imagetype from format
        tex.allocate(getWidth(), getHeight(), isRGB ? OF_IMAGE_COLOR : OF_IMAGE_GRAYSCALE); // MEMO
 //       unsigned char pixels[width * height * 3];     // MEMO. what does this line do?
 //       memset(pixels, 0, getWidth() * getHeight() * 3);        // MEMO
 //       tex.loadData(pixels, getWidth(), getHeight(), GL_RGB);  // MEMO
    }

    bGrabberInited = true;
    return initResult;
}

//--------------------------------------------------------------------
bool AVideoGrabber::isFrameNew()
{
    return bIsFrameNew;
}

//--------------------------------------------------------------------
unsigned char* AVideoGrabber::getPixels()
{
    return videoGrabber.getPixels();
}

void AVideoGrabber::doneWithCurrentFrame()
{
    videoGrabber.doneWithCurrentFrame();
}

//--------------------------------------------------------------------
void AVideoGrabber::update()
{
	grabFrame();
}

//--------------------------------------------------------------------
void AVideoGrabber::grabFrame()
{

    if (bGrabberInited){
        bIsFrameNew = videoGrabber.haveNewFrame();
        if(bIsFrameNew) {
            if (bUseTexture){
                // MEMO. create texture here, for some reason width/height isn't correct in init()

				tex.loadData(getPixels(), getWidth(), getHeight(), isRGB ? GL_RGB : GL_ALPHA);   // MEMO
			}
			//videoGrabber.doneWithCurrentFrame();
        }
    }
}

//--------------------------------------------------------------------
void AVideoGrabber::draw(float _x, float _y, float _w, float _h)
{
	if (bUseTexture){
		tex.draw(_x, _y, _w, _h);
	}
}

//--------------------------------------------------------------------
void AVideoGrabber::draw(float _x, float _y)
{
	draw(_x, _y, (float)getWidth(), (float)getHeight());    // MEMO
}

//--------------------------------------------------------------------
void AVideoGrabber::close()
{
    if(bGrabberInited){
        bGrabberInited 		= false;
        bIsFrameNew 		= false;
        videoGrabber.close();
    }
}

//--------------------------------------------------------------------
void AVideoGrabber::setFeaturesOnePushMode()
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.setFeaturesOnePushMode();
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.setFeaturesOnePushMode();
	#endif
}

//--------------------------------------------------------------------
bool AVideoGrabber::UICapable()
{
	#ifdef A_VIDEO_CAPTURE_POINTGREY
		return true;
	#elif A_VIDEO_CAPTURE_LIB_DC1394        // MEMO
		return true;
	#else
		return false;
	#endif
}

//--------------------------------------------------------------------
void AVideoGrabber::updateAllFeatureVals()
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.updateAllFeatureVals();
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.updateAllFeatureVals();
	#endif
}

//--------------------------------------------------------------------
void AVideoGrabber::setFeatureMode( int _feature, int _featureMode)
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.setFeatureMode( _feature, _featureMode);
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.setFeatureMode( _feature, _featureMode );
	#endif
}


//--------------------------------------------------------------------
void AVideoGrabber::setFeatureStateOnOff( bool _val, int _feature, int _featureMode )
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.setFeatureStateOnOff( _val, _feature, _featureMode);
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.setFeatureStateOnOff( _val, _feature, _featureMode);
	#endif
}

//--------------------------------------------------------------------
void AVideoGrabber::setFeatureAbsoluteVal( float _val, int _feature )
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
        videoGrabber.setFeatureAbsoluteVal( _val, _feature);
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.setFeatureAbsoluteVal( _val, _feature);
	#endif
}

//--------------------------------------------------------------------
void AVideoGrabber::setFeatureVal( float _val, int _feature )
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.setFeatureVal( _val, _feature );
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY
		videoGrabber.setFeatureVal( _val, _feature );
	#endif
}

//--------------------------------------------------------------------
void AVideoGrabber::setFeatureWhiteBalance(float _val1, float _val2)
{
	#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		videoGrabber.setFeatureWhiteBalance(_val1,_val2);
    #endif

	#ifdef A_VIDEO_CAPTURE_POINTGREY

	#endif

}



