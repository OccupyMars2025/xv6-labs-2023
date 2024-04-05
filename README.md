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

