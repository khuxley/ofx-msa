/***********************************************************************
 
 This class is for drawing a fluidsolver using the openFrameworks texture
 
 -----------------------------------
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/


#include "ofxMSAFluidDrawer.h"

ofxMSAFluidDrawer::ofxMSAFluidDrawer() {
	//	printf("ofxMSAFluidDrawer::ofxMSAFluidDrawer()\n");	
	_pixels				= NULL;
	_byteCount			= 0;
	_fluidSolver		= NULL;
	_didICreateTheFluid	= false;
	alpha				= 1;
	setDrawMode(FLUID_DRAW_COLOR);
}

ofxMSAFluidDrawer::~ofxMSAFluidDrawer() {
	//	printf("ofxMSAFluidDrawer::~ofxMSAFluidDrawer()\n");		
	deleteFluidSolver();
}



ofxMSAFluidSolver* ofxMSAFluidDrawer::setup(int NX, int NY) {
	//	printf("ofxMSAFluidDrawer::createFluidSolver(%i, %i, %.6f, %.6f, %.6f)\n", NX, NY, dt, visc, fadeSpeed);
	deleteFluidSolver();
	_fluidSolver = new ofxMSAFluidSolver;
	_fluidSolver->setup(NX, NY);
	createTexture();
	
	return _fluidSolver;
}

ofxMSAFluidSolver* ofxMSAFluidDrawer::setFluidSolver(ofxMSAFluidSolver* f) {
	deleteFluidSolver();
	_fluidSolver = f;
	createTexture();
	
	return _fluidSolver;
}

ofxMSAFluidSolver* ofxMSAFluidDrawer::getFluidSolver() {
	return _fluidSolver;
}

void ofxMSAFluidDrawer::createTexture() {
	if(_pixels) delete _pixels;
	_pixels = new unsigned char[_fluidSolver->getNumCells() * 3];
#ifdef FLUID_TEXTURE
	tex.allocate(_fluidSolver->getWidth(), _fluidSolver->getHeight(), GL_RGB);	
#endif
}


void ofxMSAFluidDrawer::reset() {
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::reset() - Fluid not ready\n");
		return;
	}
	_fluidSolver->reset();
}

void ofxMSAFluidDrawer::update() {
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::updateFluid() - Fluid not ready\n");
		return;
	}
	_fluidSolver->update();
}


void ofxMSAFluidDrawer::setDrawMode(int newDrawMode) {
	_drawMode = newDrawMode;
}


void ofxMSAFluidDrawer::draw(float x, float y, float renderWidth, float renderHeight) {
	switch(_drawMode) {
		case FLUID_DRAW_COLOR:
			drawColor(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_MOTION:
			drawMotion(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_SPEED:
			drawSpeed(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_VECTORS:
			drawVectors(x, y, renderWidth, renderHeight);
			break;
			
	}
}


void ofxMSAFluidDrawer::drawColor(float x, float y, float renderWidth, float renderHeight) {
	if(alpha == 0) return;
	
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::drawColor() - Fluid not ready\n");
		return;
	}
	//	int index;
	int numCells = _fluidSolver->getNumCells();
	
	ofPoint color;
	for(int i=0, index=0; i<numCells; i++, index+=3) {
		_fluidSolver->getInfoAtCell(i, NULL, &color);
		_pixels[index]		= MIN(color.x * 255 * alpha, 255);
		_pixels[index + 1]	= MIN(color.y * 255 * alpha, 255);		
		_pixels[index + 2]	= MIN(color.z * 255 * alpha, 255);		
		//		_pixels[index]		= ofRandom(0, 255);
		//		_pixels[index + 1]	= ofRandom(0, 255);		
		//		_pixels[index + 2]	= ofRandom(0, 255);		
	}  
	
	int w = _fluidSolver->getWidth();
	int h = _fluidSolver->getHeight();
	
	if(renderWidth == FLUID_DEFAULT_SIZE) renderWidth = w;
	if(renderHeight == FLUID_DEFAULT_SIZE) renderHeight = h;
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, w, h, GL_RGB);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
	
}

void ofxMSAFluidDrawer::drawMotion(float x, float y, float renderWidth, float renderHeight) {
	if(alpha == 0) return;
	
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::drawColor() - Fluid not ready\n");
		return;
	}
	//	int index;
	int numCells = _fluidSolver->getNumCells();
	
	int w = _fluidSolver->getWidth();
	int h = _fluidSolver->getHeight();
	
	ofPoint vel;
	for(int i=0, index=0; i<numCells; i++, index+=3) {
		_fluidSolver->getInfoAtCell(i, &vel, NULL);
		_pixels[index]		= MIN(fabs(vel.x) * w * 255 * alpha, 255);
		_pixels[index + 1]	= MIN(fabs(vel.y) * h * 255 * alpha, 255);		
		_pixels[index + 2]	= 0;		
	}  
	if(renderWidth == FLUID_DEFAULT_SIZE) renderWidth = w;
	if(renderHeight == FLUID_DEFAULT_SIZE) renderHeight = h;
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, w, h, GL_RGB);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
}

void ofxMSAFluidDrawer::drawSpeed(float x, float y, float renderWidth, float renderHeight) {
	if(alpha == 0) return;
	
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::drawColor() - Fluid not ready\n");
		return;
	}
	//	int index;
	int numCells = _fluidSolver->getNumCells();
	
	int w = _fluidSolver->getWidth();
	int h = _fluidSolver->getHeight();
	
	ofPoint vel;
	for(int i=0, index=0; i<numCells; i++, index+=3) {
		_fluidSolver->getInfoAtCell(i, &vel, NULL);
		float speed2 = fabs(vel.x) * w + fabs(vel.y) * h;
		int speed = MIN(speed2 * 255 * alpha, 255);
		_pixels[index]		= speed;
		_pixels[index + 1]	= speed;
		_pixels[index + 2]	= speed;		
	}  
	
	if(renderWidth == FLUID_DEFAULT_SIZE) renderWidth = w;
	if(renderHeight == FLUID_DEFAULT_SIZE) renderHeight = h;
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, w, h, GL_RGB);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
}


void ofxMSAFluidDrawer::deleteFluidSolver() {
	//	printf("ofxMSAFluidDrawer::deleteFluidSolver()\n");	
	if(_fluidSolver && _didICreateTheFluid) {
		delete _fluidSolver;
		_fluidSolver = NULL;
		
		if(_pixels) delete _pixels;
		_pixels = NULL;
		
#ifdef FLUID_TEXTURE		
		tex.clear();
#endif		
	}	
}

bool ofxMSAFluidDrawer::isFluidReady() {
	if(!_fluidSolver) {
		printf("ofxMSAFluidDrawer::isFluidReady() - No fluid solver\n");
		return false;
	}
	
	if(!_fluidSolver->isInited()) {
		printf("ofxMSAFluidDrawer::isFluidReady() - Fluid solver not initialized yet, call init()\n");
		return false;
	}
	
	return true;
}

