#include "lib.h"

#define BOOST_TEST_MODULE project_test

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using namespace std;
using test_stream = boost::test_tools::output_test_stream;

struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer )
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

private:
    std::streambuf * old;
};

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_print_ip)
{
    test_stream stream;
    cout_redirect tmp(stream.rdbuf());

    print_ip(char(-1));
    BOOST_CHECK(stream.is_equal("255\n"));

    stream.clear();
    print_ip(short(0));
    BOOST_CHECK(stream.is_equal("0.0\n"));

    stream.clear();
    print_ip(int(2130706433));
    BOOST_CHECK(stream.is_equal("127.0.0.1\n"));

    stream.clear();
    print_ip(long(8875824491850138409));
    BOOST_CHECK(stream.is_equal("123.45.67.89.101.112.131.41\n"));

    stream.clear();
    print_ip("192.168.1.1");
    BOOST_CHECK(stream.is_equal("192.168.1.1\n"));

    stream.clear();
    print_ip(vector<int>{ 192, 168, 1, 2 });
    BOOST_CHECK(stream.is_equal("192.168.1.2\n"));

    stream.clear();
    print_ip(list<long>{ 192, 168, 1, 3 });
    BOOST_CHECK(stream.is_equal("192.168.1.3\n"));

    stream.clear();
    print_ip(make_tuple(192, 168, 1, 4));
    BOOST_CHECK(stream.is_equal("192.168.1.4\n"));

    stream.clear();
    print_ip(make_tuple("192", "168", "1", "5"));
    BOOST_CHECK(stream.is_equal("192.168.1.5\n"));




    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
