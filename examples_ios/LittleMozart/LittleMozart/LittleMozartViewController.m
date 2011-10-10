//
//  LittleMozartViewController.m
//  LittleMozart
//
//  Created by Gonçalo Rodrigues on 10/10/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "LittleMozartViewController.h"

@implementation LittleMozartViewController
@synthesize btnNoteDo;
@synthesize btnNoteRe;
@synthesize btnNoteMi;
@synthesize btnNoteFa;
@synthesize btnNoteSol;
@synthesize btnNoteLa;
@synthesize btnNoteSi;
@synthesize btnNoteDo2;
@synthesize btnNotePause;
@synthesize btnDuration01;
@synthesize btnDuration02;
@synthesize btnDuration03;
@synthesize btnDuration04;

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
}
*/

- (void)viewDidUnload
{
    [self setBtnNoteDo:nil];
    [self setBtnNoteRe:nil];
    [self setBtnNoteMi:nil];
    [self setBtnNoteFa:nil];
    [self setBtnNoteSol:nil];
    [self setBtnNoteLa:nil];
    [self setBtnNoteSi:nil];
    [self setBtnNoteDo2:nil];
    [self setBtnNotePause:nil];
    [self setBtnDuration01:nil];
    [self setBtnDuration02:nil];
    [self setBtnDuration03:nil];
    [self setBtnDuration04:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {
    [btnNoteDo release];
    [btnNoteRe release];
    [btnNoteMi release];
    [btnNoteFa release];
    [btnNoteSol release];
    [btnNoteLa release];
    [btnNoteSi release];
    [btnNoteDo2 release];
    [btnNotePause release];
    [btnDuration01 release];
    [btnDuration02 release];
    [btnDuration03 release];
    [btnDuration04 release];
    [super dealloc];
}

- (void)unselectAllNoteButtons {
    
    [btnNoteDo setSelected:FALSE];
    [btnNoteRe setSelected:FALSE];
    [btnNoteMi setSelected:FALSE];
    [btnNoteFa setSelected:FALSE];
    [btnNoteSol setSelected:FALSE];
    [btnNoteLa setSelected:FALSE];
    [btnNoteSi setSelected:FALSE];
    [btnNoteDo2 setSelected:FALSE];
    [btnNotePause setSelected:FALSE];
    
    [btnNoteDo setBackgroundColor:[UIColor clearColor]];
    [btnNoteRe setBackgroundColor:[UIColor clearColor]];
    [btnNoteMi setBackgroundColor:[UIColor clearColor]];
    [btnNoteFa setBackgroundColor:[UIColor clearColor]];
    [btnNoteSol setBackgroundColor:[UIColor clearColor]];
    [btnNoteLa setBackgroundColor:[UIColor clearColor]];
    [btnNoteSi setBackgroundColor:[UIColor clearColor]];
    [btnNoteDo2 setBackgroundColor:[UIColor clearColor]];
    [btnNotePause setBackgroundColor:[UIColor clearColor]];

}

- (IBAction)btnNoteDoTouch:(id)sender {
    
    [self unselectAllNoteButtons];
    [btnNoteDo setSelected:TRUE];
    [btnNoteDo setBackgroundColor:[UIColor blueColor]];
    
}

- (IBAction)btnNotereTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteRe setSelected:TRUE];
    [btnNoteRe setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteMiTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteMi setSelected:TRUE];
    [btnNoteMi setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteFaTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteFa setSelected:TRUE];
    [btnNoteFa setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteSolTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteSol setSelected:TRUE];
    [btnNoteSol setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteLaTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteLa setSelected:TRUE];
    [btnNoteLa setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteSiTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteSi setSelected:TRUE];
    [btnNoteSi setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNoteDo2Touch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteDo2 setSelected:TRUE];
    [btnNoteDo2 setBackgroundColor:[UIColor blueColor]];
}

- (IBAction)btnNotePauseTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNotePause setSelected:TRUE];
    [btnNotePause setBackgroundColor:[UIColor blueColor]];
}

@end
