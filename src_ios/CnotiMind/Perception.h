//
//  Perception.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MindNode.h"


@interface Perception : NSObject {
    
    id _value;
    NSString* _name;
    int _id;
}


@property (readwrite, retain) id value;
@property (readwrite, assign) int id;
@property (readwrite, retain) NSString* name;

- (id) init;
- (id) initWithNameAndAValue:(NSString*)aName value:(NSString*)aValue;
- (id) initWithNameAndAValueAndId:(NSString*)aName value:(NSString*)aValue id:(int)aId;
- (void) dealloc;

@end
