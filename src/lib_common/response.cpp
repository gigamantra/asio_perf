#include "response.hpp"


using namespace rest::common;

string status_codes[] = {
    "HTTP/1.0 200 OK\r\n",
    "HTTP/1.0 400 Bad Request\r\n",
    "HTTP/1.0 401 Unauthorized\r\n",
    "HTTP/1.0 500 Internal Server Error\r\n",
    "HTTP/1.0 501 Not Implemented\r\n"
};

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

// Serialize this response to a vector of buffers
void response::to_buffers(vector<boost::asio::const_buffer>& buffer) const 
{
    buffer.push_back(boost::asio::buffer(to_string(_status)));
    vector<boost::asio::const_buffer>* ptr_buffer = &buffer;
    iterate( [ptr_buffer](const string& key, const string& value) mutable
        {
            ptr_buffer->push_back(boost::asio::buffer(key));
            ptr_buffer->push_back(boost::asio::buffer(name_value_separator));
            ptr_buffer->push_back(boost::asio::buffer(value));
            ptr_buffer->push_back(boost::asio::buffer(crlf));
        } 
    );

    buffer.push_back(boost::asio::buffer(_payload.str()));
}

const string& response::to_string(status_type status) const
{
    return status_codes[status];
}