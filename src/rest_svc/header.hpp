#ifndef __REST_SVC_HEADER__
#define __REST_SVC_HEADER__

#include <string>

namespace rest {
namespace svc {

    struct header 
    {
        std::string name;
        std::string value;
    };

} // namespace svc
} // namespace rest

#endif // __REST_SVC_HEADER__