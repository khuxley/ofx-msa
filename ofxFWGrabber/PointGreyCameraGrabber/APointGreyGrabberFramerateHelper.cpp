
#ifdef A_VIDEO_CAPTURE_POINTGREY

#include "APointGreyGrabberFramerateHelper.h"


FlyCaptureFrameRate APointGreyGrabberFramerateHelper::degradeFramerate( FlyCaptureFrameRate newRate )
{
	switch (newRate )
	{

		case FLYCAPTURE_FRAMERATE_1_875:
			return FLYCAPTURE_FRAMERATE_ANY;
			break;

		case FLYCAPTURE_FRAMERATE_3_75:
			return FLYCAPTURE_FRAMERATE_1_875;
			break;

		case FLYCAPTURE_FRAMERATE_7_5:
			return FLYCAPTURE_FRAMERATE_3_75;
			break;

		case FLYCAPTURE_FRAMERATE_15:
			return FLYCAPTURE_FRAMERATE_7_5;
			break;

		case FLYCAPTURE_FRAMERATE_30:
			return FLYCAPTURE_FRAMERATE_15;
			break;

		case FLYCAPTURE_FRAMERATE_60:
			return FLYCAPTURE_FRAMERATE_30;
			break;

		case FLYCAPTURE_FRAMERATE_120:
			return FLYCAPTURE_FRAMERATE_60;
			break;

		case FLYCAPTURE_FRAMERATE_240:
			return FLYCAPTURE_FRAMERATE_120;
			break;

		default:
			return FLYCAPTURE_FRAMERATE_ANY;
	}

}

FlyCaptureFrameRate APointGreyGrabberFramerateHelper::numToFlyCapFramerate( int rateNum  )
{

	switch (rateNum )
	{

	case 1:
		return FLYCAPTURE_FRAMERATE_1_875;
		break;

	case 2:
		return FLYCAPTURE_FRAMERATE_1_875;
		break;

	case 3:
		return FLYCAPTURE_FRAMERATE_3_75;
		break;

	case 4:
		return FLYCAPTURE_FRAMERATE_3_75;
		break;


	case 7:
		return FLYCAPTURE_FRAMERATE_7_5;
		break;

	case 8:
		return FLYCAPTURE_FRAMERATE_7_5;
		break;


	case 15:
		return FLYCAPTURE_FRAMERATE_15;
		break;

	case 24:
		return FLYCAPTURE_FRAMERATE_30;
		break;

	case 25:
		return FLYCAPTURE_FRAMERATE_30;
		break;

	case 30:
		return FLYCAPTURE_FRAMERATE_30;
		break;

	case 60:
		return FLYCAPTURE_FRAMERATE_60;
		break;

	case 120:
		return FLYCAPTURE_FRAMERATE_120;
		break;

	case 240:
		return FLYCAPTURE_FRAMERATE_240;
		break;

	default:
		return FLYCAPTURE_FRAMERATE_ANY;
		break;
	}
}

string APointGreyGrabberFramerateHelper::flyCapFrameRateToString( FlyCaptureFrameRate rate )
{
	switch ( rate )
	{

	case FLYCAPTURE_FRAMERATE_1_875:
		return "FLYCAPTURE_FRAMERATE_1_875";
		break;

	case FLYCAPTURE_FRAMERATE_3_75:
		return "FLYCAPTURE_FRAMERATE_3_75";
		break;

	case FLYCAPTURE_FRAMERATE_7_5:
		return "FLYCAPTURE_FRAMERATE_7_5";
		break;

	case FLYCAPTURE_FRAMERATE_15:
		return "FLYCAPTURE_FRAMERATE_15";
		break;

	case FLYCAPTURE_FRAMERATE_30:
		return "FLYCAPTURE_FRAMERATE_30";
		break;

	case FLYCAPTURE_FRAMERATE_60:
		return "FLYCAPTURE_FRAMERATE_60";
		break;

	case FLYCAPTURE_FRAMERATE_120:
		return "FLYCAPTURE_FRAMERATE_120";
		break;

	case FLYCAPTURE_FRAMERATE_240:
		return "FLYCAPTURE_FRAMERATE_240";
		break;

	case FLYCAPTURE_FRAMERATE_ANY:
		return "FLYCAPTURE_FRAMERATE_ANY";
		break;

	default:
		return "FLYCAPTURE_FRAMERATE **UNKNOWN**";
	}

}


#endif

/*
RATE_FLYCAPTURE_FRAME 1_875,
ATE_   FLYCAPTURE_FRAMER 3_75,
ATE_ER   FLYCAPTURE_FRAM 7_5,
_   FLYCAPTURE_FRAMERATE 15,
_   FLYCAPTURE_FRAMERATE 30,
E_   FLYCAPTURE_FRAMERAT 50,
FLYCAPTURE_FRAMERATE_60,
FLYCAPTURE_FRAMERATE_120,
FLYCAPTURE_FRAMERATE_240,
FLYCAPTURE_NUM_FRAMERATES,
FLYCAPTURE_FRAMERATE_CUSTOM,
URE_FRAMERATE_ANY,    FLYCAPT
*/
