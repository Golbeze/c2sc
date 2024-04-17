#ifndef MYSYSCALL_H
#define MYSYSCALL_H

#ifdef __amd64__


#include <sys/syscall.h>
#include <stdarg.h>

typedef unsigned long size_t;
typedef long ssize_t;
typedef unsigned char __u_char;

#include "defs.h" 


#define TYPEFY(X, name) typeof((X) - (X)) name
#define ARGIFY(X) ((typeof((X) - (X))) (X))
#define REGISTERS_CLOBBERED_BY_SYSCALL "cc", "r11", "cx"

#undef internal_syscall0
#define internal_syscall0(number)			                \
({									\
    unsigned long int resultvar;					\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number)							\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall1
#define internal_syscall1(number, arg1)				        \
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1)						\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall2
#define internal_syscall2(number, arg1, arg2)			        \
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg2, __arg2) = ARGIFY (arg2);			 	\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg2, _a2) asm ("rsi") = __arg2;			\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1), "r" (_a2)				\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall3
#define internal_syscall3(number, arg1, arg2, arg3)     \
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg3, __arg3) = ARGIFY (arg3);			 	\
    TYPEFY (arg2, __arg2) = ARGIFY (arg2);			 	\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg3, _a3) asm ("rdx") = __arg3;			\
    register TYPEFY (arg2, _a2) asm ("rsi") = __arg2;			\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1), "r" (_a2), "r" (_a3)			\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall4
#define internal_syscall4(number, arg1, arg2, arg3, arg4)		\
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg4, __arg4) = ARGIFY (arg4);			 	\
    TYPEFY (arg3, __arg3) = ARGIFY (arg3);			 	\
    TYPEFY (arg2, __arg2) = ARGIFY (arg2);			 	\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg4, _a4) asm ("r10") = __arg4;			\
    register TYPEFY (arg3, _a3) asm ("rdx") = __arg3;			\
    register TYPEFY (arg2, _a2) asm ("rsi") = __arg2;			\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1), "r" (_a2), "r" (_a3), "r" (_a4)		\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall5
#define internal_syscall5(number, arg1, arg2, arg3, arg4, arg5)	\
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg5, __arg5) = ARGIFY (arg5);			 	\
    TYPEFY (arg4, __arg4) = ARGIFY (arg4);			 	\
    TYPEFY (arg3, __arg3) = ARGIFY (arg3);			 	\
    TYPEFY (arg2, __arg2) = ARGIFY (arg2);			 	\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg5, _a5) asm ("r8") = __arg5;			\
    register TYPEFY (arg4, _a4) asm ("r10") = __arg4;			\
    register TYPEFY (arg3, _a3) asm ("rdx") = __arg3;			\
    register TYPEFY (arg2, _a2) asm ("rsi") = __arg2;			\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1), "r" (_a2), "r" (_a3), "r" (_a4),		\
      "r" (_a5)								\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})

#undef internal_syscall6
#define internal_syscall6(number, arg1, arg2, arg3, arg4, arg5, arg6) \
({									\
    unsigned long int resultvar;					\
    TYPEFY (arg6, __arg6) = ARGIFY (arg6);			 	\
    TYPEFY (arg5, __arg5) = ARGIFY (arg5);			 	\
    TYPEFY (arg4, __arg4) = ARGIFY (arg4);			 	\
    TYPEFY (arg3, __arg3) = ARGIFY (arg3);			 	\
    TYPEFY (arg2, __arg2) = ARGIFY (arg2);			 	\
    TYPEFY (arg1, __arg1) = ARGIFY (arg1);			 	\
    register TYPEFY (arg6, _a6) asm ("r9") = __arg6;			\
    register TYPEFY (arg5, _a5) asm ("r8") = __arg5;			\
    register TYPEFY (arg4, _a4) asm ("r10") = __arg4;			\
    register TYPEFY (arg3, _a3) asm ("rdx") = __arg3;			\
    register TYPEFY (arg2, _a2) asm ("rsi") = __arg2;			\
    register TYPEFY (arg1, _a1) asm ("rdi") = __arg1;			\
    asm volatile (							\
    "syscall\n\t"							\
    : "=a" (resultvar)							\
    : "0" (number), "r" (_a1), "r" (_a2), "r" (_a3), "r" (_a4),		\
      "r" (_a5), "r" (_a6)						\
    : "memory", REGISTERS_CLOBBERED_BY_SYSCALL);			\
    (long int) resultvar;						\
})


#define MAKE_SYSCALL0(sysname, nr, retval_type) \
static inline retval_type   sysname() {  \
    return internal_syscall##nr(SYS_##sysname); \
}
#define MAKE_SYSCALL1(sysname, nr, retval_type, type0, varname0) \
static inline retval_type   sysname(type0 varname0) {  \
    return internal_syscall##nr(SYS_##sysname, varname0); \
}
#define MAKE_SYSCALL2(sysname, nr, retval_type, type0, varname0, type1, varname1) \
static inline retval_type   sysname(type0 varname0, type1 varname1) {  \
    return internal_syscall##nr(SYS_##sysname, varname0, varname1); \
}
#define MAKE_SYSCALL3(sysname, nr, retval_type, type0, varname0, type1, varname1, type2, varname2) \
static inline retval_type   sysname(type0 varname0, type1 varname1, type2 varname2) {  \
    return internal_syscall##nr(SYS_##sysname, varname0, varname1, varname2); \
}
#define MAKE_SYSCALL4(sysname, nr, retval_type, type0, varname0, type1, varname1, type2, varname2, type3, varname3) \
static inline retval_type   sysname(type0 varname0, type1 varname1, type2 varname2, type3 varname3) {  \
    return internal_syscall##nr(SYS_##sysname, varname0, varname1, varname2, varname3); \
}
#define MAKE_SYSCALL5(sysname, nr, retval_type, type0, varname0, type1, varname1, type2, varname2, type3, varname3, type4, varname4) \
static inline retval_type   sysname(type0 varname0, type1 varname1, type2 varname2, type3 varname3, type4 varname4) {  \
    return internal_syscall##nr(SYS_##sysname, varname0, varname1, varname2, varname3, varname4); \
}
#define MAKE_SYSCALL6(sysname, nr, retval_type, type0, varname0, type1, varname1, type2, varname2, type3, varname3, type4, varname4, type5, varname5) \
static inline retval_type sysname(type0 varname0, type1 varname1, type2 varname2, type3 varname3, type4 varname4, type5 varname5) {  \
    return internal_syscall##nr(SYS_##sysname, varname0, varname1, varname2, varname3, varname4, varname5); \
}

#define MAKE_SYSCALL_HELPER(sysname, nr, ...) \
MAKE_SYSCALL##nr(sysname, nr, __VA_ARGS__)



#define GENERIC_SYSCALL_LIST(FUNC)              \
        FUNC(exit,          1,      int,        int,            exitcode)                                                         \
        FUNC(close,         1,      int,        int,            fd)                                                               \
        FUNC(dup2,          2,      int,        int,            old_fd,     int,            new_fd)                               \
        FUNC(munmap,        2,      int,        void *,         addr,       size_t,         len)                                  \
        FUNC(write,         3,      size_t,     int,            fd,         void *,         buff,       size_t,             len)  \
        FUNC(execve,        3,      int,        const char *,   pathname,   char * const *, argv,       char * const *,    envp)  \
        FUNC(open,          3,      int,        const char *,   filename,   int,            flags,      int,                mode) \
        FUNC(read,          3,      int,        int,            fd,         void *,         buff,       size_t,             len)  \
        FUNC(sendfile,      4,      int,        int,            to,         int,            from,       off_t *,            off,    size_t,     cnt) \
        FUNC(mmap,          6,      void *,     void *,         addr,       size_t,         length,     int,                prot,   int,        flags,      int,    fd,     off_t,      off)



GENERIC_SYSCALL_LIST(MAKE_SYSCALL_HELPER)


#define SYSCALL_CONCAT_X(a,b)     a##b
#define SYSCALL_CONCAT(a,b)       SYSCALL_CONCAT_X (a, b)

#define SYSCALL_NARGS_X(a,b,c,d,e,f,g,h,n,...) n
#define SYSCALL_NARGS(...) \
    SYSCALL_NARGS_X (__VA_ARGS__,7,6,5,4,3,2,1,0,)

#define SYSCALL_DISP(...) \
  SYSCALL_CONCAT (internal_syscall, SYSCALL_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define syscall(...)  SYSCALL_DISP(__VA_ARGS__)


#define OPEN_CONCAT_X(a,b)     a##b
#define OPEN_CONCAT(a,b)    OPEN_CONCAT_X (a, b)

#define open2(file, flags) open(file, flags, 0)
#define open3(file, flags, mode) open(file, flags, mode)

#define OPEN_NARGS_X(a,b,c,d,e,g,h,n,...) n
#define OPEN_NARGS(...) OPEN_NARGS_X(__VA_ARGS__,7,6,5,4,3,2,1,0,)

#define OPEN_DISP(...) OPEN_CONCAT(open, OPEN_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define open(...) OPEN_DISP(__VA_ARGS__)

#include "utils.h"


#ifdef _FCNTL_H

MAKE_SYSCALL_HELPER(fstat,         2,      int,        int,            fd,         struct stat *,  data)

#endif


#ifdef _NETINET_IN_H

#define NETWORK_SYSCALL_LIST(FUNC)              \
    FUNC(listen,    2,      int,    int,    sockfd,     int,    backlog) \
    FUNC(accept,    3,      int,    int,    sockfd,     struct sockaddr *,      addr,       socklen_t *,    addrlen) \
    FUNC(bind,      3,      int,    int,        fd,     struct sockaddr *,      addr,       socklen_t *,    addrlen) \
    FUNC(socket,    3,      int,    int,    domain,     int,                    type,       int,            protocol)

NETWORK_SYSCALL_LIST(MAKE_SYSCALL_HELPER)

#endif

#ifdef _LINUX_OPENAT2_H
int static inline openat2(int dirfd, const char * filename, struct open_how * how, size_t usize) {
    return internal_syscall4(SYS_openat2, dirfd, filename, how, usize);
}
#endif

#ifdef _SYS_UIO_H

size_t static inline readv(int fd, struct iovec* vec,size_t num){
    return internal_syscall3(SYS_readv, fd, vec, num);
}

size_t static inline writev(int fd, struct iovec* vec,size_t num){
    return internal_syscall3(SYS_writev, fd, vec, num);
}

#endif

#ifdef LINUX_IO_URING_H
int io_uring_setup(unsigned entries, struct io_uring_params *p)
{
    return internal_syscall2(SYS_io_uring_setup, entries, p);
}

int io_uring_enter(int ring_fd, unsigned int to_submit,
                          unsigned int min_complete, unsigned int flags, const void *argp, size_t argsz)
{
    return internal_syscall6(SYS_io_uring_enter, ring_fd, to_submit, min_complete,
                   flags, argp, argsz);
}
#endif


#endif // __amd64__ 

#endif // MYSYSCALL_H