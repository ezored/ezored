#import "ezored/data/EZRSharedDataPlatformService.h"
#import <Foundation/Foundation.h>

__attribute__((visibility("default")))
@interface EZRSharedDataPlatformServiceImpl : NSObject<EZRSharedDataPlatformService>

//
// An class method to provide an instance of the EZRSharedDataPlatformServiceImpl
// class.
//
+ (instancetype)proxy;

@end
