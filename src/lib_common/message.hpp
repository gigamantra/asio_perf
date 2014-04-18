#ifndef __REST_MESSAGE__
#define __REST_MESSAGE__

#include <string>
#include <sstream>
#include <vector>


#include <boost/noncopyable.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/asio.hpp>


namespace rest {
    namespace common {


        using namespace std;
        using namespace boost;
        using namespace boost::asio;
        using namespace boost::multi_index;
        using namespace boost::algorithm;


        /*
        The base class for http requests and responses. 
        It offers key value storage plus basic serialization
        via a vector of buffers.
        */
        class message :  private boost::noncopyable
        {
        public:

            // Adds a key and a value to the message header and returns true if the key is not present.
            // if the key is present - nothing is changed and false is returned
            bool add_key_value(const string& key, const string& value);

            // Updates the value of a given key in the message header and returns true if successful
            // If the key was not found - false is returned.
            bool update_value(const string& key, const string& value);

            // Updates the value at a given location in the message header and returns true if successful
            // If the location is invalid - false is returned.
            bool update_value(unsigned int position, const string& value);

            // Return the total number of key-value pairs in our header
            size_t get_number_of_key_values() { return _headers.size();}

            // Fetches the value for a given key from the header.and returns true if found.
            // If not present false is returned.
            bool get_value(const string& key, string& value);

            // Fetches the value at a given position and returns true if found
            // if position is out of bounds - false is returned
            bool get_value(unsigned int position, string& value);

            // Fetches the key and the associated value at a given position and returns true if found
            // if position is out of bounds - false is returned
            bool get_key_value(unsigned int position, string& key, string& value);

            // Iterates over the key value pairs in the header and invokes the
            // supplied function with each key-value pair
            void iterate(std::function<void(const string&, const string&)> itor_func);

            // Fetch the payload stream for this message object
            stringstream& get_payload() { return _payload;}

            // Serialize the message to a collection of const buffers
            // Note: the underlying memory needs to be valid until the 
            // write operation is completed.
            vector<boost::asio::const_buffer> to_buffers();

        private:
            // All headers consist of key-value pairs
            // where the keys are not case sensitive
            // although we store the original case
            struct key_value {
                key_value(const string& key, const string& value)
                    : _key(key), _value(value) {}
                
                string _key;
                string _value;

                string lcase_key() const {
                    return to_lower_copy(_key);
                }
            };

            // container that supports access randomly
            // as well as by key
            typedef multi_index_container   <key_value,
                                                indexed_by<
                                                    random_access<>,
                                                    hashed_unique< 
                                                        const_mem_fun<  key_value, 
                                                                        string, 
                                                                        &key_value::lcase_key
                                                        >
                                                    >
                                                >
                                            > header_collection;

            typedef header_collection::nth_index<0>::type headers_by_position;
            typedef header_collection::nth_index<1>::type headers_by_key;

            header_collection _headers;
            stringstream _payload;
        };


    } // common
} // rest


#endif //__REST_MESSAGE__
