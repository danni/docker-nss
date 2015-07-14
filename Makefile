DESTDIR ?=
NSSDIR ?= /usr/lib
BINDIR ?= /usr/bin


STRIP = strip
CC = gcc
CFLAGS = -fPIC -Wall -Werror -ggdb `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`

OBJS = \
	nss.o

MODULE = libnss_docker.so.2

BINS = \
	$(MODULE) \
	test inspect

$(MODULE): $(OBJS) Makefile
	$(CC) -fPIC -shared -o $@ -Wl,-soname,$@ $< $(LDFLAGS)

TEST_OBJS = \
	test.o

INSPECT_OBJS = \
	inspect.o

test: $(TEST_OBJS) $(MODULE) Makefile
	$(CC) -o $@ $< $(LDFLAGS)

inspect: $(INSPECT_OBJS) $(MODULE) Makefile
	$(CC) -o $@ $<
	$(STRIP) $@

all: $(BINS)

install: all
	mkdir -p $(DESTDIR)$(NSSDIR)
	install -m 0644 $(MODULE) $(DESTDIR)$(NSSDIR)/$(MODULE)
	install -g docker -m 2755 inspect $(DESTDIR)$(BINDIR)/dockerip
	ldconfig

clean:
	rm -f $(BINS) $(OBJS) $(TEST_OBJS)

.PHONY: all install clean
