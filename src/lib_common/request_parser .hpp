#ifndef __REST_REQUEST_PARSER__
#define __REST_REQUEST_PARSER__


#include "request.hpp"


#include <boost/noncopyable.hpp>


namespace rest {
    namespace common {

        /*
        The request parser is responsible for reading
        in a stream of bytes and populating a response object.
        */
        class request_parser  :  private boost::noncopyable
        {


        };

    } // common
} // rest


#endif //__REST_REQUEST_PARSER__

