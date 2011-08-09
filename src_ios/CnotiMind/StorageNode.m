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
    MemoryEvent* m = [[MemoryEvent alloc] initWithEventAndValue:_event value:_value];
    //  TODO
    //  [_brain storeToMemory:m memory:_memory];

}


- (void) exec:(NSMutableDictionary*)aVariables
{
    MemoryEvent* m = [[MemoryEvent alloc] initWithEventAndValue:_event value: [self variableToValue:_value variables:aVariables]];
    //  TODO
    //  [_brain storeToMemory:m memory:_memory];

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Storage key=%@ value=%@", space, _event, _value];
    
    return info;
}



@end
