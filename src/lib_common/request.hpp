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
            request(){}

            request(const string& method, const string& uri, 
                    int http_version_major,int http_version_minor)
                    :
                    _method(method), _uri(uri), 
                    _http_version_major(http_version_major), _http_version_minor(http_version_minor){}

            // Override the base to_buffers
            virtual vector<boost::asio::const_buffer> to_buffers() const;

        public:
            // Accessors
            const string& get_method() { return _method; }
            const string& get_uri() { return _uri; }
            int get_http_major_verion() { return _http_version_major;}
            int get_http_minor_verion() { return _http_version_minor;}

        private:
            string _method;
            string _uri;
            int _http_version_major;
            int _http_version_minor;

        };
    } // common
} // rest


#endif //__REST_REQUEST__