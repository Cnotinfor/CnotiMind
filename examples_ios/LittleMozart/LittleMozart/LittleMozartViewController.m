//
//  LittleMozartViewController.m
//  LittleMozart
//
//  Created by Gonçalo Rodrigues on 10/10/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "LittleMozartViewController.h"

@implementation LittleMozartViewController
@synthesize actionsUITextView;
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
@synthesize btnDurationCancel;
@synthesize btnMelodyStartNew;
@synthesize btnMelodyDeleteLastNote;
@synthesize btnMelodyFinish;
@synthesize emotionsUITextView;

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    _brain = [[Brain alloc] init];
    self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"whitey.png"]];
        
    //  load XML rulles;
    DLog(@"--- load XML rulles ---");

    NSString* XMLFile = [NSString stringWithString:@""];
    XMLFile = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"mozart_rules.xml"];	
    
    [_brain loadXmlRules:XMLFile];
    [_brain printRules];
    
    NSString* XMLFileSettings = [NSString stringWithString:@""];
    XMLFileSettings = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"mozart_mind.xml"];	
    
    [_brain loadXmlSettings:XMLFileSettings];
    [_brain printSettings];
    
    
    DLog(@"--- start brain ---");
    [_brain startThreadRun];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(actionReceived:) 
                                                 name:SEND_ACTION
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(emotionReceived:) 
                                                 name:SEND_EMOTIONAL_STATE
                                               object:nil];
    
    [super viewDidLoad];
}


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
    [self setActionsUITextView:nil];
    [self setEmotionsUITextView:nil];
    [self setBtnDurationCancel:nil];
    [self setBtnMelodyStartNew:nil];
    [self setBtnMelodyDeleteLastNote:nil];
    [self setBtnMelodyFinish:nil];
    [self setBtnMelodyDeleteLastNote:nil];
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
    [actionsUITextView release];
    [emotionsUITextView release];
    [btnDurationCancel release];
    [btnMelodyStartNew release];
    [btnMelodyDeleteLastNote release];
    [btnMelodyFinish release];
    [btnMelodyDeleteLastNote release];
    [super dealloc];
}

- (NSString*)selectedNoteButton {
    
    if ([btnNoteDo isSelected]) {
        return [NSString stringWithString:@"Do"];
    }
    else if ([btnNoteRe isSelected]) {
        return [NSString stringWithString:@"Re"];
    }
    else if ([btnNoteMi isSelected]) {
        return [NSString stringWithString:@"Mi"];
    }
    else if ([btnNoteFa isSelected]) {
        return [NSString stringWithString:@"Fa"];
    }
    else if ([btnNoteSol isSelected]) {
        return [NSString stringWithString:@"Sol"];
    }
    else if ([btnNoteLa isSelected]) {
        return [NSString stringWithString:@"La"];
    }
    else if ([btnNoteSi isSelected]) {
        return [NSString stringWithString:@"Si"];
    }
    else if ([btnNoteDo2 isSelected]) {
        return [NSString stringWithString:@"DoAgudo"];
    }
    else if ([btnNotePause isSelected]) {
        return [NSString stringWithString:@"Pause"];
    }
    else {
        return nil;
    }
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
    
    Perception* perceptionDo = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Do"];
    [_brain receivePerception:perceptionDo];
    
}

- (IBAction)btnNoteReTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteRe setSelected:TRUE];
    [btnNoteRe setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionRe = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Re"];
    [_brain receivePerception:perceptionRe];
}

- (IBAction)btnNoteMiTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteMi setSelected:TRUE];
    [btnNoteMi setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionMi = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Mi"];
    [_brain receivePerception:perceptionMi];
}

- (IBAction)btnNoteFaTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteFa setSelected:TRUE];
    [btnNoteFa setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionFa = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Fa"];
    [_brain receivePerception:perceptionFa];
}

- (IBAction)btnNoteSolTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteSol setSelected:TRUE];
    [btnNoteSol setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionSol = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Sol"];
    [_brain receivePerception:perceptionSol];
}

- (IBAction)btnNoteLaTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteLa setSelected:TRUE];
    [btnNoteLa setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionLa = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"La"];
    [_brain receivePerception:perceptionLa];
}

- (IBAction)btnNoteSiTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteSi setSelected:TRUE];
    [btnNoteSi setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionSi = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Si"];
    [_brain receivePerception:perceptionSi];
}

- (IBAction)btnNoteDo2Touch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNoteDo2 setSelected:TRUE];
    [btnNoteDo2 setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionDo2 = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"DoAgudo"];
    [_brain receivePerception:perceptionDo2];
}

- (IBAction)btnNotePauseTouch:(id)sender {
    [self unselectAllNoteButtons];
    [btnNotePause setSelected:TRUE];
    [btnNotePause setBackgroundColor:[UIColor blueColor]];
    
    Perception* perceptionPause = [[Perception alloc] initWithNameAndAValue:@"Note" value:@"Pause"];
    [_brain receivePerception:perceptionPause];
}

- (IBAction)btnDuration01:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Duration" value:@"1"];
    [_brain receivePerception:perceptionDuration];
}

- (IBAction)btnDuration02:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Duration" value:@"2"];
    [_brain receivePerception:perceptionDuration];

}

- (IBAction)btnDuration03:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Duration" value:@"3"];
    [_brain receivePerception:perceptionDuration];

}

- (IBAction)btnDuration04:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Duration" value:@"4"];
    [_brain receivePerception:perceptionDuration];

}

- (IBAction)btnDurationCancel:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Delete Note" value:@""];
    [_brain receivePerception:perceptionDuration];
    
    [self unselectAllNoteButtons];
}

- (IBAction)btnMelodyStartNew:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Start Melody" value:@""];
    [_brain receivePerception:perceptionDuration];
}

- (IBAction)btnMelodyDeleteLastNote:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Delete Note" value:@""];
    [_brain receivePerception:perceptionDuration];
    Perception* perceptionDuration2 = [[Perception alloc] initWithNameAndAValue:@"Delete Duration" value:@""];
    [_brain receivePerception:perceptionDuration2];
}

- (IBAction)btnMelodyFinish:(id)sender {
    Perception* perceptionDuration = [[Perception alloc] initWithNameAndAValue:@"Finish Melody" value:@""];
    [_brain receivePerception:perceptionDuration];
}

- (void)actionReceived:(NSNotification*)aNotif
{
    DLog(@"actionReceived: %@", aNotif);
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSString* receivedOld = actionsUITextView.text;
        
        NSMutableString* received = [[NSMutableString alloc] init];
        received = [NSMutableString stringWithString:[[aNotif object] description]];
        
        [received replaceOccurrencesOfString:@"{" withString:@"" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [received length])];
        [received replaceOccurrencesOfString:@"}" withString:@"" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [received length])];
        
        NSString* received2 = [NSString stringWithString:received];
        received2 = [received2 stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        received2 = [received2 stringByAppendingString:@"\n"];

        NSString* newReceived = [NSString stringWithFormat:@"%@%@", receivedOld, received];
        
        [actionsUITextView setText:newReceived];

        NSRange range = NSMakeRange(actionsUITextView.text.length - 1, 1);
        [actionsUITextView scrollRangeToVisible:range];
    });
}


- (void)emotionReceived:(NSNotification*)aNotif
{
    DLog(@"emotionReceived: %@", aNotif);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSString* receivedOld = emotionsUITextView.text;
        
        NSMutableString* received = [[NSMutableString alloc] init];
        received = (NSMutableString*)[[aNotif object] description];
        
        [received replaceOccurrencesOfString:@"{" withString:@"" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [received length])];
        [received replaceOccurrencesOfString:@"}" withString:@"" options:NSCaseInsensitiveSearch range:NSMakeRange(0, [received length])];                

        NSString* received2 = [NSString stringWithString:received];
        received2 = [received2 stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        received2 = [received2 stringByAppendingString:@"\n"];
        
        NSString* newReceived = [NSString stringWithFormat:@"%@%@", receivedOld, received];
        
        [emotionsUITextView setText:newReceived];
        
        NSRange range = NSMakeRange(emotionsUITextView.text.length - 1, 1);
        [emotionsUITextView scrollRangeToVisible:range];
    });}

@end
