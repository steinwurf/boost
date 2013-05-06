// Copyright (c) 2013, Steinwurf ApS
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

#include <string>
#include <iterator>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <gtest/gtest.h>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;

/// Helper function to parse IPv4 addresses from a string
/// @param first iterator to beginning of input string
/// @param last iterator to end of input string
/// @param addr reference which will hold the parsed 32-bit
///        representation of the IPv4 address
template<typename Iterator>
void parse_ipv4(Iterator first, Iterator last, uint32_t& addr)
{
    using qi::int_;
    using qi::phrase_parse;
    using ascii::space;
    using boost::phoenix::ref;

    uint32_t one = 0;
    uint32_t two = 0;
    uint32_t three = 0;
    uint32_t four = 0;

    bool r = phrase_parse(first, last,
        (
            int_[ref(one) = qi::_1] >> '.' >>
            int_[ref(two) = qi::_1] >> '.' >>
            int_[ref(three) = qi::_1] >> '.' >>
            int_[ref(four) = qi::_1]
        ), space);

    if(r == false || first != last) // fail if we did not get a full match
    {
        return;
    }

    if(one > 255 || two > 255 || three > 255 || four > 255)
    {
        return;
    }

    addr = (one << 24) | (two << 16) | (three << 8) | four;
}


/// Helper function to generate an IPv4 address string from decimal
/// @param out the output iterator
/// @param addr reference which will hold the parsed 32-bit
///        representation of the IPv4 address
/// @param ec error-code which will hold an error if the parsing fails
template <typename OutputIterator>
void generate_ipv4(OutputIterator out, uint32_t addr)
{
    using karma::int_;
    using karma::generate;

    uint32_t one = (addr >> 24) & 0xff;
    uint32_t two = (addr >> 16) & 0xff;
    uint32_t three = (addr >> 8) & 0xff;
    uint32_t four = addr & 0xff;

    bool r = generate(out,
        (
            int_[karma::_1 = one] << '.' <<
            int_[karma::_1 = two] << '.' <<
            int_[karma::_1 = three] << '.' <<
            int_[karma::_1 = four]
        ));

    if(r == false )
    {
        return;
    }
}

TEST(TestBoostSpirit, parse_ipv4)
{
    const char* str = "127.0.0.1";

    uint32_t addr = 0;
    parse_ipv4(str, str + strlen(str), addr);

    EXPECT_EQ(0x7F000001, addr);
}

TEST(TestBoostSpirit, generate_ipv4)
{
    std::string generated;
    std::back_insert_iterator<std::string> iter(generated);

    uint32_t addr = 0x7F000001;
    generate_ipv4(iter, addr);

    EXPECT_EQ(std::string("127.0.0.1"), generated);
}

