/*
*  APointGreyGrabberFeatureHelper.h
*  SDL OpenGL Template
*
*  Created by Andreas Muller on 20/11/2007.
*  Copyright 2007 Nanika. All rights reserved.
*
*/
//#include "../AVideoGrabber.h"  //MEMO. creates circular dependancy

#ifdef A_VIDEO_CAPTURE_POINTGREY

#ifndef __A_POINTGREY_GRABBER_FEATURE_HELPER_H
#define __A_POINTGREY_GRABBER_FEATURE_HELPER_H


#ifdef _WIN32
	#include <windows.h>    // included in all Windows apps
	#include <winuser.h>    // Windows constants
#else
#endif

#include <pgrflycapture.h>
#include <pgrflycaptureplus.h>


#include "../AVideoGrabberTypesAndEnums.h"

class APointGreyGrabberFeatureHelper
{

public:

	static FlyCaptureProperty AVidFeatureToFlyCapFeature( int _avidFeatureEnum );
	static int flyCapFeatureToAVidFeature( FlyCaptureProperty _flyCapFeatureEnum );


};

#endif //__A_POINTGREY_GRABBER_FEATURE_HELPER_H

#endif //A_VIDEO_CAPTURE_POINTGREY
