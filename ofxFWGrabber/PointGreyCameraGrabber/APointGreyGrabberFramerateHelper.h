
#ifdef A_VIDEO_CAPTURE_POINTGREY

#ifndef __A_POINT_GREY_GRABBER_FRAMERATE_HELPER_H
#define __A_POINT_GREY_GRABBER_FRAMERATE_HELPER_H


#include <string>
#include <iostream>
using namespace std;

#include <pgrflycapture.h>
#include <pgrflycaptureplus.h>


class APointGreyGrabberFramerateHelper
{
	public:

	static FlyCaptureFrameRate numToFlyCapFramerate( int rateNum );
	static FlyCaptureFrameRate degradeFramerate( FlyCaptureFrameRate newRate );

	static string flyCapFrameRateToString( FlyCaptureFrameRate rate );

};



#endif

#endif