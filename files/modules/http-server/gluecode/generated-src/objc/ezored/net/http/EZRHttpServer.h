// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "ezored/net/http/EZRHttpServerConfig.h"
#import <Foundation/Foundation.h>
@class EZRHttpServer;

@interface EZRHttpServer : NSObject

+ (nullable EZRHttpServer *)shared;

- (void)initialize:(nonnull EZRHttpServerConfig *)config;

- (nonnull EZRHttpServerConfig *)getConfig;

- (void)start;

- (void)stop;

- (void)waitForTermination;

@end
