/*
 *  ofxMSAUtils.cpp
 *  Meshmerizer
 *
 *  Created by Mehmet Akten on 19/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSAUtils.h"

void msaClear() {
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void msaConstrain(float &pos, float &vel, float min, float max, float bounce) {
	if(pos < min) {
		pos = min;
		vel = fabs(vel) * bounce;
	} else if(pos > max) {
		pos = max;
		vel = -fabs(vel) * bounce;
	}
}	

void msaConstrain(ofPoint &pos, ofPoint &vel, ofPoint &min, ofPoint &max, float bounce) {
	msaConstrain(pos.x, vel.x, min.x, max.x, bounce);
	msaConstrain(pos.y, vel.y, min.y, max.y, bounce);
	msaConstrain(pos.z, vel.z, min.z, max.z, bounce);
}