#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <print>

#include "base.h"
#include "http.h"
#include "server.h"
#include "util.h"


void sample();

int main() {
    srv::Server s = srv::init();
    if (!s.success)
        return 1;
    srv::run(s);
    return 0;

    /* raddebugger not happy with the tryCatch */
    // return util::tryCatch([] {
    //     srv::Server s = srv::init();
    //     if (!s.success) {
    //         return 1;
    //     }
    //     srv::run(s);
    //     return 0;
    // });
}

void sample() {
    util::devprint("---  SAMPLE  ---");
    AddressInfo hints;
    AddressInfo *servinfo = nullptr;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = ::getaddrinfo("projectzoku.site", "443", &hints, &servinfo);
    if (status != 0) {
        std::println(stderr, "fail: {}", gai_strerror(status));
        return;
    }

    for (AddressInfo *p = servinfo; p != nullptr; p = p->ai_next) {
        http::print_addr_info(*p);
    }

    freeaddrinfo(servinfo);
    util::devprint("---  /SAMPLE  ---");
}
