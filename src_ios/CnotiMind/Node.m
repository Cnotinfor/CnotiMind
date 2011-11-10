//
//  Node.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/21.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "Node.h"


@implementation Node

@synthesize _key = key;
@synthesize _value = value;

- (id) init
{
    if (self == [super init]) {
    }
    return self;
}

//- (id) initWithKeyAndValue:(NSString*)aKey value:(NSString*)aValue
//{
//    if (self == [super init]) {
//        _key = aKey;
//        _value = aValue;
//    }
//    return self;
//}

//  virtual method
- (NSString*) info:(int)depth
{
    return nil;
}


- (void) dealloc
{
    [super dealloc];
}


@end
