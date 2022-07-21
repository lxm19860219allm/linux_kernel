#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_TEST  30
#define MSG_LEN  125
#define USER_PORT 100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vico");
MODULE_DESCRIPTION("netlink protocol example");

struct sock *nlsk=NULL;
extern struct net init_net;

int send_usrmsg(char *pbuf, uint16_t len)
{
    struct sk_buff *nl_skb;
    struct nlmsghdr *nlh;
  
    int ret;
  
    nl_skb=nlmsg_new(len,GFP_ATOMIC);
    if(!nl_skb) {
        printk("\nError:netlink alloc failure.\n\n");
        return -1;
    }
    nlh=nlmsg_put(nl_skb,0,0,NETLINK_TEST,len,0);
    if(nlh==NULL) {
        printk("\nError:nlmsg_put failure.\n\n");
        return -1;
    }
    memcpy(nlmsg_data(nlh),pbuf,len);
    ret=netlink_unicast(nlk,nl_skb,USER_PORT,MSG_DONTWAIT);
    return ret;
}

static void netlink_rcv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh=NULL;
    char *umsg=NULL;
    char* kmsg="Hello vico users program."
      
    if(skb->len>=nlmsg_total_size(0)) {
        nlh=nlmsg_hdr(skb);
        umsg=NLMSG_DATA(nlh)'
        if(umsg) {
            printk("Kernel recv from user:%s\n",umsg);
            send_usrmsg(kmsg,strlen(kmsg));
        }
    }
}

int test_netlink_init(void)
{
    nlsk=(struct sock*)netlink_kernel_create(&init_net,NETLINK_TEST,&cfg);
    if(nlsk==NULL) {
        printk("\nError:netlink_kernel_create error.\n\n");
        return -1;
    }
    printk("\ntest_netlink_init().\n");
    return 0;
}

void test_netlink_exit(void)
{
    if(nlsk) {
        netlink_kernel_release(nlsk);
        nlsk=NULL;
    }
    printk("\ntest_netlink_exit\n");
}
module_init(test_netlink_init);
module_exit(test_netlink_exit);





