//
//  DWRegExpUtils.h
//  RegExp
//
//  Created by Wicky on 2016/12/27.
//  Copyright © 2016年 Wicky. All rights reserved.
//

/**
 DWRegExpUtils
 
 正则语句快速生成工具类
 
 以链式语法帮你优雅的按照组件自动生成正则
 
 version 1.0.0
 提供链式语法以组件化生成正则语句
 */

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, DWRegExpComponent) {
    DWRegExpComponentNumber = 1 << 0,///数字
    DWRegExpComponentUppercaseLetter = 1 << 1,///大写字母
    DWRegExpComponentLowercaseLetter = 1 << 2,///小写字母
    DWRegExpComponentChinese = 1 << 3,///汉字
    DWRegExpComponentSymbol = 1 << 4,///符号
    DWRegExpComponentEntireExceptLF = 1 << 5,///除换行符外所有字符
    DWRegExpComponentEntire = 1<< 6,///任意字符（包括\n\r）
    DWRegExpComponentLetter = DWRegExpComponentUppercaseLetter | DWRegExpComponentLowercaseLetter,///任意字母
    DWRegExpComponentPassword = DWRegExpComponentNumber | DWRegExpComponentLetter,///字母数字组合
    DWRegExpComponentCharacter = DWRegExpComponentChinese | DWRegExpComponentLetter | DWRegExpComponentNumber | DWRegExpComponentSymbol,///中英文符号组合
};

typedef NS_ENUM(NSUInteger, DWRegExpCondition) {
    DWRegExpConditionPreSearchAllIS,///预查、全部是
    DWRegExpConditionPreSearchAllNot,///预查、全不是
    DWRegExpConditionPreSearchContain,///预查、是，不全
    DWRegExpConditionPreSearchNotAll,///预查、不全是
    DWRegExpConditionContain,///包含
    DWRegExpConditionWithout///不包含
};

#define DWINTEGERNULL ULONG_MAX

@class DWRegExpUtils;
@interface DWRegExpMaker : NSObject;

/**
 以组件类别生成正则
 */
@property (nonatomic ,copy) DWRegExpMaker * (^AddConditionWithComponentType)(DWRegExpComponent component,DWRegExpCondition condition,NSUInteger minCount,NSUInteger maxCount);

/**
 以正则文本生成正则
 */
@property (nonatomic ,copy) DWRegExpMaker * (^AddConditionWithRegExpString)(NSString * regExpStr,DWRegExpCondition condition,NSUInteger minCount,NSUInteger maxCount);

@end

@interface DWRegExpUtils : NSObject

/**
 以链式语句生成正则
 */
+(NSString *)dw_GetRegExpStringWithMaker:(void(^)(DWRegExpMaker * maker))stringMaker;

/**
 根据组件类型返回正则组件
 */
-(NSString *)dw_GetRegExpComponentStringWithComponents:(DWRegExpComponent)components;

/**
 以正则组件、条件模式、范围生成配置文件
 
 注：若min、max均为DWINTEGERNULL根据不同模式会自动补全范围
 若为预查模式则范围为最小值0，若为包含模式则范围为最小值1
 */
-(NSDictionary *)dw_CreateRegExpConfigWithComponent:(NSString *)component condition:(DWRegExpCondition)condition minCount:(NSUInteger)min maxCount:(NSUInteger)max;

/**
 以配置文件生成正则文本
 */
-(NSString *)dw_GetRegExpStringWithConfigs:(NSArray *)configs;

/**
 验证正则文本
 */
+(BOOL)dw_ValidateString:(NSString *)string withRegExpString:(NSString *)regExp;

@end
