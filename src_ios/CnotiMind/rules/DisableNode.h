//
//  DisableNode.h
//  LittleMozart
//
//  Created by Gonçalo Rodrigues on 11/21/11.
//  Copyright (c) 2011 Universidade de Coimbra. All rights reserved.
//

#import "RuleNode.h"

@interface DisableNode : RuleNode {
    NSString* _nodeName;
    BOOL _toDisable;
}

- (id) initWithNameAndValueAndBrainAndParent:(NSString*)aName 
                                       value:(NSString*)aValue
                                       brain:(Brain*)aBrain 
                                      parent:(id)aParent;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end
