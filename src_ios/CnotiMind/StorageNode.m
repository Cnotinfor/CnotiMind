//
//  StorageNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/02.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "StorageNode.h"
#import "MemoryEvent.h"
#import "Brain.h"


@implementation StorageNode


- (id) initWithEventAndValueAndAndBrainAndParent: (NSString*)aEvent 
                                           value:(NSString*)aValue 
                                          memory:(enum MemoryType)aMemory
                                           brain:(Brain*)aBrain 
                                          parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
        _memory = aMemory;
        _event = aEvent;
        _value = aValue;
        _clearStorage = FALSE;
    }

    return self;
}

/*
 Creates a memory Event and store it in the brain memory
 */
- (void) exec
{
    // Test if the node is for clearing the memory
    if( _clearStorage )
    {
        if( _memory == WorkingMemory )
        {
            [_brain clearWorkingMemory];
        }
        else
        {
            [_brain clearMemory];
        }
        return;
    }
    // If it is not for clearing, check if the value and event are valid
    if( [_event length]==0 || [_value length]==0 )
    {
        return;
    }
    
    // Create memory event to add to the memory
    MemoryEvent* m = [[MemoryEvent alloc] initWithEventAndValue:_event value:_value];
    [_brain storeToMemory:m memoryType:_memory];

}


- (void) exec:(NSMutableDictionary*)aVariables
{
//    MemoryEvent* m = [[MemoryEvent alloc] initWithEventAndValue:_event value: [self variableToValue:_value variables:aVariables]];
    [self exec];
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Storage key=%@ value=%@", space, _event, _value];
    
    return info;
}



@end
