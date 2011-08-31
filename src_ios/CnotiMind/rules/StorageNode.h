//
//  StorageNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/02.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CnotiMind.h"
#import "RuleNode.h"

@interface StorageNode : RuleNode {
    
    enum MemoryType _memory;
    NSString* _event;
    NSString* _value;
    BOOL _clearStorage;
}

- (id) initWithEventAndValueAndMemoryAndBrainAndParent: (NSString*)aEvent 
                                                 value:(NSString*)aValue 
                                                memory:(enum MemoryType)aMemory
                                                 brain:(Brain*)aBrain 
                                                parent:(id)aParent;

- (id) initWithClearAndMemoryAndBrainAndParent: (BOOL)aClear 
                                        memory:(enum MemoryType)aMemory
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent;


- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end