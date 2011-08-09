//
//  ActionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/29.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ActionNode.h"

#import "Brain.h"


@implementation ActionNode


- (id) initWithNameAndValueAndBrainAndParent: (NSString*)aName value:(NSString*)aValue brain:(Brain*)aBrain parent:(id)aParent
{
//    return [super initWithKeyAndValueAndBrainAndParent:aKey value:aValue brain:aBrain parent:aParent];
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _name = aName;
        _value = aValue;
    }
    
    return self;
}


- (void) exec
{
    DLog(@"ActionNode exec");
//    [_brain executeAction:_key value:_value]; 
}


- (void) exec:(NSString*)aVariables
{
    
    DLog(@"ActionNode exec");
    DLog(@"ActionNode exec name: %@", _name);
    DLog(@"ActionNode exec value: %@", _value);

    [_brain executeAction:_name value:_value];
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];

    info = [info stringByAppendingFormat:@"%@ Action (%@) value= ", space, _name, _value];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

@end
