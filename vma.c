//编写一个内核模块，遍历一个用户进程中所有VMA，并且打印这个属性信息，比如VMA大小，起始地址，结束地址等。
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>

static int pid;
module_param(pid, int, S_IRUGO);

static void PrintFunc(struct task_struct *task)
{
    struct mm_struct *mm;
    struct vm_area_struct *vma;
    int i=0;
    unsigned long start, end, length;
  
    mm=task->mm;
    pr_info("mm=%p \n", mm);
    
    vma=mm->mmap;
    down_read(&mm->mmap_sem);
    pr_info("vmas:vma start end\t\tlength\n");
  
    while(vma)
    {
        i++;
        start=vma->vm_start;
        end=vma->vm_end;
        length=end-start;
        pr_info("%d : %p--%lx--%lx=%ld\n", i, vma, start, end, length);
        vma=vma->vm_next;
    }
    up_read(&mm->mmap_sem);
}

static int __init myvma_init(void)
{
    struct task_struct *task;
    if(pid) {
        task=current;
        pid=current->pid;
    }
    else {
        task=pid_task(find_vpid(pid), PIDTYPE_PID);
    }
    if(!task) {
        return -1;
    }
    pr_info("Exam vma's for pid=%d,command=%s\n", pid, task->comm);
    PrintFunc(task);
    return 0;
}

static void __exit myvma_exit(void)
{
    pr_info("\n Module uninstalled sucessfully.\n");
}

module_init(myvma_init);
module_exit(myvma_exit);

MODULE_AUTHOR("Vico");
MODULE_LICENSE("GPL");

