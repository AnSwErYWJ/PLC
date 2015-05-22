#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "common.h"

int client_init(int port, char *ip)
{
	
	int fd;

	fd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&clientaddr,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(port);
	inet_pton(AF_INET,ip,&clientaddr.sin_addr);
	
	return fd;
}


