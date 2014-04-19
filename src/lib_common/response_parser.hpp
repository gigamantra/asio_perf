#ifndef __REST_RESPONSE_PARSER__
#define __REST_RESPONSE_PARSER__


#include "response.hpp"


#include <boost/noncopyable.hpp>


namespace rest {
    namespace common {

        /*
        The response parser is responsible for reading in a stream 
        of bytes and populating a response object
        */
        class response_parser  :  private boost::noncopyable
        {


        };

    } // common
} // rest


#endif //__REST_RESPONSE_PARSER__

