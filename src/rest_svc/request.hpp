#ifndef __REST_SVC_REQUEST__
#define __REST_SVC_REQUEST__

#include <string>
#include <vector>
#include "header.hpp"

namespace rest {
namespace svc {

    /// A request received from a client.
    struct request 
    {
        std::string method;
        std::string uri;
        int http_version_major;
        int http_version_minor;
        std::vector<header> headers;
    };

} // namespace svc
} // namespace rest

#endif // __REST_SVC_REQUEST__
