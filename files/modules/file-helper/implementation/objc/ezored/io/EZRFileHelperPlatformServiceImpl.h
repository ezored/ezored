#import "ezored/io/EZRFileHelperPlatformService.h"
#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@interface EZRFileHelperPlatformServiceImpl : NSObject<EZRFileHelperPlatformService>

//
// An class method to provide an instance of the EZRFileHelperPlatformServiceImpl
// class.
//
+ (instancetype)proxy;

@end
