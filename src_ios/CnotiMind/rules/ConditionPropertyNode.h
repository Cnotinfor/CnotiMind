//
//  ConditionPropertyNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "ConditionNode.h"

@interface ConditionPropertyNode : ConditionNode {

}

- (id) initWithPropertyAndValuAndOperatorAndBrainAndParent: (NSString*)aProperty 
                                                     value:(NSString*)aValue
                                                  operator:(enum ConditionOperator)aOperator
                                                     brain:(Brain*)aBrain 
                                                    parent:(id)aParent;

- (BOOL) isTrue;
- (NSString*) info:(int)aDepth;

@end
