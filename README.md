# c2sc
convert c code to shellcode

but preserve struct and macro info in source code

only x86_64 supported

## advantage

reference C struct and macro as normal, and exploit gcc -Os optimization for complicate shellcode logic.

## usage

write your c code in source.c and run ./gen.py

make sure that your c code compile

## example

```python
from pwn import *  
import gen

sh = process('test/test')

gdb.attach(sh)
sh.send(gen.my_asm('./source.c', opt=True))

sh.interactive()
```

```C
#include <stdio.h>
int main() {
    puts("hello world"); // this is implemented in utils.h
    return 0;
}
```

or

```C
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include "linux/io_uring.h"

#ifndef SYS_io_uring_enter
#define SYS_io_uring_enter 426
#endif
#ifndef SYS_io_uring_setup
#define SYS_io_uring_setup 425
#endif

int main(void)
{
  // initialize uring
  struct io_uring_params params = {};
  int opened_fd;
  char buffer[100];
  int uring_fd = syscall(SYS_io_uring_setup, 16, &params);
  unsigned char *sq_ring = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, uring_fd, IORING_OFF_SQ_RING);
  unsigned char *cq_ring = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, uring_fd, IORING_OFF_CQ_RING);
  struct io_uring_sqe *sqes = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, uring_fd, IORING_OFF_SQES);

  sqes[0] = (struct io_uring_sqe){
      .opcode = IORING_OP_OPENAT,
      .flags = IOSQE_ASYNC,
      .fd = AT_FDCWD,
      .addr = "./flag",
      .open_flags = O_RDONLY,
  };
  ((int *)(sq_ring + params.sq_off.array))[0] = 0;
  (*(int *)(sq_ring + params.sq_off.tail))++;
  syscall(SYS_io_uring_enter, uring_fd, 1, 1, IORING_ENTER_GETEVENTS, NULL, 0);
  struct io_uring_cqe *cqe = (void *)(cq_ring + params.cq_off.cqes);
  opened_fd = (int)cqe->res;

  sqes[0] = (struct io_uring_sqe){
      .opcode = IORING_OP_READ,
      .fd = opened_fd,
      .addr = buffer,
      .len = 100,
  };
  ((int *)(sq_ring + params.sq_off.array))[0] = 0;
  (*(int *)(sq_ring + params.sq_off.tail))++;
  syscall(SYS_io_uring_enter, uring_fd, 1, 1, IORING_ENTER_GETEVENTS, NULL, 0);

  sqes[0] = (struct io_uring_sqe){
      .opcode = IORING_OP_WRITE,
      .fd = 1,
      .addr = buffer,
      .len = 100,
  };
  ((int *)(sq_ring + params.sq_off.array))[0] = 0;
  (*(int *)(sq_ring + params.sq_off.tail))++;
  syscall(SYS_io_uring_enter, uring_fd, 1, 3, IORING_ENTER_GETEVENTS, NULL, 0);
  return 0;
}
```

## how it works

use gcc preprocessor to get all macro and struct definition and strip those useless extern function declarations (use python regex, ugly)

merge them into one defs.h header file

and implement a custom syscall header file by mimicing glibc syscall wrapper code

there is also some small points, like 

* using linker script to make sure main is always first one 
* use gcc options to strip unused function
* merge code section and data section into one section, and copy them all

the code is short, find code you interested by yourself.

## more todo

add a option to gen.py for checking if source.c compiled normally

implement more needed syscall

more test
