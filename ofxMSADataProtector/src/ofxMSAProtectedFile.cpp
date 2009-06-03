/*
 *  ofxMSAProtectedFile.cpp
 *  ofxMSADataProtector Demo
 *
 *  Created by Mehmet Akten on 03/06/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSAProtectedFile.h"

bool ofxMSAProtectedFile::loadProtected(string filename, string checkAgainstHash, bool checkMD5) {
	md5wrapper md5;
	string path = ofToDataPath(filename);
	string currentHash = md5.getHashFromFile(path);
	bool isCorrect = checkAgainstHash.compare(currentHash) == 0;
	printf("MD5 for file %s : %s comparing against %s is %s\n", filename.c_str(), currentHash.c_str(), checkAgainstHash.c_str(), isCorrect ? "TRUE" : "FALSE");
	if(!isCorrect) {
		printf(" **** DATA CORRUPT **** ");
		std:exit(1);
	}
	
	return true;
}