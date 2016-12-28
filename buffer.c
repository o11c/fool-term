#include "buffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


void fool_buffer_clear(fool_buffer *buf)
{
    free(buf->begin_alloc);
    memset(buf, '\0', sizeof(*buf));
}

void fool_buffer_append(fool_buffer *buf, char *b, char *e)
{
    size_t added_size = e - b;
    if (added_size == 0)
        return;
    size_t right_avail = buf->end_cap - buf->end;
    if (added_size <= right_avail)
    {
        memcpy(buf->end, b, added_size);
        buf->end += added_size;
        return;
    }
    size_t left_avail = buf->begin - buf->begin_alloc;
    size_t cur_size = buf->end - buf->begin;
    if (added_size <= left_avail + right_avail)
    {
        memmove(buf->begin_alloc, buf->begin, cur_size);
        buf->begin -= left_avail;
        buf->end -= left_avail;
        memcpy(buf->end, b, added_size);
        buf->end += added_size;
        return;
    }
    size_t needed_size = cur_size + added_size;
    size_t new_size = cur_size + !cur_size;
    while (new_size < needed_size)
    {
        new_size <<= 1;
        assert (new_size != 0 && "overflow");
    }
    buf->begin_alloc = (char *)malloc(new_size);
    buf->end_cap = buf->begin_alloc + new_size;
    if (cur_size)
        memcpy(buf->begin_alloc, buf->begin, cur_size);
    free(buf->begin - left_avail);
    buf->begin = buf->begin_alloc;
    buf->end = buf->begin + cur_size;
    memcpy(buf->end, b, added_size);
    buf->end += added_size;
}

void fool_buffer_cut(fool_buffer *buf, size_t n)
{
    buf->begin += n;
    if (buf->begin == buf->end)
    {
        buf->begin = buf->begin_alloc;
        buf->end = buf->begin_alloc;
    }
}
