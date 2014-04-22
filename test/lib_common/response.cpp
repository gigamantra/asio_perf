#include "lib_common\response.hpp"

#include <boost/test/unit_test.hpp>



using namespace rest::common;



BOOST_AUTO_TEST_SUITE( ut_response )

BOOST_AUTO_TEST_CASE( to_buffers )
{
    response respond;
    respond.add_key_value("hello","world");

    vector<boost::asio::const_buffer> buffer;
    respond.to_buffer(buffer);
    buffer.clear();
}



BOOST_AUTO_TEST_SUITE_END()