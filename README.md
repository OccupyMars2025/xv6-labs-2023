## 2023/11/9 - 12/2: round 1, failure
## 2024/2/2 - 4/5: round 2
# ===============================

## TODO: study the test code of each lab, study the Makefile of each lab, complete the "Optional Challenge" part of each lab, re-study the "net" lab
## https://pdos.csail.mit.edu/6.1810/2023/schedule.html
## https://xiayingp.gitbook.io/build_a_os
## https://risc-v-getting-started-guide.readthedocs.io/en/latest/
# https://pdos.csail.mit.edu/6.1810/2023/labs/traps.html
# It will be easier to look at traps with gdb if you tell qemu to use only one CPU, which you can do by running `make CPUS=1 qemu-gdb`, then `(gdb) set $sstatus=0x200000020` to disable all interrupts, especially the timer interrupt
```
You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".
This issue may be helpful:
https://github.com/OccupyMars2025/xv6-labs-2023/issues/10
```

## [related resources on csdiy](https://csdiy.wiki/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/MIT6.S081/)
# goal: 2024/2/2 - 4/5: thoroughly complete learning this course
- [x] (4 days)(2024/2/2 7:30 - 2/6 14:10) sep 6: Introduction and examples
- [x] (3 hours)(2024/2/6 14:10 - 17:05) sep 11:  C in xv6, slides, and examples
- [x] (7 days)(2024/2/6 17:05 - 2/13 13:58)sep 13: OS design
  - [x] (3 days)(2024/2/6 17:05 - 2/9 18:00) sep 13: OS design, chapter 2
  - [x] (2 days)(2024/2/9 18:00 - 2/11 15:40) sep 13: OS design, lecture
  - [x] (2024/2/11 15:40 - ) sep 13: OS design, Assignment: Lab syscall: System calls
    - [x] (3h 23min)Using gdb (easy): 2024/2/12 13:00 - 16:23
    - [x] (2h 10min)System call tracing (moderate): 2024/2/13 8:30 - 10:40
    - [x] (48 min)Sysinfo (moderate): 2/13 13:10 - 13:58
- [x] (4 days)(2/13 13:58 - 2/17 10:10)sep 18: page tables
- [x] (3 days)(2/17 10:10 - 2/20 15:20)	sep 20:GDB Calling conventions
  - [x] (2 days)(2/17 10:10 - 2/19 10:30)	complete reading material
  - [x] (1 day)(2/19 10:30 - 2/20 15:20) Lab pgtbl: Page tables
    - [x] (2h 35min)(2/20 6:25 - 9:00) Speed up system calls (easy)
    - [x] (1h 35min)(2/20 9:00 - 10:35) Print a page table (easy)
    - [x] (2h 40min)(2/20 12:40 - 15:20) Detect which pages have been accessed (hard)
- [x] (2 days 25min)(2024/2/20 15:20 - 2/22 15:45)sep 25: LEC 6: System call entry/exit
  - [x] (1 day 6h)(2/20 15:20 - 2/21 21:50) Read Chapter 4, except 4.6
  - [x] (8h 45min)(2/22 7:00 - 2/22 15:45) lecture: https://pdos.csail.mit.edu/6.1810/2023/lec/l-internal.txt
- [x] (2 days 2h)(2024/2/22 15:45 - 2/24 17:30)sep 27:LEC 7: Page faults
  - [x] (9h)(2024/2/22 15:45 - 2/23 0:24)Read Section 4.6, 4.7
  - [x] (7h 30min)(2/23 7:20 - 14:50) slides
  - [x] (2h)(2/23 14:50 - 16:50) https://pdos.csail.mit.edu/6.1810/2023/lec/l-pgfaults.txt
  - [x] (1 day)(2/23 18:00 - 2/24 17:30)Lab: traps
    - [x] (3h)(2/23 19:00 - 22:00)RISC-V assembly (easy)
    - [x] (3h 55min)(2/24 7:40 - 11:20, 11:44 - 11:59) Backtrace (moderate)
    - [x] (4h 20min)(2/24 13:10 - 17:30) Alarm (hard)
- [x] (23h)(2024/2/24 17:30 - 2/25 16:30)oct 2: LEC 8: Q&A labs (slides)
  - [x] (4h 50min)(2/24 20:00 - 22:20, 2/25 9:30 - 12:00) slides
  - [x] (3h 10min)(2/25 13:20 - 16:30) LEC 8: Q&A labs
- [x] (2024/2/25 16:30 - 3/4 15:20)oct 4: LEC 9: Device drivers
  - [x] (1 day 8h)(2/26 8:30 - 2/27 16:30)Read Chapter 5
  - [x] (2/27 19:00 - 2/29 15:50) Lecture 9: Device drivers
  - [x] (2/29 15:50 - 3/4 15:20) Lab: Copy-on-Write Fork for xv6
    - [x] (2/29 22:40) bug: https://github.com/OccupyMars2025/xv6-labs-2023/issues/9
    - [x] (3/4 7:00 - 15:20) complete this lab successfully
# ========== why so slow ==================
- [x] (3/4 15:20 - 3/16 7:30) oct 11: LEC 10: Locking
  - [x] (3/4 17:00 - 3/15 18:00) read chapter 6: Locking
  - [x] (3/15 18:00 - 3/16 7:30) lecture, Locking
# ============================
- [x] (3/16 7:30 - 3/20 9:40)  oct 16, LEC 11 (rtm): Scheduling 1
  - [x] (3/16 7:30 - 3/19 18:00) Read "Chapter 7: Scheduling" 
  - [x] (3/19 18:00 - 3/20 9:40) lecture 11 (rtm): Scheduling 1
- [x] (3/20 9:40 - 3/21 20:40) LEC 12 (rtm): Coordination, code
  - [x] (3/20 9:40 - 19:40) Lecture 12: Coordination (sleep&wakeup)
  - [x] (3/20 19:40 - 3/21 20:40) Lab: Multithreading
    - [x] (3/20 19:40 - 3/21 15:40) Uthread: switching between threads (moderate)
    - [x] (3/21 15:40 - 19:40) Using threads (moderate)
    - [x] (3/21 19:40 - 20:40) Barrier(moderate)
# ============================
### Don't worry about the details at first; just get a feel for how the manual is structured so you can find things later. The E1000 has many advanced features, most of which you can ignore. Only a small set of basic features is needed to complete this lab.
# Never read a manual like a textbook. This is not how the manual is used
- [x] (3/21 20:40 - 3/24 17:20) oct 25, Assignment: Lab net: Network driver
  - [x] (3/21 20:40 - 3/23 18:20) read Section 1, 2, 3.2 of the manual like a textbook
  - [x] (3/23 18:20 - 3/24 17:20) read the source code, complete the lab
### Reading the source code is much more enjoyable than reading the manual     
# ============================
- [x] (3/24 17:20 - 3/30 7:30) nov 1, LEC 13 (ab): File systems
  - [x] (3/24 17:20 - 3/29 18:00) read Chapter 8: File system
  - [x] (3/29 18:00 - 3/30 7:30) lecture
- [ ] (3/30 7:30 - ) nov 6, LEC 14 (ab): Crash recovery
      


## Q: How to read the source code ?
## A: Go to each branch, read the commits by OccupyMars2025
### =====================
### In each lab, don't edit the file "README", it is needed, for example in "trace 32 grep hello README", you can add another file "README.md"
## BUILDING AND RUNNING XV6
### You will need a RISC-V "newlib" tool chain from https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for riscv64-softmmu.  Once they are installed, and in your shell search path, you can run "make qemu".

## https://github.com/OccupyMars2025/xv6-labs-2023-deprecated
## [QEMU: Keys in the character backend multiplexer](https://www.qemu.org/docs/master/system/mux-chardev.html)
### Ctrl-a c : "Rotate between the frontends", so just use "Ctrl-a c" twice to switch back to the original frontend
## useful commands:
```
xv6 has no ps command, but, if you type Ctrl-p, the kernel will print information about each process. If you try it now, you'll see two lines: one for init, and one for sh.

To quit qemu type: Ctrl-a x (press Ctrl and a at the same time, followed by x).

riscv64-linux-gnu-objdump -S user/_cat
  same as user/cat.asm
0x0: cat
  what if we run two cat programs at the same time?
  see pgtbl lecture
0x8e: _main
  user.ld:
    entry: _main
what is _main?
  defined in ulib.c, which calls main() and exit(0)
where is data memory? (e.g., buf)
  in data/bss segment
  must be setup by kernel
but we know address where buf should be
  riscv64-linux-gnu-nm -n user/_cat
```
## Use GDB to help you debug! I know that using GDB is really annoying in the beginning but it is super super helpful in the later labs and we want you all to know the basic commands to make debugging less painful in the future.
## it is worth your time to revisit the following tutorials when tracking down kernel bugs. 
# =======================
```
https://pdos.csail.mit.edu/6.1810/2023/labs/traps.html

It will be easier to look at traps with gdb if you tell qemu to use only one CPU, which you can do by running
    make CPUS=1 qemu-gdb
```
# =======================
# add the following functions to help debug:
# 1. [print page table](https://github.com/OccupyMars2025/xv6-labs-2023/commit/0dac84319f52691399963bc1a2c003229925778d)
## https://pdos.csail.mit.edu/6.1810/2023/lec/l-QA1_2.pdf, page 13
## https://pdos.csail.mit.edu/6.1810/2023/labs/pgtbl.html
# 2. [backtrace](https://github.com/OccupyMars2025/xv6-labs-2023/commit/bc1a1cbdec7abf75a3d167c1318c41cff885bf34)
## gdb has "backtrace" command in itself, you don't need to add it
## https://pdos.csail.mit.edu/6.1810/2023/labs/traps.html
## Once your backtrace is working, call it from panic in kernel/printf.c so that you see the kernel's backtrace when it panics.
```
    backtrace:
    0x0000000080002cda
    0x0000000080002bb6
    0x0000000080002898
  
After bttest exit qemu. In a terminal window: run addr2line -e kernel/kernel (or riscv64-unknown-elf-addr2line -e kernel/kernel) and cut-and-paste the addresses from your backtrace, like this:
    $ addr2line -e kernel/kernel
    0x0000000080002de2
    0x0000000080002f4a
    0x0000000080002bfc
    Ctrl-D
  
You should see something like this:
    kernel/sysproc.c:74
    kernel/syscall.c:224
    kernel/trap.c:85
```

# =======================
## when you enter "make qemu-gdb", you can see the following infomation about file system:
```
nmeta 46 (boot, super, log blocks 30 inode blocks 13, bitmap blocks 1) blocks 1954 total 2000
balloc: first 915 blocks have been allocated
balloc: write bitmap block at sector 45
```
# [How to use GDB to debug xv6:](https://pdos.csail.mit.edu/6.1810/2023/lec/l-os.txt)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/syscall.html)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/gdb.html)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/guidance.html)
# [Using the GNU Debugger](https://pdos.csail.mit.edu/6.828/2019/lec/gdb_slides.pdf)
# [calling convention and debug](https://pdos.csail.mit.edu/6.1810/2023/lec/l-riscv.txt)
# [gdb: System call entry/exit](https://pdos.csail.mit.edu/6.1810/2023/lec/l-internal.txt)
# [use gdb to examine thread switching/scheduler()/sched()](https://pdos.csail.mit.edu/6.1810/2023/lec/l-threads.txt)
# Caution: if the interrupts (particularly the timer interrupt) are NOT disabled, then when you debug, the "next" command may take you to some strange location
# [use gdb to debug interrupt process](https://pdos.csail.mit.edu/6.1810/2023/lec/l-interrupt.txt)
## very useful: use "(gdb) watch cons" and "(gdb) watch uart_tx_buf" to see the changes in "cons" and "uart_tx_buf", you can see how "you keystroke", "console" and "uart" interact with each other.   "user/sh.c" -> main() -> getcmd() -> gets() -> read() -> sys_read() -> fileread() -> consoleread() to read the characters that I typed in the console.
```
https://pdos.csail.mit.edu/6.1810/2023/lec/l-internal.txt
use gdb to check system call entry/exit

$ make clean
$ make qemu-gdb
(you can see "-gdb tcp::26000" in the last line of the output)

(now open a new terminal)
$ riscv64-unknown-elf-gdb
(gdb) target remote localhost:26000
(gdb) file user/_sh
(gdb) break getcmd
(gdb) c
(gdb) info breakpoints
(gdb) layout split 
(gdb) b write
(gdb) x/3i 0xe10
(gdb) p $a0
(gdb) p (char*)$a1
$11 = 0x1310 "$ "
(gdb) x/2c $a1
0x1310:	36 '$'	32 ' '
(gdb) p $a2

(si "ecall", you can see that you get to "uservec")

(gdb) file kernel/kernel
(gdb) break usertrap
(gdb) c

can we tell that we're in supervisor mode?
  I don't know a way to find the mode directly.
but once you execute "ecall" and get to "uservec", you can see the following,
but actually at this time "satp" still points to the user page table
(gdb) p (char*)$a1
$11 = 0x1310 <error: Cannot access memory at address 0x1310>
(gdb) x/2c $a1
0x1310:	Cannot access memory at address 0x1310
(gdb) 

```

```

building xv6
  % make 
  gcc on each kernel/*.c, .o files, linker, kernel/kernel
  % ls -l kernel/kernel
  % more kernel/kernel.asm
  and produces a disk image containing file system
  % ls -l fs.img

qemu
  % make qemu
  qemu, loads kernel binary into "memory", simulates a disk with fs.img
  jumps to kernel's first instruction
  qemu maintains mock hardware registers and RAM, interprets instructions

I'll walk through xv6 booting up, to first process making first system call

% make CPUS=1 qemu-gdb
% riscv64-unknown-elf-gdb
(gdb) b *0x80000000
(gdb) c
kernel is loaded at 0x80000000 b/c that's where RAM starts
  lower addresses are device hardware
% vi kernel/entry.S
"m mode"
set up stack for C function calls
jump to start, which is C code

% vi start.c
  sets up hardware for interrupts &c
  changes to supervisor mode
  jumps to main

(gdb) b main
(gdb) c
(gdb) tui enable

main()
  core 0 sets up a lot of software / hardware
  other cores wait
  "next" through first kernel printfs

let's glance at an example of initialization -- kernel memory allocator
(gdb) step -- into kinit()
(gdb) step -- into freerange()
(gdb) step -- into free()
% vi kernel/kalloc.c
kinit/freerange find all pages of physical RAM
  make a list from them
  threaded through the first 64 bytes of each page
  [diagram]
  struct run
  the cast in kfree()
  and the list insert
  a simple allocator, only 4096-byte units, for e.g. user memory

how to get processes going?
  our goal is to get the first C user-level program running
    called init (see user/init.c)
    init starts up everything else (just console sh on xv6)
  need:
    struct proc
    user memory
    instruction bytes in user memory
    user registers, at least sp and epc
  main() does this by calling userinit()

(gdb) b userinit
(gdb) continue

% vi kernel/proc.c
allocproc()
  struct proc
  p->pagetable

back to userinit()

% vi user/initcode.S
exec("/init", ...)
ecall
a7, SYS_exec
% vi kernel/syscall.h
note SYS_exec is number 7

back to userinit()

epc -- where process will start in *user* space
and sp
p->state = RUNNABLE

(gdb) b *0x0
(gdb) c
(gdb) tui disable
(gdb) x/10i 0

what's the effect of ecall?
(gdb) b syscall
(gdb) c
back in the kernel
(gdb) tui enable
(gdb) n
(gdb) n
(gdb) n
(gdb) print num
      from saved user register a7
(gdb) print syscalls[7]
(gdb) b exec
(gdb) c

% vi kernel/exec.c
  a complex system call
  read file from disk
  "ELF" format
  text, data
  defensive, lots of checks
  don't be tricked into overwriting kernel memory!
  allocate stack
  write arguments onto stack
  epc = 
  sp = 

(gdb) c

% vi user/init.c
  top-level process
  console file descriptors, 0 and 1
  sh

```

## If you want to see what assembly code the compiler generates for the xv6 kernel or find out what instruction is at a particular kernel address, see the file kernel/kernel.asm, which the Makefile produces when it compiles the kernel. (The Makefile also produces .asm for all user programs.)


## https://pdos.csail.mit.edu/6.1810/2023/labs/syscall.html
```
The user-space "stubs" that route system calls into the kernel are in user/usys.S, which is generated by user/usys.pl when you run make. 
Declarations are in user/user.h
The kernel-space code that routes a system call to the kernel function that implements it is in kernel/syscall.c and kernel/syscall.h.
Process-related code is kernel/proc.h and kernel/proc.c.
```

## https://github.com/OccupyMars2025/xv6-riscv

# trap: system call , exception, interrupt
```
A trap may occur while executing in user space if the user program makes a system call (ecall 
instruction), or does something illegal, or if a device interrupts. The high-level path of a trap from
user space is uservec (kernel/trampoline.S:21), then usertrap (kernel/trap.c:37); and when re-
turning, usertrapret (kernel/trap.c:90) and then userret (kernel/trampoline.S:101).
```
# =======================
# TODO:
## [Here's a more whimsical description of little- and big-endian](https://www.rfc-editor.org/ien/ien137.txt)
## https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html
## study the source code of Makefile, grade-lab-* and other auxiliary files in each lab
## all "Optional challenge exercises" of the labs are NOT done
## all exercises on book-xv6-riscv-rev3.pdf are NOT done
## https://pdos.csail.mit.edu/6.1810/2023/reference.html
## [sep 27, LEC 7: Cool things you can do with virtual memory (slides)](https://pdos.csail.mit.edu/6.1810/2023/lec/l-usingvm.pdf)
## [sep 27, LEC 7: Cool things you can do with virtual memory ](https://pdos.csail.mit.edu/6.1810/2023/lec/l-pgfaults.txt)
### Key idea: Combination of page faults and updating page table is powerful!
### [How to handle page faults ? You can refer to this exercise "Alarm (hard)"](https://pdos.csail.mit.edu/6.1810/2023/labs/traps.html)
## Can you hack xv6-riscv ?
## Instead of gcc and gdb, can you use LLVM tools to compile and debug xv6-riscv ?
### The RISC-V Reader: An Open Architecture Atlas
### https://github.com/takahirox/riscv-rust
## In "oct 2:LEC 8: Q&A labs (slides)", there is some discussion about how Linux implements the features that you implement in xv6.
# =======================
# other OS courses:
## 2024/2/2 - 3/15: [xv6-riscv](https://github.com/OccupyMars2025/xv6-labs-2023)
## [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)
## [Operating Systems (Honor Track) Peking University, 2023 Spring](https://pku-os.github.io/sp23/)
## https://kaashoek.github.io/65810-2023/
## https://pdos.csail.mit.edu/6.824/
## https://web.mit.edu/6.033/www/
## MIT course: 6.1910 (6.004)
## https://rcore-os.cn/rCore-Tutorial-Book-v3/index.html
# =======================

# hint:
## [Oh, and 6.828 students, if you're having trouble with Lab 5, it's probably because of a bug in your Lab 2.](https://blogs.oracle.com/linux/post/the-ksplice-pointer-challenge)
