#include "ev.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "signals.h"
#include "util.h"


static bool setting_string(void *ptr, char *value)
{
    *(const char **)ptr = value;
    return *value;
}
static bool setting_int(void *ptr, char *value)
{
    *(int *)ptr = strtol(value, &value, 10);
    if (*value)
        return false;
    return true;
}
static void setting_true(void *ptr)
{
    *(bool *)ptr = true;
}
static void setting_false(void *ptr)
{
    *(bool *)ptr = false;
}
static bool setting_encoding(void *ptr, char *value)
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
#if 0
    else if (strcmp(value, "euc") == 0)
        enc = FOOL_EUC;
#endif
    else
        return false;
    *(int8_t *)ptr = enc;
    return true;
}

static struct
{
    const char *name;
    size_t offset;
    void (*without_arg)(void *ptr);
    bool (*with_arg)(void *ptr, char *value);
    const char *help;
}
ev_opt_settings[] =
{
#define STRING(name, help)      {#name, offsetof(fool_options, name), NULL, setting_string, help}
#define INT(name, help)         {#name, offsetof(fool_options, name), NULL, setting_int, help}
#define NEGATIVE(name, help)    {#name, offsetof(fool_options, no_##name), setting_true, NULL, "Do "help" (default)"}, \
                                {"no_"#name, offsetof(fool_options, no_##name), setting_false, NULL, "Don't "help}
#define POSITIVE(name, help)    {#name, offsetof(fool_options, name), setting_true, NULL, "Do "help}, \
                                {"no_"#name, offsetof(fool_options, name), setting_false, NULL, "Don't "help" (default)"}
    STRING(term, "Terminal type"),
    INT(esc_delay, "Milliseconds to wait when the ESC key is pressed"),
    NEGATIVE(close_read, "close the input FD"),
    NEGATIVE(close_write, "close the output FD"),
    {"encoding", offsetof(fool_options, encoding), NULL, setting_encoding, "Encoding family (utf-8 (default), 8-bit)"},
    NEGATIVE(tty_ioctl, "use TTY-specific ioctls"),
    NEGATIVE(tty_report, "use TTY stream reports"),
    NEGATIVE(signals, "install signal handlers"),
    {"nonblocking", offsetof(fool_options, nonblocking), setting_false, NULL, "Use nonblocking input"},
    {"blocking", offsetof(fool_options, nonblocking), setting_true, NULL, "Use blocking input (default)"},
    NEGATIVE(extra, "return dynamically-allocated data"),
    POSITIVE(keep_input_break, "let the terminal handle break"),
    POSITIVE(keep_input_sig, "let the terminal handle signals"),
    POSITIVE(keep_input_xon_xoff, "let the terminal handle XON/XOFF"),
    POSITIVE(force_meta, "interpret latin1 printables as meta-ascii"),
    NEGATIVE(c1, "use 8-bit escapes"),
    NEGATIVE(osc_bel, "terminate OSC with BEL"),
    POSITIVE(csi_dollar, "treat $ as a CSI terminator"),
    NEGATIVE(ss3, "treat SS3 as a single-character introducer"),
    NEGATIVE(long_ss3, "treat SS3 as a CSI-like sequence introducer"),
    NEGATIVE(csi_lsqb, "allow [ as a CSI intermediate (for linux)"),
};

static void help(void)
{
    printf("Usage: ./ev-test.x [args]\n");
    for (size_t i = 0; i < sizeof(ev_opt_settings)/sizeof(ev_opt_settings[0]); ++i)
    {
        printf("  --%-20s %s\n", ev_opt_settings[i].name, ev_opt_settings[i].help);
    }
    exit(0);
}

static void parse_opt(fool_options *opts, char *arg)
{
    if (strcmp(arg, "--help") == 0)
    {
        help();
    }
    if (arg[0] != '-' || arg[1] != '-')
        goto invalid;
    arg += 2;
    for (size_t i = 0; arg[i]; ++i)
    {
        if (arg[i] == '-')
            arg[i] = '_';
    }
    char *val = strchr(arg, '=');
    if (val)
    {
        *val = '\0';
        ++val;
    }
    // TODO: sort and use binary search.
    for (size_t i = 0; i < sizeof(ev_opt_settings)/sizeof(ev_opt_settings[0]); ++i)
    {
        if (strcmp(arg, ev_opt_settings[i].name) == 0)
        {
            char *ptr = (char *)opts;
            ptr += ev_opt_settings[i].offset;
            if (val)
            {
                if (!ev_opt_settings[i].with_arg(ptr, val))
                    goto invalid;
            }
            else
            {
                ev_opt_settings[i].without_arg(ptr);
            }
            return;
        }
    }

invalid:
    arg -= 2;
    if (val)
        val[-1] = '=';
    printf("Invalid argument '%s'.\n", arg);
    printf("Use '--help' to list valid options.\n");
    exit(1);
}

int main(int argc, char **argv)
{
    unsigned alarm_time = 30;
    unsigned ctl_c_needed = 3;

    fool_options opts = {};
    for (int i = 1; i < argc; ++i)
    {
        parse_opt(&opts, argv[i]);
    }

    printf("Program will exit after %u seconds of inactivity\n", alarm_time);
    printf("(or by pressing ctrl-c %u times)\n", ctl_c_needed);

    fool_io *io = fool_io_open2(STDIN_FILENO, STDOUT_FILENO, &opts, sizeof(opts));
    if (!io)
    {
        printf("Failed to open terminal!\n");
        return 2;
    }

    unsigned ctl_c_actual = 0;
    fool_event ev;
    while (alarm(alarm_time), ctl_c_actual != ctl_c_needed && fool_event_get(io, &ev) != FOOL_EVENT_EOF)
    {
        if (ev.basic != FOOL_EVENT_NOTHING)
        {
            printf("(0x%08x) -> %s\r\n", ev.basic, fool_event_string(io, &ev, 0));
            if (ev.basic == (FOOL_MASK_CTRL | 'C') || ev.basic == (FOOL_MASK_CTRL | 'c'))
            {
                ctl_c_actual++;
            }
            else
            {
                ctl_c_actual = 0;
            }
        }
        fool_event_free(io, &ev);
    }

    fool_io_close(io);
}
