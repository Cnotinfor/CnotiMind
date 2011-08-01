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


- (id) initWithKeyAndValueAndOperatorAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent
{
    
    if (self == [super initWithKeyAndValueAndBrainAndParent: aKey value:aValue operator:aOperator brain:aBrain parent:aParent])
    {
    
    }
    return self;
}


- (void) exec
{
    DLog(@"TETE");
    
    if ([self isTrue]) {
        NSMutableDictionary* variables = [[NSMutableDictionary alloc] init];
        [variables setObject:_value forKey:@"[Perception.value]"];
        DLog(@"TETE 2");
        //  TODO
        [self execChildren:variables];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    DLog(@"TATA");
    if ([self isTrue]) {
        [aVariables setObject:_value forKey:@"[Perception.value]"];
        [self execChildren];
    }

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=Perception", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (BOOL) isTrue
{
    
    //  TODO
    return TRUE;
    
    // Check if there are perceptions to be processed in the brain
    if( [_brain.receivedPerceptions count]!=0 )
    {
        // Just test the first perception
        Perception* p = (Perception*)[_brain.receivedPerceptions objectAtIndex:0];
        
        // Check if it is the percetion for this Node
        if( [p.name isEqual:_key] )
        {
            if( [_value length]==0 )
            {
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
							return [_value isEqualToString:s];
						case ConditionOperatorDifferent:
							return ![_value isEqualToString:s];
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
