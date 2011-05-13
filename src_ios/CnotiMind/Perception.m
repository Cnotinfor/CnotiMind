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
        _name = [NSString stringWithFormat:@""];
        _value = [NSNumber numberWithInt:0];
    }
    return self;
}




@end
