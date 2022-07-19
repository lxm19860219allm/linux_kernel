//编写一个内核模块，创建名称为“mycaches”的slab描述符，大小为40字节，align为8字节，flag为0，从这个slab描述符中分配一个空闲对象。
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/init.h>

static char *kbuf;
static int size 40;
static struct kmem_cache *my_caches;
module_param(size, int, 0644);

static int __init myslab_init(void)
{
    if(size>KMALLOC_MAX_SIZE) {
        pr_err(" Size=%d is too big. You can't have more than %lu.\n", size, KMALLOC_MAX_SIZE);
        return -1;
    }
    my_caches=kmem_cache_create("mycaches",size,0,SLAB_HWCACHE_ALIGN,NULL);
    if(!my_caches) {
        pr_err(" kmem_cache_create() Failed.\n");
        return -ENOMEM;
    }
    pr_info(" create mycaches correct.\n");
    
    kbuf=kmem_cache_alloc(my_caches,GFP_ATOMIC);
    if(!kbuf) {
        pr_err(" Create a cache object Failed.\n");
        (void)kmem_cache_destroy(my_caches);
        return -1;
    }
    return 0;
}

static void __exit myslab_exit(void)
{

}

module_init(myslab_init);
module_exit(myslab_exit);

MODULE_AUTHOR("vico");
MODULE_LICENSE("GPL");
