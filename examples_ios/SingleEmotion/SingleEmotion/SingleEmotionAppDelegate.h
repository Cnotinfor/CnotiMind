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

    IBOutlet UILabel* labelHelloField;

    Brain* _brain;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

- (IBAction) onClickButtonHello;

- (void) actionReceived;
//- (void) actionReceived:(NSString*)aKey value:(NSString*)aValue;
- (void) emotionReceived:(NSString*)aEmotion number:(NSNumber*)aValue;

@end
