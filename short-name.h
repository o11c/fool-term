#pragma once

/*
    Definitions from the following standards:

    CCITT T.51 = ISO 6937
    CCITT T.61
    CCITT T.101
    (and apparently ISO 10367, but I don't have a copy)

    Each short-name consists of 2 letters, followed by 2-4 digits.

    A[A-Z]: arabic letters
    B?: thai (no known source table - possibly IBM specific?)
    C?: control functions (omitted by design, use ISO-IR tables instead?)
    DA: arabic spacing version of combining marks
    DG: drawing characters (conflicting entries use DG99xx)
    G[A-Z]: greek letters
    H[A-Z]: hebrew letters (note slight conflict with hiragana)
    HK: japanese hiragana (no usable source table, plus it would slightly conflict with hebrew)
    JA: japanese katakana
    JK: japanese kanji pictoral (no usable source table)
    JS: japanese kanji special (no usable source table)
    K[A-Z]: cyrillic letters
    L[A-Z]: lattin letters
    MG: mosaic block graphics
    MS: mosaic general smooth graphics
    ND: numeric digit
    NF: numeric fraction
    NS: numeric superscript
    O? korean (no known source table - possibly IBM specific?)
    SA: symbol, arithmetic
    SC: symbol, currency
    SD: symbol, diacritic
    SG: mosaic subcell smooth graphics
    SM: symbol, general
    SP: symbol, punctuation
*/

#define unavailable(xx) 0
//#define unavailable(xx) ((char16_t)(0xE000 | xx))

#define AA01 'َ'
#define AA31 'ً'
#define AB01 u'ب'
#define AD01 u'د'
#define AD29 u'ض'
#define AD61 u'ذ'
#define AF01 u'ف'
#define AG23 u'ج'
#define AG61 u'غ'
#define AH01 u'ه'
#define AH29 u'ح'
#define AH61 u'ء'
#define AH61 u'خ'
#define AI01 'ِ'
#define AI31 'ٍ'
#define AK01 u'ك'
#define AL01 u'ل'
#define AM01 u'م'
#define AN01 u'ن'
#define AQ01 u'ق'
#define AR01 u'ر'
#define AS01 u'س'
#define AS21 u'ش'
#define AS29 u'ص'
#define AT01 u'ت'
#define AT29 u'ط'
#define AT61 u'ث'
#define AU01 'ُ'
#define AU31 'ٌ'
#define AW01 u'و'
#define AX33 u'ا'
#define AY01 u'ي'
#define AZ01 u'ز'
#define AZ29 u'ظ'
#define DA10 u'ﹰ'
#define DA11 u'ﹲ'
#define DA12 u'ﹴ'
#define DA13 u'ﹶ'
#define DA14 u'ﹸ'
#define DA15 u'ﹺ'
#define DA16 u'ﹼ'
#define DA17 u'ﹾ'
#define DG01 u'┷'
#define DG02 u'┯'
#define DG03 u'┝'
#define DG04 u'┥'
#define DG05 unavailable(0x94)
#define DG06 unavailable(0x95)
#define DG07 unavailable(0x96)
#define DG08 unavailable(0x97)
#define DG09 unavailable(0x98)
#define DG10 unavailable(0x99)
#define DG11 unavailable(0x9A)
#define DG12 unavailable(0x9B)
#define DG13 u'┿'
#define DG14 u'│'
#define DG15 u'─'
#define DG16 u'┌'
#define DG17 u'┐'
#define DG18 u'└'
#define DG19 u'┘'
#define DG20 u'├'
#define DG21 u'┤'
#define DG22 u'┬'
#define DG23 u'┴'
#define DG24 u'┼'
#define DG25 unavailable(0xA8)
#define DG26 unavailable(0xA9)
#define DG27 unavailable(0xAA)
#define DG28 unavailable(0xAB)
#define DG29 u'⚫'
#define DG30 u'●'
#define DG31 u'○'
#define DG32 unavailable(0xAF)
#define DG33 u'┨'
#define DG34 u'┒'
#define DG35 u'┑'
#define DG36 u'┚'
#define DG37 u'┙'
#define DG38 u'┠'
#define DG39 u'┸'
#define DG40 u'┰'
#define DG41 u'┖'
#define DG42 u'┕'
#define DG43 u'┍'
#define DG44 u'┎'
#define DG45 u'╂'
#define DG46 u'▌'
#define DG47 u'▐'
#define DG48 u'■'
#define DG49 u'█'
#define DG50 u'▄'
#define DG51 u'▀'
#define DG52 u'┃'
#define DG53 u'━'
#define DG54 u'┏'
#define DG55 u'┓'
#define DG56 u'┗'
#define DG57 u'┛'
#define DG58 u'┣'
#define DG59 u'┫'
#define DG60 u'┳'
#define DG61 u'┻'
#define DG62 u'╋'
#define DG63 u'░'
#define DG64 u'▒'
#define DG65 u'▓'
#define DG9933 u'╱'
#define DG9934 u'╲'
#define DG9935 u'┃'
#define DG9936 u'━'
#define DG9937 u'┏'
#define DG9938 u'┓'
#define DG9939 u'┗'
#define DG9940 u'┛'
#define DG9941 u'┣'
#define DG9942 u'┫'
#define DG9943 u'┳'
#define DG9944 u'┻'
#define DG9945 u'╋'
#define DG9946 u'┠'
#define DG9947 u'┨'
#define DG9948 u'┰'
#define DG9949 u'┸'
#define DG9950 u'╂'
#define GA01 u'α'
#define GA02 u'Α'
#define GA11 u'ἀ'
#define GA12 u'Ά'
#define GB01 u'β'
#define GB02 u'Β'
#define GD01 u'δ'
#define GD02 u'Δ'
#define GE01 u'ε'
#define GE02 u'Ε'
#define GE11 u'έ'
#define GE12 u'Έ'
#define GE61 u'η'
#define GE62 u'Η'
#define GE63 u'ή'
#define GE64 u'Ή'
#define GF01 u'φ'
#define GF02 u'Φ'
#define GG01 u'γ'
#define GG02 u'Γ'
#define GH01 u'χ'
#define GH02 u'Χ'
#define GI01 u'ι'
#define GI02 u'Ι'
#define GI11 u'ί'
#define GI12 u'Ί'
#define GI17 u'ϊ'
#define GI18 u'Ϊ'
#define GI33 u'ΐ'
#define GK01 u'κ'
#define GK02 u'Κ'
#define GL01 u'λ'
#define GL02 u'Λ'
#define GM01 u'µ'
#define GM02 u'Μ'
#define GN01 u'ν'
#define GN02 u'Ν'
#define GO01 u'ο'
#define GO02 u'Ο'
#define GO11 u'ό'
#define GO12 u'Ό'
#define GO61 u'ω'
#define GO62 u'Ω'
#define GO63 u'ώ'
#define GO64 u'Ώ'
#define GP01 u'π'
#define GP02 u'Π'
#define GP61 u'ψ'
#define GP62 u'Ψ'
#define GR01 u'ρ'
#define GR02 u'Ρ'
#define GS01 u'σ'
#define GS02 u'Σ'
#define GS61 u'ς'
#define GT01 u'τ'
#define GT02 u'Τ'
#define GT61 u'θ'
#define GT62 u'Θ'
#define GU01 u'υ'
#define GU02 u'Υ'
#define GU11 u'ύ'
#define GU12 u'Ύ'
#define GU17 u'ϋ'
#define GU18 u'Ϋ'
#define GU33 u'ΰ'
#define GX01 u'ξ'
#define GX02 u'Ξ'
#define GZ01 u'ζ'
#define GZ02 u'Ζ'
#define HB01 u'ב'
#define HD01 u'ד'
#define HG01 u'ג'
#define HH01 u'ה'
#define HH45 u'ח'
#define HK01 u'כ'
#define HK61 u'ך'
#define HL01 u'ל'
#define HM01 u'מ'
#define HM61 u'ם'
#define HN01 u'נ'
#define HN61 u'ן'
#define HP01 u'פ'
#define HP61 u'ף'
#define HQ01 u'ק'
#define HR01 u'ר'
#define HS01 u'ס'
#define HS21 u'ש'
#define HS45 u'צ'
#define HS61 u'ץ'
#define HT01 u'ת'
#define HT45 u'ט'
#define HW01 u'ו'
#define HX33 u'א'
#define HX35 u'ע'
#define HY01 u'י'
#define HZ01 u'ז'
#define JA01 u'｡' // u'。'
#define JA02 u'｢' // u'「'
#define JA03 u'｣' // u'」'
#define JA04 u'､' // u'、'
#define JA05 u'･' // u'・'
#define JA06 u'ｦ' // u'ヲ'
#define JA07 u'ｧ' // u'ァ'
#define JA08 u'ｨ' // u'ィ'
#define JA09 u'ｩ' // u'ゥ'
#define JA10 u'ｪ' // u'ェ'
#define JA11 u'ｫ' // u'ォ'
#define JA12 u'ｬ' // u'ヤ'
#define JA13 u'ｭ' // u'ュ'
#define JA14 u'ｮ' // u'ヨ'
#define JA15 u'ｯ' // u'ッ'
#define JA16 u'ｰ' // u'ー'
#define JA17 u'ｱ' // u'ア'
#define JA18 u'ｲ' // u'イ'
#define JA19 u'ｳ' // u'ウ'
#define JA20 u'ｴ' // u'エ'
#define JA21 u'ｵ' // u'オ'
#define JA22 u'ｶ' // u'カ'
#define JA23 u'ｷ' // u'キ'
#define JA24 u'ｸ' // u'ク'
#define JA25 u'ｹ' // u'ケ'
#define JA26 u'ｺ' // u'コ'
#define JA27 u'ｻ' // u'サ'
#define JA28 u'ｼ' // u'シ'
#define JA29 u'ｽ' // u'ス'
#define JA30 u'ｾ' // u'セ'
#define JA31 u'ｿ' // u'ソ'
#define JA32 u'ﾀ' // u'タ'
#define JA33 u'ﾁ' // u'チ'
#define JA34 u'ﾂ' // u'ツ'
#define JA35 u'ﾃ' // u'テ'
#define JA36 u'ﾄ' // u'ト'
#define JA37 u'ﾅ' // u'ナ'
#define JA38 u'ﾆ' // u'ニ'
#define JA39 u'ﾇ' // u'ヌ'
#define JA40 u'ﾈ' // u'ネ'
#define JA41 u'ﾉ' // u'ノ'
#define JA42 u'ﾊ' // u'ハ'
#define JA43 u'ﾋ' // u'ヒ'
#define JA44 u'ﾌ' // u'フ'
#define JA45 u'ﾍ' // u'ヘ'
#define JA46 u'ﾎ' // u'ホ'
#define JA47 u'ﾏ' // u'マ'
#define JA48 u'ﾐ' // u'ミ'
#define JA49 u'ﾑ' // u'ム'
#define JA50 u'ﾒ' // u'メ'
#define JA51 u'ﾓ' // u'モ'
#define JA52 u'ﾔ' // u'ヤ'
#define JA53 u'ﾕ' // u'ユ'
#define JA54 u'ﾖ' // u'ヨ'
#define JA55 u'ﾗ' // u'ラ'
#define JA56 u'ﾘ' // u'リ'
#define JA57 u'ﾙ' // u'ル'
#define JA58 u'ﾚ' // u'レ'
#define JA59 u'ﾛ' // u'ロ'
#define JA60 u'ﾜ' // u'ワ'
#define JA61 u'ﾝ' // u'ン'
#define JA62 u'ﾞ' // u'゛'
#define JA63 u'ﾟ' // u'゜'
#define KA01 u'а'
#define KA02 u'А'
#define KA61 u'я'
#define KA62 u'Я'
#define KB01 u'б'
#define KB02 u'Б'
#define KC01 u'ц'
#define KC02 u'Ц'
#define KC21 u'ч'
#define KC22 u'Ч'
#define KC61 u'щ'
#define KC62 u'Щ'
#define KD01 u'д'
#define KD02 u'Д'
#define KE01 u'е'
#define KE02 u'Е'
#define KE17 u'ё'
#define KE18 u'Ё'
#define KE61 u'э'
#define KE62 u'Э'
#define KF01 u'ф'
#define KF02 u'Ф'
#define KG01 u'г'
#define KG02 u'Г'
#define KH01 u'х'
#define KH02 u'Х'
#define KI01 u'и'
#define KI02 u'И'
#define KI23 u'й'
#define KI24 u'Й'
#define KJ01 u'ж'
#define KJ02 u'Ж'
#define KK01 u'к'
#define KK02 u'К'
#define KL01 u'л'
#define KL02 u'Л'
#define KM01 u'м'
#define KM02 u'М'
#define KN01 u'н'
#define KN02 u'Н'
#define KO01 u'о'
#define KO02 u'О'
#define KP01 u'п'
#define KP02 u'П'
#define KR01 u'р'
#define KR02 u'Р'
#define KS01 u'с'
#define KS02 u'С'
#define KS23 u'ш'
#define KS24 u'Ш'
#define KT01 u'т'
#define KT02 u'Т'
#define KU01 u'у'
#define KU02 u'У'
#define KV01 u'в'
#define KV02 u'В'
#define KV61 u'ю'
#define KV62 u'Ю'
#define KY01 u'ы'
#define KY02 u'Ы'
#define KY61 u'ь'
#define KY62 u'Ь'
#define KY63 u'ъ'
#define KY64 u'Ъ'
#define KZ01 u'з'
#define KZ02 u'З'
#define LA01 u'a'
#define LA02 u'A'
#define LA11 u'á'
#define LA12 u'Á'
#define LA13 u'à'
#define LA14 u'À'
#define LA15 u'â'
#define LA16 u'Â'
#define LA17 u'ä'
#define LA18 u'Ä'
#define LA19 u'ã'
#define LA20 u'Ã'
#define LA23 u'ă'
#define LA24 u'Ă'
#define LA27 u'å'
#define LA28 u'Å'
#define LA31 u'ā'
#define LA32 u'Ā'
#define LA43 u'ą'
#define LA44 u'Ą'
#define LA51 u'æ'
#define LA52 u'Æ'
#define LB01 u'b'
#define LB02 u'B'
#define LC01 u'c'
#define LC02 u'C'
#define LC11 u'ć'
#define LC12 u'Ć'
#define LC15 u'ĉ'
#define LC16 u'Ĉ'
#define LC21 u'č'
#define LC22 u'Č'
#define LC29 u'ċ'
#define LC30 u'Ċ'
#define LC41 u'ç'
#define LC42 u'Ç'
#define LD01 u'd'
#define LD02 u'D'
#define LD21 u'ď'
#define LD22 u'Ď'
#define LD61 u'đ'
#define LD62 u'Đ'
#define LD63 u'ð'
#define LE01 u'e'
#define LE02 u'E'
#define LE11 u'é'
#define LE12 u'É'
#define LE13 u'è'
#define LE14 u'È'
#define LE15 u'ê'
#define LE16 u'Ê'
#define LE17 u'ë'
#define LE18 u'Ë'
#define LE21 u'ě'
#define LE22 u'Ě'
#define LE29 u'ė'
#define LE30 u'Ė'
#define LE31 u'ē'
#define LE32 u'Ē'
#define LE43 u'ę'
#define LE44 u'Ę'
#define LF01 u'f'
#define LF02 u'F'
#define LG01 u'g'
#define LG02 u'G'
#define LG11 u'ǵ'
#define LG15 u'ĝ'
#define LG16 u'Ĝ'
#define LG23 u'ğ'
#define LG24 u'Ğ'
#define LG29 u'ġ'
#define LG30 u'Ġ'
#define LG41 u'ǵ'
#define LG42 u'Ģ'
#define LH01 u'h'
#define LH02 u'H'
#define LH15 u'ĥ'
#define LH16 u'Ĥ'
#define LH61 u'ħ'
#define LH62 u'Ħ'
#define LI01 u'i'
#define LI02 u'I'
#define LI11 u'í'
#define LI12 u'Í'
#define LI13 u'ì'
#define LI14 u'Ì'
#define LI15 u'î'
#define LI16 u'Î'
#define LI17 u'ï'
#define LI18 u'Ï'
#define LI19 u'ĩ'
#define LI20 u'Ĩ'
#define LI30 u'İ'
#define LI31 u'ī'
#define LI32 u'Ī'
#define LI43 u'į'
#define LI44 u'Į'
#define LI51 u'ĳ'
#define LI52 u'Ĳ'
#define LI61 u'ı'
#define LJ01 u'j'
#define LJ02 u'J'
#define LJ15 u'ĵ'
#define LJ16 u'Ĵ'
#define LK01 u'k'
#define LK02 u'K'
#define LK41 u'ķ'
#define LK42 u'Ķ'
#define LK61 u'ĸ'
#define LL01 u'l'
#define LL02 u'L'
#define LL11 u'ĺ'
#define LL12 u'Ĺ'
#define LL21 u'ľ'
#define LL22 u'Ľ'
#define LL41 u'ļ'
#define LL42 u'Ļ'
#define LL61 u'ł'
#define LL62 u'Ł'
#define LL63 u'ŀ'
#define LL64 u'Ŀ'
#define LM01 u'm'
#define LM02 u'M'
#define LN01 u'n'
#define LN02 u'N'
#define LN11 u'ń'
#define LN12 u'Ń'
#define LN19 u'ñ'
#define LN20 u'Ñ'
#define LN21 u'ň'
#define LN22 u'Ň'
#define LN41 u'ņ'
#define LN42 u'Ņ'
#define LN61 u'ŋ'
#define LN62 u'Ŋ'
#define LN63 u'ŉ'
#define LO01 u'o'
#define LO02 u'O'
#define LO11 u'ó'
#define LO12 u'Ó'
#define LO13 u'ò'
#define LO14 u'Ò'
#define LO15 u'ô'
#define LO16 u'Ô'
#define LO17 u'ö'
#define LO18 u'Ö'
#define LO19 u'õ'
#define LO20 u'Õ'
#define LO25 u'ő'
#define LO26 u'Ő'
#define LO31 u'ō'
#define LO32 u'Ō'
#define LO51 u'œ'
#define LO52 u'Œ'
#define LO61 u'ø'
#define LO62 u'Ø'
#define LP01 u'p'
#define LP02 u'P'
#define LQ01 u'q'
#define LQ02 u'Q'
#define LR01 u'r'
#define LR02 u'R'
#define LR11 u'ŕ'
#define LR12 u'Ŕ'
#define LR21 u'ř'
#define LR22 u'Ř'
#define LR41 u'ŗ'
#define LR42 u'Ŗ'
#define LS01 u's'
#define LS02 u'S'
#define LS11 u'ś'
#define LS12 u'Ś'
#define LS15 u'ŝ'
#define LS16 u'Ŝ'
#define LS21 u'š'
#define LS22 u'Š'
#define LS41 u'ş'
#define LS42 u'Ş'
#define LS61 u'ß'
#define LT01 u't'
#define LT02 u'T'
#define LT21 u'ť'
#define LT22 u'Ť'
#define LT41 u'ţ'
#define LT42 u'Ţ'
#define LT61 u'ŧ'
#define LT62 u'Ŧ'
#define LT63 u'þ'
#define LT64 u'Þ'
#define LU01 u'u'
#define LU02 u'U'
#define LU11 u'ú'
#define LU12 u'Ú'
#define LU13 u'ù'
#define LU14 u'Ù'
#define LU15 u'û'
#define LU16 u'Û'
#define LU17 u'ü'
#define LU18 u'Ü'
#define LU19 u'ũ'
#define LU20 u'Ũ'
#define LU23 u'ŭ'
#define LU24 u'Ŭ'
#define LU25 u'ű'
#define LU26 u'Ű'
#define LU27 u'ů'
#define LU28 u'Ů'
#define LU31 u'ū'
#define LU32 u'Ū'
#define LU43 u'ų'
#define LU44 u'Ų'
#define LV01 u'v'
#define LV02 u'V'
#define LW01 u'w'
#define LW02 u'W'
#define LW15 u'ŵ'
#define LW16 u'Ŵ'
#define LX01 u'x'
#define LX02 u'X'
#define LY01 u'y'
#define LY02 u'Y'
#define LY11 u'ý'
#define LY12 u'Ý'
#define LY15 u'ŷ'
#define LY16 u'Ŷ'
#define LY17 u'ÿ'
#define LY18 u'Ÿ'
#define LZ01 u'z'
#define LZ02 u'Z'
#define LZ11 u'ź'
#define LZ12 u'Ź'
#define LZ21 u'ž'
#define LZ22 u'Ž'
#define LZ29 u'ż'
#define LZ30 u'Ż'
#define MG00 u' '
#define MG01 unavailable(0x01)
#define MG02 unavailable(0x02)
#define MG03 unavailable(0x03)
#define MG04 unavailable(0x04)
#define MG05 unavailable(0x05)
#define MG06 unavailable(0x06)
#define MG07 unavailable(0x07)
#define MG08 unavailable(0x08)
#define MG09 unavailable(0x09)
#define MG10 unavailable(0x0A)
#define MG11 unavailable(0x0B)
#define MG12 unavailable(0x0C)
#define MG13 unavailable(0x0D)
#define MG14 unavailable(0x0E)
#define MG15 unavailable(0x0F)
#define MG16 unavailable(0x10)
#define MG17 unavailable(0x11)
#define MG18 unavailable(0x12)
#define MG19 unavailable(0x13)
#define MG20 unavailable(0x14)
#define MG21 u'▌'
#define MG22 unavailable(0x16)
#define MG23 unavailable(0x17)
#define MG24 unavailable(0x18)
#define MG25 unavailable(0x19)
#define MG26 unavailable(0x1A)
#define MG27 unavailable(0x1B)
#define MG28 unavailable(0x1C)
#define MG29 unavailable(0x1D)
#define MG30 unavailable(0x1E)
#define MG31 unavailable(0x1F)
#define MG32 unavailable(0x20)
#define MG33 unavailable(0x21)
#define MG34 unavailable(0x22)
#define MG35 unavailable(0x23)
#define MG36 unavailable(0x24)
#define MG37 unavailable(0x25)
#define MG38 unavailable(0x26)
#define MG39 unavailable(0x27)
#define MG40 unavailable(0x28)
#define MG41 unavailable(0x29)
#define MG42 u'▐'
#define MG43 unavailable(0x2B)
#define MG44 unavailable(0x2C)
#define MG45 unavailable(0x2D)
#define MG46 unavailable(0x2E)
#define MG47 unavailable(0x2F)
#define MG48 unavailable(0x30)
#define MG49 unavailable(0x31)
#define MG50 unavailable(0x32)
#define MG51 unavailable(0x33)
#define MG52 unavailable(0x34)
#define MG53 unavailable(0x35)
#define MG54 unavailable(0x36)
#define MG55 unavailable(0x37)
#define MG56 unavailable(0x38)
#define MG57 unavailable(0x39)
#define MG58 unavailable(0x3A)
#define MG59 unavailable(0x3B)
#define MG60 unavailable(0x3C)
#define MG61 unavailable(0x3D)
#define MG62 unavailable(0x3E)
#define MG63 u'█'
#define MG64 u'█'
#define MS01 u'▖'
#define MS02 u'■'
#define MS03 unavailable(0x79)
#define MS04 u'▟'
#define MS05 unavailable(0x7B)
#define MS06 unavailable(0x7C)
#define MS07 unavailable(0x7D)
#define MS08 unavailable(0x7E)
#define MS09 unavailable(0x7F)
#define MS10 unavailable(0x80)
#define MS11 unavailable(0x81)
#define MS12 unavailable(0x82)
#define MS13 unavailable(0xC3)
#define MS14 unavailable(0xC4)
#define MS15 unavailable(0xC5)
#define MS16 u'▄'
#define MS17 u'▗'
#define MS18 unavailable(0x85)
#define MS19 unavailable(0x86)
#define MS20 unavailable(0x87)
#define MS21 unavailable(0x88)
#define MS22 unavailable(0x89)
#define MS23 unavailable(0x8A)
#define MS24 unavailable(0x8B)
#define MS25 unavailable(0x8C)
#define MS26 unavailable(0x8D)
#define MS27 unavailable(0x8E)
#define MS28 unavailable(0x8F)
#define MS29 unavailable(0xC6)
#define MS30 unavailable(0xC7)
#define MS31 unavailable(0xC8)
#define ND01 u'1'
#define ND02 u'2'
#define ND03 u'3'
#define ND04 u'4'
#define ND05 u'5'
#define ND06 u'6'
#define ND07 u'7'
#define ND08 u'8'
#define ND09 u'9'
#define ND10 u'0'
#define NF01 u'½'
#define NF04 u'¼'
#define NF05 u'¾'
#define NF18 u'⅛'
#define NF19 u'⅜'
#define NF20 u'⅝'
#define NF21 u'⅞'
#define NS01 u'¹'
#define NS02 u'²'
#define NS03 u'³'
#define SA01 u'+'
#define SA02 u'±'
#define SA03 u'<'
#define SA04 u'='
#define SA05 u'>'
#define SA06 u'÷'
#define SA07 u'×'
#define SC01 u'¤'
#define SC02 u'£'
#define SC03 u'$'
#define SC04 u'¢'
#define SC05 u'¥'
#define SD11 u'´'
#define SD13 u'`'
#define SD15 u'^'
#define SD17 u'¨'
#define SD19 u'~'
#define SD21 u'ˇ'
#define SD23 u'˘'
#define SD25 u'˝'
#define SD27 u'˚'
#define SD29 u'˙'
#define SD31 u'¯'
#define SD33 u'΅'
#define SD41 u'¸'
#define SD43 u'˛'
#define SG01 unavailable(0x40)
#define SG02 unavailable(0x41)
#define SG03 unavailable(0x42)
#define SG04 unavailable(0x43)
#define SG05 unavailable(0x44)
#define SG06 unavailable(0x45)
#define SG07 unavailable(0x46)
#define SG08 unavailable(0x47)
#define SG09 unavailable(0x48)
#define SG10 unavailable(0x49)
#define SG11 unavailable(0x4A)
#define SG12 unavailable(0x4B)
#define SG13 unavailable(0x4C)
#define SG14 unavailable(0x4D)
#define SG15 unavailable(0x4E)
#define SG16 unavailable(0x4F)
#define SG17 unavailable(0x50)
#define SG18 unavailable(0x51)
#define SG19 unavailable(0x52)
#define SG20 unavailable(0x53)
#define SG21 unavailable(0x54)
#define SG22 unavailable(0x55)
#define SG23 unavailable(0x56)
#define SG24 unavailable(0x57)
#define SG25 unavailable(0x58)
#define SG26 unavailable(0x59)
#define SG27 unavailable(0x5A)
#define SG28 unavailable(0x5B)
#define SG29 unavailable(0x5C)
#define SG30 unavailable(0x5D)
#define SG31 unavailable(0x5E)
#define SG32 unavailable(0x5F)
#define SG33 unavailable(0x60)
#define SG34 unavailable(0x61)
#define SG35 unavailable(0x62)
#define SG36 unavailable(0x63)
#define SG37 unavailable(0x64)
#define SG38 unavailable(0x65)
#define SG39 unavailable(0x66)
#define SG40 unavailable(0x67)
#define SG41 unavailable(0x68)
#define SG42 unavailable(0x69)
#define SG43 unavailable(0x6A)
#define SG44 unavailable(0x6B)
#define SG45 unavailable(0x6C)
#define SG46 unavailable(0x6D)
#define SG47 unavailable(0x6E)
#define SG48 unavailable(0x6F)
#define SG49 unavailable(0x70)
#define SG50 unavailable(0x71)
#define SG51 unavailable(0x72)
#define SG52 unavailable(0x73)
#define SG53 unavailable(0x74)
#define SG54 unavailable(0x75)
#define SG55 unavailable(0x76)
#define SG56 unavailable(0x77)
#define SM01 u'#'
#define SM02 u'%'
#define SM03 u'&'
#define SM04 u'*'
#define SM05 u'@'
#define SM06 u'['
#define SM07 u'\\'
#define SM08 u']'
#define SM11 u'{'
#define SM12 u'─'
#define SM13 u'│'
#define SM14 u'}'
#define SM17 u'μ'
#define SM18 u'Ω'
#define SM19 u'°'
#define SM20 u'º'
#define SM21 u'ª'
#define SM24 u'§'
#define SM25 u'¶'
#define SM26 u'·'
#define SM30 u'←'
#define SM31 u'→'
#define SM32 u'↑'
#define SM33 u'↓'
#define SM34 u''
#define SM35 u'®'
#define SM36 u'©'
#define SM37 u'™'
#define SM38 u'♪'
#define SM39 u'⅛'
#define SM40 u'⅜'
#define SM41 u'⅝'
#define SM42 u'⅞'
#define SM43 u'^'
#define SM44 u'`'
#define SM45 u'⎸'
#define SM46 u'⎹'
#define SM47 u'~'
#define SM48 u'_'
#define SM49 u'ـ'
#define SM49 '̲'
#define SM50 '⃗'
#define SM51 '̷'
#define SM52 u'©'
#define SM53 u'®'
#define SM54 u'™'
#define SM65 u'¦'
#define SM66 u'¬'
#define SM93 u'♪'
#define SM95 u'¦'
#define SM96 u'¬'
#define SP01 u' u'
#define SP02 u'!'
#define SP03 u'¡'
#define SP04 u'"'
#define SP05 u'\''
#define SP06 u'('
#define SP07 u')'
#define SP08 u','
#define SP09 u'_'
#define SP10 u'-'
#define SP11 u'.'
#define SP12 u'/'
#define SP13 u':'
#define SP14 u';'
#define SP15 u'?'
#define SP16 u'¿'
#define SP17 u'«'
#define SP18 u'»'
#define SP19 u'‘'
#define SP20 u'’'
#define SP21 u'“'
#define SP22 u'”'
#define SP31 u' '
#define SP32 u'\u00ad'

#undef unavailable
