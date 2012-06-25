//
//  SETTINGSXmlHandler.h
//  SingleEmotion
//

#ifndef CRUTCHESXMLHANDLER_H
#define CRUTCHESXMLHANDLER_H

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

@interface CrutchesXmlHandler : NSObject
{    
    Brain* _brain;

    bool _insideCrutch;
    NSString* _elementType;
    NSString* _elementName;
    bool _needValues;
    
    NSMutableArray* _possibleValues;
    NSMutableArray* _crutchAttributes;
    
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
    
    NSString* _currentAction;
    NSString* _currentEmotion;
    NSString* _currentEmotionMin;
    NSString* _currentEmotionMax;
    NSMutableDictionary* _currentProperties;
    NSString* _currentOrder;
}

@property (readwrite, retain) RuleNode* rootNode;
@property (readwrite, retain) RuleNode* currentNode;

- (id)init;
- (id)initWithBrain:(Brain*)aBrain;

- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts;
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName;

- (BOOL) elementAction:(GDataXMLElement*)atts;
- (BOOL) elementEmotion:(GDataXMLElement*)atts;
- (BOOL) elementProperty:(GDataXMLElement*)atts;
- (BOOL) elementOrder:(GDataXMLElement*)atts;
- (BOOL) elementCrutch:(GDataXMLElement*)atts;
- (BOOL) endElementCrutch;

- (void)dealloc; 

@end
#endif // CRUTCHESXMLHANDLER_H