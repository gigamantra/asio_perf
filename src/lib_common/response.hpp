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


            response(status_type status): _status(status){}

        public:
            // Serialize this response to a vector of buffers
            void to_buffer(vector<boost::asio::const_buffer>& buffer) const;

        public:
            // Accessor
            status_type get_status() { return _status;}

            // Mutator
            void set_status(status_type status) {_status = status;}

        private:
            // The status of the request
            status_type _status;
        };


    } // common
} // rest


#endif //__REST_RESPONSE__