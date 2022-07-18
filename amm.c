#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/vmalloc.h>

static int mem=1024;
#define MB (1024*1024)

static int __init my_init(void)
{
    char *kbuf;
    unsigned long size;
    unsigned long order;
    char *vm_buff;
    /* __get_free_pages() */
    for(size=PAGE_SIZE,order=0; order<MAX_ORDER; order++, size*=2)
    {
        pr_info("order=%2lu,pages=%5lu, size=%8lu ", order, size/PAGE_SIZE, size);
        kbuf=(char*)__get_free_pages(GFP_ATOMIC, order);
        if(!kbuf) {
            pr_err("Testing Function: __get_free_pages Failed.\n");
            break;
        }
        pr_info("Testing --> __get_free_pages OK.\n");
        free_pages((unsigned long)kbuf, order);
    
  
    /* kmalloc() */
    pr_info("/n");
    for(size=PAGE_SIZE,order=0; order<MAX_ORDER;order++,size*=2) {
        pr_info("order=%2lu,page%5lu,size-%8lu ", order, size/PAGE_SIZE, size);
        kbuf=kmalloc((size_t)size,GFP_ATOMIC);
        if(!kbuf) {
            pr_err("Testing Function: kmalloc Failed.\n");
            break;
        }
        pr_info("Testing --> kmalloc() ok.\n");
        kfree(kbuf);
    }
    /* vmalloc */
    pr_info("\n");
    for(size=20*MB;size<=mem*MB;size+=20*MB) {
        pr_info(" pages=%6lu,size=%8lu ", size/PAGE_SIZE, size/MB);
        vm_buff=vmalloc(size);
        if(!vm_buff) {
             pr_err(" Testing --> vmalloc() ok.\n");
             break;
        }
        pr_info(" Testing --> vmalloc() ok.\n");
        vfree(vm_buff());
    }
   
    return 0;
}

static void __exit my_exit(void)
{
    pr_info("Module Exit System OK.");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Vico 2022/07/18");
MODULE_LICENSE("GPL");
