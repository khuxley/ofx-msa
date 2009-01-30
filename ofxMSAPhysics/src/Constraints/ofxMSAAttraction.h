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

#define OF_ADDON_USING_OFXVECTORMATH
#include "ofMain.h"
#include "ofAddons.h"

#include "ofxMSAConstraint.h"

class ofxMSAAttraction : public ofxMSAConstraint {
public:	
	friend class ofxMSAPhysics;
	
	ofxMSAAttraction(ofxMSAParticle *a, ofxMSAParticle *b, float strength, float minimumDistance) {
		this->_a = a;
		this->_b = b;
		setStrength(strength);
		setMinimumDistance(minimumDistance);
		
		_type = OFX_MSA_CONSTRAINT_TYPE_ATTRACTION;
	}
	
	// set minimum distance before force takes affect
	inline void setMinimumDistance(float d) {
		_minDist = d;
		_minDist2 = d*d;
	}
	
	// get minimum distance
	inline float getMinimumDistance() {
		return _minDist;
	}
	
	// set strength of attraction (+ve
	inline void setStrength(float newStrength) {
		_strength = newStrength;
	}
	
	inline float getStrength() {
		return _strength;
	}
	
	
protected:	
	float _minDist, _minDist2;
	float _strength;
	
	void solve() {
		if(isOff()) return;
		
		ofxVec3f delta = (*_b) - (*_a);
		float deltaLength2 = delta.lengthSquared();
		if(_minDist2 && deltaLength2 > _minDist2) return;
		
		float force = _strength * (_b->getMass()) * (_a->getMass()) / (deltaLength2 + 0.001);		// to avoid divide by zero
		
		if (!_a->isFixed()) *_a += (_a->getInvMass() * force) * delta;
		if (!_b->isFixed()) *_b -= (_b->getInvMass() * force) * delta;
	}
	
};
