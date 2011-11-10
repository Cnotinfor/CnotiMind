//
//  DeleteNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "RuleNode.h"
#import "CnotiMind.h"

@interface DeleteNode : RuleNode{
    NSString* _key;
    NSString* _value;
    enum DeletePosition _position;
    enum MemoryType _memory;
}


- (id) initWithKeyAndValueAndPositionAndMemoryAndBrainAndParent:(NSString*)aKey
                                                          value:(NSString*)aValue
                                                       position:(enum DeletePosition)aPosition
                                                         memory:(enum MemoryType)aMemory 
                                                          brain:(Brain*)aBrain 
                                                         parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (void) dealloc;


@end
