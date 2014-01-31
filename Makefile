DESTDIR ?=
NSSDIR ?= /usr/lib

CC = gcc
CFLAGS = -fPIC -Wall -Werror -ggdb `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`

OBJS = \
	nss.o

MODULE = libnss_docker.so.2

BINS = \
	$(MODULE)

$(MODULE): $(OBJS)
	$(CC) $(LDFLAGS) -fPIC -shared -o $@ -Wl,-soname,$@ $<

all: $(BINS)

install: all
	mkdir -p $(DESTDIR)$(NSSDIR)
	install -m 0644 $(MODULE) $(DESTDIR)$(NSSDIR)/$(MODULE)

clean:
	rm -f $(BINS) $(OBJS)

.PHONY: all install clean
