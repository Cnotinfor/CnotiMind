//
//  SETTINGSXmlHandler.h
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#ifndef SETTINGSXMLHANDLER_H
#define SETTINGSXMLHANDLER_H

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

@interface SettingsXmlHandler : NSObject
{
    
    Brain* _brain;
    
    bool _insidePerception;
    bool _insideAction;
    bool _insideEmotion;
    bool _insideValue;
    NSString* _elementType;
    NSString* _elementName;
    bool _needValues;
    
    NSMutableArray* _possibleValues;
    NSMutableArray* _emotionAttributes;
    
    // Constants
    NSString* TYPE;
    NSString* TYPE_INT;
    NSString* TYPE_STRING;
    NSString* TYPE_VALUES;
    
    NSString* NAME;
    
    RuleNode* _parentObject; // Parent of the RootNode
    
    RuleNode* _rootNode;
    RuleNode* _currentNode;
    
    int _line;
}

@property (readwrite, retain) RuleNode* rootNode;
@property (readwrite, retain) RuleNode* currentNode;

- (id)init;
- (id)initWithBrain:(Brain*)aBrain;

- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts;
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName;

- (BOOL) characters:(NSString*)aCharacter;

//RuleNode* rootNode() const;
//int line() const;

- (BOOL) elementPerception:(GDataXMLElement*)atts;
- (BOOL) elementAction:(GDataXMLElement*)atts;
- (BOOL) elementEmotion:(GDataXMLElement*)atts;

- (BOOL) endElementPerception;
- (BOOL) endElementAction;
- (BOOL) endElementEmotion;

@end
#endif // SETTINGSXMLHANDLER_H
