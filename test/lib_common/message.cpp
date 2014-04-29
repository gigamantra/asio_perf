#include "lib_common/message.hpp"

#include <boost/test/unit_test.hpp>
#include <sstream>


using namespace rest::common;

void populate_key_value( int count, string& key, string& value )
{
    stringstream ss;
    ss << count;
    key = ss.str();
    ss << ".value";
    value = ss.str();
}

void get_updated_key_value( int count, string& key, string& value )
{
    stringstream ss;
    ss << count;
    key = ss.str();
    ss << ".new.value";
    value = ss.str();
}


BOOST_AUTO_TEST_SUITE( ut_message )

BOOST_AUTO_TEST_CASE( add_key_value )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 100; ++i){
        string key, value;
        populate_key_value(i, key, value);
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }
}

BOOST_AUTO_TEST_CASE( update_value )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 100; ++i){
        string key, value;
        populate_key_value(i, key, value);
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }

    for (int i =0; i < 100; ++i){
        string key, value;
        get_updated_key_value(i, key, value);
        msg.update_value(key, value);
    }
    BOOST_CHECK( msg.get_number_of_key_values() == 100);

    for (int i =0; i < 100; ++i){
        string key, value, updatedValue;
        get_updated_key_value(i, key, value);
        msg.get_value(key, updatedValue);
        BOOST_CHECK( value == updatedValue);
    }
}

BOOST_AUTO_TEST_CASE( update_value_by_position )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 100; ++i){
        string key, value;
        populate_key_value(i, key, value);
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }

    for (int i =0; i < 100; ++i){
        stringstream ss;
        ss << i << ".new.value";
        string value(ss.str());
        msg.update_value(i, value);
        
    }
    BOOST_CHECK( msg.get_number_of_key_values() == 100);

    for (int i =0; i < 100; ++i){
        stringstream ss;
        ss << i << ".new.value";
        string updatedValue(ss.str());
        string value;
        msg.get_value(i, value);
        BOOST_CHECK( value == updatedValue);
    }
}


BOOST_AUTO_TEST_CASE(iterate_over_entries)
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 100; ++i){
        string key, value;
        populate_key_value(i, key, value);
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }

    int count = 0;
    msg.iterate( [count](const string& key, const string& value) mutable
        {
            string orig_key, orig_value;
            populate_key_value(count++, orig_key, orig_value);
            BOOST_CHECK(key == orig_key);
            BOOST_CHECK(value == orig_value);
        } 
    );
}

BOOST_AUTO_TEST_SUITE_END()
