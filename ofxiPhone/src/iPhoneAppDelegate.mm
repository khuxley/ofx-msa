/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
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
#include "iPhoneGlobals.h"
#include "ofMain.h"



@implementation iPhoneAppDelegate


-(void) timerLoop {
	// create autorelease pool in case anything needs it
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	iPhoneGlobals.iPhoneOFWindow->timerLoop();
	
	// release pool
	[pool release];
}



-(void) applicationDidFinishLaunching:(UIApplication *)application {    
	printf("applicationDidFinishLaunching() start\n");
	
	// get screen bounds
	CGRect	rect = [[UIScreen mainScreen] bounds];
	
	// create fullscreen window
	window = [[UIWindow alloc] initWithFrame:rect];
	
	// make window active
	[window makeKeyAndVisible];
	
	
	// create the OpenGL view and add it to the window
	iPhoneGlobals.glView = [[EAGLView alloc] initWithFrame:rect pixelFormat:GL_RGB565_OES depthFormat:GL_DEPTH_COMPONENT16_OES preserveBackbuffer:NO];	
	[window addSubview:iPhoneGlobals.glView];
	
	// release iPhoneGlobals.glView (window still has retain on it)
	[iPhoneGlobals.glView release];
	
	// save reference to the delegate
	iPhoneGlobals.appDelegate = self;
	
	// start timer
	[self setFrameRate:60];
	
	//----- DAMIAN
	// set data path root for ofToDataPath()
	// path on iPhone will be ~/Applications/{application GUID}/openFrameworks.app/data
	// get the resource path for the bundle (ie '~/Applications/{application GUID}/openFrameworks.app')
	NSString *bundle_path_ns = [[NSBundle mainBundle] resourcePath];
	// convert to UTF8 STL string
	string path = [bundle_path_ns UTF8String];
	// append data
	//path.append( "/data/" ); // ZACH
	path.append( "/" ); // ZACH
	printf("setting data path root to '%s'\n", path.c_str() );
	ofSetDataPathRoot( path );
	//-----
	
	// call testApp::setup()
	iPhoneGlobals.baseApp->setup();

	// show or hide status bar depending on OF_WINDOW or OF_FULLSCREEN
	[[UIApplication sharedApplication] setStatusBarHidden:(iPhoneGlobals.iPhoneOFWindow->windowMode == OF_FULLSCREEN) animated:YES];
	[[UIApplication sharedApplication] setStatusBarOrientation: UIInterfaceOrientationLandscapeRight animated:NO];
	
	
	// clear background
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


-(void) setFrameRate:(float)frameRate {
//	NSLog(@"setFrameRate %.3f", frameRate);
	[timer invalidate];
	timer = [NSTimer scheduledTimerWithTimeInterval:(1.0f / frameRate) target:self selector:@selector(timerLoop) userInfo:nil repeats:YES];
}



-(void) dealloc {
    [window release];
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
}


-(void) applicationDidReceiveMemoryWarning:(UIApplication *)application {
	// add callback for this
}


@end
