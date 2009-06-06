/*
 *  ALibdc1394GrabberHelpers.cpp
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 10/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */
#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394

#include "ALibdc1394GrabberHelpers.h"

/*-----------------------------------------------------------------------
 *  Prints the type of format to standard out
 *-----------------------------------------------------------------------*/
void ALibdc1394GrabberHelpers::print_format( uint32_t format )
{
#define print_case(A) case A: printf(#A ""); break;

  switch( format ) {
    print_case(DC1394_VIDEO_MODE_160x120_YUV444);
    print_case(DC1394_VIDEO_MODE_320x240_YUV422);
    print_case(DC1394_VIDEO_MODE_640x480_YUV411);
    print_case(DC1394_VIDEO_MODE_640x480_YUV422);
    print_case(DC1394_VIDEO_MODE_640x480_RGB8);
    print_case(DC1394_VIDEO_MODE_640x480_MONO8);
    print_case(DC1394_VIDEO_MODE_640x480_MONO16);
    print_case(DC1394_VIDEO_MODE_800x600_YUV422);
    print_case(DC1394_VIDEO_MODE_800x600_RGB8);
    print_case(DC1394_VIDEO_MODE_800x600_MONO8);
    print_case(DC1394_VIDEO_MODE_1024x768_YUV422);
    print_case(DC1394_VIDEO_MODE_1024x768_RGB8);
    print_case(DC1394_VIDEO_MODE_1024x768_MONO8);
    print_case(DC1394_VIDEO_MODE_800x600_MONO16);
    print_case(DC1394_VIDEO_MODE_1024x768_MONO16);
    print_case(DC1394_VIDEO_MODE_1280x960_YUV422);
    print_case(DC1394_VIDEO_MODE_1280x960_RGB8);
    print_case(DC1394_VIDEO_MODE_1280x960_MONO8);
    print_case(DC1394_VIDEO_MODE_1600x1200_YUV422);
    print_case(DC1394_VIDEO_MODE_1600x1200_RGB8);
    print_case(DC1394_VIDEO_MODE_1600x1200_MONO8);
    print_case(DC1394_VIDEO_MODE_1280x960_MONO16);
    print_case(DC1394_VIDEO_MODE_1600x1200_MONO16);

  default:
    fprintf(stderr,"Unknown format\n");
//    exit(1);
  }

}

/*-----------------------------------------------------------------------
 *  Returns the number of pixels in the image based upon the format
 *-----------------------------------------------------------------------*/
uint32_t ALibdc1394GrabberHelpers::get_num_pixels(dc1394camera_t *camera, uint32_t format ) {
  uint32_t w,h;

  dc1394_get_image_size_from_video_mode(camera, format,&w,&h);

  return w*h;
}

/*-----------------------------------------------------------------------
 *  Prints the type of color encoding
 *-----------------------------------------------------------------------*/
void ALibdc1394GrabberHelpers::print_color_coding( uint32_t color_id )
{
  switch( color_id ) {
  case DC1394_COLOR_CODING_MONO8:
    printf("MONO8");
    break;
  case DC1394_COLOR_CODING_YUV411:
    printf("YUV411");
    break;
  case DC1394_COLOR_CODING_YUV422:
    printf("YUV422");
    break;
  case DC1394_COLOR_CODING_YUV444:
    printf("YUV444");
    break;
  case DC1394_COLOR_CODING_RGB8:
    printf("RGB8");
    break;
  case DC1394_COLOR_CODING_MONO16:
    printf("MONO16");
    break;
  case DC1394_COLOR_CODING_RGB16:
    printf("RGB16");
    break;
  case DC1394_COLOR_CODING_MONO16S:
    printf("MONO16S");
    break;
  case DC1394_COLOR_CODING_RGB16S:
    printf("RGB16S");
    break;
  case DC1394_COLOR_CODING_RAW8:
    printf("RAW8");
    break;
  case DC1394_COLOR_CODING_RAW16:
    printf("RAW16");
    break;

  default:
    fprintf(stderr,"Unknown color coding = %d\n",color_id);
//    exit(1);
  }
}


/*-----------------------------------------------------------------------
 *  Prints various information about the mode the camera is in
 *-----------------------------------------------------------------------*/
void ALibdc1394GrabberHelpers::print_mode_info( dc1394camera_t *camera , dc1394video_mode_t mode )
{

  printf("Mode: ");
  print_format(mode);
  printf("\n");

  dc1394framerates_t framerates;
  if(dc1394_video_get_supported_framerates(camera,mode,&framerates) != DC1394_SUCCESS) {
    fprintf( stderr, "Can't get frame rates\n");
  //  exit(1);
  }

  printf("Frame Rates:\n");
  for(unsigned int j = 0; j < framerates.num; j++ ) {
    dc1394framerate_t rate = framerates.framerates[j];
    float f_rate;
    dc1394_framerate_as_float(rate,&f_rate);
    printf("  [%d] rate = %f\n",j,f_rate );
  }

}

#endif


