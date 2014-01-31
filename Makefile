CC = gcc
CFLAGS = -Wall -Werror -ggdb

OBJS = \
	nss.o

libnss_docker.so.2: $(OBJS)
	$(CC) -shared -o $@ -Wl,-soname,$@ $<


