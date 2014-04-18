#include "server.hpp"


#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


#include <vector>
#include <iostream>


using namespace std;
using namespace rest::svc;


server::server(const std::string& port, std::size_t thread_pool_size)
                :
                thread_pool_size_(thread_pool_size),
                signals_(io_service_),
                acceptor_(io_service_),
                new_connection_(),
                request_handler_(".") 
{
    // Register for ctrl-c, ctrl-break etc so that
    // we know when the user wants to shut us down
    signals_.add(SIGINT);
    signals_.add(SIGTERM);

#if defined(SIGBREAK)
    signals_.add(SIGBREAK);
#endif // defined(SIGBREAK)

#if defined(SIGQUIT)
    signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)

    // Set handle_stop as the shutdown handler
    signals_.async_wait(boost::bind(&server::handle_stop, this));

    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query("0.0.0.0", port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    start_accept();
}


void server::run()
{
    // Create a pool of threads to run all of the io_services.
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < thread_pool_size_; ++i) {
        boost::shared_ptr<boost::thread> thread( new boost::thread( 
            boost::bind(&boost::asio::io_service::run, &io_service_) ) );
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    cout << "Waiting for all threads to shut down" << endl;
    for (std::size_t i = 0; i < threads.size(); ++i) {
        threads[i]->join();
    }

    cout << "All threads shut down successfully" << endl;
}


void server::start_accept()
{
    new_connection_.reset(new connection(io_service_, request_handler_));
    acceptor_.async_accept( new_connection_->socket(),
                            boost::bind(&server::handle_accept, 
                            this,
                            boost::asio::placeholders::error));
}


void server::handle_accept(const boost::system::error_code& e)
{
    if (!e) {
        new_connection_->start();
    }

    start_accept();
}

void server::handle_stop()
{
    cout << "Shutting down rest service" << endl;
    io_service_.stop();
}


