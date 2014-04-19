#include "lib_common\response.hpp"

#include <boost/test/unit_test.hpp>



using namespace rest::common;



BOOST_AUTO_TEST_SUITE( ut_response )

BOOST_AUTO_TEST_CASE( to_buffers )
{
    response respond(response::status_type::ok);
    respond.add_key_value("hello","world");
    respond.add_key_value("hello again","world again");

    vector<boost::asio::const_buffer> buffer;
    respond.to_buffers(buffer);

    auto x = buffer[0];
}



BOOST_AUTO_TEST_SUITE_END()