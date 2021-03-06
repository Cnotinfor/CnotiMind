//
//  ConditionEmotionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Emotion.h"
#import "ConditionNode.h"




@interface ConditionEmotionNode : ConditionNode {
    
}

- (id) initWithEmotionAndValueAndOperatorAndBrainAndParent: (NSString*)aEmotion value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent;

- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (BOOL) isTrue;
- (BOOL) testEmotion:(Emotion*)aEmotion;


@end
