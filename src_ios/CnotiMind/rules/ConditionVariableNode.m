//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "ConditionVariableNode.h"

#import "Brain.h"
#import "Perception.h"

@implementation ConditionVariableNode


- (id) initWithVariableAndValueAndOperatorAndBrainAndParent: (NSString*)aKey 
                                                      value:(NSString*)aValue 
                                                   operator: (enum ConditionOperator)aOperator 
                                                      brain:(Brain*)aBrain 
                                                     parent:(id)aParent
{
    
    if (self == [super initWithKeyAndValueAndBrainAndParent: aKey 
                                                      value:aValue 
                                                   operator:aOperator 
                                                      brain:aBrain 
                                                     parent:aParent])
    {
    }
    return self;
}


- (void) exec
{
    // Does nothing, since this Node, need variables to exec
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if ([self isTrue:aVariables]) {
        [aVariables setObject:_value forKey:@"[perception.value]"];
        [self execChildren:aVariables];
    }

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=Variable", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

/*
 Returns false, since it requires variables to work correctly
 */
- (BOOL) isTrue
{
    return FALSE;
}


- (BOOL) isTrue:(NSMutableDictionary*)aVariables
{
    NSEnumerator* eVariables = [aVariables keyEnumerator];
    
    for (NSString* aKey in eVariables) {
        
        NSString* k = [NSString stringWithFormat:@"%@", aKey];
        NSString* v = [NSString stringWithFormat:@"%@", [aVariables objectForKey:aKey]];

        // Test if found the variable
        if (![_key caseInsensitiveCompare:k]) {
            
            // Try to convert the value from the variable to number
            float value = [v floatValue];
//            BOOL ok = ([[NSScanner scannerWithString:v] scanFloat:NULL]) ? TRUE : FALSE;
            
            // if both values are numbers
            if ([self isNumeric:v]) {
                if (_isValueNumeric) { // if the value to compare is a number
                    
                    switch( (int)_operator )
                    {
                        case ConditionOperatorBigger: return  value > _valueNumeric;
                        case ConditionOperatorBiggerOrEqual: return value >= _valueNumeric;
                        case ConditionOperatorSmaller: return value < _valueNumeric;
                        case ConditionOperatorSmallerOrEqual: return value <= _valueNumeric;
                        case ConditionOperatorEqual: return value == _valueNumeric;
                        case ConditionOperatorDifferent: return value != _valueNumeric;
                    }
                    return false;    
                }
                
                else { // if it is not a number, test if it is variable
                
                    NSString* strValue = [NSString stringWithFormat:@"%@", _value];
                    [self tagsToValue:&strValue variables:&aVariables];
                    
                    if ([self isNumeric:strValue]) {
                        float compareValue = [strValue floatValue];

                        switch( (int)_operator )
                        {
                            case ConditionOperatorBigger: return value > compareValue;
                            case ConditionOperatorBiggerOrEqual: return value >= compareValue;
                            case ConditionOperatorSmaller: return value < compareValue;
                            case ConditionOperatorSmallerOrEqual: return value <= compareValue;
                            case ConditionOperatorEqual: return value == compareValue;
                            case ConditionOperatorDifferent: return value != compareValue;
                        }
                        return false;
                    }
                }           
            }
        
            else // If one of the value is not a number
            {
                NSString* strValue = [NSString stringWithFormat:@"%@", _value];
                [self tagsToValue:&strValue variables:&aVariables];                
                
                switch( (int)_operator ) // it's a string, just to this 2 operators
                {
                    case ConditionOperatorEqual: return ![strValue caseInsensitiveCompare:v];
                    case ConditionOperatorDifferent: return [strValue caseInsensitiveCompare:v];
                }
                return false;
            }
        }
    }
    
    // No equal variables found
    return false;
}

@end