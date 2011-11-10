//
//  ConditionEmotionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CnotiMind.h"

#import "RuleNode.h"
#import "Emotion.h"

@class Brain;


@interface EmotionNode : RuleNode {
    
    NSString* _emotion;
    NSString* _value;
    
    double _min;
    double _max;
    
    double _valueNumeric;
    BOOL _valueNumericOk;
}

- (id) initWithEmotionAndValueAndAndBrainAndParent:(NSString*)aEmotion
                                             value:(NSString*)aValue 
                                             brain:(Brain*)aBrain 
                                            parent:(id)aParent;

- (id) initWithEmotionAndValueAndMaxAndMinAndBrainAndParent:(NSString*)aEmotion 
                                                      value:(NSString*)aValue 
                                                        max:(double)aMax
                                                        min:(double)aMin
                                                      brain:(Brain*)aBrain 
                                                     parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

@end
