//
//  PropertyNode.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/31/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "RuleNode.h"

@interface PropertyNode : RuleNode {
    NSString* _key;
    NSString* _value;
}

- (id) initWithKeyAndValuAndBrainAndParent:(NSString*)aKey
                                     value:(NSString*)aValue
                                     brain:(Brain*)aBrain 
                                    parent:(id)aParent;

@property(retain,readonly) NSString* key;
@property(retain,readonly) NSString* value;


- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*) info:(int)aDepth;
- (void) dealloc;

@end
