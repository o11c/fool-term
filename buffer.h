#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct fool_buffer fool_buffer;

/*
    A queue.

    Simply zero-initialize to start using.
*/
struct fool_buffer
{
    /* Beginning of allocation. */
    char *begin_alloc;
    /* Beginning of active data. */
    char *begin;
    /* End of active data. */
    char *end;
    /* End of allocation. */
    char *end_cap;
};

/*
    Return the buffer to a zeroed state.
*/
void fool_buffer_clear(fool_buffer *buf);

/*
    Append to the buffer, reallocating and compact as needed.
*/
void fool_buffer_append(fool_buffer *buf, char *b, char *e);

/*
    Remove characters from front of buffer.
*/
void fool_buffer_cut(fool_buffer *buf, size_t n);

__attribute__((unused))
static inline size_t fool_buffer_size(fool_buffer *buf)
{
    return buf->end - buf->begin;
}

__attribute__((unused))
static inline bool fool_buffer_has(fool_buffer *buf, size_t idx)
{
    return idx < fool_buffer_size(buf);
}

__attribute__((unused))
static inline char fool_buffer_at(fool_buffer *buf, size_t idx)
{
    assert (fool_buffer_has(buf, idx));

    return buf->begin[idx];
}
