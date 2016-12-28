CC = gcc
CFLAGS = -g -g3 -O0 -Werror=unused -Werror=unused-result
LDLIBS = -pthread
LDFLAGS = -O1


ALL = ev-test.x

override CFLAGS += -Werror=all -Werror=extra -Werror=format=2
override CFLAGS += -Werror=c++-compat -Werror=write-strings
override CFLAGS += -Werror=missing-declarations -Werror=redundant-decls

all: ${ALL}
clean:
	rm -f *.x *.so *.o
test: check
check: check-symbols
check-symbols: all
	! nm *.x *.so | grep -v -w -f symbol_whitelist

%.x:
	${CC} ${LDFLAGS} $^ ${LDLIBS} -o $@
%.so:
	${CC} -shared ${LDFLAGS} $^ ${LDLIBS} -o $@
	chmod -x $@
%.o: %.c
	${CC} -fPIC ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

ev-test.x: \
    libfool-term.so \
    ev-test.o
libfool-term.so: \
    ev.o \
    buffer.o \
    util.o \
    signals.o \

ev-test.o: \
    ev.h \
    util.h \
    signals.h \
    ev-test.c
ev.o: \
    util.h \
    buffer.h \
    ev.c ev.h
util.o: \
    util.c util.h
buffer.o: \
    buffer.c buffer.h
signals.o: \
    util.h \
    signals.c signals.h
