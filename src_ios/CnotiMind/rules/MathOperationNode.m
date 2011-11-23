//
//  MathOperationNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "MathOperationNode.h"

@implementation MathOperationNode


- (id) initWithMathOperationAndVariableAndValueAndResutVariableAndBrainAndParent: (enum MathOperation)aMathOperation
                                                                        variable:(NSString*)aVariable
                                                                           value:(NSString*)aValue
                                                                           resultVariable:(NSString*)aResultVariable
                                                                           brain:(Brain*)aBrain 
                                                                          parent:(id)aParent
{

    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _operation = aMathOperation;
        _variable = (aVariable == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aVariable];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
        _resultVariable = (aResultVariable == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aResultVariable];
    }
    
    
    return self;
}


/*
 It does not do nothing, since it requires variables to be executed
 */
- (void) exec
{
    return;
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    float numericValue;
    
    // Test if the value to use in the operation is a variable
    if(!_isNumericValue)
    {
        NSString* value = _value;
        [self tagsToValue:&value variables:&aVariables];
        
        // Variable not found
        if( [value length]==0 )
        {
            DLog("[MathOperationNode::exec] value %@ has not found in variables", value);
            return; // does nothing
        }
        
        
        BOOL valueOk;
        // Convert to number
        if ([self isNumeric:value]) {
            valueOk = TRUE;
            numericValue = [value floatValue];
        }
        
        if( !valueOk )
        {
            DLog("[MathOperationNode::exec] value %@ is not a number", value);
            return; // It was not possible to convert to number
        }
        
        // update the numeric value from the node
        _numericValue = numericValue;
    }
    
    // Get the value from the Variable
    NSString* variableValue = _variable;
    [self tagsToValue:&variableValue variables:&aVariables];
    
    // Test if the variable exists
    if( [variableValue length]!=0 )
    {
        // Test if the variable value is a numeric value
        float variableNumericValue;
        bool variableOk;
        if ([self isNumeric:variableValue]) {
            variableOk = TRUE;
            variableNumericValue = [variableValue floatValue];
        }
                
        
        if( variableOk )
        {
            // Apply the operator
            float result = [self applyOperation:variableNumericValue];
            DLog(@"result: %f", result);
            
            // Save the output
            if( [_resultVariable length]==0 ) // If it is empty, save on the same variable
            {
                [aVariables setValue:[NSString stringWithFormat:@"%f", result] forKey:_variable];
            }
            else
            {
                [aVariables setValue:[NSString stringWithFormat:@"%f", result] forKey:_resultVariable];
            }
            
            // Execute the children nodes with the new variable values
            [self execChildren:aVariables];
        }
    }
}


- (float) applyOperation:(float)aVariableValue
{
    switch( (int)_operation )
    {
        case MathOperationSum:
            return aVariableValue + _numericValue;
        case MathOperationMultiplication:
            return aVariableValue * _numericValue ;
        case MathOperationDivision:
            if( aVariableValue == 0 )
            {
                return 0;
            }
            return aVariableValue / _numericValue;
        case MathOperationRemainder:
            if( aVariableValue == 0 )
            {
                return 0;
            }
            return (int) aVariableValue % (int) _numericValue;
        case MathOperationSubtraction:
            return aVariableValue - _numericValue;
        case MathOperationSquareRoot:
            return sqrt( aVariableValue );
    }
    
    // If undefined return the same value from the variable
    return aVariableValue;
}


- (NSString*) info:(int)aDepth
{

    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ MathOperation %@", space, [super info:aDepth]];
    
    return info;
}


- (void) dealloc
{
    [super dealloc];
}


@end
