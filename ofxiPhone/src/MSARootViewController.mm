//
//  MSARootViewController.m
//  Meshmerizer
//
//  Created by Mehmet Akten on 18/02/2009.
//  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
//

#import "MSARootViewController.h"
#import "ofxiPhone.h"

@implementation MSARootViewController



-(void) saveButtonReset {
	[saveButton setTitle:@"Save to Photos"];	
}


-(BOOL) isOn {
	return _isOn;
}

int numPages = 0;
CGRect scrollFrame;

-(void)addPage:(UIView*)view {
	scrollFrame.origin.x = scrollFrame.size.width * numPages++;
	view.frame = scrollFrame;
	view.backgroundColor = [UIColor clearColor];
	[scrollView addSubview:view];	
}

-(void)updatePages {
	pageControl.numberOfPages = numPages;
	pageControl.currentPage = 0;
    scrollView.contentSize = CGSizeMake(scrollFrame.size.width * numPages, scrollFrame.size.height);
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	NSLog(@"MSARootViewController::viewDidLoad");
	
    [super viewDidLoad];
	
	window = [[UIApplication sharedApplication] keyWindow];
	
	scrollFrame = scrollView.frame;
    scrollView.contentSize = CGSizeMake(scrollFrame.size.width * 3, scrollFrame.size.height);
	scrollView.delegate = self;
	scrollFrame.origin.y = 0;
	
	[self addPage:infoView];
//	[self addPage:optionsView1];
//	[self addPage:optionsView2];
}




- (void)scrollViewDidScroll:(UIScrollView *)sender {
    if(pageControlUsed) return;
	
    // Switch the indicator when more than 50% of the previous/next page is visible
    CGFloat pageWidth = scrollView.frame.size.width;
    int page = floor((scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
	pageControl.currentPage = page;
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    pageControlUsed = NO;
}

- (IBAction)pageChanged:(id)sender {
    int page = pageControl.currentPage;
    CGRect frame = scrollView.frame;
    frame.origin.x = frame.size.width * page;
    frame.origin.y = 0;
    [scrollView scrollRectToVisible:frame animated:YES];
    pageControlUsed = YES;
}



// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}




#define ANIMATION_TIME		0.5f
#define ANIMATION_CURVE		UIViewAnimationCurveEaseIn


-(IBAction) openView {
	if(self.view.superview == nil) {
		[self saveButtonReset];
		
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:ANIMATION_TIME];
		[UIView setAnimationTransition:UIViewAnimationTransitionCurlDown forView:window cache:YES];
		[UIView setAnimationCurve: ANIMATION_CURVE];
		[self viewWillAppear:YES];
		[window addSubview:self.view];
		[self viewDidAppear:YES];
		[UIView commitAnimations];
		
		activityIndicator.hidesWhenStopped = YES;
		[activityIndicator stopAnimating];
	}
	
	_isOn = true;
}

-(IBAction) closeView:(id)sender {
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:ANIMATION_TIME];
	[UIView setAnimationTransition:UIViewAnimationTransitionCurlUp forView:window cache:YES];
	//		[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:window cache:YES];
	[UIView setAnimationCurve: ANIMATION_CURVE];
	[self viewWillDisappear:YES];
	[self.view removeFromSuperview];
	[self viewDidDisappear:YES];
	[UIView commitAnimations];
	
	_isOn = false;
}


-(IBAction) savePhoto:(id)sender {
	[saveButton setTitle:@"Saving..."];
	[activityIndicator startAnimating];
	
	iPhoneScreenGrab(self);
}


-(void)saveComplete {
	UIActionSheet *alert = [[UIActionSheet alloc] initWithTitle:@"Image saved to Photos application" delegate:self cancelButtonTitle:@"Ok" destructiveButtonTitle:nil otherButtonTitles:nil];
//	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Save complete" message:@"Image saved to Photos application" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil];
	
	UIImage *iconImage = [[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"PhotoAppIcon" ofType:@"png"]];
	UIImageView *iconView = [[UIImageView alloc] initWithImage:iconImage];
	
	[alert addSubview:iconView];
	iconView.frame = CGRectMake(90, 6, 32, 32);
//	iconView.frame = CGRectMake(13, 10, 32, 32);
	
	[alert showInView:self.view];
//	[alert show];
	
	[alert release];
	[iconImage release];
	[iconView release];
	
	[activityIndicator stopAnimating];
	[self saveButtonReset];
}


-(void)alertView:(UIAlertView*)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
	[self closeView:nil];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}




- (void)dealloc {
    [super dealloc];
}


@end
