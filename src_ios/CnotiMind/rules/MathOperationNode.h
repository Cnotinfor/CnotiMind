//
//  MathOperationNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "RuleNode.h"
#import "CnotiMind.h"

@interface MathOperationNode : RuleNode {
    
    enum MathOperation _operation;
    NSString* _variable;
    NSString* _value;
    float _numericValue;
    bool _isNumericValue;
    NSString* _resultVariable;
}

- (id) initWithMathOperationAndVariableAndValueAndresutVariableAndBrainAndParent: (enum MemoryType)aMemory 
                                                                           brain:(Brain*)aBrain 
                                                                          parent:(id)aParent;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (float) applyOperation:(float)aVariableValue;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end