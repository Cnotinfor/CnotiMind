//
//  RulesXmlHandler.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#ifndef RULESXMLHANDLER_H
#define RULESXMLHANDLER_H

@class CnotiMind;
@class RuleNode;
@class RootNode;
@class ActionNode;
@class StorageNode;
@class EmotionNode;
@class ConditionNode;
@class ConditionPerceptionNode;
@class ConditionEmotionNode;
@class ConditionDataMiningNode;
@class Brain;

#import "GDataXMLNode.h"

@interface RulesXmlHandler : NSObject
{
    RuleNode* _rootNode;
    RuleNode* _currentNode;
    RuleNode* _parentNode;
    Brain* _brain;
    
    RuleNode* _parentObject; // Parent of the RootNode
    
    int _line;
}

@property (readwrite, retain) RuleNode* rootNode;
@property (readwrite, retain) RuleNode* currentNode;

- (id)init;
- (id)initWithBrain:(Brain*)aBrain;

- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts;
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName;

//RuleNode* rootNode() const;
//int line() const;

- (BOOL) createRootNode:(GDataXMLElement*)atts;
- (BOOL) createActionNode:(GDataXMLElement*)atts;
- (BOOL) createStorageNode:(GDataXMLElement*)atts;
- (BOOL) createEmotionNode:(GDataXMLElement*)atts;
- (BOOL) createDataMiningNode:(GDataXMLElement*)atts;
- (BOOL) createConditionNode:(GDataXMLElement*)atts;
- (BOOL) createConditionPerceptionNode:(GDataXMLElement*)atts;
- (BOOL) createConditionVariableNode:(GDataXMLElement*)atts;
- (BOOL) createConditionPropertyNode:(GDataXMLElement*)atts;
- (BOOL) createConditionEmotionNode:(GDataXMLElement*)atts;
- (BOOL) createConditionDataMiningNode:(GDataXMLElement*)atts;
- (BOOL) createMathOperationNode:(GDataXMLElement*)atts;
- (BOOL) createPropertyNode:(GDataXMLElement*)atts;
- (BOOL) createDeleteNode:(GDataXMLElement*)atts;
- (BOOL) createClearMemoryNode:(GDataXMLElement*)atts;
- (BOOL) createRandomNode:(GDataXMLElement*)atts;

@end
#endif // RULESXMLHANDLER_H
