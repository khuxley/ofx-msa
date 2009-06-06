
/*
*  APointGreyGrabberFeatures.cpp
*  SDL OpenGL Template
*
*  Created by Andreas Muller on 20/11/2007.
*  Copyright 2007 Nanika. All rights reserved.
*
*/

#include "../AVideoGrabber.h"

//#define A_VIDEO_CAPTURE_POINTGREY 1 // for now so it goddamn colour codes the code

#ifdef A_VIDEO_CAPTURE_POINTGREY

#include "APointGreyGrabber.h"

void APointGreyGrabber::initFeatures()
{

/*
flycaptureGetCameraPropertyRangeEx(
FlyCaptureContext     context,
FlyCaptureProperty    cameraProperty,
bool*                pbPresent,
bool*                pbOnePush,
bool*                pbReadOut,
bool*                pbOnOff,
bool*                pbAuto,
bool*                pbManual,
int*                 piMin,
int*                 piMax )
*/
	vector< FlyCaptureProperty > availableProps;

	for( int i = FEATURE_FIRST; i <= FEATURE_LAST; i++ )
	{
		//cout << cameraFeatureToTitle( i ) << endl;

		// first find out if the prop exists

		FlyCaptureProperty tmpProp = APointGreyGrabberFeatureHelper::AVidFeatureToFlyCapFeature( i );

		if( tmpProp != -1 )
		{
			bool isPresent = false;
			flycaptureGetCameraPropertyRangeEx( context,  tmpProp, &isPresent, NULL, NULL, NULL, NULL, NULL, NULL, NULL );
			//cout << cameraFeatureToTitle( i ) << "			"; if (isPresent) { cout << " (X)";} else { cout << " ( )"; } cout << endl;
			availableProps.push_back( tmpProp );
		}
	}

	availableFeatureAmount = availableProps.size();
	featureVals = new AGrabberCameraFeatureVals[availableFeatureAmount];

	for( int i = 0; i < availableFeatureAmount; i++ )
	{

		bool pbPresent	= false;
		bool pbOnePush	= false;
		bool pbReadOut	= false;
		bool pbOnOff	= false;
		bool pbAuto		= false;
		bool pbManual	= false;
		int  piMin = 0;
		int  piMax = 0;

		flycaptureGetCameraPropertyRangeEx( context, availableProps.at( i ),
											&pbPresent, &pbOnePush, &pbReadOut, &pbOnOff, &pbAuto, &pbManual, &piMin, &piMax );

		bool pbOnePushActive = false;
		bool pbOnOffActive = false;
		bool pbAutoActive = false;
		int piValueA = 0;
		int piValueB = 0;

		flycaptureGetCameraPropertyEx( context,availableProps.at( i ),
										&pbOnePushActive, &pbOnOffActive, &pbAutoActive, &piValueA, &piValueB );


		bool pbAbsoluteMode = false;

		// we know the exist from the previous check

		featureVals[i].feature			= APointGreyGrabberFeatureHelper::flyCapFeatureToAVidFeature( availableProps.at( i ) );
		featureVals[i].name				= cameraFeatureToTitle( featureVals[i].feature );

		featureVals[i].isPresent			= pbPresent;
		featureVals[i].isReadable			= pbReadOut;

		featureVals[i].hasAbsoluteMode		= false; //tmpFeatureSet.feature[i].absolute_capable;
//		featureVals[i].absoluteModeActive	= tmpFeatureSet.feature[i].abs_control;

		featureVals[i].hasManualMode		= pbManual;

		featureVals[i].isOnOffSwitchable	= pbOnOff;
		featureVals[i].isOn					= pbOnOffActive;

		featureVals[i].hasOnePush			= pbOnePush;
		featureVals[i].hasOnePushActive		= pbOnePushActive;

		featureVals[i].hasAutoMode			= pbAuto;
		featureVals[i].hasAutoModeActive	= pbAutoActive;

		if( pbAbsoluteMode )
		{
			/*
			dc1394_feature_set_absolute_control( camera, tmpFeatureSet.feature[i].id, DC1394_ON );


			featureVals[i].currVal = tmpFeatureSet.feature[i].abs_value;

			featureVals[i].minVal  = tmpFeatureSet.feature[i].abs_min;
			featureVals[i].maxVal  = tmpFeatureSet.feature[i].abs_max;
			*/

		}
		else
		{

			featureVals[i].currVal = (float)piValueA;

			featureVals[i].minVal  = (float)piMin;
			featureVals[i].maxVal  = (float)piMax;
		}

	}

}

void APointGreyGrabber::setFeaturesOnePushMode()
{

	setFeatureStateOnOff( false, FEATURE_EXPOSURE, FEATURE_MODE_AUTO );
	setFeatureStateOnOff( true,  FEATURE_EXPOSURE, FEATURE_ONESHOT_MODE );

	setFeatureStateOnOff( false, FEATURE_SHUTTER, FEATURE_MODE_AUTO );
	setFeatureStateOnOff( true,  FEATURE_SHUTTER, FEATURE_ONESHOT_MODE );

	setFeatureStateOnOff( false, FEATURE_GAIN, FEATURE_MODE_AUTO );
	setFeatureStateOnOff( true,  FEATURE_GAIN, FEATURE_ONESHOT_MODE );

	setFeatureStateOnOff( false, FEATURE_WHITE_BALANCE, FEATURE_MODE_AUTO );
	setFeatureStateOnOff( true,  FEATURE_WHITE_BALANCE, FEATURE_ONESHOT_MODE );

	setFeatureStateOnOff( false, FEATURE_HUE, FEATURE_IS_ON );

//setFeatureStateOnOff( bool _val, int _feature, int _featureMode )

	/*

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
*/
}

void APointGreyGrabber::updateAllFeatureVals()
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

void APointGreyGrabber::updateFeatureVals( AGrabberCameraFeatureVals* _feature )
{

	FlyCaptureProperty tmpProp = APointGreyGrabberFeatureHelper::AVidFeatureToFlyCapFeature( _feature->feature );

	bool pbOnePushActive = false;
	bool pbIsOn = false;
	bool pbAutoActive = false;
	int piValueA = 0;
	int piValueB = 0;

	FlyCaptureError err = flycaptureGetCameraPropertyEx( context, tmpProp,
														&pbOnePushActive, &pbIsOn, &pbAutoActive, &piValueA, &piValueB );

	if (err != FLYCAPTURE_OK ) cout << "** APointGreyGrabber::updateFeatureVals error retrieving properties" << endl;

	if( _feature->hasAbsoluteMode )
	{
		//_feature->currVal = tmpFeatureVals.abs_value;
		//_feature->minVal = tmpFeatureVals.abs_min;
		//_feature->maxVal = tmpFeatureVals.abs_max;
		cout << "** NOT IMPLEMENTED ** APointGreyGrabber::updateFeatureVals setting absolute features." << endl;
	}
	else
	{
		_feature->currVal = (float)piValueA;
		//_feature->minVal = (float)tmpFeatureVals.min;
		//_feature->maxVal = (float)tmpFeatureVals.max;
	}



	if( _feature->isOnOffSwitchable )
	{
		_feature->isOn = pbIsOn;
	}

	if( _feature->hasAutoMode )
	{
		_feature->hasAutoModeActive = pbAutoActive;
	}


}

void APointGreyGrabber::setFeatureMode( int _feature, int _featureMode )
{
	cout << "** NOT IMPLEMENTED ** APointGreyGrabber::setFeatureMode " << _feature << ", " << _featureMode << endl;
}

void APointGreyGrabber::setFeatureStateOnOff( bool _val, int _feature, int _featureMode )
{

	FlyCaptureProperty tmpProp = APointGreyGrabberFeatureHelper::AVidFeatureToFlyCapFeature( _feature );

	// get current values
	bool pbOnePushActive = false;
	bool pbIsOn = false;
	bool pbAutoActive = false;
	int piValueA = 0;
	int piValueB = 0;

	FlyCaptureError err = flycaptureGetCameraPropertyEx( context, tmpProp,
														&pbOnePushActive, &pbIsOn, &pbAutoActive, &piValueA, &piValueB );

	if (err != FLYCAPTURE_OK ) cout << "** APointGreyGrabber::setFeatureStateOnOff error retrieving properties" << endl;

	if( _featureMode == FEATURE_AUTO_MODE )
	{

		//cout << "FEATURE_AUTO_MODE" << endl;

		if( _val )
		{
			//err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_AUTO );
			err = flycaptureSetCameraPropertyEx( context, tmpProp, pbOnePushActive, pbIsOn,  true,  piValueA, piValueB );
		}
		else
		{
			//err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_MANUAL );
			err = flycaptureSetCameraPropertyEx( context, tmpProp, pbOnePushActive, pbIsOn,  false,  piValueA, piValueB );
		}
	}
	else if( _featureMode == FEATURE_ONESHOT_MODE )
	{

		//cout << "FEATURE_ONESHOT_MODE" << endl;

		// set feature to manual first (?)
		setFeatureStateOnOff( false, _feature, FEATURE_AUTO_MODE );

		err = flycaptureSetCameraPropertyEx( context, tmpProp, true, pbIsOn,  pbAutoActive,  piValueA, piValueB );

		//err = dc1394_feature_set_mode( camera, tmpFeature, DC1394_FEATURE_MODE_ONE_PUSH_AUTO );
	}
	else if( _featureMode == FEATURE_IS_ON )
	{

		//cout << "FEATURE_IS_ON" << endl;

		if( _val ) { err = flycaptureSetCameraPropertyEx( context, tmpProp, pbOnePushActive, true,  pbAutoActive,  piValueA, piValueB );}
		else { err = flycaptureSetCameraPropertyEx( context, tmpProp, pbOnePushActive, false,  pbAutoActive,  piValueA, piValueB ); }

		//cout << "** NOT IMPLEMENTED ** APointGreyGrabber::setFeatureStateOnOff: Turn Camera Power On/Off " << endl;
	}

	if (err != FLYCAPTURE_OK ) cout << "** APointGreyGrabber::setFeatureStateOnOff error setting properties" << endl;

}

void APointGreyGrabber::setFeatureAbsoluteVal( float _val, int _feature )
{

	cout << "** NOT IMPLEMENTED ** APointGreyGrabber::setFeatureAbsoluteVal " << endl;

}

void APointGreyGrabber::setFeatureVal( float _val, int _feature )
{
	FlyCaptureProperty tmpProp = APointGreyGrabberFeatureHelper::AVidFeatureToFlyCapFeature( _feature );

	// get current values
	bool pbOnePushActive = false;
	bool pbIsOn = false;
	bool pbAutoActive = false;
	int piValueA = 0;
	int piValueB = 0;

	//cout << "_val: " << _val << endl;

	FlyCaptureError err = flycaptureGetCameraPropertyEx( context, tmpProp, &pbOnePushActive, &pbIsOn, &pbAutoActive, &piValueA, &piValueB );

	if (err != FLYCAPTURE_OK ) cout << "** APointGreyGrabber::setFeatureVal error getting properties." << endl;

	err = flycaptureSetCameraPropertyEx( context, tmpProp, pbOnePushActive, pbIsOn, pbAutoActive,  (int)_val, piValueB );

	if (err != FLYCAPTURE_OK ) cout << "** APointGreyGrabber::setFeatureVal error setting property." << endl;
}


#endif //A_VIDEO_CAPTURE_POINTGREY
