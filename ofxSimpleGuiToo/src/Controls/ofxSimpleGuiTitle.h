#pragma once

#include "ofxSimpleGuiControl.h"


class ofxSimpleGuiTitle  : public ofxSimpleGuiControl {
public:

	ofxSimpleGuiTitle(string name) : ofxSimpleGuiControl(name) {
		controlType = "Title";
		setup();
	}
	
	void setup() {
		setSize(config->columnWidth, config->titleHeight);
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		
		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(x, y, 0);		
		ofFill();
		ofSetColor(105, 105, 105, 200);
		ofRect(0, 0, config->columnWidth, config->titleHeight);
		ofSetColor(0xffffff);
		ofDrawBitmapString(name, 3, 15);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
};
