//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ConditionEmotionNode.h"

#import "Brain.h"

@implementation ConditionEmotionNode


- (id) initWithEmotionAndValueAndOperatorAndBrainAndParent: (NSString*)aEmotion 
                                                     value:(NSString*)aValue 
                                                  operator:(enum ConditionOperator)aOperator 
                                                     brain:(Brain*)aBrain 
                                                    parent:(id)aParent
{
    if (self == [super initWithKeyAndValueAndBrainAndParent: aEmotion value:aValue operator:aOperator brain:aBrain parent:aParent])
    {
    }
    return self;
}


- (void) exec
{
    if ([self isTrue]) {
        NSMutableDictionary* variables = [[NSMutableDictionary alloc] init];
        [variables setObject:_value forKey:@"[Emotion.value]"];
        
        //  TODO
        [self execChildren:variables];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if ([self isTrue]) {
        [aVariables setObject:_value forKey:@"[Emotion.value]"];
        [self execChildren];
    }

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=Emotion", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (BOOL) isTrue
{
    
    // If the brain doesn't have emotions
    if( [_brain.emotions count] == 0)
    {
        return false;
    }
    
    // search the emotion
    NSEnumerator* eEmotions = [_brain.emotions objectEnumerator];
    Emotion* objectEmotion;
    while (objectEmotion = [eEmotions nextObject]) {
        if (![[objectEmotion name] caseInsensitiveCompare: _key]) {
            return [self testEmotion:objectEmotion];
        }
    }
    
    return true;
}


- (BOOL) testEmotion:(Emotion*)aEmotion
{
    if( _isValueNumeric )
    {
        switch( (int)_operator )
        {
            case ConditionOperatorBigger: return [aEmotion value] > _valueNumeric;
            case ConditionOperatorBiggerOrEqual: return [aEmotion value] >= _valueNumeric;
            case ConditionOperatorSmaller: return [aEmotion value] < _valueNumeric;
            case ConditionOperatorSmallerOrEqual: return [aEmotion value] <= _valueNumeric;
            case ConditionOperatorEqual: return [aEmotion value] == _valueNumeric;
            case ConditionOperatorDifferent: return [aEmotion value] != _valueNumeric;
        }
    }
    // if the operator is invalid or the value is not numeric
    return false;
}

@end
