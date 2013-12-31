#import <Cordova/CDV.h>

@interface CDVKudosKit : CDVPlugin

- (void)setup:(CDVInvokedUrlCommand*)command;
- (void)startRightSpot:(CDVInvokedUrlCommand*)command;
- (void)debug:(CDVInvokedUrlCommand*)command;

@end
