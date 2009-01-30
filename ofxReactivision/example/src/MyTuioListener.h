/*
 *  MyTuioListener.h
 *  Reactivision Test
 *
 *  Created by Mehmet Akten on 15/09/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#pragma once

#include "ofxReactivision.h"
#include <string>

// this class just dumps the event info to the log and screen
// all the drawing of objects is done in testApp::draw()

// these events are called from a seperate thread, so you cannot draw to the screen

extern string eventString;		// quick'n'dirty way to send string to testApp

class MyTuioListener : public TuioListener {
	char sz[255];
	void addTuioObject(TuioObject *tobj) {
		sprintf(sz, "MyTuioListener::addTuioObject() fiducialId:%i (sessionId:%i)\n   pos:(%.5f, %.5f), posSpeed:%.5f, posAccel:%.5f\n   rot:%.5f, rotSpeed:%.5f, rotAccel: %.5f\n", 
				tobj->getFiducialID(), tobj->getSessionID(), tobj->getX(), tobj->getY(), tobj->getMotionSpeed(), tobj->getMotionAccel(), tobj->getAngle(), tobj->getRotationSpeed(), tobj->getRotationAccel());
		printf(sz);
		eventString = string(sz);
	}
	
	void updateTuioObject(TuioObject *tobj) {
		sprintf(sz, "MyTuioListener::updateTuioObject() fiducialId:%i (sessionId:%i)\n   pos:(%.5f, %.5f), posSpeed:%.5f, posAccel:%.5f\n   rot:%.5f, rotSpeed:%.5f, rotAccel: %.5f\n", 
				tobj->getFiducialID(), tobj->getSessionID(), tobj->getX(), tobj->getY(), tobj->getMotionSpeed(), tobj->getMotionAccel(), tobj->getAngle(), tobj->getRotationSpeed(), tobj->getRotationAccel());
		printf(sz);
		eventString = string(sz);
	}
	
	void removeTuioObject(TuioObject *tobj) {	
		sprintf(sz, "MyTuioListener::removeTuioObject() fiducialId: %i, sessionId: %i\n", tobj->getFiducialID(), tobj->getSessionID());
		printf(sz);
		eventString = string(sz);
	}
	
	void addTuioCursor(TuioCursor *tcur) {
		sprintf(sz, "MyTuioListener::addTuioCursor() fingerId:%i (sessionId:%i)\n   pos:(%.5f, %.5f), posSpeed:%.5f, posAccel:%.5f\n", 
				tcur->getFingerID(), tcur->getSessionID(), tcur->getX(), tcur->getY(), tcur->getMotionSpeed(), tcur->getMotionAccel());
		printf(sz);
		eventString = string(sz);
	}
	
	void updateTuioCursor(TuioCursor *tcur) {
		sprintf(sz, "MyTuioListener::updateTuioCursor() fingerId:%i (sessionId:%i)\n   pos:(%.5f, %.5f), posSpeed:%.5f, posAccel:%.5f\n", 
				tcur->getFingerID(), tcur->getSessionID(), tcur->getX(), tcur->getY(), tcur->getMotionSpeed(), tcur->getMotionAccel());
		printf(sz);
		eventString = string(sz);
	}
	
	void removeTuioCursor(TuioCursor *tcur) {
		sprintf(sz, "MyTuioListener::removeTuioCursor() fingerId: %i, sessionId: %i\n", tcur->getFingerID(), tcur->getSessionID());
		printf(sz);
		eventString = string(sz);
	}
	
	void refresh(long timestamp) {
		printf("MyTuioListener::refresh(%i)\n", timestamp);
	}
};