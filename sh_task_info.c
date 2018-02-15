#include <linux/kernel.h>
#include <linux/file.h>
#include<linux/fs.h>
#include<linux/fcntl.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
asmlinkage long sys_sh_task_info(int pid, char *name)
{
//	struct pid *getpid;
//	struct task_struct *task;
//	getpid = find_get_pid(pid);
//	if (getpid == NULL)
//		return -14;
//	task = pid_task(getpid,PIDTYPE_PID);
	struct file *file ;
	loff_t pos = 0;
	int fd;
	int flag = 0;
//	char *data = task->comm;
	mm_segment_t old_fs;// = get_fs();
	struct pid *getpid;
	struct task_struct *task;
	getpid = find_get_pid(pid);
	if (getpid == NULL)
		return -14;
	task = pid_task(getpid,PIDTYPE_PID);
	char *data = task->comm;
//	printk("%s",task->comm);
	printk("value of state is %ld",task->state);
	printk("value of prio is %d",task->prio);
//	printk("value of cpu is %d",task->cpu);
	printk("value of static_prio is %d",task->static_prio);
	printk("value of normal_prio is %d",task->normal_prio);
	printk("value of rt_priority is %d",task->rt_priority);
	printk("value of tgid is %d",task->tgid);
	printk(KERN_ALERT "writing to the console");
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	// *data = "write to file";
	fd = sys_open(name,O_WRONLY|O_CREAT,0644);
	if (fd >=0)
	{
		sys_write(fd,data,strlen(data));
		file = fget(fd);
		if (file)
			{
				vfs_write(file,data,strlen(data),&pos);
				fput(file);
			}
		sys_close(fd);
	}
	else
	{
		flag = 1;
	}
	set_fs(old_fs);
	if (flag == 1)
		return -10;
	return 0;
}
