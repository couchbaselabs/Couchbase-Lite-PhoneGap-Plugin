#import <Cordova/CDV.h>

@interface CBLite : CDVPlugin

@property (nonatomic, strong) NSURL *liteURL;

- (void)getURL:(CDVInvokedUrlCommand*)urlCommand;

@end

