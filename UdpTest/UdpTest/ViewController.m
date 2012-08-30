//
//  ViewController.m
//  UdpTest
//
//  Created by 安達　彰典 on 12/08/30.
//  Copyright (c) 2012年 安達　彰典. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.button addTarget:self
                               action:@selector(postUdp:) forControlEvents:UIControlEventTouchUpInside];

    self.ipaddrtf.text = [NSString stringWithFormat:@"%s",SV_ADDR];
    self.porttf.text = [NSString stringWithFormat:@"%d",SV_PORT];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)postUdp:(UIButton*)button
{
    int sock;
    struct sockaddr_in addr;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons([self.porttf.text intValue]);
    addr.sin_addr.s_addr = inet_addr([self.ipaddrtf.text cStringUsingEncoding:1]);

    sendto(sock, "HELLO", 5, 0, (struct sockaddr *)&addr, sizeof(addr));
    
    int size;
    char buf[2048];
    char str[16];
    struct sockaddr_in from;
    socklen_t sockaddr_in_size = sizeof(struct sockaddr_in);
    
    size = recvfrom(sock, buf, 2048-1, 0,
                    (struct sockaddr *)&from, &sockaddr_in_size);
    buf[2048-1] = 0;
    
    inet_ntop(AF_INET, &from.sin_addr, str, sizeof(str));
    self.label.text = [NSString stringWithFormat:@"recv data from : %s:%d\ndata :\n%s",str, ntohs(from.sin_port), buf];
    printf("%s\n",buf);
    printf("recv data from : %s:%d\n", str, ntohs(from.sin_port));

    close(sock);
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

@end
