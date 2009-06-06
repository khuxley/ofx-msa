/*
 *  ofFBOTexture.h
 *  openFrameworks
 *
 *  Created by Zach Gage on 3/28/08.
 *  Copyright 2008 STFJ.NET. All rights reserved.
 *
 */

#ifndef _FBO_TEX
#define _FBO_TEX


#include "ofMain.h"
#include "ofxThreadedImageSaver.h"

#include <iostream>


class ofFBOTexture : public ofTexture {
public:
	
	void allocate(int w, int h, bool autoClear);
	
	void swapIn();
	void swapOut();
	
	void setupScreenForMe();
	void setupScreenForThem();
	
	void begin() {
		swapIn();
		setupScreenForMe();
	}
	
	void end() {
		swapOut();
		setupScreenForThem();
	}
	
	void saveImage(string fileName);
	
	
	void clear();
	
	
protected:
	bool		_isActive;
	GLuint fbo;					// Our handle to the FBO
	GLuint depthBuffer;			// Our handle to the depth render buffer
	bool autoClear;
	void clean();
	ofxThreadedImageSaver imageSaver;
};

#endif

