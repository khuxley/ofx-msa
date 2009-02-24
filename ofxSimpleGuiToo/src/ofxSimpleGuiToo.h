
#ifndef OFX_SIMPLE_GUI_H
#define OFX_SIMPLE_GUI_H

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "ofxSimpleGuiIncludes.h"

#define	OFX_SIMPLEGUITOO_XML_NAME	"ofxSimpleGuiToo.xml"

class ofxSimpleGuiToo {

	
public:
	int							guiFocus;
	ofxSimpleGuiConfig			*config;	
	
	ofxSimpleGuiToo();

	void					loadFromXML(string file = OFX_SIMPLEGUITOO_XML_NAME);
	void					saveToXML(string file = OFX_SIMPLEGUITOO_XML_NAME);	
	void					setAutoSave(bool b);

	void					setVerbose(bool v);
	
//	int		getValueI(string nameID);
//	float	getValueF(string nameID);
//	bool	getValueB(string nameID);
	
	void					drawFocus(float x, float y);
	void					setDraw(bool b);
	void					toggleDraw();
	void					draw();
	bool					isOn();
	
	void					nextPage();
	void					prevPage();
	void					setPage(int i);				// 1 based index of page
	void					setPage(string name);
	
	ofxSimpleGuiPage		*page(int i);				// 1 based index of page
	ofxSimpleGuiPage		*page(string name);
	
	ofxSimpleGuiPage		*addPage(string name = "");
	ofxSimpleGuiControl		*addControl(ofxSimpleGuiControl* control);
	ofxSimpleGuiButton		*addButton(string name, bool *value);
	ofxSimpleGuiSliderInt	*addSlider(string name, int *value, int min, int max);
	ofxSimpleGuiSliderFloat	*addSlider(string name, float *value, float min, float max, float smoothing = 0);
	ofxSimpleGuiSlider2d	*addSlider2d(string name, ofPoint* value, float xmin, float xmax, float ymin, float ymax);
	ofxSimpleGuiQuadWarp	*addQuadWarper(string name, float x, float y, float sw, float sh, ofPoint **pts);
	ofxSimpleGuiMovieSlider	*addMovieSlider(string name, ofVideoPlayer* input);
	ofxSimpleGuiToggle		*addToggle(string name, bool *value);
	ofxSimpleGuiTitle		*addTitle(string name);
	ofxSimpleGuiContent		*addContent(string name, ofBaseDraws *content, float fixwidth = -1);
	
protected:
	bool							doAutoSave;
	bool							doSave, doSaveBackup;
	bool							changePage;
	int								currentPage;			// 1 based index of page (0 is for global controls)
	
	ofxXmlSettings					XML;
	string							xmlFile;
	
	bool							verbose;
	bool							doDraw;
	float							border;

	ofxSimpleGuiPage				*headerPage;
	vector <ofxSimpleGuiPage*>		pages;				// 0 is for headerPage
	
	void addListeners();
	void removeListeners();
	
//	void setup(ofEventArgs &e);
	void update(ofEventArgs &e);
//  void draw(ofEventArgs &e);
//	void exit(ofEventArgs &e);
	
	void mouseMoved(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);	
	void mouseDragged(ofMouseEventArgs &e);	
	void mouseReleased(ofMouseEventArgs &e);
	
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);
};

#endif






