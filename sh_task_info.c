#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/pid.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/proc_fs.h>
asmlinkage long sys_sh_task_info(int pid,char *file)
{
/*	type casting caller function may pass an intger to the function
	struct task_struct *proc = find_task_by_vpid(pid);
	if((long)task_pid_nr(proc) < 0){
		return -14;
	}
	printk("printing before referencing");
	printk("process : %s      pid: %ld \n ",proc->comm, \
				 (long)task_pid_nr(proc));
	printk("The process  pid is  %lu", (long) pid);
	return 133;
*/
	struct pid *getpid;
	struct  task_struct *gettask;
	getpid= find_get_pid(pid);
	if(getpid == NULL){
		return -14;
	
	}
	gettask=pid_task(getpid,PIDTYPE_PID);// taken from manual  directly
	printk("process : %s		pid: %ld\n " , gettask->comm, \
					(long)task_pid_nr(gettask));
	return 0;

}
