//
//  Brain.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/27.
//  Copyright 2011 Cnotinfor. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RuleNode.h"
#import "Emotion.h"
#import "Perception.h"
#import "MemoryEvent.h"

#import "ConditionDataMiningNode.h"
#import "ActionNode.h"
#import "EmotionNode.h"
#import "StorageNode.h"

#import "CnotiMind.h"
//#import "MemoryType.h"

#import "RulesXmlHandler.h"
#import "SettingsXmlHandler.h"



extern NSString* const SEND_ACTION;
extern NSString* const SEND_EMOTIONAL_STATE;

enum { HAS_DATA, NO_DATA };

@interface Brain : NSObject {
    
    RuleNode* _rules;
    RuleNode* _currentNode;
    RuleNode* _parentNode;
    
    NSMutableArray* _validPerceptions;
    NSMutableArray* _validActions;
    NSMutableArray* _emotions;

    //  QSemaphore _semaphoreBrain;
    NSConditionLock* _semaphoreBrain;
    
    NSMutableArray* _receivedPerceptions;
    NSMutableArray* _emotionsChanged;
    NSMutableArray* _longTermMemory;
    NSMutableArray* _workingMemory;
    
    NSMutableDictionary* _properties;
    
    int _timerDecayEmotions;
    
    bool _quit;
    
    RulesXmlHandler* _rulesXMLHandler;
    SettingsXmlHandler* _settingsXMLHandler;
}


@property (readwrite, retain) NSMutableArray* emotions;
@property (readwrite, retain) NSMutableArray* receivedPerceptions;

@property (readwrite, retain) NSMutableDictionary* properties;

- (id) init;
- (id) initWithPath:(NSString*)aPath;
- (IBAction) startThreadRun;

- (BOOL) loadXmlSettings:(NSString*)aFilename;

- (void) addValidPerception:(NSString*)aPerception;
- (void) addValidAction:(NSString*)aAction;
- (void) addEmotion:(Emotion*)aEmotion;

- (BOOL) loadXmlSettings:(NSString*)aFilename;
- (BOOL) loadXmlRules:(NSString*)aFilename;
- (BOOL) loadXMLRecursive:(NSArray*)rulesMembers;
- (BOOL) loadXMLRecursiveSettings:(NSArray*)settingsMembers;


- (BOOL) validateXml:(NSString*)aFilename;
- (BOOL) saveMemory:(NSString*)aFilename;
- (BOOL) loadMemory:(NSString*)aFilename;
- (BOOL) saveEmotionalState:(NSString*)aFilename;
- (BOOL) loadEmotionalState:(NSString*)aFilename;

// Methods to clear brain state
- (void) clearWorkingMemory;
- (void) clearMemory;

// Methods for printing brain data in console
- (void) printSettings;
- (void) printRules;
- (void) printMemory:(enum MemoryType) aType;


- (void) receivePerception:(Perception*)aPerception;
- (void) stop;

//  signals NOTIFICATION CENTER
- (void) sendAction:(NSString*)aKey value:(NSString*)aValue;
- (void) sendEmotionalState:(NSString*)aKey value:(NSString*)aValue;
//  END signals NOTIFICATION CENTER

// private

- (void) updateEmotionValue:(NSString*)aEmotionName variation:(double)aVariation max:(double)aMax min:(double)aMin;
- (void) updateEmotionValue:(NSString*)aEmotionName variation:(double)aVariation;

- (void) updatePropertyValue:(NSString*)aPropertyName value:(NSString*)aValue;

- (void) storeToMemory:(MemoryEvent*)aMemoryEvent memoryType:(enum MemoryType)aMemoryType;


- (void) executeAction:(NSString*)aKey value:(NSString*)aValue;
//- (void) executeAction:(NSMutableArray*)aVariables;

- (void) deleteEvent:(NSString*)aKey position:(enum DeletePosition)aPosition memory:(enum MemoryType)aMemory;
- (void) deleteEvent:(NSString*)aKey value:(NSString*)aValue position:(enum DeletePosition)aPosition memory:(enum MemoryType)aMemory;

// Methods to get information from the memory
- (id) dataMining: (enum DataMiningOperation)aOperation event:(NSString*)aEvent memoryType:(enum MemoryType)aMemoryType valid:(BOOL*)aValid;
- (id) dataMining: (enum DataMiningOperation)aOperation event:(NSString*)aEvent value:(id)aValue memoryType:(enum MemoryType)aMemoryType valid:(BOOL*)aValid;

- (float) dataMiningMax:(NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (float) dataMiningMin:(NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (float) dataMiningSum:(NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (BOOL)isNumeric:(NSString*)s;
- (float) dataMiningSum:(NSString*)aEvent value:(float)aValue memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;

- (float) dataMiningCount:(NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (float) dataMiningCount:(NSString*)aEvent value:(NSString*)aValue memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (float) dataMiningMean:(NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;

- (bool) dataMiningExists: (NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (bool) dataMiningExists: (NSString*)aEvent value:(NSString*)aValue memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;

- (NSString*) dataMiningLast: (NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;
- (NSString*) dataMiningFirst: (NSString*)aEvent memory:(NSMutableArray*)aMemory valid:(BOOL*)aValid;

- (NSString*) dataMiningDuration: (NSString*)aEvent memory:(NSMutableArray*)aMemory;
- (NSString*) dataMiningTime: (NSString*)aEvent memory:(NSMutableArray*)aMemory;

// method to help set valid value
- (void) setValid:(BOOL*)aValid value:(BOOL)aValue;


/**
 Main loop for the thread.
 
 Everytime a perceptions arrives, the _semaphoreBrian is made available, so it unlocks
 and start
 */
- (void) run;

@end
