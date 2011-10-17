//
//  RulesXmlHandler.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 8/17/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "RulesXmlHandler.h"
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

#import "MathOperationNode.h"
#import "PropertyNode.h"
#import "DeleteNode.h"
#import "ClearMemoryNode.h"
#import "RandomNode.h"

#import "CnotiMind.h"
#import "Brain.h"

@implementation RulesXmlHandler

@synthesize rootNode = _rootNode;
@synthesize currentNode = _currentNode;

- (id)init
{
    self = [super init];
    if (self) {

        // Initialization code here.
        _rootNode = NULL;
        _currentNode = NULL;
        _parentNode = NULL;
//        _brain = [[Brain alloc] init];
        _parentObject = [[RuleNode alloc] init];
        _line = 0;
    }
    return self;
}

- (id)initWithBrain:(Brain*)aBrain
{
    self = [super init];
    if (self) {
        // Initialization code here.
        _rootNode = NULL;
        _currentNode = NULL;
        _parentNode = NULL;
        _brain = aBrain;
        _parentObject = [[RuleNode alloc] init];
        _line = 0;

    }
    return self;
}


- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts
{
    _line++;
    
    if( ![aQName caseInsensitiveCompare:@"Rules"] )
    {
        return [self createRootNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Condition"] )
    {
        return [self createConditionNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Action"] )
    {
        return [self createActionNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Storage"] )
    {
        return [self createStorageNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Emotion"] )
    {
        return [self createEmotionNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"DataMining"] )
    {
        return [self createDataMiningNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"MathOperation"] )
    {
        return [self createMathOperationNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Property"] )
    {
        return [self createPropertyNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Delete"] )
    {
        return [self createDeleteNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"ClearMemory"] )
    {
        return [self createClearMemoryNode:atts];
    }
    if( ![aQName caseInsensitiveCompare:@"Random"] )
    {
        return [self createRandomNode:atts];
    }
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
        return true;
    }
    if (![aQName caseInsensitiveCompare:@"StorageCopy"])
    {
        return true;
    }
    if (![aQName caseInsensitiveCompare:@"text"])
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
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
        return true;
    }
    if (![aQName caseInsensitiveCompare:@"StorageCopy"])
    {
        return true;
    }
    if (![aQName caseInsensitiveCompare:@"text"])
    {
        return true;
    }

    
    if( _rootNode == _currentNode )
    {
        _currentNode = NULL;
        return true;
    }
    
    _currentNode = _parentNode;
    _parentNode = (RuleNode*)_currentNode.parent;
    
    return true;
}


- (BOOL) createRootNode:(GDataXMLElement*)atts
{
    
    // it can only exist 1 root node.
    if( _rootNode != NULL )
    {
        return false;
    }
    
    _rootNode = [[RootNode alloc] initWithBrainAndParent: _brain parent:_parentObject];
    _currentNode = _rootNode;
    
    return true;
}

- (BOOL) createActionNode:(GDataXMLElement*)atts
{
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }

    NSString* name = [[atts attributeForName:@"name"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* probability = [[atts attributeForName:@"probability"] stringValue];
    
    if( [probability length]==0 )
    {
        probability = @"1";
    }
    
    _parentNode = _currentNode;
    _currentNode = [[ActionNode alloc] initWithNameAndValueAndBrainAndParent: name 
                                                                       value:value 
                                                                       brain:_brain 
                                                                      parent:_parentNode];
    
    return true;
}

- (BOOL) createStorageNode:(GDataXMLElement*)atts
{
    
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }
    
    NSString* event = [[atts attributeForName:@"event"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* clear = [[atts attributeForName:@"clear"] stringValue];
    
    NSString* memory = [[atts attributeForName:@"memory"] stringValue];

    enum MemoryType memoryType;
    memoryType = [CnotiMind translateMemoryType: memory];
    
    _parentNode = _currentNode;
    
    
    
    if ( (![clear caseInsensitiveCompare:@"yes"]) && (clear!=nil) ) {
        _currentNode = [[StorageNode alloc] initWithClearAndMemoryAndBrainAndParent:true 
                                                                             memory:memoryType 
                                                                              brain:_brain 
                                                                             parent:_parentNode];
    }
    else {
        _currentNode = [[StorageNode alloc] initWithEventAndValueAndMemoryAndBrainAndParent:event 
                                                                                      value:value 
                                                                                     memory:memoryType 
                                                                                      brain:_brain 
                                                                                     parent:_parentNode];
    }
    
    return true;
    
}

- (BOOL) createEmotionNode:(GDataXMLElement*)atts
{
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }
    
    NSString* emotion = [[atts attributeForName:@"name"] stringValue];
    NSString* value = [[atts attributeForName:@"increment"] stringValue];
    BOOL okMin = [CnotiMind isNumeric: [[atts attributeForName:@"min"] stringValue]];
    double min = [[[atts attributeForName:@"min"] stringValue] floatValue];
    BOOL okMax = [CnotiMind isNumeric: [[atts attributeForName:@"max"] stringValue]];
    double max = [[[atts attributeForName:@"max"] stringValue] floatValue];
        
    if (!okMin) {
        min = INT_MIN;
    }
    if (!okMax) {
        max = INT_MAX;
    }
    _parentNode = _currentNode;
    _currentNode = [[EmotionNode alloc] initWithEmotionAndValueAndMaxAndMinAndBrainAndParent:emotion 
                                                                                       value:value 
                                                                                         max:max 
                                                                                         min:min 
                                                                                       brain:_brain 
                                                                                      parent:_parentNode];
    
    return true;
}

- (BOOL) createDataMiningNode:(GDataXMLElement*)atts
{
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }
    
    NSString* event = [[atts attributeForName:@"event"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* op = [[atts attributeForName:@"operator"] stringValue];
    NSString* opDataMining = [[atts attributeForName:@"operation"] stringValue];
    NSString* variable = [[atts attributeForName:@"variable"] stringValue];
    
    NSString* position = [[atts attributeForName:@"position"] stringValue];
    NSString* memory = [[atts attributeForName:@"memory"] stringValue];

    enum ConditionOperator opType;
    opType = [CnotiMind translateConditionOperator: op];
    
    enum DataMiningOperation opDataMiningType;
    opDataMiningType = [CnotiMind translateDataMiningOperator: opDataMining];
    
    enum MemoryType memoryType;
    memoryType = [CnotiMind translateMemoryType: memory];

    
    _parentNode = _currentNode;
    _currentNode = [[DataMiningNode alloc] initWithEventAndValueAndOperatorAndMemoryAndVariableAndPositionAndBrainAndParent:event 
                                                                                                                      value:value 
                                                                                                                   operator:opDataMiningType 
                                                                                                                     memory:memoryType 
                                                                                                                   variable:variable 
                                                                                                                   position:position 
                                                                                                                      brain:_brain 
                                                                                                                     parent:_parentNode];
    
    return true;
}

- (BOOL) createConditionNode:(GDataXMLElement*)atts
{
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }
    
    NSString* typeCondition = [[atts attributeForName:@"type"] stringValue];

    
    if (![typeCondition caseInsensitiveCompare:@"perception"]) {
        return [self createConditionPerceptionNode:atts];
    }
    else if (![typeCondition caseInsensitiveCompare:@"datamining"]) {
        return [self createConditionDataMiningNode:atts];
    }
    else if (![typeCondition caseInsensitiveCompare:@"emotion"]) {
        return [self createConditionEmotionNode:atts];
    }
    else if (![typeCondition caseInsensitiveCompare:@"variable"]) {
        return [self createConditionVariableNode:atts];
    }
    else if (![typeCondition caseInsensitiveCompare:@"property"]) {
        return [self createConditionPropertyNode:atts];
    }
    
    DLog(@"[RulesXmlHandler::createConditionNode] Invalid condition node type: %@", typeCondition);
    
    return false;    
}


- (BOOL) createConditionPerceptionNode:(GDataXMLElement*)atts
{
    NSString* perception = [[atts attributeForName:@"perception"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* opCondition = [[atts attributeForName:@"operator"] stringValue];

    enum ConditionOperator opConditionType;
    opConditionType = [CnotiMind translateConditionOperator: opCondition];
    
    _parentNode = _currentNode;
    _currentNode = [[ConditionPerceptionNode alloc] initWithPerceptionAndValueAndOperatorAndBrainAndParent:perception 
                                                                                                     value:value 
                                                                                                  operator:opConditionType 
                                                                                                     brain:_brain 
                                                                                                    parent:_parentNode];
    
    return true;
}


- (BOOL) createConditionVariableNode:(GDataXMLElement*)atts
{
    NSString* variable = [[atts attributeForName:@"variable"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* opCondition = [[atts attributeForName:@"operator"] stringValue];
    
    enum ConditionOperator opConditionType;
    opConditionType = [CnotiMind translateConditionOperator: opCondition];
    
    _parentNode = _currentNode;
    _currentNode = [[ConditionVariableNode alloc] initWithVariableAndValueAndOperatorAndBrainAndParent:variable 
                                                                                                 value:value 
                                                                                              operator:opConditionType 
                                                                                                 brain:_brain 
                                                                                                parent:_parentNode];
    
    return true;    
}

- (BOOL) createConditionPropertyNode:(GDataXMLElement*)atts
{
//    TODO
    return false;
}

- (BOOL) createConditionEmotionNode:(GDataXMLElement*)atts
{
    NSString* emotion = [[atts attributeForName:@"emotion"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* opCondition = [[atts attributeForName:@"operator"] stringValue];
    
    enum ConditionOperator opConditionType;
    opConditionType = [CnotiMind translateConditionOperator: opCondition];
    
    _parentNode = _currentNode;
    _currentNode = [[ConditionEmotionNode alloc] initWithEmotionAndValueAndOperatorAndBrainAndParent:emotion 
                                                                                               value:value 
                                                                                            operator:opConditionType 
                                                                                               brain:_brain 
                                                                                              parent:_parentNode];
    
    return true;  
}

- (BOOL) createConditionDataMiningNode:(GDataXMLElement*)atts
{
    NSString* event = [[atts attributeForName:@"event"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* operator = [[atts attributeForName:@"operator"] stringValue];
    NSString* operation = [[atts attributeForName:@"operation"] stringValue];
    NSString* variable = [[atts attributeForName:@"variable"] stringValue];
    NSString* compareValue = [[atts attributeForName:@"compareValue"] stringValue];
    NSString* memory = [[atts attributeForName:@"memory"] stringValue];

    enum DataMiningOperation operationType;
    operationType = [CnotiMind translateDataMiningOperator: operation];
    
    enum ConditionOperator operatorType;
    operatorType = [CnotiMind translateConditionOperator: operator];
    
    enum MemoryType memoryType;
    memoryType = [CnotiMind translateMemoryType: memory];
    
    _parentNode = _currentNode;
    _currentNode = [[ConditionDataMiningNode alloc] initWithKeyAndValueAndOperatorAndOperationAndMemoryAndVariableAndCompareValueBrainAndParent:event 
                                                                                                                                          value:value
                                                                                                                                       operator:operatorType
                                                                                                                                      operation:operationType 
                                                                                                                                         memory:memoryType 
                                                                                                                                       variable:variable 
                                                                                                                                   compareValue:compareValue 
                                                                                                                                          brain:_brain 
                                                                                                                                         parent:_parentNode];
    
    return true;     
}

- (BOOL) createMathOperationNode:(GDataXMLElement*)atts
{
    if( _rootNode == NULL || _currentNode == NULL )
    {
        return false;
    }
    
    NSString* operation = [[atts attributeForName:@"name"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* variable = [[atts attributeForName:@"variable"] stringValue];
    NSString* result = [[atts attributeForName:@"result"] stringValue];
    
    enum MathOperation mathOperationType;
    mathOperationType = [CnotiMind translateMathOperation:operation];

    _parentNode = _currentNode;
    _currentNode = [[MathOperationNode alloc] initWithMathOperationAndVariableAndValueAndResutVariableAndBrainAndParent:mathOperationType variable:variable value:value resultVariable:result brain:_brain parent:_parentNode];
    
    return true;
}

- (BOOL) createPropertyNode:(GDataXMLElement*)atts
{

    NSString* name = [[atts attributeForName:@"name"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];

    _parentNode = _currentNode;
    _currentNode = [[PropertyNode alloc] initWithKeyAndValuAndBrainAndParent:name value:value brain:_brain parent:_parentNode];
    
    return true;   
}

- (BOOL) createDeleteNode:(GDataXMLElement*)atts
{
    NSString* name = [[atts attributeForName:@"name"] stringValue];
    NSString* value = [[atts attributeForName:@"value"] stringValue];
    NSString* position = [[atts attributeForName:@"position"] stringValue];
    NSString* memory = [[atts attributeForName:@"memory"] stringValue];
    
    enum DeletePosition positionType;
    positionType = [CnotiMind translateDeletePosition:position];

    enum MemoryType memoryType;
    memoryType = [CnotiMind translateMemoryType:memory];
    
    _parentNode = _currentNode;
    _currentNode = [[DeleteNode alloc] initWithKeyAndValueAndPositionAndMemoryAndBrainAndParent:name value:value position:positionType memory:memoryType brain:_brain parent:_parentNode];
    
    return true;   
}

- (BOOL) createClearMemoryNode:(GDataXMLElement*)atts
{
    NSString* memory = [[atts attributeForName:@"memory"] stringValue];
    
    enum MemoryType memoryType;
    memoryType = [CnotiMind translateMemoryType:memory];
    
    _parentNode = _currentNode;
    _currentNode = [[ClearMemoryNode alloc] initWithMemoryAndBrainAndParent:memoryType brain:_brain parent:_parentNode];
    
    return true;    
}

- (BOOL) createRandomNode:(GDataXMLElement*)atts
{
    _parentNode = _currentNode;
    _currentNode = [[RandomNode alloc] initWithBrainAndParent:_brain parent:_parentNode];
    return true;    
}


@end