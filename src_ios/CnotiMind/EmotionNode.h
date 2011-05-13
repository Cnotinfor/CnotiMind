//
//  ConditionEmotionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CnotiMind.h"

#import "RuleNode.h"
#import "Emotion.h"

@class Brain;


@interface EmotionNode : RuleNode {
    
    
    NSNumber* _min;
    NSNumber* _max;
    
    NSNumber* _valueNumeric;
    BOOL _valueNumericOk;
}

- (id) initWithKeyAndValueAndAndBrainAndParent: (NSString*)aKey 
                                                value:(NSString*)aValue 
                                                brain:(Brain*)aBrain 
                                                parent:(id)aParent;

- (id) initWithKeyAndValueAndAndBrainAndParent: (NSString*)aKey 
                                         value:(NSString*)aValue 
                                           max:(NSNumber*)aMax
                                           min:(NSNumber*)aMin
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

@end
