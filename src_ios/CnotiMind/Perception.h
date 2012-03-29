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
}


@property (readwrite, retain) id value;
@property (readwrite, retain) NSString* name;

- (id) init;
- (id) initWithNameAndAValue:(NSString*)aName value:(NSString*)aValue;

- (void) dealloc;

@end
