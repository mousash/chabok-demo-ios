//
//  PushClientMessage.h
//  AdpPushClient
//
//  Created by Farshad Mousalou on 6/14/15.
//  Copyright (c) 2015 Farshad Mousalou. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PushClientMessage : NSObject

@property (nonatomic, readonly) NSString *id;
@property (nonatomic, readonly) NSString *messageBody;
@property (nonatomic, readonly) NSDictionary *data;
@property (nonatomic, readonly) NSString *topicName;
@property (nonatomic, readonly) NSDate *serverTime;
@property (nonatomic, readonly) NSDate *expireTime;
@property (nonatomic, readonly) NSDate *receivedTime;
@property (nonatomic, readonly) NSString *senderId;
@property (nonatomic, readonly) NSString *sentId;
@property (nonatomic, readwrite) BOOL inApp;
@property (nonatomic, readwrite) BOOL stateful;
@property (nonatomic, readwrite) BOOL useAsAlert;
@property (nonatomic, readwrite) BOOL silent;
@property (nonatomic, readwrite) NSString *alertText;

- (instancetype)initWithData:(NSData *)data topic:(NSString *)topic;

- (instancetype)initWithJson:(NSDictionary *)json topic:(NSString *)topic;

- (instancetype)initWithMessage:(NSString *)content topic:(NSString *)topic;

- (instancetype)initWithMessage:(NSString *)content withData:(NSDictionary *)data topic:(NSString *)topic;

- (NSData *)toData;

@end
