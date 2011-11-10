//
//  ConditionDataMiningNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ConditionNode.h"
#import "Brain.h"

@interface ConditionDataMiningNode : ConditionNode {
    enum DataMiningOperation _dataMiningOperation;
    NSString* _variable;
    NSString* _compareValue;
    
    float _compareValueNumeric;
    enum MemoryType _memory;
    BOOL _isCompareValueNumeric;
    NSString* _result;
}


- (id) initWithKeyAndValueAndOperatorAndOperationAndMemoryAndVariableAndCompareValueBrainAndParent: (NSString*)aKey 
                                                                                             value:(NSString*)aValue 
                                                                                            operator: (enum ConditionOperator)aOperator 
                                                                                        operation:(enum DataMiningOperation)aOperation 
                                                                                        memory:(enum MemoryType)aMemory
                                                                                        variable:(NSString*)aVariable
                                                                                    compareValue:(NSString*)aCompareValue
                                                                                            brain:(Brain*)aBrain 
                                                                                            parent:(id)aParent;


- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (BOOL) isTrue;

- (void) dealloc;

@end
