#pragma once

#include "ofxSimpleGuiControl.h"


class ofxSimpleGuiSlider2d : public ofxSimpleGuiControl {
public:
	ofPoint		*value;
	ofPoint		point, min, max;
	
	//--------------------------------------------------------------------- construct
	ofxSimpleGuiSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) : ofxSimpleGuiControl(name) {
		min.set(xmin, ymin);
		max.set(xmax, ymax);
		this->value = value;
		controlType = "Slider2D";
		setup();
	}
	
	void setup() {
		setSize(config->slider2DSize.x, config->slider2DSize.y + config->slider2DTextHeight);
		point.x = ofMap((*value).x, min.x, max.x, x, x+width); 
		point.y = ofMap((*value).y, min.y, max.y, y, y+height-config->slider2DTextHeight); 
	}

	void loadFromXML(ofxXmlSettings &XML) {
		value->set(XML.getValue("controls:" + controlType + "_" + key + ":valueX", 0.0f), XML.getValue("controls:" + controlType + "_" + key + ":valueY", 0.0f));
	}
	
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("valueX", value->x);
		XML.addValue("valueY", value->y);
		XML.popTag();
	}
	
	
	//--------------------------------------------------------------------- set xy
	void set(float x, float y) {
		(*value).x = x;
		(*value).y = y;
	}
	void setMin(float x, float y) {
		min.x = x;
		min.y = y;
	}	
	void setMax(float x, float y) {
		max.x = x;
		max.y = y;
	}	

	//--------------------------------------------------------------------- mouse pressed
	void onPress(int x, int y, int button) {
		lock = true;
		point.set(x, y);
	}
	
	//--------------------------------------------------------------------- mouse dragged
	void onDragOver(int x, int y, int button) {
		if(lock) {
			point.set(x, y);
		}
	}
	
	void onDragOutside(int x, int y, int button) {
		if(lock) {
			point.set(x, y);
		}
	}	
	
	//--------------------------------------------------------------------- mouse released
	void onRelease() {
		lock = false;
	}
	
	//--------------------------------------------------------------------- update
	void update() {
		if(point.x > x + width)				point.x = x + width; 
		else if(point.x < x)				point.x = x; 
		
		if(point.y > y+height - config->slider2DTextHeight)			point.y = y + height - config->slider2DTextHeight;
		else if(point.y < y)				point.y = y;
		
		if(lock){
			(*value).x = ofMap(point.x, x, x+width, min.x, max.x); 
			(*value).y = ofMap(point.y, y, y+height-config->slider2DTextHeight, min.y, max.y); 
		}
	}
	
	//--------------------------------------------------------------------- draw
	void draw(float x, float y) {
		setPos(x, y);
		ofPoint	pointv;
		pointv.x = ofMap((*value).x, min.x, max.x, x, x+width);
		pointv.y = ofMap((*value).y, min.y, max.y, y, y+height-config->slider2DTextHeight);
		
		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(x, y, 0);		
		
		ofFill();
		ofSetColor(config->sliderFullColor.r, config->sliderFullColor.g, config->sliderFullColor.b, 200);
		if(isMouseOver() || lock)	ofSetColor(config->overColor.r, config->overColor.g, config->overColor.b, 200);
		if(focused && !isMouseOver()) ofSetColor(config->focusColor.r, config->focusColor.g, config->focusColor.b);
		
		ofRect(0, 0, width, height - config->slider2DTextHeight);
		
		ofFill();
		ofSetColor(105, 105, 105, 200);
		ofRect(0, height-config->slider2DTextHeight, width, config->slider2DTextHeight);
		ofSetColor(0xffffff);
		ofDrawBitmapString(name+"\nx:"+ofToString(value->x, 2)+"\ny:"+ofToString(value->y, 2), 3, height+15-config->slider2DTextHeight);
		
		ofSetColor(config->sliderFullColor.r/10, config->sliderFullColor.g/10, config->sliderFullColor.b/10, 200);
		ofCircle(pointv.x-x, pointv.y-y, 2);
		ofSetColor(config->sliderFullColor.r/10, config->sliderFullColor.g/10, config->sliderFullColor.b/10, 100);
		
		ofLine(pointv.x-x, 0, pointv.x-x, height-config->slider2DTextHeight);
		ofLine(0, pointv.y-y,width, pointv.y-y);
		
		glPopMatrix();
		ofDisableAlphaBlending();
		
	}
	
};