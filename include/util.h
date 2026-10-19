#pragma once

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <concepts>
#include <print>
#include <utility>
#include <cstddef>

#include "base.h"
#include "server.h"

namespace util {

template <std::invocable F>
int tryCatch(F&& func) {
    try {
        std::forward<F>(func)();
    } catch (const srv::server_error& e) {
        std::println(stderr, "Server error caught: {}", e.what());
        return 1;
    } catch (const std::exception& e) {
        std::println(stderr, "Standard exception: {}", e.what());
        return 1;
    } catch (...) {
        std::println(stderr, "Unknown non-standard exception caught");
        return 1;
    }
    return 0;
}

template <typename... Args>
inline void devprint(std::format_string<Args...> fmt, Args&&... values) {
    const char* env = std::getenv("ENV");
    if (env == nullptr || std::strcmp(env, "development") != 0) {
        return;
    }
    std::print("\x1b[33m");
    std::print(fmt, std::forward<Args>(values)...);
    std::println("\x1b[0m");
}

inline void get_ipv4(SocketAddressIPv4 &sa, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET, addr, &(sa.sin_addr));
    ::inet_ntop(AF_INET, &sa.sin_addr, out, out_len);
}

inline void get_ipv6(SocketAddressIPv6 &sa6, const char* addr, char *out, size_t out_len)
{
    ::inet_pton(AF_INET6, addr, &(sa6.sin6_addr));
    ::inet_ntop(AF_INET6, &sa6.sin6_addr, out, out_len);
}

inline const char* inet_ntop(const char* addr, char *out, size_t out_len)
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

inline bool strequal(std::string a, std::string b)
{
    if (a.size() != b.size())
        return false;
}

} // namespace util
