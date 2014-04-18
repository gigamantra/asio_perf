#include <iostream>
#include <string>


#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>


#include "server.hpp"


using namespace std;


void print_usage()
{
    cout    << "Usage: rest_svc <port> <num threads>" << endl
            << "Defaulting to port 8000 and 8 threads." << endl;
}


int main(int argc, char* argv[]) 
{
    try {
        // Set up suitable defaults for our service
        string port = "8000";
        size_t num_threads = 8;

        // try and over ride them with arguments passed in
        if (3 != argc ) {
            print_usage();
        } else {
            port = argv[1];
            num_threads = boost::lexical_cast<std::size_t>(argv[2]);
        }

        // Initialize the service...
        rest::svc::server svc(port, num_threads);

        // ... and run it until stopped.
        svc.run();

    } catch (const exception& ex) {
        cerr << "Exception: " << ex.what() << endl;
    }

    return 0;
}
