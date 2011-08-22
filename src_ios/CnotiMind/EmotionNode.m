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
    
        _emotion = [[NSString alloc] initWithString:aEmotion];
        _value = [[NSString alloc] initWithString:aValue];
        _min = INT_MIN;
        _max = INT_MAX;
        _valueNumericOk = TRUE;
        _valueNumeric = [aValue floatValue];
    }
    
    return self;
}

- (id) initWithEmotionAndValueAndMaxAndMinAndBrainAndParent:(NSString*)aEmotion 
                                                      value:(NSString*)aValue 
                                                        max:(double)aMax
                                                        min:(double)aMin
                                                      brain:(Brain*)aBrain 
                                                     parent:(id)aParent
{
    if ( self == [super initWithBrainAndParent:aBrain parent:aParent] ) {        

        DLog(@"->%@", aEmotion);
        DLog(@"->%@", aValue);        
        _emotion = [[NSString alloc] initWithString:aEmotion];
        _value = [[NSString alloc] initWithString:aValue];
        
        DLog(@"->%@", _emotion);
        DLog(@"->%@", _value);
        
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
//    NSString* space = [self space:aDepth];
//    DLog(@"---");
//    DLog(@"- %@ -", space);
//    DLog(@"- %@ -", _emotion);
//    DLog(@"- %@ -", _value);
//    info = [info stringByAppendingFormat:@"%@ Emotion (%@) increment=%@", space, _emotion, _value];
    
    if (_min != INT_MIN) {
        [info stringByAppendingFormat:@" min= %@", _min ];
    }
    if (_max != INT_MAX) {
        [info stringByAppendingFormat:@" max= %@", _max ];
    }
    
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

@end
