#import "EZRSharedDataPlatformServiceImpl.h"

@interface EZRSharedDataPlatformServiceImpl ()
@property (strong, nonatomic) NSString *groupName;
@property (strong, nonatomic) NSUserDefaults *userDefaults;
@end

@implementation EZRSharedDataPlatformServiceImpl

//------------------------------------------------------------------------------
#pragma mark - Class Initializer
//------------------------------------------------------------------------------

+ (instancetype)proxy {
    return [[self alloc] init];
}

//------------------------------------------------------------------------------
#pragma mark - Initialization
//------------------------------------------------------------------------------

- (instancetype)init {
    self = [super init];
    if (self) {

    }
    return self;
}

- (instancetype)initWithGroupName:(NSString *)groupName {
    if (self = [super init]) {
        self.groupName = groupName;
    }
    return self;
}

//------------------------------------------------------------------------------
#pragma mark - EZRSharedDataPlatformServiceImpl
//------------------------------------------------------------------------------

- (void)setString:(nonnull NSString *)key value:(nonnull NSString *)value {
    if (_userDefaults != nil) {
        [_userDefaults setObject:value forKey:[self getKeyName:key]];
    }
}

- (void)setInteger:(nonnull NSString *)key value:(int32_t)value {
    if (_userDefaults != nil) {
        [_userDefaults setInteger:value forKey:[self getKeyName:key]];
    }
}

- (void)setLong:(nonnull NSString *)key value:(int64_t)value {
    if (_userDefaults != nil) {
        [_userDefaults setObject:[NSNumber numberWithLongLong:value] forKey:[self getKeyName:key]];
    }
}

- (void)setBool:(nonnull NSString *)key value:(BOOL)value {
    if (_userDefaults != nil) {
        [_userDefaults setBool:value forKey:[self getKeyName:key]];
    }
}

- (void)setFloat:(nonnull NSString *)key value:(float)value {
    if (_userDefaults != nil) {
        [_userDefaults setFloat:value forKey:[self getKeyName:key]];
    }
}

- (void)setDouble:(nonnull NSString *)key value:(double)value {
    if (_userDefaults != nil) {
        [_userDefaults setDouble:value forKey:[self getKeyName:key]];
    }
}

- (nonnull NSString *)getString:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        NSString *value = [_userDefaults stringForKey:[self getKeyName:key]];
        
        if (value != nil) {
            return value;
        }
    }
    
    return @"";
}

- (int32_t)getInteger:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        return (int32_t)[_userDefaults integerForKey:[self getKeyName:key]];
    }
    
    return 0;
}

- (int64_t)getLong:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        NSNumber *value = [_userDefaults objectForKey:[self getKeyName:key]];
        
        if (value != nil) {
            return [value longLongValue];
        }
    }
    
    return 0;
}

- (BOOL)getBool:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        return [_userDefaults boolForKey:[self getKeyName:key]];
    }
    
    return NO;
}

- (float)getFloat:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        return [_userDefaults floatForKey:[self getKeyName:key]];
    }
    
    return 0.0;
}

- (double)getDouble:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        return [_userDefaults doubleForKey:[self getKeyName:key]];
    }
    
    return 0.0;
}

- (void)save:(BOOL)async autoFinish:(BOOL)autoFinish {
    if (async) {
        [self saveAsync];
    } else {
        [self saveSync];
    }
    
    if (autoFinish) {
        [self finish];
    }
}

- (void)saveAsync {
    [self finish];
}

- (void)saveSync {
    [self finish];
}

- (void)start:(nonnull NSString *)groupName {
    _groupName = groupName;    
    _userDefaults = [NSUserDefaults standardUserDefaults];
}

- (void)finish {
    _groupName = nil;
    _userDefaults = nil;
}

- (void)clear {
    NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier];
    [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain];
}

- (BOOL)getBoolWithDefaultValue:(nonnull NSString *)key defaultValue:(BOOL)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            return [_userDefaults boolForKey:[self getKeyName:key]];
        }
    }
    
    return defaultValue;
}

- (double)getDoubleWithDefaultValue:(nonnull NSString *)key defaultValue:(double)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            return [_userDefaults doubleForKey:[self getKeyName:key]];
        }
    }
    
    return defaultValue;
}

- (float)getFloatWithDefaultValue:(nonnull NSString *)key defaultValue:(float)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            return [_userDefaults floatForKey:[self getKeyName:key]];
        }
    }
    
    return defaultValue;
}

- (int32_t)getIntegerWithDefaultValue:(nonnull NSString *)key defaultValue:(int32_t)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            return (int32_t)[_userDefaults integerForKey:[self getKeyName:key]];
        }
    }
    
    return defaultValue;
}

- (int64_t)getLongWithDefaultValue:(nonnull NSString *)key defaultValue:(int64_t)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            NSNumber *value = [_userDefaults objectForKey:[self getKeyName:key]];
            
            if (value != nil) {
                return [value longLongValue];
            }
        }
    }
    
    return defaultValue;
}

- (nonnull NSString *)getStringWithDefaultValue:(nonnull NSString *)key defaultValue:(nonnull NSString *)defaultValue {
    if (_userDefaults != nil) {
        if ([self has:[self getKeyName:key]]) {
            NSString *value = [_userDefaults stringForKey:[self getKeyName:key]];
            
            if (value != nil) {
                return value;
            }
        }
    }
    
    return defaultValue;
}

- (BOOL)has:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        if ([[[_userDefaults dictionaryRepresentation] allKeys] containsObject:[self getKeyName:key]]) {
            return YES;
        }
    }
    
    return NO;
}

- (void)remove:(nonnull NSString *)key {
    if (_userDefaults != nil) {
        [_userDefaults removeObjectForKey:[self getKeyName:key]];
    }
}

- (NSString *)getKeyName:(nonnull NSString *)key {
    if (_groupName == nil || [_groupName length] == 0) {
        return [NSString stringWithFormat:@"%@", key];
    } else {
        return [NSString stringWithFormat:@"%@[%@]", _groupName, key];
    }
}

@end
