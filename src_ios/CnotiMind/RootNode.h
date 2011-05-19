//
//  RootNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RuleNode.h"


@interface RootNode : RuleNode {
    
}


- (id) initWithBrainAndParent:(Brain*)aBrain parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (BOOL) isRoot;
- (NSString*) info:(int)aDepth;


@end
