//
//  ActionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/29.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RuleNode.h"

@class Brain;

@interface ActionNode : RuleNode {
    NSString* _name;
    NSString* _value;
    
    NSString* _probability;
    BOOL _isProbabilityNumeric;
    float _probabilityValue;
}

- (id) initWithNameAndValueAndBrainAndParent: (NSString*)aName 
                                       value:(NSString*)aValue 
                                       brain:(Brain*)aBrain 
                                      parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end
