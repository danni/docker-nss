/*
 * NSS plugin for looking up Docker containers
 *
 * (c) 2014  Danielle Madeley  <danielle@madeley.id.au>
 */

#include <errno.h>
#include <glib.h>
#include <nss.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

/* define a suffix that containers have */
#define SUFFIX ".docker"

#define ALIGN(a) (((a+sizeof(void*)-1)/sizeof(void*))*sizeof(void*))

enum nss_status
_nss_docker_gethostbyname2_r (const char *name,
        int af,
        struct hostent *result,
        char *buffer,
        size_t buflen,
        int *errnop,
        int *h_errnop)
{
    char *aliases, *addr, *addrlist;
    size_t l, idx;

    if (af != AF_INET)
      {
        *errnop = EAFNOSUPPORT;
        *h_errnop = NO_DATA;
        return NSS_STATUS_UNAVAIL;
      }

    if (!g_str_has_suffix(name, SUFFIX))
      {
        *errnop = ENOENT;
        *h_errnop = HOST_NOT_FOUND;
        return NSS_STATUS_NOTFOUND;
      }

    /* we can't allocate any memory, the buffer is where we need to
     * return things we want to use
     *
     * 1st, the hostname */
    l = strlen(name);
    result->h_name = buffer;
    memcpy (result->h_name, name, l);

    idx = ALIGN (l+1);

    /* 2nd, the empty aliases array */
    aliases = buffer + idx;
    *(char **) aliases = NULL;
    idx += sizeof (char*);

    result->h_aliases = (char **) aliases;

    result->h_addrtype = af;
    result->h_length = sizeof (struct in_addr);

    /* 3rd, address */
    addr = buffer + idx;
    memcpy(addr, "AAAA", result->h_length);
    idx += ALIGN (result->h_length);

    /* 4th, the addresses ptr array */
    addrlist = buffer + idx;
    ((char **) addrlist)[0] = addr;
    ((char **) addrlist)[1] = NULL;

    result->h_addr_list = (char **) addrlist;

    return NSS_STATUS_SUCCESS;
}

enum nss_status
_nss_docker_gethostbyname_r (const char *name,
        struct hostent *result,
        char *buffer,
        size_t buflen,
        int *errnop,
        int *h_errnop)
{
    return _nss_docker_gethostbyname2_r(name,
            AF_INET,
            result,
            buffer,
            buflen,
            errnop,
            h_errnop);
}

enum nss_status
_nss_docker_gethostbyaddr_r (const void *addr,
        int len,
        int af,
        struct hostent *result,
        char *buffer,
        size_t buflen,
        int *errnop,
        int *h_errnop)
{
    return NSS_STATUS_NOTFOUND;
}
