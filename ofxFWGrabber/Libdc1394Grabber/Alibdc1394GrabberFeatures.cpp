/*
 *  Alibdc1394GrabberFeatures.cpp
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 16/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

#include "../AVideoGrabber.h"

#ifdef A_VIDEO_CAPTURE_LIB_DC1394

#include "ALibdc1394Grabber.h"

void ALibdc1394Grabber::initFeatures()
{

	dc1394featureset_t tmpFeatureSet;

	// get camera features ----------------------------------
	if ( dc1394_feature_get_all(camera,&tmpFeatureSet) !=DC1394_SUCCESS)
	{
        fprintf( stderr, "unable to get feature set\n");
    }
	else
	{
		//dc1394_print_feature_set(&tmpFeatureSet);

		int tmpAvailableFeatures = 0;
		for( int i = 0; i < CAMERA_FEATURE_AMOUNT; i++ )
		{
			if( tmpFeatureSet.feature[i].available ) { tmpAvailableFeatures++; }
		}

		availableFeatureAmount = tmpAvailableFeatures;

		featureVals = new AGrabberCameraFeatureVals[availableFeatureAmount];

		tmpAvailableFeatures = 0;

        cout << "Name\t" << "\tAbs." << "\tCurr." << "\tCurr2."  << "\tMin." << "\tMax." << endl;
		for( int i = 0; i < CAMERA_FEATURE_AMOUNT; i++ )
		{
			if(tmpFeatureSet.feature[i].available)
			{
				featureVals[tmpAvailableFeatures].feature			= Alibdc1394GrabberFeatureHelper::libdcFeatureToAVidFeature( tmpFeatureSet.feature[i].id );
				featureVals[tmpAvailableFeatures].name				= cameraFeatureToTitle( featureVals[tmpAvailableFeatures].feature );

				featureVals[tmpAvailableFeatures].isPresent			= tmpFeatureSet.feature[i].available;
				featureVals[tmpAvailableFeatures].isReadable		= tmpFeatureSet.feature[i].readout_capable;

				featureVals[tmpAvailableFeatures].hasAbsoluteMode	= tmpFeatureSet.feature[i].absolute_capable;
				featureVals[tmpAvailableFeatures].absoluteModeActive = tmpFeatureSet.feature[i].abs_control;

                for(unsigned int j = 0; j < tmpFeatureSet.feature[i].modes.num; j++)
                {
                    if(tmpFeatureSet.feature[i].modes.modes[j] == DC1394_FEATURE_MODE_MANUAL)
                    {
                        featureVals[tmpAvailableFeatures].hasManualMode	= true;
                    }
                    else if(tmpFeatureSet.feature[i].modes.modes[j] == DC1394_FEATURE_MODE_AUTO)
                    {
                        featureVals[tmpAvailableFeatures].hasAutoMode = true;
                    }
                    else if(tmpFeatureSet.feature[i].modes.modes[j] == DC1394_FEATURE_MODE_ONE_PUSH_AUTO)
                    {
                        featureVals[tmpAvailableFeatures].hasOnePush = true;
                    }
                }

				featureVals[tmpAvailableFeatures].isOnOffSwitchable	= tmpFeatureSet.feature[i].on_off_capable;
				featureVals[tmpAvailableFeatures].isOn				= tmpFeatureSet.feature[i].is_on;

                if(tmpFeatureSet.feature[i].current_mode == DC1394_FEATURE_MODE_MANUAL)
                {
                    featureVals[tmpAvailableFeatures].hasManualActive	= true;
                }
                else if(tmpFeatureSet.feature[i].current_mode == DC1394_FEATURE_MODE_AUTO)
                {
                    featureVals[tmpAvailableFeatures].hasAutoModeActive	= true;
                }
                else if(tmpFeatureSet.feature[i].current_mode == DC1394_FEATURE_MODE_ONE_PUSH_AUTO)
                {
                    featureVals[tmpAvailableFeatures].hasOnePushActive = true;
                }


				if( featureVals[tmpAvailableFeatures].hasAbsoluteMode )
				{
					dc1394_feature_set_absolute_control( camera, tmpFeatureSet.feature[i].id, DC1394_ON );


					featureVals[tmpAvailableFeatures].currVal = tmpFeatureSet.feature[i].abs_value;

					featureVals[tmpAvailableFeatures].minVal  = tmpFeatureSet.feature[i].abs_min;
					featureVals[tmpAvailableFeatures].maxVal  = tmpFeatureSet.feature[i].abs_max;

				}
				else
				{
                    if(tmpFeatureSet.feature[i].id == DC1394_FEATURE_WHITE_BALANCE)
                    {
                        featureVals[tmpAvailableFeatures].currVal = (float)tmpFeatureSet.feature[i].BU_value;
                        featureVals[tmpAvailableFeatures].currVal2 = (float)tmpFeatureSet.feature[i].RV_value;
                        featureVals[tmpAvailableFeatures].minVal  = (float)tmpFeatureSet.feature[i].min;
                        featureVals[tmpAvailableFeatures].maxVal  = (float)tmpFeatureSet.feature[i].max;
                    }
                    else {
                        featureVals[tmpAvailableFeatures].currVal = (float)tmpFeatureSet.feature[i].value;
                        featureVals[tmpAvailableFeatures].minVal  = (float)tmpFeatureSet.feature[i].min;
                        featureVals[tmpAvailableFeatures].maxVal  = (float)tmpFeatureSet.feature[i].max;
                    }
				}

				cout << setw(13) << featureVals[tmpAvailableFeatures].name
				<< " :\t" << featureVals[tmpAvailableFeatures].hasAbsoluteMode
				<< "\t" << featureVals[tmpAvailableFeatures].currVal;

				if(tmpFeatureSet.feature[i].id == DC1394_FEATURE_WHITE_BALANCE)
				{
				    cout << "\t" << featureVals[tmpAvailableFeatures].currVal2;
                }
                else
                {
                    cout << "\t";
                }

				cout << "\t" << featureVals[tmpAvailableFeatures].minVal
				<< "\t" << featureVals[tmpAvailableFeatures].maxVal << endl;

				tmpAvailableFeatures++;
			}
		}

	}

}

void ALibdc1394Grabber::updateAllFeatureVals()
{

	if( availableFeatureAmount == 0 ) return;

	for( int i = 0; i < availableFeatureAmount; i++ )
	{
		if(featureVals[i].isPresent)
		{
			updateFeatureVals( &featureVals[i] );
		}
	}

}


void ALibdc1394Grabber::updateFeatureVals( AGrabberCameraFeatureVals* _feature )
{

	dc1394feature_info_t tmpFeatureVals;
	tmpFeatureVals.id = Alibdc1394GrabberFeatureHelper::AVidFeatureToLibdcFeature( _feature->feature );

	dc1394_feature_get( camera, &tmpFeatureVals);

	if( _feature->hasAbsoluteMode )
	{
		_feature->currVal = tmpFeatureVals.abs_value;
		_feature->minVal = tmpFeatureVals.abs_min;
		_feature->maxVal = tmpFeatureVals.abs_max;
	}
	else
	{
        if(tmpFeatureVals.id == DC1394_FEATURE_WHITE_BALANCE)
        {
            _feature->currVal = (float)tmpFeatureVals.BU_value;
            _feature->currVal2 = (float)tmpFeatureVals.RV_value;
            _feature->minVal = (float)tmpFeatureVals.min;
            _feature->maxVal = (float)tmpFeatureVals.max;
        }
        else {
            _feature->currVal = (float)tmpFeatureVals.value;
            _feature->minVal = (float)tmpFeatureVals.min;
            _feature->maxVal = (float)tmpFeatureVals.max;
        }
	}

	if( _feature->isOnOffSwitchable )
	{
		_feature->isOn = tmpFeatureVals.is_on;
	}

	if( _feature->hasManualMode )
	{
        if(tmpFeatureVals.current_mode == DC1394_FEATURE_MODE_MANUAL)
        {
            _feature->hasManualActive = true;
        }
        else
        {
            _feature->hasManualActive = false;
        }
	}

	if( _feature->hasAutoMode )
	{
        if(tmpFeatureVals.current_mode == DC1394_FEATURE_MODE_AUTO)
        {
            _feature->hasAutoModeActive = true;
        }
        else
        {
            _feature->hasAutoModeActive = false;
        }
	}

    if( _feature->hasOnePush )
	{
        if(tmpFeatureVals.current_mode == DC1394_FEATURE_MODE_ONE_PUSH_AUTO)
        {
            _feature->hasOnePushActive = true;
        }
        else
        {
            _feature->hasOnePushActive = false;
        }
	}

}

void ALibdc1394Grabber::setFeatureAbsoluteVal( float _val, int _feature )
{
	dc1394error_t err;

	//cout << " ALibdc1394Grabber::setFeatureAbsoluteVal " << _val << ", " << _feature << endl;

	err = dc1394_feature_set_absolute_value( camera, Alibdc1394GrabberFeatureHelper::AVidFeatureToLibdcFeature( _feature ), _val );
	if( err != DC1394_SUCCESS )
	{
		cout << "*******************" << endl;
		//cout << dc1394_error_strings[err] << endl;
		cout << "ALibdc1394Grabber::setFeatureAbsoluteVal, failed to set feature: " << cameraFeatureToTitle( _feature ) << endl;
		cout << "*******************" << endl;
	}
}

void ALibdc1394Grabber::setFeatureWhiteBalance( float u_b_value, float v_r_value)
{
	dc1394error_t err;

	err = dc1394_feature_whitebalance_set_value( camera, (unsigned int) u_b_value, (unsigned int) v_r_value );
	if( err != DC1394_SUCCESS )
	{
		cout << "*******************" << endl;
		cout << "ALibdc1394Grabber::setFeatureWhiteBalance, failed to set feature" << endl;
		cout << "*******************" << endl;
	}
}

void ALibdc1394Grabber::setFeatureVal( float _val, int _feature )
{
	dc1394error_t err;

	//cout << " ALibdc1394Grabber::setFeatureVal " << _val << ", " << _feature << endl;

	err = dc1394_feature_set_value( camera, Alibdc1394GrabberFeatureHelper::AVidFeatureToLibdcFeature( _feature ), (unsigned int)_val );
	if( err != DC1394_SUCCESS )
	{
		cout << "*******************" << endl;
		//cout << dc1394_error_strings[err] << endl;
		cout << "ALibdc1394Grabber::setFeatureVal, failed to set feature: " << cameraFeatureToTitle( _feature ) << endl;
		cout << "*******************" << endl;
	}

}


void ALibdc1394Grabber::setFeatureMode( int _feature, int _featureMode )
{
    dc1394error_t err;
    dc1394feature_t tmpFeature = Alibdc1394GrabberFeatureHelper::AVidFeatureToLibdcFeature( _feature );

	if (_featureMode == FEATURE_MODE_MANUAL)
	{
	    err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_MANUAL );
	}
	else if(_featureMode == FEATURE_MODE_AUTO)
	{
	    err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_AUTO );
	}
	else if(_featureMode == FEATURE_MODE_ONE_PUSH_AUTO)
	{
	    err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_ONE_PUSH_AUTO );
	}

    if( err != DC1394_SUCCESS )
	{
		cout << "*******************" << endl;
		cout << "ALibdc1394Grabber::setFeatureMode, failed to set mode for feature: " << cameraFeatureToTitle( _feature ) << endl;
		cout << "*******************" << endl;
	}
}

void ALibdc1394Grabber::setFeatureStateOnOff( bool _val, int _feature, int _featureMode )
{

	dc1394error_t err;

cout << " ALibdc1394Grabber::setFeatureOnOffState " << _val << ", " << _feature << ", " << _featureMode << endl;

	dc1394feature_t tmpFeature = Alibdc1394GrabberFeatureHelper::AVidFeatureToLibdcFeature( _feature );

	if( _featureMode == FEATURE_AUTO_MODE )
	{
		if( _val )
		{
			err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_AUTO );
		}
		else
		{
			err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_MANUAL );
		}
	}
	else if( _featureMode == FEATURE_ONESHOT_MODE )
	{

		// set feature to manual first (?)
		setFeatureStateOnOff( false, _feature, FEATURE_AUTO_MODE );

		err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_ONE_PUSH_AUTO );
	}
	else if( _featureMode == FEATURE_IS_ON )
	{
		if( _val ) { err = dc1394_feature_set_power( camera, tmpFeature, DC1394_ON ); }
		else { err = dc1394_feature_set_power( camera, tmpFeature, DC1394_OFF ); }

	}

	if( err != DC1394_SUCCESS )
	{
		cout << "*******************" << endl;
		//cout << dc1394_error_strings[err] << endl;
		cout << "ALibdc1394Grabber::setFeatureStateOnOff, failed to set feature: " << cameraFeatureToTitle( _feature ) << endl;
		cout << "*******************" << endl;
	}

}



void ALibdc1394Grabber::setFeaturesOnePushMode()
{


	//DC1394_FEATURE_MODE_ONE_PUSH_AUTO, DC1394_FEATURE_MODE_AUTO

	setFeatureStateOnOff( false, FEATURE_SHUTTER, FEATURE_MODE_AUTO );
	dc1394_feature_set_mode( camera, DC1394_FEATURE_SHUTTER,	DC1394_FEATURE_MODE_ONE_PUSH_AUTO );

	//dc1394_feature_set_mode( camera, DC1394_FEATURE_WHITE_BALANCE, DC1394_FEATURE_MODE_ONE_PUSH_AUTO );


	setFeatureStateOnOff( false, FEATURE_GAIN, FEATURE_MODE_AUTO );
	dc1394_feature_set_mode( camera, DC1394_FEATURE_GAIN,		DC1394_FEATURE_MODE_ONE_PUSH_AUTO );

	//dc1394_feature_set_mode( camera, DC1394_FEATURE_IRIS,		DC1394_FEATURE_MODE_ONE_PUSH_AUTO );

	setFeatureStateOnOff( false, FEATURE_EXPOSURE, FEATURE_MODE_AUTO );
	dc1394_feature_set_mode( camera, DC1394_FEATURE_EXPOSURE,	DC1394_FEATURE_MODE_ONE_PUSH_AUTO );

	//dc1394_feature_set_mode( camera, DC1394_FEATURE_BRIGHTNESS, DC1394_FEATURE_MODE_ONE_PUSH_AUTO );
}


int ALibdc1394Grabber::stringToFeature( string _featureName )
{


	return -1;
}


#endif //A_VIDEO_CAPTURE_LIB_DC1394



/*
dc1394_feature_set_mode()

Arguments:
dc1394camera_t	:	*camera	:	A pointer to an initialized camera structure
dc1394feature_t	:	feature	:	The feature identifier (DC1394_FEATURE_SHUTTER,...)
dc1394feature_mode_t	:	mode

DC1394_FEATURE_MODE_MANUAL= 0,
DC1394_FEATURE_MODE_AUTO,
DC1394_FEATURE_MODE_ONE_PUSH_AUTO

*/


/*
string name;

int feature;

float currVal;

float minVal;
float maxVal;

bool isPresent;
bool isReadable;

bool hasAbsoluteMode;
bool absoluteModeActive;

bool hasManualMode;

bool isOn;
bool isOnOffSwitchable;

bool hasOnePush;
bool hasOnePushActive;

bool hasAutoMode;
bool hasAutoModeActive;
*/



/*
dc1394feature_t    id;
dc1394bool_t       available;

dc1394bool_t       one_push;
dc1394bool_t       absolute_capable;
dc1394bool_t       readout_capable;
dc1394bool_t       on_off_capable;
dc1394bool_t       auto_capable;
dc1394bool_t       manual_capable;
dc1394bool_t       polarity_capable;
dc1394switch_t     one_push_active;
dc1394switch_t     is_on;
dc1394bool_t       auto_active;

dc1394trigger_modes_t    trigger_modes;
dc1394trigger_mode_t     trigger_mode;
dc1394trigger_polarity_t trigger_polarity;
dc1394trigger_sources_t  trigger_sources;
dc1394trigger_source_t   trigger_source;
uint_t             min;
uint_t             max;
uint_t             value;

uint_t             BU_value;
uint_t             RV_value;
uint_t             B_value;
uint_t             R_value;
uint_t             G_value;
uint_t             target_value;

dc1394switch_t     abs_control;
float              abs_value;
float              abs_max;
float              abs_min;
*/

/*
FEATURE_BRIGHTNESS;
FEATURE_EXPOSURE;
FEATURE_SHARPNESS;
FEATURE_WHITE_BALANCE;
FEATURE_HUE;
FEATURE_SATURATION;
FEATURE_GAMMA;
FEATURE_SHUTTER;
FEATURE_GAIN;
FEATURE_IRIS;
FEATURE_FOCUS;
FEATURE_TEMPERATURE;
FEATURE_TRIGGER;
FEATURE_TRIGGER_DELAY;
FEATURE_WHITE_SHADING;
FEATURE_FRAME_RATE;
FEATURE_ZOOM;
FEATURE_PAN;
FEATURE_TILT;
FEATURE_OPTICAL_FILTER;
FEATURE_CAPTURE_SIZE;
FEATURE_CAPTURE_QUALITY;
*/

