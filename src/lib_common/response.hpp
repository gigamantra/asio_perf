#ifndef __REST_RESPONSE__
#define __REST_RESPONSE__


#include "message.hpp"


#include <boost/asio.hpp>


namespace rest {
    namespace common {
        class response_parser;

        /*
        Represents a HTTP response. It derives most of it's
        functionality from the message class
        */
        class response :  public message
        {
            friend class response_parser;

        public:
            // The status of the reply. We will only support a small
            // subset of http response codes
            enum status_type 
            {
                ok,
                bad_request,
                unauthorized,
                internal_server_error,
                not_implemented
            };

        public:
            // Default constructor - nothing much here for the time being
            // the status and other contents will be filled in by a response parser
            response() {}

            // Initialize the response
            response(status_type status): _status(status){}

            // Serialize this response to a vector of buffers
            void to_buffer(vector<boost::asio::const_buffer>& buffer) const;

        private:
            // The status of the request
            status_type _status;
        };


    } // common
} // rest


#endif //__REST_RESPONSE__