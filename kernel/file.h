struct file {
#ifdef LAB_NET
  enum { FD_NONE, FD_PIPE, FD_INODE, FD_DEVICE, FD_SOCK } type;
#else
  enum { FD_NONE, FD_PIPE, FD_INODE, FD_DEVICE } type;
#endif
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe; // FD_PIPE
  struct inode *ip;  // FD_INODE and FD_DEVICE
#ifdef LAB_NET
  struct sock *sock; // FD_SOCK
#endif
  uint off;          // FD_INODE
  short major;       // FD_DEVICE
};

#define major(dev)  ((dev) >> 16 & 0xFFFF)
#define minor(dev)  ((dev) & 0xFFFF)
#define	mkdev(m,n)  ((uint)((m)<<16| (n)))

// in-memory copy of an inode
struct inode {
  uint dev;           // Device number

  /*
  Inode number, used to index the array of dinodes,
  there are some disk blocks that are dedicated to store 
  the array of dinodes, refer to ilock(), // it seems that "inum" starts from 1,  (0 means none), refer to dirlookup() and ialloc() ???
  */
  uint inum;          
  int ref;            // Reference count, refer to idup(), iput(), "ref" means how many processes(or how many FS system calls) are using this inode ???
  struct sleeplock lock; // protects everything below here
  int valid;          // inode has been read from disk? refer to ilock(struct inode *ip)

/*
 the following are copy of disk inode, the same as "struct dinode"
*/


  short type;        // the file's type: directory(T_DIR = 1), file(T_FILE = 2) or device(T_DEVICE = 3)
  short major;
  short minor;
  short nlink;      // the number of links referring to it, refer to iput(), "nlink" means how many files or directories "refer to" it ??? How many directories contain it ??? If this inode represents a file which is in a directory, then you should add 1 to nlink (see ip->nlink = 1; in create() ). path "a/b/c", "b" contains a dirent ".." which refers to "a", so that adds 1 to the nlink of "a" (refer to dp->nlink++; in create())
  /*
  the file's size, in bytes, refer to readi()
  In sequence, byte 0-1023 of the file are stored on the block addrs[0],
  byte 1024-2047 of the file are stored on the block addrs[1], ...
  */
  uint size;        
  uint addrs[NDIRECT+1]; // if addrs[i] is 0, it means "none". disk block id cannot be 0
};

// map major device number to device functions.
struct devsw {
  int (*read)(int, uint64, int);  // the arguments: (int user_dst, uint64 dst, int n),  "n" is how many bytes you want to read, refer to statsread()
  int (*write)(int, uint64, int);
};

extern struct devsw devsw[];

#define CONSOLE 1
#define STATS   2
