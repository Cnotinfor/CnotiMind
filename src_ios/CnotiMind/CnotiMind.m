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
    
    if(![aText caseInsensitiveCompare:@"WM"])
    {
        return WorkingMemory;
    }
    if(![aText caseInsensitiveCompare:@"LTM"])
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
    if( (![aText caseInsensitiveCompare:@">"]) || (![aText caseInsensitiveCompare:@"bigger"]) )
    {
        return ConditionOperatorBigger;
    }
    if( ![aText caseInsensitiveCompare:@">="])
    {
        return ConditionOperatorBiggerOrEqual;
    }
    if( (![aText caseInsensitiveCompare:@"<"]) || (![aText caseInsensitiveCompare:@"smaller"]) )
    {
        return ConditionOperatorSmaller;
    }
    if( ![aText caseInsensitiveCompare:@"<="])
    {
        return ConditionOperatorSmallerOrEqual;
    }
    if( (![aText caseInsensitiveCompare:@"=="]) || (![aText caseInsensitiveCompare:@"="]) || (![aText caseInsensitiveCompare:@"equal"]) )
    {
        return ConditionOperatorEqual;
    }
    if( (![aText caseInsensitiveCompare:@"!="] ) || (![aText caseInsensitiveCompare:@"different"]) )
    {
        return ConditionOperatorDifferent;
    }
    
    return ConditionOperatorUndefined;
}


+ (enum DataMiningOperation) translateDataMiningOperator:(NSString*)aText
{
    
    if( ![aText caseInsensitiveCompare:@"max"] )
    {
        return DMO_Max;
    }
    if( ![aText caseInsensitiveCompare:@"min"] )
    {
        return DMO_Min;
    }
    if( ![aText caseInsensitiveCompare:@"sum"] )
    {
        return DMO_Sum;
    }
    if( ![aText caseInsensitiveCompare:@"count"] )
    {
        return DMO_Count;
    }
    if( ![aText caseInsensitiveCompare:@"mean"] )
    {
        return DMO_Mean;
    }
    if( ![aText caseInsensitiveCompare:@"exists"] )
    {
        return DMO_Exists;
    }
    if( ![aText caseInsensitiveCompare:@"last"] )
    {
        return DMO_Last;
    }
    if( ![aText caseInsensitiveCompare:@"first"] )
    {
        return DMO_First;
    }
    if( ![aText caseInsensitiveCompare:@"duration"] )
    {
        return DMO_Duration;
    }
    if( ![aText caseInsensitiveCompare:@"time"] )
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
    if( ![text caseInsensitiveCompare: @"sum"]  ||
       ![text caseInsensitiveCompare: @"+"]  )
    {
        return MathOperationSum;
    }
    if( ![text caseInsensitiveCompare: @"sub"]  ||
       ![text caseInsensitiveCompare: @"subtraction"]  ||
       ![text caseInsensitiveCompare: @"-"]  )
    {
        return MathOperationSubtraction;
    }
    if( ![text caseInsensitiveCompare: @"mul"]  ||
       ![text caseInsensitiveCompare: @"multiplication"]  ||
       ![text caseInsensitiveCompare: @"x"]  ||
       ![text caseInsensitiveCompare: @"*"]  )
    {
        return MathOperationMultiplication;
    }
    if( ![text caseInsensitiveCompare: @"div"]  ||
       ![text caseInsensitiveCompare: @"division"]  ||
       ![text caseInsensitiveCompare: @"quotient"]  ||
       ![text caseInsensitiveCompare: @"/"]  )
    {
        return MathOperationDivision;
    }
    if( ![text caseInsensitiveCompare: @"remainder"]  ||
       ![text caseInsensitiveCompare: @"%"]  )
    {
        return MathOperationRemainder;
    }
    if( ![text caseInsensitiveCompare: @"sqrt"]  )
    {
        return MathOperationSquareRoot;
    }
    
    return MathOperationUndefined;
}


+ (enum DeletePosition) translateDeletePosition:(NSString*)aText
{
    
    if( ![aText caseInsensitiveCompare:@"last"] )
    {
        return DeleteLast;
    }
    if( ![aText caseInsensitiveCompare:@"first"] )
    {
        return DeleteFirst;
    }
    if( ![aText caseInsensitiveCompare:@"item"] )
    {
        return DeleteItem;
    }
    if( ![aText caseInsensitiveCompare:@"all"] )
    {
        return DeleteAll;
    }
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
