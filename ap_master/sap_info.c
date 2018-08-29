/*
 * 创建macaddr 和　sock 及其他信息的表
 * 提供根据macaddr找到sock的函数
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "type.h"
//#include "send.h"
//#include "rcv.h"
//#include "log.h"
//#include "define.h"
#include "list.h"
#include "sap_info.h"


static ListNode g_sap_info[HASH_SAP];

void init_sap_info() 
{
	int i;

	for(i = 0; i < HASH_SAP; i ++) 
	{
		init_node(&g_sap_info[i]);
	}
}

void init_sap_node(SAP_INFO* p_send, int sock) 
{
	init_node(&p_send-> node);
	init_node(&p_send-> head);
	
	p_send-> sock = sock;
	
}

void add_sap_node(SAP_INFO* p_send) 
{
	int hash;
	
	hash = p_send->macaddr[MAC_LEN-1] % HASH_SAP;
	
	add_node(&g_sap_info[hash], &p_send-> node);
}

// not use
void delete_sap_node(SAP_INFO* p_send) 
{
	delete_node(&p_send->node);
	return;
}

// find send sock

SAP_INFO* find_sap_sock(unsigned char *macaddr) 
{	
	SAP_INFO* p_send;
	ListNode* p_node;
	int hash;
	
	hash = macaddr[MAC_LEN-1] % HASH_SAP;
	p_node = g_sap_info[hash].next;
	
	for(; p_node != &g_sap_info[hash]; p_node = p_node-> next) {
		
		p_send = (SAP_INFO*)(p_node);
		if(0 == (memcmp(p_send->macaddr, macaddr, MAC_LEN)))
        {
			return p_send;
		}
	}
	printf("XXX find_sap_sock macaddr not find\n");
	return NULL;
}

//?ṹ?屣?????׽?????-1
int sap_sock_unset(int sock) 
{

	s32 i;
	ListNode* p_node;
	SAP_INFO* p_send;

	log_print_msg("Sock is as follows:\n");

	for(i = 0; i < HASH_SAP; i ++) {

		p_node = g_sap_info[i].next;
		if(p_node == &g_sap_info[i]) {

			continue;
		}

		for(; p_node != &g_sap_info[i]; p_node = p_node-> next) {

			p_send = (SAP_INFO*)(p_node);
			if(sock == p_send->sock)
			{
                i = HASH_SAP;   //?˳???ѭ??
                break;
            }
		}
	}
    p_send->sock = -1;
    printf("%02x-%02x-%02x-%02x-%02x-%02x offline\n", 
        p_send->macaddr[0],p_send->macaddr[1],p_send->macaddr[2],
        p_send->macaddr[3],p_send->macaddr[4],p_send->macaddr[5]);
    return 0;
}

