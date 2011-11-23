//
//  SETTINGSXmlHandler.h
//  SingleEmotion
//

#ifndef MEMORYXMLHANDLER_H
#define MEMORYXMLHANDLER_H

#import "CnotiMind.h"

@class Brain;

#import "GDataXMLNode.h"

@interface MemoryXmlHandler : NSObject
{    
    Brain* _brain;
    enum MemoryType _type;
    int _line;
}

- (id)init;
- (id)initWithBrain:(Brain*)aBrain;

- (BOOL) startElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName atts:(GDataXMLElement*)atts;
- (BOOL) endElement:(NSString*)aNamespaceURI localName:(NSString*)aLocalName qName:(NSString*)aQName;

- (void)dealloc; 

@end
#endif // MEMORYXMLHANDLER_H