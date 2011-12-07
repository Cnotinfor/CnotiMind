//
//  Crutch.m
//  LittleMozart
//

#import "Crutch.h"

@implementation Crutch

@synthesize name = _name;
@synthesize action = _action;
@synthesize emotion = _emotion;
@synthesize min = _min;
@synthesize max = _max;
@synthesize order = _order;
@synthesize properties = _properties;

- (id)init {
    self = [super init];
    if (self) {
        _name = [[NSString alloc] initWithFormat:@""];
        _action = [[NSString alloc] initWithFormat:@""];
        _emotion = [[NSString alloc] initWithFormat:@""];
        _min = INT8_MIN;
        _max = INT8_MAX;
        _order = -1;
        
    }
    return self;
}

- (id)initWithNameAndActionAndEnforcementAndOrder:(NSString*)aName 
                                           action:(NSString*)aAction 
                                          emotion:(NSString*)aEmotion
                                              min:(NSString*)aMin
                                              max:(NSString*)aMax
                                            order:(enum EnumCrutchOrder)aOrder
                                       properties:(NSMutableDictionary*)aProperties {
    if ( self = [self init] ) {
        _name = (aName == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aName];
        _action = (aAction == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aAction];
        _emotion = (aEmotion == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aEmotion];
        NSString* minString = (aMin == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aMin];
        NSString* maxString = (aMax == nil) ? [[NSString alloc] initWithString:@""] : [[NSString alloc] initWithString:aMax];

        if ( [self isNumeric:minString] ) {
            _min = [minString intValue];
        }
        
        if ( [self isNumeric:maxString] ) {
            _max = [maxString intValue];
        }
        
        _order = -1;
        _properties = aProperties;
    }
    return self;
}

- (BOOL)isNumeric:(NSString*)s
{
    NSScanner *sc = [NSScanner scannerWithString: s];
    // We can pass NULL because we don't actually need the value to test
    // for if the string is numeric. This is allowable.
    if ( [sc scanFloat:NULL] )
    {
        // Ensure nothing left in scanner so that "42foo" is not accepted.
        // ("42" would be consumed by scanFloat above leaving "foo".)
        return [sc isAtEnd];
    }
    // Couldn't even scan a float :(
    return NO;
}

- (void)dealloc {
    [_name release];
    [_action release];
    [_emotion release];
    [_properties release];
    
    [super dealloc];
}

@end
