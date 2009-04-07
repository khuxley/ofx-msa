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


#include "ofxMSATouchServer.h"

ofxMSATouchServer::ofxMSATouchServer() {
	host		= "";
	port		= 0;
	cursors		= NULL;
	maxTouches	= 0;
}


ofxMSATouchServer::~ofxMSATouchServer() {
	if(cursors) delete [] cursors;
}


void ofxMSATouchServer::cursorPressed(float x, float y, int cursorId) {
//	printf("ofxMSATouchServer::cursorPressed %.3f, %.3f\n", x, y);
	if(!cursors) return;
	cursors[cursorId].cursorPressed(x, y, cursorId);
	numDown++;
}

void ofxMSATouchServer::cursorDragged(float x, float y, int cursorId) {
	if(!cursors) return;
	cursors[cursorId].cursorDragged(x, y, cursorId);
}

void ofxMSATouchServer::cursorReleased(float x, float y, int cursorId) {
	if(!cursors) return;
	cursors[cursorId].cursorReleased(x, y, cursorId);
	numDown--;
}

void ofxMSATouchServer::setMaxTouches(int i) {
	if(cursors) delete [] cursors;	
	
	maxTouches = i;
	cursors = new ofxMSATouch[maxTouches];
	
}


void ofxMSATouchServer::setup(string host, int port) {
	if(this->host.compare(host) == 0 && this->port == port) return;
	
//	printf("ofxMSATouchServer::setup(host: %s, port: %i\n", host.c_str(), port);
	this->host = host;
	this->port = port;
	oscSender.setup(host, port);
}


void ofxMSATouchServer::update() {
	if(port == 0) return;

	ofxOscBundle b;
	for(int i=0; i<maxTouches; i++) cursors[i].addToBundle(b);
	oscSender.sendBundle(b);
}





