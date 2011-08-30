//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ConditionVariableNode.h"

#import "Brain.h"
#import "Perception.h"

@implementation ConditionVariableNode


- (id) initWithVariableAndValueAndOperatorAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent
{
    
    if (self == [super initWithKeyAndValueAndBrainAndParent: aKey value:aValue operator:aOperator brain:aBrain parent:aParent])
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
    if ([self isTrue]) {
        [aVariables setObject:_value forKey:@"[Perception.value]"];
        [self execChildren];
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


- (BOOL) isTrue
{
    return FALSE;
}


- (BOOL) isTrue:(NSMutableDictionary*)aVariables
{
    NSEnumerator* eVariables = [aVariables objectEnumerator];
    
    MemoryEvent* objectVariable;
    while (objectVariable = [eVariables nextObject]) {
        
        
        NSString* k = [NSString stringWithFormat:@"%@", [objectVariable event]];
        NSString* v = [NSString stringWithFormat:@"%@", [objectVariable value]];

        // Test if found the variable
        if (![_key caseInsensitiveCompare:k]) {
            
            // Try to convert the value from the variable to number
            float value = [v floatValue];
            BOOL ok = ([[NSScanner scannerWithString:v] scanFloat:NULL]) ? TRUE : FALSE;
            
            // if both values are numbers
            if (ok && _isValueNumeric) {
                
                switch( (int)_operator )
                {
                    case ConditionOperatorBigger: return _valueNumeric > value;
                    case ConditionOperatorBiggerOrEqual: return _valueNumeric >= value;
                    case ConditionOperatorSmaller: return _valueNumeric < value;
                    case ConditionOperatorSmallerOrEqual: return _valueNumeric <= value;
                    case ConditionOperatorEqual: return _valueNumeric == value;
                    case ConditionOperatorDifferent: return _valueNumeric != value;
                }
                return false;
                
            }
        
            else // If one of the value is not a number
            {
                switch( (int)_operator ) // it's a string, just to this 2 operators
                {
                    case ConditionOperatorEqual: return ![_value caseInsensitiveCompare:v];
                    case ConditionOperatorDifferent: return [_value caseInsensitiveCompare:v];
                }
                return false;
            }
        }
    }
    
    // No equal variables found
    return false;
}

@end
