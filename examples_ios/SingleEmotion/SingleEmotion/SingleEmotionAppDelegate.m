//
//  SingleEmotionAppDelegate.m
//  SingleEmotion
//
//  Created by Gonçalo Rodrigues on 11/05/16.
//  Copyright 2011 Universidade de Coimbra. All rights reserved.
//

#import "SingleEmotionAppDelegate.h"

@implementation SingleEmotionAppDelegate


@synthesize window=_window;

@synthesize navigationController=_navigationController;


- (id)init
{
    
    if (self == [super init]) {
        _brain = [[Brain alloc] init];
        
        [_brain loadXmlRules:@""];
        
        //  load XML rulles;
    }
    
    return self;
}


- (IBAction) onClickButtonHello
{
    NSLog(@"I clicked on the Button!");
    Perception* p = [[Perception alloc] initWithNameAndAValue:@"User talk" value:@"Hello"];
    
    [_brain receivePerception:p];
    
    //  return nil;
}

- (void) actionReceived:(NSString*)aKey value:(NSString*)aValue
{}

- (void) emotionReceived:(NSString*)aEmotion number:(NSNumber*)aValue
{}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    // Add the navigation controller's view to the window and display.
//    self.window.rootViewController = self.navigationController;
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

- (void)dealloc
{
    [_window release];
    [_navigationController release];
    [super dealloc];
}

@end
