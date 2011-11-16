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
//      _parentNode = NULL;
        _brain = aBrain;
        _line = 0;
        
        _insideCrutch = false;
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
    if( ![aQName caseInsensitiveCompare:@"Crutches"] )
    {
        return true;
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


- (BOOL) elementCrutch:(GDataXMLElement*)atts
{
    
    // Get the emotion name
    _elementName = [[atts attributeForName:@"name"] stringValue];

    if([_elementName length]==0)
    {
        return false;
    }
    
    // Test if it has all the attributes required for the crutches
    if( [atts attributeForName:@"name"] != nil &&
       [atts attributeForName:@"action"] != nil &&
       [atts attributeForName:@"emotion"] != nil &&
       [atts attributeForName:@"order"] != nil )
    {
        [_crutchAttributes removeAllObjects];
        
        NSString* name = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"name"] stringValue]];
        NSString* action = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"action"] stringValue]];
        NSString* emotion = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"emotion"] stringValue]];
        
        NSString* min = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"min"] stringValue]];
        NSString* max = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"max"] stringValue]];
        
        NSString* orderString = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"order"] stringValue]];
        
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
                                                                               order:order];
        
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
        Emotion* e = [[Emotion alloc] initWithNameAndValueAndMaxAndMin:_elementName value:[[_crutchAttributes objectAtIndex:0] floatValue] max:[[_crutchAttributes objectAtIndex:1] floatValue] min:[[_crutchAttributes objectAtIndex:2] floatValue]];
        [_brain addEmotion:e];
        _insideCrutch = false;
        return true;
    }
//    TODO
    return false;
}


@end
