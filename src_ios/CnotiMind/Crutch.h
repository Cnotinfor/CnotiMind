//
//  Crutch.h
//  LittleMozart
//

#import <Foundation/Foundation.h>

enum EnumCrutchOrder
{
	CrutchOrder_BEGIN=1,
	CrutchOrder_BEGIN_AND_END=2,
	CrutchOrder_END=3
};

@interface Crutch : NSObject {    
    NSString* _name;
    NSString* _action;
    NSString* _emotion;
    int _min;
    int _max;
    enum EnumCrutchOrder _order;
}

@property (readwrite, assign) NSString* name;
@property (readwrite, assign) NSString* action;
@property (readwrite, assign) NSString* emotion;
@property (readwrite, assign) int min;
@property (readwrite, assign) int max;
@property (readwrite, assign) enum EnumCrutchOrder order;

- (id)init;
- (id)initWithNameAndActionAndEnforcementAndOrder:(NSString*)aName 
                                           action:(NSString*)aAction 
                                          emotion:(NSString*)aEmotion
                                              min:(NSString*)aMin
                                              max:(NSString*)aMax
                                            order:(enum EnumCrutchOrder)aOrder;
- (BOOL)isNumeric:(NSString*)s;
- (void)dealloc;

@end
