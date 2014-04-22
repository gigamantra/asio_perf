#ifndef __REST_REQUEST__
#define __REST_REQUEST__


#include "message.hpp"

#include <boost/asio.hpp>


namespace rest {
    namespace common {

        /*
        Represents a HTTP request. It derives most of it's
        functionality from the message class
        */
        class request :  public message
        {
        public:
            // Serialize the request to a vector of buffers
            vector<boost::asio::const_buffer> to_buffer() const;

        public:
            // Accessors
            const string& get_method() { return _method; }
            const string& get_uri() { return _uri; }
            int get_http_verion_major() { return _http_version_major;}
            int get_http_verion_minor() { return _http_version_minor;}

            // Mutators
            void set_method(const string& method ) { _method = method;}
            void set_uri(const string& uri ) { _uri = uri;}
            void set_http_version_major(int version) { _http_version_major = version;}
            void set_http_version_minor(int version) { _http_version_minor = version;}

        private:
            string _method;
            string _uri;
            int _http_version_major;
            int _http_version_minor;

        };
    } // common
} // rest


#endif //__REST_REQUEST__