#pragma once

#include <cstdlib>
#include <cstring>
#include <concepts>
#include <print>
#include <utility>
#include <cstddef>

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

inline bool str_iequal(const std::string& a, const std::string& b)
{
    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.size(); i++) {
        if (std::tolower(a[i]) != std::tolower(b[i]))
            return false;
    }

    return true;
}

inline void str_ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void str_rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void str_trim(std::string &s)
{
    str_ltrim(s);
    str_rtrim(s);
}

} // namespace util
