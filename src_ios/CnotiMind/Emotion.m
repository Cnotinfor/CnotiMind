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
@synthesize key = _key;

@synthesize min = _min;
@synthesize max = _max;


- (id) init
{
    if (self == [super init]) {
        _key = [NSString stringWithFormat:@""];
        _value = 0;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (id) initWithKeyAndValue:(NSString*)aKey value:(double)aValue
{
    if (self == [super init]) {
        _key = aKey;
        _value = aValue;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (id) initWithKeyAndValueAndMaxAndMin:(NSString*)aKey value:(double)aValue max:(double)aMax min:(double)aMin
{
    if (self == [super init]) {
        _key = aKey;
        _value = aValue;
        _min = INT8_MIN;
        _max = INT8_MAX;
    }
    return self;
}


- (void) setValue:(double)aValue max:(double)aMax min:(double)aMin
{

//    double oldValue = _value;
    
    double newMax = MAX(aMax, _max);
    double newMin = MIN(aMin, _min);
    
    
    _value = MAX(newMin, MIN(aValue, newMax));
    
//    return oldValue != _value;
}


- (void) setValue:(double)aValue
{
    [self setValue:aValue max:_max min:_min];
}


- (void) addValue:(double)aIncrement max:(double)aMax min:(double)aMin
{
    [self setValue:_value + aIncrement max:aMax min:aMin];
}


- (void) addValue:(double)aIncrement
{
    [self setValue:_value + aIncrement];
}


+ (BOOL) compareWithEmotionAndString:(Emotion*)aEmotion name:(NSString*)aEmotionName
{
    return [aEmotion.key isEqualToString:aEmotionName];
}


+ (BOOL) compareWithStringAndEmotion:(NSString*)aEmotionName emotion:(Emotion*)aEmotion
{
    return [aEmotionName isEqualToString:aEmotion.key];
}


+ (BOOL) compareWithEmotions:(Emotion*)aEmotion1 emotion:(Emotion*)aEmotion2
{
    return [aEmotion1.key isEqualToString:aEmotion2.key];
}


+ (BOOL) insertEmotionIntoArray:(Emotion*)aEmotion array:(NSMutableArray*)aArray
{
    [aArray addObject:aEmotion];
    
    return TRUE;
}

- (NSString *)description:(Emotion*)aEmotion
{

    NSString* res = [NSString stringWithFormat:@"Emotion: %@; value: %@; min: %f; max: %f;", aEmotion.key, aEmotion.value, aEmotion.min, aEmotion.max];

    NSLog(@"%@", res);
    return res;
}

@end
