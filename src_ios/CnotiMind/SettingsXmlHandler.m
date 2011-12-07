//
//  RulesXmlHandler.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
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
        _line = 0;
        _emotionAttributes = [[NSMutableArray alloc] init];
        
    }
    return self;
}

- (id)initWithBrain:(Brain*)aBrain
{
    self = [super init];
    if (self) {

        _rootNode = NULL;
        _currentNode = NULL;
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
        
        _emotionAttributes = [[NSMutableArray alloc] init];

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
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
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
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
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
    // Test if it inside another element
    if( _insidePerception || _insideAction || _insideEmotion )
    {
        return false;
    }
    // Check it it need values for the perception
//    _needValues = ![[atts valueForKey:TYPE] caseInsensitiveCompare:TYPE_VALUES];
    [_possibleValues removeAllObjects];
    
    // Get the perception name
    _elementName = [atts valueForKey:NAME];
                    
    if([_elementName length]==0)
    {
        return false;
    }
    
    _insidePerception = true;
    
    return true;  
}



- (BOOL) elementAction:(GDataXMLElement*)atts
{
    // Test if it inside another element
    if( _insidePerception || _insideAction || _insideEmotion )
    {
        return false;
    }
    // Check it it need values for the perception
//    _needValues = ![[atts valueForKey:TYPE] caseInsensitiveCompare:TYPE_VALUES];
    [_possibleValues removeAllObjects];
    
    // Get the action name
    _elementName = [atts valueForKey:NAME];
    
    if([_elementName length]==0)
    {
        return false;
    }
    
    _insideAction = true;
    
    return true;    
}

- (BOOL) elementEmotion:(GDataXMLElement*)atts
{

    // Test if it inside another element
    if( _insidePerception || _insideAction || _insideEmotion )
    {
        return false;
    }
    
    // Get the emotion name
    _elementName = [[atts attributeForName:@"name"] stringValue];

    if([_elementName length]==0)
    {
        return false;
    }
    
    // Test if it has all the attributes required for the emotions
    if( [atts attributeForName:@"value"] != nil &&
       [atts attributeForName:@"max"] != nil &&
       [atts attributeForName:@"min"] != nil )
    {
        int i;
        NSNumber* num;
        [_emotionAttributes removeAllObjects];
        
        
        if ([CnotiMind isNumeric: [[atts attributeForName:@"value"] stringValue]]) {
            i = [[[atts attributeForName:@"value"] stringValue] intValue];
        }
        else {
            DLog("[SettingsXmlHandler::elementEmotion] Invalid attribute value: value = %d", i);
            return false;
        }
        
        num = [[NSNumber alloc] initWithInt:i];
        [_emotionAttributes addObject:num];
        
        
        if ([CnotiMind isNumeric: [[atts attributeForName:@"max"] stringValue]]) {
            i = [[[atts attributeForName:@"max"] stringValue] intValue];
        }
        else {
            DLog("[SettingsXmlHandler::elementEmotion] Invalid attribute value: max = %d", i);
            return false;
        }
        num = [[NSNumber alloc] initWithInt:i];
        [_emotionAttributes addObject:num];
        
        
        if ([CnotiMind isNumeric: [[atts attributeForName:@"min"] stringValue]]) {
            i = [[[atts attributeForName:@"min"] stringValue] intValue];
        }
        else {
            DLog("[SettingsXmlHandler::elementEmotion] Invalid attribute value: min = %d", i);
            return false;
        }
        
        num = [[NSNumber alloc] initWithInt:i];
        [_emotionAttributes addObject:num];
        

        for (NSNumber* num in _emotionAttributes) {
            DLog(@"...%@", num)
        }
        DLog(@"tata: %@", _emotionAttributes);
    }
    else
    {
        return false;
    }
    
    _insideEmotion = true;
    return true;

}




- (BOOL) endElementPerception
{
    if( _insidePerception )
    {
        [_brain addValidPerception:_elementName];
        _insidePerception = false;
        return true;
    }
    return false;
}


- (BOOL) endElementAction
{
    if( _insideAction )
    {
        [_brain addValidAction:_elementName];
        _insideAction = false;
        return true;
    }
    return false; 
}


- (BOOL) endElementEmotion
{

    if( _insideEmotion )
    {
        Emotion* e = [[Emotion alloc] initWithNameAndValueAndMaxAndMin:_elementName 
                                                                 value:[[_emotionAttributes objectAtIndex:0] floatValue] 
                                                                   max:[[_emotionAttributes objectAtIndex:1] floatValue] 
                                                                   min:[[_emotionAttributes objectAtIndex:2] floatValue]];
        [_brain addEmotion:e];
        _insideEmotion = false;
        return true;
    }
//    TODO
    return false;
}


@end
