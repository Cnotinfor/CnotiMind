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
}

- (id) initWithNameAndValueAndBrainAndParent: (NSString*)aName value:(NSString*)aValue brain:(Brain*)aBrain parent:(id)aParent;

- (void) exec;
- (void) exec:(NSString*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end
