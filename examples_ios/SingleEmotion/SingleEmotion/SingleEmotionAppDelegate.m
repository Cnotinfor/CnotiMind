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


- (id)init
{
    if (self == [super init]) {
        
        
        _brain = [[Brain alloc] init];
        
        //  load XML rulles;
        DLog(@"--- load XML rulles ---");
//        [_brain loadXmlRulesWithoutXML];
//        [_brain loadXmlRulesWithoutXMLKickMe];
        
        [_brain loadXmlRulesWithoutXMLKickMeWithHandler];
        [_brain printRules];
        DLog(@"--- start brain ---");
        [_brain startThreadRun];
        
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(actionReceived:) 
                                                 name:SEND_ACTION
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(emotionReceived:) 
                                                 name:SEND_EMOTIONAL_STATE
                                               object:nil];

    return self;
}


- (IBAction) onClickButtonHello
{
    DLog(@"I clicked on the Button!");

//    Perception* perception = [[Perception alloc] initWithNameAndAValue:@"User Talk" value:@"Bye"];
//    [_brain receivePerception:perception];
    
    Perception* perception2 = [[Perception alloc] initWithNameAndAValue:@"kicked" value:@"being kicked"];
    [_brain receivePerception:perception2];
    
    [_brain printMemory:LongTermMemory];
    [_brain printMemory:WorkingMemory];
}


- (void) actionReceived:(NSNotification*)aNotif
{
    
    NSArray* values = [[aNotif object] allValues]; 
    for (id value in values) {
//        DLog(@"setText: %@", value);
    }

    DLog(@"actionReceived: %@", aNotif);
}


- (void) emotionReceived:(NSNotification*)aNotif
{
    DLog(@"emotionReceived: %@", aNotif);
}


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
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

@end
