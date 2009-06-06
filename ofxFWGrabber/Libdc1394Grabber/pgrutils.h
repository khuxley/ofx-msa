

#ifdef A_VIDEO_CAPTURE_LIB_DC1394       // MEMO

#ifndef PGRUTILS_LIBDC_2_H
#define PGRUTILS_LIBDC_2_H

//#include <dc1394/dc1394_control.h>
//#include <dc1394/dc1394_register.h>

#include <dc1394/dc1394.h>
#include <dc1394/control.h>
#include <dc1394/register.h>
#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>

dc1394error_t
getBayerTile( dc1394camera_t* camera,
	      dc1394color_filter_t* bayerPattern );


#endif // PGRUTILS_LIBDC_2_H

#endif
