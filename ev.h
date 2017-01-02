#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


typedef int fool_fd;
typedef struct fool_options fool_options;
typedef struct fool_io fool_io;
typedef struct fool_event fool_event;

/*
    This library does not do any encoding; it only needs to know where the
    boundaries are. Thus, this information is sufficient.

    Only code-unit boundaries are handled, not e.g. combining characters.
*/
enum
{
    // Please, please, *please*, just use this.
    // It's the only thing that's *really* supported.
    FOOL_UTF8 = 0,

    // But this probably works too.
    // And the below can be implemented using it if you really need to.
    // If 0x80 through 0x9f are printable, you must also set no_c1 = true.
    FOOL_8BIT = 1,

    // Characters with the high-bit set are usually paired.
    // Fully ASCII-safe.
    // 0x8f (C1 SS3) starts a 3-byte sequence (for EUC-JP).
    // 0x8e (C1 SS2) starts a 4-byte sequence (for EUC-TW).
    // No other C1 controls are used internally.
    // EUC-CN and EUC-KR need no exceptions.
    // TODO - figure out how to do text encoding for these!
    //FOOL_EUC,

    // Lead(and third) 0x81-0xfe, 2-byte second 0x40-0xfe, four-byte 2nd/4th 0x30-0x39
    // Never ASCII-safe.
    // FOOL_LEGACY_CJK,

    // Actually, this is a meta-encoding, it should be separate?
    // Can be made ASCII-safe, but usually isn't.
    // FOOL_ISO2022,

    FOOL_MAX_ENCODINGS,
};

struct fool_options
{
    // Value of the TERM environment variable for this terminal.
    char *term;

    // Timeout, in milliseconds, to forcibly break an escape sequence.
    // This is necessary when the user presses the "Esc" key.
    // If 0, use getenv("ESCDELAY") or 1000.
    // If -1, never timeout, (reproducible, but usually breaks various things).
    //
    // We use esc_delay when the input buffer has one of the following forms:
    //  *   \e
    //  *   \e\e
    //  *   \eA
    // In particular, it is *not* used once we have committed to a sequence.
    int esc_delay;

    // Don't close the FDs passed to io_open.
    // The "right thing" will be done if the same FD is passed for both.
    bool no_close_read, no_close_write;

    // Which encoding the terminal uses.
    // Only UTF-8 is really supported.
    int8_t encoding;

    // Avoid using ioctl's that assume the FDs belong to a TTY.
    bool no_tty_ioctl;

    // Avoid writing various sequences that cause special replies.
    bool no_tty_report;

    // Don't install a handler for SIGWINCH and various crashes.
    // Note that existing handlers will be chained, so this is usually
    // safe. Also remember that signal handlers are *global*, so if they
    // are installed for *any* fool_io, they will exist.
    // The signal handlers will never be uninstalled, but they will be
    // no-ops if no fool_io remains.
    bool no_signals;

    // Always return immediately from fool_event_get.
    bool nonblocking;

    // Forbid fool_event_get from setting the extra field, removing the
    // need to call fool_event_free if you don't call other functions
    // such as fool_event_string.
    bool no_extra;

    // Don't change various termios settings.
    bool keep_input_break, keep_input_sig;
    bool keep_input_xon_xoff;

    // Interpret U+00a0 through U+00ff as meta-modified ascii.
    bool force_meta;

    // Always use long-form ESC+letter controls rather than C1 controls.
    // This is probably only useful with encoding=FOOL_8BIT, if you're
    // using something like windows cp1252, which treats them as printable.
    bool no_c1;

    // Don't accept BEL in place of ST (under OSC only; an xterm extension).
    bool no_osc_bel;

    // Terminate CSI sequences on $ (an rxvt bug, prevents other sequences).
    bool csi_dollar;

    // Don't allow SS3 as a prefix, or as a CSI introducer.
    // Needed for various special keys in some terminal emulators.
    bool no_ss3, no_long_ss3;
    // Don't treat [ as a CSI intermediate.
    // Needed on the Linux console for F1-F5.
    bool no_csi_lsqb;

    // More options will be added in future.
    // For source-compatibility, initialize the entire structure to 0.
    // For binary-compatibility, pass the known size to fool_io_open2.
};

struct fool_event
{
    // Same as the return value.
    int32_t basic;
    union
    {
        // Valid only if FOOL_EVENT_IS_TEXT, otherwise undefined.
        char utf8[4];
        // Used for winch and mouse events.
        uint16_t coords[2];
    };
    // Used for certain special cases, unless no_extra is set.
    void *extra;
};

// This was not a TTY, and the end of file/pipe was reached.
// For TTYs, you will get SIGHUP instead, unless you ignore it.
#define FOOL_EVENT_EOF      (FOOL_KEY_ALLOC - 1)
// There was no complete input yet, and opt.nonblock was set.
#define FOOL_EVENT_TIMEOUT  (FOOL_KEY_ALLOC - 2)
// Distinguish pastes from typed text.
#define FOOL_EVENT_PASTE_BEGIN  (FOOL_KEY_ALLOC - 3)
#define FOOL_EVENT_PASTE_END    (FOOL_KEY_ALLOC - 4)
// Is xterm the active window?
#define FOOL_EVENT_FOCUS_GAINED (FOOL_KEY_ALLOC - 5)
#define FOOL_EVENT_FOCUS_LOST   (FOOL_KEY_ALLOC - 6)
// Please redraw the entire window.
#define FOOL_EVENT_WINCH    (FOOL_KEY_ALLOC + 1)
// Unparsed escape sequences.
#define FOOL_EVENT_OTHER_ISO2022 (FOOL_KEY_ALLOC + ' ')
#define FOOL_EVENT_OTHER_SS3    (FOOL_KEY_ALLOC + 'O')
#define FOOL_EVENT_OTHER_DCS    (FOOL_KEY_ALLOC + 'P')
#define FOOL_EVENT_OTHER_SOS    (FOOL_KEY_ALLOC + 'X')
#define FOOL_EVENT_OTHER_CSI    (FOOL_KEY_ALLOC + '[')
#define FOOL_EVENT_OTHER_OSC    (FOOL_KEY_ALLOC + ']')
#define FOOL_EVENT_OTHER_PM     (FOOL_KEY_ALLOC + '^')
#define FOOL_EVENT_OTHER_APC    (FOOL_KEY_ALLOC + '_')

/*
    Check if the event is textual input (without modifiers).
    Note that tab, newline, and escape (as well as other control characters)
    will *not* satisfy this.
*/
#define FOOL_EVENT_IS_TEXT(evb)     ((evb) <= 0x10FFFF)

/*
    Start immediately after the end of Unicode.
*/
#define FOOL_KEY_START      0x00110000
#define FOOL_KEY_MASK       0x001fffff
#define FOOL_KEY_ALLOC      0x00180000
#define FOOL_KEY_F0         0x001f0000
#define FOOL_KEY_F(n)       (FOOL_KEY_F0 + (n))

#define FOOL_KEY_ESC        (FOOL_KEY_START + 1)
#define FOOL_KEY_TAB        (FOOL_KEY_START + 2)
#define FOOL_KEY_ENTER      (FOOL_KEY_START + 3)
#define FOOL_KEY_BACKSPACE  (FOOL_KEY_START + 4)
#define FOOL_KEY_INSERT     (FOOL_KEY_START + 5)
#define FOOL_KEY_DELETE     (FOOL_KEY_START + 6)
#define FOOL_KEY_HOME       (FOOL_KEY_START + 7)
#define FOOL_KEY_END        (FOOL_KEY_START + 8)
#define FOOL_KEY_PAGEUP     (FOOL_KEY_START + 9)
#define FOOL_KEY_PAGEDOWN   (FOOL_KEY_START + 10)
#define FOOL_KEY_UP         (FOOL_KEY_START + 11)
#define FOOL_KEY_DOWN       (FOOL_KEY_START + 12)
#define FOOL_KEY_RIGHT      (FOOL_KEY_START + 13)
#define FOOL_KEY_LEFT       (FOOL_KEY_START + 14)
#define FOOL_KEY_BEGIN      (FOOL_KEY_START + 15)

#define FOOL_MASK_KEYPAD    (1 << 23)
#define FOOL_MASK_SHIFT     (1 << 24)
#define FOOL_MASK_ALT       (1 << 25)
#define FOOL_MASK_CTRL      (1 << 26)
#define FOOL_MASK_META      (1 << 27)
#define FOOL_MASK_LMB       (1 << 28)
#define FOOL_MASK_MMB       (1 << 29)
#define FOOL_MASK_RMB       (1 << 30)
#define FOOL_MOD_MASK       0x7f800000

// 2 bits left.
#define FOOL_TODO_MASK      0x00600000


/*
    Open a terminal for reading. A writing FD still must be supplied in
    order to inform the terminal of certain settings.

    Usually rfd and wfd will be the same, but it can be useful to make them
    different in some circumstances.

    Pass both the opt struct and its size, for binary compatibility.
    Passing NULL is permitted if the default options are acceptable.
*/
fool_io *fool_io_open2(fool_fd rfd, fool_fd wfd, fool_options *opt, size_t opt_size);
/*
    Convenience macro if rfd == wfd. Also takes care of passing the
    opt_size in. NULL is still permitted for opt.
*/
#define fool_io_open(fd, opt)           \
({                                      \
        fool_fd _fd = (fd);             \
        fool_options *_opt = (opt);     \
                                        \
        fool_io_open2(_fd, _fd, _opt, sizeof(*_opt);    \
})
/*
    Close a terminal and clean up.

    This MUST NOT be called from a signal handler.
*/
void fool_io_close(fool_io *io);
/*
    Perform *only* the cleanups that are safe to call from
    within a signal handler.
*/
void fool_io_crash(fool_io *io);

/*
    If nonblocking is not set, wait for at least one event and return it.
    Else, return an event if available, or FOOL_EVENT_TIMEOUT if not.

    If ev is non-NULL, additional info is stored there. In this case,
    you MUST call fool_event_free unless you set the no_extra option.

    Depending on the input, this may block for up to ESCDELAY milliseconds.
*/
int32_t fool_event_get(fool_io *io, fool_event *ev);
/*
    Convert the input event to a unique and human-readable string.

    The return value will not contain any ASCII whitespace, although if
    the variant argument is implemented, that may change.

    Note that you cannot uniquely concatenate multiple events.
    For example "A-a" vs "A" "-" "a".

    This may invalidate the ev->extra field, and thus you MUST call
    fool_event_free afterwards.
*/
const char *fool_event_string(fool_io *io, fool_event *ev, int variant);
/*
    Release additional resources associated with an event.
*/
void fool_event_free(fool_io *io, fool_event *ev);
