#pragma once

#include <sys/types.h>

#include <stddef.h>


struct iovec;


void *fool_memdup(void *p, size_t sz);
#define memdup(p, sz) ((__typeof__(p)) fool_memdup(p, sz))

void fool_wait_for_write(int fd);
ssize_t fool_write_harder(int fd, const void *buf, size_t count);
ssize_t fool_writev_harder(int fd, struct iovec *iov, int iovcnt);

#undef MIN
#undef MAX
#define MIN(x, y)           \
({                          \
    typeof((x)) _x = (x);   \
    typeof((y)) _y = (y);   \
                            \
    _x < _y ? _x : _y;      \
})
#define MAX(x, y)           \
({                          \
    typeof((x)) _x = (x);   \
    typeof((y)) _y = (y);   \
                            \
    _x > _y ? _x : _y;      \
})
