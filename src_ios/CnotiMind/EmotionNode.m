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



- (id) initWithKeyAndValueAndAndBrainAndParent: (NSString*)aKey 
                                         value:(NSString*)aValue 
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent
{
    if ( self == [super initWithKeyAndValueAndBrainAndParent:aKey value:aValue brain:aBrain parent:aParent] ) {
    
        _min = [NSNumber numberWithInt:INT_MIN];
        _max = [NSNumber numberWithInt:INT_MAX];
        
        _valueNumeric = [NSNumber numberWithFloat:[aValue floatValue]];
    }
    
    return self;
}

- (id) initWithKeyAndValueAndAndBrainAndParent: (NSString*)aKey 
                                         value:(NSString*)aValue 
                                           max:(NSNumber*)aMax
                                           min:(NSNumber*)aMin
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent
{
    if ( self == [super initWithKeyAndValueAndBrainAndParent:aKey value:aValue brain:aBrain parent:aParent] ) {
        
        _min = aMin;
        _max = aMax;
        
        _valueNumeric = [NSNumber numberWithFloat:[aValue floatValue]];
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
    

    [_brain updateEmotionValue:_key variation:_valueNumeric max:_max min:_min];
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if (!_valueNumericOk) {

        NSString* value = [self variableToValue:_value variables:aVariables];
        
        // Test if the value from the variable is a valid number
        BOOL ok = ([[NSScanner scannerWithString:value] scanFloat:NULL]) ? TRUE : FALSE;
        NSNumber* newValueInt = [NSNumber numberWithFloat:[value floatValue]];
        
        
        if( !ok )
        {
            return;// Not valid, it doesn't do nothing
        }
        
        // Update the numeric value
        _valueNumeric = newValueInt;
    }
    
    [_brain updateEmotionValue:_key variation:_valueNumeric max:_max min:_min];
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
