//
//  PropertyNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "PropertyNode.h"
#import "Brain.h"

@implementation PropertyNode

- (id) initWithKeyAndValuAndBrainAndParent:(NSString*)aKey
                                     value:(NSString*)aValue
                                     brain:(Brain*)aBrain 
                                    parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _key = (aKey == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aKey];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];    
    }
    return self;
}


- (void) exec
{
    [_brain updatePropertyValue:_key value:_value];
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    // Convert tags that can be in the value of the property
    NSString* value = _value;
    [self tagsToValue:&value variables:&aVariables];
    [_brain updatePropertyValue:_key value:value];
}

- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Property key:%@ value:%@", space, _key, _value];
    
    return info;
}

- (void) dealloc
{
    [super dealloc];
}


@end
