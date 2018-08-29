
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "type.h"
#include "time.h"

static Timer* p_tm;

int client_init(struct sockaddr_in *their_addr)
{
	int sockfd = -1;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd) {

		printf("Failed to create socket. \n");
		return -1;
	}

	if(-1 == connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr))){

		printf("Cannot connect. \n");
		return -1;
	}

    return sockfd;
}

static void hello(void* param) {

	int sockfd = *(int *)param;
	str = 
	send(sockfd, "client", s);

	start_timer(p_tm);
}


int main(int argc, char *argv[]) 
{
	int sockfd;
    struct sockaddr_in their_addr;

	if(argc < 2) {

		printf("No ip and port info.\n");
		exit(1);
	}
	their_addr.sin_family = AF_INET;
	their_addr.sin_addr.s_addr = inet_addr(argv[1]);
	their_addr.sin_port = htons(atoi(argv[2]));
	bzero(&their_addr.sin_zero, 8);
	sockfd = client_init(&their_addr);

	// init cloud

	cloud_init();

	// create timer

	p_tm = create_timer(5, hello, &sockfd);
	assert(p_tm);

	start_timer(p_tm);

	//  run cloud

	cloud_run(0);

	return 0;
}
