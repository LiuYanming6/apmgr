
#ifndef _SAP_INFO_H
#define _SAP_INFO_H

#define MAC_LEN	 6
#define HASH_SAP 10

//slave ap info
typedef struct _SAP_INFO 
{
	ListNode node;
	int sock;
	ListNode head;
    unsigned char macaddr[MAC_LEN];
}SAP_INFO;

void init_sap_info();
SAP_INFO *find_sap_sock(unsigned char * macaddr);
int sap_sock_unset(int sock);
void init_sap_node(SAP_INFO* p_send, int sock);

#endif
