#pragma once

#include <cstdint>
#include <expected>
#include <string>

#include "headers.h"
#include "base.h"

enum class ParseError {
    InvalidRequestSections,
    InvalidRequestLine,
    InvalidHeader,
};

namespace http {
AddressInfo* get_addr_info(const char *host, const char *port, const ::AddressInfo& hints);
void* get_in_addr(::SocketAddress *sa);
void print_addr_info(const ::AddressInfo& addr_info);

bool send_msg(int sock_fd, const std::string& msg, int flags);
const std::string recv_msg(int sock_fd, int flags);
std::expected<HttpRequest, ParseError> get_http_request(const std::string& raw_request);
std::string create_http_response(const HttpResponse& response);

uint32_t htonf(float f);
float ntohf(uint32_t p);
uint64_t pack754(long double f, unsigned bits, unsigned expbits);
long double unpack754(uint64_t i, unsigned bits, unsigned expbits);

} // namespace http
