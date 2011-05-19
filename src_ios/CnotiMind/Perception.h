//
//  Perception.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Node.h"


@interface Perception : NSObject {
    
    id _value;
    NSString* _name;
}

- (id) init;

@property (readwrite, assign) id value;
@property (readwrite, assign) NSString* name;


@end
