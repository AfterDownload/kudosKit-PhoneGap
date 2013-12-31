
#import "PhoneGap-KudosKit.h"
#import "KudosKit.h"

@implementation CDVKudosKit

static BOOL did_call_setup = FALSE;

- (void)pluginInitialize
{
    [super pluginInitialize];
    NSLog(@"Kudos kit plugin initialized");
}

- (void)setup:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* appKey = [command.arguments objectAtIndex:0];
    NSArray* inApps = [command.arguments objectAtIndex:1];
    if (appKey != nil && [appKey length] > 0)
    {
        if( !did_call_setup )
        {
            did_call_setup = [[KudosKit instance] setupWithKey:appKey features:nil inApps:inApps];
        }
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"ok"];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


- (void)startRightSpot:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* name = [command.arguments objectAtIndex:0];
    NSNumber* force = [command.arguments objectAtIndex:1];
    
    if ( did_call_setup && name && force )
    {
        [[KudosKit instance] startRightSpot:name completion:nil force:[force boolValue]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"ok"];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)debug:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    if ( did_call_setup )
    {
        [[KudosKit instance] debug];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"ok"];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


@end