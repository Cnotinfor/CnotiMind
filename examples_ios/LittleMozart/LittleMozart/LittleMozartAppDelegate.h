//
//  LittleMozartAppDelegate.h
//  LittleMozart
//
//  Created by Gonçalo Rodrigues on 10/10/11.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LittleMozartViewController;

@interface LittleMozartAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet LittleMozartViewController *viewController;

@end
