#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

#include "ofxXmlSettings.h"
#include "ofTextureAdv.h"

class ofxRenderManager {


public:

	ofxRenderManager();
	~ofxRenderManager();
	void allocateForNScreens(int numScreens, int renderWidth, int renderHeight);

	void drawInputMaps(float x, float y, float w, float h); // can't specify abs dimensions, since might be diff apsect ratio...
	void drawOutputMaps(float x, float y, float w, float h); // can't specify abs dimensions, since might be diff apsect ratio...

	void drawScreen(int nScreen);

	void begin();
	void end();

	bool mouseSelectInputPoint(ofRectangle &drawRect, int x, int y, float clickRadius = 15);
	bool mouseDragInputPoint(ofRectangle &drawRect, int x, int y);

	bool mouseSelectOutputPoint(ofRectangle &drawRect, int x, int y, float clickRadius = 15);
	bool mouseDragOutputPoint(ofRectangle &drawRect, int x, int y);

	void resetCoordinates();

	void loadFromXML();
	void loadFromXML(string xmlFileName);
	void saveToXML();
	void saveToXML(string xmlFileName);


	int    activeScreenIn;
	int    activePointIn;

	int    activeScreenOut;
	int    activePointOut;

	float width, height;
	float screenWidth, screenHeight;
	int nScreens;

	bool bInputSelected;

	ofPoint ** outputPositions;
	ofPoint ** inputPositions;

	string xmlFile;

	ofTextureAdv myOffscreenTexture;
	ofxXmlSettings xml;


	// MEMO
	int screenStartPos;					// the ratio at which to show the display screen
	int screenStartPosOld;
	ofRectangle guiIn;
	ofRectangle guiOut;
	ofRectangle renderRect;

	inline void update() {
		if(screenStartPosOld != screenStartPos) {
			autoLayout();
		}
	}


	void autoLayout();

	void destroy();
	void clear() {
		myOffscreenTexture.clear();
	}

	// draws final warped output
	inline void drawOutput() {
		drawOutput(renderRect.x, renderRect.y, renderRect.width, renderRect.height);
	}

	inline void drawOutput(float x, float y, float w, float h) {
		glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(w/width, h/height, 1);
		glColor4f(1, 1, 1, 1);
		for(int i=0; i<nScreens; i++) drawScreen(i);
		glPopMatrix();
	}

	// draws original
	inline void drawOrig() {
		myOffscreenTexture.draw(0, 0, renderRect.x, renderRect.height);
	}

	inline void drawOrig(float x, float y, float w, float h) {
		myOffscreenTexture.draw(x, y, w, h);
	}

//	inline void draw() {
//		drawConfig();
//		drawOutput();
//	}

	// draws config maps
	inline void drawConfig() {
		drawInputMaps();
		drawOutputMaps();
	}

	inline void drawInputMaps() {
		drawInputMaps(guiIn.x, guiIn.y, guiIn.width, guiIn.height);
	}

	inline void drawOutputMaps() {
		drawOutputMaps(guiOut.x, guiOut.y, guiOut.width, guiOut.height);
	}

	void addListeners();
	void removeListeners();
	void _mousePressed(ofMouseEventArgs &e);
	void _mouseDragged(ofMouseEventArgs &e);

};

#endif

