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


#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "EAGLView.h"

#include "ofxMultiTouch.h"
#include "ofMain.h"


//CLASS IMPLEMENTATIONS:

@implementation EAGLView

@synthesize surfaceSize=_size, framebuffer = _framebuffer, pixelFormat = _format, depthFormat = _depthFormat, context = _context;

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (BOOL) _createSurface
{
	CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
	CGSize					newSize;
	GLuint					oldRenderbuffer;
	GLuint					oldFramebuffer;
	
	if(![EAGLContext setCurrentContext:_context]) {
		return NO;
	}
	
	newSize = [eaglLayer bounds].size;
	newSize.width = roundf(newSize.width);
	newSize.height = roundf(newSize.height);
	
	glGetIntegerv(GL_RENDERBUFFER_BINDING_OES, (GLint *) &oldRenderbuffer);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, (GLint *) &oldFramebuffer);
	
	glGenRenderbuffersOES(1, &_renderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _renderbuffer);
	
	if(![_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(id<EAGLDrawable>)eaglLayer]) {
		glDeleteRenderbuffersOES(1, &_renderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_BINDING_OES, oldRenderbuffer);
		return NO;
	}
	
	glGenFramebuffersOES(1, &_framebuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, _framebuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, _renderbuffer);
	if (_depthFormat) {
		glGenRenderbuffersOES(1, &_depthBuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, _depthBuffer);
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES, _depthFormat, newSize.width, newSize.height);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, _depthBuffer);
	}

	_size = newSize;
	if(!_hasBeenCurrent) {
		glViewport(0, 0, newSize.width, newSize.height);
		glScissor(0, 0, newSize.width, newSize.height);
		_hasBeenCurrent = YES;
	}
	else {
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, oldFramebuffer);
	}
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, oldRenderbuffer);
	
	return YES;
}

- (void) _destroySurface
{
	EAGLContext *oldContext = [EAGLContext currentContext];
	
	if (oldContext != _context)
		[EAGLContext setCurrentContext:_context];
	
	if(_depthFormat) {
		glDeleteRenderbuffersOES(1, &_depthBuffer);
		_depthBuffer = 0;
	}
	
	glDeleteRenderbuffersOES(1, &_renderbuffer);
	_renderbuffer = 0;

	glDeleteFramebuffersOES(1, &_framebuffer);
	_framebuffer = 0;
	
	if (oldContext != _context)
		[EAGLContext setCurrentContext:oldContext];
}

- (id) initWithFrame:(CGRect)frame
{
	return [self initWithFrame:frame pixelFormat:GL_RGB565_OES depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format 
{
	return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(GLuint)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained
{
	if((self = [super initWithFrame:frame])) {
		CAEAGLLayer*			eaglLayer = (CAEAGLLayer*)[self layer];
		
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
										[NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		_format = format;
		_depthFormat = depth;
		
		_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		if(_context == nil) {
			[self release];
			return nil;
		}
		
		if(![self _createSurface]) {
			[self release];
			return nil;
		}
		
		self.multipleTouchEnabled = true;
	}

	return self;
}

- (void) swapBuffers
{
	EAGLContext *oldContext = [EAGLContext currentContext];
	GLuint oldRenderbuffer;
	
	if(oldContext != _context)
		[EAGLContext setCurrentContext:_context];
	
	glGetIntegerv(GL_RENDERBUFFER_BINDING_OES, (GLint *) &oldRenderbuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _renderbuffer);
	
	if(![_context presentRenderbuffer:GL_RENDERBUFFER_OES])
		NSLog(@"Failed to swap renderbuffer in %s\n", __FUNCTION__);

	if(oldContext != _context)
		[EAGLContext setCurrentContext:oldContext];
}

- (void) dealloc
{
	[self _destroySurface];
	
	[_context release];
	_context = nil;
	
	[super dealloc];
}


-(void) setApp:(ofBaseApp*)theApp {
	baseApp = theApp;
}


/******************* TOUCH EVENTS ********************/


//------------------------------------------------------
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	
	NSArray *all = [touches allObjects];
	int count = [all count];
	NSAutoreleasePool *pool =  [[NSAutoreleasePool alloc] init];
	for(int i=0; i<count; i++){
		
		// find a new touch
		UITouch *touch = [all objectAtIndex:i];
		if([touch phase] != UITouchPhaseBegan)
			continue;
		
		// place it in an empty space in the array
		int index=0;
		while( index<MAX_TOUCHES && touchesExist[index] )
			index++;
		if(index==MAX_TOUCHES)
			index=0;
		
		touchesExist[index] = true;
		activeTouches[index] = touch;
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( index==0 ){
			baseApp->mouseX = touchPoint.x;
			baseApp->mouseY = touchPoint.y;
			baseApp->mousePressed(touchPoint.x, touchPoint.y, 1);
		}
		
		if([touch tapCount] == 1) ofxMultiTouch.touchDown(touchPoint.x, touchPoint.y, index);
		else {
			ofxMultiTouch.touchDoubleTap(touchPoint.x, touchPoint.y, index);
		}
	}
	[pool release];
}

//------------------------------------------------------
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	
	NSArray *all = [touches allObjects];
	int count = [all count];
	NSAutoreleasePool *pool =  [[NSAutoreleasePool alloc] init];
	for(int i=0; i<count; i++){
		
		// find a moved touch
		UITouch *touch = [all objectAtIndex:i];
		if([touch phase] != UITouchPhaseMoved)
			continue;
		
		// find it in the list!
		int index=0;
		while( index<MAX_TOUCHES && (!touchesExist[index] || activeTouches[index]!=touch) )
			index++;
		if( index==MAX_TOUCHES )
			continue;
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( index==0 ){
			baseApp->mouseX = touchPoint.x;
			baseApp->mouseY = touchPoint.y;
			baseApp->mouseDragged(touchPoint.x, touchPoint.y, 1);
		}
		
		//		baseApp->touchMove(touchPoint.x, touchPoint.y, index);
		ofxMultiTouch.touchMoved(touchPoint.x, touchPoint.y, index);
	}
	[pool release];
}

//------------------------------------------------------
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	NSArray *all = [touches allObjects];
	int count = [all count];
	NSAutoreleasePool *pool =  [[NSAutoreleasePool alloc] init];
	for(int i=0; i<count; i++){
		
		// find a finished touch
		UITouch *touch = [all objectAtIndex:i];
		if([touch phase] != UITouchPhaseEnded)
			continue;
		
		// find it in the list!
		int index=0;
		while( index<MAX_TOUCHES && (!touchesExist[index] || activeTouches[index]!=touch) )
			index++;
		if( index==MAX_TOUCHES )
			continue;
		
		touchesExist[index] = false;
		
		CGPoint touchPoint = [touch locationInView:self];
		
		if( index==0 ){
			baseApp->mouseX = touchPoint.x;
			baseApp->mouseY = touchPoint.y;
			baseApp->mouseReleased(touchPoint.x, touchPoint.y, 1);
			baseApp->mouseReleased();
		}
		
		//		baseApp->touchUp(touchPoint.x, touchPoint.y, index);
		ofxMultiTouch.touchUp(touchPoint.x, touchPoint.y, index);
		
	}
	[pool release];
}

//------------------------------------------------------
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	// end all active touches
	for(int i=0; i<MAX_TOUCHES; i++){
		if(touchesExist[i]){
			touchesExist[i] = false;
			
			UITouch * touch = activeTouches[i];
			
			CGPoint touchPoint = [touch locationInView:self];
			
			if( i==0 ){
				baseApp->mouseX = touchPoint.x;
				baseApp->mouseY = touchPoint.y;
				baseApp->mouseReleased(touchPoint.x, touchPoint.y, 1);
				baseApp->mouseReleased();
			}
		}
	}
}


@end