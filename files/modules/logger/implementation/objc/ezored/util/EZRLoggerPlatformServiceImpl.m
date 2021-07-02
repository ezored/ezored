#import "EZRLoggerPlatformServiceImpl.h"

@interface EZRLoggerPlatformServiceImpl ()
@property(nonatomic, strong) NSString *group;
@end

@implementation EZRLoggerPlatformServiceImpl

//------------------------------------------------------------------------------
#pragma mark - Class Initializer
//------------------------------------------------------------------------------

+ (instancetype)proxy
{
    return [[self alloc] init];
}

//------------------------------------------------------------------------------
#pragma mark - Initialization
//------------------------------------------------------------------------------

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        self.group = @"";
    }
    return self;
}

- (instancetype)initWithGroup:(NSString *)group
{
    if (self = [super init])
    {
        self.group = group;
    }
    return self;
}

//------------------------------------------------------------------------------
#pragma mark - EZRLoggerPlatformServiceImpl
//------------------------------------------------------------------------------

- (void)v:(nonnull NSString *)message
{
    printf("[%s] 💜 %s\n", [[[NSDate date] description] UTF8String], [[NSString stringWithFormat:@"%@", message] UTF8String]);
}

- (void)d:(nonnull NSString *)message
{
    printf("[%s] 💚 %s\n", [[[NSDate date] description] UTF8String], [[NSString stringWithFormat:@"%@", message] UTF8String]);
}

- (void)i:(nonnull NSString *)message
{
    printf("[%s] 💙 %s\n", [[[NSDate date] description] UTF8String], [[NSString stringWithFormat:@"%@", message] UTF8String]);
}

- (void)w:(nonnull NSString *)message
{
    printf("[%s] 💛 %s\n", [[[NSDate date] description] UTF8String], [[NSString stringWithFormat:@"%@", message] UTF8String]);
}

- (void)e:(nonnull NSString *)message
{
    printf("[%s] ❤️ %s\n", [[[NSDate date] description] UTF8String], [[NSString stringWithFormat:@"%@", message] UTF8String]);
}

- (void)setGroup:(nonnull NSString *)group
{
    _group = group;
}

@end
