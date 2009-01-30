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


#import "iPhoneAppDelegate.h"
#include "ofMain.h"



@implementation iPhoneAppDelegate


-(void) timerLoop {
	// create autorelease pool in case anything needs it
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	iPhoneWindow->timerLoop();
	
	// release pool
	[pool release];
}



-(void) applicationDidFinishLaunching:(UIApplication *)application {    
	// get screen bounds
	CGRect	rect = [[UIScreen mainScreen] bounds];
	
	// create fullscreen window
	window = [[UIWindow alloc] initWithFrame:rect];
	
	// create the OpenGL view and add it to the window
	glView = [[EAGLView alloc] initWithFrame:rect pixelFormat:GL_RGB565_OES depthFormat:GL_DEPTH_COMPONENT16_OES preserveBackbuffer:NO];	
	[window addSubview:glView];
	
	// release glView (window still has retain on it)
	[glView release];
	
	// make window active
	[window makeKeyAndVisible];
	
	// save reference to ofAppiPhoneWindow for quick access
	iPhoneWindow = (ofAppiPhoneWindow*)ofAppWindow;
	
	// give baseApp reference to glView for touch callbacks
	[glView setApp:iPhoneWindow->baseApp];
	
	// give glView reference to iPhoneWindow
	iPhoneWindow->glView = glView;
	
	// gobe delegate reference to iPhoneWindow
	iPhoneWindow->appDelegate = self;
	
	// show or hide status bar depending on OF_WINDOW or OF_FULLSCREEN
	[[UIApplication sharedApplication] setStatusBarHidden:(iPhoneWindow->windowMode == OF_FULLSCREEN) animated:YES];

	// start timer
//	[self setFrameRate:60];
	timer = [NSTimer scheduledTimerWithTimeInterval:(1.0f / 60.0f) target:self selector:@selector(timerLoop) userInfo:nil repeats:YES];
	
	
	// call testApp::setup()
	iPhoneWindow->baseApp->setup();
}

-(void) setFrameRate:(float)frameRate {
//	[timer invalidate];
//	timer = [NSTimer scheduledTimerWithTimeInterval:(1.0f / frameRate) target:self selector:@selector(timerLoop) userInfo:nil repeats:YES];
}


-(void) dealloc {
    [window release];
//	[glView release];		// we dont need to release this, window will
    [super dealloc];
}




-(void) applicationWillResignActive:(UIApplication *)application {
	// add lostFocus() to baseApp?
}


-(void) applicationDidBecomeActive:(UIApplication *)application {
	// add gotFocus() to baseApp?
}


-(void) applicationWillTerminate:(UIApplication *)application {
	[timer invalidate];
	iPhoneWindow->baseApp->exit();
	delete iPhoneWindow->baseApp;
}


-(void) applicationDidReceiveMemoryWarning:(UIApplication *)application {
	// add callback for this
}


@end
