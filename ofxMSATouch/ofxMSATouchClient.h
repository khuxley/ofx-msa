/*
 *  ofxMSATouchListener.h
 *  FBO Paint
 *
 *  Created by Mehmet Akten on 02/03/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMultiTouch.h"

#include "ofxMSAReceivedTouch.h"


class ofxMSATouchClient {
public:
	ofxMultiTouchListener	*multiTouchListener;
	int						baseIndex;			// cursorId's can start at any number (to give room for mouse)
	
	ofxMSATouchClient();
	~ofxMSATouchClient();
	
	void	setup(int port);
	void	update();
	
	void	updateCursors(ofxMSAReceivedTouch &cursor);
	void	clear();

	
protected:
	ofxOscReceiver					oscReceiver;
	vector<ofxMSAReceivedTouch>		cursors;
};