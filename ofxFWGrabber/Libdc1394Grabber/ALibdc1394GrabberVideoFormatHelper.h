/*
 *  ALibdc1394GrabberVideoFormatHelper.h
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 11/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394

#ifndef __A_LIB_DC1394_GRABBER_VIDEO_FORMAT_HELPER_H
#define __A_LIB_DC1394_GRABBER_VIDEO_FORMAT_HELPER_H



#include <dc1394/dc1394.h>
#include <inttypes.h>

#include "../AVideoGrabberTypesAndEnums.h"


class ALibdc1394GrabberVideoFormatHelper
{

public:

	static int libcd1394ColorFormatToVidFormat(  uint32_t _colorFormatID );

	static dc1394video_mode_t videoFormatFromParams( int _width, int _height, int _vidFormat, bool _forceColor = false );


	static dc1394video_mode_t videoFormatFromParams160x120( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams320x240( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams640x480( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams800x600( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams1024x768( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams1280x960( int _vidFormat, bool _forceColor );
	static dc1394video_mode_t videoFormatFromParams1600x1200( int _vidFormat, bool _forceColor );

};

#endif

#endif
