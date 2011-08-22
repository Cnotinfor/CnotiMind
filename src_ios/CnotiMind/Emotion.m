//
//  Emotion.m
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/21.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "Emotion.h"


@implementation Emotion

@synthesize value = _value;
@synthesize name = _name;

@synthesize min = _min;
@synthesize max = _max;


- (id) init
{
    if (self == [super init]) {
        _name = [[NSString alloc] initWithString:@""];
        _value = 0;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (id) initWithNameAndValue:(NSString*)aName value:(double)aValue
{
    if (self == [super init]) {
        _name = [[NSString alloc] initWithString:aName];
        _value = aValue;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (id) initWithNameAndValueAndMaxAndMin:(NSString*)aName value:(double)aValue max:(double)aMax min:(double)aMin
{
    if (self == [super init]) {
        _name = [[NSString alloc] initWithString:aName];
        _value = aValue;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (void) setEmotionValue:(double)aValue max:(double)aMax min:(double)aMin
{
//    double oldValue = _value;
//    double newMax = MAX(aMax, _max);
//    double newMin = MIN(aMin, _min);
    
    _value = MAX(aMin, MIN(aValue, aMax));
    DLog(@"setEmotionValue; %f", _value);
    
//    return oldValue != _value;
}


- (void) setEmotionValue:(double)aValue
{
    [self setEmotionValue:aValue max:_max min:_min];
}


- (void) addValue:(double)aIncrement max:(double)aMax min:(double)aMin
{
    [self setEmotionValue:_value + aIncrement max:aMax min:aMin];
}


- (void) addValue:(double)aIncrement
{
    [self setValue:_value + aIncrement];
}


+ (BOOL) compareWithEmotionAndString:(Emotion*)aEmotion name:(NSString*)aEmotionName
{
    return [aEmotion.name isEqualToString:aEmotionName];
}


+ (BOOL) compareWithStringAndEmotion:(NSString*)aEmotionName emotion:(Emotion*)aEmotion
{
    return [aEmotionName isEqualToString:aEmotion.name];
}


+ (BOOL) compareWithEmotions:(Emotion*)aEmotion1 emotion:(Emotion*)aEmotion2
{
    return [aEmotion1.name isEqualToString:aEmotion2.name];
}


+ (BOOL) insertEmotionIntoArray:(Emotion*)aEmotion array:(NSMutableArray*)aArray
{
    [aArray addObject:aEmotion];
    
    return TRUE;
}

- (NSString *)description:(Emotion*)aEmotion
{

    NSString* res = [NSString stringWithFormat:@"Emotion: %@; value: %@; min: %f; max: %f;", aEmotion.name, aEmotion.value, aEmotion.min, aEmotion.max];

    NSLog(@"%@", res);
    return res;
}

- (void) dealloc
{
    [_name release];
    [super dealloc];
}

@end
