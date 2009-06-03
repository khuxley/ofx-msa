/*
 *  ofxMSAProtectedImage.cpp
 *  ofxMSADataProtector Demo
 *
 *  Created by Mehmet Akten on 03/06/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSAProtectedImage.h"

bool ofxMSAProtectedImage::loadProtected(string fileName, string checkAgainstHash, bool checkMD5) {
	ofxMSAProtectedFile::loadProtected(fileName, checkAgainstHash, checkMD5);
	return loadImage(fileName);
}