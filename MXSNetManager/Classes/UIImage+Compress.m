//
//  UIImage+Compress.m
//  BANetManager
//
//  Created by aicai on 2019/8/27.
//  Copyright © 2019 boai. All rights reserved.
//

#import "UIImage+Compress.h"

@implementation UIImage (Compress)

+(JPEGImage *)needCompressImage:(UIImage *)image size:(CGSize )size scale:(CGFloat )scale
{
    JPEGImage *newImage = nil;
    //创建画板
    UIGraphicsBeginImageContext(size);
    
    //写入图片
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    
    //得到新的图片
    newImage = UIGraphicsGetImageFromCurrentImageContext();
    
    //释放画板
    UIGraphicsEndImageContext();
    
    //比例压缩
    newImage = [UIImage imageWithData:UIImageJPEGRepresentation(newImage, scale)];
    //    newImage = [UIImage imageWithData:UIImageJPEGRepresentation(newImage, 1.0) scale:scale];
    
    return newImage;
}

+(JPEGImage *)needCompressImageData:(NSData *)imageData size:(CGSize )size scale:(CGFloat )scale
{
    PNGImage *image = [UIImage imageWithData:imageData];
    return [UIImage needCompressImage:image size:size scale:scale];
}

+ (JPEGImage *)needCenterImage:(UIImage *)image size:(CGSize )size scale:(CGFloat )scale
{
    /* 想切中间部分,待解决 */
    //#warning area of center image
    JPEGImage *newImage = nil;
    //创建画板
    UIGraphicsBeginImageContext(size);
    
    //写入图片,在中间
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    
    //得到新的图片
    newImage = UIGraphicsGetImageFromCurrentImageContext();
    
    //释放画板
    UIGraphicsEndImageContext();
    
    //比例压缩
    newImage = [UIImage imageWithData:UIImageJPEGRepresentation(newImage, scale)];
    
    return newImage;
}

+(JPEGImage *)jpegImageWithPNGImage:(PNGImage *)pngImage
{
    return [UIImage needCompressImage:pngImage size:pngImage.size scale:1.0];
}

+(JPEGImage *)jpegImageWithPNGData:(PNGData *)pngData
{
    PNGImage *pngImage = [UIImage imageWithData:pngData];
    return [UIImage needCompressImage:pngImage size:pngImage.size scale:1.0];
}

+(JPEGData *)jpegDataWithPNGData:(PNGData *)pngData
{
    return UIImageJPEGRepresentation([UIImage jpegImageWithPNGData:pngData], 1.0);
}

+(JPEGData *)jpegDataWithPNGImage:(PNGImage *)pngImage
{
    return UIImageJPEGRepresentation([UIImage jpegImageWithPNGImage:pngImage], 1.0);
}

@end
