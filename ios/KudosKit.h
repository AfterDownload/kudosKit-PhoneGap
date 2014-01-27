//
//  KudosKit.h
//  KudosKit
//
//  Created by Michael Badichi on 4/3/13.
//  Copyright (c) 2013 After Download. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>

#define KKIT_VERSION    @"1.5.7"

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

@class KudosKit;

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

@protocol KudosKitAppDelegate <NSObject>

@optional

//you can bypass Appreciation module if there is a critical condition and you dont want to
//override the default flow of your app.
//naturally you would do all the checking you want before you call startRightSpot
- (BOOL)kudosKit:(KudosKit*)obj shouldEnterScene:(NSString*)name;

//allows the developer to take action before the purchase dialog is popping up
//this does not neccessarily mean he buys, you should check if the purchase was successful
//or cancelled with the below didMakePayment and didFailMakingPayment delegates
- (void)kudosKit:(KudosKit*)obj willMakePayment:(NSString*)inappid;

//allows the developer to indicate that a purchase was made
//you might want to award the contributer for it
- (void)kudosKit:(KudosKit*)obj didMakePayment:(NSString*)inappid;

//allows the developer to receive a callback when an Appreciation module is presented
- (void)kudosKit:(KudosKit*)obj didEnterScene:(NSString*)name;

//allows the developer to receive a callback before an Appreciation module is presented
- (void)kudosKit:(KudosKit*)obj willEnterScene:(NSString*)name;

//todo:
//- (void)kudosKit:(KudosKit*)obj willLeaveScene:(NSString*)name;
//- (void)kudosKit:(KudosKit*)obj didLeaveScene:(NSString*)name;
//- (void)kudosKit:(KudosKit*)obj didFailMakingPayment:(NSString*)inappid;

//this is where you handle the features you support
//currently the features includes mail, facebook and twitter.
//the command is the feature name you support
//the value is the value corresponds to the the feature, in the case of the currently supported features,
// value is the message to share suggested by the server, it can be null. so be sure to handle your own text to share
//should return TRUE when handled 
- (BOOL)kudosKit:(KudosKit*)obj didGetCommandFromScene:(NSString*)command value:(NSString*)value;

@end

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


@interface KudosKit : NSObject

//------------------------------------------------------------------------------------------------

enum {
    KKIT_DebugLevelNone                 = 0,
    KKIT_DebugLevelErrors               = (1<<0),
    KKIT_DebugLevelWarnings             = (1<<1),
    KKIT_DebugLevelInformative          = (1<<2),
    KKIT_DebugLevelWarningsAndErrors    = KKIT_DebugLevelErrors | KKIT_DebugLevelWarnings,
    KKIT_DebugLevelAll                  = KKIT_DebugLevelInformative | KKIT_DebugLevelWarningsAndErrors,
};
typedef NSInteger KKIT_DebugLevel;

//------------------------------------------------------------------------------------------------

// return single instance KudosKit object, if none exists, it will be created
// this is a helper function, naturally you would only have a single instance
// for the SDK in your app.
+(KudosKit*)instance;

// return SDK version
+(NSString*)version;

//------------------------------------------------------------------------------------------------

// this is the 1st thing you would want to call in your app
// the best place for this is in the head of your didFinishLaunchingWithOptions
// you should provide the appKey that you obtained from kudos-kit.com for this app, and an array of in-apps IDs
// these in apps IDs are the consumable in-apps you generated for your apps for KudosKit
// note that this does not guarentee that the Key is valid. only that it will be used the the upcoming session
// return TRUE if setup was successful
// features are a set of features supported for by the application.
//  at the time of writing this doc. the only features supported by the kudosKit modules are "mail", "facebook" and "twitter"
// return FALSE if there was an invalid key supplied or if there are no items in the array
-(BOOL)setupWithKey:(NSString*)appKey features:(NSArray *)features inApps:(NSArray *)inAppIDs;

//opens up a special debugging Appreciation module, very useful for checking that sdk integration done properly
-(void)debug;

//asks the user for a store rating for this app
-(void)rateOnStore;

// sets up the reporting level on the stdout console
// the default level if not set is KKIT_DebugLevelAll
-(void)setDebugLevel:(KKIT_DebugLevel)level;

// eventname is decision making rule-set you specify on the kudosKit Management Consule.

// optional, pull if the next call to startRightSpot would actually show our named kudosKit scene
// if this IS the right spot, it will also preload the view so it would appear as fast as possible when started
-(BOOL)isRightSpot:(NSString*)eventname;

// register for notifcations/confirmations
-(void)addDelegate:(id<KudosKitAppDelegate>)delegate;
-(void)removeDelegate:(id<KudosKitAppDelegate>)delegate;

//if the kudosKit engine has decided that this is the right spot for placing the kudosKit scene it would
//be started with full screen.
//the call returns TRUE if this was the right spot, (in which case it would also start "running the scene")
//or FALSE if this is not the right moment.
//if you want to get notified for events regarding the scene state, you should add yourself as a delegate
-(BOOL)startRightSpot:(NSString*)eventname completion:(void (^)(void))completion force:(BOOL)isForced;

//start the scene inside a view
-(BOOL)startRightSpot:(NSString*)eventname asSubviewOf:(UIView*)view completion:(void (^)(void))completion force:(BOOL)isForced;

//------------------------------------------------------------------------------------------------

//normal counter/setter (no history is saved for counters)
-(void)counterUpdate:(NSString*)varname value:(NSNumber *)value;
-(void)counterSet:(NSString*)varname value:(NSNumber *)value;

//duration counters
-(void)durationSrart:(NSString*)varname;
-(void)durationEnd:(NSString*)varname;

//tracked values (like scores, number of friends on facebook, number of appointments this week or whatever
//valueable data your app posses, that can be used for server side decision making logic
//note that there should be a limited "history" items, the kudosKit Management Consule will provide
//additional statistical represntation
//value can be a NSString (there should be a size limitation) or a NSNumber
-(void)pushRecord:(NSString*)varname value:(id)val;

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

@end
