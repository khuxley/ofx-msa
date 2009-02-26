/*
 *  ofxSimpleGuiControl.h
 *  MSH Ribbons 00573
 *
 *  Created by Mehmet Akten on 04/10/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#pragma once

#include "ofxMSAInteractiveObject.h"
#include "ofxSimpleGuiConfig.h"
#include "ofxXmlSettings.h"

class ofxSimpleGuiControl : public ofxMSAInteractiveObject {
public:
	string		name;		// Human readable name this is what is displayed on screen
	string		key;		// Machine readable name (don't change this after creating control, used for saving/loading)
	string		controlType;
	bool		lock;
	bool		focused;
	
	ofxSimpleGuiControl(string name);	
	void setName(string newName);
	void setKey(string newKey);
	void setConfig(ofxSimpleGuiConfig *config);
	
	void setTextColor();
	void setTextBGColor();
	void setFullColor(bool forceActive = false);
	void setEmptyColor();
	
	virtual void loadFromXML(ofxXmlSettings &XML) {}
	virtual void saveToXML(ofxXmlSettings &XML) {}	
	
	virtual void setup() {}

	virtual void draw(float x, float y) {}
	virtual void draw() { draw(x, y); }
	
	virtual void onKeyUp() {}
	virtual void onKeyDown() {}
	virtual void onKeyLeft() {}
	virtual void onKeyRight() {}
	virtual void onKeyEnter() {}
	
protected:
	ofxSimpleGuiConfig	*config;
};