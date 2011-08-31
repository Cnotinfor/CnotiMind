//
//  RootNode.m
//  CnotiMind
//

#import "RootNode.h"

@implementation RootNode

- (id) initWithBrainAndParent:(Brain*)aBrain 
                       parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
    }
    
    return self;
}

- (void) exec
{
    [self execChildren];
}

/*
 This method should not be called
 Unless in the future, variable are passed already to the root node.
 */
- (void) exec:(NSMutableDictionary*)aVariables
{
    [self execChildren:aVariables];
}

- (BOOL) isRoot
{
    return TRUE;
}

- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    info = [info stringByAppendingFormat:@"Root%@", [super info:aDepth]];
    
    return info;
}

@end
