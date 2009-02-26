/*
 *  ofxSimpleGuiConfig.h
 *  ofxSimpleGuiToo Demo
 *
 *  Created by Mehmet Akten on 23/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once

#include "ofTypes.h"

class ofxSimpleGuiConfig {
public:	
	ofPoint	gridSize;

	float	buttonHeight;
	float	toggleHeight;
	float	sliderHeight;
	float	sliderTextHeight;
	float	slider2DTextHeight;
	float	titleHeight;
	
	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
	
	int	textColor;
	int textOverColor;
	int textBGColor;
	int textBGOverColor;
	
	int fullColor;
	int	fullOverColor;
	int fullActiveColor;
	int emptyColor;
	int borderColor;
	
	ofxSimpleGuiConfig() {

		sliderHeight		= 12;
		sliderTextHeight	= 18;
		titleHeight			= sliderHeight + sliderTextHeight;
		toggleHeight		= titleHeight;
		buttonHeight		= titleHeight;
		slider2DTextHeight	= titleHeight * 1.5;

		
		padding.set			(titleHeight/2, titleHeight/2);
		offset.set			(titleHeight/2, titleHeight/2);
		slider2DSize.set	(titleHeight * 4, titleHeight * 4);
		
		gridSize.x			= titleHeight * 8 + padding.x;		
		gridSize.y			= toggleHeight + padding.y;
		
		textColor			= 0xAAAAAA;
		textOverColor		= 0xFFFFFF;
		textBGColor			= 0x303030;
		textBGOverColor		= 0x707070;
		
		fullColor			= 0x37a9a9;
		fullOverColor		= 0x64b4b4;
		fullActiveColor		= 0xb41818;
		emptyColor			= 0xDCDCDC;		
		
		borderColor			= 0xCCCCCC;
	}
};


extern ofxSimpleGuiConfig defaultSimpleGuiConfig;