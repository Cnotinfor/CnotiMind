//
//  SingleEmotionAppDelegate.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 11/05/16.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Brain.h"
#import "Perception.h"
#import "Action.h"
#import "Emotion.h"

#import "ConditionPerceptionNode.h"
#import "RuleNode.h"


@interface SingleEmotionAppDelegate : NSObject <UIApplicationDelegate> {
    Brain* _brain;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

- (IBAction) onClickButtonHello;

- (void) actionReceived:(NSNotification*)aNotif;
- (void) emotionReceived:(NSString*)aEmotion number:(NSNumber*)aValue;

@end
