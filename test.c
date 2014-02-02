/*
 * NSS plugin for looking up Docker containers -- testcases
 *
 * (c) 2014  Danielle Madeley  <danielle@madeley.id.au>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <glib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BADGER_DOCKER_IP "172.11.22.33"

static void
test_gethostbyname (void)
{
    struct hostent *results;
    char buffer[INET_ADDRSTRLEN];

    results = gethostbyname("badger.docker");

    g_assert(results != NULL);

    g_assert_cmpstr(results->h_name, ==, "badger.docker");
    g_assert(results->h_aliases[0] == NULL);
    g_assert_cmpint(results->h_addrtype, ==, AF_INET);
    g_assert_cmpint(results->h_length, ==, 4);
    g_assert(results->h_addr_list[0] != NULL);
    g_assert(results->h_addr_list[1] == NULL);

    inet_ntop(AF_INET, results->h_addr_list[0], buffer, INET_ADDRSTRLEN);
    g_assert_cmpstr(buffer, ==, BADGER_DOCKER_IP);
}

static void
test_gethostbyname_not_docker (void)
{
    struct hostent *results;

    results = gethostbyname("badger");

    g_assert(results == NULL);
    g_assert_cmpint(h_errno, ==, HOST_NOT_FOUND);
}

static void
test_gethostbyname_by_image_name (void)
{
    struct hostent *results;

    results = gethostbyname("stoat.docker");

    g_assert(results == NULL);
    g_assert_cmpint(h_errno, ==, HOST_NOT_FOUND);
}

static void
test_gethostbyname_unknown_name (void)
{
    struct hostent *results;

    results = gethostbyname("mushroom.docker");

    g_assert(results == NULL);
    g_assert_cmpint(h_errno, ==, HOST_NOT_FOUND);
}

static void
test_gethostbyname2 (void)
{
    struct hostent *results;
    char buffer[INET_ADDRSTRLEN];

    results = gethostbyname2("badger.docker", AF_INET);

    g_assert(results != NULL);

    g_assert_cmpstr(results->h_name, ==, "badger.docker");
    g_assert(results->h_aliases[0] == NULL);
    g_assert_cmpint(results->h_addrtype, ==, AF_INET);
    g_assert_cmpint(results->h_length, ==, 4);
    g_assert(results->h_addr_list[0] != NULL);
    g_assert(results->h_addr_list[1] == NULL);

    inet_ntop(AF_INET, results->h_addr_list[0], buffer, INET_ADDRSTRLEN);
    g_assert_cmpstr(buffer, ==, BADGER_DOCKER_IP);
}

static void
test_gethostbyname2_inet6 (void)
{
    struct hostent *results;

    results = gethostbyname2("badger.docker", AF_INET6);

    g_assert(results == NULL);
    g_assert_cmpint(errno, ==, EAFNOSUPPORT);
    g_assert_cmpint(h_errno, ==, NO_DATA);
}

# if 0
static void
test_gethostbyaddr (void)
{
    struct hostent *results;
    struct in_addr addr;
    char buffer[INET_ADDRSTRLEN];

    inet_pton(AF_INET, "10.0.0.0", &addr);

    results = gethostbyaddr(&addr, 4, AF_INET);

    g_assert (results != NULL);

    g_assert_cmpstr(results->h_name, ==, "container.docker");
    g_assert(results->h_aliases[0] == NULL);
    g_assert_cmpint(results->h_addrtype, ==, AF_INET);
    g_assert_cmpint(results->h_length, ==, 4);
    g_assert(results->h_addr_list[0] != NULL);
    g_assert(results->h_addr_list[1] == NULL);

    inet_ntop(AF_INET, results->h_addr_list[0], buffer, INET_ADDRSTRLEN);
    g_assert_cmpstr(buffer, ==, "10.0.0.0");
}
# endif

int
main (int argc,
        char **argv)
{
    g_test_init (&argc, &argv, NULL);

    g_test_add_func("/test/gethostbyname", test_gethostbyname);
    g_test_add_func("/test/gethostbyname_not_docker",
            test_gethostbyname_not_docker);
    g_test_add_func("/test/gethostbyname_by_image_name",
            test_gethostbyname_by_image_name);
    g_test_add_func("/test/gethostbyname_unknown_name",
            test_gethostbyname_unknown_name);
    g_test_add_func("/test/gethostbyname2", test_gethostbyname2);
    g_test_add_func("/test/gethostbyname2_inet6", test_gethostbyname2_inet6);
    // g_test_add_func("/test/gethostbyaddr", test_gethostbyaddr);

    return g_test_run ();
}
