//
//  Node.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/21.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Node : NSObject {
    
    NSString* _key;
    NSString* _value;
}


@property (readwrite, assign) NSString* _key;
@property (readwrite, assign) NSString* _value;

- (id) init;
- (id) initWithKeyAndValue:(NSString*)aKey value:(NSString*)aValue;


- (NSString*) info:(int)depth;


@end
