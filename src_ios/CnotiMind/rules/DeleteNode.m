//
//  DeleteNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "DeleteNode.h"
#import "Brain.h"

@implementation DeleteNode

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (id) initWithKeyAndValueAndPositionAndMemoryAndBrainAndParent:(NSString*)aKey
                                                          value:(NSString*)aValue
                                                       position:(enum DeletePosition)aPosition
                                                         memory:(enum MemoryType)aMemory 
                                                          brain:(Brain*)aBrain 
                                                         parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        
        _key = (aKey == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aKey];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
        _memory = aMemory;
        _position = aPosition;
    }
    return self;
}


- (void) exec
{
    if([_value length]==0)
    {
        [_brain deleteEvent:_key position:_position memory:_memory];
    }
    else
    {
        [_brain deleteEvent:_key value:_value position:_position memory:_memory];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if([_value length]==0)
    {
        [_brain deleteEvent:_key position:_position memory:_memory];
    }
    else
    {
        // Test if there are variables in the value
        NSString* value = _value;
        [self tagsToValue:&value variables:&aVariables];
        
        [_brain deleteEvent:_key value:value position:_position memory:_memory];
    }
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ DeleteNode key:%@ value:%@ (%@)", space, _key, _value, _memory == LongTermMemory ? @"LTM" : @"WM"];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (void) dealloc
{
    [super dealloc];
}


@end
