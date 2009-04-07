/***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 ***********************************************************************/ 

#pragma once

#include "ofMain.h"
#include "ofxMSAConstraint.h"

class ofxMSASpring : public ofxMSAConstraint {
public:	
	friend class ofxMSAPhysics;
	
	float restLength;
	float strength;
	
	ofxMSASpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength) {
		this->_a = a;
		this->_b = b;
		strength	= _strength;
		restLength	= _restLength;
		_type = OFX_MSA_CONSTRAINT_TYPE_SPRING;
		setClassName(string("ofxMSASpring"));
	}
	
protected:	
	void solve() {
		ofPoint delta = (*_b) - (*_a);
		float deltaLength2 = msaLengthSquared(delta);
		float deltaLength = sqrt(deltaLength2);	// TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
		float force = strength * (deltaLength - restLength) / (deltaLength * (_a->getInvMass() + _b->getInvMass()));
		
		if (!_a->isFixed()) *_a += delta * (_a->getInvMass() * force);
		if (!_b->isFixed()) *_b -= delta * (_b->getInvMass() * force);
 	}
	
};
