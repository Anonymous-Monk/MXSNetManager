//
//  MXSNetManager.h
//  MXSNetManager
//
//  Created by aicai on 2019/8/27.
//  Copyright © 2019 boai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


#define MXSNetManagerShare [MXSNetManager sharedMXSNetManager]

#define MXSWeak  __weak __typeof(self) weakSelf = self

/*! 过期属性或方法名提醒 */
#define MXSNetManagerDeprecated(instead) __deprecated_msg(instead)


/*! 使用枚举NS_ENUM:区别可判断编译器是否支持新式枚举,支持就使用新的,否则使用旧的 */
typedef NS_ENUM(NSUInteger, MXSNetworkStatus)
{
    /*! 未知网络 */
    MXSNetworkStatusUnknown           = 0,
    /*! 没有网络 */
    MXSNetworkStatusNotReachable,
    /*! 手机 3G/4G 网络 */
    MXSNetworkStatusReachableViaWWAN,
    /*! wifi 网络 */
    MXSNetworkStatusReachableViaWiFi
};

/*！定义请求类型的枚举 */
typedef NS_ENUM(NSUInteger, MXSHttpRequestType)
{
    /*! get请求 */
    MXSHttpRequestTypeGet = 0,
    /*! post请求 */
    MXSHttpRequestTypePost,
    /*! put请求 */
    MXSHttpRequestTypePut,
    /*! delete请求 */
    MXSHttpRequestTypeDelete
};

typedef NS_ENUM(NSUInteger, MXSHttpRequestSerializer) {
    /** 设置请求数据为JSON格式*/
    MXSHttpRequestSerializerJSON,
    /** 设置请求数据为HTTP格式*/
    MXSHttpRequestSerializerHTTP,
};

typedef NS_ENUM(NSUInteger, MXSHttpResponseSerializer) {
    /** 设置响应数据为JSON格式*/
    MXSHttpResponseSerializerJSON,
    /** 设置响应数据为HTTP格式*/
    MXSHttpResponseSerializerHTTP,
};

/*! 实时监测网络状态的 block */
typedef void(^MXSNetworkStatusBlock)(MXSNetworkStatus status);

/*! 定义请求成功的 block */
typedef void( ^ MXSResponseSuccessBlock)(id response);
/*! 定义请求失败的 block */
typedef void( ^ MXSResponseFailBlock)(NSError *error);

/*! 定义上传进度 block */
typedef void( ^ MXSUploadProgressBlock)(int64_t bytesProgress,
                                       int64_t totalBytesProgress);
/*! 定义下载进度 block */
typedef void( ^ MXSDownloadProgressBlock)(int64_t bytesProgress,
                                         int64_t totalBytesProgress);

/*!
 *  方便管理请求任务。执行取消，暂停，继续等任务.
 *  - (void)cancel，取消任务
 *  - (void)suspend，暂停任务
 *  - (void)resume，继续任务
 */
typedef NSURLSessionTask MXSURLSessionTask;

@class MXSDataEntity;



NS_ASSUME_NONNULL_BEGIN

@interface MXSNetManager : NSObject

/**
 创建的请求的超时间隔（以秒为单位），此设置为全局统一设置一次即可，默认超时时间间隔为30秒。
 */
@property (nonatomic, assign) NSTimeInterval timeoutInterval;

/**
 设置网络请求参数的格式，此设置为全局统一设置一次即可，默认：MXSHttpRequestSerializerJSON
 */
@property (nonatomic, assign) MXSHttpRequestSerializer requestSerializer;

/**
 设置服务器响应数据格式，此设置为全局统一设置一次即可，默认：MXSHttpResponseSerializerJSON
 */
@property (nonatomic, assign) MXSHttpResponseSerializer responseSerializer;

/**
 自定义请求头：httpHeaderField
 */
@property(nonatomic, strong) NSDictionary *httpHeaderFieldDictionary;

/**
 将传入 的 string 参数序列化
 */
@property(nonatomic, assign) BOOL isSetQueryStringSerialization;

/**
 是否开启 log 打印，默认不开启
 */
@property(nonatomic, assign) BOOL isOpenLog;

/*!
 *  获得全局唯一的网络请求实例单例方法
 *
 *  @return 网络请求类MXSNetManager单例
 */
+ (instancetype)sharedMXSNetManager;


#pragma mark - 网络请求的类方法 --- get / post / put / delete

/**
 网络请求的实例方法 get
 
 @param entity 请求信息载体
 @param successBlock 请求成功的回调
 @param failureBlock 请求失败的回调
 @param progressBlock 进度回调
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_request_GETWithEntity:(MXSDataEntity *)entity
                                  successBlock:(MXSResponseSuccessBlock)successBlock
                                  failureBlock:(MXSResponseFailBlock)failureBlock
                                 progressBlock:(MXSDownloadProgressBlock)progressBlock;

/**
 网络请求的实例方法 post
 
 @param entity 请求信息载体
 @param successBlock 请求成功的回调
 @param failureBlock 请求失败的回调
 @param progressBlock 进度
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_request_POSTWithEntity:(MXSDataEntity *)entity
                                   successBlock:(MXSResponseSuccessBlock)successBlock
                                   failureBlock:(MXSResponseFailBlock)failureBlock
                                  progressBlock:(MXSDownloadProgressBlock)progressBlock;

/**
 网络请求的实例方法 put
 
 @param entity 请求信息载体
 @param successBlock 请求成功的回调
 @param failureBlock 请求失败的回调
 @param progressBlock 进度
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_request_PUTWithEntity:(MXSDataEntity *)entity
                                  successBlock:(MXSResponseSuccessBlock)successBlock
                                  failureBlock:(MXSResponseFailBlock)failureBlock
                                 progressBlock:(MXSDownloadProgressBlock)progressBlock;

/**
 网络请求的实例方法 delete
 
 @param entity 请求信息载体
 @param successBlock 请求成功的回调
 @param failureBlock 请求失败的回调
 @param progressBlock 进度
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_request_DELETEWithEntity:(MXSDataEntity *)entity
                                     successBlock:(MXSResponseSuccessBlock)successBlock
                                     failureBlock:(MXSResponseFailBlock)failureBlock
                                    progressBlock:(MXSDownloadProgressBlock)progressBlock;

/**
 上传图片(多图)
 
 @param entity 请求信息载体
 @param successBlock 上传成功的回调
 @param failureBlock 上传失败的回调
 @param progressBlock 上传进度
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_uploadImageWithEntity:(MXSDataEntity *)entity
                                  successBlock:(MXSResponseSuccessBlock)successBlock
                                   failurBlock:(MXSResponseFailBlock)failureBlock
                                 progressBlock:(MXSUploadProgressBlock)progressBlock;

/**
 视频上传
 
 @param entity 请求信息载体
 @param successBlock 成功的回调
 @param failureBlock 失败的回调
 @param progressBlock 上传的进度
 */
+ (void)mxs_uploadVideoWithEntity:(MXSDataEntity *)entity
                    successBlock:(MXSResponseSuccessBlock)successBlock
                    failureBlock:(MXSResponseFailBlock)failureBlock
                   progressBlock:(MXSUploadProgressBlock)progressBlock;

/**
 文件下载
 
 @param entity 请求信息载体
 @param successBlock 下载文件成功的回调
 @param failureBlock 下载文件失败的回调
 @param progressBlock 下载文件的进度显示
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_downLoadFileWithEntity:(MXSDataEntity *)entity
                                   successBlock:(MXSResponseSuccessBlock)successBlock
                                   failureBlock:(MXSResponseFailBlock)failureBlock
                                  progressBlock:(MXSDownloadProgressBlock)progressBlock;

/**
 文件上传
 
 @param entity 请求信息载体
 @param successBlock successBlock description
 @param failureBlock failureBlock description
 @param progressBlock progressBlock description
 @return MXSURLSessionTask
 */
+ (MXSURLSessionTask *)mxs_uploadFileWithWithEntity:(MXSDataEntity *)entity
                                     successBlock:(MXSResponseSuccessBlock)successBlock
                                     failureBlock:(MXSResponseFailBlock)failureBlock
                                    progressBlock:(MXSUploadProgressBlock)progressBlock;


#pragma mark - 网络状态监测
/*!
 *  开启实时网络状态监测，通过Block回调实时获取(此方法可多次调用)
 */
+ (void)mxs_startNetWorkMonitoringWithBlock:(MXSNetworkStatusBlock)networkStatus;

#pragma mark - 自定义请求头
/**
 *  自定义请求头
 */
+ (void)mxs_setValue:(NSString *)value forHTTPHeaderKey:(NSString *)HTTPHeaderKey;

/**
 删除所有请求头
 */
+ (void)mxs_clearAuthorizationHeader;

#pragma mark - 取消 Http 请求
/*!
 *  取消所有 Http 请求
 */
+ (void)mxs_cancelAllRequest;

/*!
 *  取消指定 URL 的 Http 请求
 */
+ (void)mxs_cancelRequestWithURL:(NSString *)URL;

/**
 清空缓存：此方法可能会阻止调用线程，直到文件删除完成。
 */
- (void)mxs_clearAllHttpCache;

@end

NS_ASSUME_NONNULL_END
