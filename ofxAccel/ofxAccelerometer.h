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

#include "ofTypes.h"

#define OFXACCEL_DEFAULT_SMOOTHING				0.1f

typedef void (*ofxAccelCB)(ofPoint&);			// typedef for accelerometer callback

class ofxAccelerometerHandler {
public:
	ofxAccelerometerHandler() {
		callback = NULL;
		smoothAmount = OFXACCEL_DEFAULT_SMOOTHING;			// amount to smooth incoming data by
	}
	
	// call this to set it all up
	void setup();
	
	// call this when you no longer need the accelerometer
	void exit();
	
	// returns current accelerometer data (value in number of g's (1g = gravity, 9.8m/s^2)
	ofPoint &getForce() {
		return force;
	}
	
	// returns current orientation in degrees (x: pitch, y: roll, z: not used)
	ofPoint &getOrientation() {
		calcOrientation();
		return orientation;
	}
	
	// set amount of smoothing on data (0: no smooth, 1:very smooth)
	void setSmooth(float new_smoothAmount) {
		smoothAmount = new_smoothAmount;
	}
	
	// if you have a callback which conforms to ofxAccelCB, pass it to this to have it called when motion is detected
	void setCallback(ofxAccelCB new_callback) {
		callback = new_callback;
	}

	
	// platform specific accelerometer engine should call this when motion is detected
	void update(float x, float y, float z) {
		if(smoothAmount) {
			float lerpFactor = 1 - smoothAmount;	
			if(lerpFactor>1) lerpFactor = 1;
			else if(lerpFactor < 0.01) lerpFactor = 0.01;
			
			force.x += (x - force.x) * lerpFactor;
			force.y += (y - force.y) * lerpFactor;
			force.z += (z - force.z) * lerpFactor;
		} else {
			force.set(x, y, z);
		}
		
		if(callback) callback(force);
	}			
	
protected:
	ofxAccelCB callback;
	float smoothAmount;			// amount to smooth incoming data by
	ofPoint force;				// current acceleration
	ofPoint orientation;		// current orientation
	ofPoint restAccel;			// rest acceleration (for calibration)
	
	void calcOrientation() {
		orientation.x = atan2(force.y, -force.z) * RAD_TO_DEG; 
		orientation.y = atan2(force.x, -force.z) * RAD_TO_DEG;
		orientation.z = 0;
	}
};

extern ofxAccelerometerHandler ofxAccelerometer;
