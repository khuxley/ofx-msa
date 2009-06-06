
#ifdef A_VIDEO_CAPTURE_POINTGREY

#include "APointGreyGrabber.h"

//-------------------------------------------------------------------------------------------------------------------------------
//
APointGreyGrabber::APointGreyGrabber()
{

	FlyCaptureContext	context = NULL;
	//arpBuffers;

	hasNewImage = false;
	grabbedFirstImage = false;
	incomingImageNeedsConversion = true;

	availableFeatureAmount = 0;
}


//-------------------------------------------------------------------------------------------------------------------------------
//
APointGreyGrabber::~APointGreyGrabber()
{
	releaseResources();
}


//-------------------------------------------------------------------------------------------------------------------------------
//
int APointGreyGrabber::init( int _width, int _height, int _format, int _targetFormat, int _framerate )
{
	tmpCount = 0;


	//
	// Create the context.
	//
	error = flycaptureCreateContext( &context );
	_CHECK_ERROR( error, "flycaptureCreateContext()" );

	//
	// Initialize the camera.
	//
	printf( "Initializing camera %u.\n", 0 );
	error = flycaptureInitialize( context, 0 );
	_CHECK_ERROR( error, "flycaptureInitialize()" );

	desiredVideoMode = APointGreyGrabberVideoFormatHelper::videoFormatFromParams( _width, _height, _format );
	desiredFrameRate = APointGreyGrabberFramerateHelper::numToFlyCapFramerate( _framerate );

	bool isSupported = false;
	bool bailedFramerate = false;

	flycaptureCheckVideoMode( context, desiredVideoMode, desiredFrameRate, &isSupported );

	if( !isSupported )
	{
		int bailCnt = 0;
		bool secondaryFormatFound = false;

		FlyCaptureVideoMode secondaryVideoMode = desiredVideoMode;
		FlyCaptureFrameRate secondaryFrameRate = desiredFrameRate;

		while( !secondaryFormatFound )
		{

			int tmpBailFrameRateCnt = 0;
			bool canDoThisFormatWithAFramerate = false;
			bool hadToBailDoingThisFormatWithFramerate = false;
			while( !canDoThisFormatWithAFramerate && !hadToBailDoingThisFormatWithFramerate )
			{
				secondaryFrameRate = APointGreyGrabberFramerateHelper::degradeFramerate( secondaryFrameRate );
				flycaptureCheckVideoMode( context, secondaryVideoMode, secondaryFrameRate, &secondaryFormatFound );
				tmpBailFrameRateCnt++;
				if( tmpBailFrameRateCnt > 30 )
				{
					hadToBailDoingThisFormatWithFramerate = true;
				}

			}

			if( hadToBailDoingThisFormatWithFramerate)
			{
				secondaryVideoMode = APointGreyGrabberVideoFormatHelper::degradeVideoFormat( secondaryVideoMode );
				flycaptureCheckVideoMode( context, secondaryVideoMode, secondaryFrameRate, &secondaryFormatFound );
			}

			bailCnt++;
			if( bailCnt > 2000 )
			{
				secondaryVideoMode = FLYCAPTURE_VIDEOMODE_ANY;
				secondaryFrameRate = FLYCAPTURE_FRAMERATE_ANY;
				secondaryFormatFound = true;
				bailedFramerate = true;
				cout << "Bailed from trying to find a suitable framerate." << endl;
			}
		}

		desiredVideoMode = secondaryVideoMode;
		desiredFrameRate = secondaryFrameRate;

	}

	//
	// Start grabbing images in the current videomode and framerate.
	//
	printf( "Starting camera.\n\n" );

	error = flycaptureStart( context,  desiredVideoMode, desiredFrameRate );

	_CHECK_ERROR( error, "flycaptureStart()" );

	memset( &rawCameraImage, 0x0, sizeof( FlyCaptureImage ) );
	//memset( &convertedImage, 0x0, sizeof( FlyCaptureImage ) );

	targetFormat =_targetFormat;

	initFeatures();

	update();   // MEMO. call this to init width and height

	startThread(false, true);   // blocking, verbose

	return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::threadedFunction()
{
	while( 1 )
	{
		update();

		ofSleepMillis( 2 );
		//SDL_Delay (2); // delay a little bit
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------------------------
//
bool APointGreyGrabber::haveNewFrame()
{
	return hasNewImage;
}


//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::doneWithCurrentFrame()
{
	hasNewImage = false;
}


//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::update()
{
	if( !hasNewImage )
	{

		tmpCount++;

		error = flycaptureGrabImage2( context, &rawCameraImage );
		_CHECK_ERROR( error, "flycaptureGrabImage2()" );

		if( !grabbedFirstImage )
		{
			outputImageWidth = rawCameraImage.iCols;
			outputImageHeight = rawCameraImage.iRows;

			width = outputImageWidth;       // MEMO
			height = outputImageHeight;     // MEMO

			cout << "********************************" << endl;
			cout << "** outputImageWidth:	" << outputImageWidth << endl;
			cout << "** outputImageHeight:	" << outputImageHeight << endl;
			cout << "** format: " << pixelFormatToString( rawCameraImage.pixelFormat ) << endl;
			cout << "** framerate: " << APointGreyGrabberFramerateHelper::flyCapFrameRateToString( desiredFrameRate ) << endl;
			cout << "********************************" << endl;

			if( targetFormat == VID_FORMAT_BGR )
			{
				if( rawCameraImage.pixelFormat == FLYCAPTURE_BGR )
				{
					convertedImage = &rawCameraImage;
					incomingImageNeedsConversion = false;
					cout << "No conversion needed." << endl;
				}
				else
				{
					convertedImage = new FlyCaptureImage();
					convertedImage->pixelFormat = FLYCAPTURE_BGR;
					convertedImage->pData = new unsigned char[ outputImageWidth * outputImageHeight * 3 ];
					cout << "Conversion is needed." << endl;
				}
			}
			else
			{
				convertedImage = &rawCameraImage;
				incomingImageNeedsConversion = false;
				cout << "No conversion will be performed." << endl;
			}

			finalImageDataPointer = convertedImage->pData;

			grabbedFirstImage = true;
		}

		if( incomingImageNeedsConversion )
		{
			error = flycaptureConvertImage( context, &rawCameraImage, convertedImage );
			_CHECK_ERROR( error, "flycaptureConvertImage()" );
		}
		hasNewImage = true;

		//cout << tmpCount << " ";
	}

	//cout << tmpCount << " ";
}


//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::releaseResources()
{
	if( context != NULL )
	{
	    if(incomingImageNeedsConversion) {      // MEMO delete converted image
	        delete convertedImage->pData;
	        delete convertedImage;
	    }

		//
		// Stop grabbing images.
		//
		//printf( "Stopping camera.\n" );
		flycaptureStop( context );

		//
		// Destroy the camera context
		//
		flycaptureDestroyContext( context );


		context = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::setLoopType( int _loopType ) {}
void APointGreyGrabber::play() {}
void APointGreyGrabber::pause() {}
void APointGreyGrabber::stop() {}


//-------------------------------------------------------------------------------------------------------------------------------
//
void APointGreyGrabber::reportCameraInfo( const FlyCaptureInfoEx* pinfo )
{
	printf( "Serial number: %d\n", pinfo->SerialNumber );
	printf( "Camera model: %s\n", pinfo->pszModelName );
	printf( "Camera vendor: %s\n", pinfo->pszVendorName );
	printf( "Sensor: %s\n", pinfo->pszSensorInfo );
	printf( "DCAM compliance: %1.2f\n", (float)pinfo->iDCAMVer / 100.0 );
	printf( "Bus position: (%d,%d).\n", pinfo->iBusNum, pinfo->iNodeNum );
}

//-------------------------------------------------------------------------------------------------------------------------------
//
string APointGreyGrabber::pixelFormatToString( FlyCapturePixelFormat _pixelFormat )
{
	switch ( _pixelFormat )
	{

	case FLYCAPTURE_411YUV8:
		return "FLYCAPTURE_411YUV8 YUV 4:1:1.";
		break;

	case FLYCAPTURE_422YUV8:
		return "FLYCAPTURE_422YUV8 YUV 4:2:2.";
		break;

	case FLYCAPTURE_444YUV8:
		return 	"FLYCAPTURE_444YUV8 YUV 4:4:4.";
		break;

	case FLYCAPTURE_BGR:
		return "FLYCAPTURE_BGR 24 bit BGR";
		break;

	case FLYCAPTURE_BGRU:
		return "FLYCAPTURE_BGRU 32 bit BGRU";
		break;

	case FLYCAPTURE_MONO16:
		return "FLYCAPTURE_MONO16 16 bits of mono information.";
		break;

	case FLYCAPTURE_MONO8:
		return "FLYCAPTURE_MONO8 8 bits of mono information. ";
		break;

	case FLYCAPTURE_RAW16:
		return "FLYCAPTURE_RAW16 16 bit raw data output of sensor.";
		break;

	case FLYCAPTURE_RAW8:
		return "FLYCAPTURE_RAW8 8 bit raw data output of sensor.";
		break;

	case FLYCAPTURE_RGB16:
		return "FLYCAPTURE_RGB16 R=G=B=16 bits";
		break;

	case FLYCAPTURE_RGB8:
		return "FLYCAPTURE_RGB8 R=G=B=8 bits";
		break;

	case FLYCAPTURE_S_MONO16:
		return 	"FLYCAPTURE_S_MONO16 16 bits of signed mono information.";
		break;

	case FLYCAPTURE_S_RGB16:
		return "FLYCAPTURE_S_RGB16 R=G=B=16 bits signed";
		break;

	default:
		return "unknown!!";
		break;
	}
}

#endif //A_VIDEO_CAPTURE_POINTGREY

/*

FLYCAPTURE_411YUV8 YUV 4:1:1.
FLYCAPTURE_422YUV8 YUV 4:2:2.
FLYCAPTURE_444YUV8 YUV 4:4:4.
FLYCAPTURE_BGR 24 bit BGR
FLYCAPTURE_BGRU 32 bit BGRU
FLYCAPTURE_MONO16 16 bits of mono information.
FLYCAPTURE_MONO8 8 bits of mono information.
FLYCAPTURE_RAW16 16 bit raw data output of sensor.
FLYCAPTURE_RAW8 8 bit raw data output of sensor.
FLYCAPTURE_RGB16 R=G=B=16 bits
FLYCAPTURE_RGB8 R=G=B=8 bits
FLYCAPTURE_S_MONO16 16 bits of signed mono information.
FLYCAPTURE_S_RGB16 R=G=B=16 bits signed

*/
