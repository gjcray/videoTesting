/*
 * sockclnt.h
 * open a client socket to trigger the host for playing video
 */

#ifndef SOCKCLNT_H
#define SOCKCLNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in */
#include <arpa/inet.h>
#include <unistd.h>

int Socket_trigger(int DEST_PORT);

#endif
