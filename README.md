## https://pdos.csail.mit.edu/6.1810/2023/labs/lock.html

## before run "kalloctest", "statistics" has already existed. Attention: "tot= 0"
```c
// user/init.c: main
  if(open("console", O_RDWR) < 0){
    mknod("console", CONSOLE, 0);
    mknod("statistics", STATS, 0);
    open("console", O_RDWR);
  }
```
### Attention: "cat: read error", "statistics" is not a file, so maybe you cannot use "cat statistics" to get its data
```
hart 1 starting
hart 2 starting
init: starting sh
$ cat statistics
--- lock kmem/bcache stats
lock: kmem: #test-and-set 0 #acquire() 32991
lock: bcache: #test-and-set 0 #acquire() 1180
--- top 5 contended locks:
lock: virtio_disk: #test-and-set 88691 #acquire() 141
lock: proc: #test-and-set 10049 #acquire() 289186
lock: proc: #test-and-set 9090 #acquire() 289176
lock: cons: #test-and-set 4852 #acquire() 31
lock: cons: #test-and-set 4852 #acquire() 31
tot= 0
cat: read error
$    

```

## in user/kalloctest.c, if we only run test1() before the lab, we get 

```
$ kalloctest
start test1
ntas() return 0
test1 results:
--- lock kmem/bcache stats
lock: kmem: #test-and-set 25617 #acquire() 433108
lock: bcache: #test-and-set 0 #acquire() 2124
--- top 5 contended locks:
lock: proc: #test-and-set 96355 #acquire() 468939
lock: virtio_disk: #test-and-set 75144 #acquire() 156
lock: proc: #test-and-set 35125 #acquire() 868846
lock: proc: #test-and-set 34272 #acquire() 868839
lock: kmem: #test-and-set 25617 #acquire() 433108
tot= 25617
ntas() return 25617
test1 FAIL

```

# bug occurs: https://github.com/OccupyMars2025/xv6-labs-2023/issues/12


## [how to debug](https://pdos.csail.mit.edu/6.1810/2023/labs/guidance.html)
```
If you want to see what assembly code the compiler generates for the xv6 kernel or find out what instruction is at a particular kernel address, see the file kernel/kernel.asm, which the Makefile produces when it compiles the kernel. (The Makefile also produces .asm for all user programs.)

If the kernel causes an unexpected fault (e.g. uses an invalid memory address), it will print an error message that includes the program counter ("sepc") at the point where it crashed; you can search kernel.asm to find the function containing that program counter, or you can run addr2line -e kernel/kernel pc-value (run man addr2line for details). If you want to get backtrace, restart using gdb: run 'make qemu-gdb' in one window, run gdb (or riscv64-linux-gnu-gdb) in another window, set breakpoint in panic ('b panic'), followed by followed by 'c' (continue). When the kernel hits the break point, type 'bt' to get a backtrace.

If your kernel hangs, perhaps due to a deadlock, you can use gdb to find out where it is hanging. Run run 'make qemu-gdb' in one window, run gdb (riscv64-linux-gnu-gdb) in another window, followed by followed by 'c' (continue). When the kernel appears to hang hit Ctrl-C in the qemu-gdb window and type 'bt' to get a backtrace.

qemu has a "monitor" that lets you query the state of the emulated machine. You can get at it by typing control-a c (the "c" is for console). A particularly useful monitor command is info mem to print the page table. You may need to use the cpu command to select which core info mem looks at, or you could start qemu with make CPUS=1 qemu to cause there to be just one core.
```
