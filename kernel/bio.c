// Buffer cache.
//
// The buffer cache is a linked list of buf structures holding
// cached copies of disk block contents.  Caching disk blocks
// in memory reduces the number of disk reads and also provides
// a synchronization point for disk blocks used by multiple processes.
//
// Interface:
// * To get a buffer for a particular disk block, call bread.
// * After changing buffer data, call bwrite to write it to disk.
// * When done with the buffer, call brelse.
// * Do not use the buffer after calling brelse.
// * Only one process at a time can use a buffer,
//     so do not keep them longer than necessary.


#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "riscv.h"
#include "defs.h"
#include "fs.h"
#include "buf.h"

// char bucket_lock_names[NBUCKETS][LOCK_NAME_MAX_LENGTH];

// struct {
//   struct spinlock lock;
//   struct buf buf[NBUF];

//   // // Linked list of all buffers, through prev/next.
//   // // Sorted by how recently the buffer was used.
//   // // head.next is most recent, head.prev is least.
//   // struct buf head;
//   struct spinlock bucket_locks[NBUCKETS];
//   struct buf* buckets[NBUCKETS];

// } bcache;


struct {
  // struct spinlock lock;
  struct buf buf[NBUF];

  char bucket_lock_names[NBUCKETS][LOCK_NAME_MAX_LENGTH];
  struct spinlock bucket_locks[NBUCKETS];
  struct buf* buckets[NBUCKETS];

  /*
  You will always acquire some bucket_locks[i] first, 
  then acquire free_buffers_lock
  */
  char free_buffers_lock_name[LOCK_NAME_MAX_LENGTH];
  struct spinlock free_buffers_lock;
  struct buf* free_buffers;
} bcache;


int bcache_buckets_hash_function(int blockno) {
  return (blockno * 3) % NBUCKETS;
}

void
binit(void)
{
  // struct buf *b;

  // initlock(&bcache.lock, "bcache");

  // // Create linked list of buffers
  // bcache.head.prev = &bcache.head;
  // bcache.head.next = &bcache.head;
  // for(b = bcache.buf; b < bcache.buf+NBUF; b++){
  //   b->next = bcache.head.next;
  //   b->prev = &bcache.head;
  //   initsleeplock(&b->lock, "buffer");
  //   bcache.head.next->prev = b;
  //   bcache.head.next = b;
  // }
  // memset(bcache.buf, 0, sizeof(bcache.buf));

  for (int i = 0; i < NBUCKETS; i++)
  {
    snprintf(bcache.bucket_lock_names[i], LOCK_NAME_MAX_LENGTH, "bcache_bucket_%d", i);
    initlock(bcache.bucket_locks + i, bcache.bucket_lock_names[i]);
    // printf("%s\n", bcache.bucket_lock_names[i]);
  }

  snprintf(bcache.free_buffers_lock_name, LOCK_NAME_MAX_LENGTH, "bcache_free_buffer");
  initlock(&(bcache.free_buffers_lock), bcache.free_buffers_lock_name);
  // printf("%s\n", bcache.free_buffers_lock_name);

  for (struct buf* b = bcache.buf; b < bcache.buf + NBUF; ++b) {
    initsleeplock(&b->lock, "buffer");
  }

  // memset(bcache.buckets, 0, sizeof(bcache.buckets));
  
  // construct a linked list of free buffers
  for (struct buf* b = bcache.buf; b < bcache.buf + NBUF - 1; ++b) {
    b->next = b + 1;
  }
  bcache.buf[NBUF - 1].next = 0;
  bcache.free_buffers = bcache.buf;
}

// Look through buffer cache for block on device dev.
// If not found, allocate a buffer.
// In either case, return locked buffer.
static struct buf*
bget(uint dev, uint blockno)
{
  struct buf *b, *b2 = 0;

  // Is the block already inserted in the buckets ?
  int hash_index = bcache_buckets_hash_function(blockno);
  
  acquire(&(bcache.bucket_locks[hash_index]));
  for(b = bcache.buckets[hash_index]; b != 0; b = b->next) {
    if(b->dev == dev && b->blockno == blockno) {
      b->refcnt++;
      release(&(bcache.bucket_locks[hash_index]));
      acquiresleep(&(b->lock));
      return b;
    }
    if(b->next == 0) {
      b2 = b;
    }
  }

  // // Not in the buckets. Insert an empty buffer in the buckets and return it
  // for (b = bcache.buf; b < bcache.buf + NBUF; ++b) {
  //   if(b->refcnt == 0) {
  //     /* make sure "b" is not in the buckets, 
  //     so we delete the buffer from the buckets if its refcnt is 0
  //     */
  //     b->dev = dev;
  //     b->blockno = blockno;
  //     b->valid = 0;
  //     b->refcnt = 1;

  //     // now insert this buffer into the buckets
  //     acquire(&(bcache.bucket_locks[hash_index]));
  //     b2 = bcache.buckets[hash_index]; 
  //     if(b2 == 0) {
  //       bcache.buckets[hash_index] = b;  b->next = 0;
  //     } else {
  //       while (b2->next != 0)
  //       {
  //         b2 = b2->next;
  //       }
  //       b2->next = b;
  //       b->next = 0;
  //       // b->prev = b2;
  //     }
  //     release(&(bcache.bucket_locks[hash_index]));

  //     release(&(bcache.lock));
  //     acquiresleep(&(b->lock));
  //     return b;
  //   }
  // }

  // panic("bget: no buffers");

  acquire(&(bcache.free_buffers_lock));
  b = bcache.free_buffers;
  if(b == 0) {
    panic("bget: out of block buffers\n");
  } else {
    bcache.free_buffers = b->next;
    b->dev = dev;
    b->blockno = blockno;
    b->refcnt = 1;
    b->valid = 0;
  }
  release(&(bcache.free_buffers_lock));

  // append the allocated empty buffer to the end of the linked list bcache.buckets[hash_index]
  if(b2 != 0) {
    b2->next = b;
    b->next = 0;
  } else {
    bcache.buckets[hash_index] = b;
    b->next = 0;
  }

  release(&(bcache.bucket_locks[hash_index]));
  acquiresleep(&(b->lock));
  return b;
}

// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno)
{
  struct buf *b;

  b = bget(dev, blockno);
  if(!b->valid) {
    virtio_disk_rw(b, 0);
    b->valid = 1;
  }
  return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("bwrite");
  virtio_disk_rw(b, 1);
}

// Release a locked buffer.
// Move to the head of the most-recently-used list, (bcache.head.next = b)
void
brelse(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("brelse");

  int hash_index = bcache_buckets_hash_function(b->blockno);
  releasesleep(&b->lock);
  // /*
  // now b->refcnt > 0, so nothing bad will happen
  // in between ???
  // */
  // acquire(&bcache.lock);
  // b->refcnt--;
  // if (b->refcnt == 0) {
  //   // no one is waiting for it.
  //   b->next->prev = b->prev;
  //   b->prev->next = b->next;
  //   b->next = bcache.head.next;
  //   b->prev = &bcache.head;
  //   bcache.head.next->prev = b;
  //   bcache.head.next = b;
  // }
  
  // release(&bcache.lock);

  acquire(&(bcache.bucket_locks[hash_index]));
  b->refcnt--;
  if(b->refcnt == 0) {
    int found = 0;
    // delete this buffer from the buckets
    struct buf *buf_iterator = bcache.buckets[hash_index];
    if(buf_iterator != 0) {
      if(buf_iterator == b) {
        found = 1;
        bcache.buckets[hash_index] = b->next;
      } else {
        while (buf_iterator->next != 0)
        {
          if(buf_iterator->next == b) {
            found = 1;
            buf_iterator->next = b->next;
            break;
          }
          buf_iterator = buf_iterator->next;
        }
      }
    }
    if(found == 0) {
      panic("brelse: the allocated buffer NOT in bcache.buckets\n");
    }
    acquire(&(bcache.free_buffers_lock));
    struct buf* b2 = bcache.free_buffers;
    if(b2 == 0) {
      bcache.free_buffers = b;
      b->next = 0;
    } else {
      b->next = b2->next;
      b2->next = b;
    }
    release(&(bcache.free_buffers_lock));
  }
  release(&(bcache.bucket_locks[hash_index]));
}


// Question: I don't understand what bpin() and bunpin() are doing ???
void
bpin(struct buf *b) {
  int hash_index = bcache_buckets_hash_function(b->blockno);
  // acquire(&bcache.lock);
  // b->refcnt++;
  // release(&bcache.lock);
  acquire(&(bcache.bucket_locks[hash_index]));
  b->refcnt++;
  release(&(bcache.bucket_locks[hash_index]));
}

void
bunpin(struct buf *b) {
  int hash_index = bcache_buckets_hash_function(b->blockno);
  // acquire(&bcache.lock);
  // b->refcnt++;
  // release(&bcache.lock);
  acquire(&(bcache.bucket_locks[hash_index]));
  b->refcnt--;
  release(&(bcache.bucket_locks[hash_index]));
}