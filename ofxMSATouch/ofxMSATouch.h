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
#include "ofxOsc.h"

#define MSATOUCH_ADDRESS		"/msaremote/touch"

class ofxMSATouch {
public:
	// sent info
	ofPoint		pos;
	int			cursorId;
	bool		isDown;
	
	ofxMSATouch() {
		isDown = false;
	}
	

	void cursorPressed(float x, float y, int cursorId) {
		pos.set(x, y);
		this->cursorId = cursorId;
		isDown = true;
	}
	
	
	void cursorReleased(float x, float y, int cursorId) {
		pos.set(x, y);
		this->cursorId = cursorId;
		isDown = false;
	}
	
	void cursorDragged(float x, float y, int cursorId) {
		pos.set(x, y);
		this->cursorId = cursorId;
		isDown = true;
	}
	
	
	void addToBundle(ofxOscBundle &b) {
		if(!isDown) return;
		
		ofxOscMessage m;
		m.setAddress(MSATOUCH_ADDRESS);
		m.addIntArg(cursorId);
		m.addFloatArg(pos.x);
		m.addFloatArg(pos.y);
		b.addMessage(m);
	}
};
