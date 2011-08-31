//
//  ConditionPropertyNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ConditionPropertyNode.h"

#import "Brain.h"

@implementation ConditionPropertyNode

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (id) initWithPropertyAndValuAndOperatorAndBrainAndParent: (NSString*)aProperty 
                                                     value:(NSString*)aValue
                                                  operator:(enum ConditionOperator)aOperator
                                                     brain:(Brain*)aBrain 
                                                    parent:(id)aParent
{

    if (self = [super initWithKeyAndValueAndBrainAndParent:aProperty value:aValue operator:aOperator brain:aBrain parent:aParent]) {
    }

    return self;
}


- (BOOL) isTrue{

    NSEnumerator* eProperties = [[_brain properties] objectEnumerator];
    
    for (NSString* aKey in eProperties) {
        
        NSString* k = [NSString stringWithFormat:@"%@", aKey];
        NSString* v = [NSString stringWithFormat:@"%@", [[_brain properties] objectForKey:aKey]];
        
        // Test if found the property
        if (![_key caseInsensitiveCompare:k]) {
            // Try to convert the value from the variable to number
            
            BOOL ok;
            float valueNumeric;
            if ([self isNumeric:v]) {
                ok = true;
                valueNumeric = [v floatValue];
            }
            
            if (ok && _isValueNumeric) { // if both values are numbers
                switch( (int)_operator )
                {
                    case ConditionOperatorBigger: return _valueNumeric > valueNumeric;
                    case ConditionOperatorBiggerOrEqual: return _valueNumeric >= valueNumeric;
                    case ConditionOperatorSmaller: return _valueNumeric < valueNumeric;
                    case ConditionOperatorSmallerOrEqual: return _valueNumeric <= valueNumeric;
                    case ConditionOperatorEqual: return _valueNumeric == valueNumeric;
                    case ConditionOperatorDifferent: return _valueNumeric != valueNumeric;
                }
                return false;            
            }
            else { // If one of the value is not a number
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


- (NSString*) info:(int)aDepth{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=Property %@", space, [super info:aDepth]];
    
    return info;
}

@end
