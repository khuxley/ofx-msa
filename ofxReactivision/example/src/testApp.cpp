/*
 *  TuioTest.cpp
 *  Reactivision Test
 *
 *  Created by Mehmet Akten on 15/09/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#include "testApp.h"

string eventString;	// quick'n'dirty way to get string from testApp

//--------------------------------------------------------------
void testApp::setup(){	 
	tuioClient = new TuioClient(3333);
	tuioClient->addTuioListener(&tuioListener);
	tuioClient->start();
}


//--------------------------------------------------------------
void testApp::update() {
	
}


//--------------------------------------------------------------
void testApp::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	char id[3];
	
	// draw the cursors
	list<TuioCursor*> cursorList = tuioClient->getTuioCursors();
	for (list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		list<TuioPoint> path = (*tuioCursor)->getPath();
		if (path.size()>0) {
			TuioPoint last_point = path.front();
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			for (list<TuioPoint>::iterator point = path.begin(); point!=path.end(); point++) {
				glVertex3f(last_point.getX()*ofGetWidth(), last_point.getY()*ofGetHeight(), 0.0f);
				glVertex3f(point->getX()*ofGetWidth(), point->getY()*ofGetHeight(), 0.0f);
				last_point.update(point->getX(), point->getY());
			}
			glEnd();
			
			float xpos = last_point.getX() * ofGetWidth();
			float ypos = last_point.getY() * ofGetHeight();
			
			// draw the finger tip
			glColor3f(1, 0, 0);
			int radius = ofGetHeight()/100;
			ofEllipse(xpos, ypos, radius, radius);
			
			ofDrawBitmapString(ofToString((*tuioCursor)->getFingerID()), xpos + radius, ypos+5);
		}
	}
	
	// draw the objects
	list<TuioObject*> objectList = tuioClient->getTuioObjects();
	for (list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		float xpos  = (*tuioObject)->getX() * ofGetWidth();
		float ypos  = (*tuioObject)->getY() * ofGetHeight();
		float angle = (*tuioObject)->getAngle() / M_PI*180;
		
		glColor3f(0, 0, 1);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		int radius = ofGetHeight()/20.0f;
		ofRect(-radius, -radius, 2*radius, 2*radius);
		glPopMatrix();
		
		glColor3f(1.0, 1.0, 1.0);
		ofDrawBitmapString(ofToString((*tuioObject)->getFiducialID()), xpos, ypos+5);
	}
	
	glColor3f(0, 0, 0);
	ofDrawBitmapString(eventString, 10, 30);
}


//--------------------------------------------------------------
void testApp::exit() {
	tuioClient->stop();
	delete tuioClient;
}