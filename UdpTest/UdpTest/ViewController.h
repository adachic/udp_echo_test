//
//  ViewController.h
//  UdpTest
//
//  Created by 安達　彰典 on 12/08/30.
//  Copyright (c) 2012年 安達　彰典. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

@interface ViewController : UIViewController

#define SV_ADDR "182.48.53.36"
#define SV_PORT (12345)

@property IBOutlet UIButton *button;
@property IBOutlet UITextView *label;
@property IBOutlet UITextField *ipaddrtf;
@property IBOutlet UITextField *porttf;

- (void)postUdp:(UIButton*)button;
@end
