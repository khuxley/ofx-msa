#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ toggle
class ofxSimpleGuiContent  : public ofxSimpleGuiControl {
public:
	float			fixwidth;
	float			fixheight;
	ofBaseDraws		*content;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiContent(string name, ofBaseDraws* content, float fixwidth=250.0) : ofxSimpleGuiControl(name) {
		this->content = content;
		this->fixwidth  = fixwidth;
		controlType = "Content";
		setup();
	}
	
	void setup() {
		fixheight = fixwidth * content->getHeight()/content->getWidth();
		setSize(fixwidth, fixheight + config->sliderTextHeight);
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofEnableAlphaBlending();
		ofSetColor(0xffffff);
		content->draw(0, 0, width,fixheight); 
		
		ofFill();
		ofSetColor(config->frameBG.r, config->frameBG.g, config->frameBG.b, 200);
		ofRect(0, fixheight, width, config->sliderTextHeight);
		ofSetColor(config->textColor.r, config->textColor.g, config->textColor.b);	
		ofDrawBitmapString(name, 3, fixheight + 15);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
};
