 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "type.h"
#include "socket.h"
#include "rcv.h"
#include "sap_info.h"


// on connect
//创建结构体，包括
//fd 
void is_connected(RCV_SOCK* p_hand) 
{
    //stdio
    if (0 == p_hand->sock)
    {
        return;
    }
	printf("is_connected \n");
    SAP_INFO *p_send;
	p_send = malloc(sizeof(SAP_INFO));
	if(p_send) 
    {   
        bzero(p_send, sizeof(SAP_INFO));
    	init_sap_node(p_send, p_hand->sock);
    	add_sap_node(p_send);
	}

    return;
}

// on close
void is_close(RCV_SOCK* p_hand) 
{
    sap_sock_unset(p_hand->sock);
    return;
}

// on read
void is_read(RCV_SOCK* p_hand) {
	s8* buf;
    s8 *sendBuf = NULL;
	u32 len;
	STATUS result;
    SAP_INFO *p_sap = NULL;

	result = get_rcv_buf(p_hand->sock, &buf, &len);
	if (FALSE == result)
	{
        return;
    }
	printf("rcv from client: %s\n", buf);
    //if heardbeat,update sap_info:mac ip status ...

    unsigned char mac[6] = {0};//test use
    p_sap = find_sap_sock(mac);

    sendBuf = malloc(512);
    if ((p_sap) && (p_sap->sock > 0) && (sendBuf))
    {
        memset(sendBuf, 0, sizeof(512));
        memcpy(sendBuf, buf, strlen(buf));
	    send_buf(p_sap->sock, sendBuf, strlen(buf));
    }
    
	free(buf);//rember to free

    return;
}


// entry of executive file

int main(int argc, char *argv[]) 
{
	STATUS result;
	int sock;

	if(argc < 2) {

		printf("No port parameter.\n");
		exit(1);
	}

    //初始化从ap信息
	init_sap_info();

	// init cloud

	cloud_init();

	// register call back

	register_callback_func(is_connected, is_close, is_read);

	// new socket

	result = create_server_socket(&sock, atoi(argv[1]));
	assert(result == TRUE);

	//  run cloud

	cloud_run(sock);

	return 0;
}
