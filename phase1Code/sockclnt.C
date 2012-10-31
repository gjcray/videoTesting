/* 
 * sockclnt.c
 */

#include "sockclnt.h"
#define DEST_IP "192.168.1.106"
int Socket_trigger(int DEST_PORT)
{
	int res;
	int sockfd;
	struct sockaddr_in dest_addr;

	char *msg = "Hello world\n";
	int len, bytes_sent;

	char *buf;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket()");
		exit(1);
	}

	//setup info for connection
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DEST_PORT);	//remote port
	dest_addr.sin_addr.s_addr = inet_addr(DEST_IP); // remote ip
	bzero(&(dest_addr.sin_zero), 8);

	// conneting remote host
	res = connect(sockfd, (struct sockaddr *)&dest_addr, 
												sizeof(struct sockaddr_in));
	if (res == -1) {
		perror("connect()");
		exit(1);
	}

	len = strlen(msg);
	bytes_sent = send(sockfd,
				msg, // content
				len, // length of content
				0); // mark of sending, usually is 0

	buf = (char *)malloc(255);
	if (buf == NULL) {
		printf("malloc failed\n");
		exit(1);
	}

	res = recv(sockfd, buf, 255, 0);
	if (res == -1) {
		perror("recv()");
		exit(1);
	}

	// close the socket
	close(sockfd);

	printf("recv data:%s\n", buf);
	free(buf);

	return 0;
}	  
