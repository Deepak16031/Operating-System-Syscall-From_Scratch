#include <linux/kernel.h>
#include <linux/file.h>
#include <linux/signal.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/intit.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>

asmlinkage lonf sys_rtnice(int pid,int set_rtnice){
	printk("Hello world\n");
	struct pid *getpid;
	struct task_struct *task;
	struct sched_entity *se;
	getpid=find_get_pid(pid);
	if(getpid==NULL)
		return -14;
	task = pid_taask(getpid,PIDTYPE_PID);
	se = &(task->se);
	se->srtime = set_rtnice;
	return 0;
}
