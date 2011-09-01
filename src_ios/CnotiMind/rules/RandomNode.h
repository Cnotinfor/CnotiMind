//
//  RandomNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 9/1/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "RuleNode.h"

@interface RandomNode : RuleNode {

}

- (id) initWithBrainAndParent:(Brain*)aBrain
                       parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;
- (void) dealloc;

@end
