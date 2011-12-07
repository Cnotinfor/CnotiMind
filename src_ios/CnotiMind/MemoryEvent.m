//
//  MemoryEvent.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Cnotinfor. All rights reserved.
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
        _event = [[NSString alloc] initWithString:aEvent];
        _value = [[NSString alloc] initWithString:aValue];

        _time = [[NSDate date] timeIntervalSince1970];
    }
    return self;
}


- (id) initWithEventAndValueAndTime:(NSString*)aEvent value:(NSString*)aValue time:(NSString*)aTime
{
    if (self == [self initWithEventAndValue: aEvent value:aValue]) {        
        _time = [aTime floatValue];
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
    DLog(@"event: %@", _event);
    DLog(@"value: %@", _value);
    DLog(@"time: %f", _time);
    xml = [NSString stringWithFormat:@"\t<MemoryEvent event=\"%@\" value=\"%@\" time=\"%f\" />\n", _event, _value, _time];
    
    return xml;
}

- (void) dealloc
{
    [_event release];
    [_value release];
    
    [super dealloc];
}

@end
