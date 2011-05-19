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


- (id) initWithKeyAndValueAndAndBrainAndParent: (NSString*)aKey 
                                         value:(NSString*)aValue 
                                        memory:(enum MemoryType)aMemory
                                         brain:(Brain*)aBrain 
                                        parent:(id)aParent
{
    if (self == [super initWithKeyAndValueAndBrainAndParent:aKey value:aValue brain:aBrain parent:aParent]) {
    
        _memory = aMemory;
    }

    return self;
}

/*
 Creates a memory Event and store it in the brain memory
 */
- (void) exec
{
    MemoryEvent* m = [[MemoryEvent alloc] initWithKeyAndValue:_key value:_value];
    //  TODO
    //  [_brain storeToMemory:m memory:_memory];

}


- (void) exec:(NSMutableDictionary*)aVariables
{
    MemoryEvent* m = [[MemoryEvent alloc] initWithKeyAndValue:_key value: [self variableToValue:_value variables:aVariables]];
    //  TODO
    //  [_brain storeToMemory:m memory:_memory];

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Storage key=%@ value=%@", space, _key, _value];
    
    return info;
}



@end
