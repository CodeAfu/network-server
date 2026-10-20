#pragma once

#include <arpa/inet.h>
#include <cstddef>

#include "base.h"

namespace nw {
void get_ipv4(SocketAddressIPv4 &sa, const char* addr, char *out, size_t out_len);
void get_ipv6(SocketAddressIPv6 &sa6, const char* addr, char *out, size_t out_len);
const char* inet_ntop(const char* addr, char *out, size_t out_len);
} // namespace nw

#ifdef NETWORK_IMPLEMENTATION
void nw::get_ipv4(SocketAddressIPv4 &sa, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET, addr, &(sa.sin_addr));
    ::inet_ntop(AF_INET, &sa.sin_addr, out, out_len);
}

void nw::get_ipv6(SocketAddressIPv6 &sa6, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET6, addr, &(sa6.sin6_addr));
    ::inet_ntop(AF_INET6, &sa6.sin6_addr, out, out_len);
}

const char* nw::inet_ntop(const char* addr, char *out, size_t out_len)
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
    
    return ::inet_ntop(sas->ss_family, src, out, out_len);
}
#endif
