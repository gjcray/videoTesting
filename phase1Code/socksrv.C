/*
 * socksrv.C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /* for struct sockaddr_in*/

#define BACKLOG 10
#define MYPORT 4000

int main()
{
	char *addr;
	int sockfd;
	int new_fd;
	struct sockaddr_in my_addr, their_addr;

	int res;
	int sin_size;

	char *msg = "Connection Estabished\n";
	int len, bytes_sent;

	char *buf;

	sockfd = socket(AF_INET, /* domain */
					SOCK_STREAM, /* type */
					0); /* protocol */

	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}

	/* Init sockaddr_in */
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero), 8);

	res = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
	if (res == -1) {
		perror("bind");
		exit(1);
	}

	//waiting for connection
	res = listen(sockfd, BACKLOG);
	if (res == -1) {
		perror("listen");
		exit(1);
	}

	// setting up connection
	sin_size = sizeof(struct sockaddr_in);
	new_fd = accept(sockfd, (void *)&their_addr, &sin_size);
	buf = (char *)malloc(255);
	if (buf == NULL) {
		printf("malloc failed\n");
		exit(1);
	}

	//receiving info
	res = recv(new_fd, buf, 255, 0);
	if (res == -1) {
		perror("recv()");
		exit(1);
	}

	len = strlen(msg);
	bytes_sent = send(new_fd,
					msg,
					len,
					0);

	// close connetion
	close(new_fd);

	// clse listening
	close(sockfd);

	printf("recv data:%s\n", buf);
	free(buf);

	system("kmplayer test.mpg");
	return 0;
}
