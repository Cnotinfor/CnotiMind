//
//  ConditionNode.m
//  CnotiMind
//

#import "ConditionNode.h"


@implementation ConditionNode



- (id) initWithKeyAndValueAndBrainAndParent: (NSString*)aKey value:(NSString*)aValue operator: (enum ConditionOperator)aOperator brain:(Brain*)aBrain parent:(id)aParent
{
    if (self == [super initWithBrainAndParent:aBrain parent:aParent]) {
        
        
        _key = aKey;
        _value = aValue;
        
        // If not condition operator is set, it uses the Equal Operator
		if(aOperator == ConditionOperatorUndefined)
		{
			_operator = ConditionOperatorEqual;
		}
        else
        {
            _operator = aOperator;
        }
        
        _valueNumeric = [aValue floatValue];
        
        if ( strcmp([[NSNumber numberWithDouble:[aValue floatValue]] objCType], "f") ) {
            _isValueNumeric = TRUE;
        }
        else {
            _isValueNumeric = FALSE;
        }
        
        DLog(@"_isValueNumeric: %d", _isValueNumeric);
        
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


@end
