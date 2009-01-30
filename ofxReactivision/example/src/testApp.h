#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofAddons.h"

#include "ofxReactivision.h"
#include "MyTuioListener.h"

class testApp : public ofSimpleApp {
public:
	TuioClient *tuioClient;
	MyTuioListener tuioListener;
	
	void setup();
	void update();
	void draw();
	void exit();
};

#endif

