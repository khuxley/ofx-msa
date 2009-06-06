/*
 *  ALibdc1394GrabberHelpers.h
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 10/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394

#ifndef __A_LIB_DC1394_GRABBER_HELPERS_H
#define __A_LIB_DC1394_GRABBER_HELPERS_H



#include <dc1394/dc1394.h>
#include <inttypes.h>

#include "pgrutils.h"

#include "../AVideoGrabberTypesAndEnums.h"

class ALibdc1394GrabberHelpers
{

public:

	static void print_format( uint32_t format );
	static uint32_t get_num_pixels(dc1394camera_t *camera, uint32_t format );
	static void print_color_coding( uint32_t color_id );
	static void print_mode_info( dc1394camera_t *camera , dc1394video_mode_t mode );

};

#endif

#endif
