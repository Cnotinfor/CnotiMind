//
//  ClearMemoryNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "RuleNode.h"
#import "CnotiMind.h"

@interface ClearMemoryNode : RuleNode {
    enum MemoryType _memory;
}

- (id) initWithMemoryAndBrainAndParent: (enum MemoryType)aMemory 
                                 brain:(Brain*)aBrain 
                                parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;

@end
