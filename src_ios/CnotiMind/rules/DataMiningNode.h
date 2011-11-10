//
//  ConditionEmotionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CnotiMind.h"

#import "ConditionNode.h"
#import "Emotion.h"


@interface DataMiningNode : RuleNode {
    
    
    NSString* _event;
    NSString* _value;
    enum DataMiningOperation _operation;
    enum MemoryType _memory;
    NSString* _variable;
    
    NSNumber* _valueNumeric;
    BOOL _isValueNumeric;
    id _result;
    NSString* _position;
    BOOL _isPositionNumeric;
    int _positionNumeric;
}

- (id) initWithEventAndValueAndOperatorAndMemoryAndVariableAndPositionAndBrainAndParent: (NSString*)aEvent 
                                                                                  value:(NSString*)aValue 
                                                                               operator:(enum DataMiningOperation)aDataMiningOperation 
                                                                                 memory:(enum MemoryType)aMemory
                                                                               variable:(NSString*)aVariable
                                                                               position:(NSString*)aPosition
                                                                                  brain:(Brain*)aBrain 
                                                                                 parent:(id)aParent;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (BOOL) isTrue;
- (BOOL) isTrue:(NSMutableDictionary*)aVariables;

- (void) dealloc;

@end
