#import "EZRSharedDataPlatformServiceImpl.h"

@interface EZRSharedDataPlatformServiceImpl ()
@end

@implementation EZRSharedDataPlatformServiceImpl

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
    }
    return self;
}

//------------------------------------------------------------------------------
#pragma mark - EZRSharedDataPlatformServiceImpl
//------------------------------------------------------------------------------

- (void)setString:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(nonnull NSString *)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setObject:value forKey:[self getKeyName:groupName key:key]];
    }
}

- (void)setInteger:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(int32_t)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setInteger:value forKey:[self getKeyName:groupName key:key]];
    }
}

- (void)setLong:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(int64_t)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setObject:[NSNumber numberWithLongLong:value] forKey:[self getKeyName:groupName key:key]];
    }
}

- (void)setBool:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(BOOL)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setBool:value forKey:[self getKeyName:groupName key:key]];
    }
}

- (void)setFloat:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(float)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setFloat:value forKey:[self getKeyName:groupName key:key]];
    }
}

- (void)setDouble:(nonnull NSString *)groupName key:(nonnull NSString *)key value:(double)value
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults setDouble:value forKey:[self getKeyName:groupName key:key]];
    }
}

- (nonnull NSString *)getString:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        NSString *value = [userDefaults stringForKey:[self getKeyName:groupName key:key]];

        if (value != nil)
        {
            return value;
        }
    }

    return @"";
}

- (int32_t)getInteger:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        return (int32_t)[userDefaults integerForKey:[self getKeyName:groupName key:key]];
    }

    return 0;
}

- (int64_t)getLong:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        NSNumber *value = [userDefaults objectForKey:[self getKeyName:groupName key:key]];

        if (value != nil)
        {
            return [value longLongValue];
        }
    }

    return 0;
}

- (BOOL)getBool:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        return [userDefaults boolForKey:[self getKeyName:groupName key:key]];
    }

    return NO;
}

- (float)getFloat:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        return [userDefaults floatForKey:[self getKeyName:groupName key:key]];
    }

    return 0.0;
}

- (double)getDouble:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        return [userDefaults doubleForKey:[self getKeyName:groupName key:key]];
    }

    return 0.0;
}

- (void)clear:(nonnull NSString *)groupName
{
    NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier];
    [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain];
}

- (BOOL)getBoolWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(BOOL)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            return [userDefaults boolForKey:[self getKeyName:groupName key:key]];
        }
    }

    return defaultValue;
}

- (double)getDoubleWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(double)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            return [userDefaults doubleForKey:[self getKeyName:groupName key:key]];
        }
    }

    return defaultValue;
}

- (float)getFloatWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(float)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            return [userDefaults floatForKey:[self getKeyName:groupName key:key]];
        }
    }

    return defaultValue;
}

- (int32_t)getIntegerWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(int32_t)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            return (int32_t)[userDefaults integerForKey:[self getKeyName:groupName key:key]];
        }
    }

    return defaultValue;
}

- (int64_t)getLongWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(int64_t)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            NSNumber *value = [userDefaults objectForKey:[self getKeyName:groupName key:key]];

            if (value != nil)
            {
                return [value longLongValue];
            }
        }
    }

    return defaultValue;
}

- (nonnull NSString *)getStringWithDefaultValue:(nonnull NSString *)groupName key:(nonnull NSString *)key defaultValue:(nonnull NSString *)defaultValue
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:groupName key:key]])
        {
            NSString *value = [userDefaults stringForKey:[self getKeyName:groupName key:key]];

            if (value != nil)
            {
                return value;
            }
        }
    }

    return defaultValue;
}

- (BOOL)has:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        if ([[[userDefaults dictionaryRepresentation] allKeys] containsObject:key])
        {
            return YES;
        }
    }

    return NO;
}

- (void)remove:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];

    if (userDefaults != nil)
    {
        [userDefaults removeObjectForKey:[self getKeyName:groupName key:key]];
    }
}

- (NSString *)getKeyName:(nonnull NSString *)groupName key:(nonnull NSString *)key
{
    if (groupName == nil || [groupName length] == 0)
    {
        return [NSString stringWithFormat:@"%@", key];
    }
    else
    {
        return [NSString stringWithFormat:@"%@[%@]", groupName, key];
    }
}

@end
