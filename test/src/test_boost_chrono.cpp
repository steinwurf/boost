// Copyright (c) 2012, Steinwurf ApS
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

#include <iostream>

#include <gtest/gtest.h>

#include <boost/chrono.hpp>

namespace bc = boost::chrono;

TEST(TestBoostChrono, intervals)
{
    using namespace boost::chrono;
    milliseconds ms(2500);
    auto s1 = floor<seconds>(ms);
    s1 = round<seconds>(ms);
    s1 = ceil<seconds>(ms);
    ms = milliseconds(2516);

    typedef duration<long, boost::ratio<1, 30> > frame_rate;
    auto s2 =  floor<frame_rate>(ms);
    s2 = round<frame_rate>(ms);
    s2 = ceil<frame_rate>(ms);
}


template <class Clock>
double get_nanosec(typename Clock::duration delta)
{
    return (double)bc::duration_cast<bc::nanoseconds>(delta).count();
}

TEST(TestBoostChrono, resolution)
{
    using namespace boost::chrono;

    system_clock::time_point d4 = system_clock::now();
    system_clock::time_point d5 = system_clock::now();

    EXPECT_GE(get_nanosec<system_clock>(d5 - d4), 0.0);

    steady_clock::time_point d6 = steady_clock::now();
    steady_clock::time_point d7 = steady_clock::now();

    EXPECT_GE(get_nanosec<steady_clock>(d7 - d6), 0.0);

    high_resolution_clock::time_point d8 = high_resolution_clock::now();
    high_resolution_clock::time_point d9 = high_resolution_clock::now();

    EXPECT_GE(get_nanosec<high_resolution_clock>(d9 - d8), 0.0);
}
