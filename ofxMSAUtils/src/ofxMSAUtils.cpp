/*
 *  ofxMSAUtils.cpp
 *  Meshmerizer
 *
 *  Created by Mehmet Akten on 19/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSAUtils.h"

void msaClear() {
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void msaConstrain(float &pos, float &vel, float min, float max, float bounce) {
	if(pos < min) {
		pos = min;
		vel = fabs(vel) * bounce;
	} else if(pos > max) {
		pos = max;
		vel = -fabs(vel) * bounce;
	}
}	

void msaConstrain(ofPoint &pos, ofPoint &vel, ofPoint &min, ofPoint &max, float bounce) {
	msaConstrain(pos.x, vel.x, min.x, max.x, bounce);
	msaConstrain(pos.y, vel.y, min.y, max.y, bounce);
	msaConstrain(pos.z, vel.z, min.z, max.z, bounce);
}


void msaDrawFPS() {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(0x000000);
	ofFill();
	ofDisableAlphaBlending();
	ofRect(ofGetWidth() - (120+5), (ofGetHeight()-35), 90, 50);
	ofSetColor(0, 255, 0);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, ofGetWidth() - 120, ofGetHeight()-20);
}

void msaDrawFPS(int x, int y) {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
	ofSetColor(0x000000);
	ofSetColor(0, 255, 0);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, x, y);
}

void msaDrawFPS(int color) {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
	ofSetColor(color);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 20, ofGetHeight()-20);
}


void msaSetCursor(bool forceOn) {
	if(forceOn || ofGetWindowMode() == OF_WINDOW) ofShowCursor();
	else ofHideCursor();
}
