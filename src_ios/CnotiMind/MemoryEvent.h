//
//  MemoryEvent.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Perception.h"

@interface MemoryEvent : NSObject 
{
    id _value;
    NSString* _event;
    NSTimeInterval _time;
}

@property (readwrite, retain) id value;
@property (readwrite, retain) NSString* event;

@property (readwrite, assign) NSTimeInterval time;


- (id) initWithEventAndValue:(NSString*)aEvent value:(id)aValue;
- (id) initWithEventAndValueAndTime:(NSString*)aEvent value:(NSString*)aValue time:(NSString*)aTime;

- (id) initWithPerception: (Perception*)aPerception;

- (NSString*) toXML;

- (void) dealloc;


@end
