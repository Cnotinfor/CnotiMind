//
//  ConditionEmotionNode.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/05/09.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "DataMiningNode.h"

#import "Brain.h"
#import "Perception.h"

@implementation DataMiningNode


- (id) initWithEventAndValueAndOperatorAndBrainAndParent: (NSString*)aEvent 
                                                   value:(NSString*)aValue 
                                                operator:(enum DataMiningOperation)aDataMiningOperation 
                                                  memory:(enum MemoryType)aMemory
                                                variable:(NSString*)aVariable
                                                   brain:(Brain*)aBrain 
                                                  parent:(id)aParent
{
    
    if ( self == [super initWithBrainAndParent:aBrain parent:aParent] )
    {
        _event = aEvent;
        _value = aValue;
        
        _operation = aDataMiningOperation;
        _memory = aMemory;
        _variable = aVariable;
        _valueNumeric = [NSNumber numberWithFloat:[aValue floatValue]];
        
        
//      _position( position ),
//		_positionNumeric( position.toInt( &_isPositionNumeric ) )
    }
    return self;
}


- (void) exec
{
    if( [self isTrue] )
    {
        if( [_variable length]==0 )
        {
            // this should not happen, since the _variable should never be empty
            [self execChildren];
        }
        else
        {
            NSMutableDictionary* variables = [[NSDictionary alloc] init];
            [variables setObject:_result forKey:_variable];
            
            //  TODO    
            [self execChildren: variables];
        }
    }
}


- (void) exec:(NSMutableDictionary*)aVariables
{
    if ([self isTrue]) {
        
        if ( [_variable length] != 0 ) {
            [aVariables setObject:_result forKey:_variable];
        }
        
        [self execChildren];
    }

}


- (NSString*) info:(int)aDepth
{
    NSString* info = [NSString stringWithFormat:@""];
    NSString* space = [self space:aDepth];
    
    info = [info stringByAppendingFormat:@"%@ DataMining", space];
    info = [info stringByAppendingFormat:@"%@", [super info:aDepth]];
    
    return info;
}


- (BOOL) isTrue
{
    BOOL valid;
    
    // If the values are numbers it should use the
    if( _isValueNumeric )
    {
        _result = [_brain dataMining: _operation event:_event value:_valueNumeric memoryType:_memory valid:&valid];
        return valid;
    }
    else // If the value is QString
    {
        _result = [_brain dataMining: _operation event:_event value:_value memoryType:_memory valid:&valid];
        
        return valid;
    }
}

/*
 Check if in the value string there are variable or property tags
 
 If it is a variable tag try to get the value from the variables lists.
 
 Variables tags are betweeen square brackets [].
 Property tags are between curl brackets {}.
 
 If the variable/property tag is not found, it is replaced by an empty string.
 */

- (BOOL) isTrue:(NSMutableDictionary*)aVariables
{
    
    BOOL valid;
    int position = 0;
    
    // TODO stuff
//    [self tagsToValue:<#(NSString **)#> variables:<#(NSMutableDictionary **)#>]
    
    // If the values are numbers it should use the
    if( _isValueNumeric )
    {
        _result = [_brain dataMining: _operation event:_event value:_valueNumeric memoryType:_memory valid:&valid];
        return valid;
    }
    else // If the value is QString
    {
        _result = [_brain dataMining: _operation event:_event value:_value memoryType:_memory valid:&valid];
        
        return valid;
    }
}

@end
