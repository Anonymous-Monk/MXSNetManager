//
//  MXSNetManagerCache.m
//  BANetManager
//
//  Created by aicai on 2019/8/27.
//  Copyright © 2019 boai. All rights reserved.
//

#import "MXSNetManagerCache.h"
#import "YYCache.h"

static NSString * const kMXSNetManagerCache = @"MXSNetManagerCache";
static  YYCache *_dataCache;


@implementation MXSNetManagerCache

+ (void)initialize
{
    _dataCache = [YYCache cacheWithName:kMXSNetManagerCache];
}

/**
 异步缓存网络数据,根据请求的 url 与 parameters
 
 @param httpData 服务器返回的数据
 @param urlString 请求的 URL 地址
 @param parameters 请求的参数
 */
+ (void)mxs_setHttpCache:(id)httpData
              urlString:(NSString *)urlString
             parameters:(NSDictionary *)parameters
{
    NSString *cacheKey = [self mxs_cacheWithUrlString:urlString parameters:parameters];
    [_dataCache setObject:httpData forKey:cacheKey];
}

/**
 根据请求的 URL 与 parameters 异步取出缓存数据
 
 @param urlString 请求的URL
 @param parameters 请求的参数
 @return 缓存的服务器数据
 */
+ (id)mxs_httpCacheWithUrlString:(NSString *)urlString
                     parameters:(NSDictionary *)parameters
{
    NSString *cacheKey = [self mxs_cacheWithUrlString:urlString parameters:parameters];
    return [_dataCache objectForKey:cacheKey];
}

/**
 根据请求的 URL 与 parameters 异步取出缓存数据
 
 @param urlString 请求的URL
 @param parameters 请求的参数
 @param block 异步回调缓存的数据
 */
+ (void)mxs_httpCacheWithUrlString:(NSString *)urlString
                       parameters:(NSDictionary *)parameters block:(void(^)(id <NSCoding> responseObject))block
{
    NSString *cacheKey = [self mxs_cacheWithUrlString:urlString parameters:parameters];
    [_dataCache objectForKey:cacheKey withBlock:^(NSString * _Nonnull key, id<NSCoding>  _Nonnull object) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            block(object);
        });
    }];
    
}

+ (NSString *)mxs_cacheWithUrlString:(NSString *)urlString
                         parameters:(NSDictionary *)parameters
{
    if (!parameters)
    {
        return urlString;
    }
    if ([parameters isKindOfClass:[NSDictionary class]])
    {
        NSData *cacheData = [NSJSONSerialization dataWithJSONObject:parameters options:0 error:nil];
        NSString *cacheString = [[NSString alloc] initWithData:cacheData encoding:NSUTF8StringEncoding];
        
        NSString *cacheKey = [NSString stringWithFormat:@"%@%@", urlString, cacheString];
        return cacheKey;
    }
    return nil;
}

/**
 返回此缓存中对象的总大小（以M为单位）。
   此方法可能阻止调用线程，直到文件读取完成。
 
 @return 总对象的大小（以M为单位）。
 */
+ (CGFloat)mxs_getAllHttpCacheSize
{
    return [_dataCache.diskCache totalCost]/1024.0/1024.0;
}

/**
 清空缓存。
   此方法可能会阻止调用线程，直到文件删除完成。
 */
+ (void)mxs_clearAllHttpCache
{
    [_dataCache.diskCache removeAllObjects];
}


@end
