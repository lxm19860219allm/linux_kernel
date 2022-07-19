//在多处理器系统中，每处理器变量为每个处理器生成一个变量的副本，每个处理器访问自己的副本，从而避免处理器之间互斥和处理器缓存之间的同步，提高程序的执行速率。
//写一个内核模块，创建一个per-cpu变量，并且初始化per-cpu变量，修改per-cpu变量的值，将这些值进行输出。
 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/percpu.h>
#include <linux/cpumask.h>

static DEFINE_PER_CPU(long, cpuvar)=5;
static long __percpu *cpualloc;

static int __init my_init(void)
{
    int cpu;
    pr_info("Module Loaded at 0x%p\n",my_init);
    for_each_possible_cpu(cpu) {
        per_cpu(cpuvar,cpu)=10;
        pr_info("Init: Cpuvar on CPU %d=%ld\n",cpu, get_cpu_var(cpuvar));
    }
    put_cpu_var(cpuvar);
  
    __this_cpu_var(cpuvar);
    cpualloc=alloc_percpu(long);
    for_each_possible_cpu(cpu) {
        *per_cpu_ptr(cpualloc, cpu)=6688;
        pr_info("init: cpu:%d cpualloc=%ld\n", cpu, *per_cpu_ptr(cpualloc,cpu));
    }
    return 0;
}

static void __exit my_exit(void)
{ 
    int cpu;
    pr_info("Exit mODULE......\n");
    for_each_possible_cpu(cpu {
        pr_info("Cpuvar cpu %d=%ld\n", cpu, per_cpu(cpuvar, cpu));
        pr_info("exit: cpualloc %d=%lf\n",cpu, *per_cpu_ptr(cpualloc,cpu));
    }
    free_percpu(cpualloc);
    pr_info("end: module unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("vico");
MODULE_LICENSE("GPL");
