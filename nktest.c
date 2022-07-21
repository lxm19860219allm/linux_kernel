#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <net/netlink.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

#define NETLINK_TEST 30
#define MSG_LEN 125
#define MAX_PLOAD 125

typedef struct _user_msg_info
{
    struct nlmsghdr hdr;
    char msg[MSG_LEN];
}user_msg_info;

int main(int argc, char** argv)
{
    int skfd;
    int ret;
    user_msg_info u_info;
    socklen_t len;
    struct nlmsghdr *nlh=NULL;
    struct sockaddr_nl saddr,daddr;
    char *umsg="Hello Netlink protocol.";
  
    skfd=socket(AF_NETLINK.SOCK_RAW,NETLINK_TEST);
    if(skfd==-1){
        perror("\nError: create socket error.\n\n");
        return 0;
    }
    memset(&saddr,0,sizeof(saddr));
    saddr.nl_family=AF_NETLINK;
    saddr.nl_pid=100;
    saddr.nl_group=0;
  
    if(bind(skfd,(struct sockaddr*)&saddr, sizeof(saddr))!=0)
    {
        perror("\nError:bind() error.\n\n");
        close(skfd);
        return -1;
    }
  
    memset(&daddr,0,sizeof(daddr));
    daddr.nl_family=AF_NETLINK;
    daddr.nl_pid=100;
    daddr.nl_group=0;
  
    nlh=(struct nlmsghdr*)malloc();
    memset(nlh,0,sizeof(struct nlmsghdr));
  
    return 0;
}
