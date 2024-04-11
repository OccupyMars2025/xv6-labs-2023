// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

// struct {
//   struct spinlock lock;
//   struct run *freelist;
// } kmem;
struct {
  struct spinlock lock;
  struct run *freelist;
} kmems[NCPU];

char kmems_name[NCPU][15];

void
kinit()
{
  // for (int i = 0; i < NCPU; i++)
  // {
  //   initlock(&kmems[i].lock, "kmem");
  // }

  /* Quesion: 
  If we place the following line in kinit(),
  char kmems_name[NCPU][15];
  then when exiting kinit(), the physical page that stores kmems_name 
  will be recycled, so kmems[i].lock.name will become a wild pointer ???
  */
  for (int i = 0; i < NCPU; i++)
  {
    snprintf(kmems_name[i], 15, "kmem_cpu%d", i);
    initlock(&kmems[i].lock, kmems_name[i]);
    printf("kmem_name: %s\n", kmems[i].lock.name);
  }
  
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by pa,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  // refer to myproc(), add push_off() and pop_off()
  push_off();
  int hart_id = cpuid();
  // pop_off();

  acquire(&kmems[hart_id].lock);
  r->next = kmems[hart_id].freelist;
  kmems[hart_id].freelist = r;
  release(&kmems[hart_id].lock);

  pop_off();
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  push_off();
  int hart_id = cpuid();
  // pop_off();

  acquire(&kmems[hart_id].lock);
  r = kmems[hart_id].freelist;
  if(r)
    kmems[hart_id].freelist = r->next;
  release(&kmems[hart_id].lock);

  /*
  this CPU has empty freelist, so "steal" one page
  from some other CPU's freelist
  */
  /*
   You want to use "while(!r)" to make sure that kalloc() 
   allocates a valid page and never returns 0, but it's impossible,
   and user/kalloctest.c:countfree() depends on the failure of sbrk(4096)
   to exit the its while loop. kalloc() returning 0 leads to the failure of sbrk(4096) 
  */
  // while(!r) {
  if(!r) {
    /*
    start from (hart_id + 1) % NCPU , not from 0, so
    the freelist on each CPU may be more balanced
    */
    for(int i = (hart_id + 1) % NCPU; i != hart_id; i = (i + 1) % NCPU) {
      acquire(&kmems[i].lock);
      r = kmems[i].freelist;
      if(r) {
        kmems[i].freelist = r->next;
      }
      release(&kmems[i].lock);
      if(r) {
        break;
      }
    }
    // printf("kalloc: while loop\n");
    // if(!r) {
    //    // pop_off() before yield()
    //   yield();
    // }
  }

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk

  pop_off();

  return (void*)r;
}
