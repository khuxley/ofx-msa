/*
 *  ALibdc1394GrabberFramerateHelper.h
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 10/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394


#ifndef __A_LIB_DC1394_GRABBER_FRAMERATE_HELPER_H
#define __A_LIB_DC1394_GRABBER_FRAMERATE_HELPER_H


#include <dc1394/dc1394.h>
#include <inttypes.h>

#include "../AVideoGrabberTypesAndEnums.h"

class ALibdc1394GrabberFramerateHelper
{

public:

	static dc1394framerate_t numToDcLibFramerate( int rateNum  );
	static string DcLibFramerateToString( dc1394framerate_t _framerate );

};

#endif

#endif
