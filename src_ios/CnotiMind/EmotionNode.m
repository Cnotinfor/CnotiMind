//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "EmotionNode.h"

#import "Brain.h"
#import "Perception.h"

@implementation EmotionNode

- (id) initWithEmotionAndValueAndAndBrainAndParent:(NSString*)aEmotion 
                                             value:(NSString*)aValue 
                                             brain:(Brain*)aBrain 
                                            parent:(id)aParent
{
    if ( self == [super initWithBrainAndParent:aBrain parent:aParent] ) {
    
        _emotion = aEmotion;
        _value = aValue;
        _min = INT_MIN;
        _max = INT_MAX;
        _valueNumericOk = TRUE;
        _valueNumeric = [aValue floatValue];
    }
    
    return self;
}

- (id) initWithEmotionAndValueAndAndBrainAndParent:(NSString*)aEmotion 
                                             value:(NSString*)aValue 
                                               max:(double)aMax
                                               min:(double)aMin
                                             brain:(Brain*)aBrain 
                                            parent:(id)aParent
{
    if ( self == [super initWithBrainAndParent:aBrain parent:aParent] ) {        
        _emotion = aEmotion;
        _value = aValue;

        _min = aMin;
        _max = aMax;
        _valueNumericOk = TRUE;        
        _valueNumeric = [aValue floatValue];
    }
    
    return self;
}


- (void) exec
{
    // Test if the value is valid
    if(!_valueNumericOk) // it is not a number, it could be a variable, but there are no variables
    {
        return; // it doesn't do nothing
    }
    
    // TODO
    [_brain updateEmotionValue:_emotion variation:_valueNumeric max:_max min:_min];
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if (!_valueNumericOk) {

        NSString* value = [self variableToValue:_value variables:aVariables];
        
        // Test if the value from the variable is a valid number
        BOOL ok = ([[NSScanner scannerWithString:value] scanFloat:NULL]) ? TRUE : FALSE;
        double newValueInt = [value floatValue];
        
        
        if( !ok )
        {
            return;// Not valid, it doesn't do nothing
        }
        
        // Update the numeric value
        _valueNumeric = newValueInt;
    }
    
    [_brain updateEmotionValue:_emotion variation:_valueNumeric max:_max min:_min];
}

- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ DataMining", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

@end
