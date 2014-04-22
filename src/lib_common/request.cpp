#include "request.hpp"

using namespace rest::common;

// Override the base to_buffers
vector<boost::asio::const_buffer> request::to_buffer() const 
{
    std::vector<boost::asio::const_buffer> buffers;
    return buffers;
}


