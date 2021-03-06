/***********************************************************************

 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/


#include "testApp.h"
#include "ofxMSAPhysics.h"


#define	SPRING_MIN_STRENGTH		0.005
#define SPRING_MAX_STRENGTH		0.1

#define	SPRING_MIN_WIDTH		1
#define SPRING_MAX_WIDTH		3

#define NODE_MIN_RADIUS			10
#define NODE_MAX_RADIUS			30

#define MIN_MASS				1
#define MAX_MASS				3

#define MIN_BOUNCE				0.2
#define MAX_BOUNCE				0.9

#define	FIX_PROBABILITY			10		// % probability of a particle being fixed on creation

#define FORCE_AMOUNT			10

#define EDGE_DRAG				0.98

#define	GRAVITY					1

#define MAX_ATTRACTION			10
#define MIN_ATTRACTION			3


bool				mouseAttract	= false;
bool				doMouseXY		= false;		// pressing left mmouse button moves mouse in XY plane
bool				doMouseYZ		= false;		// pressing right mouse button moves mouse in YZ plane
int					forceTimer		= false;


float				rotSpeed		= 0;
float				mouseMass		= 1;

static int			width;
static int			height;


ofxMSAPhysics		physics;
ofxMSAParticle		mouseNode;


void initScene() {
	// clear all particles and springs etc
	physics.clear();

	// you can add your own particles to the physics system
	physics.addParticle(&mouseNode);
	mouseNode.makeFixed();
	mouseNode.setMass(MIN_MASS);
	mouseNode.moveTo(0, 0, 0);
	mouseNode.setRadius(NODE_MAX_RADIUS);
	mouseNode.enableCollision();

	// or tell the system to create and add particles
	physics.makeParticle(-width/4, 0, -width/4, MIN_MASS)->makeFixed();		// create a node in top left back and fix
	physics.makeParticle( width/4, 0, -width/4, MIN_MASS)->makeFixed();		// create a node in top right back and fix
	physics.makeParticle(-width/4, 0,  width/4, MIN_MASS)->makeFixed();		// create a node in top left front and fix
	physics.makeParticle( width/4, 0,  width/4, MIN_MASS)->makeFixed();		// create a node in top right front and fix
}


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	width = ofGetWidth();
	height = ofGetHeight();

	//	physics.verbose = true;			// dump activity to log
	physics.setGravity(0, GRAVITY, 0);

	// set world dimensions, not essential, but speeds up collision
	physics.setWorldSize(ofPoint(-width/2, -height, -width/2), ofPoint(width/2, height, width/2));
	physics.setCollisionBinCount(ofPoint(10, 10, 10));
    physics.setDrag(0.97f);

	initScene();

	// setup lighting
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0, height/2, 0.0, 0.0 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);

	// enable back-face culling (so we can see through the walls)
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}


void addRandomParticle() {
	float posX		= ofRandom(-width/2, width/2);
	float posY		= ofRandom(0, height);
	float posZ		= ofRandom(-width/2, width/2);
	float mass		= ofRandom(MIN_MASS, MAX_MASS);
	float bounce	= ofRandom(MIN_BOUNCE, MAX_BOUNCE);
	float radius	= ofMap(mass, MIN_MASS, MAX_MASS, NODE_MIN_RADIUS, NODE_MAX_RADIUS);

	// physics.makeParticle returns a particle pointer so you can customize it
	ofxMSAParticle* p = physics.makeParticle(posX, posY, posZ);

	// and set a bunch of properties (you don't have to set all of them, there are defaults)
	p->setMass(mass)->setBounce(bounce)->setRadius(radius)->enableCollision()->makeFree();

	// add an attraction to the mouseNode
	if(mouseAttract) physics.makeAttraction(&mouseNode, p, ofRandom(MIN_ATTRACTION, MAX_ATTRACTION), 0);
}

void addRandomSpring() {
	ofxMSAParticle *a = physics.getParticle((int)ofRandom(0, physics.numberOfParticles()));
	ofxMSAParticle *b = physics.getParticle((int)ofRandom(0, physics.numberOfParticles()));
	physics.makeSpring(a, b, ofRandom(SPRING_MIN_STRENGTH, SPRING_MAX_STRENGTH), ofRandom(10, width/2));
}


void killRandomParticle() {
	ofxMSAParticle *p = physics.getParticle(floor(ofRandom(0, physics.numberOfParticles())));
	if(p && p != &mouseNode) p->kill();
}

void killRandomSpring() {
	ofxMSASpring *s = physics.getSpring( floor(ofRandom(0, physics.numberOfSprings())));
	if(s) s->kill();
}

void killRandomConstraint() {
	ofxMSAConstraint *c = physics.getConstraint(floor(ofRandom(0, physics.numberOfConstraints())));
	if(c) c->kill();
}


void toggleMouseAttract() {
	mouseAttract = !mouseAttract;
	if(mouseAttract) {
		// loop through all particles and add attraction to mouse
		// (doesn't matter if we attach attraction from mouse-mouse cos it won't be added internally
		for(int i=0; i<physics.numberOfParticles(); i++) physics.makeAttraction(&mouseNode, physics.getParticle(i), ofRandom(MIN_ATTRACTION, MAX_ATTRACTION), 0);
	} else {
		// loop through all existing attractsions and delete them
		for(int i=0; i<physics.numberOfAttractions(); i++) physics.getAttraction(i)->kill();
	}
}

void addRandomForce(float f) {
	forceTimer = f;
	for(int i=0; i<physics.numberOfParticles(); i++) {
		ofxMSAParticle *p = physics.getParticle(i);
		if(p->isFree()) p->addVelocity(ofRandom(-f, f), ofRandom(-f, f), ofRandom(-f, f));
	}
}

void lockRandomParticles() {
	for(int i=0; i<physics.numberOfParticles(); i++) {
		ofxMSAParticle *p = physics.getParticle(i);
		if(ofRandom(0, 100) < FIX_PROBABILITY) p->makeFixed();
		else p->makeFree();
	}
	mouseNode.makeFixed();
}

void unlockRandomParticles() {
	for(int i=0; i<physics.numberOfParticles(); i++) {
		ofxMSAParticle *p = physics.getParticle(i);
		p->makeFree();
	}
	mouseNode.makeFixed();
}



//--------------------------------------------------------------
void testApp::update() {
	width = ofGetWidth();
	height = ofGetHeight();

	physics.update();
}


//--------------------------------------------------------------
void testApp::draw() {
	ofEnableAlphaBlending();
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	glTranslatef(width/2, 0, -width / 3);		// center scene
	static float rot = 0;
	glRotatef(rot, 0, 1, 0);			// rotate scene
	rot += rotSpeed;						// slowly increase rotation (to get a good 3D view)

	if(forceTimer) {
		float translateMax = forceTimer;
		glTranslatef(ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax), ofRandom(-translateMax, translateMax));
		forceTimer--;
	}


	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	// draw right wall
	glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, width/2);
	glColor3f(1, 1, 1);				glVertex3f(width/2, -height, width/2);
	glColor3f(0.95, 0.95, 0.95);	glVertex3f(width/2, -height, -width/2);
	glColor3f(.85, 0.85, 0.85);		glVertex3f(width/2, height+1, -width/2);

	// back wall
	glColor3f(.9, 0.9, 0.9);		glVertex3f(width/2, height+1, -width/2);
	glColor3f(1, 1, 1);				glVertex3f(width/2, -height, -width/2);
	glColor3f(0.95, 0.95, 0.95);	glVertex3f(-width/2, -height, -width/2);
	glColor3f(.85, 0.85, 0.85);		glVertex3f(-width/2, height+1, -width/2);

	// left wall
	glColor3f(.9, 0.9, 0.9);		glVertex3f(-width/2, height+1, -width/2);
	glColor3f(1, 1, 1);				glVertex3f(-width/2, -height, -width/2);
	glColor3f(0.95, 0.95, 0.95);	glVertex3f(-width/2, -height, width/2);
	glColor3f(.85, 0.85, 0.85);		glVertex3f(-width/2, height+1, width/2);

	// front wall
	glColor3f(0.95, 0.95, 0.95);	glVertex3f(width/2, -height, width/2);
	glColor3f(.85, 0.85, 0.85);		glVertex3f(width/2, height+1, width/2);
	glColor3f(.9, 0.9, 0.9);		glVertex3f(-width/2, height+1, width/2);
	glColor3f(1, 1, 1);				glVertex3f(-width/2, -height, width/2);

	// floor
	glColor3f(.8, 0.8, 0.8);
	glVertex3f(width/2, height+1, width/2);
	glVertex3f(width/2, height+1, -width/2);
	glVertex3f(-width/2, height+1, -width/2);
	glVertex3f(-width/2, height+1, width/2);


	glEnd();

	glEnable(GL_LIGHTING);

	// draw springs
	glColor4f(0.5, 0.5, 0.5, 0.5);
	for(int i=0; i<physics.numberOfSprings(); i++) {
		ofxMSASpring *spring = (ofxMSASpring *) physics.getSpring(i);
		ofxMSAParticle *a = spring->getOneEnd();
		ofxMSAParticle *b = spring->getTheOtherEnd();
		ofPoint vec = (*b - *a);
		float dist = msaLength(vec);
		float angle = acos( vec.z / dist ) * RAD_TO_DEG;
		if(vec.z <= 0 ) angle = -angle;
		float rx = -vec.y * vec.z;
		float ry =  vec.x * vec.z;

		glPushMatrix();
		glTranslatef(a->x, a->y, a->z);
		glRotatef(angle, rx, ry, 0.0);
		float size  = ofMap(spring->strength, SPRING_MIN_STRENGTH, SPRING_MAX_STRENGTH, SPRING_MIN_WIDTH, SPRING_MAX_WIDTH);

		glScalef(size, size, dist);
		glTranslatef(0, 0, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}

	// draw particles
	for(int i=0; i<physics.numberOfParticles(); i++) {
		ofxMSAParticle *p = physics.getParticle(i);
		if(p->isFixed()) glColor4f(1, 0, 0, 1);
		else glColor4f(1, 1, 1, 1);

		// draw ball
		glPushMatrix();
		glTranslatef(p->x, p->y, p->z);
		glutSolidSphere(p->getRadius(), 15, 15);
		glPopMatrix();

		// draw shadow
		float alpha = ofMap(p->y, -height, height, 0, 1);
		if(alpha>0) {
			glPushMatrix();
			glTranslatef(p->x, height, p->z);
			glRotatef(-90, 1, 0, 0);
			glColor4f(0, 0, 0, alpha * alpha * alpha * alpha);
			ofCircle(0, 0, p->getRadius());
			glPopMatrix();
		}


	}

	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor4f(0, 0, 0, 1);
	ofDrawBitmapString( " FPS: " + ofToString(ofGetFrameRate(), 2)
					   + " | Number of particles: " + ofToString(physics.numberOfParticles(), 2)
					   + " | Number of springs: " + ofToString(physics.numberOfSprings(), 2)
					   + " | Mouse Mass: " + ofToString(mouseNode.getMass(), 2)
					   , 20, 15);




}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch(key) {
		case 'a': toggleMouseAttract(); break;
		case 'p': addRandomParticle(); break;
		case 'P': killRandomParticle(); break;
		case 's': addRandomSpring(); break;
		case 'S': killRandomSpring(); break;
		case 'c': physics.isCollisionEnabled() ? physics.disableCollision() : physics.enableCollision(); break;
		case 'C': killRandomConstraint(); break;
		case 'f': addRandomForce(FORCE_AMOUNT); break;
		case 'F': addRandomForce(FORCE_AMOUNT * 3); break;
		case 'l': lockRandomParticles(); break;
		case 'u': unlockRandomParticles(); break;
		case ' ': initScene(); break;
		case 'x': doMouseXY = true; break;
		case 'z': doMouseYZ = true; break;
		case ']': rotSpeed += 0.01f; break;
		case '[': rotSpeed -= 0.01f; break;
		case '+': mouseNode.setMass(mouseNode.getMass() +0.1); break;
		case '-': mouseNode.setMass(mouseNode.getMass() -0.1); break;
		case 'm': mouseNode.hasCollision() ? mouseNode.disableCollision() : mouseNode.enableCollision();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
	switch(key) {
		case 'x': doMouseXY = false; break;
		case 'z': doMouseYZ = false; break;
	}

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	static int oldMouseX = -10000;
	static int oldMouseY = -10000;
	int velX = x - oldMouseX;
	int velY = y - oldMouseY;
	if(doMouseXY) mouseNode.moveBy(velX, velY, 0);
	if(doMouseYZ) mouseNode.moveBy(velX, 0, velY);
	oldMouseX = x;
	oldMouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	switch(button) {
		case 0:	doMouseXY = true; mouseMoved(x, y); break;
		case 2: doMouseYZ = true; mouseMoved(x, y); break;
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	doMouseXY = doMouseYZ = false;
}
