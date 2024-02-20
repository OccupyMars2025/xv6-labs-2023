#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


#ifdef LAB_PGTBL
int
sys_pgaccess(void)
{
  uint64 base_address;
  argaddr(0, &base_address);

  int len;
  argint(1, &len);
  if(len > 64) {
    printf("sys_pgaccess: error: len > 64, you can only check at most 64 pages\n");
    return -1;
  }

  uint64 mask_address;
  argaddr(2, &mask_address);

  uint64 mask = 0;
  struct proc* p = myproc();
  pte_t* pte_pointer;
  for(int i = 0; i < len; ++i) {
    pte_pointer = walk(p->pagetable, base_address + i * PGSIZE, 0);
    if(0 == pte_pointer) {
      printf("sys_pgaccess: walk() error !\n");
      return -1;
    }
    if((*pte_pointer) & PTE_A) {
      mask |= (1 << i);
      /*
      https://pdos.csail.mit.edu/6.1810/2023/labs/pgtbl.html

      Be sure to clear PTE_A after checking if it is set. Otherwise, it won't be possible to 
      determine if the page was accessed since the last time 
      pgaccess() was called (i.e., the bit will be set forever).
      */
      (*pte_pointer) &= (~(pte_t)PTE_A);
    }
  }

  if(copyout(p->pagetable, mask_address, (char*)(&mask), (len+7)/8) != 0) {
    printf("sys_pgaccess: copyout() error !\n");
    return -1;
  }

  return 0;
}
#endif

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
