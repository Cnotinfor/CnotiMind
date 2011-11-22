//
//  DisableNode.m
//  LittleMozart
//

#import "DisableNode.h"
#import "Brain.h"

@implementation DisableNode


- (id) initWithNameAndValueAndBrainAndParent:(NSString*)aName 
                                       value:(NSString*)aValue
                                       brain:(Brain*)aBrain 
                                      parent:(id)aParent
{
    if (self = [super initWithBrainAndParent:aBrain parent:aParent]) {
        _nodeName = (aName == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aName];
        NSString* _value = (aValue == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aValue];
        
        if ( [_value length] == 0 ) {
            _toDisable = true;
        }
        else if ( ![_value caseInsensitiveCompare:@"false"] ) {
            _toDisable = false;
        }
        else {
            _toDisable = true;
        }
        
        DLog(@"init DisableNode: %@ %@ %d", _nodeName, _value, _toDisable);
    }
    
    return self;
}


- (void) exec 
{
    if (_toDisable) {
        [_brain deactivateTask:_nodeName];
    }
    else {
        [_brain activateTask:_nodeName];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables 
{
    [self exec];

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Disable (%@) value=%d", space, _nodeName, _toDisable];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (void) dealloc
{
    [_nodeName release];
    [super dealloc];
}


@end
