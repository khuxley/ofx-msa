/*
 *  AVideoGrabberFeatureUIHelper.h
 *  SDL OpenGL Template
 *
 *  Created by Andreas Muller on 18/05/2007.
 *  Copyright 2007 Nanika. All rights reserved.
 *
 */

 #include "AVideoGrabberTypesAndEnums.h"

void setFeatureVal( float _val, int _feature, int _mode, int _feature_prop )
{
	myGrabber.setFeatureVal( _val, _feature );
}

void setFeatureAbsoluteVal( float _val, int _feature, int _mode, int _feature_prop )
{
	myGrabber.setFeatureAbsoluteVal( _val, _feature );
}

void setFeatureStateOnOff( bool _val, int _feature, int _featureMode, int _unused )
{
	myGrabber.setFeatureStateOnOff( _val, _feature, _featureMode );
}


void featureButtonPushed( int _feature, int _featureMode, int _unused )
{
	myGrabber.setFeatureStateOnOff( true, _feature, _featureMode );
}


void setFeatureMode( int _val, int _feature )
{
	myGrabber.setFeatureMode( _val, _feature );
}

/*
	FEATURE_AUTO_MODE		= 0,
	FEATURE_ONESHOT_MODE	= 1,
	FEATURE_IS_ON
*/

void setupCameraUI()
{
	if( myGrabber.UICapable() )
	{

		const int skipListAmount = 10;
		int skipList[skipListAmount] = { FEATURE_CAPTURE_QUALITY, FEATURE_CAPTURE_SIZE, FEATURE_OPTICAL_FILTER, FEATURE_TRIGGER, FEATURE_TRIGGER_DELAY, FEATURE_TEMPERATURE, FEATURE_PAN, FEATURE_TILT, FEATURE_ZOOM, FEATURE_WHITE_SHADING };

		float screenPadding = 20.0f;
		float tmpPanelWidth = 260.0f;
		AParameterUI* ui = AParameterUI::Instance();

		AParameterUIPanelGrabber* newPanel = new AParameterUIPanelGrabber(); // must be created with new, AParameterUIPanelGrabber newPanel will NOT work.

		string panelTitle = "";

#ifdef A_VIDEO_CAPTURE_LIB_DC1394
		panelTitle = "Camera Properties (libdc1394)";
#endif

#ifdef A_VIDEO_CAPTURE_POINTGREY
		panelTitle = "Camera Properties (FlyCap)";
#endif

		newPanel->init( panelTitle, widthf-tmpPanelWidth-screenPadding-screenPadding, screenPadding, &myGrabber,
						myGrabber.videoGrabber.featureVals, myGrabber.videoGrabber.availableFeatureAmount );


		for( int i = 0; i < myGrabber.videoGrabber.availableFeatureAmount; i++ )
		{

			int tmpFeatureID = myGrabber.videoGrabber.featureVals[i].feature;

			// see if the feature is in the skip list
			bool skipFeature = false;
			for( int j = 0; j < skipListAmount; j++ ) { if ( tmpFeatureID == skipList[j]) {skipFeature = true;} }

			if( !skipFeature)
			{

				float currVal = myGrabber.videoGrabber.featureVals[i].currVal;
				float minVal = myGrabber.videoGrabber.featureVals[i].minVal;
				float maxVal = 	myGrabber.videoGrabber.featureVals[i].maxVal;

				AParameterUIObjectSliderFloat* tmpFloatSlider = newPanel->addSliderFloat( myGrabber.videoGrabber.featureVals[i].name, tmpPanelWidth - 20.0f, minVal, maxVal, currVal );

				if( myGrabber.videoGrabber.featureVals[i].hasAbsoluteMode ) { tmpFloatSlider->changedParameterCallback = &setFeatureAbsoluteVal; }
				else { tmpFloatSlider->changedParameterCallback = &setFeatureVal; }

				tmpFloatSlider->featureID = tmpFeatureID;
				tmpFloatSlider->arg1 = tmpFeatureID;
				tmpFloatSlider->funcPointerSet = true;


				if( myGrabber.videoGrabber.featureVals[i].hasAutoMode )
				{
					AParameterUIObjectCheckbox*	tmpAutoModeCheckbox = tmpFloatSlider->addCheckbox( "Auto", myGrabber.videoGrabber.featureVals[i].hasAutoModeActive );
					tmpAutoModeCheckbox->changedParameterCallback = &setFeatureStateOnOff;

					tmpAutoModeCheckbox->arg1 = tmpFeatureID;
					tmpAutoModeCheckbox->arg2 = FEATURE_AUTO_MODE;

					tmpAutoModeCheckbox->funcPointerSet = true;
				}

				if( myGrabber.videoGrabber.featureVals[i].hasOnePush )
				{
					AParameterUIObjectPushButton*	tmpOnePushButton = tmpFloatSlider->addPushButton( "One Push" );
					tmpOnePushButton->changedParameterCallback = &featureButtonPushed;

					tmpOnePushButton->arg1 = tmpFeatureID;
					tmpOnePushButton->arg2 = FEATURE_ONESHOT_MODE;

					tmpOnePushButton->funcPointerSet = true;
				}

				if( myGrabber.videoGrabber.featureVals[i].isOnOffSwitchable )
				{
					AParameterUIObjectCheckbox*	tmpAutoModeCheckbox = tmpFloatSlider->addCheckbox( "On", myGrabber.videoGrabber.featureVals[i].isOn );
					tmpAutoModeCheckbox->changedParameterCallback = &setFeatureStateOnOff;

					tmpAutoModeCheckbox->arg1 = tmpFeatureID;
					tmpAutoModeCheckbox->arg2 = FEATURE_IS_ON;

					tmpAutoModeCheckbox->funcPointerSet = true;
				}

			}

		}

		ui->addObject( newPanel );

	}

}

/*
	if( _feature->isOnOffSwitchable )
	{
		_feature->isOn = tmpFeatureVals.is_on;
	}

	if( _feature->hasAutoMode )
*/


/*
	AParameterUIObjectSliderFloat* tmpFloatSlider2 = tmpPanel->addSliderFloat( "A Float Slider", 300, 0.0f, (float)100.0f, 50.0f );

	tmpFloatSlider2->changedParameterCallback = &testFloatFunction2;
	tmpFloatSlider2->funcPointerSet = true;

	AParameterUIObjectCheckbox*	tmpAutoModeCheckbox2 = tmpFloatSlider2->addCheckbox( "Auto Mode", true );
	tmpAutoModeCheckbox2->changedParameterCallback = &lightingToggleFunction;
	tmpAutoModeCheckbox2->funcPointerSet = true;

	AParameterUIObjectPushButton*	tmpOnePushButton2 = tmpFloatSlider2->addPushButton( "One Push" );
	tmpOnePushButton2->changedParameterCallback = &buttonPressed;
	tmpOnePushButton2->funcPointerSet = true;


*/
