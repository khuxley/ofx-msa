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





