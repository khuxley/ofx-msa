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