#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "MXSDataEntity.h"
#import "MXSNetManager.h"
#import "MXSNetManagerCache.h"
#import "MXSNetworkTool.h"
#import "UIImage+Compress.h"

FOUNDATION_EXPORT double MXSNetManagerVersionNumber;
FOUNDATION_EXPORT const unsigned char MXSNetManagerVersionString[];

