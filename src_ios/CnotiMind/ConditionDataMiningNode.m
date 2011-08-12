//
//  ConditionDataMiningNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ConditionDataMiningNode.h"


@implementation ConditionDataMiningNode


- (id) initWithKeyAndValueAndOperatorAndOperationAndMemoryAndVariableAndCompareValueBrainAndParent: (NSString*)aKey 
                                                                                             value:(NSString*)aValue 
                                                                                          operator: (enum ConditionOperator)aOperator 
                                                                                         operation:(enum DataMiningOperation)aOperation 
                                                                                            memory:(enum MemoryType)aMemory
                                                                                          variable:(NSString*)aVariable
                                                                                      compareValue:(NSString*)aCompareValue
                                                                                             brain:(Brain*)aBrain 
                                                                                            parent:(id)aParent
{
    if (self == [super initWithKeyAndValueAndBrainAndParent: aKey value:aValue operator: aOperator brain:aBrain parent:aParent]) {
    
        _dataMiningOperation = aOperation;
        _variable = aVariable;
        _compareValue = aCompareValue;
        _memory = aMemory;
        _isCompareValueNumeric = FALSE;

        if ([[NSScanner scannerWithString:_compareValue] scanFloat:NULL]){
            _isCompareValueNumeric = TRUE;
        }
        else {
            _isCompareValueNumeric = FALSE;
        }
    }
    
    return self;
}


- (void) exec
{
    DLog(@"ConditionDataMining exec");
    
    if ([self isTrue]) {
            
        if ([_variable length]==0) {
            [super execChildren];
        }
        else {
            NSMutableDictionary* variables = [[NSDictionary alloc] init];
            [variables setObject:_result forKey:_variable];
            
            //  TODO
            [self execChildren:variables];
        }
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    DLog(@"ConditionDataMining exec aVariables");
    
    if ([self isTrue]) {
    
        if ([_variable length]!=0) {
            [aVariables setObject:_result forKey:_variable];
        }
        
        //  TODO        
        [self execChildren:aVariables];
    }
}



- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition type=DataMining", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (BOOL) isTrue
{
    BOOL valid;
    
    // If the values are numbers it should use the
    if( _isValueNumeric && _isCompareValueNumeric )
    {
        id result = [_brain dataMining:_dataMiningOperation event:_key value:[NSString stringWithFormat:@"%f", _valueNumeric] memoryType:_memory valid:&valid];
                     
        if(!valid)
        {
            return false;
        }
        
        _result = (NSString*)result;
        
        NSLog(@"0 - isTrue result: %@",result);
        
        int _resultNumeric = [result intValue];

        NSLog(@"0 - isTrue resultNumeric: %d",_resultNumeric);
        
        switch( (int)_operator )
        {
            case ConditionOperatorBigger: 
                return _resultNumeric > _compareValueNumeric ;
            case ConditionOperatorBiggerOrEqual:
                return _resultNumeric >= _compareValueNumeric;
            case ConditionOperatorSmaller: 
                return _resultNumeric < _compareValueNumeric;
            case ConditionOperatorSmallerOrEqual: 
                return _resultNumeric <= _compareValueNumeric;
            case ConditionOperatorEqual: 
                return _resultNumeric == _compareValueNumeric;
            case ConditionOperatorDifferent: 
                return _resultNumeric != _compareValueNumeric;
        }
        
        return false;
    }
    else // If the value is String
    {
        id result = [_brain dataMining: _dataMiningOperation event:_key memoryType:_memory valid:&valid];
        
        if(!valid)
        {
            return false;
        }
        
        DLog(@"1 - isTrue result: %@", result);
        DLog(@"1 - isTrue _compareValue: %@", _compareValue);
        
        _result = result;
        
        switch( (int)_operator )
        {
            case ConditionOperatorEqual: 
                return [_result isEqualToString:_compareValue];
            case ConditionOperatorDifferent: 
                return [_result isEqualToString:_compareValue];
        }
        
        return false;
    }
}

@end
