#ifndef __REST_SVC_REQUEST_HANDLER__
#define __REST_SVC_REQUEST_HANDLER__

#include <string>
#include <boost/noncopyable.hpp>

namespace rest {
namespace svc {

    struct reply;
    struct request;

    /// The common handler for all incoming requests.
    class request_handler : private boost::noncopyable 
    {
    public:
        /// Construct with a directory containing files to be served.
        explicit request_handler(const std::string& doc_root);

        /// Handle a request and produce a reply.
        void handle_request(const request& req, reply& rep);

    private:
        /// The directory containing the files to be served.
        std::string doc_root_;

        /// Perform URL-decoding on a string. Returns false if the encoding was
        /// invalid.
        static bool url_decode(const std::string& in, std::string& out);
    };

} // namespace svc
} // namespace rest

#endif // __REST_SVC_REQUEST_HANDLER__
