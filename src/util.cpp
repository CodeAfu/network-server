#include <arpa/inet.h>

#include "base.h"
#include "util.h"

void util::get_ipv4(SocketAddressIPv4 &sa, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET, addr, &(sa.sin_addr));
    ::inet_ntop(AF_INET, &sa.sin_addr, out, out_len);
}

void util::get_ipv6(SocketAddressIPv6 &sa6, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET6, addr, &(sa6.sin6_addr));
    ::inet_ntop(AF_INET6, &sa6.sin6_addr, out, out_len);
}

const char* util::inet_ntop(const char* addr, char *buf, size_t size)
{
    SocketAddressStorage *sas = (SocketAddressStorage*)addr;
    SocketAddressIPv4 *sa4 = nullptr;
    SocketAddressIPv6 *sa6 = nullptr;
    void *src;

    switch (sas->ss_family) {
        case (AF_INET):
            sa4 = (SocketAddressIPv4*)addr;
            src = &(sa4->sin_addr);
            break;
        case (AF_INET6):
            sa6 = (SocketAddressIPv6*)addr;
            src = &(sa6->sin6_addr);
            break;
        default:
            return nullptr;
    }
    
    return ::inet_ntop(sas->ss_family, src, buf, size);
}
