#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

#include "ofxXmlSettings.h"
#include "ofTextureAdv.h"
#include "ofxSimpleGuiToo.h"

/********** TODO **************
- edge blending
- warp on second display output or first

****************************/

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

	ofTextureAdv fbo;
	ofxXmlSettings xml;


	// MEMO
	bool enabled;
	bool doDrawConfig;
	bool doDrawOrig;
	bool doReset;
	bool doSave;
	bool doLoad;
	int screenStartPos;					// the ratio at which to show the display screen
	int screenStartPosOld;
	ofRectangle guiIn;
	ofRectangle guiOut;
	ofRectangle renderRect;
	ofPoint fullSize;

	void setupUI(ofxSimpleGuiToo &ui);

	inline void update() {
        if(doReset) {
            doReset = false;
            resetCoordinates();
        }

        if(doSave) {
            doSave = false;
            saveToXML();
        }

        if(doLoad) {
            doLoad = false;
            loadFromXML();
        }


		if(screenStartPosOld != screenStartPos) {
			autoLayout();
		}
	}


	void autoLayout(float x = 0, float y = 0);

	void destroy();
	void clear() {
		fbo.clear();
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
	    glColor4f(1, 1, 1, 1);
		fbo.draw(0, 0, renderRect.x, renderRect.height);
	}

	inline void drawOrig(float x, float y, float w, float h) {
		glColor4f(1, 1, 1, 1);
		fbo.draw(x, y, w, h);
	}

	inline void draw() {
        if(enabled ) {
            ofDisableAlphaBlending();
            if(doDrawConfig) drawConfig();
            else if(doDrawOrig) drawOrig();
            drawOutput();
        }
	}

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

