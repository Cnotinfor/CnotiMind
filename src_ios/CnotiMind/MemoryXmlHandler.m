//
//  MemoryXmlHandler.m
//  SingleEmotion
//

#import "MemoryXmlHandler.h"
#import "RootNode.h"

#import "Brain.h"

@implementation MemoryXmlHandler

- (id)init
{
    self = [super init];
    if (self) {
        _line = 0;
        _type = UndefinedMemory;
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
    if( ![aQName caseInsensitiveCompare:@"Memory"] )
    {
        _type = UndefinedMemory;
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"LongTermMemory"] )
    {
        _type = LongTermMemory;
        return true;

    }
    if( ![aQName caseInsensitiveCompare:@"WorkingMemory"] )
    {
        _type = WorkingMemory;
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"MemoryEvent"] )
    {
        
        if ( _type == UndefinedMemory ) {
            return false;
        }
        
        if( [atts attributeForName:@"event"] != nil &&
           [atts attributeForName:@"value"] != nil && 
           [atts attributeForName:@"time"] != nil ) {
            NSString* event = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"event"] stringValue]];
            NSString* value = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"value"] stringValue]];
            NSString* time = [NSString stringWithFormat:@"%@", [[atts attributeForName:@"time"] stringValue]];

            MemoryEvent* memoryEvent = [[MemoryEvent alloc] initWithEventAndValueAndTime:event value:value time:time];
            
            [_brain storeToMemory:memoryEvent memoryType:_type];
            
            DLog(@"MemoryEvent: name: %@ value: %@", event, value);
            
            return true;
        }
        else {
            return false;
        }

        
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
    
    if( ![aQName caseInsensitiveCompare:@"LongTermMemory"] && _type == LongTermMemory )
    {
        _type = UndefinedMemory;
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"WorkingMemory"] && _type == WorkingMemory )
    {
        _type = UndefinedMemory;
        return true;
    }
    if( ![aQName caseInsensitiveCompare:@"MemoryEvent"] || ![aQName caseInsensitiveCompare:@"Memory"] )
    {
        return true;
    }
    if (![aQName caseInsensitiveCompare:@"comment"])
    {
        return true;
    }
    
    DLog(@"[MemoryXmlHandler::endElement] Invalid element: %@",aQName);
    
    return true;

}


- (void)dealloc {
    
    [super dealloc];
}

@end
