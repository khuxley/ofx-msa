/*
 *  ofxSimpleGuiPage.h
 *  ofxSimpleGUIToo Demo
 *
 *  Created by Mehmet Akten on 23/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once

#include "ofxSimpleGuiIncludes.h"

class ofxSimpleGuiPage : public ofxSimpleGuiControl {
public:
	ofxSimpleGuiPage(string name);
	~ofxSimpleGuiPage();
	
	void					draw(float x = 0, float y = 0);
	
	void					loadFromXML(ofxXmlSettings &XML);
	void					saveToXML(ofxXmlSettings &XML);
	
	ofxSimpleGuiControl		*addControl(ofxSimpleGuiControl* control);
	ofxSimpleGuiButton		*addButton(string name, bool *value);
	ofxSimpleGuiSliderInt	*addSlider(string name, int *value, int min, int max);
	ofxSimpleGuiSliderFloat	*addSlider(string name, float *value, float min, float max, float smoothing = 0);
	ofxSimpleGuiSlider2d	*addSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax);
	ofxSimpleGuiQuadWarp	*addQuadWarper(string name, float x, float y, float sw, float sh, ofPoint **pts);
	ofxSimpleGuiMovieSlider	*addMovieSlider(string name, ofVideoPlayer* input);
	ofxSimpleGuiToggle		*addToggle(string name, bool *value);
	ofxSimpleGuiTitle		*addTitle(string name);
	ofxSimpleGuiContent		*addContent(string name, ofBaseDraws *content, float fixwidth = -1);

	
	//	void setup(ofEventArgs &e);
	void update(ofEventArgs &e);
	//  void draw(ofEventArgs &e);
	//	void exit(ofEventArgs &e);
	
	void mouseMoved(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);	
	void mouseDragged(ofMouseEventArgs &e);	
	void mouseReleased(ofMouseEventArgs &e);
	
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);	
	
protected:
	vector <ofxSimpleGuiControl*>	controls;

};