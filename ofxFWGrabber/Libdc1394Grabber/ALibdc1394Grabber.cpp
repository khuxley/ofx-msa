/*
 *  ALibdc1394Grabber.cpp
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 10/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#ifdef A_VIDEO_CAPTURE_LIB_DC1394       // MEMO

#include "ALibdc1394Grabber.h"
#include "AVideoGrabber.h"

int ALibdc1394Grabber::g_cameraIndex = -1;
dc1394_t* ALibdc1394Grabber::d = NULL;

ALibdc1394Grabber::ALibdc1394Grabber()
{
	conversionNeeded = false;
	grabbedFirstImage = false;

	YUV_BYTE_ORDER = DC1394_BYTE_ORDER_UYVY; //DC1394_BYTE_ORDER_UYVY, DC1394_BYTE_ORDER_YUYV
	ISO_SPEED = DC1394_ISO_SPEED_400;

	bayerMethod = DC1394_BAYER_METHOD_BILINEAR;
	bayerPattern = DC1394_COLOR_FILTER_GBRG;

	/*
	DC1394_COLOR_FILTER_RGGB,
    DC1394_COLOR_FILTER_GBRG,
    DC1394_COLOR_FILTER_GRBG,
    DC1394_COLOR_FILTER_BGGR
	*/

	availableFeatureAmount = 0;

	camera = NULL;
	pixels = NULL;
}



ALibdc1394Grabber::~ALibdc1394Grabber()
{

	if (camera != NULL )
	{
		fprintf(stderr,"stop transmission\n");
		// Stop data transmission
		if (dc1394_video_set_transmission(camera,DC1394_OFF)!=DC1394_SUCCESS)
		{
			printf("couldn't stop the camera?\n");
		}
		// Close camera
		cleanupCamera();
	}

}


void ALibdc1394Grabber::close()
{

	if (camera != NULL )
	{
		fprintf(stderr,"stop transmission\n");
		// Stop data transmission
		if (dc1394_video_set_transmission(camera,DC1394_OFF)!=DC1394_SUCCESS)
		{
			printf("couldn't stop the camera?\n");
		}
		// Close camera
		cleanupCamera();
	}
}

int ALibdc1394Grabber::init( int _width, int _height, int _format, int _targetFormat, int _frameRate )
{

    cout << "initialising:"  << endl;
    cout << "width: " << _width << " height: " << _height << endl;
    cout <<" format " << vidFormatToString(_format) << "  targetFormat: " << vidFormatToString(_targetFormat) << endl;

	targetFormat = _targetFormat;

	dc1394framerate_t  desiredFrameRate = ALibdc1394GrabberFramerateHelper::numToDcLibFramerate( _frameRate );
	dc1394video_mode_t desiredVideoMode	= ALibdc1394GrabberVideoFormatHelper::videoFormatFromParams( _width, _height, _format );

	initCam( desiredVideoMode, desiredFrameRate );
    initInternalBuffers();

	startThread(false, true);   // blocking, verbose

	return 1;
}

int ALibdc1394Grabber::initCam( dc1394video_mode_t _videoMode, dc1394framerate_t _frameRate )
{

    dc1394error_t err;
	dc1394camera_t **cameras = NULL;
	uint32_t numCameras, i;
	dc1394camera_list_t * list;

    /* Initialise libdc1394 */
    if(!d) {
	d = dc1394_new ();
    }
    if (!d) {
        cout << "Failed to initialise libdc1394." << endl;
       return 1;
    }

    /* Find cameras */
	err=dc1394_camera_enumerate (d, &list);
    DC1394_ERR_RTN(err,"Failed to enumerate cameras");

    /* Verify that we have at least one camera */
    if (list->num == 0) {
        dc1394_log_error("No cameras found");
		cout << " No cameras found!" << endl;
        return 1;
    }

	numCameras = list->num;

/*
	if (err!=DC1394_SUCCESS && err != DC1394_NO_CAMERA)
	{
		fprintf( stderr, "Unable to look for cameras\n\n"  "On Linux, please check \n" "  - if the kernel modules `ieee1394',`raw1394' and `ohci1394' are loaded \n" "  - if you have read/write access to /dev/raw1394\n\n");
		//exit(1);
	}
*/

	printf( "There were %d cameras found attached to your PC\n", numCameras );

	/*-----------------------------------------------------------------------
	*  get the camera nodes and describe them as we find them
	*-----------------------------------------------------------------------*/
	/*
	if (numCameras < 1)  { fprintf(stderr, "no cameras found :(\n"); }
	camera = cameras[0];
	printf("working with the first camera on the bus\n");
	// free the other cameras
	for (i=1;i<numCameras;i++) { dc1394_free_camera(cameras[i]); }
	*/

// maybe the problem here is that we are using the first camera.
	camera = dc1394_camera_new (d, list->ids[++g_cameraIndex].guid);                     /* Work with first camera */
    if (!camera) {
        dc1394_log_error("Failed to initialize camera with guid %llx", list->ids[0].guid);
        return 1;
    }
    dc1394_camera_free_list (list);
	free(cameras);

	cout << "Using Camera with GUID " << camera->guid << endl;

	// get video modes:
	if (dc1394_video_get_supported_modes(camera,&video_modes)!=DC1394_SUCCESS)  { fprintf(stderr,"Can't get video modes\n"); cleanupCamera(); }


	printf("Listing Modes\n");
	for(i = 0; i < video_modes.num; i++ )  { dc1394video_mode_t mode = video_modes.modes[i]; ALibdc1394GrabberHelpers::print_mode_info( camera , mode ); }


/*
	// select highest res mode:
	for (i=video_modes.num-1;i>=0;i--)
	{
		if (!dc1394_is_video_mode_scalable(video_modes.modes[i]))
		{
			dc1394_get_color_coding_from_video_mode(camera,video_modes.modes[i], &coding);
			if (coding==DC1394_COLOR_CODING_MONO8)
			{
				video_mode = video_modes.modes[i];
				break;
			}
		}
	}
*/

	// search the list for our preferred video mode
	bool foundVideoMode = false;
  	for (i=video_modes.num-1;i>=0;i--)
	{
		if( video_modes.modes[i] == _videoMode ) { foundVideoMode = true; break; }
	}


	video_mode = _videoMode;

	dc1394_get_color_coding_from_video_mode(camera, video_mode, &coding);
	//dc1394_get_color_coding_from_video_mode(camera,video_modes.modes[i], &coding);

	//if ((dc1394_is_video_mode_scalable(video_modes.modes[i]))|| (coding!=DC1394_COLOR_CODING_MONO8))  { fprintf(stderr,"Could not get a valid MONO8 mode\n"); cleanupCamera(); }

	//cout << endl << "**** Chosen Color coding ****" << endl;
	//ALibdc1394GrabberHelpers::print_color_coding( coding );
	//cout << endl << "*****************************" << endl << endl;

	sourceFormatLibDC = coding;
	sourceFormat = ALibdc1394GrabberVideoFormatHelper::libcd1394ColorFormatToVidFormat(  coding );


	// get framerates
	if (dc1394_video_get_supported_framerates(camera,video_mode,&framerates)!=DC1394_SUCCESS)
	{
		fprintf(stderr,"Can't get framerates\n");
		cleanupCamera();
	}

	// search the list for our preferred framerate
	bool foundFramerate = false;
	for( i = 0; i < framerates.num; i++ )
	{
		if( framerates.framerates[i] == _frameRate )
		{
			framerate = framerates.framerates[i];
			foundFramerate = true;
			break;
		}
	}

	// if we didn't find it, select the highest one.
	if( !foundFramerate ) framerate=framerates.framerates[framerates.num-1];


	/*-----------------------------------------------------------------------
	*  setup capture
	*-----------------------------------------------------------------------*/
	fprintf(stderr,"Setting capture\n");

	dc1394_video_set_iso_speed(camera, DC1394_ISO_SPEED_400);

	dc1394_video_set_mode(camera, video_mode);
	dc1394_video_set_framerate(camera, framerate);

	if (dc1394_capture_setup(camera,4,DC1394_CAPTURE_FLAGS_DEFAULT)!=DC1394_SUCCESS)
	{
		fprintf( stderr,"unable to setup camera-\n"  "check line %d of %s to make sure\n" "that the video mode and framerate are\n" "supported by your camera\n",  __LINE__,__FILE__);
		cleanupCamera();
	}

	cout << "chosen video format: "; ALibdc1394GrabberHelpers::print_format( video_mode ); cout << endl;
	cout << "chosen frame rate: " << ALibdc1394GrabberFramerateHelper::DcLibFramerateToString( framerate ) << endl;

/*
	// report camera's features ----------------------------------
	if (dc1394_get_camera_feature_set(camera,&features) !=DC1394_SUCCESS)  { fprintf( stderr, "unable to get feature set\n"); }
	else  { dc1394_print_feature_set(&features); }
*/


	fprintf(stderr,"start transmission\n");
	/*-----------------------------------------------------------------------
	*  have the camera start sending us data
	*-----------------------------------------------------------------------*/
	if (dc1394_video_set_transmission(camera, DC1394_ON) !=DC1394_SUCCESS)
	{
		fprintf( stderr, "unable to start camera iso transmission\n");
		cleanupCamera();
	}

	fprintf(stderr,"wait transmission\n");
	/*-----------------------------------------------------------------------
	*  Sleep until the camera has a transmission
	*-----------------------------------------------------------------------*/
	dc1394switch_t status = DC1394_OFF;

	i = 0;
	while( status == DC1394_OFF && i++ < 5 )
	{
		usleep(50000);
		if (dc1394_video_get_transmission(camera, &status)!=DC1394_SUCCESS)
		{
			fprintf(stderr, "unable to get transmission status\n");
			cleanupCamera();
		}
	}

	if( i == 5 )
	{
		fprintf(stderr,"Camera doesn't seem to want to turn on!\n");
		cleanupCamera();
	}


    dc1394_get_image_size_from_video_mode(camera, video_mode, &width, &height);
    outputImageWidth = width;
    outputImageHeight = height;

	initFeatures();

	fprintf(stderr,"capture\n");

	return 1;
}




bool ALibdc1394Grabber::haveNewFrame()
{
	return hasNewImage;
}

void ALibdc1394Grabber::doneWithCurrentFrame()
{
	hasNewImage = false;
}

void ALibdc1394Grabber::initInternalBuffers()
{
	int bpp = 0;

	if( targetFormat == VID_FORMAT_GREYSCALE || targetFormat == VID_FORMAT_Y8 ) { bpp = 1; }
	else if( targetFormat == VID_FORMAT_RGB || targetFormat == VID_FORMAT_BGR ) { bpp = 3; }
	else{ cout << "**** " << endl << "*** ALibdc1394Grabber: Unsupported output format! *** " << endl << "***************************************** " << endl; }

	finalImageDataBufferLength = width*height*bpp;
	pixels = new unsigned char[finalImageDataBufferLength];
	for ( int i = 0; i < finalImageDataBufferLength; i++ ) { pixels[i] = 0; }

}

void ALibdc1394Grabber::threadedFunction()
{
	while( 1 )
	{
		captureFrame();
		ofSleepMillis(2);
	}

	return;
}

unsigned char* ALibdc1394Grabber::getPixels()
{
    return pixels;
}

void ALibdc1394Grabber::captureFrame()
{

	if( !hasNewImage && (camera != NULL ) )
	{
		/*-----------------------------------------------------------------------
		*  capture one frame
		*-----------------------------------------------------------------------*/
		if (dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &frame) != DC1394_SUCCESS)
		{
			fprintf(stderr, "unable to capture a frame\n");
			cleanupCamera();
		}

		if( !grabbedFirstImage )
		{
			setBayerPatternIfNeeded();
			grabbedFirstImage = true;
		}

		processCameraImageData( frame->image );

		dc1394_capture_enqueue(camera, frame);

		hasNewImage = true;
	}

}

/*
  DC1394_FEATURE_BRIGHTNESS= 416,
  DC1394_FEATURE_EXPOSURE,
  DC1394_FEATURE_SHARPNESS,
  DC1394_FEATURE_WHITE_BALANCE,
  DC1394_FEATURE_HUE,
  DC1394_FEATURE_SATURATION,
  DC1394_FEATURE_GAMMA,
  DC1394_FEATURE_SHUTTER,
  DC1394_FEATURE_GAIN,
  DC1394_FEATURE_IRIS,
  DC1394_FEATURE_FOCUS,
  DC1394_FEATURE_TEMPERATURE,
  DC1394_FEATURE_TRIGGER,
  DC1394_FEATURE_TRIGGER_DELAY,
  DC1394_FEATURE_WHITE_SHADING,
  DC1394_FEATURE_FRAME_RATE,
  DC1394_FEATURE_ZOOM,
  DC1394_FEATURE_PAN,
  DC1394_FEATURE_TILT,
  DC1394_FEATURE_OPTICAL_FILTER,
  DC1394_FEATURE_CAPTURE_SIZE,
  DC1394_FEATURE_CAPTURE_QUALITY
*/

/*
	VID_FORMAT_GREYSCALE  =	0,
	VID_FORMAT_BGR		  =	1,

	VID_FORMAT_YUV411	  =	2,
	VID_FORMAT_YUV422	  = 3,
	VID_FORMAT_YUV444	  =	4,

	VID_FORMAT_RGB		  =	5,

	VID_FORMAT_Y8		  = 6,
	VID_FORMAT_Y16		  = 7
*/

/*
  DC1394_COLOR_CODING_MONO8,
  DC1394_COLOR_CODING_YUV411,
  DC1394_COLOR_CODING_YUV422,
  DC1394_COLOR_CODING_YUV444,
  DC1394_COLOR_CODING_RGB8,

  DC1394_COLOR_CODING_MONO16,
  DC1394_COLOR_CODING_RGB16,
  DC1394_COLOR_CODING_MONO16S,
  DC1394_COLOR_CODING_RGB16S,
  DC1394_COLOR_CODING_RAW8,

  DC1394_COLOR_CODING_RAW16
*/

void ALibdc1394Grabber::processCameraImageData( unsigned char* _cameraImageData )
{
	if( sourceFormatLibDC == DC1394_COLOR_CODING_RAW8 || sourceFormatLibDC == DC1394_COLOR_CODING_MONO8 )
	{

		if( targetFormat == VID_FORMAT_GREYSCALE || targetFormat == VID_FORMAT_Y8 )
		{
			memcpy ( pixels, _cameraImageData, finalImageDataBufferLength );
		}
		else if( targetFormat == VID_FORMAT_RGB )
		{
			dc1394_bayer_decoding_8bit( _cameraImageData, pixels, width, height,  bayerPattern, bayerMethod );
		}
		else if ( targetFormat == VID_FORMAT_BGR )
		{
			dc1394_bayer_decoding_8bit( _cameraImageData, pixels, width, height,  bayerPattern, bayerMethod ); // we should really be converting this
		}
		else
		{
			cout << "************* ALibdc1394Grabber::processCameraImageData Unsupported target format (" << vidFormatToString( targetFormat ) << ") from DC1394_COLOR_CODING_RAW8 or DC1394_COLOR_CODING_MONO8 *************" << endl;
		}

	}
	else if(  sourceFormatLibDC == DC1394_COLOR_CODING_MONO16 || sourceFormatLibDC == DC1394_COLOR_CODING_RAW16 )
	{
		if( targetFormat == VID_FORMAT_RGB )
		{
//			dc1394_bayer_decoding_16bit( _cameraImageData, pixels, width, height,  bayerPattern, bayerMethod );
		}
		else if ( targetFormat == VID_FORMAT_BGR )
		{
//			dc1394_bayer_decoding_16bit( _cameraImageData, pixels, width, height,  bayerPattern, bayerMethod ); // we should really be converting this
		}
		else
		{
			cout << "************* ALibdc1394Grabber::processCameraImageData Unsupported target format (" << vidFormatToString( targetFormat ) << ") from DC1394_COLOR_CODING_MONO16 or DC1394_COLOR_CODING_RAW16 *************" << endl;
		}
	}
	else if(  sourceFormatLibDC == DC1394_COLOR_CODING_YUV411 || sourceFormatLibDC == DC1394_COLOR_CODING_YUV422 || sourceFormatLibDC == DC1394_COLOR_CODING_YUV444 )
	{
		if( targetFormat == VID_FORMAT_RGB )
		{
			dc1394_convert_to_RGB8( _cameraImageData, pixels, width, height, YUV_BYTE_ORDER, sourceFormatLibDC, 16);
		}
		else if ( targetFormat == VID_FORMAT_BGR )
		{
			dc1394_convert_to_RGB8( _cameraImageData, pixels, width, height, YUV_BYTE_ORDER, sourceFormatLibDC, 16); // we should really be converting this
		}
		else
		{
			cout << "************* ALibdc1394Grabber::processCameraImageData Unsupported target format (" << vidFormatToString( targetFormat ) << ") from DC1394_COLOR_CODING_YUV411, DC1394_COLOR_CODING_YUV422 or DC1394_COLOR_CODING_YUV444 *************" << endl;
		}

	}
	else if(  sourceFormatLibDC == DC1394_COLOR_CODING_RGB8 )
	{
		if( targetFormat == VID_FORMAT_RGB )
		{
			memcpy ( pixels, _cameraImageData, finalImageDataBufferLength );
		}
		else if ( targetFormat == VID_FORMAT_BGR )
		{
			memcpy ( pixels, _cameraImageData, finalImageDataBufferLength ); // we should really be converting this
		}
		else
		{
			cout << "************* ALibdc1394Grabber::processCameraImageData Unsupported target format (" << vidFormatToString( targetFormat ) << ") from DC1394_COLOR_CODING_RGB8 *************" << endl;
		}
	}
	else
	{

		cout << "************* ALibdc1394Grabber::processCameraImageData Unsupported source format! *************" << endl;
	}

}

void ALibdc1394Grabber::setBayerPatternIfNeeded()
{
	if( sourceFormatLibDC == DC1394_COLOR_CODING_RAW8 || sourceFormatLibDC == DC1394_COLOR_CODING_MONO8 || sourceFormatLibDC == DC1394_COLOR_CODING_MONO16 || sourceFormatLibDC == DC1394_COLOR_CODING_RAW16 )
	{
		if( targetFormat == VID_FORMAT_RGB || targetFormat == VID_FORMAT_BGR )
		{

		dc1394color_filter_t tmpBayerPattern;
		if( dc1394_format7_get_color_filter(camera, video_mode, &tmpBayerPattern) != DC1394_SUCCESS )
		{
			cout << "ALibdc1394Grabber::setBayerPatternIfNeeded(), Failed to get the dc1394_format7_get_color_filter." << endl;
		}
		else
		{
			cout << "ALibdc1394Grabber::setBayerPatternIfNeeded(), We got a pattern, it was: " << tmpBayerPattern << endl;
		}


			if ( getBayerTile( camera, &bayerPattern ) != DC1394_SUCCESS )
			{
				fprintf( stderr, "************* Could not get bayer tile pattern from camera\n *********" );
			} else { cout << "grabbed a bayer pattern from the camera" << endl; }
		}

	}
}



/*-----------------------------------------------------------------------
 *  Releases the cameras and exits
 *-----------------------------------------------------------------------*/
void ALibdc1394Grabber::cleanupCamera()
{
  dc1394_capture_stop(camera);
  dc1394_video_set_transmission(camera, DC1394_OFF);

  /* cleanup and exit */
  dc1394_camera_free (camera);
  camera = NULL;

  if(d) {
    dc1394_free (d);
    d = NULL;
  }
}


/*
  DC1394_BAYER_METHOD_NEAREST=0,
  DC1394_BAYER_METHOD_SIMPLE,
  DC1394_BAYER_METHOD_BILINEAR,
  DC1394_BAYER_METHOD_HQLINEAR,
  DC1394_BAYER_METHOD_DOWNSAMPLE,
  DC1394_BAYER_METHOD_EDGESENSE,
  DC1394_BAYER_METHOD_VNG,
  DC1394_BAYER_METHOD_AHD
*/

#endif


