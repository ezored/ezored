#import "EZRHttpClientPlatformServiceImpl.h"

@interface EZRHttpClientPlatformServiceImpl ()

@end

@implementation EZRHttpClientPlatformServiceImpl

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
        //
    }
    return self;
}

//------------------------------------------------------------------------------
#pragma mark - EZRHttpClientPlatformServiceImpl
//------------------------------------------------------------------------------

- (nonnull EZRHttpResponse *)doRequest:(nonnull EZRHttpRequest *)request
{
    // general
    NSURL *nsurl = [[NSURL alloc] initWithString:[request url]];

    NSMutableURLRequest *urlRequest = [NSMutableURLRequest requestWithURL:nsurl];
    [urlRequest setHTTPMethod:[self getMethodFromHttpMethod:[request method]]];

    // headers
    if ([request headers] != nil && [request headers].count > 0)
    {
        for (EZRHttpHeader *header in [request headers])
        {
            if ([header name] != nil && [header value] != nil)
            {
                [urlRequest setValue:[header value] forHTTPHeaderField:[header name]];
            }
        }
    }

    // request data
    NSString *body = @"";

    if ([request params] != nil && [request params].count > 0)
    {
        for (EZRHttpRequestParam *param in [request params])
        {
            if ([param name] != nil && [param value] != nil)
            {
                NSString *format;

                if (body != nil && [body length] > 0)
                {
                    format = @"&%@=%@";
                }
                else if (body != nil)
                {
                    format = @"%@=%@";
                }

                body = [body stringByAppendingString:[NSString stringWithFormat:format, [param name], [param value]]];
            }
        }
    }
    else
    {
        if ([request body] != nil)
        {
            body = [request body];
        }
    }

    // request data
    if (body != nil)
    {
        NSData *requestData = [body dataUsingEncoding:NSUTF8StringEncoding];

        if (requestData != nil)
        {
            [urlRequest setHTTPBody:requestData];
            [urlRequest setValue:[NSString stringWithFormat:@"%lu", (unsigned long)[requestData length]] forHTTPHeaderField:@"Content-Length"];
        }
    }

    // prepare and do the request
    NSURLResponse *response = nil;
    NSError *error = nil;
    NSData *receivedData = [self sendSynchronousRequest:urlRequest returningResponse:&response error:&error];
    NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;

    if (error != nil)
    {
        return [[EZRHttpResponse alloc] initWithCode:((int)[httpResponse statusCode]) body:@"" url:[request url] headers:@[]];
    }

    // get response body
    NSString *responseBody = @"";
    [NSString stringEncodingForData:receivedData encodingOptions:nil convertedString:&responseBody usedLossyConversion:nil];

    // get response headers
    NSDictionary *responderHeaders = [(NSHTTPURLResponse *)response allHeaderFields];
    NSMutableArray<EZRHttpHeader *> *headers = [NSMutableArray array];

    if (responderHeaders != nil)
    {
        for (NSString *headerName in responderHeaders)
        {
            if (headerName != nil)
            {
                NSString *headerValue = responderHeaders[headerName];

                if (headerValue != nil)
                {
                    EZRHttpHeader *header = [[EZRHttpHeader alloc] initWithName:headerName value:headerValue];
                    [headers addObject:header];
                }
            }
        }
    }

    return [[EZRHttpResponse alloc] initWithCode:((int)[httpResponse statusCode]) body:responseBody url:[request url] headers:headers];
}

- (nonnull NSString *)getMethodFromHttpMethod:(EZRHttpMethod)method
{
    switch (method)
    {
    case EZRHttpMethodMethodGet:
        return @"GET";
        break;

    case EZRHttpMethodMethodPost:
        return @"POST";
        break;

    case EZRHttpMethodMethodPut:
        return @"PUT";
        break;

    case EZRHttpMethodMethodHead:
        return @"HEAD";
        break;

    case EZRHttpMethodMethodPatch:
        return @"PATCH";
        break;

    case EZRHttpMethodMethodTrace:
        return @"TRACE";
        break;

    case EZRHttpMethodMethodDelete:
        return @"DELETE";
        break;

    case EZRHttpMethodMethodConnect:
        return @"CONNECT";
        break;

    case EZRHttpMethodMethodOptions:
        return @"OPTIONS";
        break;

    default:
        return @"";
        break;
    }
}

- (NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse **)response error:(NSError **)error
{
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);

    NSError __block *err = NULL;
    NSData __block *data;
    NSURLResponse __block *resp;

    [[[NSURLSession sharedSession] dataTaskWithRequest:request
                                     completionHandler:^(NSData *_data, NSURLResponse *_response, NSError *_error) {
                                         resp = _response;
                                         err = _error;
                                         data = _data;
                                         dispatch_group_leave(group);
                                     }] resume];

    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);

    if (response)
    {
        *response = resp;
    }

    if (error)
    {
        *error = err;
    }

    return data;
}

@end
