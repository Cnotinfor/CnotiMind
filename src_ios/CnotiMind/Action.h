//
//  Action.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/21.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Node.h"

@interface Action : Node {
    
}


- (id) initWithKeyAndValue:(NSString*)aKey value:(NSString*)aValue;

@end
