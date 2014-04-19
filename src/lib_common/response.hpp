#ifndef __REST_RESPONSE__
#define __REST_RESPONSE__


#include "message.hpp"


#include <boost/asio.hpp>


namespace rest {
    namespace common {

        /*
        Represents a HTTP response. It derives most of it's
        functionality from the message class
        */
        class response :  public message
        {
        public:
            // The status of the reply.
            enum status_type 
            {
                ok,
                bad_request,
                unauthorized,
                internal_server_error,
                not_implemented
            };

        public:
            response() {}

            response(status_type status): _status(status){}

            // Serialize this response to a vector of buffers
            void to_buffers(vector<boost::asio::const_buffer>& buffer) const;

        private:
            status_type _status;

            const string& to_string(status_type status) const;
        };


    } // common
} // rest


#endif //__REST_RESPONSE__