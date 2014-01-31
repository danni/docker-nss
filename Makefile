CC = gcc
CFLAGS = -Wall -Werror -ggdb `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`

OBJS = \
	nss.o

libnss_docker.so.2: $(OBJS)
	$(CC) $(LDFLAGS) -shared -o $@ -Wl,-soname,$@ $<
