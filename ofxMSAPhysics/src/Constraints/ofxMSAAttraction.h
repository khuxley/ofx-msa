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
#pragma once

#include "ofMain.h"
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
		ofPoint delta = (*_b) - (*_a);
		float deltaLength2 = msaLengthSquared(delta);
		if(_minDist2 && deltaLength2 > _minDist2) return;
		
		float force = _strength * (_b->getMass()) * (_a->getMass()) / (deltaLength2 + 0.001);		// to avoid divide by zero
		
		if (!_a->isFixed()) *_a += delta * (_a->getInvMass() * force);
		if (!_b->isFixed()) *_b -= delta * (_b->getInvMass() * force);
	}
	
};
