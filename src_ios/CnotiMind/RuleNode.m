//
//  RuleNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "RuleNode.h"
#import "Brain.h"

@implementation RuleNode

@synthesize children = children_;
@synthesize parent = parent_;
@synthesize userData = userData_;

@synthesize brain = brain_;

#pragma mark Init

+(id) node
{
	return [[[self alloc] init] autorelease];
}


// TODO
-(id) init
{
	if ((self=[super init]) ) {
		
		// children (lazy allocs)
		children_ = nil;
        if( ! children_ )
            [self childrenAlloc];
		
		// userData is always inited as nil
		userData_ = nil;
        
		//initialize parent to nil
		parent_ = nil;
	}
	
	return self;
}


-(id) initWithParent: (RuleNode*)aParent
{
	if ((self=[super init]) ) {
		
		// children (lazy allocs)
		children_ = nil;
        if( ! children_ )
            [self childrenAlloc];
		
		// userData is always inited as nil
		userData_ = nil;
        
		//initialize parent to nil
		parent_ = aParent;
        
        if (aParent != nil) {
            [aParent insertChild:self];
        }
        
        DLog(@"%@", parent_);
	}
	
	return self;
}


//- (id) initWithKeyAndValueAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue brain:(Brain*)aBrain parent:(id)aParent
//{
//
//    if ((self=[super initWithKeyAndValue:aKey value:aValue])) {
//        [self initWithParent:aParent];
//        //  TODO
//        _brain = aBrain;
//    }
//    
//    return self;
//}

- (id) initWithBrainAndParent:(Brain*)aBrain parent:(id)aParent
{
    if (self = [super init]) {
        [self initWithParent:aParent];
        _brain = aBrain;        
    }
    
    return self;
}

#pragma mark Add and remove

/* "add" logic MUST only be on this method
 * If a class want's to extend the 'addChild' behaviour it only needs
 * to override this method
 */
-(void) addChild: (RuleNode*) child
{	
	NSAssert( child != nil, @"Argument must be non-nil");
	NSAssert( child.parent == nil, @"child already added. It can't be added again");
	
	if( ! children_ )
		[self childrenAlloc];
	
	[self insertChild:child];
	
    //	child.tag = aTag;
	
	[child setParent: self];
	
    //	if( isRunning_ ) {
    //		[child onEnter];
    //		[child onEnterTransitionDidFinish];
    //	}
}


// helper used by reorderChild & add
-(void) insertChild:(RuleNode*)child
{	
	[children_ addObject:child];
}


-(void) removeFromParentAndCleanup:(BOOL)cleanup
{
	[parent_ removeChild:self cleanup:cleanup];
}


/* "remove" logic MUST only be on this method
 * If a class want's to extend the 'removeChild' behavior it only needs
 * to override this method
 */
-(void) removeChild: (RuleNode*)child cleanup:(BOOL)cleanup
{
	// explicit nil handling
	if (child == nil)
		return;
	
	if ( [children_ containsObject:child] )
		[self detachChild:child cleanup:cleanup];
}


-(void) detachChild:(RuleNode *)child cleanup:(BOOL)doCleanup
{
	// IMPORTANT:
	//  -1st do onExit
	//  -2nd cleanup
    //	if (isRunning_)
    //		[child onExit];
	
	// If you don't do cleanup, the child's actions will not get removed and the
	// its scheduledSelectors_ dict will not get released!
    //	if (doCleanup)
    //		[child cleanup];
	
	// set parent nil at the end (issue #476)
	[child setParent:nil];
	
	[children_ removeObject:child];
}


#pragma mark Execute tree


-(void) execChildren
{
    NSEnumerator* e = [children_ objectEnumerator];

    id object;
    while (object = [e nextObject]) {
        [object exec];
    }
}


- (void) execChildren:(NSMutableDictionary*)aVariables
{    
    NSEnumerator* e = [children_ objectEnumerator];
    id object;
    
    while (object = [e nextObject]) {
        RuleNode* node = (RuleNode*)object;
        [node exec: aVariables];
    }
}


// virtual method
- (void) exec
{

}


// virtual method
- (void) exec:(NSMutableDictionary*)aVariables
{

}



/*
 Check if there is a variable in the value parameter. 
 If it is a variable try to get the value from the variables.
 Variables are betweeen square brackets [].
 If the variable is not found, it return an empty QString
 */
- (NSString*)variableToValue:(NSString*)aValue variables:(NSDictionary*)aVariables
{

    NSString* empty = [NSString stringWithFormat:@""];

    // A variable is between square brackets
    if (([aValue characterAtIndex:0] == '[') && ([aValue characterAtIndex:([aValue length]-1)]==']') ){
        
        NSEnumerator* eVariables = [aVariables objectEnumerator];
        
        NSDictionary* objectVariable;
        
        while (objectVariable = [eVariables nextObject]) {
            if (![[objectVariable valueForKey:aValue] caseInsensitiveCompare:aValue]) {
                return [objectVariable valueForKey:aValue];
            }
        }
    }

    return empty;
}


/*
 Writes the information about the node and child nodes
 Depth parameter is to be used internally to beautify the output
 */
- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
//    NSString* space = [self space:aDepth];
    
    NSEnumerator* eChildren = [children_ objectEnumerator];
    
    Node* objectNode;
    while (objectNode = [eChildren nextObject]) {
        info = [info stringByAppendingFormat:@"%@", [objectNode info:aDepth + 1]];
    }
    
    return info;
}

/*
 Check if in the value string there are variable or property tags
 
 If it is a variable tag try to get the value from the variables lists.
 
 Variables tags are betweeen square brackets [].
 Property tags are between curl brackets {}.
 
 If the variable/property tag is not found, it is replaced by an empty string.
 */

// TODO
- (void) tagsToValue:(NSString**)aValue variables:(NSMutableDictionary**)aVariables
{
    NSString* empty = [NSString stringWithFormat:@""];
    
    DLog(@"%@", *aValue);
    
    // VARIABLES
    NSRegularExpression *regex_variables_tags = [NSRegularExpression regularExpressionWithPattern:@"(\\[[a-zA-Z0-9_\\- \\.]+\\])"
                                                                           options:NSRegularExpressionCaseInsensitive
                                                                             error:nil];
    // Search for variable value is between square brackets
    int pos = 0;
    
    while( (pos = [regex_variables_tags firstMatchInString:*aValue options:0 range:NSMakeRange(0, [*aValue length])].range.location ) != 0 )
    {
        NSRange rangeOfFirstMatch = [regex_variables_tags rangeOfFirstMatchInString:*aValue options:0 range:NSMakeRange(0, [*aValue length])];
        NSString* var = [*aValue substringWithRange:rangeOfFirstMatch];
        
        DLog(@"var: %@", var);
        DLog(@"aVariables: %@", *aVariables);
        
        NSString* valueFromKey = [[NSString alloc] initWithFormat:@"%@", [*aVariables valueForKey:var]];
        
        DLog(@"valueFromKey: %@", valueFromKey);

        
        if ([valueFromKey length]>0) {
            // found it, replace by the variable tag, by the variable value
            
            *aValue = [*aValue stringByReplacingOccurrencesOfString:var
                                                         withString:valueFromKey];
            pos += [valueFromKey length];
        }
        else {
            // not found replace by an empty string
            *aValue = [*aValue stringByReplacingOccurrencesOfString:var
                                                         withString:empty];
        }
        DLog(@"aValue: %@", *aValue);
    }
    
    // PROPERTIES - TODO
    NSRegularExpression *regex_properties_tags = [NSRegularExpression regularExpressionWithPattern:@"\\{([a-zA-Z0-9_\\- \\.]+)\\}"
                                                                                          options:NSRegularExpressionCaseInsensitive
                                                                                            error:nil];
    // Search for variable value is between curl brackets
    pos = 0;    
    
    while( (pos = [regex_properties_tags firstMatchInString:*aValue options:0 range:NSMakeRange(0, [*aValue length])].range.length ) != 0 )
    {
        NSRange rangeOfFirstMatch = [regex_properties_tags rangeOfFirstMatchInString:*aValue options:0 range:NSMakeRange(0, [*aValue length])];
        
        NSString* var = [*aValue substringWithRange:rangeOfFirstMatch];
        
        DLog(@"var: %@", var);
        DLog(@"aVariables: %@", *aVariables);
        NSString* valueFromKey = [[NSString alloc] initWithString: [*aVariables valueForKey:var]];
        DLog(@"valueFromKey: %@", valueFromKey);
        
        if ([valueFromKey length]>0) {
            
            NSString* var2 = [NSString stringWithFormat:@""];
            var2 = [NSString stringWithFormat:@"{%@}",var];
            
            *aValue = [*aValue stringByReplacingOccurrencesOfString:var2
                                                         withString:valueFromKey];
            pos += [valueFromKey length];
        }
        else {
            // not found replace by an empty string
            *aValue = [*aValue stringByReplacingOccurrencesOfString:var
                                                         withString:empty];
            
        }
        DLog(@"aValue: %@", *aValue);
    }
}

- (NSString*) space:(int)aDepth
{
    NSString* space = [NSString stringWithFormat:@"\n"];
    for( int i=0; i <= aDepth; i++ )
    {
        space = [space stringByAppendingFormat:@"---\t"];
    }
    
    return space;
}


#pragma mark CCNode Composition

-(void) childrenAlloc
{
	children_ = [[NSMutableArray alloc] init];
}


#pragma mark Extra functions


- (BOOL) isRoot
{
    return (parent_ == nil);
}

- (BOOL)isNumeric:(NSString*)s
{
    DLog(@"%@", s);
    NSScanner *sc = [NSScanner scannerWithString: s];
    // We can pass NULL because we don't actually need the value to test
    // for if the string is numeric. This is allowable.
    if ( [sc scanFloat:NULL] )
    {
        // Ensure nothing left in scanner so that "42foo" is not accepted.
        // ("42" would be consumed by scanFloat above leaving "foo".)
        return [sc isAtEnd];
    }
    // Couldn't even scan a float :(
    return NO;
}

#pragma mark Cleanup

- (void) dealloc
{
	// children
    
    for (RuleNode* child in children_) {
        child.parent = nil;
    }
	
	[children_ release];
	
	[super dealloc];
}

- (NSString *)captureRegex:(NSString *)pattern {
    
    NSError *error = nil;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern options:NSRegularExpressionDotMatchesLineSeparators error:&error];
    if(regex == nil) {
        NSLog(@"-- %@", error);
        return nil;
    }
    
    NSRange rangeOfFirstMatch = [regex rangeOfFirstMatchInString:pattern options:0 range:NSMakeRange(0, [pattern length])];
    if(rangeOfFirstMatch.location == NSNotFound) return nil;
    
    return [pattern substringWithRange:rangeOfFirstMatch];
}

@end
