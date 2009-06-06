#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_POINTGREY

#include "APointGreyGrabberVideoFormatHelper.h"

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams( int _width,
																			   int _height,
																			   int _vidFormat,
																			   bool _forceColor )
{

	if( _width == 160 && _height == 120 )
	{
		return videoFormatFromParams160x120(  _vidFormat,  _forceColor );
	}
	else if ( _width == 320 && _height == 240 )
	{
		return videoFormatFromParams320x240( _vidFormat, _forceColor );
	}
	else if ( _width == 640 && _height == 480 )
	{
		return videoFormatFromParams640x480( _vidFormat, _forceColor );
	}
	else if ( _width == 800 && _height == 600 )
	{
		return videoFormatFromParams800x600( _vidFormat, _forceColor );
	}
	else if ( _width == 1024 && _height == 768 )
	{
		return videoFormatFromParams1024x768( _vidFormat, _forceColor );
	}
	else if ( _width == 1280 && _height == 960 )
	{
		return videoFormatFromParams1280x960( _vidFormat, _forceColor );
	}
	else if ( _width == 1600 && _height == 1200 )
	{
		return videoFormatFromParams1600x1200( _vidFormat, _forceColor );
	}

	return FLYCAPTURE_VIDEOMODE_ANY;
}

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat( FlyCaptureVideoMode _format )
{

	if( _format == FLYCAPTURE_VIDEOMODE_CUSTOM ) { return FLYCAPTURE_VIDEOMODE_ANY; }
	else if( _format == FLYCAPTURE_VIDEOMODE_160x120YUV444 ) { return FLYCAPTURE_VIDEOMODE_ANY; }
	else if( _format == FLYCAPTURE_VIDEOMODE_320x240YUV422 ) { return FLYCAPTURE_VIDEOMODE_160x120YUV444; }


	else if( _format == FLYCAPTURE_VIDEOMODE_640x480RGB ||
			 _format == FLYCAPTURE_VIDEOMODE_640x480YUV411 ||
			 _format == FLYCAPTURE_VIDEOMODE_640x480YUV422 ||
			 _format == FLYCAPTURE_VIDEOMODE_640x480Y8 ||
			 _format == FLYCAPTURE_VIDEOMODE_640x480Y16  ) { return degradeVideoFormat640x480( _format ); }


	else if( _format == FLYCAPTURE_VIDEOMODE_800x600RGB ||
		_format == FLYCAPTURE_VIDEOMODE_800x600YUV422 ||
		_format == FLYCAPTURE_VIDEOMODE_800x600Y8 ||
		_format == FLYCAPTURE_VIDEOMODE_800x600Y16  ) { return degradeVideoFormat800x600( _format ); }

	else if( _format == FLYCAPTURE_VIDEOMODE_1024x768RGB ||
		_format == FLYCAPTURE_VIDEOMODE_1024x768YUV422 ||
		_format == FLYCAPTURE_VIDEOMODE_1024x768Y8 ||
		_format == FLYCAPTURE_VIDEOMODE_1024x768Y16  ) { return degradeVideoFormat1024x768( _format ); }

	else if( _format == FLYCAPTURE_VIDEOMODE_1280x960RGB ||
		_format == FLYCAPTURE_VIDEOMODE_1280x960YUV422 ||
		_format == FLYCAPTURE_VIDEOMODE_1280x960Y8 ||
		_format == FLYCAPTURE_VIDEOMODE_1280x960Y16  ) { return degradeVideoFormat1280x960( _format ); }

	else if( _format == FLYCAPTURE_VIDEOMODE_1600x1200RGB ||
		_format == FLYCAPTURE_VIDEOMODE_1600x1200YUV422 ||
		_format == FLYCAPTURE_VIDEOMODE_1600x1200Y8 ||
		_format == FLYCAPTURE_VIDEOMODE_1600x1200Y16  ) { return degradeVideoFormat1600x1200( _format ); }



	return FLYCAPTURE_VIDEOMODE_ANY;
}



/*
////////////// 640x480 /////////////
FLYCAPTURE_VIDEOMODE_640x480RGB 640x480 24-bit RGB.
FLYCAPTURE_VIDEOMODE_640x480Y16 640x480 16-bit greyscale or bayer tiledcolor image.
FLYCAPTURE_VIDEOMODE_640x480Y8 640x480 8-bit greyscale or bayer tiledcolor image.
FLYCAPTURE_VIDEOMODE_640x480YUV411 640x480 YUV411.
FLYCAPTURE_VIDEOMODE_640x480YUV422 640x480 YUV422.
*/


 FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat640x480( FlyCaptureVideoMode _format )
 {

	if ( _format == FLYCAPTURE_VIDEOMODE_640x480RGB )
	{
		return FLYCAPTURE_VIDEOMODE_640x480YUV422;
	}
	else if ( _format == FLYCAPTURE_VIDEOMODE_640x480YUV422 )
	{
		return FLYCAPTURE_VIDEOMODE_640x480YUV411;
	}
	else if ( _format == FLYCAPTURE_VIDEOMODE_640x480YUV411 )
	{
		return FLYCAPTURE_VIDEOMODE_640x480Y16;
	}
	else if ( _format == FLYCAPTURE_VIDEOMODE_640x480Y16 )
	{
		return FLYCAPTURE_VIDEOMODE_640x480Y8;
	}
	else if ( _format == FLYCAPTURE_VIDEOMODE_640x480Y8 )
	{
		 // go down in resolution
		return FLYCAPTURE_VIDEOMODE_320x240YUV422;
	}


 	return FLYCAPTURE_VIDEOMODE_ANY;
 }

/*
////////////// 800x600 /////////////
FLYCAPTURE_VIDEOMODE_800x600RGB 800x600 RGB.
FLYCAPTURE_VIDEOMODE_800x600Y16  800x600 16-bit greyscale or bayer tiled image.
FLYCAPTURE_VIDEOMODE_800x600Y8  800x600 8-bit greyscale or bayer tiled image.
FLYCAPTURE_VIDEOMODE_800x600YUV422 800x600 YUV422.
*/

 FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat800x600( FlyCaptureVideoMode _format )
 {

	 if ( _format == FLYCAPTURE_VIDEOMODE_800x600RGB )
	 {
		 return FLYCAPTURE_VIDEOMODE_800x600YUV422;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_800x600YUV422 )
	 {
		 return FLYCAPTURE_VIDEOMODE_800x600Y16;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_800x600Y16 )
	 {
		 return FLYCAPTURE_VIDEOMODE_800x600Y8;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_800x600Y8 )
	 {
		 // go down in resolution, but start at the top
		 return FLYCAPTURE_VIDEOMODE_640x480RGB;
	 }

 	return FLYCAPTURE_VIDEOMODE_ANY;
 }


/*
////////////// 1024x768 /////////////
FLYCAPTURE_VIDEOMODE_1024x768RGB 1024x768 RGB.
FLYCAPTURE_VIDEOMODE_1024x768Y16 1024x768 16-bit greyscale or bayer tiled color image
FLYCAPTURE_VIDEOMODE_1024x768Y8 1024x768 8-bit greyscale or bayer tiled color image
FLYCAPTURE_VIDEOMODE_1024x768YUV422 1024x768 YUV422.
*/

 FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat1024x768( FlyCaptureVideoMode _format )
 {

	 if ( _format == FLYCAPTURE_VIDEOMODE_1024x768RGB )
	 {
		 return FLYCAPTURE_VIDEOMODE_1024x768YUV422;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1024x768YUV422 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1024x768Y16;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1024x768Y16 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1024x768Y8;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1024x768Y8 )
	 {
		 // go down in resolution, but start at the top
		 return FLYCAPTURE_VIDEOMODE_800x600RGB;
	 }


 	return FLYCAPTURE_VIDEOMODE_ANY;
 }

/*
////////////// 1280x960 /////////////
FLYCAPTURE_VIDEOMODE_1280x960RGB 1280x960 RGB.
FLYCAPTURE_VIDEOMODE_1280x960Y16 1280x960 16-bit greyscale or bayer titledcolor image
FLYCAPTURE_VIDEOMODE_1280x960Y8 1280x960 8-bit greyscale or bayer titledcolor image
FLYCAPTURE_VIDEOMODE_1280x960YUV422 1280x960 YUV422.
*/

 FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat1280x960( FlyCaptureVideoMode _format )
 {


	 if ( _format == FLYCAPTURE_VIDEOMODE_1280x960RGB )
	 {
		 return FLYCAPTURE_VIDEOMODE_1280x960YUV422;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1280x960YUV422 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1280x960Y16;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1280x960Y16 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1280x960Y8;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1280x960Y8 )
	 {
		 // go down in resolution, but start at the top
		 return FLYCAPTURE_VIDEOMODE_1024x768RGB;
	 }


 	return FLYCAPTURE_VIDEOMODE_ANY;
 }

/*
////////////// 1600x1200 /////////////
FLYCAPTURE_VIDEOMODE_1600x1200RGB 1600x1200 RGB
FLYCAPTURE_VIDEOMODE_1600x1200Y16 1600x1200 16-bit greyscale or bayer titled colo
FLYCAPTURE_VIDEOMODE_1600x1200Y8 1600x1200 8-bit greyscale or bayer titled color image
FLYCAPTURE_VIDEOMODE_1600x1200YUV422 1600x1200 YUV422.
*/

 FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::degradeVideoFormat1600x1200( FlyCaptureVideoMode _format )
 {


	 if ( _format == FLYCAPTURE_VIDEOMODE_1600x1200RGB )
	 {
		 return FLYCAPTURE_VIDEOMODE_1600x1200YUV422;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1600x1200YUV422 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1600x1200Y16;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1600x1200Y16 )
	 {
		 return FLYCAPTURE_VIDEOMODE_1600x1200Y8;
	 }
	 else if ( _format == FLYCAPTURE_VIDEOMODE_1600x1200Y8 )
	 {
		 // go down in resolution, but start at the top
		 return FLYCAPTURE_VIDEOMODE_1280x960RGB;
	 }

 	return FLYCAPTURE_VIDEOMODE_ANY;
 }







/////////////////////////////////////////////////
// Make a video format from parameters
//

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams160x120( int _vidFormat, bool _forceColor )
{

	return FLYCAPTURE_VIDEOMODE_160x120YUV444;
}

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams320x240( int _vidFormat, bool _forceColor )
{

	return FLYCAPTURE_VIDEOMODE_320x240YUV422;
}

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams640x480( int _vidFormat, bool _forceColor )
{

	if( _vidFormat == VID_FORMAT_RGB ) { return FLYCAPTURE_VIDEOMODE_640x480RGB; }
	else if( _vidFormat == VID_FORMAT_YUV411 ) { return FLYCAPTURE_VIDEOMODE_640x480YUV411; }
	else if( _vidFormat == VID_FORMAT_YUV422 ) { return FLYCAPTURE_VIDEOMODE_640x480YUV422; }
	else if( _vidFormat == VID_FORMAT_YUV444 ) { return FLYCAPTURE_VIDEOMODE_640x480YUV422; }
	else if( _vidFormat == VID_FORMAT_Y8 ) { return FLYCAPTURE_VIDEOMODE_640x480Y8;}
	else if( _vidFormat == VID_FORMAT_Y16 ) { return FLYCAPTURE_VIDEOMODE_640x480Y16; }


	return FLYCAPTURE_VIDEOMODE_640x480YUV422;
}


FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams800x600( int _vidFormat, bool _forceColor )
{

	if( _vidFormat == VID_FORMAT_RGB ) { return FLYCAPTURE_VIDEOMODE_800x600RGB; }
	else if( _vidFormat == VID_FORMAT_YUV411 ) { return FLYCAPTURE_VIDEOMODE_800x600YUV422;}
	else if( _vidFormat == VID_FORMAT_YUV422 ) { return FLYCAPTURE_VIDEOMODE_800x600YUV422;}
	else if( _vidFormat == VID_FORMAT_YUV444 ) { return FLYCAPTURE_VIDEOMODE_800x600YUV422;}
	else if( _vidFormat == VID_FORMAT_Y8 ) { return FLYCAPTURE_VIDEOMODE_800x600Y8;}
	else if( _vidFormat == VID_FORMAT_Y16 ) { return FLYCAPTURE_VIDEOMODE_800x600Y16;}


	return FLYCAPTURE_VIDEOMODE_800x600YUV422;
}

FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams1024x768( int _vidFormat, bool _forceColor )
{

	if( _vidFormat == VID_FORMAT_RGB ) { return FLYCAPTURE_VIDEOMODE_1024x768RGB; }
	else if( _vidFormat == VID_FORMAT_YUV411 ) { return FLYCAPTURE_VIDEOMODE_1024x768YUV422; }
	else if( _vidFormat == VID_FORMAT_YUV422 ) { return FLYCAPTURE_VIDEOMODE_1024x768YUV422;}
	else if( _vidFormat == VID_FORMAT_YUV444 ) { return FLYCAPTURE_VIDEOMODE_1024x768YUV422;}
	else if( _vidFormat == VID_FORMAT_Y8 ) { return FLYCAPTURE_VIDEOMODE_1024x768Y8;}
	else if( _vidFormat == VID_FORMAT_Y16 ) { return FLYCAPTURE_VIDEOMODE_1024x768Y16;}


	return FLYCAPTURE_VIDEOMODE_1024x768YUV422;
}



FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams1280x960( int _vidFormat, bool _forceColor )
{
	if( _vidFormat == VID_FORMAT_RGB ) { return FLYCAPTURE_VIDEOMODE_1280x960RGB; }
	else if( _vidFormat == VID_FORMAT_YUV411 ) { return FLYCAPTURE_VIDEOMODE_1280x960YUV422; }
	else if( _vidFormat == VID_FORMAT_YUV422 ) { return FLYCAPTURE_VIDEOMODE_1280x960YUV422;}
	else if( _vidFormat == VID_FORMAT_YUV444 ) { return FLYCAPTURE_VIDEOMODE_1280x960YUV422;}
	else if( _vidFormat == VID_FORMAT_Y8 ) { return FLYCAPTURE_VIDEOMODE_1280x960Y8;}
	else if( _vidFormat == VID_FORMAT_Y16 ) { return FLYCAPTURE_VIDEOMODE_1280x960Y16;}

	return FLYCAPTURE_VIDEOMODE_1280x960YUV422;
}


FlyCaptureVideoMode APointGreyGrabberVideoFormatHelper::videoFormatFromParams1600x1200( int _vidFormat, bool _forceColor )
{

	if( _vidFormat == VID_FORMAT_RGB ) { return FLYCAPTURE_VIDEOMODE_1600x1200RGB; }
	else if( _vidFormat == VID_FORMAT_YUV411 ) { return FLYCAPTURE_VIDEOMODE_1600x1200YUV422; }
	else if( _vidFormat == VID_FORMAT_YUV422 ) { return FLYCAPTURE_VIDEOMODE_1600x1200YUV422;}
	else if( _vidFormat == VID_FORMAT_YUV444 ) { return FLYCAPTURE_VIDEOMODE_1600x1200YUV422;}
	else if( _vidFormat == VID_FORMAT_Y8 ) { return FLYCAPTURE_VIDEOMODE_1600x1200Y8;}
	else if( _vidFormat == VID_FORMAT_Y16 ) { return FLYCAPTURE_VIDEOMODE_1600x1200Y16;}


	return FLYCAPTURE_VIDEOMODE_1600x1200YUV422;
}

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


#endif
