//
//  RootNode.m
//  CnotiMind
//

#import "RootNode.h"

@implementation RootNode

- (id) initWithBrainAndParent:(Brain*)aBrain parent:(id)aParent
{
    if (self == [self initWithKeyAndValueAndBrainAndParent:@"Root" value:@"" brain:aBrain parent:aParent]) {
        
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
//    NSString* space = [self space:aDepth];
    DLog(@"RootNode: info: %@", [super info:1]);
    info = [info stringByAppendingFormat:@"Root%@", [super info:aDepth]];
    
    return info;
}

@end
