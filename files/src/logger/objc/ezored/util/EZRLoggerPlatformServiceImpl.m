#import "EZRLoggerPlatformServiceImpl.h"

@interface EZRLoggerPlatformServiceImpl ()
@property (nonatomic, strong) NSString *group;
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
    if (self) {
        self.group = @"";
    }
    return self;
}

- (instancetype)initWithGroup:(NSString *)group 
{
    if (self = [super init]) {
        self.group = group;
    }
    return self;
}

//------------------------------------------------------------------------------
#pragma mark - EZRLoggerPlatformServiceImpl
//------------------------------------------------------------------------------

- (void)v:(nonnull NSString *)message 
{
    NSLog(@"💜 %@", message);
}

- (void)d:(nonnull NSString *)message 
{
    NSLog(@"💚 %@", message);
}

- (void)i:(nonnull NSString *)message 
{
    NSLog(@"💙 %@", message);
}

- (void)w:(nonnull NSString *)message 
{
    NSLog(@"💛 %@", message);
}

- (void)e:(nonnull NSString *)message 
{
    NSLog(@"❤️ %@", message);
}

- (void)f:(nonnull NSString *)message 
{
    NSLog(@"🖤 %@", message);
}

- (void)setGroup:(nonnull NSString *)group 
{
    _group = group;
}

@end
