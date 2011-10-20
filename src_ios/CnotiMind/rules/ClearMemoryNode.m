//
//  ClearMemoryNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ClearMemoryNode.h"
#import "Brain.h"

@implementation ClearMemoryNode

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (id) initWithMemoryAndBrainAndParent: (enum MemoryType)aMemory 
                                 brain:(Brain*)aBrain 
                                parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _memory = aMemory;
    }
    
    return self;
}


- (void) exec
{
    switch (_memory) {
        case LongTermMemory:
            [_brain clearMemory];
            break;
        case WorkingMemory:
            [_brain clearWorkingMemory];
            break;
            
        default:
            break;
    }

}


- (void) exec:(NSMutableDictionary*)aVariables{
    [self exec];
}


- (NSString*) info:(int)aDepth{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ ClearMemory (%@)", space, _memory == LongTermMemory ? @"LTM" : @"WM"];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (void)dealloc
{
    [super dealloc];
}


@end
