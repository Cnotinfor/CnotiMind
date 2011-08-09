//
//  Emotion.h
//  CnotiMind
//
//  Created by Gonçalo Rodrigues on 11/04/21.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Emotion : NSObject {
    
    double _value;
    double _max;
    double _min;
    NSString* _key;
    
}

@property (readwrite, assign) double value;
@property (readwrite, assign) NSString* key;

@property (readwrite, assign) double min;
@property (readwrite, assign) double max;

- (id) init;
- (id) initWithKeyAndValue:(NSString*)aKey value:(double)aValue;
- (id) initWithKeyAndValueAndMaxAndMin:(NSString*)aKey value:(double)aValue max:(double)aMax min:(double)aMin;

- (void) setValue:(double)aValue max:(double)aMax min:(double)aMin;
- (void) setValue:(double)aValue;
- (void) addValue:(double)aIncrement max:(double)aMax min:(double)aMin;
- (void) addValue:(double)aIncrement;

+ (BOOL) compareWithEmotionAndString:(Emotion*)aEmotion name:(NSString*)aEmotionName;
+ (BOOL) compareWithStringAndEmotion:(NSString*)aEmotionName emotion:(Emotion*)aEmotion;
+ (BOOL) compareWithEmotions:(Emotion*)aEmotion1 emotion:(Emotion*)aEmotion2;

+ (BOOL) insertEmotionIntoArray:(Emotion*)aEmotion array:(NSMutableArray*)aArray;

//- (NSString *)description;



@end
