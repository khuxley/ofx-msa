

#ifdef A_VIDEO_CAPTURE_POINTGREY

#ifndef __A_POINT_GREY_GRABBER_VIDEO_FORMAT_HELPER_H
#define __A_POINT_GREY_GRABBER_VIDEO_FORMAT_HELPER_H



#include <iostream>
using namespace std;

#include <pgrflycapture.h>
#include <pgrflycaptureplus.h>

#include "../AVideoGrabberTypesAndEnums.h"

/*
enum VID_FORMATS
{
	VID_FORMAT_GREYSCALE  =	0,
	VID_FORMAT_BGR		  =	1,

	VID_FORMAT_YUV411	  =	2,
	VID_FORMAT_YUV422	  = 3,
	VID_FORMAT_YUV444	  =	4,

	VID_FORMAT_RGB		  =	5,

	VID_FORMAT_Y8		  = 6,
	VID_FORMAT_Y16		  = 7
};
*/


class APointGreyGrabberVideoFormatHelper
{
public:

	static FlyCaptureVideoMode videoFormatFromParams( int _width, int _height, int _vidFormat, bool _forceColor = false );

	static FlyCaptureVideoMode degradeVideoFormat( FlyCaptureVideoMode _format );


	static FlyCaptureVideoMode degradeVideoFormat640x480( FlyCaptureVideoMode _format );
	static FlyCaptureVideoMode degradeVideoFormat800x600( FlyCaptureVideoMode _format );
	static FlyCaptureVideoMode degradeVideoFormat1024x768( FlyCaptureVideoMode _format );
	static FlyCaptureVideoMode degradeVideoFormat1280x960( FlyCaptureVideoMode _format );
	static FlyCaptureVideoMode degradeVideoFormat1600x1200( FlyCaptureVideoMode _format );


	static FlyCaptureVideoMode videoFormatFromParams160x120( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams320x240( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams640x480( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams800x600( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams1024x768( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams1280x960( int _vidFormat, bool _forceColor );
	static FlyCaptureVideoMode videoFormatFromParams1600x1200( int _vidFormat, bool _forceColor );
};



#endif

#endif