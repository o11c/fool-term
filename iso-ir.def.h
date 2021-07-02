// This header is designed to be included multiple times.
// vim: tw=75

// ISO 2022 (= ECMA 35) specifies the structure
// ISO 2375 specifies the procedure for the registry
// ITSCJ, under JISC, maintains the registry here:
// https://www.itscj.ipsj.or.jp/itscj_english/index.html

#ifdef ISO_IR_DEFAULTS
# ifndef ISO_IR_SBCS94
#  define ISO_IR_SBCS94(reg, rev, ...) /* nothing */
# endif
# ifndef ISO_IR_SBCS96
#  define ISO_IR_SBCS96(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_MBCS94
#  define ISO_IR_MBCS94(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_C0
#  define ISO_IR_C0(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_C1
#  define ISO_IR_C1(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_SINGLE
#  define ISO_IR_SINGLE(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_SWITCH_RETURN
#  define ISO_IR_SWITCH_RETURN(reg, rev, f) /* nothing */
# endif
# ifndef ISO_IR_SWITCH_NORETURN
#  define ISO_IR_SWITCH_NORETURN(reg, rev, f) /* nothing */
# endif
#else
# ifndef ISO_IR_SBCS94
#  error "ISO_IR_SBCS94 is not defined"
# endif
# ifndef ISO_IR_SBCS96
#  error "ISO_IR_SBCS96 is not defined"
# endif
# ifndef ISO_IR_MBCS94
#  error "ISO_IR_MBCS94 is not defined"
# endif
# ifndef ISO_IR_C0
#  error "ISO_IR_C0 is not defined"
# endif
# ifndef ISO_IR_C1
#  error "ISO_IR_C1 is not defined"
# endif
# ifndef ISO_IR_SINGLE
#  error "ISO_IR_SINGLE is not defined"
# endif
# ifndef ISO_IR_SWITCH_RETURN
#  error "ISO_IR_SWITCH_RETURN is not defined"
# endif
# ifndef ISO_IR_SWITCH_NORETURN
#  error "ISO_IR_SWITCH_NORETURN is not defined"
# endif
#endif

/// 94-Character graphic character sets with one Intermediate byte
#if 0
    // Template for (mostly-non-ASCII) character sets not based on ISO 646.
    ISO_IR_SBCS94_DATA(
        /**/  u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,
        u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,
        u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,
        u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,
        u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,
        u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0,   u0    /**/
    )
    // Template for (mostly-ASCII) character sets based on ISO 646. (= IR 170)
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u0,   u0,    '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u0,    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u0,   u0,   u0,   u0,    '_',
        u0,    'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u0,   u0,   u0,   u0    /**/
    )
    // Template for (never-ASCII) 96-character character sets.
    ISO_IR_SBCS96_DATA(
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ',
        u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' ', u' '
    )
#endif
// IRV of ISO 646 : 1983
ISO_IR_SBCS94(2,(-1), 0x40)
    // 1975-12-01
    // G0: ESC \x28 \x40
    // G1: ESC \x29 \x40
    // G2: ESC \x2a \x40
    // G3: ESC \x2b \x40
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}', u'¯'  /**/
    )
// ISO 646, British Version BSI 4730
ISO_IR_SBCS94(4,(-1), 0x41)
    // 1975-12-01
    // G0: ESC \x28 \x41
    // G1: ESC \x29 \x41
    // G2: ESC \x2a \x41
    // G3: ESC \x2b \x41
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}', u'¯'  /**/
    )
// ISO 646, USA Version X3.4 - 1968
ISO_IR_SBCS94(6,(-1), 0x42)
    // 1975-12-01
    // G0: ESC \x28 \x42
    // G1: ESC \x29 \x42
    // G2: ESC \x2a \x42
    // G3: ESC \x2b \x42
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}',  '~'  /**/
    )
// NATS, Primary Set for Finland and Sweden
ISO_IR_SBCS94(8001,(-1), 0x43)
    // 1975-12-01
    // G0: ESC \x28 \x43
    // G1: ESC \x29 \x43
    // G2: ESC \x2a \x43
    // G3: ESC \x2b \x43
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    u'\u2003', 'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ä', u'Ö', u'Å', u'█',  '_',
    u'\u2002', 'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ä', u'ö', u'å', u'‐'  /**/
    )
// NATS, Secondary Set for Finland and Sweden
ISO_IR_SBCS94(8002,(-1), 0x44)
    // 1975-12-01
    // G0: ESC \x28 \x44
    // G1: ESC \x29 \x44
    // G2: ESC \x2a \x44
    // G3: ESC \x2b \x44
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,   u'À',  0,    0,   u'Đ', u'É',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'Þ',  0,    0,    0,    0,   u'Ü',  0,    0,    0,    0,    0,   u'Æ', u'Ø',  0,    0,    0,
         0,   u'à',  0,    0,   u'đ', u'é',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'þ',  0,    0,    0,    0,   u'ü',  0,    0,    0,    0,    0,   u'æ', u'ø',  0,    0    /**/
    )
// NATS, Primary Set for Denmark and Norway
ISO_IR_SBCS94(9001,(-1), 0x45)
    // 1975-12-01
    // G0: ESC \x28 \x45
    // G1: ESC \x29 \x45
    // G2: ESC \x2a \x45
    // G3: ESC \x2b \x45
    ISO_IR_SBCS94_DATA(
        /**/   '!', u'«', u'»',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    u'\u2003', 'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Æ', u'Ø', u'Å', u'█',  '_',
    u'\u2002', 'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'æ', u'ø', u'å', u'‐'  /**/
    )
// NATS, Secondary Set for Denmark and Norway
ISO_IR_SBCS94(9002,(-1), 0x46)
    // 1975-12-01
    // G0: ESC \x28 \x46
    // G1: ESC \x29 \x46
    // G2: ESC \x2a \x46
    // G3: ESC \x2b \x46
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,   u'À',  0,    0,   u'Đ', u'É',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'Þ',  0,    0,    0,    0,   u'Ü',  0,    0,    0,    0,    0,   u'Ä', u'Ö',  0,    0,    0,
         0,   u'à',  0,    0,   u'đ', u'é',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'þ',  0,    0,    0,    0,   u'ü',  0,    0,    0,    0,    0,   u'ä', u'ö',  0,    0    /**/
    )
// ISO 646, Swedish Version SEN 850200 (Ann. B)
ISO_IR_SBCS94(1 0,   0x47)
    // 1975-12-01
    // G0: ESC \x28 \x47
    // G1: ESC \x29 \x47
    // G2: ESC \x2a \x47
    // G3: ESC \x2b \x47
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ä', u'Ö', u'Å',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ä', u'ö', u'å', u'¯'  /**/
    )
// ISO 646, Swedish Version for Names, (SEN 850200 Ann. C)
    // 1975-12-01
    // G0: ESC \x28 \x48
    // G1: ESC \x29 \x48
    // G2: ESC \x2a \x48
    // G3: ESC \x2b \x48
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'É',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ä', u'Ö', u'Å', u'Ü',  '_',
        u'é',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ä', u'ö', u'å', u'ü'  /**/
    )
ISO_IR_SBCS94(11,(-1), 0x48)
// Katakana Character Set JIS C6220-1969
ISO_IR_SBCS94(13,(-1), 0x49)
    // 1975-12-01
    // G0: ESC \x28 \x49
    // G1: ESC \x29 \x49
    // G2: ESC \x2a \x49
    // G3: ESC \x2b \x49
    ISO_IR_SBCS94_DATA(
        /**/  u'｡', u'｢', u'｣', u'､', u'･', u'ｦ', u'ｧ', u'ｨ', u'ｩ', u'ｪ', u'ｫ', u'ｬ', u'ｭ', u'ｮ', u'ｯ',
        u'ｰ', u'ｱ', u'ｲ', u'ｳ', u'ｴ', u'ｵ', u'ｶ', u'ｷ', u'ｸ', u'ｹ', u'ｺ', u'ｻ', u'ｼ', u'ｽ', u'ｾ', u'ｿ',
        u'ﾀ', u'ﾁ', u'ﾂ', u'ﾃ', u'ﾄ', u'ﾅ', u'ﾆ', u'ﾇ', u'ﾈ', u'ﾉ', u'ﾊ', u'ﾋ', u'ﾌ', u'ﾍ', u'ﾎ', u'ﾏ',
        u'ﾐ', u'ﾑ', u'ﾒ', u'ﾓ', u'ﾔ', u'ﾕ', u'ﾖ', u'ﾗ', u'ﾘ', u'ﾙ', u'ﾚ', u'ﾛ', u'ﾜ', u'ﾝ', u'ﾞ', u'ﾟ',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// ISO 646, Japanese Version for Roman Characters JIS C6220-1969
ISO_IR_SBCS94(14,(-1), 0x4a)
    // 1975-12-01
    // G0: ESC \x28 \x4a
    // G1: ESC \x29 \x4a
    // G2: ESC \x2a \x4a
    // G3: ESC \x2b \x4a
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', u'¥',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}', u'¯'  /**/
    )
// ISO 646, Version for Italian, ECMA (Olivetti)
ISO_IR_SBCS94(15,(-1), 0x59)
    // 1976-02-01
    // G0: ESC \x28 \x59
    // G1: ESC \x29 \x59
    // G2: ESC \x2a \x59
    // G3: ESC \x2b \x59
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'§',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'°', u'ç', u'é',  '^',  '_',
        u'ù',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'à', u'ò', u'è', u'ì'  /**/
    )
// ISO 646, Version for Portuguese, ECMA (Olivetti)
ISO_IR_SBCS94(16,(-1), 0x4c)
    // 1976-12-30
    // G0: ESC \x28 \x4c
    // G1: ESC \x29 \x4c
    // G2: ESC \x2a \x4c
    // G3: ESC \x2b \x4c
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'§',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ã', u'Ç', u'Õ',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ã', u'ç', u'õ', u'°'  /**/
    )
// ISO 646, Version for Spanish, ECMA (Olivetti)
ISO_IR_SBCS94(17,(-1), 0x5a)
    // 1976-02-01
    // G0: ESC \x28 \x5a
    // G1: ESC \x29 \x5a
    // G2: ESC \x2a \x5a
    // G3: ESC \x2b \x5a
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'§',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'¡', u'Ñ', u'¿',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'°', u'ñ', u'ç',  '~'  /**/
    )
// Character Set for Greek, ECMA (Olivetti)
ISO_IR_SBCS94(18,(-1), 0x5b)
    // 1976-02-01
    // G0: ESC \x28 \x5b
    // G1: ESC \x29 \x5b
    // G2: ESC \x2a \x5b
    // G3: ESC \x2b \x5b
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':', u';',  '<',  '=',  '>',  '?',
        u'´', u'α', u'β', u'ψ', u'δ', u'ε', u'φ', u'γ', u'η', u'ι', u'ξ', u'κ', u'λ', u'μ', u'ν', u'ο',
        u'π', u'ͺ', u'ρ', u'σ', u'τ', u'θ', u'ω', u'ς', u'χ', u'υ', u'ζ', u'῏', u'᾿', u'῎',  '~',  '_',
        u'`', u'Α', u'Β', u'Ψ', u'Δ', u'Ε', u'Φ', u'Γ', u'Η', u'Ι', u'Ξ', u'Κ', u'Λ', u'Μ', u'Ν', u'Ο',
        u'Π',  0,   u'Ρ', u'Σ', u'Τ', u'Θ', u'Ω', u'·', u'Χ', u'Υ', u'Ζ', u'῟', u'῾', u'῞', u'¨'  /**/
    )
// Latin-Greek Character Set, ECMA (Olivetti)
ISO_IR_SBCS94(19,(-1), 0x5c)
    // 1976-02-01
    // G0: ESC \x28 \x5c
    // G1: ESC \x29 \x5c
    // G2: ESC \x2a \x5c
    // G3: ESC \x2b \x5c
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', u'´',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':', u';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
        u'`', u'Α', u'Β', u'Ψ', u'Δ', u'Ε', u'Φ', u'Γ', u'Η', u'Ι', u'Ξ', u'Κ', u'Λ', u'Μ', u'Ν', u'Ο',
        u'Π',  0,   u'Ρ', u'Σ', u'Τ', u'Θ', u'Ω', u'·', u'Χ', u'Υ', u'Ζ',  '{',  '|',  '}', u'¨'  /**/
    )
// ISO 646, German Version DIN 66083
ISO_IR_SBCS94(21,(-1), 0x4b)
    // 1975-12-01
    // G0: ESC \x28 \x4b
    // G1: ESC \x29 \x4b
    // G2: ESC \x2a \x4b
    // G3: ESC \x2b \x4b
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'§',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ä', u'Ö', u'Ü',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ä', u'ö', u'ü', u'ß'  /**/
    )
// ISO 646, French Version, NF Z 62010-1973 (Withdrawn in April 1985)
// Use ISO_IR_SBCS94(69, 0x66) instead.
ISO_IR_SBCS94(25,(-1), 0x52)
    // 1975-12-01
    // G0: ESC \x28 \x52
    // G1: ESC \x29 \x52
    // G2: ESC \x2a \x52
    // G3: ESC \x2b \x52
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'à',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'°', u'ç', u'§',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'ù', u'è', u'¨'  /**/
    )
// Latin-Greek Character Set, ECMA (Honeywell-Bull)
ISO_IR_SBCS94(27,(-1), 0x55)
    // 1976-04-01
    // G0: ESC \x28 \x55
    // G1: ESC \x29 \x55
    // G2: ESC \x2a \x55
    // G3: ESC \x2b \x55
    ISO_IR_SBCS94_DATA(
        /**/  u'Ξ',  '"', u'Γ', u'§',  '%',  '&', u'´',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':', u';',  '<',  '=',  '>', u'Π',
        u'Δ', u'Α', u'Β',  'C',  'D', u'Ε',  'F',  'G', u'Η', u'Ι',  'J', u'Κ',  'L', u'Μ', u'Ν', u'Ο',
        u'Ρ',  'Q',  'R',  'S', u'Τ',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ω', u'Θ', u'Φ', u'Λ', u'Σ',
        u'`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}', u'¯'  /**/
    )
// Greek Character Set for Bibliography, ISO 5428
ISO_IR_SBCS94(31,(-1), 0x58)
    // 1976-08-13
    // G0: ESC \x28 \x58
    // G1: ESC \x29 \x58
    // G2: ESC \x2a \x58
    // G3: ESC \x2b \x58
    ISO_IR_SBCS94_DATA(
        // Note: in the marked columns, 0x2_ should be overstruck on lowercase,
        // whereas 0x3_ should occur before a capital.
        //                              v     v     v     v                 v     v     v     v
         0,   u'`', u'´', u'῭', u'῀', u'᾿', u'῾', u'῎', u'῞', u'¨', u'ͺ', u'῍', u'῝', u'῏', u'῟', u'΅',
         0,    0,    0,    0,    0,   u'᾿', u'῾', u'῎', u'῞',  0,    0,   u'῍', u'῝', u'῏', u'῟',  0,
        //                              ^     ^     ^     ^                 ^     ^     ^     ^
         0,   u'Α', u'Β', u'Γ', u'Δ', u'Ε', u'Ζ', u'Η', u'Θ', u'Ι', u'Κ', u'Λ', u'Μ', u'Ν', u'Ξ', u'Ο',
        u'Π', u'Ρ', u'Σ', u'Τ', u'Υ', u'Φ', u'Χ', u'Ψ', u'Ω', u'·', u'«', u'»', u'“', u'”', u'ʹ', u'͵',
         0,   u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ', u'ο',
        u'π', u'ρ', u'σ', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω', u'ς', u'Ϝ', u'Ϟ', u'Ϡ', u'Ϛ',  0,    0,
    )
// Basic Cyrillic Character Set, ECMA (Cii Honeywell-Bull) and ISO 5427
ISO_IR_SBCS94(37,(-1), 0x4e)
    // 1979-05-30 (amended October 1983)
    // G0: ESC \x28 \x4e
    // G1: ESC \x29 \x4e
    // G2: ESC \x2a \x4e
    // G3: ESC \x2b \x4e
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        // Same order as KOI8-R
        u'ю', u'а', u'б', u'ц', u'д', u'е', u'ф', u'г', u'х', u'и', u'й', u'к', u'л', u'м', u'н', u'о',
        u'п', u'я', u'р', u'с', u'т', u'у', u'ж', u'в', u'ь', u'ы', u'з', u'ш', u'э', u'щ', u'ч', u'ъ',
        u'Ю', u'А', u'Б', u'Ц', u'Д', u'Е', u'Ф', u'Г', u'Х', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О',
        u'П', u'Я', u'Р', u'С', u'Т', u'У', u'Ж', u'В', u'Ь', u'Ы', u'З', u'Ш', u'Э', u'Щ', u'Ч'  /**/
    )
// Extended Graphic Character Set for Bibliography, DIN 31624
ISO_IR_SBCS94(38,(-1), 0x4f)
    // 1979-07-15
    // G0: ESC \x28 \x4f
    // G1: ESC \x29 \x4f
    // G2: ESC \x2a \x4f
    // G3: ESC \x2b \x4f
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'„', u'£', u'¤', u'‰', u'†',  '@', u'°',  '[',  '{', u'«', u'♭', u'©', u'℗', u'®',
        u'ʿ', u'ʾ', u'‚',  0,   '\\',  '|', u'‡', u'·', u'→',  ']',  '}', u'»', u'♯', u'ʹ', u'ʺ', u'¿',
        // These two rows are *precombining*, unlike unicode, and unlike
        // most other ISO-2022 diacritics, which require an explicit BS.
        // Beware of *multiple* accents, in the same or different CCCs.
        // Position 5/13 is ambiguous; it depends on the next cell.
        u'̉',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',  u'̶',  u'̊',  u'̕',  u'̒',  u'̋',  u'̛',  u'̌',
        u'̧',  u'̜',  u'̦',  u'̨',  u'̥',  u'̮',  u'̣',  u'̷',  u'̲',  u'̳',  u'̩',  u'̭',   0,   u'︠',  u'︡',  u'︣',
         0,   u'Æ', u'Đ',  0,    0,    0,    0,    0,   u'Ł', u'Ø', u'Œ',  0,   u'Þ',  0,    0,    0,
         0,   u'æ', u'đ', u'ð',  0,   u'ı',  0,    0,   u'ł', u'ø', u'œ', u'Ʀ', u'þ',  0,    0,    0,
    )
// Character Set for African Languages, DIN 31625 and ISO 6438
ISO_IR_SBCS94(39,(-1), 0x4d)
    // 1979-06-15
    // G0: ESC \x28 \x4d
    // G1: ESC \x29 \x4d
    // G2: ESC \x2a \x4d
    // G3: ESC \x2b \x4d
    ISO_IR_SBCS94_DATA(
        // Same as ISO 6438
         0,    0,   u'Ɓ', u'Ƈ', u'Ɗ', u'Ɖ',  0,   u'Ɛ', u'Ǝ',  0,   u'Ƒ', u'Ɠ', u'Ɣ', u'Ħ',  0,   u'Ɨ',
         0,    0,   u'ɓ', u'ƈ', u'ɗ', u'ɖ',  0,   u'ɛ', u'ə',  0,   u'ƒ', u'ɠ', u'ɣ', u'ħ',  0,   u'ɪ',
        u'Ƙ',  0,    0,    0,    0,    0,    0,   u'Ŋ',  0,   u'Ɵ', u'Ɔ', u'Ƥ',  0,    0,    0,   u'Ʃ',
        u'ƙ', u'ɬ', u'ɱ', u'ɳ', u'ɲ',  0,    0,   u'ŋ',  0,   u'ɵ', u'ɔ', u'ƥ',  0,   u'ɽ',  0,   u'ʃ',
        u'Ƭ', u'Ʈ',  0,   u'Ʊ', u'Ʋ', u'Χ', u'Ƴ', u'Ʒ',  0,    0,    0,    0,    0,    0,    0,    0,
        u'ƭ', u'ʈ',  0,   u'ʊ', u'ʋ', u'χ', u'ƴ', u'ʒ', u'ʕ', u'ʔ', u'ʘ', u'ǀ', u'ǂ', u'ǃ', u'ǁ'  /**/
    )
// Character Set for Viewdata and Teletext (UK)
ISO_IR_SBCS94(47,(-1), 0x56)
    // 1981-06-01
    // G0: ESC \x28 \x56
    // G1: ESC \x29 \x56
    // G2: ESC \x2a \x56
    // G3: ESC \x2b \x56
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'←', u'½', u'→', u'↑', u'⌗',
        u'―',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'¼', u'‖', u'¾', u'÷'  /**/
    )
// INIS, Sub-set of the IRV
ISO_IR_SBCS94(49,(-1), 0x57)
    // 1981-07-15
    // G0: ESC \x28 \x57
    // G1: ESC \x29 \x57
    // G2: ESC \x2a \x57
    // G3: ESC \x2b \x57
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    '$',  '%',  0,   '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  0,
         0,    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[',  0,    ']',  0,    0,
         0,    'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  0,    '|',  0,    0    /**/
    )
// INIS, Non-standard Extension of Reg. 49
ISO_IR_SBCS94(50,(-1), 0x5d)
    // 1981-07-15
    // G0: ESC \x28 \x5d
    // G1: ESC \x29 \x5d
    // G2: ESC \x2a \x5d
    // G3: ESC \x2b \x5d
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'α', u'β', u'γ', u'σ', u'Ξ',  0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'→', u'∫',
        u'⁰', u'¹', u'²', u'³', u'⁴', u'⁵', u'⁶', u'⁷', u'⁸', u'⁹', u'⁺', u'⁻', u'√', u'Δ', u'Λ', u'Ω',
        u'₀', u'₁', u'₂', u'₃', u'₄', u'₅', u'₆', u'₇', u'₈', u'₉', u'Σ', u'μ', u'ν', u'ω', u'π'  /**/
    )
// INIS, Cyrillic Extension of Reg. 49
ISO_IR_SBCS94(51,(-1), 0x5e)
    // 1981-07-15
    // G0: ESC \x28 \x5e
    // G1: ESC \x29 \x5e
    // G2: ESC \x2a \x5e
    // G3: ESC \x2b \x5e
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'√',  0,   u'→', u'∫',
        u'α', u'β', u'γ', u'δ', u'Σ', u'μ', u'ν', u'ω', u'π', u'Ξ', u'Δ', u'Λ', u'Ω', u'Ъ', u'⁻', u'⁺',
        // Same order as KOI8-R
        u'ю', u'а', u'б', u'ц', u'д', u'е', u'ф', u'г', u'х', u'и', u'й', u'к', u'л', u'м', u'н', u'о',
        u'п', u'я', u'р', u'с', u'т', u'у', u'ж', u'в', u'ь', u'ы', u'з', u'ш', u'э', u'щ', u'ч', u'ъ',
        u'Ю', u'А', u'Б', u'Ц', u'Д', u'Е', u'Ф', u'Г', u'Х', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О',
        u'П', u'Я', u'Р', u'С', u'Т', u'У', u'Ж', u'В', u'Ь', u'Ы', u'З', u'Ш', u'Э', u'Щ', u'Ч'  /**/
    )
// Extended Graphic Character Set for Bibliography ISO 5426-1980
ISO_IR_SBCS94(53,(-1), 0x50)
    // 1982-06-01
    // G0: ESC \x28 \x50
    // G1: ESC \x29 \x50
    // G2: ESC \x2a \x50
    // G3: ESC \x2b \x50
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'„', u'£',  '$', u'¥', u'†', u'§', u'′', u'‘', u'“', u'«', u'♭', u'©', u'℗', u'®',
        u'ʿ', u'ʾ', u'‚',  0,    0,    0,   u'‡', u'·', u'″', u'’', u'”', u'»', u'♯', u'ʹ', u'ʺ', u'¿',
        // These two rows are *precombining*, unlike unicode, and unlike
        // most other ISO-2022 diacritics, which require an explicit BS.
        // Beware of *multiple* accents, in the same or different CCCs.
        // Position 5/13 is ambiguous; it depends on the next cell.
        u'̉',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',  u'̈',  u'̊',  u'̕',  u'̒',  u'̋',  u'̛',  u'̌',
        u'̧',  u'̜',  u'̦',  u'̨',  u'̥',  u'̮',  u'̣',  u'̤',  u'̲',  u'̳',  u'̩',  u'̭',   0,   u'︠',  u'︡',  u'︣',
         0,   u'Æ', u'Đ',  0,    0,    0,   u'Ĳ',  0,   u'Ł', u'Ø', u'Œ',  0,   u'Þ',  0,    0,    0,
         0,   u'æ', u'đ', u'ð',  0,   u'ı', u'ĳ',  0,   u'ł', u'ø', u'œ', u'ß', u'þ',  0,    0,    0,
    )
// Extension of the Cyrillic Character Set of Reg. 37, ISO 5427-1981
ISO_IR_SBCS94(54,(-1), 0x51)
    // 1982-06-01
    // G0: ESC \x28 \x51
    // G1: ESC \x29 \x51
    // G2: ESC \x2a \x51
    // G3: ESC \x2b \x51
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'ґ', u'ђ', u'ѓ', u'є', u'ё', u'ѕ', u'і', u'ї', u'ј', u'љ', u'њ', u'ћ', u'ќ', u'ў', u'џ',  0,
        u'ѣ', u'ѳ', u'ѵ', u'ѫ',  0,    0,    0,    0,    0,    0,    0,    '[',  0,    ']',  0,    '_',
        u'Ґ', u'Ђ', u'Ѓ', u'Є', u'Ё', u'Ѕ', u'І', u'Ї', u'Ј', u'Љ', u'Њ', u'Ћ', u'Ќ', u'Ў', u'Џ',  0,
        u'Ѣ', u'Ѳ', u'Ѵ', u'Ѫ',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// Greek Character Set for Bibliography, ISO 5428-1980
ISO_IR_SBCS94(55,(-1), 0x53)
    // 1982-06-01
    // G0: ESC \x28 \x53
    // G1: ESC \x29 \x53
    // G2: ESC \x2a \x53
    // G3: ESC \x2b \x53
    ISO_IR_SBCS94_DATA(
        // Unlike unicode, this row is *precombining*.
         0,   u'̀',  u'́',  u'̈',  u'͂',  u'̓',  u'̔',  u'ͅ',   0,    0,    0,    0,    0,    0,    0,    0,
        u'«', u'»', u'“', u'”', u'ʹ', u'͵',  0,    0,    0,    0,    0,   u'·',  0,    0,    0,   u';',
         0,   u'Α', u'Β',  0,   u'Γ', u'Δ', u'Ε', u'Ϛ', u'Ϝ', u'Ζ', u'Η', u'Θ', u'Ι', u'Κ', u'Λ', u'Μ',
        u'Ν', u'Ξ', u'Ο', u'Π', u'Ϟ', u'Ρ', u'Σ',  0,   u'Τ', u'Υ', u'Φ', u'Χ', u'Ψ', u'Ω', u'Ϡ',  0,
         0,   u'α', u'β', u'ϐ', u'γ', u'δ', u'ε', u'ϛ', u'ϝ', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ',
        u'ν', u'ξ', u'ο', u'π', u'ϟ', u'ρ', u'σ', u'ς', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω', u'ϡ'  /**/
    )
// Coded Character Set for Information Interchange, Standard Chinese GB 1988-80
ISO_IR_SBCS94(57,(-1), 0x54)
    // 1982-06-01
    // G0: ESC \x28 \x54
    // G1: ESC \x29 \x54
    // G2: ESC \x2a \x54
    // G3: ESC \x2b \x54
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¥',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', '\\',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}', u'¯'  /**/
    )
// Arabic Character Set CODAR-U IERA (Morocco)
ISO_IR_SBCS94(59,(-1), 0x5f)
    // 1982-06-01
    // G0: ESC \x28 \x5f
    // G1: ESC \x29 \x5f
    // G2: ESC \x2a \x5f
    // G3: ESC \x2b \x5f
    ISO_IR_SBCS94_DATA(
        // TODO needs attention from a native/expert.
        // Also, should probably unconditionally fix presentation forms.
         0,    '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+', u'،',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':', u'؛',  '<',  '=',  '>', u'؟',
         '@', u'ﳲ', u'ﱠ', u'ﳳ', u'ﱡ', u'ﳴ', u'ﱢ', u'ﹷ', u'ﹶ', u'ﹰ', u'ﹹ', u'ﹸ', u'ﹲ', u'ﹻ', u'ﹺ', u'ﹴ',
        u'ﹿ', u'ﹾ', u'ﹽ', u'ﹼ', u'أ', u'آ', u'ؤ', u'ئ', u'ۓ', u'إ', u'ي', u'پ', u'ڤ', u'گ', u'ﺀ', u'ا',
        u'ب', u'ت', u'ة', u'ث', u'ﺟ', u'ﺣ', u'ﺧ', u'د', u'ذ', u'ر', u'ز', u'س', u'ش', u'ص', u'ض', u'ط',
        u'ظ', u'ﻋ', u'ﻏ', u'ف', u'ق', u'ﻛ', u'ﻟ', u'ﻣ', u'ﻧ', u'ﻫ', u'و', u'ے', u'¦', u'ى',  '_'  /**/
    )
// ISO 646, Norwegian Version NS 4551
ISO_IR_SBCS94(60,(-1), 0x60)
    // 1982-06-01
    // G0: ESC \x28 \x60
    // G1: ESC \x29 \x60
    // G2: ESC \x2a \x60
    // G3: ESC \x2b \x60
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Æ', u'Ø', u'Å',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'æ', u'ø', u'å', u'¯'  /**/
    )
// Norwegian Character Set, Version 2, NS 4551 (Withdrawn in June 1987)
ISO_IR_SBCS94(61,(-1), 0x61)
    // 1982-06-01
    // G0: ESC \x28 \x61
    // G1: ESC \x29 \x61
    // G2: ESC \x2a \x61
    // G3: ESC \x2b \x61
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'§',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Æ', u'Ø', u'Å',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'æ', u'ø', u'å',  '|'  /**/
    )
// APL Character Set, Canadian APL Working Group
ISO_IR_SBCS94(68,(-1), 0x65)
    // 1983-06-01
    // G0: ESC \x28 \x65
    // G1: ESC \x29 \x65
    // G2: ESC \x2a \x65
    // G3: ESC \x2b \x65
    ISO_IR_SBCS94_DATA(
        /**/  u'¨',  ')',  '<', u'≤',  '=',  '>',  ']', u'∧', u'∨', u'≠', u'÷',  ',',  '+',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '(',  '[',  ';', u'×',  ':', '\\',
        u'¯', u'⍺', u'⊥', u'∩', u'⌊', u'∊',  '_', u'∇', u'∆', u'⍳', u'∘', '\'', u'⎕',  '|', u'⊤', u'○',
        u'⋆',  '?', u'⍴', u'⌈', u'∼', u'↓', u'∪', u'⍵', u'⊂', u'↑', u'⊃', u'←', u'⊢', u'→', u'≥',  '-',
        u'⋄',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '{', u'⊣',  '}',  '$'  /**/
    )
// ISO 646, French Version NF Z 62010-1982
ISO_IR_SBCS94(69,(-1), 0x66)
    // 1983-06-01
    // G0: ESC \x28 \x66
    // G1: ESC \x29 \x66
    // G2: ESC \x2a \x66
    // G3: ESC \x2b \x66
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'à',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'°', u'ç', u'§',  '^',  '_',
        u'μ',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'ù', u'è', u'¨'  /**/
    )
// Supplementary Set for Videotex, CCITT
ISO_IR_SBCS94(70,(-1), 0x62)
    // 1988-11-01
    // G0: ESC \x28 \x62
    // G1: ESC \x29 \x62
    // G2: ESC \x2a \x62
    // G3: ESC \x2b \x62
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'¢', u'£',  '$', u'¥',  '#', u'§', u'¤', u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
        // Unlike unicode, this row is *precombining*.
        u'̈́',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',   0,   u'̊',  u'̧',   0,   u'̋',  u'̨',  u'̌',
        u'―', u'¹', u'®', u'©', u'™', u'♪',  0,    0,    0,    0,    0,    0,   u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ',  0,   u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ'  /**/
    )
// Second Supplementary Set for Videotex (Mosaic), CCITT
ISO_IR_SBCS94(71,(-1), 0x63)
    // 1983-10-01
    // G0: ESC \x28 \x63
    // G1: ESC \x29 \x63
    // G2: ESC \x2a \x63
    // G3: ESC \x2b \x63
    ISO_IR_SBCS94_DATA(
        /**/  MG01, MG02, MG03, MG04, MG05, MG06, MG07, MG08, MG09, MG10, MG11, MG12, MG13, MG14, MG15,
        MG16, MG17, MG18, MG19, MG20, MG21, MG22, MG23, MG24, MG25, MG26, MG27, MG28, MG29, MG30, MG31,
        SG01, SG02, SG03, SG04, SG05, SG06, SG07, SG08, SG09, SG10, SG11, SG12, SG13, SG14, SM45, DG32,
        SG28, SG27, SG26, SG25, SG24, SG23, SG22, SG21, SG20, SG19, SG18, SG17, SG16, SG15, SM46, MG63,
        MG32, MG33, MG34, MG35, MG36, MG37, MG38, MG39, MG40, MG41, MG42, MG43, MG44, MG45, MG46, MG47,
        MG48, MG49, MG50, MG51, MG52, MG53, MG54, MG55, MG56, MG57, MG58, MG59, MG60, MG61, MG62  /**/
    )
// Third Supplementary Set for Videotex, (Mosaic), CCITT (superseded by Reg. 173)
ISO_IR_SBCS94(72,(-1), 0x64)
    // 1983-10-01
    // G0: ESC \x28 \x64
    // G1: ESC \x29 \x64
    // G2: ESC \x2a \x64
    // G3: ESC \x2b \x64
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        DG01, DG02, DG03, DG04, DG05, DG06, DG07, DG08, DG09, DG10, DG11, DG12, DG13, DG29, DG30, DG31,
        DG14, DG15, DG16, DG17, DG18, DG19, DG20, DG21, DG22, DG23, DG24, DG25, DG26, DG27, DG28,  0,
        SG29, SG30, SG31, SG32, SG33, SG34, SG35, SG36, SG37, SG38, SG39, SG40, SG41, SG42,  0,    0,
        SG43, SG44, SG45, SG46, SG47, SG48, SG49, SG50, SG51, SG52, SG53, SG54, SG55, SG56,  0    /**/
    )
// ISO 646, Version for Portuguese, ECMA (IBM)
ISO_IR_SBCS94(84,(-1), 0x67)
    // 1984-07-01
    // G0: ESC \x28 \x67
    // G1: ESC \x29 \x67
    // G2: ESC \x2a \x67
    // G3: ESC \x2b \x67
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'´',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Ã', u'Ç', u'Õ',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'ã', u'ç', u'õ',  '~'  /**/
    )
// ISO 646, Version for the Spanish languages, ECMA (IBM)
ISO_IR_SBCS94(85,(-1), 0x68)
    // 1984-07-01
    // G0: ESC \x28 \x68
    // G1: ESC \x29 \x68
    // G2: ESC \x2a \x68
    // G3: ESC \x2b \x68
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'·',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'¡', u'Ñ', u'Ç', u'¿',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'´', u'ñ', u'ç', u'¨'  /**/
    )
// ISO 646, Hungarian Version Hungarian standard 7795/3
ISO_IR_SBCS94(86,(-1), 0x69)
    // 1984-07-01
    // G0: ESC \x28 \x69
    // G1: ESC \x29 \x69
    // G2: ESC \x2a \x69
    // G3: ESC \x2b \x69
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'Á',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'É', u'Ö', u'Ü',  '^',  '_',
        u'á',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'ö', u'ü', u'˝'  /**/
    )
// Greek Character Set ELOT, Hellenic Organization for Standardization (Withdrawn in November 1986)
ISO_IR_SBCS94(88,(-1), 0x6a)
    // 1984-07-01
    // G0: ESC \x28 \x6a
    // G1: ESC \x29 \x6a
    // G2: ESC \x2a \x6a
    // G3: ESC \x2b \x6a
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@', u'Α', u'Β', u'Γ', u'Δ', u'Ε', u'Ζ', u'Η', u'Θ', u'Ι',  0,   u'Κ', u'Λ', u'Μ', u'Ν', u'Ξ',
        u'Ο', u'Π', u'Ρ', u'Σ', u'Τ', u'Υ', u'Φ',  0,   u'Χ', u'Ψ', u'Ω',  '[', '\\',  ']',  '^',  '_',
         '`', u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι',  0,   u'κ', u'λ', u'μ', u'ν', u'ξ',
        u'ο', u'π', u'ρ', u'σ', u'τ', u'υ', u'φ', u'ς', u'χ', u'ψ', u'ω',  '{',  '|',  '}', u'¯'  /**/
    )
// 7-bit Arabic Code for Information Interchange, Arab standard ASMO-449, ISO 9036
ISO_IR_SBCS94(89,(-1), 0x6b)
    // 1985-01-01
    // G0: ESC \x28 \x6b
    // G1: ESC \x29 \x6b
    // G2: ESC \x2a \x6b
    // G3: ESC \x2b \x6b
    ISO_IR_SBCS94_DATA(
        // Note: > and < are pre-mirrored. If your rendering system is BIDI
        // aware, swap them ... but then you need to explicitly set
        // BIDI=RTL when using this codepage so isolated ones are correct.
        // Note: it is unclear whether positions 6/11 to 7/2 should be
        // combining or not.
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+', u'،',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':', u'؛',  '>',  '=',  '<', u'؟',
         '@', u'ء', u'آ', u'أ', u'ؤ', u'إ', u'ئ', u'ا', u'ب', u'ت', u'ة', u'ث', u'ج', u'ح', u'خ', u'د',
        u'ذ', u'ر', u'ز', u'س', u'ش', u'ص', u'ض', u'ط', u'ظ', u'ع', u'غ',  ']', '\\',  '[',  '^',  '_',
        u'ـ', u'ف', u'ق', u'ك', u'ل', u'م', u'ن', u'ه', u'و', u'ى', u'ي', u'ﹰ', u'ﹲ', u'ﹴ', u'ﹶ', u'ﹸ',
        u'ﹺ', u'ﹼ', u'ﹾ',  0,    0,    0,    0,    0,    0,    0,    0,    '}',  '|',  '{', u'¯'  /**/
    )
// Supplementary Set for Use with Registration No.2
ISO_IR_SBCS94(90,(-1), 0x6c)
    // 1985-01-01
    // G0: ESC \x28 \x6c
    // G1: ESC \x29 \x6c
    // G2: ESC \x2a \x6c
    // G3: ESC \x2b \x6c
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'¢', u'£',  '$', u'¥',  0,   u'§',  0,   u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
         0,   u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',   0,   u'̊',  u'̧',  u'̲',  u'̋',  u'̨',  u'̌',
        u'—', u'¹', u'®', u'©', u'™'  u'♪',  0,    0,    0,    0,    0,    0,   u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ',  0,   u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ'  /**/
    )
// Japanese OCR-A graphic set JIS C6229-1984
ISO_IR_SBCS94(91,(-1), 0x6d)
    // 1985-08-01
    // G0: ESC \x28 \x6d
    // G1: ESC \x29 \x6d
    // G2: ESC \x2a \x6d
    // G3: ESC \x2b \x6d
    ISO_IR_SBCS94_DATA(
        /**/   0,    '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';', u'⑀',  '=', u'⑁',  '?',
         0,    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  0,   u'¥', u'⑂'   0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    '|',  0,    0    /**/
    )
// Japanese OCR-B Graphic Set JIS C6229-1984
ISO_IR_SBCS94(92,(-1), 0x6e)
    // 1985-08-01
    // G0: ESC \x28 \x6e
    // G1: ESC \x29 \x6e
    // G2: ESC \x2a \x6e
    // G3: ESC \x2b \x6e
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', u'¥',  ']',  '^',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  '{',  '|',  '}',  '~'  /**/
    )
// Japanese OCR-B, Additional Graphic Set, JIS C6229-1984
ISO_IR_SBCS94(93,(-1), 0x6f)
    // 1985-08-01
    // G0: ESC \x28 \x6f
    // G1: ESC \x29 \x6f
    // G2: ESC \x2a \x6f
    // G3: ESC \x2b \x6f
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,   u'£', u'¤', '\\',  0,   u'§',  0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// Japanese Basic Hand-printed Graphic Set for OCR JIS C6229-1984
ISO_IR_SBCS94(94,(-1), 0x70)
    // 1985-08-01
    // G0: ESC \x28 \x70
    // G1: ESC \x29 \x70
    // G2: ESC \x2a \x70
    // G3: ESC \x2b \x70
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[', u'¥',  ']',  '^',  '_',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    '|',  0,    0    /**/
    )
// Japanese Additional Handprinted Graphic Character Set for OCR JIS C6229- 1984
ISO_IR_SBCS94(95,(-1), 0x71)
    // 1985-08-01
    // G0: ESC \x28 \x71
    // G1: ESC \x29 \x71
    // G2: ESC \x2a \x71
    // G3: ESC \x2b \x71
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,   '\\',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// Katakana hand-printed Graphic Character Set for OCR JIS C6229-1984
ISO_IR_SBCS94(96,(-1), 0x72)
    // 1985-08-01
    // G0: ESC \x28 \x72
    // G1: ESC \x29 \x72
    // G2: ESC \x2a \x72
    // G3: ESC \x2b \x72
    ISO_IR_SBCS94_DATA(
        /**/   0,   u'｢', u'｣',  0,    0,   u'ｦ',  0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'ｰ', u'ｱ', u'ｲ', u'ｳ', u'ｴ', u'ｵ', u'ｶ', u'ｷ', u'ｸ', u'ｹ', u'ｺ', u'ｻ', u'ｼ', u'ｽ', u'ｾ', u'ｿ',
        u'ﾀ', u'ﾁ', u'ﾂ', u'ﾃ', u'ﾄ', u'ﾅ', u'ﾆ', u'ﾇ', u'ﾈ', u'ﾉ', u'ﾊ', u'ﾋ', u'ﾌ', u'ﾍ', u'ﾎ', u'ﾏ',
        u'ﾐ', u'ﾑ', u'ﾒ', u'ﾓ', u'ﾔ', u'ﾕ', u'ﾖ', u'ﾗ', u'ﾘ', u'ﾙ', u'ﾚ', u'ﾛ', u'ﾜ', u'ﾝ', u'ﾞ', u'ﾟ',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// E13B Graphic Character Set Japanese National Committee for ISO/TC97/SC2
ISO_IR_SBCS94(98,(-1), 0x73)
    // 1985-08-01
    // G0: ESC \x28 \x73
    // G1: ESC \x29 \x73
    // G2: ESC \x2a \x73
    // G3: ESC \x2b \x73
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9', u'⑆', u'⑇', u'⑈', u'⑉',  0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )
// Supplementary Set of Graphic Characters for Videotex and Teletext ANSI and Teletext ANSI and CSA (Withdrawn in November 1986)
ISO_IR_SBCS94(99,(-1), 0x74)
    // 1985-08-01
    // G0: ESC \x28 \x74
    // G1: ESC \x29 \x74
    // G2: ESC \x2a \x74
    // G3: ESC \x2b \x74
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'¢', u'£',  '$', u'¥',  '#', u'§', u'¤', u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
        u'⃗',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',  u'̷',  u'̊',  u'̧',  u'̲',  u'̋',  u'̨',  u'̌',
        u'—', u'¹', u'®', u'©', u'™'  u'♪', u'─', u'│', u'╱', u'╲', SG23, SG06, u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ', u'┼', u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ'  /**/
    )
// Teletex Primary Set of Graphic Characters CCITT Rec. T.61
ISO_IR_SBCS94(102,(-1), 0x75)
    // 1985-08-01
    // G0: ESC \x28 \x75
    // G1: ESC \x29 \x75
    // G2: ESC \x2a \x75
    // G3: ESC \x2b \x75
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  '[',  0,    ']',  0,    '_',
         0,    'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  0,    '|',  0,    0    /**/
    )
// Teletex Supplementary Set of Graphic characters CCITT Rec. T.61
ISO_IR_SBCS94(103,(-1), 0x76)
    // 1985-08-01
    // G0: ESC \x28 \x76
    // G1: ESC \x29 \x76
    // G2: ESC \x2a \x76
    // G3: ESC \x2b \x76
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'¢', u'£',  '$', u'¥',  '#', u'§', u'¤',  0,    0,   u'«',  0,    0,    0,    0,
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷',  0,    0,   u'»', u'¼', u'½', u'¾', u'¿',
         0,   u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',   0,   u'̊',  u'̧',  u'̲',  u'̋',  u'̨',  u'̌',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ',  0,   u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ'  /**/
    )
// Alternate Primary Graphic Set No. 1 CSA Standard Z 243.4-1985
ISO_IR_SBCS94(121,(-1), 0x77)
    // 1986-02-01
    // G0: ESC \x28 \x77
    // G1: ESC \x29 \x77
    // G2: ESC \x2a \x77
    // G3: ESC \x2b \x77
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'à',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'â', u'ç', u'ê', u'î',  '_',
        u'ô',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'ù', u'è', u'û'  /**/
    )
// Alternate Primary Graphic Set No.2 CSA Standard Z 243.4-1985
ISO_IR_SBCS94(122,(-1), 0x78)
    // 1986-02-01
    // G0: ESC \x28 \x78
    // G1: ESC \x29 \x78
    // G2: ESC \x2a \x78
    // G3: ESC \x2b \x78
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'à',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'â', u'ç', u'ê', u'É',  '_',
        u'ô',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'ù', u'è', u'û'  /**/
    )
// Supplementary Set of graphic Characters for CCITT Rec. T.101, Data Syntax III
ISO_IR_SBCS94(128,(-1), 0x7c)
    // 1986-11-30
    // G0: ESC \x28 \x7c
    // G1: ESC \x29 \x7c
    // G2: ESC \x2a \x7c
    // G3: ESC \x2b \x7c
    ISO_IR_SBCS94_DATA(
        /**/  u'¡', u'¢', u'£',  '$', u'¥',  '#', u'§', u'¤', u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
        u'⃗',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',  u'̷',  u'̊',  u'̧',  u'̲',  u'̋',  u'̨',  u'̌',
        u'—', u'¹', u'®', u'©', u'™'  u'♪', u'─', u'│', u'╱', u'╲', SG23, SG06, u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ', u'┼', u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ'  /**/
    )
// Mosaic-1 Set of Data Syntax I of CCITT Rec. T.101
ISO_IR_SBCS94(137,(-1), 0x79)
    // 1987-07-31
    // G0: ESC \x28 \x79
    // G1: ESC \x29 \x79
    // G2: ESC \x2a \x79
    // G3: ESC \x2b \x79
    ISO_IR_SBCS94_DATA(
        /**/  MS01, MS02, MS03, MS04, MS05, MS06, MS07, MS08, MS09, MS10, MS11, MS12, MS13, MS14, MS15,
        MS16, MS17, MS18, MS19, MS20, MS21, MS22, MS23, MS24, MS25, MS26, MS27, MS28, MS29, MS30, MS31,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        SG29, SG30, SG31, SG32, SG33, SG34, SG35, SG36, SG37, SG38, SG39, SG40, SG41, SG42,  0,    0,
        SG43, SG44, SG45, SG46, SG47, SG48, SG49, SG50, SG51, SG52, SG53, SG54, SG55, SG56,  0    /**/
    )
// Serbocroatian and Slovenian Latin Alphabet
ISO_IR_SBCS94(141,(-1), 0x7a)
    // 1987-11-01
    // G0: ESC \x28 \x7a
    // G1: ESC \x29 \x7a
    // G2: ESC \x2a \x7a
    // G3: ESC \x2b \x7a
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'Ž',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'Š', u'Đ', u'Ć', u'Č',  '_',
        u'ž',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'š', u'đ', u'ć', u'č'  /**/
    )
// Serbocroatian Cyrillic Alphabet
ISO_IR_SBCS94(146,(-1), 0x7b)
    // 1988-10-01
    // G0: ESC \x28 \x7b
    // G1: ESC \x29 \x7b
    // G2: ESC \x2a \x7b
    // G3: ESC \x2b \x7b
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'Ж', u'А', u'Б', u'Ц', u'Д', u'Е', u'Ф', u'Г', u'Х', u'И', u'Ј', u'К', u'Л', u'М', u'Н', u'О',
        u'П', u'Љ', u'Р', u'С', u'Т', u'У', u'В', u'Њ', u'Џ', u'Ѕ', u'З', u'Ш', u'Ђ', u'Ћ', u'Ч',  '_',
        u'ж', u'а', u'б', u'ц', u'д', u'е', u'ф', u'г', u'х', u'и', u'ј', u'к', u'л', u'м', u'н', u'о',
        u'п', u'љ', u'р', u'с', u'т', u'у', u'в', u'њ', u'џ', u'ѕ', u'з', u'ш', u'ђ', u'ћ', u'ч'  /**/
    )
// Macedonian Cyrillic Alphabet
ISO_IR_SBCS94(147,(-1), 0x7d)
    // 1988-10-01
    // G0: ESC \x28 \x7d
    // G1: ESC \x29 \x7d
    // G2: ESC \x2a \x7d
    // G3: ESC \x2b \x7d
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'Ж', u'А', u'Б', u'Ц', u'Д', u'Е', u'Ф', u'Г', u'Х', u'И', u'Ј', u'К', u'Л', u'М', u'Н', u'О',
        u'П', u'Љ', u'Р', u'С', u'Т', u'У', u'В', u'Њ', u'Џ', u'Ѕ', u'З', u'Ш', u'Ѓ', u'Ќ', u'Ч',  '_',
        u'ж', u'а', u'б', u'ц', u'д', u'е', u'ф', u'г', u'х', u'и', u'ј', u'к', u'л', u'м', u'н', u'о',
        u'п', u'љ', u'р', u'с', u'т', u'у', u'в', u'њ', u'џ', u'ѕ', u'з', u'ш', u'ѓ', u'ќ', u'ч'  /**/
    )
// Third supplementary set of Mosaic Characters/ Videotex and Facsimile
ISO_IR_SBCS94(173,(0), 0x64)
    // 1983-10-01
    // G0: ESC \x28 \x40 ESC \x28 \x64
    // G1: ESC \x28 \x40 ESC \x29 \x64
    // G2: ESC \x28 \x40 ESC \x2a \x64
    // G3: ESC \x28 \x40 ESC \x2b \x64
    // Note: source does not mention the IRR.
        /**/  DG33, DG34, DG35, DG36, DG37, DG38, DG39, DG40, DG41, DG42, DG43, DG44, DG45,  0,   DG46,
        DG52, DG53, DG54, DG55, DG56, DG57, DG58, DG59, DG60, DG61, DG62, DG51, DG50, DG49, DG48, DG47,
        DG01, DG02, DG03, DG04, DG05, DG06, DG07, DG08, DG09, DG10, DG11, DG12, DG13, DG29, DG30, DG31,
        DG14, DG15, DG16, DG17, DG18, DG19, DG20, DG21, DG22, DG23, DG24, DG25, DG26, DG27, DG28, DG63,
        SG29, SG30, SG31, SG32, SG33, SG34, SG35, SG36, SG37, SG38, SG39, SG40, SG41, SG42, DG64, DG65,
        SG43, SG44, SG45, SG46, SG47, SG48, SG49, SG50, SG51, SG52, SG53, SG54, SG55, SG56,  0    /**/

/// 94-Character graphic character set with second Intermediate byte
// Greek Primary Set of CCITT
ISO_IR_SBCS94(150,(-1), 0x21, 0x40)
    // 1988-11-01
    // G0: ESC \x28 \x21 \x40
    // G1: ESC \x29 \x21 \x40
    // G2: ESC \x2a \x21 \x40
    // G3: ESC \x2b \x21 \x40
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@', u'Α', u'Β', u'Γ', u'Δ', u'Ε', u'Ζ', u'Η', u'Θ', u'Ι', u'Κ', u'Λ', u'Μ', u'Ν', u'Ξ', u'Ο',
        u'Π', u'Ρ',  0,   u'Σ', u'Τ', u'Υ', u'Φ', u'Χ', u'Ψ', u'Ω',  0,    '[', '\\',  ']',  '^',  '_',
         0,   u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ', u'ο',
        u'π', u'ρ', u'ς', u'σ', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω',  0,    '{',  '|',  '}', u'¯'  /**/
    )
// Character Set of Cuba
ISO_IR_SBCS94(151,(-1), 0x21, 0x41)
    // 1988-11-01
    // G0: ESC \x28 \x21 \x41
    // G1: ESC \x29 \x21 \x41
    // G2: ESC \x2a \x21 \x41
    // G3: ESC \x2b \x21 \x41
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#', u'¤',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'¡', u'Ñ',  ']', u'¿',  '_',
         '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'´', u'ñ',  '[', u'¨'  /**/
    )
// Invariant characters (82) of ISO/IEC 646
ISO_IR_SBCS94(170,(-1), 0x21, 0x42)
    // 1993-01-21
    // G0: ESC \x28 \x21 \x42
    // G1: ESC \x29 \x21 \x42
    // G2: ESC \x2a \x21 \x42
    // G3: ESC \x2b \x21 \x42
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  0,    0,    '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         0,    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  0,    0,    0,    0,    '_',
         0,    'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  0,    0,    0,    0    /**/
    )
// Variant of the ISO 7-bit coded character set for the Irish Gaelic language
ISO_IR_SBCS94(207,(-1), 0x21, 0x43)
    // 1993-01-21
    // G0: ESC \x28 \x21 \x43
    // G1: ESC \x29 \x21 \x43
    // G2: ESC \x2a \x21 \x43
    // G3: ESC \x2b \x21 \x43
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"', u'£',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
        u'Ó',  'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
         'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z', u'É', u'Í', u'Ú', u'Á',  '_',
        u'ó',  'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'p',
         'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z', u'é', u'í', u'ú', u'á'  /**/
    )
// Turkmen Alphabet
ISO_IR_SBCS94(230,(-1), 0x21, 0x44)
    // 2000-09-14
    // G0: ESC \x28 \x21 \x44
    // G1: ESC \x29 \x21 \x44
    // G2: ESC \x2a \x21 \x44
    // G3: ESC \x2b \x21 \x44
    ISO_IR_SBCS94_DATA(
        /**/   '!',  '"',  '#',  '$',  '%',  '&', '\'',  '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
         '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
         '@',  'A',  'B', u'Ç',  'D',  'E', u'Ä',  'F',  'G',  'H',  'I',  'J', u'Ž',  'K',  'L',  'M',
         'N', u'Ň',  'O', u'Ö',  'P',  'R',  'S', u'Ş',  'T',  'U', u'Ü',  'W',  'Y', u'Ý',  'Z',  '_',
        u'№',  'a',  'b', u'ç',  'd',  'e', u'ä',  'f',  'g',  'h',  'i',  'j', u'ž',  'k',  'l',  'm',
         'n', u'ň',  'o', u'ö',  'p',  'r',  's', u'ş',  't',  'u', u'ü',  'w',  'y', u'ý',  'z'  /**/
    )
// American National Standard Extended Latin Alphabet Coded Character Set for Bibliographic Use (ANSEL)
ISO_IR_SBCS94(231,(-1), 0x21, 0x45)
    // 2002-09-25
    // G0: ESC \x28 \x21 \x45
    // G1: ESC \x29 \x21 \x45
    // G2: ESC \x2a \x21 \x45
    // G3: ESC \x2b \x21 \x45
    ISO_IR_SBCS94_DATA(
        /**/  u'Ł', u'Ø', u'Đ', u'Þ', u'Æ', u'Œ', u'ʹ', u'·', u'♭', u'®', u'±', u'Ơ', u'Ư', u'ʼ',  0,
        u'ʻ', u'ł', u'ø', u'đ', u'þ', u'æ', u'œ', u'ʺ', u'ı', u'£', u'ð',  0,   u'ơ', u'ư',  0,    0,
        u'°', u'ℓ', u'℗', u'©', u'♯', u'¿', u'¡',  0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        // These two rows are *precombining*, unlike unicode, and unlike
        // most other ISO-2022 diacritics, which require an explicit BS.
        u'̉',  u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',  u'̌',  u'̊',  u'︠',  u'︡',  u'̕',  u'̋',  u'̐',
        u'̧',  u'̨',  u'̣',  u'̤',  u'̥',  u'̳',  u'̲',  u'̦',  u'̜',  u'̮',  u'︢',  u'︣',   0,    0,   u'̓'  /**/
    )
// Turkmen character set for 8-bit codes
ISO_IR_SBCS94(232,(-1), 0x21, 0x46)
    // 2003-09-10
    // G0: ESC \x28 \x21 \x46
    // G1: ESC \x29 \x21 \x46
    // G2: ESC \x2a \x21 \x46
    // G3: ESC \x2b \x21 \x46
    ISO_IR_SBCS94_DATA(
        /**/   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    'A',  'B', u'Ç',  'D',  'E', u'Ä',  'F',  'G',  'H',  'I',  'J', u'Ž',  'K',  'L',  'M',
         'N', u'Ň',  'O', u'Ö',  'P',  'R',  'S', u'Ş',  'T',  'U', u'Ü',  'W',  'Y', u'Ý',  'Z',  '_',
        u'№',  'a',  'b', u'ç',  'd',  'e', u'ä',  'f',  'g',  'h',  'i',  'j', u'ž',  'k',  'l',  'm',
         'n', u'ň',  'o', u'ö',  'p',  'r',  's', u'ş',  't',  'u', u'ü',  'w',  'y', u'ý',  'z',  0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    /**/
    )

/// 96-Character graphic character set
// Right-hand Part of Latin Alphabet No.1 ISO 8859/1, ECMA-94
ISO_IR_SBCS96(100,(-1), 0x41)
    // 1986-02-01
    // G1: ESC \x2d \x41
    // G2: ESC \x2e \x41
    // G3: ESC \x2f \x41
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'¨', u'©', u'ª', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'µ', u'¶', u'·', u'¸', u'¹', u'º', u'»', u'¼', u'½', u'¾', u'¿',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ð', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ð', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'þ', u'ÿ'
    )
// Right-hand Part of Latin Alphabet No.2 ISO 8859/2, ECMA-94
ISO_IR_SBCS96(101,(-1), 0x42)
    // 1986-02-01
    // G1: ESC \x2d \x42
    // G2: ESC \x2e \x42
    // G3: ESC \x2f \x42
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'˘', u'Ł', u'¤', u'Ľ', u'Ś', u'§', u'¨', u'Š', u'Ş', u'Ť', u'Ź', u'\u00ad', u'Ž', u'Ż',
        u'°', u'ą', u'˛', u'ł', u'´', u'ľ', u'ś', u'ˇ', u'¸', u'š', u'ş', u'ť', u'ź', u'˝', u'ž', u'ż',
        u'Ŕ', u'Á', u'Â', u'Ă', u'Ä', u'Ĺ', u'Ć', u'Ç', u'Č', u'É', u'Ę', u'Ë', u'Ě', u'Í', u'Î', u'Ď',
        u'Đ', u'Ń', u'Ň', u'Ó', u'Ô', u'Ő', u'Ö', u'×', u'Ř', u'Ů', u'Ú', u'Ű', u'Ü', u'Ý', u'Ţ', u'ß',
        u'ŕ', u'á', u'â', u'ă', u'ä', u'ĺ', u'ć', u'ç', u'č', u'é', u'ę', u'ë', u'ě', u'í', u'î', u'ď',
        u'đ', u'ń', u'ň', u'ó', u'ô', u'ő', u'ö', u'÷', u'ř', u'ů', u'ú', u'ű', u'ü', u'ý', u'ţ', u'˙'
    )
// Right-hand Part of Latin Alphabet No.3 ISO DIS 8859/3, ECMA-94
ISO_IR_SBCS96(109,(-1), 0x43)
    // 1986-02-01
    // G1: ESC \x2d \x43
    // G2: ESC \x2e \x43
    // G3: ESC \x2f \x43
    ISO_IR_SBCS96_DATA(
        u' ', u'Ħ', u'˘', u'£', u'¤',  0,   u'Ĥ', u'§', u'¨', u'İ', u'Ş', u'Ğ', u'Ĵ', u'\u00ad',  0,   u'Ż',
        u'°', u'ħ', u'²', u'³', u'´', u'µ', u'ĥ', u'·', u'¸', u'ı', u'ş', u'ğ', u'ĵ', u'½',  0,   u'ż',
        u'À', u'Á', u'Â',  0,   u'Ä', u'Ċ', u'Ĉ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
         0,   u'Ñ', u'Ò', u'Ó', u'Ô', u'Ġ', u'Ö', u'×', u'Ĝ', u'Ù', u'Ú', u'Û', u'Ü', u'Ŭ', u'Ŝ', u'ß',
        u'à', u'á', u'â',  0,   u'ä', u'ċ', u'ĉ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
         0,   u'ñ', u'ò', u'ó', u'ô', u'ġ', u'ö', u'÷', u'ĝ', u'ù', u'ú', u'û', u'ü', u'ŭ', u'ŝ', u'˙'
    )
// Right-hand Part of Latin Alphabet No.4 ISO DIS 8859/4, ECMA-94
ISO_IR_SBCS96(110,(-1), 0x44)
    // 1986-02-01
    // G1: ESC \x2d \x44
    // G2: ESC \x2e \x44
    // G3: ESC \x2f \x44
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'ĸ', u'Ŗ', u'¤', u'Ĩ', u'Ļ', u'§', u'¨', u'Š', u'Ē', u'Ģ', u'Ŧ', u'\u00ad', u'Ž', u'¯',
        u'°', u'ą', u'˛', u'ŗ', u'´', u'ĩ', u'ļ', u'ˇ', u'¸', u'š', u'ē', u'ģ', u'ŧ', u'Ŋ', u'ž', u'ŋ',
        u'Ā', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Į', u'Č', u'É', u'Ę', u'Ë', u'Ė', u'Í', u'Î', u'Ī',
        u'Đ', u'Ņ', u'Ō', u'Ķ', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ų', u'Ú', u'Û', u'Ü', u'Ũ', u'Ū', u'ß',
        u'ā', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'į', u'č', u'é', u'ę', u'ë', u'ė', u'í', u'î', u'ī',
        u'đ', u'ņ', u'ō', u'ķ', u'ô', u'õ', u'ö', u'÷', u'ø', u'ų', u'ú', u'û', u'ü', u'ũ', u'ū', u'˙'
    )
// Right-hand Part of the Latin/Cyrillic Alphabet ECMA-113 (Version of June 1986) [later versions are much different]
ISO_IR_SBCS96(111,(-1), 0x40)
    // 1986-02-01
    // G1: ESC \x2d \x40
    // G2: ESC \x2e \x40
    // G3: ESC \x2f \x40
    ISO_IR_SBCS96_DATA(
        u' ', u'ђ', u'ѓ', u'ё', u'є', u'ѕ', u'і', u'ї', u'ј', u'љ', u'њ', u'ћ', u'ќ', u'\u00ad', u'ў', u'џ',
        u'№', u'Ђ', u'Ѓ', u'Ё', u'Є', u'Ѕ', u'І', u'Ї', u'Ј', u'Љ', u'Њ', u'Ћ', u'Ќ', u'¤', u'Ў', u'Џ',
        u'ю', u'а', u'б', u'ц', u'д', u'е', u'ф', u'г', u'х', u'и', u'й', u'к', u'л', u'м', u'н', u'о',
        u'п', u'я', u'р', u'с', u'т', u'у', u'ж', u'в', u'ь', u'ы', u'з', u'ш', u'э', u'щ', u'ч', u'ъ',
        u'Ю', u'А', u'Б', u'Ц', u'Д', u'Е', u'Ф', u'Г', u'Х', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О',
        u'П', u'Я', u'Р', u'С', u'Т', u'У', u'Ж', u'В', u'Ь', u'Ы', u'З', u'Ш', u'Э', u'Щ', u'Ч', u'Ъ'
    )
// General Purpose Supplementary Graphic Set CSA Standard Z 243.4-1985
ISO_IR_SBCS96(123,(-1), 0x45)
    // 1986-02-01
    // G1: ESC \x2d \x45
    // G2: ESC \x2e \x45
    // G3: ESC \x2f \x45
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¨', u'£', u'¢', u'¥', u'±', u'´', u'⁽', u'⁾', u'½', u'⁺', u'¸', u'\u00ad', u'·', u'⁻',
        u'⁰', u'¹', u'²', u'³', u'⁴', u'⁵', u'⁶', u'⁷', u'⁸', u'⁹', u'¼', u'¾', u'≤', u'≠', u'≥', u'¿',
        u'À', u'Á', u'Â', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Í', u'Î', u'Ï', u'Ñ', u'Ó', u'Ô', u'Ù', u'Ú',
        u'Û', u'Ü', u'™', u'§', u'¶', u'μ', u'ª', u'º', u'‘', u'’', u'“', u'”', u'«', u'»', u'°', u'¦',
        u'à', u'á', u'â', u'ç', u'è', u'é', u'ê', u'ë', u'í', u'î', u'ï', u'ñ', u'ó', u'ô', u'ù', u'ú',
        u'û', u'ü', u'©', u'─', u'│', u'└', u'┘', u'┐', u'┌', u'├', u'┴', u'┤', u'┬', u'┼', u'¬', u'█'
    )
// Right-hand Part of the Latin/Greek Alphabet Standard ELOT 928, ECMA-118, ISO DIS 8859/7
ISO_IR_SBCS96(126,(-1), 0x46)
    // 1986-11-30
    // G1: ESC \x2d \x46
    // G2: ESC \x2e \x46
    // G3: ESC \x2f \x46
    ISO_IR_SBCS96_DATA(
        u' ', u'‘', u'’', u'£',  0,    0,   u'¦', u'§', u'¨', u'©',  0,   u'«', u'¬', u'\u00ad',  0,   u'―',
        u'°', u'±', u'²', u'³', u'΄', u'΅', u'Ά', u'·', u'Έ', u'Ή', u'Ί', u'»', u'Ό', u'½', u'Ύ', u'Ώ',
        u'ΐ', u'Α', u'Β', u'Γ', u'Δ', u'Ε', u'Ζ', u'Η', u'Θ', u'Ι', u'Κ', u'Λ', u'Μ', u'Ν', u'Ξ', u'Ο',
        u'Π', u'Ρ',  0,   u'Σ', u'Τ', u'Υ', u'Φ', u'Χ', u'Ψ', u'Ω', u'Ϊ', u'Ϋ', u'ά', u'έ', u'ή', u'ί',
        u'ΰ', u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ', u'ο',
        u'π', u'ρ', u'ς', u'σ', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω', u'ϊ', u'ϋ', u'ό', u'ύ', u'ώ',  0
    )
// Right-hand Part of the Latin/Arabic Alphabet ECMA-114, ISO 8859/6
ISO_IR_SBCS96(127,(-1), 0x47)
    // 1986-11-30
    // G1: ESC \x2d \x47
    // G2: ESC \x2e \x47
    // G3: ESC \x2f \x47
    ISO_IR_SBCS96_DATA(
        u' ',  0,    0,    0,   u'¤',  0,    0,    0,    0,    0,    0,    0,   u'،', u'\u00ad',  0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'؛',  0,    0,    0,   u'؟',
         0,   u'ء', u'آ', u'أ', u'ؤ', u'إ', u'ئ', u'ا', u'ب', u'ة', u'ت', u'ث', u'ج', u'ح', u'خ', u'د',
        u'ذ', u'ر', u'ز', u'س', u'ش', u'ص', u'ض', u'ط', u'ظ', u'ع', u'غ',  0,    0,    0,    0,    0,
        u'ـ', u'ف', u'ق', u'ك', u'ل', u'م', u'ن', u'ه', u'و', u'ى', u'ي', u'ً',  u'ٌ',  u'ٍ',  u'َ',  u'ُ',
        // The IR doesn't specify these last 8 as combining, but the cited standards do
        // Does that mean IR 89 should change, or not?
        u'ِ',  u'ّ',  u'ْ',   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
    )
// Supplementary Set of Mosaic Characters for CCITT Rec. 101, Data Syntax III
ISO_IR_SBCS96(129,(-1), 0x7d)
    // 1986-11-30
    // G1: ESC \x2d \x7d
    // G2: ESC \x2e \x7d
    // G3: ESC \x2f \x7d
    ISO_IR_SBCS96_DATA(
        MG00, MG01, MG02, MG03, MG04, MG05, MG06, MG07, MG08, MG09, MG10, MG11, MG12, MG13, MG14, MG15,
        MG16, MG17, MG18, MG19, MG20, MG21, MG22, MG23, MG24, MG25, MG26, MG27, MG28, MG29, MG30, MG31,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   MG63,
        MG32, MG33, MG34, MG35, MG36, MG37, MG38, MG39, MG40, MG41, MG42, MG43, MG44, MG45, MG46, MG47,
        MG48, MG49, MG50, MG51, MG52, MG53, MG54, MG55, MG56, MG57, MG58, MG59, MG60, MG61, MG62, MG64
    )
// Latin/Hebrew Alphabet Standard ECMA-121
ISO_IR_SBCS96(138,(-1), 0x48)
    // 1987-07-31
    // G1: ESC \x2d \x48
    // G2: ESC \x2e \x48
    // G3: ESC \x2f \x48
    ISO_IR_SBCS96_DATA(
        u' ',  0,   u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'¨', u'©', u'×', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'μ', u'¶', u'·', u'¸', u'¹', u'÷', u'»', u'¼', u'½', u'¾',  0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'‗',
        u'א', u'ב', u'ג', u'ד', u'ה', u'ו', u'ז', u'ח', u'ט', u'י', u'ך', u'כ', u'ל', u'ם', u'מ', u'ן',
        u'נ', u'ס', u'ע', u'ף', u'פ', u'ץ', u'צ', u'ק', u'ר', u'ש', u'ת',  0,    0,    0,    0,    0
    )
// Right-hand Part for Czechoslovak Standard CSN 369103
ISO_IR_SBCS96(139,(-1), 0x49)
    // 1987-07-31
    // G1: ESC \x2d \x49
    // G2: ESC \x2e \x49
    // G3: ESC \x2f \x49
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'˘', u'Ł',  '$', u'Ľ', u'Ś', u'§', u'¨', u'Š', u'Ş', u'Ť', u'Ź', u'\u00ad', u'Ž', u'Ż',
        u'°', u'ą', u'˛', u'ł', u'´', u'ľ', u'ś', u'ˇ', u'¸', u'š', u'ş', u'ť', u'ź', u'˝', u'ž', u'ż',
        u'Ŕ', u'Á', u'Â', u'Ă', u'Ä', u'Ĺ', u'Ć', u'Ç', u'Č', u'É', u'Ę', u'Ë', u'Ě', u'Í', u'Î', u'Ď',
        u'Đ', u'Ń', u'Ň', u'Ó', u'Ô', u'Ő', u'Ö', u'×', u'Ř', u'Ů', u'Ú', u'Ű', u'Ü', u'Ý', u'Ţ', u'ß',
        u'ŕ', u'á', u'â', u'ă', u'ä', u'ĺ', u'ć', u'ç', u'č', u'é', u'ę', u'ë', u'ě', u'í', u'î', u'ď',
        u'đ', u'ń', u'ň', u'ó', u'ô', u'ő', u'ö', u'÷', u'ř', u'ů', u'ú', u'ű', u'ü', u'ý', u'ţ', u'˙'
    )
// Supplementary Set of Latin Alphabetic and non-Alphabetic Graphic Characters
ISO_IR_SBCS96(142,(-1), 0x4a)
    // 1988-05-01
    // G1: ESC \x2d \x4a
    // G2: ESC \x2e \x4a
    // G3: ESC \x2f \x4a
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£',  '$', u'¥',  0,   u'§',  0,   u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
        // Unlike unicode, this row is *precombining*.
         0,   u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',   0,   u'̊',  u'̧',  u'̲',  u'̋',  u'̨',  u'̌',
        u'—', u'¹', u'®', u'©', u'™'  u'♪', u'¬', u'¦',  0,    0,    0,    0,   u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ',  0,   u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ', u'\u00ad'
    )
// Technical Set
ISO_IR_SBCS96(143,(-1), 0x4b)
    // 1988-05-01
    // G1: ESC \x2d \x4b
    // G2: ESC \x2e \x4b
    // G3: ESC \x2f \x4b
    ISO_IR_SBCS96_DATA(
        u'ˇ', u'≡', u'∧', u'∨', u'∩', u'∪', u'⊂', u'⊃', u'⇐', u'⇒', u'∴', u'∵', u'∈', u'∋', u'⊆', u'⊇',
        u'∫', u'∮', u'∞', u'∇', u'∂', u'∼', u'≈', u'≃', u'≅', u'≤', u'≠', u'≥', u'↔', u'¬', u'∀', u'∃',
        u'א', u'□', u'∥', u'Γ', u'Δ', u'⊥', u'∠', u'∟', u'Θ', u'〈',u'〉',u'Λ', u'′', u'″', u'Ξ', u'∓',
        u'Π', u'²', u'Σ', u'×', u'³', u'Υ', u'Φ', u'·', u'Ψ', u'Ω', u'∅', u'⇀', u'√', u'ƒ', u'∝', u'±',
        u'°', u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ', u'‰',
        u'π', u'ρ', u'σ', u'÷', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω', u'†', u'←', u'↑', u'→', u'↓', u'‾'
    )
// Cyrillic part of the Latin/Cyrillic Alphabet
ISO_IR_SBCS96(144,(-1), 0x4c)
    // 1988-05-01
    // G1: ESC \x2d \x4c
    // G2: ESC \x2e \x4c
    // G3: ESC \x2f \x4c
    ISO_IR_SBCS96_DATA(
        u' ', u'Ё', u'Ђ', u'Ѓ', u'Є', u'Ѕ', u'І', u'Ї', u'Ј', u'Љ', u'Њ', u'Ћ', u'Ќ', u'\u00ad', u'Ў', u'Џ',
        u'А', u'Б', u'В', u'Г', u'Д', u'Е', u'Ж', u'З', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О', u'П',
        u'Р', u'С', u'Т', u'У', u'Ф', u'Х', u'Ц', u'Ч', u'Ш', u'Щ', u'Ъ', u'Ы', u'Ь', u'Э', u'Ю', u'Я',
        u'а', u'б', u'в', u'г', u'д', u'е', u'ж', u'з', u'и', u'й', u'к', u'л', u'м', u'н', u'о', u'п',
        u'р', u'с', u'т', u'у', u'ф', u'х', u'ц', u'ч', u'ш', u'щ', u'ъ', u'ы', u'ь', u'э', u'ю', u'я',
        u'№', u'ё', u'ђ', u'ѓ', u'є', u'ѕ', u'і', u'ї', u'ј', u'љ', u'њ', u'ћ', u'ќ', u'§', u'ў', u'џ'
    )
// Right-hand part of Latin Alphabet No.5
ISO_IR_SBCS96(148,(-1), 0x4d)
    // 1988-10-01
    // G1: ESC \x2d \x4d
    // G2: ESC \x2e \x4d
    // G3: ESC \x2f \x4d
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'¨', u'©', u'ª', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'µ', u'¶', u'·', u'¸', u'¹', u'º', u'»', u'¼', u'½', u'¾', u'¿',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ğ', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'İ', u'Ş', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ğ', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ı', u'ş', u'ÿ'
    )
// Residual Characters from ISO 6937-2 : 1983
ISO_IR_SBCS96(152,(-1), 0x4e)
    // 1989-07-01
    // G1: ESC \x2d \x4e
    // G2: ESC \x2e \x4e
    // G3: ESC \x2f \x4e
    ISO_IR_SBCS96_DATA(
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'“',  0,   u'←', u'↑', u'→', u'↓',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'”',  0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,   u'™', u'♪',  0,    0,    0,    0,    0,    0,   u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω',  0,    0,    0,    0,    0,   u'Ĳ', u'Ŀ',  0,    0,   u'Œ',  0,   u'Ŵ', u'Ŷ', u'Ÿ', u'ŉ',
         0,    0,    0,    0,    0,    0,   u'ĳ', u'ŀ',  0,    0,   u'œ',  0,   u'ŵ', u'ŷ',  0,    0
    )
// Basic Cyrillic Character Set for 8-bit Codes
ISO_IR_SBCS96(153,(-1), 0x4f)
    // 1989-12-01
    // G1: ESC \x2d \x4f
    // G2: ESC \x2e \x4f
    // G3: ESC \x2f \x4f
    ISO_IR_SBCS96_DATA(
        u' ', u'Ё',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'\u00ad',  0,    0,
        u'А', u'Б', u'В', u'Г', u'Д', u'Е', u'Ж', u'З', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О', u'П',
        u'Р', u'С', u'Т', u'У', u'Ф', u'Х', u'Ц', u'Ч', u'Ш', u'Щ', u'Ъ', u'Ы', u'Ь', u'Э', u'Ю', u'Я',
        u'а', u'б', u'в', u'г', u'д', u'е', u'ж', u'з', u'и', u'й', u'к', u'л', u'м', u'н', u'о', u'п',
        u'р', u'с', u'т', u'у', u'ф', u'х', u'ц', u'ч', u'ш', u'щ', u'ъ', u'ы', u'ь', u'э', u'ю', u'я',
         0,   u'ё',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
    )
// Supplementary set for Latin Alphabets No.1, No.2 and No.5
ISO_IR_SBCS96(154,(-1), 0x50)
    // 1990-03-01
    // G1: ESC \x2d \x50
    // G2: ESC \x2e \x50
    // G3: ESC \x2f \x50
    ISO_IR_SBCS96_DATA(
         0,    0,   u'Ā', u'Ĉ', u'Ċ',  0,   u'Ė', u'Ē', u'Ĝ', u'‘', u'“', u'™', u'←', u'↑', u'→', u'↓',
         0,    0,   u'ā', u'ĉ', u'ċ', u'ð', u'ė', u'ē', u'ĝ', u'’', u'”', u'♪', u'⅛', u'⅜', u'⅝', u'⅞',
         0,   u'Ğ', u'Ġ', u'Ģ', u'Ĥ', u'Ħ', u'Ĩ', u'İ', u'Ī', u'Į', u'Ĳ', u'Ĵ', u'Ķ', u'Ļ', u'Ŀ', u'Ņ',
        u'—', u'Ŋ', u'Ō', u'Œ', u'Ŗ', u'Ŝ', u'Ŧ', u'Þ', u'Ũ', u'Ŭ', u'Ū', u'Ų', u'Ŵ', u'Ý', u'Ŷ', u'Ÿ',
        u'Ω', u'ğ', u'ġ', u'ģ', u'ĥ', u'ħ', u'ĩ', u'ı', u'ī', u'į', u'ĳ', u'ĵ', u'ķ', u'ļ', u'ŀ', u'ņ',
        u'ĸ', u'ŋ', u'ō', u'œ', u'ŗ', u'ŝ', u'ŧ', u'þ', u'ũ', u'ŭ', u'ū', u'ų', u'ŵ', u'ý', u'ŷ', u'ŉ'
    )
// Basic Box Drawings Set
ISO_IR_SBCS96(155,(-1), 0x51)
    // 1990-04-16
    // G1: ESC \x2d \x51
    // G2: ESC \x2e \x51
    // G3: ESC \x2f \x51
    ISO_IR_SBCS96_DATA(
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'┃', u'━', u'┏', u'┓', u'┗', u'┛', u'┣', u'┫', u'┳', u'┻', u'╋', u'▀', u'▄', u'█', u'▪',  0,
        u'│', u'─', u'┌', u'┐', u'└', u'┘', u'├', u'┤', u'┬', u'┴', u'┼', u'░', u'▒', u'▓',  0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
    )
// Supplementary Set ISO/IEC 6937 : 1992
ISO_IR_SBCS96(156,(-1), 0x52)
    // 1991-12-15
    // G1: ESC \x2d \x52
    // G2: ESC \x2e \x52
    // G3: ESC \x2f \x52
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£',  0,   u'¥',  0,   u'§', u'¤', u'‘', u'“', u'«', u'←', u'↑', u'→', u'↓',
        u'°', u'±', u'²', u'³', u'×', u'μ', u'¶', u'·', u'÷', u'’', u'”', u'»', u'¼', u'½', u'¾', u'¿',
        // Unlike unicode, this row is *precombining*.
         0,   u'̀',  u'́',  u'̂',  u'̃',  u'̄',  u'̆',  u'̇',  u'̈',   0,   u'̊',  u'̧',   0,   u'̋',  u'̨',  u'̌',
        u'—', u'¹', u'®', u'©', u'™'  u'♪', u'¬', u'¦',  0,    0,    0,    0,   u'⅛', u'⅜', u'⅝', u'⅞',
        u'Ω', u'Æ', u'Đ', u'ª', u'Ħ',  0,   u'Ĳ', u'Ŀ', u'Ł', u'Ø', u'Œ', u'º', u'Þ', u'Ŧ', u'Ŋ', u'ŉ',
        u'ĸ', u'æ', u'đ', u'ð', u'ħ', u'ı', u'ĳ', u'ŀ', u'ł', u'ø', u'œ', u'ß', u'þ', u'ŧ', u'ŋ', u'\u00ad'
    )
// Supplementary Set for Latin Alphabet No. 6
ISO_IR_SBCS96(157,(-1), 0x56)
    // 1992-09-07
    // G1: ESC \x2d \x56
    // G2: ESC \x2e \x56
    // G3: ESC \x2f \x56
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'Ē', u'Ģ', u'Ī', u'Ĩ', u'Ķ', u'§', u'Ļ', u'Đ', u'Š', u'Ŧ', u'Ž', u'\u00ad', u'Ū', u'Ŋ',
        u'°', u'ą', u'ē', u'ģ', u'ī', u'ĩ', u'ķ', u'·', u'ļ', u'đ', u'š', u'ŧ', u'ž', u'―', u'ū', u'ŋ',
        u'Ā', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Į', u'Č', u'É', u'Ę', u'Ë', u'Ė', u'Í', u'Î', u'Ï',
        u'Ð', u'Ņ', u'Ō', u'Ó', u'Ô', u'Õ', u'Ö', u'Ũ', u'Ø', u'Ų', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'ā', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'į', u'č', u'é', u'ę', u'ë', u'ė', u'í', u'î', u'ï',
        u'ð', u'ņ', u'ō', u'ó', u'ô', u'õ', u'ö', u'ũ', u'ø', u'ų', u'ú', u'û', u'ü', u'ý', u'þ', u'ĸ'
    )
// Sami (Lappish) Supplementary Set
ISO_IR_SBCS96(158,(-1), 0x58)
    // 1992-09-07
    // G1: ESC \x2d \x58
    // G2: ESC \x2e \x58
    // G3: ESC \x2f \x58
    ISO_IR_SBCS96_DATA(
        u'´',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        // Note: 3/0 is misnamed in the IR and in several standards.
        u'ʽ',  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'Ă', u'À', u'Ǟ', u'Ǡ', u'Ǣ', u'Ĕ', u'È', u'Ǥ', u'Ǧ', u'Ǩ', u'Ŏ', u'Ò', u'Ǫ', u'Ǭ', u'Ʒ', u'Ǯ',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'ă', u'à', u'ǟ', u'ǡ', u'ǣ', u'ĕ', u'è', u'ǥ', u'ǧ', u'ǩ', u'ŏ', u'ò', u'ǫ', u'ǭ', u'ʒ', u'ǯ',
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
    )
// CCITT Hebrew Supplementary Set
ISO_IR_SBCS96(164,(-1), 0x53)
    // 1992-09-07
    // G1: ESC \x2d \x53
    // G2: ESC \x2e \x53
    // G3: ESC \x2f \x53
    ISO_IR_SBCS96_DATA(
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u'א', u'ב', u'ג', u'ד', u'ה', u'ו', u'ז', u'ח', u'ט', u'י', u'ך', u'כ', u'ל', u'ם', u'מ', u'ן',
        u'נ', u'ס', u'ע', u'ף', u'פ', u'ץ', u'צ', u'ק', u'ר', u'ש', u'ת',  0,    0,    0,    0,    0,
    )
// Thai Set
ISO_IR_SBCS96(166,(-1), 0x54)
    // 1992-07-13
    // G1: ESC \x2d \x54
    // G2: ESC \x2e \x54
    // G3: ESC \x2f \x54
    ISO_IR_SBCS96_DATA(
        u' ', u'ก', u'ข', u'ฃ', u'ค', u'ฅ', u'ฆ', u'ง', u'จ', u'ฉ', u'ช', u'ซ', u'ฌ', u'ญ', u'ฎ', u'ฏ',
        u'ฐ', u'ฑ', u'ฒ', u'ณ', u'ด', u'ต', u'ถ', u'ท', u'ธ', u'น', u'บ', u'ป', u'ผ', u'ฝ', u'พ', u'ฟ',
        u'ภ', u'ม', u'ย', u'ร', u'ฤ', u'ล', u'ฦ', u'ว', u'ศ', u'ษ', u'ส', u'ห', u'ฬ', u'อ', u'ฮ', u'ฯ',
        // Note: special combining/ordering rules. Vowels are precombining,
        // despite the fact that they are pronounced afterward.
        u'ะ', u'ั',  u'า', u'ำ', u'ิ',  u'ี',  u'ึ',  u'ื',  u'ุ',  u'ู',  u'ฺ',   0,    0,    0,    0,   u'฿',
        u'เ', u'แ', u'โ', u'ใ', u'ไ', u'ๅ', u'ๆ', u'็',  u'่',  u'้',  u'๊',  u'๋',  u'์',  u'ํ',  u'๎',  u'๏',
        u'๐', u'๑', u'๒', u'๓', u'๔', u'๕', u'๖', u'๗', u'๘', u'๙', u'๚', u'๛',  0,    0,    0,    0
    )
// Arabic/French/German Set
ISO_IR_SBCS96(167,(-1), 0x55)
    // 1992-07-13
    // G1: ESC \x2d \x54
    // G2: ESC \x2e \x54
    // G3: ESC \x2f \x54
    ISO_IR_SBCS96_DATA(
        // Note: it is unclear whether positions 6/11 to 7/2 should be
        // combining or not.
        // Note: acute or grave on the U/u? Source is schizophrenic.
        u' ',  0,    0,    0,   u'¤',  0,    0,    0,   u'È', u'É', u'Ê', u'Ë', u'،', u'\u00ad', u'Î', u'Ï',
        u'À', u'Â', u'â', u'Ä', u'ß', u'ä', u'Ç', u'ç', u'è', u'é', u'ê', u'؛', u'ë', u'î', u'ï', u'؟',
        u'à', u'ء', u'آ', u'أ', u'ؤ', u'إ', u'ئ', u'ا', u'ب', u'ة', u'ت', u'ث', u'ج', u'ح', u'خ', u'د',
        u'ذ', u'ر', u'ز', u'س', u'ش', u'ص', u'ض', u'ط', u'ظ', u'ع', u'غ', u'Ô', u'Ö', u'Ù', u'Û', u'Ü',
        u'ـ', u'ف', u'ق', u'ك', u'ل', u'م', u'ن', u'ه', u'و', u'ى', u'ي', u'ﹰ', u'ﹲ', u'ﹴ', u'ﹶ', u'ﹸ',
        u'ﹺ', u'ﹼ', u'ﹾ',  0,    0,    0,    0,    0,    0,    0,    0,   u'ô', u'ö', u'ù', u'û', u'ü'
    )
// Baltic Rim Supplementary Set
ISO_IR_SBCS96(179,(-1), 0x59)
    // 1993-04-01
    // G1: ESC \x2d \x59
    // G2: ESC \x2e \x59
    // G3: ESC \x2f \x59
    ISO_IR_SBCS96_DATA(
        u' ', u'”', u'¢', u'£', u'¤', u'„', u'¦', u'§', u'Ø', u'©', u'Ŗ', u'«', u'¬', u'\u00ad', u'®', u'Æ',
        u'°', u'±', u'²', u'³', u'“', u'μ', u'¶', u'·', u'ø', u'¹', u'ŗ', u'»', u'¼', u'½', u'¾', u'æ',
        u'Ą', u'Į', u'Ā', u'Ć', u'Ä', u'Å', u'Ę', u'Ē', u'Č', u'É', u'Ź', u'Ė', u'Ģ', u'Ķ', u'Ī', u'Ļ',
        u'Ŝ', u'Ń', u'Ņ', u'Ó', u'Ō', u'Õ', u'Ö', u'×', u'Ų', u'Ł', u'Ś', u'Ū', u'Ü', u'Ż', u'Ž', u'ß',
        u'ą', u'į', u'ā', u'ć', u'ä', u'å', u'ę', u'ē', u'č', u'é', u'ź', u'ė', u'ģ', u'ķ', u'ī', u'ļ',
        u'ŝ', u'ń', u'ņ', u'ó', u'ō', u'õ', u'ö', u'÷', u'ų', u'ł', u'ś', u'ū', u'ü', u'ż', u'ž', u'’',
    )
// Vietnamese Standard Code for Information Interchange
ISO_IR_SBCS96(180,(-1), 0x5a)
    // 1993-11-01
    // G1: ESC \x2d \x5a
    // G2: ESC \x2e \x5a
    // G3: ESC \x2f \x5a
    // Note: lacks proper footnotes.
    ISO_IR_SBCS96_DATA(
        u' ', u'Ă', u'Â', u'Ê', u'Ô', u'Ơ', u'Ư', u'Đ', u'ă', u'â', u'ê', u'ô', u'ơ', u'ư', u'đ', u'Ằ',
        u'̀',  u'̉',  u'̃',  u'́',  u'̣',  u'à', u'ả', u'ã', u'á', u'ạ', u'Ẳ', u'ằ', u'ẳ', u'ẵ', u'ắ', u'Ẵ',
        u'Ắ', u'Ầ', u'Ẩ', u'Ẫ', u'Ấ', u'Ề', u'ặ', u'ầ', u'ẩ', u'ẫ', u'ấ', u'ậ', u'è', u'Ể', u'ẻ', u'ẽ',
        u'é', u'ẹ', u'ề', u'ể', u'ễ', u'ế', u'ệ', u'ì', u'ỉ', u'Ễ', u'Ế', u'Ồ', u'ĩ', u'í', u'ị', u'ò',
        u'Ổ', u'ỏ', u'õ', u'ó', u'ọ', u'ồ', u'ổ', u'ỗ', u'ố', u'ộ', u'ờ', u'ở', u'ỡ', u'ớ', u'ợ', u'ù',
        u'Ỗ', u'ủ', u'ũ', u'ú', u'ụ', u'ừ', u'ử', u'ữ', u'ứ', u'ự', u'ỳ', u'ỷ', u'ỹ', u'ý', u'ỵ', u'Ố'
    )
// Technical Character Set No.1: IEC Publication 1289
ISO_IR_SBCS96(181,(-1), 0x5b)
    // 1994-03-16
    // G1: ESC \x2d \x5b
    // G2: ESC \x2e \x5b
    // G3: ESC \x2f \x5b
    ISO_IR_SBCS96_DATA(
        u' ', u'┐', u'⎍', u'⎎', u'◇', u'⎏', u'⎐', u'⎑', u'⎒', u'©', u'≤', u'≪', u'¬', u'\u00ad', u'®', 0,
        u'°', u'±', u'÷', u'∞', u'∫', u'…', u'≠', u'·', u'≅', u'≡', u'≥', u'≫', u'™', u'℄', u'―', u'⎓',
        u'‰', u'←',  0,   u'Γ', u'Δ', u'◁', u'▽', u'▷', u'Θ', u'⋂', u'⎔', u'Λ',  0,    0,   u'Ξ',  0,
        u'Π', u'→',  0,   u'Σ',  0,   u'Υ', u'Φ', u'×', u'Ψ', u'Ω', u'□', u'⌀', u'∠', u'∼', u'≈', u'≋',
         0,   u'α', u'β', u'γ', u'δ', u'ϵ', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ',  0,
        u'π', u'ρ',  0,   u'σ', u'τ', u'υ', u'ϕ', u'χ', u'ψ', u'ω', u'ϑ', u'φ', u'ε',  0,    0,    0
    )
// Welsh variant of Latin Alphabet No. 1
ISO_IR_SBCS96(182,(-1), 0x5c)
    // 1994-03-16
    // G1: ESC \x2d \x5c
    // G2: ESC \x2e \x5c
    // G3: ESC \x2f \x5c
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'Ẁ', u'©', u'Ẃ', u'«', u'Ỳ', u'\u00ad', u'®', u'Ÿ',
        u'°', u'±', u'²', u'³', u'´', u'µ', u'¶', u'·', u'ẁ', u'¹', u'ẃ', u'»', u'ỳ', u'Ẅ', u'ẅ', u'¿',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ŵ', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Ŷ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ŵ', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'ŷ', u'ÿ'
    )
// Sami supplementary Latin set
ISO_IR_SBCS96(197,(-1), 0x5d)
    // 1997-01-24
    // G1: ESC \x2d \x5d
    // G2: ESC \x2e \x5d
    // G3: ESC \x2f \x5d
    ISO_IR_SBCS96_DATA(
        u' ', u'Č', u'č', u'Đ', u'đ', u'Ǥ', u'ǥ', u'§', u'Ǧ', u'©', u'ǧ', u'«', u'Ǩ', u'\u00ad', u'ǩ', u'Ŋ',
        u'°', u'ŋ', u'Š', u'š', u'´', u'Ŧ', u'¶', u'·', u'ŧ', u'Ž', u'ž', u'»', u'Ʒ', u'ʒ', u'Ǯ', u'ǯ',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ð', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ð', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'þ', u'ÿ'
    )
// Latin/Hebrew Alphabet
ISO_IR_SBCS96(198,(-1), 0x5e)
    // 1998-05-01
    // G1: ESC \x2d \x5e
    // G2: ESC \x2e \x5e
    // G3: ESC \x2f \x5e
    ISO_IR_SBCS96_DATA(
        u' ',  0,   u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'¨', u'©', u'×', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'μ', u'¶', u'·', u'¸', u'¹', u'÷', u'»', u'¼', u'½', u'¾',  0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   u'‗',
        u'א', u'ב', u'ג', u'ד', u'ה', u'ו', u'ז', u'ח', u'ט', u'י', u'ך', u'כ', u'ל', u'ם', u'מ', u'ן',
        u'נ', u'ס', u'ע', u'ף', u'פ', u'ץ', u'צ', u'ק', u'ר', u'ש', u'ת',  0,    0,   u'\u200e', u'\u200f',  0
    )
// Celtic Supplementary Latin Set
ISO_IR_SBCS96(199,(-1), 0x5f)
    // 1998-05-01
    // G1: ESC \x2d \x5f
    // G2: ESC \x2e \x5f
    // G3: ESC \x2f \x5f
    ISO_IR_SBCS96_DATA(
        u' ', u'Ḃ', u'ḃ', u'£', u'Ċ', u'ċ', u'Ḋ', u'§', u'Ẁ', u'©', u'Ẃ', u'ḋ', u'Ỳ', u'\u00ad', u'®', u'Ÿ',
        u'Ḟ', u'ḟ', u'Ġ', u'ġ', u'Ṁ', u'ṁ', u'¶', u'Ṗ', u'ẁ', u'ṗ', u'ẃ', u'Ṡ', u'ỳ', u'Ẅ', u'ẅ', u'ṡ',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ŵ', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'Ṫ', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Ŷ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ŵ', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'ṫ', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'ŷ', u'ÿ'
    )
// Uralic Supplementary Cyrllic Set
ISO_IR_SBCS96(200,(-1), 0x60)
    // 1998-05-01
    // G1: ESC \x2d \x60
    // G2: ESC \x2e \x60
    // G3: ESC \x2f \x60
    ISO_IR_SBCS96_DATA(
        u' ', u'Ё', u'Ӈ', u'Ӓ', u'Ӭ', u'Ѣ', u'І', u'Ӧ', u'Ҋ', u'Ӆ', u'Ң', u'«', u'Ӎ', u'\u00ad', u'Ҏ', u'ʼ',
        u'А', u'Б', u'В', u'Г', u'Д', u'Е', u'Ж', u'З', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О', u'П',
        u'Р', u'С', u'Т', u'У', u'Ф', u'Х', u'Ц', u'Ч', u'Ш', u'Щ', u'Ъ', u'Ы', u'Ь', u'Э', u'Ю', u'Я',
        u'а', u'б', u'в', u'г', u'д', u'е', u'ж', u'з', u'и', u'й', u'к', u'л', u'м', u'н', u'о', u'п',
        u'р', u'с', u'т', u'у', u'ф', u'х', u'ц', u'ч', u'ш', u'щ', u'ъ', u'ы', u'ь', u'э', u'ю', u'я',
        u'№', u'ё', u'ӈ', u'ӓ', u'ӭ', u'ѣ', u'і', u'ӧ', u'ҋ', u'ӆ', u'ң', u'»', u'ӎ', u'§', u'ҏ', u'”'
    )
// Volgaic Supplementary Cyrllic Set
ISO_IR_SBCS96(201,(-1), 0x61)
    // 1998-05-01
    // G1: ESC \x2d \x60
    // G2: ESC \x2e \x60
    // G3: ESC \x2f \x60
    ISO_IR_SBCS96_DATA(
        u' ', u'Ё', u'Ӑ', u'Ӓ', u'Ӗ', u'Ҫ', u'І', u'Ӧ', u'Ӥ', u'Ӝ', u'Ҥ', u'Ӹ', u'Ӟ', u'\u00ad', u'Ӱ', u'Ӵ',
        u'А', u'Б', u'В', u'Г', u'Д', u'Е', u'Ж', u'З', u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О', u'П',
        u'Р', u'С', u'Т', u'У', u'Ф', u'Х', u'Ц', u'Ч', u'Ш', u'Щ', u'Ъ', u'Ы', u'Ь', u'Э', u'Ю', u'Я',
        u'а', u'б', u'в', u'г', u'д', u'е', u'ж', u'з', u'и', u'й', u'к', u'л', u'м', u'н', u'о', u'п',
        u'р', u'с', u'т', u'у', u'ф', u'х', u'ц', u'ч', u'ш', u'щ', u'ъ', u'ы', u'ь', u'э', u'ю', u'я',
        u'№', u'ё', u'ӑ', u'ӓ', u'ӗ', u'ҫ', u'і', u'ӧ', u'ӥ', u'ӝ', u'ҥ', u'ӹ', u'ӟ', u'§', u'ӱ', u'ӵ'
    )
// European Supplementary Latin Set ("Latin 9")
ISO_IR_SBCS96(203,(-1), 0x62)
    // 1998-09-16
    // G1: ESC \x2d \x62
    // G2: ESC \x2e \x62
    // G3: ESC \x2f \x62
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£', u'€', u'¥', u'Š', u'§', u'š', u'©', u'ª', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'Ž', u'µ', u'¶', u'·', u'ž', u'¹', u'º', u'»', u'Œ', u'œ', u'Ÿ', u'¿',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ð', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ð', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'þ', u'ÿ',
    )
// Supplementary set for Latin-1 alternative with EURO SIGN
ISO_IR_SBCS96(204,(-1), 0x63)
    // 1998-09-16
    // G1: ESC \x2d \x63
    // G2: ESC \x2e \x63
    // G3: ESC \x2f \x63
    ISO_IR_SBCS96_DATA(
        u' ', u'¡', u'¢', u'£', u'€', u'¥', u'¦', u'§', u'¨', u'©', u'ª', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'µ', u'¶', u'·', u'¸', u'¹', u'º', u'»', u'¼', u'½', u'¾', u'¿',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ð', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ð', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'þ', u'ÿ'
    )
// Supplementary set for Latin-4 alternative with EURO SIGN
ISO_IR_SBCS96(205,(-1), 0x64)
    // 1998-09-16
    // G1: ESC \x2d \x64
    // G2: ESC \x2e \x64
    // G3: ESC \x2f \x64
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'ĸ', u'Ŗ', u'€', u'Ĩ', u'Ļ', u'§', u'¨', u'Š', u'Ē', u'Ģ', u'Ŧ', u'\u00ad', u'Ž', u'¯',
        u'°', u'ą', u'˛', u'ŗ', u'´', u'ĩ', u'ļ', u'ˇ', u'¸', u'š', u'ē', u'ģ', u'ŧ', u'Ŋ', u'ž', u'ŋ',
        u'Ā', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Į', u'Č', u'É', u'Ę', u'Ë', u'Ė', u'Í', u'Î', u'Ī',
        u'Đ', u'Ņ', u'Ō', u'Ķ', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ų', u'Ú', u'Û', u'Ü', u'Ũ', u'Ū', u'ß',
        u'ā', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'į', u'č', u'é', u'ę', u'ë', u'ė', u'í', u'î', u'ī',
        u'đ', u'ņ', u'ō', u'ķ', u'ô', u'õ', u'ö', u'÷', u'ø', u'ų', u'ú', u'û', u'ü', u'ũ', u'ū', u'˙'
    )
// Supplementary set for Latin-7 alternative with EURO SIGN
ISO_IR_SBCS96(206,(-1), 0x65)
    // 1998-09-16
    // G1: ESC \x2d \x65
    // G2: ESC \x2e \x65
    // G3: ESC \x2f \x65
    ISO_IR_SBCS96_DATA(
        u' ', u'”', u'¢', u'£', u'€', u'„', u'¦', u'§', u'Ø', u'©', u'Ŗ', u'«', u'¬', u'\u00ad', u'®', u'Æ',
        u'°', u'±', u'²', u'³', u'“', u'μ', u'¶', u'·', u'ø', u'¹', u'ŗ', u'»', u'¼', u'½', u'¾', u'æ',
        u'Ą', u'Į', u'Ā', u'Ć', u'Ä', u'Å', u'Ę', u'Ē', u'Č', u'É', u'Ź', u'Ė', u'Ģ', u'Ķ', u'Ī', u'Ļ',
        u'Ŝ', u'Ń', u'Ņ', u'Ó', u'Ō', u'Õ', u'Ö', u'×', u'Ų', u'Ł', u'Ś', u'Ū', u'Ü', u'Ż', u'Ž', u'ß',
        u'ą', u'į', u'ā', u'ć', u'ä', u'å', u'ę', u'ē', u'č', u'é', u'ź', u'ė', u'ģ', u'ķ', u'ī', u'ļ',
        u'ŝ', u'ń', u'ņ', u'ó', u'ō', u'õ', u'ö', u'÷', u'ų', u'ł', u'ś', u'ū', u'ü', u'ż', u'ž', u'’',
    )
// Romanian Character Set for Information Interchange
ISO_IR_SBCS96(226,(-1), 0x66)
    // 1999-08-30
    // G1: ESC \x2d \x66
    // G2: ESC \x2e \x66
    // G3: ESC \x2f \x66
    ISO_IR_SBCS96_DATA(
        u' ', u'Ą', u'ą', u'Ł', u'€', u'„', u'Š', u'§', u'š', u'©', u'Ș', u'«', u'Ź', u'\u00ad', u'ź', u'Ż',
        u'°', u'±', u'Č', u'ł', u'Ž', u'”', u'¶', u'·', u'ž', u'č', u'ș', u'»', u'Œ', u'œ', u'Ÿ', u'ż',
        u'À', u'Á', u'Â', u'Ă', u'Ä', u'Ć', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Đ', u'Ń', u'Ò', u'Ó', u'Ô', u'Ő', u'Ö', u'Ś', u'Ű', u'Ù', u'Ú', u'Û', u'Ü', u'Ę', u'Ț', u'ß',
        u'à', u'á', u'â', u'ă', u'ä', u'ć', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'đ', u'ń', u'ò', u'ó', u'ô', u'ő', u'ö', u'ś', u'ű', u'ù', u'ú', u'û', u'ü', u'ę', u'ț', u'ÿ',
    )
// Ogham coded character set for information interchange
ISO_IR_SBCS96(208,(-1), 0x67)
    // 1999-12-07
    // G1: ESC \x2d \x67
    // G2: ESC \x2e \x67
    // G3: ESC \x2f \x67
    ISO_IR_SBCS96_DATA(
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        u' ', u'ᚁ', u'ᚂ', u'ᚃ', u'ᚄ', u'ᚅ', u'ᚆ', u'ᚇ', u'ᚈ', u'ᚉ', u'ᚊ', u'ᚋ', u'ᚌ', u'ᚍ', u'ᚎ', u'ᚏ',
        u'ᚐ', u'ᚑ', u'ᚒ', u'ᚓ', u'ᚔ', u'ᚕ', u'ᚖ', u'ᚗ', u'ᚘ', u'ᚙ', u'ᚚ', u'᚛', u'᚜',  0,    0,    0
    )
// Sami supplementary Latin set no 2
ISO_IR_SBCS96(209,(-1), 0x68)
    // 1999-12-07
    // G1: ESC \x2d \x68
    // G2: ESC \x2e \x68
    // G3: ESC \x2f \x68
    ISO_IR_SBCS96_DATA(
        u' ', u'Č', u'č', u'Đ', u'đ', u'Ǥ', u'ǥ', u'§', u'Ǧ', u'©', u'ǧ', u'Ĥ', u'Ǩ', u'\u00ad', u'ǩ', u'Ŋ',
        u'°', u'ŋ', u'Š', u'š', u'´', u'Ŧ', u'¶', u'·', u'ŧ', u'Ž', u'ž', u'ĥ', u'Ʒ', u'ʒ', u'Ǯ', u'ǯ',
        u'À', u'Á', u'Â', u'Ã', u'Ä', u'Å', u'Æ', u'Ç', u'È', u'É', u'Ê', u'Ë', u'Ì', u'Í', u'Î', u'Ï',
        u'Ð', u'Ñ', u'Ò', u'Ó', u'Ô', u'Õ', u'Ö', u'×', u'Ø', u'Ù', u'Ú', u'Û', u'Ü', u'Ý', u'Þ', u'ß',
        u'à', u'á', u'â', u'ã', u'ä', u'å', u'æ', u'ç', u'è', u'é', u'ê', u'ë', u'ì', u'í', u'î', u'ï',
        u'ð', u'ñ', u'ò', u'ó', u'ô', u'õ', u'ö', u'÷', u'ø', u'ù', u'ú', u'û', u'ü', u'ý', u'þ', u'ÿ'
    )
// Right-hand part of Latin/Greek alphabet
ISO_IR_SBCS96(227,(-1), 0x69)
    // 2003-07-28
    // G1: ESC \x2d \x69
    // G2: ESC \x2e \x69
    // G3: ESC \x2f \x69
    ISO_IR_SBCS96_DATA(
        u' ', u'‘', u'’', u'£', u'€', u'₯', u'¦', u'§', u'¨', u'©', u'ͺ', u'«', u'¬', u'\u00ad',  0,   u'―',
        u'°', u'±', u'²', u'³', u'΄', u'΅', u'Ά', u'·', u'Έ', u'Ή', u'Ί', u'»', u'Ό', u'½', u'Ύ', u'Ώ',
        u'ΐ', u'Α', u'Β', u'Γ', u'Δ', u'Ε', u'Ζ', u'Η', u'Θ', u'Ι', u'Κ', u'Λ', u'Μ', u'Ν', u'Ξ', u'Ο',
        u'Π', u'Ρ',  0,   u'Σ', u'Τ', u'Υ', u'Φ', u'Χ', u'Ψ', u'Ω', u'Ϊ', u'Ϋ', u'ά', u'έ', u'ή', u'ί',
        u'ΰ', u'α', u'β', u'γ', u'δ', u'ε', u'ζ', u'η', u'θ', u'ι', u'κ', u'λ', u'μ', u'ν', u'ξ', u'ο',
        u'π', u'ρ', u'ς', u'σ', u'τ', u'υ', u'φ', u'χ', u'ψ', u'ω', u'ϊ', u'ϋ', u'ό', u'ύ', u'ώ',  0
    )
// Latin/Hebrew character set for 8-bit codes
ISO_IR_SBCS96(234,(-1), 0x6a)
    // 2004-07-20
    // G1: ESC \x2d \x6a
    // G2: ESC \x2e \x6a
    // G3: ESC \x2f \x6a
    ISO_IR_SBCS96_DATA(
        u' ',  0,   u'¢', u'£', u'¤', u'¥', u'¦', u'§', u'¨', u'©', u'×', u'«', u'¬', u'\u00ad', u'®', u'¯',
        u'°', u'±', u'²', u'³', u'´', u'μ', u'¶', u'·', u'¸', u'¹', u'÷', u'»', u'¼', u'½', u'¾',  0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,   u'€', u'₪', u'\u202d', u'\u202e', u'\u202c',  0,   u'‗',
        u'א', u'ב', u'ג', u'ד', u'ה', u'ו', u'ז', u'ח', u'ט', u'י', u'ך', u'כ', u'ל', u'ם', u'מ', u'ן',
        u'נ', u'ס', u'ע', u'ף', u'פ', u'ץ', u'צ', u'ק', u'ר', u'ש', u'ת', u'\u202a', u'\u202b', u'\u200e', u'\u200f',  0
    )

/// Multiple byte graphic character sets
// Japanese Character Set JISC C 6226-1978
ISO_IR_MBCS94(42,(-1), 0x40)
    // 1979-12-30
    // G0: ESC \x24 \x40  OR  ESC \x24 \x28 \x40
    // G1: ESC \x24 \x29 \x40
    // G2: ESC \x24 \x2a \x40
    // G3: ESC \x24 \x2b \x40
    ISO_IR_MBCS94_DATA(jisc_6226_1978)
// Chinese Character Set Chinese Standard GB 2312-80
ISO_IR_MBCS94(58,(-1), 0x41)
    // 0000-00-00
    // G0: ESC \x24 \x41  OR  ESC \x24 \x28 \x41
    // G1: ESC \x24 \x29 \x41
    // G2: ESC \x24 \x2a \x41
    // G3: ESC \x24 \x2b \x41
    ISO_IR_MBCS94_DATA(gb_2312_80)
// Japanese Character Set JIS C 6226-1983
ISO_IR_MBCS94(87,(-1), 0x42)
    // 1984-07-01
    // G0: ESC \x24 \x42  OR  ESC \x24 \x28 \x42
    // G1: ESC \x24 \x29 \x42
    // G2: ESC \x24 \x2a \x42
    // G3: ESC \x24 \x2b \x42
    ISO_IR_MBCS94_DATA(jisc_6226_1983)
// Korean Graphic Character Set, Korean Standard KSC 5601-1987
ISO_IR_MBCS94(149,(-1), 0x43)
    // 1984-07-01
    // G0: ESC \x24 \x28 \x43
    // G1: ESC \x24 \x29 \x43
    // G2: ESC \x24 \x2a \x43
    // G3: ESC \x24 \x2b \x43
    ISO_IR_MBCS94_DATA(ksc_5601_1987)
// Supplementary Japanese Graphic Character Set for Information Interchange
ISO_IR_MBCS94(159,(-1), 0x44)
    // 1991-12-15
    // G0: ESC \x24 \x28 \x44
    // G1: ESC \x24 \x29 \x44
    // G2: ESC \x24 \x2a \x44
    // G3: ESC \x24 \x2b \x44
    ISO_IR_MBCS94_DATA(jisx_0212_1990)
// CCITT Chinese Set
ISO_IR_MBCS94(165,(-1), 0x45)
    // 1992-07-13
    // G0: ESC \x24 \x28 \x45
    // G1: ESC \x24 \x29 \x45
    // G2: ESC \x24 \x2a \x45
    // G3: ESC \x24 \x2b \x45
    // Documented as "GB 2312 + GB 8565.2"
    // Note: the scans are missing the right-hand column of each page.
    ISO_IR_MBCS94_DATA(ccitt_chinese)
// Update Registration 87 Japanese Graphic Character Set for Information Interchange
ISO_IR_MBCS94(168,(0), 0x42)
    // 1992-07-13
    // G0: ESC \x26 \x40 ESC \x24 \x42  OR  ESC \x26 \x40 ESC \x24 \x28 \x42
    // G1: ESC \x26 \x40 ESC \x24 \x29 \x42
    // G2: ESC \x26 \x40 ESC \x24 \x2a \x42
    // G3: ESC \x26 \x40 ESC \x24 \x2b \x42
    ISO_IR_MBCS94_DATA(jisx_0208_1990)
// Blissymbol Graphic Character Set
ISO_IR_MBCS94(169,(-1), 0x46)
    // 1993-01-21
    // G0: ESC \x24 \x28 \x46
    // G1: ESC \x24 \x29 \x46
    // G2: ESC \x24 \x2a \x46
    // G3: ESC \x24 \x2b \x46
    // Note: not encoded in Unicode, needs decomposing.
    ISO_IR_MBCS94_DATA(blissymbols)
// Chinese Standard Interchange Code - Set 1, CNS 11643-1992
ISO_IR_MBCS94(171,(-1), 0x47)
    // 1993-01-21
    // G0: ESC \x24 \x28 \x47
    // G1: ESC \x24 \x29 \x47
    // G2: ESC \x24 \x2a \x47
    // G3: ESC \x24 \x2b \x47
    ISO_IR_MBCS94_DATA(cns_11643_1)
// Chinese Standard Interchange Code - Set 2, CNS 11643-1992
ISO_IR_MBCS94(172,(-1), 0x48)
    // 1993-01-21
    // G0: ESC \x24 \x28 \x48
    // G1: ESC \x24 \x29 \x48
    // G2: ESC \x24 \x2a \x48
    // G3: ESC \x24 \x2b \x48
    ISO_IR_MBCS94_DATA(cns_11643_2)
// Chinese Standard Interchange Code - Set 3, CNS 11643-1992
ISO_IR_MBCS94(183,(-1), 0x49)
    // 1995-01-16
    // G0: ESC \x24 \x28 \x49
    // G1: ESC \x24 \x29 \x49
    // G2: ESC \x24 \x2a \x49
    // G3: ESC \x24 \x2b \x49
    ISO_IR_MBCS94_DATA(cns_11643_3)
// Chinese Standard Interchange Code - Set 4, CNS 11643-1992
ISO_IR_MBCS94(184,(-1), 0x4a)
    // 1995-01-16
    // G0: ESC \x24 \x28 \x4a
    // G1: ESC \x24 \x29 \x4a
    // G2: ESC \x24 \x2a \x4a
    // G3: ESC \x24 \x2b \x4a
    ISO_IR_MBCS94_DATA(cns_11643_4)
// Chinese Standard Interchange Code - Set 5, CNS 11643-1992
ISO_IR_MBCS94(185,(-1), 0x4b)
    // 1995-01-16
    // G0: ESC \x24 \x28 \x4b
    // G1: ESC \x24 \x29 \x4b
    // G2: ESC \x24 \x2a \x4b
    // G3: ESC \x24 \x2b \x4b
    ISO_IR_MBCS94_DATA(cns_11643_5)
// Chinese Standard Interchange Code - Set 6, CNS 11643-1992
ISO_IR_MBCS94(186,(-1), 0x4c)
    // 1995-01-16
    // G0: ESC \x24 \x28 \x4c
    // G1: ESC \x24 \x29 \x4c
    // G2: ESC \x24 \x2a \x4c
    // G3: ESC \x24 \x2b \x4c
    ISO_IR_MBCS94_DATA(cns_11643_6)
// Chinese Standard Interchange Code - Set 7, CNS 11643-1992
ISO_IR_MBCS94(187,(-1), 0x4d)
    // 1995-01-16
    // G0: ESC \x24 \x28 \x4d
    // G1: ESC \x24 \x29 \x4d
    // G2: ESC \x24 \x2a \x4d
    // G3: ESC \x24 \x2b \x4d
    ISO_IR_MBCS94_DATA(cns_11643_7)
// DPRK Standard Korean Graphic Character Set for Information Interchange
ISO_IR_MBCS94(202,(-1), 0x4e)
    // 1998-06-22
    // G0: ESC \x24 \x28 \x4e
    // G1: ESC \x24 \x29 \x4e
    // G2: ESC \x24 \x2a \x4e
    // G3: ESC \x24 \x2b \x4e
    ISO_IR_MBCS94_DATA(kps_9566)
// Japanese Graphic Character Set for Information Interchange --- Plane 1
ISO_IR_MBCS94(228,(-1), 0x4f)
    // 2000-07-31
    // G0: ESC \x24 \x28 \x4f
    // G1: ESC \x24 \x29 \x4f
    // G2: ESC \x24 \x2a \x4f
    // G3: ESC \x24 \x2b \x4f
    ISO_IR_MBCS94_DATA(jisx_0213_1_2000)
// Japanese Graphic Character Set for Information Interchange --- Plane 2
ISO_IR_MBCS94(229,(-1), 0x50)
    // 2000-07-31
    // G0: ESC \x24 \x28 \x50
    // G1: ESC \x24 \x29 \x50
    // G2: ESC \x24 \x2a \x50
    // G3: ESC \x24 \x2b \x50
    ISO_IR_MBCS94_DATA(jisx_0213_2_2000) // unchanged in the 2004 update
// Japanese Graphic Character Set for Information Interchange, Plane 1 (Update of ISO-IR 228)
ISO_IR_MBCS94(233,(-1), 0x51)
    // 2004-04-13
    // G0: ESC \x24 \x28 \x51
    // G1: ESC \x24 \x29 \x51
    // G2: ESC \x24 \x2a \x51
    // G3: ESC \x24 \x2b \x51
    ISO_IR_MBCS94_DATA(jisx_0213_1_2004)

/// C0 Control character sets
// C0 Set of ISO 646
ISO_IR_C0(1,(-1), 0x40)
    // 1975-12-01
    // C0: ESC \x21 \x40
    ISO_IR_C0_DATA(
        /*
        Null

        A control character used to accomplish media-fill or time-fill.
        Null characters may be inserted into or removed from a stream
        of data without affecting the information content of that stream.
        But then the addition or removal of there characters may affect
        the information lay out and/or control of equipment.
        */
        NUL,
        /*
        Transmission Control Character 1 (Start of Heading)

        A transmission control character used as the first character of a
        heading of an information message.
        */
        SOH,
        /*
        Transmission Control Character 2 (Start of Text)

        A transmission control character which precedes a text and which
        is used to terminate a heading.
        */
        STX,
        /*
        Transmission Control Character 3 (End of Text)

        A transmission control character which terminates a text.
        */
        ETX,
        /*
        Transmission Control Character 4 (End of Transmission)

        A transmission control character used to indicate the conclusion of
        the transmission of one or more texts.
        */
        EOT,
        /*
        Transmission Control Character 5 (Enquiry)

        A transmission control character used as a request for a response
        from a remote station; the response may include station
        indentification and/or station status. When a "Who are you"
        function is required on the general switched transmission network,
        the first use of ENQ after the connection is established shall have
        the meaning "Who are you" (station identification). Subsequent use
        of ENQ may, or may not, include the function "Who are you", as
        determined by agreement.
        */
        ENQ,
        /*
        Transmission Control Character 5 (Acknowledge)

        A transmission control character transmitted by a receiver as an
        affirmative response to the sender.
        */
        ACK,
        /*
        Bell

        A control character that is used when there is a need to call for
        attention ; it may control alarm or attention devices.
        */
        BEL,
        /*
        Format Effector 0 (Backspace)

        A format effector which moves the active position one character
        position backwards on the same line.
        */
        BS,
        /*
        Format Effector 1 (Horizontal Tabulation)

        A format effector which advances the active position to the next
        pre-determined character position on the same line.
        */
        HT,
        /*
        Format Effector 2 (Line Feed)

        A format effector which advances the active position to the same
        character position of the nextline.
        */
        LF,
        /*
        Format Effector 3 (Vertical Tabulation)

        A format effector which advances the active position to the same
        character position on the next pre-determined line.
        */
        VT,
        /*
        Format Effector 4 (Form Feed)

        A format effector which advances the active position to the same
        character position on a pre-determined line of the next form or
        page.
        */
        FF,
        /*
        Format Effector 5 (Carriage Return)

        A format effector which moves the active position to the first
        character position on the same line.
        */
        CR,
        /*
        Shift Out

        A control character which is used in conjunction with SHIFT-IN and
        ESCAPE to extend the graphic character set of the code. It may
        alter the meaning of the bit combinations of columns 2 to 7 that
        follow it until a SHIFT-IN character is reached. However, the
        characters SPACE (2/0) and DELETE (7/15) are unaffected by
        SHIFT-OUT. The effect of using this character when using code
        extension techniques is described in International Standard
        ISO 2022
        */
        SO,
        /*
        Shift In

        A control character which is used in conjunction with SHIFT-OUT and
        ESCAPE to extend the graphic character set of the code. It may
        reinstate the standard meanings of the bit combinations which
        follow it. The effect of using this character when using code
        extension techniques is described in International Standard
        ISO 2022.
        */
        SI,

        /*
        Transmission Control Character 7 (Data Link Escape)

        A transmission control character which will change the meaning of
        a limited number of contiguously following characters. It is used
        exclusively to provide supplementary data transmission control
        functions. Only graphic characters and transmission control
        characters can be used in DLE sequences.
        */
        DLE,
        /*
        Device Control 1

        A device control character which is primarily intended for turning
        on or starting an ancillary device. If it is not required for this
        purpose, it may be used to restore a device to the basic mode of
        operation (see also DC2 and DC3), or for any other device control
        function not provided by other DCs.
        */
        DC1,
        /*
        Device Control 2

        A device control character which is primarily intended for turning
        on or starting an ancillary device. If it is not required for this
        purpose, it may be used to set a device to a special mode of
        operation (in which case DC1 is used to restore the device to the
        basic mode), or for any other device control function not provided
        by other DCs.
        */
        DC2,
        /*
        Device Control 3

        A device control character which is primarily intended for turning
        off or stopping an ancillary device. This function may be a
        secondary level stop, for example, wait, pause, stand-by or halt
        (in which case DC1 is used to restore normal operation). If it is
        not required for this purpose, it may be used for any other device
        control function not provided by other DCs.
        */
        DC3,
        /*
        Device Control 4

        A device control character which is primarily intended for turning
        off, stopping or interrupting an ancillary device. If it is not
        required for this purpose, it may be used for any other device
        control function not provided by other DCs.
        */
        DC4,
        /*
        Transmission Control Character 8 (Negative Acknowledge)

        A transmission control character transmitted by a receiver as a
        negative response to the sender.
        */
        NAK,
        /*
        Transmission Control Character 9 (Synchronous Idle)

        A transmission control character used by a synchronous transmission
        in the absense of any other character (idle condition) to provide
        a signal from which synchronism may be acheived or retained between
        data terminal equipment.
        */
        SYN,
        /*
        Transmission Control Character 10 (End of Transmission Block)

        A transmission control character used to indicate the end of a
        transmission block of data where data is divided into such blocks
        for transmission purposes.
        */
        ETB,
        /*
        Cancel

        A character, or the first character of a sequence, indicating that
        the data preceding it is in error. As a result, this data is to be
        ignored. The specific meaning of this character must be defined for
        each application and/or between sender and recipient.
        */
        CAN,
        /*
        End of Medium

        A control character that may be used to identify the physical end
        of a medium, or the end of the used portion of a medium, or the end
        of the wanted portion of data recorded on a medium. The position of
        this character does not necessarily correspond to the physical end
        of the medium.
        */
        EM,
        /*
        Substitute Character

        A control character used in the place of a character that has been
        found to be invalid or in error. SUB is intended to be introduced
        by automatic means.
        */
        SUB,
        /*
        Escape

        A control character which is used to provide addition control
        functions. It alters the meaning of a limited number of
        contiguously following bit combinations.

        The use of this character is specified in International Standard
        ISO 2022.
        */
        ESC,
        /*
        Information Separator 4 (File Separator)

        A control character used to separate and qualify data logically;
        its specific meaning has to be defined for each application. If
        this character is used in hierarchical order, it delimits a data
        item called a FILE.
        */
        FS,
        /*
        Information Separator 3 (Groupe Separator)

        A control character used to separate and qualify data logically;
        its specific meaning has to be defined for each application. If
        this character is used in hierarchical order, it delimits a data
        item called a GROUP.
        */
        GS,
        /*
        Information Separator 2 (Record Separator)

        A control character used to separate and qualify data logically;
        its specific meaning has to be defined for each application. If
        this character is used in hierarchical order, it delimits a data
        item called a RECORD.
        */
        RS,
        /*
        Information Separator 1 (Unit Separator)

        A control character used to separate and qualify data logically;
        its specific meaning has to be defined for each application. If
        this character is used in hierarchical order, it delimits a data
        item called a UNIT.
        */
        US,
    )
// NATS, C0 Set
ISO_IR_C0(7,(-1), 0x41)
    // 1975-12-01
    // C0: ESC \x21 \x41
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        /*
        Formatting

        Used for tabular work to move to the next preset tabulation
        position along the line. According to the context FO is also used
        for example when working with standard formats to indicate the next
        phase of the format.
        */
        NATS_FO,
        LF,
        /*
        End of Instruction

        Indicates the end of a typographical instruction to the device
        which makes the final typographical preparation of the text.
        */
        NATS_ECD,
        /*
        Start of Instruction

        Indicates the beginning of a typographical instruction. See also
        ECD above.
        */
        NATS_SCD,
        /*
        Quad Left

        Terminates a line and indicates that the text on the line shall
        start at the left margin.
        */
        NATS_QL,
        /*
        Upper Rail

        Initiates a change in typeface indicating that a part of the text
        to follow shall be stressed.
        */
        NATS_UR,
        /*
        Lower Rail

        Resets to lower rail.
        */
        NATS_LR,

        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        /*
        Kill Word

        Indicates that all codes from and including the last space (SP)
        shall be disregarded. If the erroneous word is preceded by an end
        of line code (QL, QC, QR, JY) that code shall remain effective.
        */
        NATS_KW,
        EM,
        SUB,
        ESC,
        /*
        Super Shift

        A non-locking control character invoking the next graphic character
        from an other properly designated set.
        */
        NATS_SS,
        /*
        Quad Centre

        Terminates the line and indicates that the text on the line shall
        be centred.
        */
        NATS_QC,
        /*
        Quad Right

        Terminates the line and indicates that the text on the line shall
        end at the right margin.
        */
        NATS_QR,
        /*
        Justify

        Terminates the line and indicates that the preceding line shall be
        justified to the given line measure with regards to indents etc.
        */
        NATS_JY,
    )
// IPTC, C0 Set
ISO_IR_C0(26,(-1), 0x43)
    // 1976-03-25
    // C0: ESC \x21 \x43
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        NATS_FO,
        LF,
        NATS_ECD,
        NATS_SCD,
        NATS_QL,
        SO,
        SI,

        DLE,
        /*
        Font 1

        Initiates a change to Normal typeface.
        */
        IPTC_FT1,
        /*
        Font 2

        Initiates a change to Italic typeface.
        */
        IPTC_FT2,
        /*
        Font 3

        Initiates a change to Bold typeface.
        */
        IPTC_FT3,
        DC4,
        NAK,
        SYN,
        ETB,
        NATS_KW,
        EM,
        SUB,
        ESC,
        NATS_SS,
        NATS_QC,
        NATS_QR,
        NATS_JY,
    )
// C0 Set of ISO 646 with SS2 instead of IS4
ISO_IR_C0(36,(-1), 0x44)
    // 1977-10-15
    // C0: ESC \x21 \x44
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        HT,
        LF,
        VT,
        FF,
        CR,
        SO,
        SI,

        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        EM,
        SUB,
        ESC,
        /*
        Single Shift for G2

        A control character which is used to extend the set of graphic
        characters of the code. It alters the meaning of the single
        bit-combination following it. That bit-combination must be one of
        those from columns 2 to 7, except Space(2/0) and Delete(7/15).
        The meaning of the bit-combination concerned is derived from a
        properly designated graphic set. Such a set consists of up to
        94 characters, represented by bit-combinations 2/1 to 7/14
        inclusive and may be designated by a three characters escape
        sequence (see ISO 2022). The use of Single Shift for G2 (SS2) is
        not affected by and does not affect the Shift State (SO/SI).
        */
        SS2,
        GS,
        RS,
        US,
    )
// INIS, Control Set
ISO_IR_C0(48,(-1), 0x42)
    // 1981-07-15
    // C0: ESC \x21 \x42
    ISO_IR_C0_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        ESC,
        0,
        /*
        Group Separator

        A control character used to separate and qualify data logically.
        Its specific meaning is to mark the end of the last variable field
        in a logical record (acc. to ISO 2709).
        */
        GS,
        /*
        Record Separator

        A control character used to separate and qualify data logically.
        Its specific meaning is to mark the end of a variable field which
        is not the last in the logical record (acc. to ISO 2709).
        */
        RS,
        0,
    )
// C0 for Japanese standard JIS C 6225-1979
ISO_IR_C0(74,(-1), 0x46)
    // 1983-10-01
    // C0: ESC \x21 \x46
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        HT,
        LF,
        VT,
        FF,
        CR,
        SO,
        SI,

        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        EM,
        SUB,
        ESC,
        /*
        Control extension

        A control character to introduce control strings to be used in
        conjunction with the Japanese graphic character sets. It alters the
        meaning of a limited number of contiguously following bit
        combinations. The syntax and semantics of the control strings
        introduced by CEX are defined in JIS C 6225.
        */
        JISC_CEX,
        GS,
        RS,
        US,
    )
// Minimum C0 Set for ISO 4873
ISO_IR_C0(104,(-1), 0x47)
    // 1985-08-01
    // C0: ESC \x21 \x47
    ISO_IR_C0_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        ESC,
        0,
        0,
        0,
        0,
    )
// Teletex primary set of Control Functions CCITT Rec. T.61
ISO_IR_C0(106,(-1), 0x45)
    // 1985-08-01
    // C0: ESC \x21 \x45
    ISO_IR_C0_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        BS,
        0,
        LF,
        0,
        FF,
        CR,
        /*
        Locking Shift One [i.e. Shift Out]

        A code extension control function which is used in conjunction with
        other locking-shift functions and with ESCAPE to extend the
        character set of an 8-bit code.

        LS1 is a locking-shift function which invokes the currently
        designated G1 set into positions 02/01 to 07/14.
        */
        LS1,
        /*
        Locking Shift Zero [i.e. Shift In]

        A code extension control function which is used in conjunction with
        other locking-shift functions and with ESCAPE to extend the
        character set of an 8-bit code.

        LS0 is a locking-shift function which invokes the currently
        designated G0 set into positions 02/01 to 07/14.
        */
        LS0,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        SS2,
        SUB,
        ESC,
        0,
        SS3,
        0,
        0,
    )
// C0 Set of ISO 646 without SI and SO ASMO-662 and COMECON ST SEV 358
ISO_IR_C0(130,(-1), 0x48)
    // 1987-07-31
    // C0: ESC \x21 \x48
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        HT,
        LF,
        VT,
        FF,
        CR,
        0,
        0,

        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        EM,
        SUB,
        ESC,
        FS,
        GS,
        RS,
        US,
    )
// Primary Control Set of Data Syntax I of CCITT Rec. T.101
ISO_IR_C0(132,(-1), 0x49)
    // 1987-07-31
    // C0: ESC \x21 \x49
    ISO_IR_C0_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        BEL,
        /*
        Active Position Backward

        This control character positions the cursor at a distance equal to
        the inter-character spacing lying parallel to the character path in
        the direction opposite to the character path. If such a movement
        causes the edge of the defined display area to be crossed, then the
        cursor is positioned at the opposite edge of the active drawing
        area and an automatic APU is executed.
        */
        CCITT_APB,
        /*
        Active Position Forward

        This control character moves the cursor a distance equal to the
        inter-character spacing lying parallel to the character path in the
        direction of the character path. If such a movement causes the edge
        of the defined display area to be crossed, then the cursor is
        positioned at the opposite edge of the active drawing area and an
        automatic APD is executed.
        */
        CCITT_APF,
        /*
        Active Position Down

        This control character moves the cursor a distance equal to the
        inter-row spacing lying perpendicular to the character path in a
        direction perpendicular to the character path (-90°). If such a
        movement causes the edge of the defined display area to be crossed,
        the cursor is positioned at the opposite edge of the defined
        display area.
        */
        CCITT_APD,
        /*
        Active Position Up

        This control character moves the cursor a distance equal to the
        inter-row spacing lying perpendicular to the character path in a
        direction perpendicular to the character path (90°). If such a
        movement causes the edge of the defined display area to be crossed,
        the cursor is positioned at the opposite edge of the defined
        display area.
        */
        CCITT_APU,
        /*
        Clear Screen

        This control character resets all the display attributes to their
        default states and activates an automatic APH. Then, all macro
        definitions and DRCS definitions are cancelled. CS clears the
        entire screen.
        */
        CCITT12_CS,
        /*
        Active Position Return

        This control character positions the cursor to the first character
        position within the defined display area along the character path
        and an automatic APD is executed.
        */
        CCITT1_APR,
        LS1,
        LS0,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        /*
        Cancel

        This control character terminates processing of all currently
        executing macros. Execution is resumed at the next presentation
        level character following the terminated macro call. The effect of
        CAN is immediate.
        */
        CAN,
        SS2,
        0,
        ESC,
        /*
        Active Position Set

        This control character sets the cursor position which is specified
        by the two-byte parameter immediately following APS.  The first
        byte represents the row address and the second byte represents the
        column address. The address is obtained by taking the binary values
        comprising bits b6 to b1, b6 being the MSB. (Each byte is from
        columns 4 to 7.)

        APS operations are as follows: first, an automatic APH is executed.
        Then the cursor is positioned n inter-row spacings below and m
        inter-character spacings right of the home position, where n is the
        number specified by the first byte and m is the number specified by
        the second byte. If any of the two bytes does not belong to columns
        4 to 7, the APS character and following two bytes are interpreted
        as NULs.
        */
        CCITT1_APS,
        SS3,
        /*
        Active Position Home

        This control character moves the cursor to the upper left character
        position in the defined display area.
        */
        CCITT_APH,
        /*
        Non Selective Reset

        This control character serves two functions. NSR resets
        non-selectively all the display attributes to their default states.
        Then NSR resets the cursor positions according to the two-byte
        parameters immediately following it.

        The cursor position is the same as APS, except APS sets the cursor
        according to the current inter-character spacing and inter-row
        spacing, while NSR sets the cursor according to their default
        values. Macro definitions and DRCS are not cancelled by NSR.
        */
        CCITT1_NSR,
    )
// Primary Control Set of Data Syntax II of CCITT Rec. T.101
ISO_IR_C0(134,(-1), 0x4a)
    // 1987-07-31
    // C0: ESC \x21 \x4a
    ISO_IR_C0_DATA(
        NUL,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        CCITT_APB,
        CCITT_APF,
        CCITT_APD,
        CCITT_APU,
        /*
        Clear Screen

        A format effector which causes the active position to be moved to
        the first character position of the first row in the defined
        display area and causes all character positions to be filled with
        spaces with all attributes set to the default condition.
        */
        CCITT12_CS,
        CR,
        LS1,
        LS0,

        0,
        CCITT_CON,
        /*
        Repeat

        A control character followed by a one-byte parameter which
        indicates the number of repetitions of the immediately preceding
        graphic character. The number of repetitions is given in binary
        form by the 6 least significant bits of the bit combination
        representing the parameter following RPT which is taken from
        columns 4 to 7. The preceding graphic character itself is not
        included in the count. This function does not apply to control
        characters.
        */
        CCITT_RPT,
        0,
        CCITT_COF,
        0,
        0,
        0,
        CAN,
        SS2,
        0,
        ESC,
        0,
        SS3,
        CCITT_APH,
        /*
        Active Position Address

        A control function followed by a two- or four- byte parameter. All
        parameter bytes shall be in the range 4/0 to 7/15 and represent
        respectively the row address and the column address in binary form,
        with 6 useful bits (bit 6 being the most significant bit) of the
        first character to be displayed.

        If the format exceeds either 63 rows or 63 columns then both
        parameters (i.e. the row and the column address) are coded as a
        two-byte sequence with 12 useful bits, the first byte carrying the
        most significant bits. The location addressed by APA, 4/1, 4/1 (or
        APA, 4/0, 4/1, 4/0, 4/1 if the format exceeds either 63 rows or 63
        columns) is the top left-hand location of the defined display area.

        If the first byte following APA is not within the range 4/0 to
        7/15, this sequence indicates a switch to an alternative coding
        scheme.
        */
        CCITT_APA,
    )
// Primary Control Set of Data Syntax III of CCITT Rec. T.101
ISO_IR_C0(135,(-1), 0x4b)
    // 0000-00-00
    // C0: ESC \x21 \x4b
    ISO_IR_C0_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        BEL,
        // mentions "active field" as a thing
        CCITT_APB,
        // mentions "active field" as a thing
        CCITT_APF,
        // mentions "active field" as a thing
        CCITT_APD,
        // mentions "active field" as a thing
        CCITT_APU,
        /*
        Clear Screen

        This control character moves the cursor to the upper left character
        position of the display area, in which the top of the character
        field coincides with the top of the display are. In colour modes 0
        and 1, it clears the display area to nominal black. In colour mode
        2, it clears the display area to the current background colour.
        */
        CCITT3_CS,
        // mentions "active field" as a thing
        CR,
        SO,
        SI,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        /*
        Cancel

        This control character terminates the processing of all currently
        executing macros. Execution is resumed at the next presentation
        layer character following the terminated macro call. The effect of
        CAN is immediate, i.e. it is not put at the end of any existing
        queue of unprocessed presentation layer code. The operation of the
        CAN character is not guaranteed unless it is guaranteed to be
        delivered by the lower layers.
        */
        CAN,
        SS2,
        /*
        Service Delimiter Character

        This control character shall be executed as a null operation at the
        presentation layer and any other use is implementation-dependent.
        */
        CCITT_SDC,
        ESC,
        /*
        Active Position Set

        This control character sets the cursor position without resetting
        any parameters or attributes.

        The two bytes immediately following an APS shall both belong to
        columns 2 to 7 or 10 to 15 of the table. They represent the row
        address and column address, respectively, to which the cursor is to
        be moved. The row address is obtained from the first byte following
        as APS by taking the integer represented in binary notation by bits
        b7 to b1, b7 being the MSB, and subtracting 32. Similarly, the
        column address is obtained from the second byte following an APS by
        taking the integer represented in binary notation by bits b7 to b1,
        b7 being the MSB, and subtracting 32. This gives an address range
        from 0 to 95 for the row and column addresses. If either of the
        characters following APS is a C0 or C1 control character, APS is
        ignored and the C0 or C1 control character is executed.

        Rows and columns are numbered starting with row 0, column 0, in the
        lower leftmost character position of the display area, and refer to
        the nominal screen format established by the current character
        field size (with the default intercharacter and interrow spacing).
        The cursor is positioned assuming zero character rotation to
        establish the character field origin. Once the character field
        origin is established, the character field and cursor are rotated,
        if necessary.
        */
        CCITT3_APS,
        SS3,
        CCITT_APH,
        /*
        Non-selective Reset

        This control character serves two functions : it non-selectively
        resets the presentation process as defined below and it can be used
        as an alternative means to position the cursor. When an NSR is
        received, the following action is taken :

        1) The G0, G1, G2, G3, C0 and C1 sets are designated to their
        default states and the code table in invoked to its default state.

        2) The DOMAIN parameters are set to their default values.

        3) The TEXT parameters (from the TEXT opcode, from the C1 set and
        the active field), are set to their default values.

        4) The TEXTURE parameters are set to their default values. The
        programmable masks are not cleared.

        5) The colour mode is set to colour mode 0 and the drawing colour
        is set to nominal white. The colour map is not changed.

        6) If the two bytes that immediately follow NSR both belong to
        columns 4 to 7 of the table, the cursor is positioned. These two
        bytes represent, in binary form (i.e. the integer represented by
        bits b6 to b1, b6 being the MSB), the row and column address,
        respectively, to which the cursor should be moved. Rows and columns
        are numbered starting with row 0, column 0 in the upper leftmost
        character position in the display area and refer to the nominal
        screen format established by the default character size. The top of
        the character field for row 0 coincides with the top boundary of
        the display area. If either of the two bytes following NSR does not
        belong to columns 4 to 7 (or columns 12 to 15) of the table, the
        non-selective reset function of NSR is executed and the cursor is
        not repositioned. If the two bytes belong to columns 2 and 3 (or
        columns 12 to 15), they are ignored. If either of the two bytes
        represents a C0 or C1 control character they terminate the NSR
        sequence and the control character(s) is executed.
        */
        CCITT3_NSR,
    )
// C0 Set of ISO 646 with EM replaced by SS2 - Czechoslovak Standard CSN 369102
ISO_IR_C0(140,(-1), 0x4c)
    // 1987-07-31
    // C0: ESC \x21 \x4c
    ISO_IR_C0_DATA(
        NUL,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        HT,
        LF,
        VT,
        FF,
        CR,
        SO,
        SI,

        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        SS2,
        SUB,
        ESC,
        FS,
        GS,
        RS,
        US,
    )

/// C1 Control character sets
// Additional Control Functions for Bibliographic Use according to DIN 31626
ISO_IR_C1(40,(-1), 0x45)
    // 1979-07-15
    // C1: ESC \x22 \x45
    ISO_IR_C1_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        /*
        Close-up for Sorting

        Filing control character which declares two strings of characters
        separated by a space [blank] to be one filing string.
        */
        CUS,
        /*
        Non-sorting Character(s) Beginning

        Filing control characters which precedes a (string of) character(s)
        with no filing value.
        */
        NSB,
        /*
        Non-sorting Character(s) End

        Filing control character to mark the end of a (string of)
        character(s) with no filing.
        */
        NSE,
        /*
        Fil Character

        Character which substitutes an otherwise mandatory alphanumeric
        character.
        */
        DIN_FIL,
        /*
        Tag-in-context Indicator

        Reference control character which - within the data of a
        bibliographic field - refers to data identified by the field number
        (tag) of another bibliographic field in the record.
        */
        DIN_TCI,
        /*
        Identification Number-in-context Indicator

        Reference control character which - within the data of a
        bibliographic field - refers to data identified by the
        identification number of another record in the data set.
        */
        DIN_ICI,
        /*
        Optional Syllabication Control

        Print control character which separates syllables in very long
        words.
        */
        DIN_OSC,
        /*
        Single Shift Two

        SS2 alters the meaning of the single bit-combination following it.
        That bit-combination must be one of those from columns 2 to 7
        except 2/0 and 7/15.  The meaning of the bit-combination concerned
        is derived from a properly designated graphic set (G2 set).
        */
        SS2,
        /*
        Single Shift Three

        SS3 alters the meaning of the single bit-combination following it.
        That bit-combination must be one of those from columns 2 to 7
        except 2/0 and 7/15.  The meaning of the bit-combination concerned
        is derived from a properly designated graphic set (G3 set).
        */
        SS3,

        0,
        /*
        Embedded Annotation Beginning

        Annotation control character which precedes an annotation of
        variable length within the data of a bibliographic field.
        */
        EAB,
        /*
        Embedded Annotation End

        Annotation control character to mark the end of an annotation.
        */
        EAE,
        /*
        Item Specification Beginning

        Indexing control character which precedes specific information of
        variable length within the data of a bibliographic field, with the
        exception of information specified by the KWB/KWE and PSB/PSE
        control characters.
        */
        DIN_ISB,
        /*
        Item Specification End

        Indexing control character to mark the end of a specific
        information.
        */
        DIN_ISE,
        0,
        0,
        0,
        0,
        /*
        Indicator for Nonstandard Character

        Character manipulation control character which identifies a
        following non-standard character.
        */
        DIN_INC,
        0,
        0,
        /*
        Keyword Beginning

        Indexing control character which precedes a keyword within the data
        of a bibliographic field.
        */
        KWB,
        /*
        Keyword End

        Indexing control character to mark the end of a keyword.
        */
        KWE,
        /*
        Permutation String Beginning

        Indexing control character which precedes a string of characters of
        variable length with which a permutation is to be effected, within
        the data of a bibliographic field.
        */
        PSB,
        /*
        Permutation String End

        Indexing control character to mark the end of a permutation string.
        */
        PSE,
    )
// Attribute Control set for UK Videotex British Telecom
ISO_IR_C1(56,(-1), 0x40)
    // 1982-06-01
    // C1: ESC \x22 \x40
    // See UKV_HMS for an important note!
    ISO_IR_C1_DATA(
        /*
        Alpha Black

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in black.
        */
        UKV_ABK,
        /*
        Alpha Red

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in red.
        */
        UKV_ANR,
        /*
        Alpha Green

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in green.
        */
        UKV_ANG,
        /*
        Alpha Yellow

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in yellow.
        */
        UKV_ANY,
        /*
        Alpha Blue

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in blue.
        */
        UKV_ANB,
        /*
        Alpha Magenta

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in magenta.
        */
        UKV_ANM,
        /*
        Alpha Cyan

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in cyan.
        */
        UKV_ANC,
        /*
        Alpha White

        Causes the designated alphanumeric set in use (current shift
        position) to be activated and characters to be written in white.
        */
        UKV_ANW,
        /*
        Flashing

        Causes the characters to be displayed alternately in the prevailing
        foreground colour and in the prevailing background colour under the
        control of a timing device in the receiver.
        */
        UKV_FSH,
        /*
        Steady

        Causes the action of Flashing to be stopped.
        */
        UKV_STD,
        /*
        End Box

        Causes the action of Start Box to be stopped.
        */
        UKV_EBX,
        /*
        Start Box

        Defines the start of a non-alphanumeric area in a page of text.
        */
        UKV_SBX,
        /*
        Single Size

        Causes the active position to move to, and to occupy, the next
        character position on the same line. All characters shall be imaged
        in this manner until either occurence of DBH or DBW or DBS, or the
        end of a line is reached.
        */
        UKV_NSZ,
        /*
        Double Height

        Causes the active position to move to, and to occupy, the next
        character position on the same line and the corresponding position
        on the next line. All characters shall be imaged in this manner
        until either occurence of NSZ or DBW or DBS, or the end of the line
        is reached. DBH is inactive on the bottom line of a form or page.
        */
        UKV_DBH,
        /*
        Double Width

        Causes the active position to move to, and to occupy, the next two
        character positions on the same line. All characters shall be
        imaged in this manner until either occurence of NSZ or DBH or DBS,
        or the end of the line is reached. DBW is inactive in the last
        character position of a line.
        */
        UKV_DBW,
        /*
        Double Size

        Causes the active position to move to, and to occupy, the next two
        character positions on the same line and the corresponding two
        positions on the next line. All characters shall be imaged in this
        manner until either occurence of NSZ or DBH or DBW, or the end of
        the line is reached. DBS is inactive in the last character position
        of a line or the bottom line of the form or page.
        */
        UKV_DBS,

        /*
        Mosaic Black

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in black.
        */
        UKV_MBK,
        /*
        Mosaic Red

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in red.
        */
        UKV_MSR,
        /*
        Mosaic Green

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in green.
        */
        UKV_MSG,
        /*
        Mosaic Yellow

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in yellow.
        */
        UKV_MSY,
        /*
        Mosaic Blue

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in blue.
        */
        UKV_MSB,
        /*
        Mosaic Magenta

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in magenta.
        */
        UKV_MSM,
        /*
        Mosaic Cyan

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in cyan.
        */
        UKV_MSC,
        /*
        Mosaic White

        Causes the designated mosaic set in use (current shift position) to
        be activated and characters to be written in white.
        */
        UKV_MSW,
        /*
        Conceal Display

        Causes the characters although stored in the receiver to be
        displayed as SPACES.
        */
        UKV_CDY,
        /*
        Stop Lining

        Causes the alphanumeric characters to be displayed without
        underline and mosaic characters to be displayed in the contiguous
        font.
        */
        UKV_SPL,
        /*
        Start Lining

        Causes alphanumeric characters to be displayed with underline and
        mosaic characters to be displayed in the separated font.
        */
        UKV_STL,
        CSI,
        /*
        Black Background

        Causes the background colour of the character positions to be
        black.
        */
        UKV_BBD,
        /*
        New Background

        Causes the background colour of character positions to be that of
        the previously applying foreground colour. The foreground colour
        remains unchanged.
        */
        UKV_NBD,
        /*
        Hold Mosaic

        When the mosaic graphic set is activated, causes the display
        locations corresponding to subsequently stored control functions to
        be imaged as the last received mosaic graphic character.

        [In this control set, all controls are spacing].
        */
        UKV_HMS,
        /*
        Release Mosaic

        Causes the action of Hold Mosaic to be stopped.
        */
        UKV_RMS,
    )
// Additional Control Functions for Bibliographic Use according to ISO 6630
ISO_IR_C1(67,(-1), 0x42)
    // 1983-06-01
    // C1: ESC \x22 \x42
    ISO_IR_C1_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        /*
        Close-up for Sorting

        A filing control character to effect that two successive strings of
        characters (which may be separated by a space or by any other
        separating character) constitute a single filing unit.
        */
        CUS,
        /*
        Non-sorting Character(s), Beginning

        A filing control character preceding a (string of) characters with
        no filing value.
        */
        NSB,
        /*
        Non-sorting Character(s), End

        A filing control character terminating a (string of) characters
        with no filing value.
        */
        NSE,
        0,
        0,
        0,
        0,
        0,
        0,

        0,
        /*
        Embedded Annotation, Beginning

        An annotation control character preceding annotations within
        descriptive bibliographic elements if this annotation is not
        separated from the bibliographic description by means of content
        designation. (For annotation with filing values see SIB).
        */
        EAB,
        /*
        Embedded Annotation, End

        An annotation control character terminating an embedded annotation
        which is not identified by means of content designation.
        */
        EAE,
        0,
        0,
        /*
        Sorting Interpolation, Beginning

        A filing control character to mark the beginning of an
        interpolation inserted for filing purposes only.
        */
        SIB,
        /*
        Sorting Interpolation, End

        A filing control character to mark the end of an interpolation with
        filing value.
        */
        SIE,
        /*
        Secondary Sorting Value, Beginning

        A filing control character to mark the beginning of a (string of)
        character(s) of subordinate filing value within a filing sequence.
        */
        SSB,
        /*
        Secondary Sorting Value, End

        A filing control character to mark the end of a (string of)
        character(s) of subordinate filing value.
        */
        SSE,
        0,
        0,
        0,
        /*
        Key-word, Beginning

        A control character for subject indexing used to indicate the
        beginning of a key-word in its bibliographic context.
        */
        KWB,
        /*
        Key-word, End

        A control character for subject indexing used to indicate the
        end of a key-word identified by the KWB control.
        */
        KWE,
        /*
        Permutation String, Beginning

        A control character which causes a permutation in an element of
        bibliographic information. If there is no PSE control a cyclic
        permutation of the bibliographic element around the PSB control is
        effected.
        */
        PSB,
        /*
        Permutation String, End

        A control character used in conjunction with the PSB control to
        effect a particular permutation by which the characters in between
        the PSB and PSE controls are placed in front of the remainder of
        the bibliographic element.
        */
        PSE,
    )
// Attribute Control Set for Videotex CCITT
ISO_IR_C1(73,(-1), 0x41)
    // 1983-10-01
    // C1: ESC \x22 \x41
    ISO_IR_C1_DATA(
        /*
        Black Foreground

        Invokes the 1st colour of the colour set.
        */
        CCITT_BKF,
        /*
        Red Foreground

        Invokes the 2nd colour of the colour set.
        */
        CCITT_RDF,
        /*
        Green Foreground

        Invokes the 3rd colour of the colour set.
        */
        CCITT_GRF,
        /*
        Yellow Foreground

        Invokes the 4th colour of the colour set.
        */
        CCITT_YLF,
        /*
        Blue Foreground

        Invokes the 5th colour of the colour set.
        */
        CCITT_BLF,
        /*
        Magenta Foreground

        Invokes the 6th colour of the colour set.
        */
        CCITT_MGF,
        /*
        Cyan Foreground

        Invokes the 7th colour of the colour set.
        */
        CCITT_CNF,
        /*
        White Foreground

        Invokes the 8th colour of the colour set.
        */
        CCITT_WHF,
        /*
        Flashing

        Causes the characters to be displayed alternately in the prevailing
        foreground colour and in the prevailing background colour under the
        control of a timing device.
        */
        CCITT_FSH,
        /*
        Steady

        Causes the action of FLASHING to be stopped.
        */
        CCITT_STD,
        /*
        End Box

        Causes the action of START BOX to be stopped.
        */
        CCITT_EBX,
        /*
        Start Box

        Applies the window/box attribute. The full screen background of the
        character positions becomes transparent.
        */
        CCITT_SBX,
        /*
        Normal Size

        Causes a character to occupy one character position. All characters
        shall be imaged in this manner until occurence of either DBH or DBW
        or DBS. NSZ remains active when the active position is moved to an
        adjacent line.
        */
        CCITT_NSZ,
        /*
        Double Height

        Causes a character to occupy two character positions, one above the
        other, on two adjacent lines. All characters shall be imaged in
        this manner until occurence of either NSZ or DBW or DBS. DBH shall
        not be active on the top line.
        */
        CCITT_DBH,
        /*
        Double Width

        Causes a character to occupy two adjacent character positions on
        the same line. All characters shall be imaged in this manner until
        occurence of either NSZ or DBH or DBS. DBW shall not be active on
        the last position of each line.
        */
        CCITT_DBW,
        /*
        Double Size

        Causes a character to occupy two adjacent character positions on
        the same line and the two corresponding positions on the line
        above. All characters shall be imaged in this manner until
        occurence of either NSZ or DBH or DBW. DBS shall not be active on
        the top line and on the last character position of each line.
        */
        CCITT_DBS,

        /*
        Black Background

        Invokes the 1st colour of the colour set.
        */
        CCITT_BKB,
        /*
        Red Background

        Invokes the 2nd colour of the colour set.
        */
        CCITT_RDB,
        /*
        Green Background

        Invokes the 3rd colour of the colour set.
        */
        CCITT_GRB,
        /*
        Yellow Background

        Invokes the 4th colour of the colour set.
        */
        CCITT_YLB,
        /*
        Blue Background

        Invokes the 5th colour of the colour set.
        */
        CCITT_BLB,
        /*
        Magenta Background

        Invokes the 6th colour of the colour set.
        */
        CCITT_MGB,
        /*
        Cyan Background

        Invokes the 7th colour of the colour set.
        */
        CCITT_CNB,
        /*
        White Background

        Invokes the 8th colour of the colour set.
        */
        CCITT_WHB,
        /*
        Conceal Display

        Causes the characters to be displayed as SPACEs until occurence of
        STOP CONCEAL.
        */
        CCITT_CDY,
        /*
        Stop Lining

        Stops the application of the action of START LINING.
        */
        CCITT_SPL,
        /*
        Start Lining

        Alphanumeric characters are displayed with an underline in which
        the underline is considered to be a part of the shape of the
        graphics character. Mosaic characters and line drawing characters
        are displayed in the separated font.
        */
        CCITT_STL,
        CSI,
        /*
        Normal Polarity

        Stops the action of INVERTED POLARITY.
        */
        CCITT_NPO,
        /*
        Inverted Polarity

        The characters are displayed as if the foreground and background
        colours had been exchanged. If flash is applied, the polarity of
        the flashing clock is also inverted.
        */
        CCITT_IPO,
        /*
        Transparent Background

        Invokes transparent background.
        */
        CCITT_TRB,
        /*
        Stop Conceal

        Stops the action of CONCEAL DISPLAY.
        */
        CCITT_SCD,
    )
// C1 Control Set of ISO 6429-1983
ISO_IR_C1(77,(-1), 0x43)
    // 1983-10-01
    // C1: ESC \x22 \x43
    ISO_IR_C1_DATA(
        0, //PAD,
        0, //HOP,
        0, //BPH,
        0, //NBH,
        /*
        Index

        IND is a format effector which causes the active position to be
        moved to the corresponding character position of the following
        line.
        */
        IND,
        /*
        Next Line

        NEL is a format effector which causes the active position to be
        moved to the first character position of the following line.
        */
        NEL,
        /*
        Start of Selected Area

        SSA indicates that the active position is the first of a string of
        character positions, the contents of which are eligible to be
        transmitted in the form of a data stream or transferred to an
        auxiliary input/output device. The end of this string is indicated
        by END OF SELECTED AREA (ESA). The string of characters actually
        transmitted or transferred depends on the setting of the GUARDED
        AREA TRANSFER MODE and on any guarded areas established by START OF
        PROTECTED AREA (SPA) or DEFINE AREA QUALIFICATION (DAQ).
        */
        SSA,
        /*
        End of Selected Area

        ESA indicates that the active position is the last of a string of
        character positions, the contents of which are eligible to be
        transmitted in the form of a data stream or transferred to an
        auxiliary input/output device. The beginning of this string is
        indicated by START OF SELECTED AREA (SSA).
        */
        ESA,
        /*
        Horizontal Tabulation Set

        HTS is a format effector which causes a horizontal tabulation stop
        to be set at the active position.

        The number of lines affected depends on the setting of the
        TABULATION STOP MODE.
        */
        HTS,
        /*
        Horizontal Tabulation with Justification

        HTJ is a format effector which causes the contents of the string of
        character positions between the the preceding horizontal tabulation
        stop and the active position to be shifted forward to the following
        horizontal tabulation stop. The active position is also moved to
        the following horizontal tabulation stop. The character positions
        between the preceding horizontal tabulation stop and the beginning
        of the shifted string are erased.
        */
        HTJ,
        /*
        Vertical Tabulation Set

        VTS is a format effector which causes a vertical tabulation stop to
        be set at the active line.
        */
        VTS,
        /*
        Partial Line Down

        PLD is a format effector which causes the active position to be
        moved to the corresponding character position of an imaginary line
        with a partial vertical offset. This offset should be sufficient
        either to image the following characters as subscripts until the
        first following occurence of PARTIAL LINE UP (PLU) in the data
        stream or, if the immediately preceding character is imaged as a
        superscript to restore subsequent imaging of characters to the
        active line.

        Any interaction between PLD and vertical format effectors other
        than PLU are not defined by ISO 6429.
        */
        PLD,
        /*
        Partial Line Up

        PLU is a format effector which causes the active position to be
        moved to the corresponding character position of an imaginary line
        with a partial vertical offset. This offset should be sufficient
        either to image the following characters as superscripts until the
        first following occurence of PARTIAL LINE DOWN (PLD) in the data
        stream or, if the immediately preceding character is imaged as a
        subscript to restore subsequent imaging of characters to the
        active line.

        Any interaction between PLU and vertical format effectors other
        than PLD are not defined by ISO 6429.
        */
        PLU,
        /*
        Reverse Index

        RI is a format effector which causes the active position to be
        moved to the corresponding character position of the preceding
        line.
        */
        RI,
        /*
        Single Shift Two

        SS2 alters the meaning of the single bit combination following it.
        That bit combination must be one of those from columns 2 to 7
        except 2/0 and 7/15. The meaning of the bit combination concerned
        is derived from an appropriately designated G2 graphic set. The use
        of this character is specified in ISO 2022.
        */
        SS2,
        /*
        Single Shift Three

        SS3 alters the meaning of the single bit combination following it.
        That bit combination must be one of those from columns 2 to 7
        except 2/0 and 7/15. The meaning of the bit combination concerned
        is derived from an appropriately designated G3 graphic set. The use
        of this character is specified in ISO 2022.
        */
        SS3,

        /*
        Device Control String

        DCS is the open delimiter of a control string for device control
        use. The command string following consists of a sequence of bit
        combinations in the range 0/8 to 0/13 and 2/0 to 7/14. The control
        string is closed by the terminating delimiter STRING TERMINATOR
        (ST).

        The command string represents either one or more command for the
        receiving device, or one or more status reports from the sending
        device. The purpose and the format of the command string are
        specified by the most recent occurence of IDENTIFY DEVICE CONTROL
        STRING, IDCS (see ISO 6429), if any, or depend on the sending
        and/or receiving device.

        This control function may need to be represented by a graphic
        symbol.
        */
        DCS,
        /*
        Private Use One

        PU1 is reserved for a function without standardized meaning for
        private use as required, subject to the prior agreement of the
        sender and recipient of the data.
        */
        PU1,
        /*
        Private Use Two

        PU2 is reserved for a function without standardized meaning for
        private use as required, subject to the prior agreement of the
        sender and recipient of the data.
        */
        PU2,
        /*
        Set Transmit State

        STS causes the transmit state to be established in the receiving
        device. In this state the transmission of data from the device is
        possible.

        The actual initiation of transmission of data is performed by a
        data communication or input/output interface control procedure
        which is outside the scope of ISO 6429.

        The transmit state is established either by the operation of an
        appropriate button on a keyboard or by SET TRANSMIT STATE in the
        received data stream.
        */
        STS,
        /*
        Cancel Character

        CCH indicates that both the preceding character in the data stream,
        if it is a graphic character (represented by one or more bit
        combinations) including SPACE, and the control function CCH itself
        are to be ignored for further interpretation of the data stream. If
        the character preceding CCH is a control function or part of a
        coded control function, the effect of CCH is not defined by ISO
        6429.
        */
        CCH,
        /*
        Message Waiting

        MW causes a message waiting indicator to be set in the receiving
        device. An appropriate acknowledgment to the receipt of MW may be
        given by DEVICE STATUS REPORT, DSR (see ISO 6429).
        */
        MW,
        /*
        Start of Guarded Protected Area

        SPA indicates that the active position is the first of a string of
        character positions, the contents of which are protected against
        manual alteration and, guarded against transmission or transfer,
        and may be protected against erasure, depending on the setting of
        ERASURE MODE. The end of this string is indicated by END OF GUARDED
        PROTECTED AREA (EPA).
        */
        SPA,
        /*
        End of Guarded Protected Area

        EPA indicates that the active position is the first of a string of
        character positions, the contents of which are protected against
        manual alteration, are guarded against transmission or transfer,
        and may be protected against erasure, depending on the setting of
        ERASURE MODE. The beginning of this string is indicated by START OF
        GUARDED PROTECTED AREA (SPA).
        */
        EPA,
        0, //SOS,
        0, //SGCI,
        0, //SCI,
        /*
        Control Sequence Introducer

        CSI is the first character of a control sequence.
        */
        CSI,
        /*
        String Terminator

        ST is the closing delimiter of a string opened by APPLICATION
        PROGRAM COMMAND (APC), DEVICE CONTROL STRING (DCS), OPERATING
        SYSTEM COMMAND (OSC), or PRIVACY MESSAGE (PM).

        This control function may need to be represented by a graphic
        symbol.
        */
        ST,
        /*
        Operating System Command

        OSC is the opening delimiter of a control sequence for operating
        system use. The command string following consists of a sequence of
        bit combinations in the range 0/8 to 0/13 and 2/0 to 7/14. The
        control string is closed by the terminating delimiter STRING
        TERMINATOR (ST). The interpretation of the command string depends
        on the relevant operating system.

        This control function may need to be represented by a graphic
        symbol.
        */
        OSC,
        /*
        Privacy Message

        PM is the opening delimiter of a control sequence for privacy
        message use. The command string following consists of a sequence of
        bit combinations in the range 0/8 to 0/13 and 2/0 to 7/14. The
        control string is closed by the terminating delimiter STRING
        TERMINATOR (ST). The interpretation of the command string depends
        on the relevant privacy discipline.

        This control function may need to be represented by a graphic
        symbol.
        */
        PM,
        /*
        Application Program Command

        APC is the opening delimiter of a control sequence for an
        application program use. The command string following consists of a
        sequence of bit combinations in the range 0/8 to 0/13 and 2/0 to
        7/14. The control string is closed by the terminating delimiter
        STRING TERMINATOR (ST). The interpretation of the command string
        depends on the relevant application program.

        This control function may need to be represented by a graphic
        symbol.
        */
        APC,
    )
// Minimum C1 Set for ISO 4873
ISO_IR_C1(105,(-1), 0x47)
    // 1985-08-01
    // C1: ESC \x22 \x47
    ISO_IR_C1_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        SS2,
        SS3,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    )
// Teletex Supplementary Set of Control Functions CCITT Rec. T.61
ISO_IR_C1(107,(-1), 0x48)
    // 1985-08-01
    // C1: ESC \x22 \x48
    ISO_IR_C1_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        PLD,
        PLU,
        0,
        0,
        0,

        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        CSI,
        0,
        0,
        0,
        0,
    )
// Upward Compatible Version of ISO 6630 (Registration 67)
ISO_IR_C1(124,(0), 0x42)
    // 1986-02-01
    // C1: ESC \x26 \x40 ESC \x22 \x42
    ISO_IR_C1_DATA(
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        CUS,
        NSB,
        NSE,
        0,
        PLD,
        PLU,
        0,
        0,
        0,

        0,
        EAB,
        EAE,
        0,
        0,
        SIB,
        SIE,
        SSB,
        SSE,
        0,
        0,
        0,
        KWB,
        KWE,
        PSB,
        PSE,
    )
// Supplementary Control Set of Data Syntax I of CCITT Rec. T.101
ISO_IR_C1(133,(-1), 0x44)
    // 1987-07-31
    // C1: ESC \x22 \x44
    ISO_IR_C1_DATA(
        /*
        Black Foreground

        This control character invokes black or the 0th colour of the Look
        Up Table as a foreground colour.
        */
        CCITT_BKF,
        /*
        Red Foreground

        This control character invokes red or the 1st colour of the Look Up
        Table as a foreground colour.
        */
        CCITT_RDF,
        /*
        Green Foreground

        This control character invokes green or the 2nd colour of the Look
        Up Table as a foreground colour.
        */
        CCITT_GRF,
        /*
        Yellow Foreground

        This control character invokes yellow or the 3rd colour of the Look
        Up Table as a foreground colour.
        */
        CCITT_YLF,
        /*
        Blue Foreground

        This control character blue or the 4th colour of the Look Up Table
        as a foreground colour.
        */
        CCITT_BLF,
        /*
        Magenta Foreground

        This control character invokes magenta or the 5th colour of the
        Look Up Table as a foreground colour.
        */
        CCITT_MGF,
        /*
        Cyan Foreground

        This control character invokes cyan or the 6th colour of the Look
        Up Table as a foreground colour.
        */
        CCITT_CNF,
        /*
        White Foreground

        This control character invokes white or the 7th colour of the Look
        Up Table as a foreground colour.
        */
        CCITT_WHF,
        /*
        Small Size

        This control character reduces the width and the height to that set
        by NSZ.
        */
        CCITT_SSZ,
        /*
        Medium Size

        This control character reduces the width to half that set by NSZ.

        The character height is the same as that set by NSZ.
        */
        CCITT_MSZ,
        /*
        Normal Size

        This control character sets the width and height to that of the
        character block specified by the P-TEXT command.
        */
        CCITT_NSZ,
        /*
        Size Control

        This control character specifies the height and width of a
        character by means of a one-byte parameter following it.

        The significance of the parameter values is specified in Rec.
        T.101.
        */
        CCITT_SZX,
        0,
        0,
        /*
        Cursor On

        This control character makes the cursor display visible.
        */
        CCITT_CON,
        /*
        Cursor Off

        This control character turns off the cursor display.
        */
        CCITT_COF,

        /*
        Background or Foreground Colour

        This control character specifies a full intensity background
        colour, a reduced intensity foreground colour or a reduced
        intensity background colour by means of a one-byte parameter
        following it.

        The significance of the parameter values is specified in Rec.
        T.101.
        */
        CCITT_COL,
        /*
        Flashing Control

        This control character specifies flashing attributes by means of a
        one-byte parameter following it.

        The significance of the parameter values is specified in Rec.
        T.101.
        */
        CCITT_FLC,
        /*
        Conceal Display Control

        This control character provides the conceal display attribute. When
        the conceal display attribute is applied, character and DRCS are
        made invisible. The character position takes ordinary advance.
        Concealed characters are made visible by the specified user action.
        CDC specifies conceal display attributes by means of a one-byte
        parameter following it.

        The significance of the parameter values is specified in Rec.
        T.101.
        */
        CCITT_CDC,
        0,
        0,
        /*
        Photo Macro

        This control character provides the capability for a string of any
        presentation level characters and commands (including transparent
        mode commands) to be stored within the terminal and to be
        subsequently executed via a single photo macro call. It is followed
        by a one-byte parameter. Each macro is identified by a value (from
        2/0 to 7/15) of this parameter. The 96 photo macros are named PM0
        to PM95.

        The significance of the parameter values is specified in Rec.
        T.101.
        */
        CCITT_P_MACRO,
        0,
        0,
        /*
        Repeat Control

        This control character causes the following G set character, if the
        following character is a non-spacing character, both the
        non-spacing character and the next character, to be displayed a
        number of times specified by a numeric parameter following it. The
        byte representing this parameter shall be from columns 4 to 7. The
        repeat count is given by the binary number comprising bits b6 to
        b1, b6 being the MSB. If the byte following RPC does not belong to
        columns 4 to 7, RPC is not executed.

        Parameter value 4/0 means repeat to end of line.
        */
        CCITT_RPC,
        /*
        Stop Lining [swapped in IR]

        This control character resets the lining attribute.
        */
        CCITT_SPL,
        /*
        Start Lining [swapped in IR]

        This control character applies the lining attribute. Characters are
        displayed with an underline whereas mosaic patterns are displayed
        in separate font.
        */
        CCITT_STL,
        0,
        0,
        0,
        /*
        Unprotected

        This control character renders the following characters
        unprotected.
        */
        CCITT_UNP,
        /*
        Protected

        This control character renders the following characters protected.
        */
        CCITT_PRT,
    )
// Supplementary Control Set of Data Syntax III of CCITT Rec. T.101
ISO_IR_C1(136,(-1), 0x46)
    // 1987-07-31
    // C1: ESC \x22 \x46
    ISO_IR_C1_DATA(
        /*
        Define Macro

        This control character defines a macro.  The bit combinations
        following this control character shall be in the range 2/0 to 7/15
        and identifies the macro being defined. All characters subsequent
        to this control function are stored (but not executed) within the
        receiving device under the specified macro name. Definition of the
        macro terminates upon receipt of one of the following C1 control
        characters: DEFINE MACRO, DEFP MACRO, DEFT MACRO, DEF DRCS, DEF
        TEXTURE, or END. The terminating control character (preceded by ESC
        in a 7-bit environment) is not stored as part of the macro. If the
        bit combination following the DEFINE MACRO is not in the specified
        range. the entire command (i.e. the C1 control and the following
        bit combination which is out of the range) is in error and is
        executed as a null operation.

        During the definition of a macro, a reference to a macro results in
        the storage of that reference only, not the expansion. The
        definition of a macro replaces any previously existing macro under
        the same name. A macro may be longer or shorter than the previously
        existing macro that it replaces. A null macro definition, i.e. a
        macro definition in which there are no characters between the macro
        name and the terminating C1 control character (preceded by ESC in a
        7-bit environment) causes that macro to be deleted. Definition of a
        macro is independent of whether the macro set is invoked or not.
        */
        CCITT_DEFM,
        /*
        Define P-Macro

        The operation of this control character is identical with that of
        DEFINE MACRO, except that incominb characters that make up the
        macro definition are simultaneously executed and stored. A macro is
        considered to be undefined during definition until the definition
        is terminated. Therefore, if a DEFP MACRO contains a reference to
        itself, or if it references another macro which references the one
        being defined, the reference to the macro being defined is executed
        as a null operation.
        */
        CCITT_DEFP,
        /*
        Define Transmit-Macro

        This control character defines a transmit-macro. Transmit-macros,
        when called, are not executed, but are transmitted in their
        entirety to the host computer or to a local application process.

        Transmit-macros are defined and deleted in a manner similar to that
        described for normal macros, and they share the same 96 macro
        names.
        */
        CCITT_DEFT,
        /*
        Define DRCS

        This control character starts the downloading operation for one of
        the DRCS characters, of which a total of 96 are permitted. The bit
        combination following this control character shall be in the range
        2/0 to 7/15 and identifies the DRCS character being defined. The
        DRCS downloading command is terminated when an END, DEFINE MACRO,
        DEFP MACRO, DEFT MACRO, DEF TEXTURE or another DEF DRCS is
        received.

        When the current DRCS downloading operation is terminated by
        another DEF DRCS, the next character of the DRCS G-set (i.e. in the
        circular sequence 2/0, 2/1, ... 2/15, 3/0, 3/1, ... 7/14, 7/15,
        2/0, 2/1 ...) is defined by the presentation layer bit combination
        immediately following this new DEF DRCS. If the bit combination
        following the DEF DRCS control character is not in the range 2/0 to
        7/15 and the DEF DRCS control function is not terminating a
        previous DEF DRCS, the entire command (i.e. the C1 control
        character and the following bit combination which is out of range)
        is in error and is executed as a null operation.

        The presentation layer bit combination defining the DRCS control
        character shall be executed upon being received. It is executed
        within the unit screen but is not displayed in the display area.
        The effect of this execution is to modify a separate storage buffer
        that is used for any subsequent display of the DRCS control
        character.

        The aspect ratio of the storage buffer shall be the same as that of
        the character field dimensions when the DEF DRCS control character
        is received. The lower left corner of the buffer shall coincide
        with the lower left corner of the unit screen. The larger buffer
        dimension shall coincide with the entire corresponding axis of the
        unit screen.
        */
        CCITT_DEFD,
        /*
        Define Texture

        This control character defines one of the four programmable texture
        masks.

        The bit combination following this control character shall be one
        of the following 4/1, 4/2, 4/3, 4/4, that causes mask A, B, C or D,
        respectively, to be defined. Any existing texture pattern
        associated with the specified mask is deleted. The mask is cleared
        by terminating the command at this point. If a presentation layer
        bit combination follows, it describes the texture mask in the same
        manner as the DRCS control character, except that the texture mask
        size is used rather than the character field size. The DEF TEXTURE
        is terminated when an END, DEF MACRO, DEFP MACRO, DEFT MACRO, DEF
        DRCS, or another DEF TEXTURE is received. If the bit combination
        following the DEF TEXTURE control character is not in the range 4/1
        to 4/4, the entire command (i.e. the C1 control character and the
        bit combination which is out of range) is in error and is executed
        as a null operation.
        */
        CCITT_DEFX,
        /*
        End

        This control character terminates the current DEF MACRO, DEFP
        MACRO, DEFT MACRO, DEF DRCS, or DEF TEXTURE operation. It is also
        used in the transmission of data in an unprotected field.
        */
        CCITT_END,
        /*
        Repeat

        This control character causes the immediately preceding byte to be
        repeated a specific number of additional times if the byte is SPACE
        or any spacing character from the primary, supplementary, DRCS, or
        mosaic sets. The bit combination following the REPEAT control shall
        be interpreted as the repeat count. This repeat count character
        shall be in the range 4/0 to 7/15; otherwise the command is in
        error and shall be executed as a null operation, and the count
        character is executed as a character from columns 0 to 3 or 8 to
        11.
        */
        CCITT_REP,
        /*
        Repeat to End of Line

        This control character causes the immediately preceding byte to be
        repeated until the last character position along the current
        character path is reached if the byte is SPACE or any spacing
        character from the primary, supplementary, DRCS, or mosaic sets.
        Otherwise the command is in error and shall be executed as a null
        operation. If the full character field corresponding to the text
        cursor lies entirely within the active field when this command is
        encountered, then characters are repeated only up to the last
        character position along the current character path within the
        active field.
        */
        CCITT_REPE,
        /*
        Reverse Video
        */
        CCITT_REVV,
        /*
        Normal Video
        */
        CCITT_NORV,
        /*
        Small Text

        This control character causes the dimensions of the character field
        to be set to dx = 1/80 and dy = 5/128, consistent with the physical
        resolution.
        */
        CCITT_SMTX,
        /*
        Medium Text

        This control character causes the dimensions of the character field
        to be set to dx = 1/32 and dy = 3/64, consistent with the physical
        resolution.
        */
        CCITT_METX,
        /*
        Normal Text

        This control character causes the dimensions of the character field
        to be set to dx = 1/40 and dy = 5/128, consistent with the physical
        resolution.
        */
        CCITT_NOTX,
        /*
        Double Height

        This control character causes the dimensions of the character field
        to be set to dx = 1/40 and dy = 5/64, consistent with the physical
        resolution.
        */
        CCITT_DBH,
        /*
        Blink Start
        */
        CCITT_BSTA,
        /*
        Double Size

        This control character causes the dimensions of the character field
        to be set to dx = 1/20 and dy = 5/64, consistent with the physical
        resolution.
        */
        CCITT_DBS,

        /*
        Protect

        This control character causes all unprotected fields of which any
        portion lies within the active field to be made protected.
        */
        CCITT_PRO,
        /*
        EDC One

        This control character is reserved for future standardization, and
        is executed as null operation.
        */
        CCITT_EDC1,
        /*
        EDC Two

        This control character is reserved for future standardization, and
        is executed as null operation.
        */
        CCITT_EDC2,
        /*
        EDC Three

        This control character is reserved for future standardization, and
        is executed as null operation.
        */
        CCITT_EDC3,
        /*
        x
        EDC Four

        This control character is reserved for future standardization, and
        is executed as null operation.
        */
        CCITT_EDC4,
        /*
        Word Wrap On

        This control character causes the receiving device to enter word
        wrap mode. In this mode, subsequently received alphanumeric text is
        buffered into words. A word is displayed on the current line only
        if the entire buffered word fits into the space remaining on the
        current line within the unit screen (or within the active field,
        should the full character field corresponding to the text cursor
        lie entirely within the active field). If the word does not fit
        into the space remaining on the current line, an automatic APR APD
        is executed and the word is displayed. The character SPACE should
        be dropped if the last word on the line is terminated with a SPACE
        that does not fit on that line. A word is defined as being an
        accumulation of characters between SPACE characters.

        Words consisting entirely of alphabetic characters and one or more
        of the following embedded (i.e. not at the beginning or end of the
        word) special terminating characters: EXCLAMATION MARK, QUOTATION
        MARK, DOLLAR SIGN, PERCENT SIGN, LEFT PARENTHESIS, RIGHT
        PARENTHESIS, LEFT SQUARE BRACKET, RIGHT SQUARE BRACKET, LESS-THAN
        SIGN, GREATER-THAN SIGN, LEFT CURLY BRACKET, RIGHT CURLY BRACKET,
        CIRCUMFLEX ACCENT, ASTERISK, PLUS SIGN, MINUS SIGN, SOLIDUS, COMMA,
        FULL STOP, COLON, SEMICOLON, LOW LINE and TILDE may be broken
        between the special terminating character and the following
        character, which causes as much of the word to fit on the current
        line as possible. All other words shall be kept together on a single line.

        A word is also terminated by a mosaic set character, a PDT, and
        C-set character defined at the presentation layer except SO, SI,
        SS2 and SS3; or any character that causes the length of the word to
        be equal to the maximum length of a line.
        */
        CCITT_WWON,
        /*
        Word Wrap Off

        This control character causes the receiving device to exit from
        word wrap mode. In this mode all text is broken on character
        boundaries whenever an automatic APR and APD are executed.
        */
        CCITT_WWOF,
        /*
        Scroll On

        In this mode, a subsequently received APD or APU control character
        or an automatic APR APD that would advance any part of the cursor
        out of the display area (or the active field, should the full
        characte rfield corresponding to the cursor lie entirely within the
        active field) causes the entire display within the area or field to
        be scrolled. Scrolling occurs pixel-by-pixel in a direction
        perpendicular to the character path and far enough to bring the
        next intended character location just into the area or field. The
        colour of background pixels scrolled into the area or field in
        nominal black in colour modes 0 and 1 and the background colour in
        colour mode 2.
        */
        CCITT_SCON,
        /*
        Scroll Off

        In this mode an APD or APU command or an automatic APR APD that
        would advance any part of the cursor out of the display area (or
        the active field, should the full character field corresponding to
        the cursor lie entirely within the active field), causes the cursor
        to be repositioned to the opposite edge of the area or field such
        that the character field so defined lies entirely within the area
        or field.
        */
        CCITT_SCOF,
        /*
        Underline Start

        This control character causes the receiving device to enter
        underline mode. In this mode, all subsequently received primary,
        supplementary, DRCS characters, and the SPACE character have a line
        added to their patterns. The line appears in the character field
        starting at the character field origin and extending across the
        entire width (dx dimension) of the character field, but not across
        the space between character fields when the intercharacter spacing
        is greater than one. Its thickness is determined by the vertical
        dimensions (dy) of the logical pel size. The underline mode also
        causes subsequently received mosaic characters to be displayed in
        separate mode. Mosaic characters are not underlined.
        */
        CCITT_USTA,
        /*
        Underline Stop
        */
        CCITT_USTO,
        /*
        Flash Cursor

        This control character turns on the cursor display and causes it to
        flash intermittently and may enable user input and user activation
        of linked macros.
        */
        CCITT_FLC,
        /*
        Steady Cursor

        This control character turns on the cursor display, which remains
        constantly visible and may enable user input and user activation of
        linked macros.
        */
        CCITT_STC,
        /*
        Cursor Off

        This control character causes the cursor to be made invisible. The
        cursor still functions and moves as usual; it is just not visible
        while in this mode.
        */
        CCITT_COF,
        /*
        Blink Stop
        */
        CCITT_BSTO,
        /*
        Unprotect

        Unprotected fields are rectangular areas on the display into which
        the user may enter or edit data for possible subsequent
        transmission.

        By default, the entire unit screen is protected; i.e. it is not
        possible for the user to enter or alter data that displays on the
        unit screen. The UNPROTECT control character causes the active
        field to be made unprotected and the user may subsequently enter or
        locally edit data within that field. Any number of unprotected
        fields may be defined by defining an active field via a FIELD
        command and then issuing the UNPROTECT control character. Should an
        UNPROTECT result in unprotecting a field that partially or wholly
        lies within an already unprotected field, the already unprotected
        field is made protected (without affecting the displayed contents)
        before the new field is made unprotected.

        Data that are received and displayed in an unprotected field after
        it has been unprotected, and when that unprotected field coincides
        with the active field, can also be subsequently edited by the user.
        When the user initiates a transmission, the information in the
        unprotected field(s) is transmitted. The FIELD command containing
        the coordinates of the origin of the unprotected field as well as
        its dimensions is transmitted, followed by the contents of the
        field, and then by the END control character. When more than one
        unprotected field is transmitted, the order of transmission is from
        the top to the bottom of the unit screen, using field origin points
        as a reference If two or more field origins have the same Y
        coordinate, the order of transmission is leftmost first.
        */
        CCITT_UNP,
    )

// DISABLE MANUAL INPUT (DMI) ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(32,(-1), 0x60)
    // 1976-12-30
    // Single: ESC \x60
    /*
        Disable Manual Input

        A control function which causes all or part of the manual
        input facilities of the receiving device to be disabled.
    */
    ISO_IR_SINGLE_DATA(DMI)
// INTERRUPT (INT), ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(33,(-1), 0x61)
    // 1976-12-30
    // Single: ESC \x61
    /*
        Interrupt

        A control function which indicates to the receiving
        device that the current process is to be interrupted
        and that an agreed procedure is to be initiated.
    */
    ISO_IR_SINGLE_DATA(INT)
// ENABLE MANUAL INPUT (EMI), ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(34,(-1), 0x62)
    // 1976-12-30
    // Single: ESC \x62
    /*
        Enable Manual Input

        A control function which enables the manual input
        facilities of the receiving device to be used.
    */
    ISO_IR_SINGLE_DATA(EMI)
// RESET TO INITIAL STATE (RIS), ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(35,(-1), 0x63)
    // 1976-12-30
    // Single: ESC \x63
    /*
        Reset to Initial State

        A control function which resets a device to its initial
        state, i.e. the state it has after it is switched on.
        This may imply, if applicable: remove tabulation stops,
        remove input areas, reset graphic rendition, erase all
        positions, move active position to the first character
        position of the first line.
    */
    ISO_IR_SINGLE_DATA(RIS)
// LOCKING-SHIFT TWO (LS2), ISO 2022, ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(62,(-1), 0x6e)
    // 1982-08-20
    // Single: ESC \x6e
    /*
        Locking Shift Two

        A code extension control function which is used in conjunction with
        other locking shift functions as specified in ISO 2022 to extend
        the graphic character set of a 7-bit or 8-bit code. LS2 is a
        locking shift function which invokes the set of graphic characters
        currently designated as a G2 set into positions 2/1 to 7/14 of a
        7-bit table or positions 02/01 to 07/14 of an 8-bit table.
    */
    ISO_IR_SINGLE_DATA(LS2)
// LOCKING-SHIFT THREE (LS3) ISO 2022, ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(63,(-1), 0x6f)
    // 1982-08-20
    // Single: ESC \x6f
    /*
        Locking Shift Three

        A code extension control function which is used in conjunction with
        other locking shift functions as specified in ISO 2022, to extend
        the graphic character set of a 7-bit or 8-bit code. LS3 is a
        locking shift function which invokes the set of graphic characters
        currently designated as a G3 set into positions 2/1 to 7/14 of a
        7-bit table or positions 02/01 to 07/14 of an 8-bit table.
    */
    ISO_IR_SINGLE_DATA(LS3)
// LOCKING-SHIFT THREE RIGHT(LS3R), ISO 2022, ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(64,(-1), 0x7c)
    // 1982-08-20
    // Single: ESC \x7c
    /*
        Locking Shift Three Right

        A code extension control function which is used in conjunction with
        other lcoking shift functions as specified in ISO 2022, to extend
        the graphic character set of an 8-bit code. LS3R is a locking shift
        function which invokes the set of graphic characters currently
        designated as a G3 set into positions 10/01 to 15/14.

        NOTE - Although LS3R is not intended to be used in a 7-bit code, it
        may be encountered in a 7-bit environment as a result of
        transformation of data originating in an 8-bit environment. It then
        invokes the set of graphic characters currently designated as a G3
        set, into positions 2/1 to 7/14.
    */
    ISO_IR_SINGLE_DATA(LS3R)
// LOCKING-SHIFT TWO RIGHT(LS2R), ISO 2022, ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(65,(-1), 0x7d)
    // 1982-08-20
    // Single: ESC \x7d
    /*
        Locking Shift Two Right

        A code extension control function which is used in conjunction with
        other lcoking shift functions as specified in ISO 2022, to extend
        the graphic character set of an 8-bit code. LS2R is a locking shift
        function which invokes the set of graphic characters currently
        designated as a G2 set into positions 10/01 to 15/14.

        NOTE - Although LS2R is not intended to be used in a 7-bit code  it
        may be encountered in a 7-bit environment as a result of
        transformation of data originating in an 8-bit environment. It then
        invokes the set of graphic characters currently designated as a G2
        set, into positions 2/1 to 7/14.
    */
    ISO_IR_SINGLE_DATA(LS2R)
// LOCKING-SHIFT ONE RIGHT (LS1R), ISO 2022, ECMA-48 (1986), ISO 6429 : 1988
ISO_IR_SINGLE(66,(-1), 0x7e)
    // 1982-08-20
    // Single: ESC \x7e
    /*
        Locking Shift One Right

        A code extension control function which is used in conjunction with
        other lcoking shift functions as specified in ISO 2022, to extend
        the graphic character set of an 8-bit code. LS1R is a locking shift
        function which invokes the set of graphic characters currently
        designated as a G1 set into positions 10/01 to 15/14.

        NOTE - Although LS1R is not intended to be used in a 7-bit code, it
        may be encountered in a 7-bit environment as a result of
        transformation of data originating in an 8-bit environment. It then
        invokes the set of graphic characters currently designated as a G1
        set, into positions 2/1 to 7/14.
    */
    ISO_IR_SINGLE_DATA(LS1R)
// CODING METHOD DELIMITER (CMD), ECMA-48 (1991), ISO/IEC 6429:1992
ISO_IR_SINGLE(189,(-1), 0x64)
    // 1994-08-10
    // Single: ESC \x64
    /*
        Coding Method Delimiter

        A control function which is used to delimit a string of data coded
        according to ISO/IEC 2022 and to switch to a general level of
        control
    */

/// Coding systems with Standard return
    // standard return = ESC \x25 \x40
// Syntax of the North American Videotex/Teletex Presentation Level Protocol (NAPLPS), CSA T 500-1983
ISO_IR_SWITCH_RETURN(108,(-1), 0x41)
    // 1985-08-01
    // Single: ESC \x25 \x41
    ISO_IR_SWITCH_RETURN_DATA(naplps)
// Data Syntax I of CCITT Rec.T.101
ISO_IR_SWITCH_RETURN(131,(-1), 0x43)
    // 1987-07-31
    // Single: ESC \x25 \x43
    ISO_IR_SWITCH_RETURN_DATA(t101_ds1)
// Data Syntax II of CCITT Rec. T.101
ISO_IR_SWITCH_RETURN(145,(-1), 0x44)
    // 1988-05-01
    // Single: ESC \x25 \x44
    ISO_IR_SWITCH_RETURN_DATA(t101_ds2)
// Photo-Videotex Data Syntax of CCITT Rec. T.101
ISO_IR_SWITCH_RETURN(160,(-1), 0x45)
    // 1992-07-13
    // Single: ESC \x25 \x45
    ISO_IR_SWITCH_RETURN_DATA(t101_photo)
// Audio Data Syntax of CCITT Rec. T.101
ISO_IR_SWITCH_RETURN(161,(-1), 0x46)
    // 1992-07-13
    // Single: ESC \x25 \x46
    ISO_IR_SWITCH_RETURN_DATA(t101_audio)
// UCS Transformation Format One (UTF-1)
ISO_IR_SWITCH_RETURN(178,(-1), 0x42)
    // 1993-01-21
    // Single: ESC \x25 \x42
    ISO_IR_SWITCH_RETURN_DATA(utf1)
// Videotex Enhanced Man Machine Interface (VEMMI) Data Syntax of ITU-T Rec. T.107
ISO_IR_SWITCH_RETURN(188,(-1), 0x48)
    // 1995-01-16
    // Single: ESC \x25 \x48
    ISO_IR_SWITCH_RETURN_DATA(vemmi)
// UTF-8 without implementation level
ISO_IR_SWITCH_RETURN(196,(-1), 0x47)
    // 1996-04-22
    // Single: ESC \x25 \x47
    ISO_IR_SWITCH_RETURN_DATA(utf8)

/// Coding Systems without Standard return
// Virtual Terminal service Transparent Set
ISO_IR_SWITCH_NORETURN(125,(-1), 0x42)
    // 1986-11-30
    // Single: ESC \x25 \x2f \x42
    ISO_IR_SWITCH_NORETURN_DATA(iso_osi_vts)
// ISO/IEC 10646:1993, UCS-2, Level 1
ISO_IR_SWITCH_NORETURN(162,(-1), 0x40)
    // 1992-07-13
    // Single: ESC \x25 \x2f \x40
    ISO_IR_SWITCH_NORETURN_DATA(ucs2_level1)
// ISO/IEC 10646:1993, UCS-4, Level 1
ISO_IR_SWITCH_NORETURN(163,(-1), 0x41)
    // 1992-07-13
    // Single: ESC \x25 \x2f \x41
    ISO_IR_SWITCH_NORETURN_DATA(ucs4_level1)
// ISO/IEC 10646:1993, UCS-2, Level 2
ISO_IR_SWITCH_NORETURN(174,(-1), 0x43)
    // 1993-01-21
    // Single: ESC \x25 \x2f \x43
    ISO_IR_SWITCH_NORETURN_DATA(ucs2_level2)
// ISO/IEC 10646:1993, UCS-4, Level 2
ISO_IR_SWITCH_NORETURN(175,(-1), 0x44)
    // 1993-01-21
    // Single: ESC \x25 \x2f \x44
    ISO_IR_SWITCH_NORETURN_DATA(ucs4_level2)
// ISO/IEC 10646:1993, UCS-2, Level 3
ISO_IR_SWITCH_NORETURN(176,(-1), 0x45)
    // 1993-01-21
    // Single: ESC \x25 \x2f \x45
    ISO_IR_SWITCH_NORETURN_DATA(ucs2_level3)
// ISO/IEC 10646:1993, UCS-4, Level 3
ISO_IR_SWITCH_NORETURN(177,(-1), 0x46)
    // 1993-01-21
    // Single: ESC \x25 \x2f \x46
    ISO_IR_SWITCH_NORETURN_DATA(ucs4_level3)
// UTF-8 Level 1
ISO_IR_SWITCH_NORETURN(190,(-1), 0x47)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x47
    ISO_IR_SWITCH_NORETURN_DATA(utf8_level1)
// UTF-8 Level 2
ISO_IR_SWITCH_NORETURN(191,(-1), 0x48)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x48
    ISO_IR_SWITCH_NORETURN_DATA(utf8_level2)
// UTF-8 Level 3
ISO_IR_SWITCH_NORETURN(192,(-1), 0x49)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x49
    ISO_IR_SWITCH_NORETURN_DATA(utf8_level3)
// UTF-16 Level 1
ISO_IR_SWITCH_NORETURN(193,(-1), 0x4a)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x4a
    ISO_IR_SWITCH_NORETURN_DATA(utf16_level1)
// UTF-16 Level 2
ISO_IR_SWITCH_NORETURN(194,(-1), 0x4b)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x4b
    ISO_IR_SWITCH_NORETURN_DATA(utf16_level2)
// UTF-16 Level 3
ISO_IR_SWITCH_NORETURN(195,(-1), 0x4c)
    // 1996-04-22
    // Single: ESC \x25 \x2f \x4c
    ISO_IR_SWITCH_NORETURN_DATA(utf16_level3)
// level 1 means simple glyph support
// level 2 means context-aware glyph alternatives
// level 3 means combining characters
