// Copyright (c) 2013, Steinwurf ApS
// All rights reserved.

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

// #include <gtest/gtest.h>
// 
// #include <boost/signals2.hpp>
// #include <boost/bind.hpp>
// 
// namespace bs2 = boost::signals2;
// 
// struct signal_emitter
// {
//     typedef bs2::signal<void ()> void_signal;
// 
//     bs2::connection on_event(const void_signal::slot_type& slot)
//     {
//         return m_signal.connect(slot);
//     }
// 
//     void raise_event()
//     {
//         m_signal();
//     }
// 
//     // The signal
//     void_signal m_signal;
// };
// 
// 
// struct signal_receiver
// {
//     signal_receiver() :
//         m_one(0), m_two(0)
//     {
//     }
// 
//     void call_one()
//     {
//         m_one++;
//     }
// 
//     void call_two()
//     {
//         m_two++;
//     }
// 
//     // To check if all callbacks were invoked
//     int m_one;
//     int m_two;
// };
// 
// TEST(TestBoostSignals, connect)
// {
//     signal_emitter emitter;
//     signal_receiver recv;
// 
//     emitter.on_event(
//         boost::bind(&signal_receiver::call_one, &recv));
//     emitter.on_event(
//         boost::bind(&signal_receiver::call_two, &recv));
// 
//     emitter.raise_event();
// 
//     EXPECT_EQ(1, recv.m_one);
//     EXPECT_EQ(1, recv.m_two);
// }






