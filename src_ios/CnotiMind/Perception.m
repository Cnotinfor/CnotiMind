//
//  Perception.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "Perception.h"

@implementation Perception

@synthesize value = _value;
@synthesize name = _name;

- (id) init
{
    if (self == [super init]) {
        _name = [[NSString alloc] initWithString:@""];
        _value = [[NSString alloc] initWithString:@""];
    }
    return self;
}

- (id) initWithNameAndAValue:(NSString*)aName value:(NSString*)aValue
{
    if (self == [super init]) {
        _name = [[NSString alloc] initWithString:aName];
        _value = [[NSString alloc] initWithString:aValue];
    }
    return self;
}

- (void) dealloc
{
    [_name release];
    [_value release];
    
    [super dealloc];
}


@end
