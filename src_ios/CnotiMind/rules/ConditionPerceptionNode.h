//
//  ConditionEmotionNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ConditionNode.h"
#import "Emotion.h"



@interface ConditionPerceptionNode : ConditionNode {
    
}

- (id) initWithPerceptionAndValueAndOperatorAndBrainAndParent: (NSString*)aKey 
                                                        value:(NSString*)aValue 
                                                     operator: (enum ConditionOperator)aOperator 
                                                        brain:(Brain*)aBrain 
                                                       parent:(id)aParent;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;

- (BOOL) isTrue;

@end
