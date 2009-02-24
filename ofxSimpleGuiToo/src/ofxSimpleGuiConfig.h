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
	float	columnWidth;

	float	buttonHeight;
	float	toggleHeight;
	float	sliderHeight;
	float	sliderTextHeight;
	float	slider2DTextHeight;
	float	titleHeight;
	
	ofPoint padding;
	ofPoint offset;
	ofPoint	slider2DSize;
	
	ofColor frameBG;
	ofColor frameFG;
	ofColor textColor;
	ofColor sliderFullColor;
	ofColor sliderEmptyColor;
	ofColor overColor;
	ofColor focusColor;
	
	ofxSimpleGuiConfig() {
		columnWidth			= 230;

		buttonHeight		= 20;
		toggleHeight		= 20;
		sliderHeight		= 15;
		sliderTextHeight	= 20;
		slider2DTextHeight	= 50;
		titleHeight			= 20;
		
		padding.set			(30, 15);
		offset.set			(10, 10);
		slider2DSize.set	(100, 100);
		
		frameBG.r			= 80;
		frameBG.g			= 80;
		frameBG.b			= 80;
		
		frameFG.r			= 150;
		frameFG.g			= 150;
		frameFG.b			= 150;
		
		textColor.r			= 230;
		textColor.g			= 230;
		textColor.b			= 230;
		
		sliderFullColor.r	= 82;
		sliderFullColor.g	= 183;
		sliderFullColor.b	= 200;
		sliderFullColor.a	= 255;
		
		sliderEmptyColor.r	= 220;
		sliderEmptyColor.g	= 220;
		sliderEmptyColor.b	= 220;
		sliderEmptyColor.a	= 255;		
		
		overColor.r			= 255;
		overColor.g			= 10;
		overColor.b			= 255;
		
		focusColor.r		= 181;
		focusColor.g		= 215;
		focusColor.b		= 45;	
	}
};


extern ofxSimpleGuiConfig defaultSimpleGuiConfig;