#import "EZRFileHelperPlatformServiceImpl.h"

@interface EZRFileHelperPlatformServiceImpl ()

@end

@implementation EZRFileHelperPlatformServiceImpl

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
#pragma mark - EZRFileHelperPlatformServiceImpl
//------------------------------------------------------------------------------

- (BOOL)createFile:(nonnull NSString *)path
{
    @try
    {
        NSData *fileContents = [@"" dataUsingEncoding:NSUTF8StringEncoding];

        [[NSFileManager defaultManager] createFileAtPath:path
                                                contents:fileContents
                                              attributes:nil];

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)createFileWithStringContent:(nonnull NSString *)path
                            content:(nonnull NSString *)content
{
    @try
    {
        NSData *fileContents = [content dataUsingEncoding:NSUTF8StringEncoding];

        [[NSFileManager defaultManager] createFileAtPath:path
                                                contents:fileContents
                                              attributes:nil];

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)createFileWithBinaryContent:(nonnull NSString *)path
                            content:(nonnull NSData *)content
{
    @try
    {
        [[NSFileManager defaultManager] createFileAtPath:path
                                                contents:content
                                              attributes:nil];

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)createDir:(nonnull NSString *)path
{
    @try
    {
        NSError *error;

        [[NSFileManager defaultManager] createDirectoryAtPath:path
                                  withIntermediateDirectories:NO
                                                   attributes:nil
                                                        error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return NO;
        }

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (nonnull NSArray<NSString *> *)listFiles:(nonnull NSString *)path
{
    @try
    {
        NSArray *dirContent = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                                  error:nil];

        NSMutableArray *files = [[NSMutableArray alloc] init];

        [dirContent enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            NSString *filename = (NSString *)obj;
            NSString *filePath = [path stringByAppendingPathComponent:filename];

            if (filename != nil)
            {
                if (filePath != nil)
                {
                    [files addObject:filePath];
                }
            }
        }];

        return files;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @[];
}

- (nonnull NSString *)getExtension:(nonnull NSString *)path
{
    @try
    {
        NSString *extension = [path pathExtension];

        if (extension == nil)
        {
            extension = @"";
        }

        return extension;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSString *)getFilename:(nonnull NSString *)path
{
    @try
    {
        NSString *filename = [path lastPathComponent];

        if (filename == nil)
        {
            filename = @"";
        }

        return filename;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSString *)getBasename:(nonnull NSString *)path
{
    @try
    {
        NSString *basename = [[path lastPathComponent] stringByDeletingPathExtension];

        if (basename == nil)
        {
            basename = @"";
        }

        return basename;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSString *)getFilenameFromUrl:(nonnull NSString *)url
{
    @try
    {
        NSString *filename = [[NSURL URLWithString:url] lastPathComponent];

        if (filename == nil)
        {
            filename = @"";
        }

        return filename;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSString *)getBasenameFromUrl:(nonnull NSString *)url
{
    @try
    {
        NSString *basename = [[[NSURL URLWithString:url] lastPathComponent] stringByDeletingPathExtension];

        if (basename == nil)
        {
            basename = @"";
        }

        return basename;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (BOOL)removeFile:(nonnull NSString *)path
{
    @try
    {
        NSError *error;

        [[NSFileManager defaultManager] removeItemAtPath:path
                                                   error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return NO;
        }

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)removeDir:(nonnull NSString *)path
{
    @try
    {
        NSError *error;

        [[NSFileManager defaultManager] removeItemAtPath:path
                                                   error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return NO;
        }

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)isDir:(nonnull NSString *)path
{
    @try
    {
        BOOL isDir;
        BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:path
                                                           isDirectory:&isDir];

        if (exists && isDir)
        {
            return YES;
        }
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)isFile:(nonnull NSString *)path
{
    @try
    {
        BOOL isDir;
        BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:path
                                                           isDirectory:&isDir];

        if (exists && !isDir)
        {
            return YES;
        }
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (int64_t)getFileSize:(nonnull NSString *)path
{
    @try
    {
        NSError *error;

        NSDictionary *attrs = [[NSFileManager defaultManager] attributesOfItemAtPath:path
                                                                               error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return 0;
        }

        return (int64_t)[attrs fileSize];
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return 0;
}

- (BOOL)copyFile:(nonnull NSString *)from
              to:(nonnull NSString *)to
{
    @try
    {
        NSError *error;

        [[NSFileManager defaultManager] copyItemAtPath:from
                                                toPath:to
                                                 error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return NO;
        }

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (BOOL)moveFile:(nonnull NSString *)from
              to:(nonnull NSString *)to
{
    @try
    {
        NSError *error;

        [[NSFileManager defaultManager] moveItemAtPath:from
                                                toPath:to
                                                 error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return NO;
        }

        return YES;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return NO;
}

- (nonnull NSString *)join:(nonnull NSString *)first
                    second:(nonnull NSString *)second
{
    @try
    {
        return [first stringByAppendingPathComponent:second];
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSString *)getFileContentAsString:(nonnull NSString *)path
{
    @try
    {
        NSError *error;
        NSString *content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return @"";
        }

        return content;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

- (nonnull NSData *)getFileContentAsBinary:(nonnull NSString *)path
{
    @try
    {
        NSError *error;
        NSData *content = [NSData dataWithContentsOfFile:path];

        if (error != nil)
        {
            NSLog(@"%@", error.description);
            return [[NSData alloc] init];
        }

        return content;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return [[NSData alloc] init];
}

- (nonnull NSString *)getHomeDir
{
    @try
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];

        if (documentsDirectory == nil)
        {
            documentsDirectory = @"";
        }

        return documentsDirectory;
    }
    @catch (NSException *exception)
    {
        NSLog(@"%@", exception.reason);
    }

    return @"";
}

@end
