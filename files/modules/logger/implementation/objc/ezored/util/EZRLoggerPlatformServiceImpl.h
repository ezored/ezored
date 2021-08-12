#import "ezored/util/EZRLoggerPlatformService.h"
#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@interface EZRLoggerPlatformServiceImpl : NSObject<EZRLoggerPlatformService>

//
// An class method to provide an instance of the EZRLoggerPlatformServiceImpl
// class.
//
+ (instancetype)proxy;

@end
