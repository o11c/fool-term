#include "ev.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "signals.h"
#include "util.h"


static void setting_string(void *ptr, const char *value)
{
    *(const char **)ptr = value;
}
static void setting_int(void *ptr, const char *value)
{
    *(int *)ptr = strtol(value, (char **)&value, 10);
    if (*value)
        abort();
}
static void setting_true(void *ptr)
{
    *(bool *)ptr = true;
}
static void setting_false(void *ptr)
{
    *(bool *)ptr = false;
}
static void setting_encoding(void *ptr, const char *value)
{
    int8_t enc;
    if (strcmp(value, "utf8") == 0)
        enc = FOOL_UTF8;
    else if (strcmp(value, "utf_8") == 0)
        enc = FOOL_UTF8;
    else if (strcmp(value, "8bit") == 0)
        enc = FOOL_8BIT;
    else if (strcmp(value, "8_bit") == 0)
        enc = FOOL_8BIT;
    else
        abort();
    *(int8_t *)ptr = enc;
}

static struct
{
    const char *setting;
    size_t offset;
    void (*without_arg)(void *ptr);
    void (*with_arg)(void *ptr, const char *value);
}
ev_opt_settings[] =
{
#define STRING(name)    {#name, offsetof(fool_options, name), NULL, setting_string}
#define INT(name)       {#name, offsetof(fool_options, name), NULL, setting_int}
#define NEGATIVE(name)  {"no_"#name, offsetof(fool_options, no_##name), setting_false, NULL}, \
                        {#name, offsetof(fool_options, no_##name), setting_true, NULL}
#define POSITIVE(name)  {#name, offsetof(fool_options, name), setting_true, NULL}, \
                        {"no_"#name, offsetof(fool_options, name), setting_false, NULL}
    STRING(term),
    INT(esc_delay),
    NEGATIVE(close_read),
    NEGATIVE(close_write),
    {"encoding", offsetof(fool_options, encoding), NULL, setting_encoding},
    NEGATIVE(tty_ioctl),
    NEGATIVE(tty_report),
    NEGATIVE(signals),
    {"nonblocking", offsetof(fool_options, nonblocking), setting_false, NULL},
    {"blocking", offsetof(fool_options, nonblocking), setting_true, NULL},
    NEGATIVE(extra),
    POSITIVE(keep_input_break),
    POSITIVE(keep_input_sig),
    POSITIVE(keep_input_xon_xoff),
    POSITIVE(force_meta),
    NEGATIVE(c1),
    NEGATIVE(osc_bel),
    POSITIVE(csi_dollar),
    NEGATIVE(ss3),
    NEGATIVE(long_ss3),
    NEGATIVE(csi_lsqb),
};

static void parse_opt(fool_options *opts, const char *arg)
{
    (void)ev_opt_settings;

    if (false)
        ;
    else if (strcmp(arg, "--csi-dollar") == 0)
        opts->csi_dollar = true;
    else if (strcmp(arg, "--no-csi-dollar") == 0)
        opts->csi_dollar = false;
    else
    {
        printf("Invalid argument '%s'\n", arg);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    unsigned alarm_time = 30;

    fool_options opts = {};
    for (int i = 1; i < argc; ++i)
    {
        parse_opt(&opts, argv[i]);
    }

    printf("Program will exit after %d seconds of inactivity\n", alarm_time);
    printf("(or by pressing ctrl-c twice)\n");

    fool_io *io = fool_io_open2(STDIN_FILENO, STDOUT_FILENO, &opts, sizeof(opts));
    if (!io)
    {
        printf("Failed to open terminal!\n");
        return 2;
    }

    bool exit_later = false;
    fool_event ev;
    while (alarm(alarm_time), fool_event_get(io, &ev) != FOOL_EVENT_EOF)
    {
        printf("(0x%08x) -> %s\r\n", ev.basic, fool_event_string(io, &ev, 0));
        fool_event_free(io, &ev);
        if (exit_later && ev.basic == (FOOL_MASK_CTRL | 'C'))
            break;
        exit_later = ev.basic == (FOOL_MASK_CTRL | 'C');
    }

    fool_io_close(io);
}
