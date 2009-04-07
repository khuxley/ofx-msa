/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 ***********************************************************************/ 

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
