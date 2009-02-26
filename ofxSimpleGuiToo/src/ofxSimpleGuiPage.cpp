/*
 *  ofxSimpleGuiPage.cpp
 *  ofxSimpleGuiPage Demo
 *
 *  Created by Mehmet Akten on 23/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxSimpleGuiPage.h"

ofxSimpleGuiPage::ofxSimpleGuiPage(string name) : ofxSimpleGuiControl(name) {
	disableAllEvents();
	height = ofGetHeight();
}

ofxSimpleGuiPage::~ofxSimpleGuiPage() {
	// delete all controls
}


void ofxSimpleGuiPage::loadFromXML(ofxXmlSettings &XML) {
	for(int i=0; i < controls.size(); i++) {
		controls[i]->loadFromXML(XML);
	}
}


void ofxSimpleGuiPage::saveToXML(ofxXmlSettings &XML) {
	for(int i=0; i < controls.size(); i++) {
		controls[i]->saveToXML(XML);
	}
}

float ofxSimpleGuiPage::getNextY(float y) {
	int iy = ceil(y/config->gridSize.y);
//	return y;
	return (iy) * config->gridSize.y;
}

void ofxSimpleGuiPage::draw(float x, float y) {
	setPos(x += config->offset.x, y += config->offset.y);
	float posX		= 0;
	float posY		= 0;
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	for(int i=0; i<controls.size(); i++) {
		float controlX = posX + x;
		float controlY = posY + y;
		
		controls[i]->draw(controlX, controlY);
		ofNoFill();
		ofSetColor(config->borderColor);
		glLineWidth(0.5f);
		ofRect(controlX, controlY, controls[i]->width, controls[i]->height);
		posY = getNextY(posY + controls[i]->height + config->padding.y);
		
		if(posY + y >= height - controls[i]->height - config->padding.y) {
			posX += config->gridSize.x;
			posY = 0;
		}
		//		if(guiFocus == controls[i]->guiID) controls[i]->focused = true;		// MEMO
		//		else							   controls[i]->focused = false;	
	}	
}


ofxSimpleGuiControl *ofxSimpleGuiPage::addControl(ofxSimpleGuiControl* control) {
	controls.push_back(control);
	return control;
}

ofxSimpleGuiButton *ofxSimpleGuiPage::addButton(string name, bool *value) {
	return (ofxSimpleGuiButton *)addControl(new ofxSimpleGuiButton(name, value));
}

ofxSimpleGuiSliderInt *ofxSimpleGuiPage::addSlider(string name, int *value, int min, int max) {
	return (ofxSimpleGuiSliderInt *)addControl(new ofxSimpleGuiSliderInt(name, value, min, max, 0));
}

ofxSimpleGuiSliderFloat *ofxSimpleGuiPage::addSlider(string name, float *value, float min, float max, float smoothing) {
	return (ofxSimpleGuiSliderFloat *)addControl(new ofxSimpleGuiSliderFloat(name, value, min, max, smoothing));
}

ofxSimpleGuiSlider2d *ofxSimpleGuiPage::addSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax) {
	return (ofxSimpleGuiSlider2d *)addControl(new ofxSimpleGuiSlider2d(name, value, xmin, xmax, ymin, ymax));
}

ofxSimpleGuiQuadWarp *ofxSimpleGuiPage::addQuadWarper(string name, float x, float y, float sw, float sh, ofPoint **pts) {
	return (ofxSimpleGuiQuadWarp *)addControl(new ofxSimpleGuiQuadWarp(name, x, y, sw, sh, pts));
}

ofxSimpleGuiMovieSlider *ofxSimpleGuiPage::addMovieSlider(string name, ofVideoPlayer* input) {
	return (ofxSimpleGuiMovieSlider *)addControl(new ofxSimpleGuiMovieSlider(name, input));
}

ofxSimpleGuiToggle *ofxSimpleGuiPage::addToggle(string name, bool *value) {
	return (ofxSimpleGuiToggle *)addControl(new ofxSimpleGuiToggle(name, value));
}

ofxSimpleGuiTitle *ofxSimpleGuiPage::addTitle(string name, bool *value) {
	return (ofxSimpleGuiTitle *)addControl(new ofxSimpleGuiTitle(name, value));
}


ofxSimpleGuiContent *ofxSimpleGuiPage::addContent(string name, ofBaseDraws *content, float fixwidth) {
	if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
	return (ofxSimpleGuiContent *)addControl(new ofxSimpleGuiContent(name, content, fixwidth));
}




void ofxSimpleGuiPage::update(ofEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->update();
}


void ofxSimpleGuiPage::mouseMoved(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseMoved(e);
}

void ofxSimpleGuiPage::mousePressed(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mousePressed(e);
}

void ofxSimpleGuiPage::mouseDragged(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseDragged(e);
}

void ofxSimpleGuiPage::mouseReleased(ofMouseEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_mouseReleased(e);
}

void ofxSimpleGuiPage::keyPressed(ofKeyEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_keyPressed(e);
}

void ofxSimpleGuiPage::keyReleased(ofKeyEventArgs &e) {
	for(int i=0; i<controls.size(); i++) controls[i]->_keyReleased(e);
}