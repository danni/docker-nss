#include <nss.h>
#include <netdb.h>
#include <stddef.h>

enum nss_status
_nss_docker_gethostbyname2_r (const char *name,
        int af,
        struct hostent *result,
        char *buffer,
        size_t buflen,
        int *errnop,
        int *h_errnop)
{
    return NSS_STATUS_NOTFOUND;
}

enum nss_status
_nss_docker_gethostbyname_r (const char *name,
        struct hostent *result,
        char *buffer,
        size_t buflen,
        int *errnop,
        int *h_errnop)
{
    return NSS_STATUS_NOTFOUND;
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
