/***********************************************************************
 
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

#pragma once

#include "ofMain.h"

void ofClear();

class ofAdvColor : public ofColor{
public:

	void set(float r, float g, float b, float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	
	// H [0..360], S and V [0..1]
	void setHSV(float h, float s, float v, float a = 1) {
		int i = (int)floor(h/60.0f) % 6;
		float f = h/60.0f - floor(h/60.0f);
		float p = v * (1 - s);
		float q = v * (1 - s * f);
		float t = v * (1 - (1 - f) * s);
		
		switch (i) {   
			case 0: set(v, t, p, a); break;
			case 1: set(q, v, p, a); break;
			case 2: set(p, v, t, a); break;
			case 3: set(p, q, v, a); break;
			case 4: set(t, p, v, a); break;
			case 5: set(v, p, q, a); break;
		}
	} 
	
	// assumes RGB is normalized [0..1]
	// returns H [0..360], S and V [0..1]
	void getHSV(ofPoint& outHSV) {
		float h, s, v;
		float y, r1,g1,b1;
		
		v = r;
		if (v<g) v=g;
		if (v<b) v=b;
		y = r;
		if (y>g) y=g;
		if (y>b) y=b;
		if (v != 0) s = (v-y)/v;
		else s = 0;
		if (s == 0) {
			h = 0;
			s = 0;
			v = (int)(v*100);
		}
		r1 = (v-r)/(v-y);
		g1 = (v-g)/(v-y);
		b1 = (v-b)/(v-y);
		if (r == v){
			if (g == y) h = 5.+b1;
			else h = 1.-g1;
		}
		else if (g == v){
			if (b == y) h = r1+1.;
			else h = 3.-b1;
		}
		else{
			if (r == y) h = 3.+g1;
			else h = 5.-r1;
		}
		// convert it all
		h = h * 60.;
		if (h >= 360.) h = h-360.;
		outHSV.set(h, s, v);
	}
};
