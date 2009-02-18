/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/


#include "ofxMSAInteractiveObject.h"

ofxMSAInteractiveObject::ofxMSAInteractiveObject() {
	_mouseOver	= false;
	_mouseDown	= false;
	enabled		= true;
	verbose		= false;
	
//	ofAddUpdateListener(this, ofxMSAInteractiveObject, _preUpdate);		// need poco update for this, call checkForMotion() manually in the meantime
	enableAppEvents();
//	setObjectName(string("ofxMSAInteractiveObject"));
}

ofxMSAInteractiveObject::~ofxMSAInteractiveObject() {
	disableMouseEvents();
	disableKeyEvents();
	disableAppEvents();
}

void ofxMSAInteractiveObject::killMe() {
	delete this;
}

void ofxMSAInteractiveObject::enableMouseEvents() {
	ofMouseEvents.addListener(this);
}

void ofxMSAInteractiveObject::disableMouseEvents() {
	ofMouseEvents.removeListener(this);
}

void ofxMSAInteractiveObject::enableKeyEvents() {
	ofKeyEvents.addListener(this);
}

void ofxMSAInteractiveObject::disableKeyEvents() {
	ofKeyEvents.removeListener(this);
}

void ofxMSAInteractiveObject::enableAppEvents() {
	ofAppEvents.addListener(this);
}

void ofxMSAInteractiveObject::disableAppEvents() {
	ofAppEvents.removeListener(this);
}


void ofxMSAInteractiveObject::setPos(float _x, float _y) {
	x = _x;
	y = _y;
}

void ofxMSAInteractiveObject::setSize(float _w, float _h) {
	width = _w;
	height = _h;
}

void ofxMSAInteractiveObject::setPosAndSize(float _x, float _y, float _w, float _h) {
	setPos(_x, _y);
	setSize(_w, _h);
}

bool ofxMSAInteractiveObject::isMouseOver() {
	return _mouseOver;
}

bool ofxMSAInteractiveObject::isMouseDown() {
	return _mouseDown;
}

int ofxMSAInteractiveObject::getMouseX() {
	return _mouseX;
}

int ofxMSAInteractiveObject::getMouseY() {
	return _mouseY;
}

int ofxMSAInteractiveObject::getLastMouseButton() {
	return _mouseButton;
}

bool ofxMSAInteractiveObject::hitTest(int tx, int ty) {
	return ((tx > x) && (tx < x + width) && (ty > y) && (ty < y + height));
}


void ofxMSAInteractiveObject::checkForMotion() {
	if(oldRect.x != this->x || oldRect.y != this->y || oldRect.width != this->width ||oldRect.height != this->height) {
		if(_mouseDown) mouseDragged(_mouseX, _mouseY, _mouseButton);
		else mouseMoved(_mouseX, _mouseY);
		oldRect =  (ofRectangle) (*this);
	}
}

/*
// need poco update for this, call checkForMotion() manually in the meantime
void ofxMSAInteractiveObject::_preUpdate(const void* sender, ofEventArgs& eventArgs) {
	if(!enabled) return;

	checkForMotion();
}
*/
void ofxMSAInteractiveObject::mouseMoved(int x, int y) {
	if(verbose) printf("ofxMSAInteractiveObject::mouseMoved(x: %i, y: %i)\n", x, y);
	if(!enabled) return;
	
	_mouseX = x;
	_mouseY = y;
	
	if(hitTest(x, y)) {						// if mouse is over the object
		if(!_mouseOver) {						// if wasn't over previous frame
			onRollOver(x, y);						// call onRollOver
			_mouseOver = true;						// update flag
		}
		onMouseMove(x, y);						// and trigger onMouseMove
	} else if(_mouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
		onRollOut();							// call onRollOut
		_mouseOver = false;						// update flag
	}
}


void ofxMSAInteractiveObject::mousePressed(int x, int y, int button) {
	if(verbose) printf("ofxMSAInteractiveObject::mousePressed(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	if(hitTest(x, y)) {						// if mouse is over
		if(!_mouseDown) {						 // if wasn't down previous frame
			onPress(x, y, button);					// call onPress
			_mouseDown = true;						// update flag
		}
	} else {								// if mouse is not over
		// do nothing
	}
}

void ofxMSAInteractiveObject::mouseDragged(int x, int y, int button) {
	if(verbose) printf("ofxMSAInteractiveObject::mouseDragged(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;

	if(hitTest(x, y)) {						// if mouse is over the object
		if(!_mouseOver) {						// if wasn't over previous frame
			//				onPress(x, y);							// call onPress - maybe not
			_mouseOver = true;						// update flag
		}
		onDragOver(x, y, button);				// and trigger onDragOver
	} else if(_mouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
		onRollOut();							// call onRollOut
		_mouseOver = false;						// update flag
	}
}

void ofxMSAInteractiveObject::mouseReleased(int x, int y, int button) {
	if(verbose) printf("ofxMSAInteractiveObject::mouseReleased(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	if(hitTest(x, y)) {
		onRelease(x, y, button);
	} else {
		onReleaseOutside(x, y, button);
	}
	_mouseDown = false;
}
