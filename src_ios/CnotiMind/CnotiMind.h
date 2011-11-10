//
//  CnotiMind.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>


enum MemoryType
{
    LongTermMemory,
    WorkingMemory,
    UndefinedMemory
};

enum ConditionOperator
{
    ConditionOperatorEqual,
    ConditionOperatorDifferent,
    ConditionOperatorSmaller,
    ConditionOperatorBigger,
    ConditionOperatorBiggerOrEqual,
    ConditionOperatorSmallerOrEqual,
    ConditionOperatorUndefined
};

enum DataMiningOperation
{
    DMO_Max,
    DMO_Min,
    DMO_Sum,
    DMO_Count,
    DMO_Mean,
    DMO_Exists,
    DMO_Last,
    DMO_First,
    DMO_Duration,
    DMO_Time,
    DMO_Undefined
};


enum MathOperation
{
    MathOperationSum,
    MathOperationMultiplication,
    MathOperationDivision,
    MathOperationRemainder,
    MathOperationSubtraction,
    MathOperationSquareRoot,
    MathOperationUndefined
};


enum DeletePosition
{
    DeleteLast,
    DeleteFirst,
    DeleteItem, // Not implemente yeat
    DeleteAll
};


@interface CnotiMind : NSObject {
    
}

+ (enum MemoryType) translateMemoryType:(NSString*)aText;
+ (enum ConditionOperator) translateConditionOperator:(NSString*)aText;
+ (enum DataMiningOperation) translateDataMiningOperator:(NSString*)aText;
+ (enum MathOperation) translateMathOperation:(NSString*)text;
+ (enum DeletePosition) translateDeletePosition:(NSString*)aText;
+ (BOOL)isNumeric:(NSString*)s;

@end
