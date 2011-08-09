//
//  MemoryEvent.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Perception.h"


@interface MemoryEvent : NSObject {
    
    id _value;
    NSString* _event;
    NSTimeInterval _time; 
    
}

@property (readwrite, assign) id value;
@property (readwrite, assign) NSString* event;

@property (readwrite, assign) NSTimeInterval time;


- (id) initWithEventAndValue:(NSString*)aEvent value:(id)aValue;
- (id) initWithEventAndValueAndTime:(NSString*)aEvent value:(id)aValue time:(NSTimeInterval)aTime;

- (id) initWithPerception: (Perception*)aPerception;

- (NSString*) toXML;




@end
