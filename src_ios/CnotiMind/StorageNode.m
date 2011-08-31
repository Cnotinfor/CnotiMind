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


- (id) initWithEventAndValueAndMemoryAndBrainAndParent: (NSString*)aEvent 
                                                 value:(NSString*)aValue 
                                                memory:(enum MemoryType)aMemory
                                                 brain:(Brain*)aBrain 
                                                parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
        _memory = aMemory;
        _event = (aEvent == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aEvent];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
        
        _clearStorage = FALSE;
    }
    
    return self;
}


- (id) initWithClearAndMemoryAndBrainAndParent: (BOOL)aClear 
                                        memory:(enum MemoryType)aMemory
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
        _memory = aMemory;
        _clearStorage = aClear;
        _event = [[NSString alloc] initWithString:@""];
        _value = [[NSString alloc] initWithString:@""];
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
    NSString* value = [NSString stringWithFormat:@"%@",_value];
    [self tagsToValue:&value variables:&aVariables];
        
    MemoryEvent* m = [[MemoryEvent alloc] initWithEventAndValue:_event value:value];
    [_brain storeToMemory:m memoryType:_memory];
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    info = [info stringByAppendingFormat:@"%@ Storage event=%@ value=%@", space, _event, _value];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

- (void) dealloc
{
    [_event release];
    [_value release];
    
    [super dealloc];
}

@end
