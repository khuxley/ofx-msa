/*
 *  ofxThreadedImageSaver.h
 *  Body Paint
 *
 *  Created by Mehmet Akten on 27/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxThread.h"

class ofxThreadedImageSaver : public ofxThread, public ofImage {
public:
	string fileName;
	
	void threadedFunction() {
		if(lock()) {
			saveImage(fileName);
			unlock();
		} else {
			printf("ofxThreadedImageSaver - cannot save %s cos I'm locked", fileName.c_str());
		}
		stopThread();
	}
	
	void saveThreaded(string fileName) {
		this->fileName = fileName;
		startThread(false, false);   // blocking, verbose
	}
};

