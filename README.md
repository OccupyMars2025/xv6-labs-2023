## https://pdos.csail.mit.edu/6.1810/2023/schedule.html
## [related resources on csdiy](https://csdiy.wiki/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/MIT6.S081/)
# goal: 2024/2/2 - 4/25: thoroughly complete learning this course
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
- [ ] (2024/2/22 15:45 - )sep 27:LEC 7: Page faults
  - [x] (9h)(2024/2/22 15:45 - 2/23 0:24)Read Section 4.6, 4.7
  - [x] (7h 30min)(2/23 7:20 - 14:50) slides
  - [x] (2h)(2/23 14:50 - 16:50) https://pdos.csail.mit.edu/6.1810/2023/lec/l-pgfaults.txt
  - [ ] (2/23 18:00 - )Lab: traps
    - [x] (3h)(2/23 19:00 - 22:00)RISC-V assembly (easy)
    - [ ] (2/24 7:40 - ) Backtrace (moderate)




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
# [How to use GDB to debug xv6:](https://pdos.csail.mit.edu/6.1810/2023/lec/l-os.txt)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/syscall.html)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/gdb.html)
# [use gdb](https://pdos.csail.mit.edu/6.1810/2023/labs/guidance.html)
# [Using the GNU Debugger](https://pdos.csail.mit.edu/6.828/2019/lec/gdb_slides.pdf)
# [calling convention and debug](https://pdos.csail.mit.edu/6.1810/2023/lec/l-riscv.txt)
# [gdb: System call entry/exit](https://pdos.csail.mit.edu/6.1810/2023/lec/l-internal.txt)
# Caution: if the interrupts (particularly the timer interrupt) are NOT disabled, then when you debug, the "next" command may take you to some strange location
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
## Can you hack xv6-riscv ?
## Instead of gcc and gdb, can you use LLVM tools to compile and debug xv6-riscv ?
### The RISC-V Reader: An Open Architecture Atlas
### https://github.com/takahirox/riscv-rust

# =======================


# hint:
## [Oh, and 6.828 students, if you're having trouble with Lab 5, it's probably because of a bug in your Lab 2.](https://blogs.oracle.com/linux/post/the-ksplice-pointer-challenge)
