//
//  ConditionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/01.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CnotiMind.h"
#import "RuleNode.h"

@interface ConditionNode : RuleNode {

    NSString* _key;
    NSString* _value;
    
    enum ConditionOperator _operator;
    
    float _valueNumeric;
    BOOL _isValueNumeric;
    
}



- (id) initWithKeyAndValueAndBrainAndParent: (NSString*)aKey 
                                      value:(NSString*)aValue 
                                   operator: (enum ConditionOperator)aOperator 
                                      brain:(Brain*)aBrain 
                                     parent:(id)aParent;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (BOOL)isTrue;

- (void) dealloc;


@end
