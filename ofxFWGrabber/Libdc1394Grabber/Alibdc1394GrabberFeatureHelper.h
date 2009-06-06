/*
 *  Alibdc1394GrabberFeatureHelper.h
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 16/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394

#ifndef __A_LIB_DC1394_GRABBER_FEATURE_HELPER_H
#define __A_LIB_DC1394_GRABBER_FEATURE_HELPER_H



#include <dc1394/dc1394.h>
#include <inttypes.h>

#include "../AVideoGrabberTypesAndEnums.h"

class Alibdc1394GrabberFeatureHelper
{

public:

	static dc1394feature_t AVidFeatureToLibdcFeature( int _avidFeatureEnum );
	static int libdcFeatureToAVidFeature( dc1394feature_t _libdcFeatureEnum );


};

#endif

#endif
