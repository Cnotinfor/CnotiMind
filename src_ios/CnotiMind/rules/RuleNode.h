//
//  RuleNode.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/26.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

//  Copied from CCNode
#import <Availability.h>
//  end Copied from CCNode

#import "Node.h"

@class Brain;

//enum RuleNodeType
//{
//    // Condition,
//    // Action,
//    // Storage,
//    // Emotion,
//    // Root,
//    // DataMining,
//    // Event
//};

@interface RuleNode : NSObject {
    
    // array of children
	NSMutableArray *children_;
    
    // weakref to parent
	RuleNode *parent_;
	
	// a tag. any number you want to assign to the node
	NSInteger tag_;
    
	// user data field
	void *userData_;
    
    Brain* _brain;
    
}

/** Array of children */
@property(nonatomic,readonly) NSArray *children;
/** A weak reference to the parent */
@property(nonatomic,readwrite,assign) RuleNode* parent;
/** A custom user data pointer */
@property(nonatomic,readwrite,assign) void *userData;


@property(retain,readonly) Brain *brain;



// initializators
/** allocates and initializes a node.
 The node will be created as "autorelease".
 */
+(id) node;
/** initializes the node */
-(id) init;
-(id) initWithParent: (RuleNode*)aParent;
//-(id) initWithKeyAndValueAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue brain:(Brain*)aBrain parent:(id)aParent;
-(id) initWithBrainAndParent: (Brain*)aBrain parent:(id)aParent;


-(void) addChild: (RuleNode*)node;
-(void) insertChild:(RuleNode*)child;

-(void) removeFromParentAndCleanup:(BOOL)cleanup; 
-(void) removeChild: (RuleNode*)child cleanup:(BOOL)cleanup;
-(void) detachChild:(RuleNode *)child cleanup:(BOOL)doCleanup;

/** recursive method that visit its children */
//-(void) visit;
- (void) execChildren;
- (void) execChildren:(NSMutableDictionary*)aVariables;
- (void) exec;
- (void) exec:(NSMutableDictionary*)aVariables;

- (NSString*)variableToValue:(NSString*)aValue variables:(NSDictionary*)aVariables;

- (NSString*) info:(int)aDepth;


- (void) tagsToValue:(NSString**)aValue variables:(NSMutableDictionary**)aVariables;

- (NSString*) space:(int)aDepth;

- (void) childrenAlloc;

- (BOOL) isRoot;

- (void) dealloc;

- (BOOL)isNumeric:(NSString*)s;

- (NSString *)captureRegex:(NSString *)pattern;


- (NSString *)valueForKeyInsensitiveSearch:(NSMutableDictionary*)aDictionary key:(NSString*)aKey;

@end
