#include <linux/kernel.h>
#include <linux/file.h>
#include <linux/signal.h>
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
	char msgstate[20];
	char msgon_cpu[20];
	char msgexec_start[40];
	char msgsum_exec_runtime[40];
	char msgvruntime[40];
	char msgprev_sum_exec_runtime[40];
	char msgnr_migrations[40];
	char msgsp0[40];
	char msgsp1[40];
	struct file *file ;
	loff_t pos = 0;
	int fd;
	int flag = 0;
	char message[1000];
	message[0] = ' ';
	message[1] = '\0';
	mm_segment_t old_fs;// = get_fs();
	struct pid *getpid;
	struct task_struct *task;
	struct sched_entity *se;
	struct thread_struct *thread;
	sigset_t *blocked,*real_blocked;
	getpid = find_get_pid(pid);
	if (getpid == NULL)
		return -14;
	task = pid_task(getpid,PIDTYPE_PID);
	se = &(task->se);
	thread = &(task->thread);
//	char *data = task->comm;
//	printk("%s",task->comm);
	printk("value of state is %ld",task->state);
	strcat(message,"state is ");
	sprintf(msgstate,"%ld",task->state);
	sprintf(msgon_cpu,"%d",task->on_cpu);
	sprintf(msgexec_start,"%llu",se->exec_start);
	sprintf(msgsum_exec_runtime,"%llu",se->sum_exec_runtime);
	sprintf(msgvruntime,"%llu",se->vruntime);
	sprintf(msgprev_sum_exec_runtime,"%llu",se->prev_sum_exec_runtime);
	sprintf(msgnr_migrations,"%llu",se->nr_migrations);
	sprintf(msgsp0,"%llu",thread->sp0);
	sprintf(msgsp1,"%llu",thread->sp);
	strcat(message,msgstate);
	strcat(message,"state :");
	strcat(message,msgstate);
	strcat(message,"\n");
	strcat(message,"on_cpu : ");
	strcat(message,msgon_cpu);
	strcat(message,"\n");
	strcat(message,"exec_start : ");
	strcat(message,msgexec_start);
	strcat(message,"\n");
	strcat(message,"sum_exec_runtime : ");
	strcat(message,msgsum_exec_runtime);
	strcat(message,"\n");
	strcat(message,"vruntime : ");
	strcat(message,msgvruntime);
	strcat(message,"\n");
	strcat(message,"prev_sum_exec_runtime : ");
	strcat(message,msgprev_sum_exec_runtime);
	strcat(message,"\n");
	strcat(message,"nr_migrations: ");
	strcat(message,msgnr_migrations);
	strcat(message,"\n");
	strcat(message,"sp0 : ");
	strcat(message,msgsp0);
	strcat(message,"\n");
	strcat(message,"sp : ");
	strcat(message,msgsp1);
	strcat(message,"\n");

//	strcat(message,task->prio);
	printk("value of prio is %d",task->prio);
//	printk("value of cpu is %d",task->cpu);
	printk("value of static_prio is %d\n",task->static_prio);
	printk("value of normal_prio is %d\n",task->normal_prio);
	printk(KERN_ALERT"value of rt_priority is %d\n",task->rt_priority);
	printk(KERN_ALERT"value of tgid is %d\n",task->tgid);
	printk(KERN_ALERT"value of on_cpu is %d\n",task->on_cpu);
	printk(KERN_ALERT"value of exec_start is %llu\n",se->exec_start);
	printk(KERN_ALERT"value of sum_exec_runtime is %llu\n",se->sum_exec_runtime);
	printk(KERN_ALERT"value of vruntime is %llu\n",se->vruntime);
	printk(KERN_ALERT"value of prev_sum_exec_runtime is %llu\n",se->prev_sum_exec_runtime);
	printk(KERN_ALERT"nr_migrations = %llu\n",se->nr_migrations);
	printk(KERN_ALERT"sp0 is %llu\n",thread->sp0);
	printk(KERN_ALERT"sp is %llu\n",thread->sp);
//	printk("sysenter_cs is %lu\n",thread->sysenter_cs);
//	printk("value of blocked is %s\n",strsignal(task->blocked));
//	printk("value of real_blocked is %x\n",task->real_blocked);
//	printk(KERN_ALERT "writing to the console");
	blocked =&(task->blocked);
	int b = 0;
	int rb = 0;
	real_blocked = &(task->real_blocked);
	int i;
	for(i = 0;i < 64;i++)
	{
		printk("reached in loop %d",i);
		if (sigismember(blocked,i))
			b++;
		if (sigismember(real_blocked,i))
			rb++;
	}

	printk(KERN_ALERT"Number of blocked are %d",b);
	printk(KERN_ALERT"Number of realblocked are %d",rb);
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	// *data = "write to file";
	fd = sys_open(name,O_WRONLY,0644);
	if (fd >=0)
	{
		sys_write(fd,message,strlen(message));
		file = fget(fd);
		if (file)
			{
				vfs_write(file,message,strlen(message),&pos);
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
