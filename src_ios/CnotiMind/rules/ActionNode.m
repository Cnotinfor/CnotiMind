//
//  ActionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/29.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "ActionNode.h"

#import "Brain.h"

#define ARC4RANDOM_MAX      0x100000000


@implementation ActionNode


- (id) initWithNameAndValueAndBrainAndParent: (NSString*)aName 
                                       value:(NSString*)aValue 
                                       brain:(Brain*)aBrain 
                                      parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _name = (aName == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aName];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
    }
    
    return self;
    
}

- (id) initWithNameAndValueAndBrainAndParent:(NSString*)aName 
                                       value:(NSString*)aValue
                                 probability:(NSString*)aProbability
                                       brain:(Brain*)aBrain 
                                      parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _name = (aName == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aName];
        _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
        
        _probability = (aProbability == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aProbability];

        if ([self isNumeric:_probability]) {
            _isProbabilityNumeric = true;
            _probabilityValue = [_probability floatValue];    
        }
    }
    
    return self;
}


- (void) exec
{
//    TODO check if probability is ok
    if (_isProbabilityNumeric) {
        if ( _probabilityValue <= 0 ) {
            return;
        }
        if (_probabilityValue < 1) {
            
            //test if should execute
            double val = floorf(((double)arc4random() / ARC4RANDOM_MAX) * 100.0f);
            val = val / 100;

            if ( val > _probabilityValue ) {
                return;
            }
            
        }
        else {
            // if the probability is not a number, return since there are no variables
			// to get the value
			return;
        }
    }
    [_brain executeAction:_name value:_value]; 
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    NSString* value = [NSString stringWithFormat:@"%@", _value];
    
    [self tagsToValue:&value variables:&aVariables];
    
    if ([value length]>0) {
        [_brain executeAction:_name value:value];        
    }

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Action (%@) value=%@", space, _name, _value];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}

- (void) dealloc
{
    [_name release];
    [_value release];
    
    [super dealloc];
}


@end
