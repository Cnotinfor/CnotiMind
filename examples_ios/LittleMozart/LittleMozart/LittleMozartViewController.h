//
//  LittleMozartViewController.h
//  LittleMozart
//
//  Created by Gonçalo Rodrigues on 10/10/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Brain.h"
#import "Perception.h"
#import "Action.h"
#import "Emotion.h"

#import "ConditionPerceptionNode.h"
#import "RuleNode.h"


@interface LittleMozartViewController : UIViewController {
    UIButton *btnNoteDo;
    UIButton *btnNoteRe;
    UIButton *btnNoteMi;
    UIButton *btnNoteFa;
    UIButton *btnNoteSol;
    UIButton *btnNoteLa;
    UIButton *btnNoteSi;
    UIButton *btnNoteDo2;
    UIButton *btnNotePause;
    UIButton *btnDuration01;
    UIButton *btnDuration02;
    UIButton *btnDuration03;
    UIButton *btnDuration04;
    
    
    Brain* _brain;
}

@property (nonatomic, retain) IBOutlet UIButton *btnNoteDo;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteRe;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteMi;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteFa;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteSol;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteLa;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteSi;
@property (nonatomic, retain) IBOutlet UIButton *btnNoteDo2;
@property (nonatomic, retain) IBOutlet UIButton *btnNotePause;

@property (nonatomic, retain) IBOutlet UIButton *btnDuration01;
@property (nonatomic, retain) IBOutlet UIButton *btnDuration02;
@property (nonatomic, retain) IBOutlet UIButton *btnDuration03;
@property (nonatomic, retain) IBOutlet UIButton *btnDuration04;
@property (retain, nonatomic) IBOutlet UIButton *btnDurationCancel;


@property (retain, nonatomic) IBOutlet UIButton *btnMelodyStartNew;
@property (retain, nonatomic) IBOutlet UIButton *btnMelodyDeleteLastNote;
@property (retain, nonatomic) IBOutlet UIButton *btnMelodyFinish;


@property (retain, nonatomic) IBOutlet UITextView *emotionsUITextView;
@property (retain, nonatomic) IBOutlet UITextView *actionsUITextView;

- (IBAction)btnNoteDoTouch:(id)sender;
- (IBAction)btnNoteReTouch:(id)sender;
- (IBAction)btnNoteMiTouch:(id)sender;
- (IBAction)btnNoteFaTouch:(id)sender;
- (IBAction)btnNoteSolTouch:(id)sender;
- (IBAction)btnNoteLaTouch:(id)sender;
- (IBAction)btnNoteSiTouch:(id)sender;
- (IBAction)btnNoteDo2Touch:(id)sender;
- (IBAction)btnNotePauseTouch:(id)sender;

- (IBAction)btnDuration01:(id)sender;
- (IBAction)btnDuration02:(id)sender;
- (IBAction)btnDuration03:(id)sender;
- (IBAction)btnDuration04:(id)sender;
- (IBAction)btnDurationCancel:(id)sender;

- (IBAction)btnMelodyStartNew:(id)sender;
- (IBAction)btnMelodyDeleteLastNote:(id)sender;
- (IBAction)btnMelodyFinish:(id)sender;

- (void)actionReceived:(NSNotification*)aNotif;
- (void)emotionReceived:(NSNotification*)aNotif;

@end
