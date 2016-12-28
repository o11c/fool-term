#include "util.h"

#include <sys/uio.h>

#include <errno.h>
#include <poll.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void *fool_memdup(void *p, size_t sz)
{
    void *rv = malloc(sz);
    if (rv)
        memcpy(rv, p, sz);
    return rv;
}

void fool_wait_for_write(int fd)
{
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLOUT;
    (void)poll(fds, sizeof(fds)/sizeof(fds[0]), -1);
}

ssize_t fool_write_harder(int fd, const void *buf, size_t count)
{
    ssize_t written = 0;
    bool had_error = 0;
    while (count)
    {
        ssize_t rv = write(fd, buf, count);
        had_error = rv == -1;
        if (had_error)
        {
            switch (errno)
            {
            case EINTR:
                continue;
            case EAGAIN:
                fool_wait_for_write(fd);
                continue;
            }
            break;
        }
        written += rv;
        buf += rv;
        count -= rv;
    }
    if (!written && had_error)
        written = -1;
    return written;
}

ssize_t fool_writev_harder(int fd, struct iovec *iov, int iovcnt)
{
    ssize_t written = 0;
    bool had_error = 0;
    while (iovcnt)
    {
        ssize_t rv = writev(fd, iov, iovcnt);
        had_error = rv == -1;
        if (had_error)
        {
            switch (errno)
            {
            case EINTR:
                continue;
            case EAGAIN:
                fool_wait_for_write(fd);
                continue;
            }
            break;
        }
        written += rv;
        while (rv)
        {
            ssize_t rv0 = MIN(rv, (ssize_t)iov[0].iov_len);
            iov[0].iov_base += rv0;
            iov[0].iov_len -= rv0;
            rv -= rv0;
            if (iov[0].iov_len)
                break;
            iov++;
            iovcnt--;
        }
    }
    if (!written && had_error)
        written = -1;
    return written;
}
