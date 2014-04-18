#include "message.hpp"


using namespace rest::common;


// Adds a key and a value to the message header and returns true if the key is not present.
// if the key is present - nothing is changed and false is returned
bool message::add_key_value(const string& key, const string& value)
{
    auto item =_headers.get<1>().find(key);
    if (_headers.get<1>().end() != item) {
        return false;
    }

    key_value newItem(key, value);
    _headers.push_back(newItem);
    return true;
}


// Updates the value of a given key in the message header and returns true if successful
// If the key was not found - false is returned.
bool message::update_value(const string& key, const string& value)
{
    auto item =_headers.get<1>().find(to_lower_copy(key));
    if (_headers.get<1>().end() == item) {
        return false;
    }

    key_value newItem = *item;
    newItem._value = value;
    return _headers.get<1>().replace(item, newItem);
}


// Updates the value at a given location in the message header and returns true if successful
// If the location is invalid - false is returned.
bool message::update_value(unsigned int position, const std::string& value)
{
    auto item =_headers.get<0>().begin() + position;
    if (_headers.get<0>().end() == item) {
        return false;
    }

    key_value newItem = *item;
    newItem._value = value;
    return _headers.get<0>().replace(item, newItem);
}


// Fetches the value for a given key from the header.and returns true if found.
// If not present false is returned.
bool message::get_value(const string& key, string& value)
{
    auto item =_headers.get<1>().find(to_lower_copy(key));
    if (_headers.get<1>().end() == item) {
        return false;
    }

    value = (*item)._value;
    return true;
}


// Fetches the value at a given position and returns true if found
// if position is out of bounds - false is returned
bool message::get_value(unsigned int position, string& value)
{
    auto item =_headers.get<0>().begin() + position;
    if (_headers.get<0>().end() == item) {
        return false;
    }

    value = (*item)._value;
    return true;
}


// Fetches the key and the associated value at a given position and returns true if found
// if position is out of bounds - false is returned
bool message::get_key_value(unsigned int position, string& key, string& value)
{
    auto item =_headers.get<0>().begin() + position;
    if (_headers.get<0>().end() == item) {
        return false;
    }

    key  = (*item)._key;
    value = (*item)._value;
    return true;
}

// Iterates over the key value pairs in the header and invokes the
// supplied function with each key-value pair
void message::iterate(std::function<void(const string&, const string&)> itor_func)
{
    auto itor = _headers.get<0>().begin();
    size_t size = get_number_of_key_values();
    for (size_t i =0; i <size; ++i){
        itor_func((*itor)._key, (*itor)._value);
        ++ itor;
    }
}


// Serialize the message to a collection of const buffers
// Note: the underlying memory needs to be valid until the 
// write operation is completed.
vector<boost::asio::const_buffer> message::to_buffers()
{
    throw std::exception("Not implemented!");
}

