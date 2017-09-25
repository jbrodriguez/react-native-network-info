//
//  RNNetworkInfo.h
//  RNNetworkInfo
//
//  Created by Corey Wilson on 7/12/15.
//  Copyright (c) 2015 eastcodes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridge.h>
#import "wol.h"
#import "SimplePing.h"
#import "GCDAsyncSocket.h"


@interface RNNetworkInfo : NSObject<RCTBridgeModule, SimplePingDelegate>

@property (nonatomic, strong, readwrite, nullable) SimplePing* pinger;
@property (nonatomic, strong, readwrite, nullable) NSTimer* sendTimer;
@property (nonatomic, strong, readwrite, nonnull) NSNumber* timeout;

@property (nonatomic, strong, readwrite, nullable) socket* GCDAsyncSocket;

@property (nonatomic, strong, readwrite, nullable) RCTResponseSenderBlock callback;

@end
