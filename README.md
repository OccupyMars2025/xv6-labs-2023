## round 2: https://pdos.csail.mit.edu/6.1810/2023/schedule.html
- [x] (4 days)(2024/2/2 7:30 - 2/6 14:10) sep 6: Introduction and examples
- [ ] (2024/2/6 14:10 - ) sep 11:  C in xv6, slides, and examples

## BUILDING AND RUNNING XV6
### You will need a RISC-V "newlib" tool chain from https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for riscv64-softmmu.  Once they are installed, and in your shell search path, you can run "make qemu".

## https://github.com/OccupyMars2025/xv6-labs-2023-deprecated

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

# TODO:
### https://github.com/takahirox/riscv-rust


# hint:
## [Oh, and 6.828 students, if you're having trouble with Lab 5, it's probably because of a bug in your Lab 2.](https://blogs.oracle.com/linux/post/the-ksplice-pointer-challenge)