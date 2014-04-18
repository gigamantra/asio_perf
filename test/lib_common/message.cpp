#include "lib_common\message.hpp"

#include <boost/test/unit_test.hpp>
#include <sstream>


using namespace rest::common;

BOOST_AUTO_TEST_SUITE( unit_test_message )

BOOST_AUTO_TEST_CASE( add_key_value )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 100; ++i){
        stringstream ss;
        ss << i;
        string key(ss.str());
        ss << ".value";
        string value(ss.str());
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }
}

BOOST_AUTO_TEST_CASE( update_value )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i;
        string key(ss.str());
        ss << ".value";
        string value(ss.str());
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i;
        string key(ss.str());
        ss << ".new.value";
        string value(ss.str());
        msg.update_value(key, value);
    }
    BOOST_CHECK( msg.get_number_of_key_values() == 10000);

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i;
        string key(ss.str());
        ss << ".new.value";
        string updatedValue(ss.str());
        string value;
        msg.get_value(key, value);
        BOOST_CHECK( value == updatedValue);
    }
}

BOOST_AUTO_TEST_CASE( update_value_by_position )
{
    message msg;
    BOOST_CHECK(0 == msg.get_number_of_key_values());

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i;
        string key(ss.str());
        ss << ".value";
        string value(ss.str());
        msg.add_key_value(key, value);
        BOOST_CHECK( msg.get_number_of_key_values() == i+1);
    }

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i << ".new.value";
        string value(ss.str());
        msg.update_value(i, value);
        
    }
    BOOST_CHECK( msg.get_number_of_key_values() == 10000);

    for (int i =0; i < 10000; ++i){
        stringstream ss;
        ss << i << ".new.value";
        string updatedValue(ss.str());
        string value;
        msg.get_value(i, value);
        BOOST_CHECK( value == updatedValue);
    }
}


BOOST_AUTO_TEST_SUITE_END()
