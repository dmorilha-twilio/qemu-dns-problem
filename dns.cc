#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int lookup(const char *hostname, int family)
{
    int r;
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
    r = getaddrinfo(hostname, "80", &hints, &res);
    printf("family=%i, ret=%i (%s)\n", family, r, gai_strerror(r));
    return r;
}

int main(int argc, char *argv[]) {
    char *hostname = "google.com";
    int r = 0;
    if (argc > 1)
        hostname = argv[1];
    r += lookup(hostname, AF_INET);
    r += lookup(hostname, AF_INET6);
    r += lookup(hostname, AF_UNSPEC);
    puts(r == 0 ? "OK": "FAIL");
    return 0;
}
