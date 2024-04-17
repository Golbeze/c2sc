#ifndef UTILS_H
#define UTILS_H

#define printf(...) (void)0;
#define fprintf(...) (void)0;

static inline size_t strlen(const char * s) {
    size_t l = 0;
    while(*s != 0) l++, s++;
    return l;
}

void static inline writestr(int fd, const char * str) {
    write(fd, str, strlen(str));
}

void static inline memset(void * buf, unsigned char c, size_t len) {
    unsigned char * ptr = (unsigned char *)buf;
    for(int i = 0; i < len; i++) ptr[i] = c;
}

void static inline perror(const char * s) {
    writestr(2, s);
}

static inline void puts(const char * s){
    writestr(1, s);
    char c = '\n';
    write(1, &c, 1);
}

#ifdef _SYS_MMAN_H

static inline char * malloc(size_t size) {
    size_t req_size = ((size + 0xfff) / 0x1000) * 0x1000;
    return (char*)mmap(0, req_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

#endif 




int static inline free(void * ptr) {return 0;}

#endif