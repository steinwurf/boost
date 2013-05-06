// Copyright (c) 2012-2013, Steinwurf ApS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Steinwurf ApS nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL Steinwurf ApS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <cstdlib>

#include <gtest/gtest.h>
#include <boost/asio.hpp>

namespace ba = boost::asio;
using namespace boost::asio::ip;

TEST(TestBoostAsio, udp_construct_bind)
{
    ba::io_service io_service;
    // Create udp socket
    udp::socket socket(io_service);
    // Open the socket
    socket.open(udp::v4());
    // Set the reuse address flag
    socket.set_option(ba::socket_base::reuse_address(true));
    // Bind to a random port on localhost
    socket.bind(udp::endpoint(address_v4::loopback(), 0));
}

TEST(TestBoostAsio, tcp_construct_client)
{
    ba::io_service io_service;
    // Create udp socket
    tcp::socket socket(io_service);
}

TEST(TestBoostAsio, tcp_construct_acceptor)
{
    ba::io_service io_service;
    // Create udp socket
    tcp::acceptor socket(io_service);
    // Open the socket
    socket.open(tcp::v4());
    // Set the reuse address flag
    socket.set_option(ba::socket_base::reuse_address(true));
    // Bind to a random port on localhost
    socket.bind(tcp::endpoint(address_v4::loopback(), 0));
    // Start listening for connections
    socket.listen(ba::socket_base::max_connections);
}