#include "response.hpp"


using namespace rest::common;


// A collection of http status codes that we
// will be returning to the callers
string status_codes[] = {
    "HTTP/1.0 200 OK\r\n",
    "HTTP/1.0 400 Bad Request\r\n",
    "HTTP/1.0 401 Unauthorized\r\n",
    "HTTP/1.0 500 Internal Server Error\r\n",
    "HTTP/1.0 501 Not Implemented\r\n"
};

// Header names need to be separated from the values
const char name_value_separator[] = { ':', ' ' };

// each line in the header needs to be demarcated via crlfs
const char crlf[] = { '\r', '\n' };

// Convert a status_type to a stringified version
const string& to_string(response::status_type status)
{
    return status_codes[status];
}


// Serialize this response to a vector of buffers
void response::to_buffer(vector<boost::asio::const_buffer>& buffer) const 
{
    // The vector of buffers will be written to the socket
    // First write out the status
    buffer.push_back(boost::asio::buffer(to_string(_status)));

    // Get the address of the buffer for our lambda to use
    // while iterating over the key value pairs in the header
    vector<boost::asio::const_buffer>* ptr_buffer = &buffer;
    iterate( [ptr_buffer](const string& key, const string& value) mutable
        {
            // Push in the keays and values in the form <key>:<value>CRLF
            ptr_buffer->push_back(boost::asio::buffer(key));
            ptr_buffer->push_back(boost::asio::buffer(name_value_separator));
            ptr_buffer->push_back(boost::asio::buffer(value));
            ptr_buffer->push_back(boost::asio::buffer(crlf));
        } 
    );

    // Finally add in the payload
    buffer.push_back(boost::asio::buffer(_payload.str()));
}

