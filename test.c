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

#include <glib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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
    g_assert_cmpstr(buffer, ==, "65.65.65.65");
}

int
main (int argc,
        char **argv)
{
    g_test_init (&argc, &argv, NULL);

    g_test_add_func("/test/gethostbyname", test_gethostbyname);

    return g_test_run ();
}
