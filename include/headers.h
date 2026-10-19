#pragma once

#include <optional>
#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <array>
#include <string_view>

#define HTTP_METHODS(X) \
    X(GET)              \
    X(POST)             \
    X(PUT)              \
    X(DELETE)           \
    X(PATCH)            \
    X(OPTIONS)

enum class MethodType {
#define X(name) name,
    HTTP_METHODS(X)
#undef X
};

constexpr std::string_view method_type(MethodType type)
{
    switch (type) {
#define X(name) case MethodType::name: return #name;
        HTTP_METHODS(X)
#undef X
    }
    return "UNKNOWN";
}

constexpr std::optional<MethodType> parse_method(std::string_view word)
{
#define X(name) if (word == #name) return MethodType::name;
    HTTP_METHODS(X)
#undef X
    return std::nullopt;
}

constexpr std::array<std::string_view, 5> VALID_HEADERS = {
    "Host",
    "User-Agent",
    "Accept",
    "Content-Type",
    "Content-Length"
};

namespace ContentType {
inline constexpr std::string_view TEXT = "text/plain";
inline constexpr std::string_view JSON = "application/json";
} // namespace ContentType

enum StatusCode {
    OK = 200,
    CREATED = 201,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
};

struct HttpHeader {
    std::string name;
    std::string value;
};

struct HttpRequest {
    std::string method; // "GET"
    std::string target; // "/index.html"
    std::string version; // "HTTP/1.1"

    std::vector<HttpHeader> headers;
    std::string body;
};

struct HttpResponse {
    uint16_t status; // 200, 404
    const std::string reason; // "OK", "Not Found"
    const std::string version; // "HTTP/1.1"

    std::vector<HttpHeader> headers;
    const std::string body;
};

namespace header {
static inline std::string status_reason(StatusCode code)
{
    switch (code) {
        case OK:
            return "OK";
        case CREATED:
            return "Created";
        case BAD_REQUEST:
            return "Bad Request";
        case UNAUTHORIZED:
            return "Unauthorized";
        case NOT_FOUND:
            return "Not Found";
        case INTERNAL_SERVER_ERROR:
            return "Internal Server Error";
        case NOT_IMPLEMENTED:
            return "Not Implemented";
        case BAD_GATEWAY:
            return "Bad Gateway";
        default:
            return "";
    }
}

} // namespace header
