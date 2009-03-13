/*
 *  ofxMSATouchListener.cpp
 *  FBO Paint
 *
 *  Created by Mehmet Akten on 02/03/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSATouchClient.h"

#define		TOUCH_LIFE		5	// how many frames a cursor should live for when no message received


ofxMSATouchClient::ofxMSATouchClient() {
	multiTouchListener = NULL;
	baseIndex = 0;
}


ofxMSATouchClient::~ofxMSATouchClient() {
	multiTouchListener = NULL;
	clear();
}


void ofxMSATouchClient::setup(int port) {
	oscReceiver.setup(port);
}



void ofxMSATouchClient::updateCursors(ofxMSAReceivedTouch &cursor) {
	int index = -1;
	
	// look for the received cursor in the vector (check ip address and cursorId of sender)
	// note cursorId in the oscmessage is not nessecarily the cursor id in this app
	for(int i=0; i<cursors.size(); i++) {
		if(cursor.senderIP.compare(cursors[i].senderIP) == 0 && cursor.cursorId == cursors[i].cursorId) {
			index = i;
			break;
		}
	}
	
	if(index == -1) {					// if not found
		cursors.push_back(cursor);			// add to vector
		index = cursors.size() - 1;
		multiTouchListener->touchDown(cursor.pos.x, cursor.pos.y, index + baseIndex);
	} else {
		cursors[index].pos = cursor.pos;
		multiTouchListener->touchMoved(cursor.pos.x, cursor.pos.y, index + baseIndex);
	}
	
	cursors[index].aliveCounter = TOUCH_LIFE;
}



void ofxMSATouchClient::clear() {
	cursors.clear();
}


void ofxMSATouchClient::update() {
	if(!multiTouchListener) return;
	
	while(oscReceiver.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
		if(m.getAddress() == MSATOUCH_ADDRESS) {
			ofxMSAReceivedTouch cursor;
			cursor.readFromMessage(m);
			updateCursors(cursor);
		}
	}
	
	for(int i=0; i<cursors.size(); i++) {
		if(cursors[i].aliveCounter > 0) {
			cursors[i].aliveCounter--;
			if(cursors[i].aliveCounter == 0) multiTouchListener->touchUp(cursors[i].pos.x, cursors[i].pos.y, i + baseIndex);			// TODO: remove from vector and update ids
		}
	}
}
