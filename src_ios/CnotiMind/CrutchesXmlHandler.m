//
//  RulesXmlHandler.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import "CrutchesXmlHandler.h"
#import "RootNode.h"

#import "Crutch.h"

#import "CnotiMind.h"
#import "Brain.h"

@implementation CrutchesXmlHandler

@synthesize rootNode = _rootNode;
@synthesize currentNode = _currentNode;

- (id)init
{
    self = [super init];
    if (self) {
        
        _rootNode = NULL;
        _currentNode = NULL;
        _line = 0;
        
        _insideCrutch = false;
        _needValues = false;
        
        _currentAction = [[NSString alloc] initWithString:@""];
        _currentEmotion = [[NSString alloc] initWithString:@""];
        _currentEmotionMin = [[NSString alloc] initWithString:@""];
        _currentEmotionMax = [[NSString alloc] initWithString:@""];
        _currentProperties = [[NSMutableDictionary alloc] init];
        _currentOrder = [[NSString alloc] initWithString:@""];
        
        _elementType = [[NSString alloc] initWithFormat:@""""];
		TYPE = [[NSString alloc] initWithFormat:@"type"];
		TYPE_INT = [[NSString alloc] initWithFormat:@"int"];
		TYPE_STRING = [[NSString alloc] initWithFormat:@"string"];
		TYPE_VALUES = [[NSString alloc] initWithFormat:@"values"];
		NAME = [[NSString alloc] initWithFormat:@"name"];
    }
    return self;
}

- (id)initWithBrain:(Brain*)aBrain
{
    self = [self init];
    if (self) {
        _brain = aBrain;                
    }
    return self;
}


- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts
{
    _line++;
    if( ![aQName caseInsensitiveCompare:@"Crutches"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Action"] )
    {
        return [self elementAction:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Emotion"] )
    {
        return [self elementEmotion:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Property"] )
    {
        return [self elementProperty:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Order"] )
    {
        return [self elementOrder:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Crutch"] )
    {
        return [self elementCrutch:atts];
    }
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
        return true;
    }
    
    DLog(@"[CrutchesXmlHandler::startElement] Invalid element: %@",aQName);
    
    return false;
}

/*
 When an element is closed the currentNode and parentNode are updated
*/
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName
{
    
    if( ![aQName caseInsensitiveCompare:@"Crutches"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Action"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Emotion"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Property"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Order"] )
    {
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"Crutch"] )
    {
        return [self endElementCrutch];
    }
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
        return true;
    }
    
    DLog(@"[CrutchesXmlHandler::endElement] Invalid element: %@",aQName);
    
    return false;

}

- (BOOL) elementAction:(GDataXMLElement*)atts
{
    if( [atts attributeForName:@"name"] != nil ) {
        NSString* name = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"name"] stringValue]];
        _currentAction = name;
    }
    else {
        return false;
    }
    
    return true;
}


- (BOOL) elementEmotion:(GDataXMLElement*)atts
{
    // clear all the currentProperties
    [_currentProperties removeAllObjects];
    
    if( [atts attributeForName:@"name"] != nil &&
        [atts attributeForName:@"min"] != nil &&
        [atts attributeForName:@"max"] != nil ) {
        NSString* name = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"name"] stringValue]];
        NSString* min = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"min"] stringValue]];
        NSString* max = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"max"] stringValue]];

        _currentEmotion = name;
        _currentEmotionMin = min;
        _currentEmotionMax = max;
    }
    else {
        return false;
    }
    
    return true; 
}


- (BOOL) elementProperty:(GDataXMLElement*)atts
{
    if( [atts attributeForName:@"name"] != nil &&
       [atts attributeForName:@"value"] != nil ) {
        NSString* name = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"name"] stringValue]];
        NSString* value = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"value"] stringValue]];
        [_currentProperties setValue:value forKey:name];
        DLog(@"elementProperty: name: %@ value: %@", name, value);
    }
    else {
        return false;
    }
    
    return true;     
}


- (BOOL) elementOrder:(GDataXMLElement*)atts
{
    if( [atts attributeForName:@"value"] != nil ) {
        NSString* value = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"value"] stringValue]];
        _currentOrder = value;
    }
    else {
        return false;
    }
    
    return true; 
}


- (BOOL) elementCrutch:(GDataXMLElement*)atts
{
    // Get the emotion name
    _elementName = [[atts attributeForName:@"name"] stringValue];

    if([_elementName length]==0)
    {
        return false;
    }
    
    // Test if it has all the attributes required for the crutches
    if( [atts attributeForName:@"name"] )
    {
        NSString* name = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"name"] stringValue]];
        NSString* action = _currentAction;
        NSString* emotion = _currentEmotion;
        
        NSString* min = _currentEmotionMin;
        NSString* max = _currentEmotionMax;
        
        NSString* orderString = _currentOrder;
        
        enum EnumCrutchOrder order;
        
        if ( ![orderString caseInsensitiveCompare:@"Begin"] ) {
            order = CrutchOrder_BEGIN;
        }
        else if ( ![orderString caseInsensitiveCompare:@"Begin And End"] ) {
            order = CrutchOrder_BEGIN_AND_END;
        }
        else {
            order = CrutchOrder_END;
        }
        
        Crutch* crutch = [[Crutch alloc] initWithNameAndActionAndEnforcementAndOrder:name 
                                                                              action:action 
                                                                             emotion:emotion 
                                                                                 min:min
                                                                                 max:max
                                                                               order:order
                                                                          properties:_currentProperties];
        [_brain addCrutch:crutch];
        
        DLog(@"Crutch added: %@, action: %@, emotion: %@, min: %@, max: %@ order: %@.", name, action, emotion, min, max, orderString);
        [crutch release];
    }
    else
    {
        return false;
    }
    
    _insideCrutch = true;
    return true;
}


- (BOOL) endElementCrutch
{
    if( _insideCrutch )
    {
        _insideCrutch = false;
        return true;
    }
    return false;
}

- (void)dealloc {
    [_currentAction release];
    [_currentEmotion release];
    [_currentEmotionMin release];
    [_currentEmotionMax release];
    [_currentProperties release];
    [_currentOrder release];
    
    [super dealloc];
}

@end
