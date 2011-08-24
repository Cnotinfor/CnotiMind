//
//  CnotiMind.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "CnotiMind.h"


@implementation CnotiMind

+ (enum MemoryType) translateMemoryType:(NSString*)aText
{
    
    if([aText isEqualToString:@"WM"])
    {
        return WorkingMemory;
    }
    if([aText isEqualToString:@"LTM"])
    {
        return LongTermMemory;
    }
    return UndefinedMemory;
}


+ (enum ConditionOperator) translateConditionOperator:(NSString*)aText
{
    if (aText==nil) {
        return ConditionOperatorUndefined;
    }
    if( [aText isEqualToString:@">"])
    {
        return ConditionOperatorBigger;
    }
    if( [aText isEqualToString:@">="])
    {
        return ConditionOperatorBiggerOrEqual;
    }
    if( [aText isEqualToString:@"<"])
    {
        return ConditionOperatorSmaller;
    }
    if( [aText isEqualToString:@"<="])
    {
        return ConditionOperatorSmallerOrEqual;
    }
    if( [aText isEqualToString:@"=="])
    {
        return ConditionOperatorEqual;
    }
    if( ([aText isEqualToString:@"!="] ) || ([aText isEqualToString:@"<>"]) )
    {
        return ConditionOperatorDifferent;
    }
    
    return ConditionOperatorUndefined;
}


+ (enum DataMiningOperation) translateDataMiningOperator:(NSString*)aText
{
    
    if( [aText isEqualToString:@"max"] )
    {
        return DMO_Max;
    }
    if( [aText isEqualToString:@"min"] )
    {
        return DMO_Min;
    }
    if( [aText isEqualToString:@"sum"] )
    {
        return DMO_Sum;
    }
    if( [aText isEqualToString:@"count"] )
    {
        return DMO_Count;
    }
    if( [aText isEqualToString:@"mean"] )
    {
        return DMO_Mean;
    }
    if( [aText isEqualToString:@"exists"] )
    {
        return DMO_Exists;
    }
    if( [aText isEqualToString:@"last"] )
    {
        return DMO_Last;
    }
    if( [aText isEqualToString:@"first"] )
    {
        return DMO_First;
    }
    if( [aText isEqualToString:@"duration"] )
    {
        return DMO_Duration;
    }
    if( [aText isEqualToString:@"time"] )
    {
        return DMO_Time;
    }
    return DMO_Undefined;
}


/*
 Convert text string to a MathOperation
 */
+ (enum MathOperation) translateMathOperation:(NSString*)text
{
    if( [text isEqualToString: @"sum"]  ||
       [text isEqualToString: @"+"]  )
    {
        return MathOperationSum;
    }
    if( [text isEqualToString: @"sub"]  ||
       [text isEqualToString: @"subtraction"]  ||
       [text isEqualToString: @"-"]  )
    {
        return MathOperationSubtraction;
    }
    if( [text isEqualToString: @"mul"]  ||
       [text isEqualToString: @"multiplication"]  ||
       [text isEqualToString: @"x"]  ||
       [text isEqualToString: @"*"]  )
    {
        return MathOperationMultiplication;
    }
    if( [text isEqualToString: @"div"]  ||
       [text isEqualToString: @"division"]  ||
       [text isEqualToString: @"quotient"]  ||
       [text isEqualToString: @"/"]  )
    {
        return MathOperationDivision;
    }
    if( [text isEqualToString: @"remainder"]  ||
       [text isEqualToString: @"%"]  )
    {
        return MathOperationRemainder;
    }
    if( [text isEqualToString: @"sqrt"]  )
    {
        return MathOperationSquareRoot;
    }
    
    return MathOperationUndefined;
}


+ (BOOL)isNumeric:(NSString*)s
{
    NSScanner *sc = [NSScanner scannerWithString: s];
    // We can pass NULL because we don't actually need the value to test
    // for if the string is numeric. This is allowable.
    if ( [sc scanFloat:NULL] )
    {
        // Ensure nothing left in scanner so that "42foo" is not accepted.
        // ("42" would be consumed by scanFloat above leaving "foo".)
        return [sc isAtEnd];
    }
    // Couldn't even scan a float :(
    return NO;
}

@end
