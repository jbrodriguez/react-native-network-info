//
// poke.c
//
// MIT LICENSE
//
// Copyright (c) 2017 Juan B. Rodriguez

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Derived from https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
// Tips from https://developer.apple.com/library/content/documentation/NetworkingInternetWeb/Conceptual/NetworkingOverview/CommonPitfalls/CommonPitfalls.html

#include "poke.h"
#include "wol.h"

int poke(char *host, int port, int timeout)
{
    struct sockaddr_in addr_s;
    short int fd=-1;
    fd_set fdset;
    struct timeval tv;
    int rc;
    int so_error;
    socklen_t len;

    addr_s.sin_family = PF_INET;
    host2addr((char *)host, &addr_s.sin_addr, &addr_s.sin_family);
    addr_s.sin_port = htons(port);

    fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    fcntl(fd, F_SETFL, O_NONBLOCK); // setup non blocking socket

    // make the connection
    rc = connect(fd, (struct sockaddr *)&addr_s, sizeof(addr_s));
    if ((rc == -1) && (errno != EINPROGRESS)) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (rc == 0) {
		printf("connect - socket %s:%d connected.\n", host, port);
        close(fd);
        return 0;
    } /*else {
        // connection attempt is in progress
    } */

    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);
    double interval = timeout / 1000;
    tv.tv_sec = interval;
    tv.tv_usec = 0;

    rc = select(fd + 1, NULL, &fdset, NULL, &tv);
    switch(rc) {
    case 1: // data to read
        len = sizeof(so_error);

        getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_error, &len);

        if (so_error == 0) {
			printf("select - socket %s:%d connected.\n", host, port);
            close(fd);
            return 0;
        } else { // error
			printf("socket %s:%d NOT connected: %s\n", host, port, strerror(so_error));
            close(fd);
			return 1;
        }

    case 0: //timeout
		fprintf(stderr, "connection timeout %.2f trying to connect to %s:%d\n", interval, host, port);
        close(fd);
		return 1;
    }

    close(fd);
    return 0;
}
