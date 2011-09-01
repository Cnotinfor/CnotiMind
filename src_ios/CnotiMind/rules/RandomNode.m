//
//  RandomNode.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 9/1/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "RandomNode.h"

@implementation RandomNode

- (id) initWithBrainAndParent:(Brain*)aBrain
                       parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        
    }
    
    return self;
}

/**
 Choose a random child node and executes it.
 */
- (void) exec
{
    int count = [[self children] count];
    
    // It must have children nodes to run
    if(count == 0)
    {
        return;
    }
    
    int n = arc4random() % count;
    
    RuleNode* node = [[self children] objectAtIndex:n-1];
    [node exec];     
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    int count = [[self children] count];
    
    // It must have children nodes to run
    if(count == 0)
    {
        return;
    }
    
    int n = arc4random() % count;
    
    RuleNode* node = [[self children] objectAtIndex:n-1];
    [node exec:aVariables]; 

}

- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Random", space];
    
    return info;  
}


- (void) dealloc
{
    [super dealloc];
}


@end
