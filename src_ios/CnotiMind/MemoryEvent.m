//
//  MemoryEvent.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "MemoryEvent.h"

/**!
 Creates a memory event with a \a key name and a \a value. The event time
 is the local time.
 */


@implementation MemoryEvent

@synthesize value = _value;
@synthesize event = _event;

@synthesize time = _time;


- (id) initWithEventAndValue:(NSString*)aEvent value:(id)aValue
{
    if (self == [super init]) {
        _event = aEvent;
        _value = aValue;

        _time = [[NSDate date] timeIntervalSince1970];
    }
    return self;
}


- (id) initWithEventAndValueAndTime:(NSString*)aEvent value:(id)aValue time:(NSTimeInterval)aTime
{
    if (self == [super init]) {
        _event = aEvent;
        _value = aValue;
        
        _time = aTime;
    }
    return self;
}


- (id) initWithPerception: (Perception*)aPerception
{
    if (self == [super init]) {
        _event = aPerception.name;
        _value = aPerception.value;
        
        _time = [[NSDate date] timeIntervalSince1970];
    }
    return self;
}


- (NSString*) toXML
{
    NSString* xml;
    
    xml = [NSString stringWithFormat:@"<MemoryEvent event=%@ value=%@ time=%@ </MemoryEvent>"];
    
    return xml;
}

@end
