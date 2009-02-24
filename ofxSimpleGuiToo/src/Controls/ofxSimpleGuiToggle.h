#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ toggle
class ofxSimpleGuiToggle : public ofxSimpleGuiControl {
	
public:
	bool	*value;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiToggle(string name, bool *value) : ofxSimpleGuiControl(name) {
		this->value	= value;
		controlType = "Toggle";
		setup();
	}
	
	
	virtual void setup() {
		setSize(config->columnWidth, config->toggleHeight);
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	bool getValue() {
		return (*value);
	}
	void set(bool b) {
		(*value) = b;
	}
	void toggle() {
		(*value) = !(*value); 
	}

	void onPress(int x, int y, int button) {
		toggle();
	}

	//---------------------------------------------------------------------		
	void update() {
		if(!enabled) return;
		enabled = false;
	}

	void onKeyEnter() {
		toggle();
	}
	
	void draw(float x, float y) {
		enabled = true;
		setPos(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		
		ofEnableAlphaBlending();
		ofSetColor(config->sliderFullColor.r, config->sliderFullColor.g, config->sliderFullColor.b, config->sliderFullColor.a);
		if(isMouseOver())				ofSetColor(config->overColor.r, config->overColor.g, config->overColor.b);
		if(focused && !isMouseOver())	ofSetColor(config->focusColor.r, config->focusColor.g, config->focusColor.b);
		
		ofRect(0, 0, height, height);
		
		if((*value)) {
			ofSetColor(255, 255, 255, 200);
			ofLine(0, 0, height, height);
			ofLine(height, 0, 0, height);
		}
		
		ofSetColor(105, 105, 105, 200);
		if(isMouseOver()) ofSetColor(105, 105, 105, 100);
		ofRect(height, 0, width - height, height);
		ofSetColor(config->textColor.r, config->textColor.g, config->textColor.b);
		ofDrawBitmapString(name, height + 15, 15);
		ofDisableAlphaBlending();
		
		glPopMatrix();
	}
};
