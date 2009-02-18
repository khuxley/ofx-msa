//
//  MSARootViewController.h
//  Meshmerizer
//
//  Created by Mehmet Akten on 18/02/2009.
//  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface MSARootViewController : UIViewController <UIActionSheetDelegate, UIScrollViewDelegate> {
	UIView *window;
	
	IBOutlet UIBarButtonItem			*saveButton;
	IBOutlet UIActivityIndicatorView	*activityIndicator;
	
	IBOutlet UIView						*infoView;

	IBOutlet UIScrollView				*scrollView;
	IBOutlet UIPageControl				*pageControl;
	IBOutlet UIViewController			*optionsViewController;
	
	BOOL _isOn;
	BOOL pageControlUsed;
	
}

-(void)addPage:(UIView*)view;

-(void) openView;
-(IBAction) closeView:(id)sender;
-(BOOL) isOn;


-(IBAction) savePhoto:(id)sender;
-(void) saveComplete;
-(IBAction) pageChanged:(id)sender;
-(void) updatePages;

@end
