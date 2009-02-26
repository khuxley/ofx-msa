/*
 *  ofxSimpleGuiControl.cpp
 *  ofxSimpleGuiToo Demo
 *
 *  Created by Mehmet Akten on 23/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxSimpleGuiControl.h"


ofxSimpleGuiControl::ofxSimpleGuiControl(string name) {
	controlType = "";
	this->config = &defaultSimpleGuiConfig;
	setName(name);
	setKey(key);
	setPos(0, 0);
	lock	  = false;
	focused	  = false;

	setup();
	
	disableAllEvents();		// just for safety to make sure nothing is registered twice
//	enableAppEvents();
//	enableMouseEvents();
//	disableKeyEvents();
}

void ofxSimpleGuiControl::setConfig(ofxSimpleGuiConfig *config) {
	this->config = config;
	setup();
}


void ofxSimpleGuiControl::setName(string newName) {
	name = newName;
	if(key.compare("") == 0) setKey("");	// if key has not been set yet, set name as key too
}


void ofxSimpleGuiControl::setKey(string newKey) {
	if(newKey.compare("") == 0) key = name;
	else key = newKey;
	for(int i=0; i<key.size(); i++) {
		if(key[i] == ' ') key[i] = '_';
	}
}

void ofxSimpleGuiControl::setTextColor() {
	if(isMouseOver()) ofSetColor(config->textOverColor);
	else ofSetColor(config->textColor);
}

void ofxSimpleGuiControl::setTextBGColor() {
	if(isMouseOver()) ofSetColor(config->textBGOverColor);
	else ofSetColor(config->textBGColor);
}

void ofxSimpleGuiControl::setFullColor(bool forceActive) {
	if(isMouseDown() || forceActive) ofSetColor(config->fullActiveColor);
	else if(isMouseOver()) ofSetColor(config->fullOverColor);
	else ofSetColor(config->fullColor);
}

void ofxSimpleGuiControl::setEmptyColor() {
	ofSetColor(config->emptyColor);
	//		if(isMouseOver()) ofSetColor(config->overColor.r, config->overColor.g, config->overColor.b);
	//		if(focused && !isMouseOver()) ofSetColor(config->focusColor.r, config->focusColor.g, config->focusColor.b);
	
}
