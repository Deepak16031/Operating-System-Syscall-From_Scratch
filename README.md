Contributors:-
Deepak Malik -2016031 
Ashish Rana  -2016022

Discalamer - Before proceeding please read this to the last, we are not here by any means responsible for non-operational machine

Note :- 
a)If wwant to test the system call jump to patching after extracting the downloaded kernel source.

To check the current version of the kernel            uname -r
Download the kernel version 3.13.0 
http://archive.ubuntu.com/ubuntu/pool/main/l/linux/linux_3.13.0.orig.tar.gz

Kernel Compilation-
First go to the folder of downloaded file, then open termianl there.
Commands-
for extracting --->     tar xf linux_3.13.0.orig.tar.gz
change directory to the extractacted folder --->       cd linux-3.13/

copying the .config file to the boot folder and then compilations of files required for kernel compilation using the make file:-
copying --->  sudo cp /boot/config-$(uname -r) .config
command --->  sudo make oldconfig

Kernel and its module compilation-
But first type --->    nproc  // it will give some value

sudo make -j 2*int_value_given_by_nproc         //  what the heck is -j ? Find yourself(Hint : obviously something related to nproc)
sudo make modules_install -j k     // k - same above
sudo make install -j k

Using this command-
sudo apt-get install libdev(dont remenber the exact name)


Adding the system System Call:-

Then to make the system call, we first boot into our kernel and go to the directory "linux-3.13" and then make a directory for our system call code and write the system call in it (details of implementation later) and write the code and made the Makefile for it.
Then we go to the kernel Makefile and changed line “core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ “ to “core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ oursystemcallFolderName/ “ to let the compiler know that our source files for our system call is inside the folder and it will comipile it along.

Then we go to the systemcall table /home/user/linux-3.13/arch/x64/syscalls/  and added the system call number in the system call table in file syscall_64.tbl
Then we go to the System call header file in /home/user/linux-3.13/include/linux/syscalls.h and added the declaration of our systemcall in the end of file
asmlinkage long sys_sh_task_info(int pid,char *name);

After that we recompiled our kernel using commands--> 
sudo make -j 4
sudo make install -j 4 
and then boot into the newly compiled kernel and tested the ystem call.

Now implementation details of our system call is given in the file name as sh_task_info.c'
Makefile is required to address kernel which file we want to compile.

Fore testing the system call:-
Compile the test file and run it.

Input :  user should give the pid number of process and file name   // use ps command to seem some currently running processes
Output : Output will be the details of task_struct in the file specified.

Error values :  if user give wrong pid then ERRNO will be set to -14 And will return 0 if everything goes fine.

Generating diff :-
Note:- Adding the System call part should be done to the extracted folder directly without any step of compilation
diff is the difference in the source code of two sources.
command  ---> sudo diff -urN /home/deepak/linux-3.13/ /usr/src/linux-3.13/ > linuxpatch

Patching:-
Go to the root directory of the extracted source
command --->  cd linux-3.13/

patch the source:-
command ---> sudo patch -p3 linuxpatch

Why use -p3 as a flag?
When we create the diff of the changed sources, the directory of that source is not root it have some path which have to be skip so that patching can be done .
If we have done all this in root, we would have used -p0. 

Now, follow from steps after extracting the downloaded file in kernel compilation part.

References : 

https://medium.freecodecamp.org/building-and-installing-the-latest-linux-kernel-from-source-6d8df5345980  (for compiling kernel)

https://tssurya.wordpress.com/2014/08/19/adding-a-hello-world-system-call-to-linux-kernel-3-16-0/  (we take the idea from hello world system call added here)

http://tuxthink.blogspot.in/2012/07/module-to-find-task-from-its-pid.html (for implementation of system call)
