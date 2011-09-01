//
//  RulesXmlHandler.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "SettingsXmlHandler.h"
#import "RootNode.h"
#import "ActionNode.h"
#import "StorageNode.h"
#import "EmotionNode.h"
#import "ConditionNode.h"
#import "ConditionPerceptionNode.h"
#import "ConditionEmotionNode.h"
#import "ConditionDataMiningNode.h"
#import "ConditionVariableNode.h"
#import "DataMiningNode.h"

#import "CnotiMind.h"
#import "Brain.h"

@implementation SettingsXmlHandler

@synthesize rootNode = _rootNode;
@synthesize currentNode = _currentNode;

- (id)init
{
    self = [super init];
    if (self) {
        
        _rootNode = NULL;
        _currentNode = NULL;
//        _parentNode = NULL;
        _line = 0;
        
    }
    return self;
}

- (id)initWithBrain:(Brain*)aBrain
{
    self = [super init];
    if (self) {

        _rootNode = NULL;
        _currentNode = NULL;
//        _parentNode = NULL;
        _brain = aBrain;
        _line = 0;
        
        _insidePerception = false;
        _insideAction = false;
        _insideEmotion = false;
        _insideValue = false;
        
        _needValues = false;
        
		_elementType = [[NSString alloc] initWithFormat:@""""];
		TYPE = [[NSString alloc] initWithFormat:@"type"];
		TYPE_INT = [[NSString alloc] initWithFormat:@"int"];
		TYPE_STRING = [[NSString alloc] initWithFormat:@"string"];
		TYPE_VALUES = [[NSString alloc] initWithFormat:@"values"];
		NAME = [[NSString alloc] initWithFormat:@"name"];
    }
    return self;
}


- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts
{
    _line++;
    
    if( ![aQName caseInsensitiveCompare:@"Settings"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Perception"] )
    {
        return [self elementPerception:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Action"] )
    {
        return [self elementAction:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Emotion"] )
    {
        return [self elementEmotion:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Value"] )
    {        
        // Test if it an element values appears, but it not child
        // from Emotion, Action or Perception element
        if( !_insidePerception && !_insideAction && !_insideEmotion )
        {
            return false;
        }
        // Test if it is already inside a Value element, it shouldn't have another child Value element
        if( _insideValue )
        {
            return false;
        }
        _insideValue = true;
        return true;
    }
    
    DLog(@"[RulesXmlHandler::startElement] Invalid element: %@",aQName);
    
    return false;
}

/*
 When an element is closed the currentNode and parentNode are updated
*/
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName
{
    
    if( ![aQName caseInsensitiveCompare:@"Settings"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Perception"] )
    {
        return [self endElementPerception];
    }
    if( ![aQName caseInsensitiveCompare:@"Action"] )
    {
        return [self endElementAction];
    }
    if( ![aQName caseInsensitiveCompare:@"Emotion"] )
    {
        return [self endElementEmotion];
    }
    if( ![aQName caseInsensitiveCompare:@"Value"] )
    {        
        _insideValue = false;
        return true;
    }
    
    DLog(@"[RulesXmlHandler::endElement] Invalid element: %@",aQName);
    
    return false;

}



/**
 TODO
 Not sure if it should have support for possible values for the elements
 */
- (BOOL) characters:(NSString*)aCharacter
{
    if( _insideValue && (_insidePerception || _insideAction || _insideEmotion) )
    {
        //_possibleValues.append( ch );
    }
    return true;    
}


- (BOOL) elementPerception:(GDataXMLElement*)atts
{

    return false;    
}


- (BOOL) elementAction:(GDataXMLElement*)atts
{

    return false;    
}

- (BOOL) elementEmotion:(GDataXMLElement*)atts
{

    return false;
}

- (BOOL) endElementPerception
{

    return false;
}


- (BOOL) endElementAction
{

    return false;    
}


- (BOOL) endElementEmotion
{

    return false;
}


@end
