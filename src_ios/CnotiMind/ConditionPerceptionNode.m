//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ConditionPerceptionNode.h"

#import "Brain.h"
#import "Perception.h"

@implementation ConditionPerceptionNode


- (id) initWithPerceptionAndValueAndOperatorAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent
{
    
    if (self == [super initWithKeyAndValueAndBrainAndParent: aKey value:aValue operator:aOperator brain:aBrain parent:aParent])
    {
    
    }
    return self;
}


- (void) exec
{
    
    if ([self isTrue]) {
        NSMutableDictionary* variables = [[NSMutableDictionary alloc] init];

        Perception* p = [[_brain receivedPerceptions] objectAtIndex:0];
        [variables setObject:[p value] forKey:@"[Perception.value]"];

        //  TODO
        [self execChildren:variables];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if ([self isTrue]) {
        // if the perception value is not in the variables list
        if ([aVariables objectForKey:@"[Perception.value]"]) {
            
            Perception* p = [[_brain receivedPerceptions] objectAtIndex:0];
            [aVariables setObject:[p value] forKey:@"[Perception.value]"];
        }
        
        [self execChildren: aVariables];
    }
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=Perception perception=%@ value=%@", space, _key, _value];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (BOOL) isTrue
{
    // Check if there are perceptions to be processed in the brain
    
//    DLog(@"%d", [_brain.receivedPerceptions count]);
    
    if( [_brain.receivedPerceptions count]!=0 )
    {
        // Just test the first perception
        Perception* p = (Perception*)[_brain.receivedPerceptions objectAtIndex:0];
//        DLog(@"0 - %@ - %@",p.name, p.value);
//        DLog(@"0 - %@",_key);

        // Check if it is the percetion for this Node
        if( ![p.name caseInsensitiveCompare:_key] )
        {
//            DLog(@"1 - %@ - %@",p.name,p.value);
            
            if( [_value length]==0 )
            {
//                DLog(@"2 - %@ - %@",p.name,p.value);
                return true;
            }
            else // test if it should be a perception with a specific value
            {
                bool ok, ok2;
                
                ok = ([[NSScanner scannerWithString:[p value]] scanFloat:NULL]) ? TRUE : FALSE;                
                float perceptionValue = [[p value] floatValue];
                
                ok2 = ([[NSScanner scannerWithString:_value] scanFloat:NULL]) ? TRUE : FALSE;
                float nodeValue = [_value floatValue];
                
                if( ok && ok2 )
                {
                    switch( (int)_operator )
                    {
                        case ConditionOperatorBigger: 
                            return perceptionValue > nodeValue;
                        case ConditionOperatorBiggerOrEqual: 
                            return perceptionValue >= nodeValue;
                        case ConditionOperatorSmaller: 
                            return perceptionValue < nodeValue;
                        case ConditionOperatorSmallerOrEqual: 
                            return perceptionValue <= nodeValue;
                        case ConditionOperatorEqual: 
                            return perceptionValue == nodeValue;
                        case ConditionOperatorDifferent: 
                            return perceptionValue != nodeValue;
                    }
                    return false;
                }
                // TODO is String                
                else if([p value] != nil)
                {
                    // If it is a String value, it can only use equal or different operator.
                    NSString* s = [NSString stringWithFormat:@"%@",[p value]];
                    switch( (int)_operator )
                    {
						case ConditionOperatorEqual:
							return ![_value caseInsensitiveCompare:s];
						case ConditionOperatorDifferent:
							return [_value caseInsensitiveCompare:s];
                    }
                    return false;
                }
                else
                {
                    // The value of the perceptions is not recognized,
                    // so this node will return false
                    return false;
                }
                
                // TODO, test the value using the condition Operator
            }
        }
    }
    
    return false;
}


@end
