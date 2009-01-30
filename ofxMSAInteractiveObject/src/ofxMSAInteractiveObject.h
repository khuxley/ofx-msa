/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 
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


#pragma once

#include "ofMain.h"


class ofxMSAInteractiveObject : public ofMouseListener, public ofKeyListener, public ofAppListener, public ofRectangle {
public:
	bool		enabled;
	bool		verbose;
	
	ofxMSAInteractiveObject();					// constructor
	virtual ~ofxMSAInteractiveObject();			// destructor
	
	void enableMouseEvents();			// call this if object should receive mouse events
	void disableMouseEvents();			// call this if object doesn't need to receive mouse events (default)
	
	void enableKeyEvents();				// call this if object should receive key events
	void disableKeyEvents();			// call this if object doesn't need to receive key events (default)
	
	void enableAppEvents();				// call this if object should update/draw automatically	(default)
	void disableAppEvents();			// call this if object doesn't need to update/draw automatically
	
	void setPos(float _x, float _y);	// set position of object
	void setSize(float _w, float _h);	// set size of object
	
	void setPosAndSize(float _x, float _y, float _w, float _h);		// set pos and size
	
	bool isMouseOver();					// returns true if mouse is over object (based on position and size)
	bool isMouseDown();					// returns true if mouse button is down and over object (based on position and size)
	int	 getMouseX();					// returns mouse X (in screen coordinates)
	int  getMouseY();					// returns mouse Y (in screen coordinates)
	int  getLastMouseButton();			// returns last mouse button to have activity
	
	bool hitTest(int tx, int ty);		// returns true if given (x, y) coordinates (in screen space) are over the object (based on position and size)
	
	void checkForMotion();				// if your object is moving, this needs to be called in the update function for onRollOver, onRollOut callbacks to operate correctly
	
	void killMe();						// if your object is a pointer, and you are done with it, call this


	// extend ofxMSAInteractiveObject and override any of the following methods
	virtual void setup(){}
	virtual void update(){}
    virtual void draw(){}
	virtual void exit(){}
	
	virtual void onRollOver(int x, int y)					{}
	virtual void onRollOut()								{}
	virtual void onMouseMove(int x, int y)					{}
	virtual void onDragOver(int x, int y, int button)		{}
	virtual void onPress(int x, int y, int button)			{}
	virtual void onRelease(int x, int y, int button)		{}
	virtual void onReleaseOutside(int x, int y, int button)	{}
	
	
	// you shouldn't need access to any of these
private:
	int			_mouseX, _mouseY, _mouseButton;
	bool		_mouseOver;
	bool		_mouseDown;
	ofRectangle	oldRect;
	
	void update(const void* sender, ofEventArgs& eventArgs);
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);	
	void mouseDragged(int x, int y, int button);	
	void mouseReleased(int x, int y, int button);
	
//	void _preUpdate(const void* sender, ofEventArgs& eventArgs);		// need poco update for this, call checkForMotion() manually in the meantime

};