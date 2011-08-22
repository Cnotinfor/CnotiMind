//
//  ConditionNode.m
//  CnotiMind
//

#import "ConditionNode.h"


@implementation ConditionNode



- (id) initWithKeyAndValueAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
//        _key = aKey;
        _key = [[NSString alloc] initWithString:aKey];        
        _value = [[NSString alloc] initWithString:aValue];;
        DLog(@"---: %@", _key);
        DLog(@"---: %@", _value);     
        // If not condition operator is set, it uses the Equal Operator
		if(aOperator == ConditionOperatorUndefined)
		{
			_operator = ConditionOperatorEqual;
		}
        else
        {
            _operator = aOperator;
        }
        
        if ([aValue length]==0) {
            _isValueNumeric = FALSE;
        }
        else {
            if ([self isNumeric:aValue]) {
                _isValueNumeric = TRUE;
            }
            else {
                _isValueNumeric = FALSE;
            }
        }
//        DLog(@"_isValueNumeric: %d", _isValueNumeric);
//        DLog(@"aValue: %@", aValue);
//        DLog(@"_valueNumeric :%f", _valueNumeric);
        
    }
    
    return self;
}

- (void) exec
{
    
    // TODO Test if the condition is true. If it is, execute the node
    if( true )
    {
        [super execChildren];
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    // TODO Test if the condition is true. If it is, execute the node
    if( true )
    {
        [super execChildren:aVariables];
    }
}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ Condition", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (void) dealloc
{
    [_key release];
    [super dealloc];
}

@end
