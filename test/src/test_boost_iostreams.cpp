// Copyright (c) 2014, Steinwurf ApS
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

#include <boost/iostreams/device/mapped_file.hpp>

#include <cstdlib>

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

TEST(TestBoostIostreams, mapped_file)
{
    std::string filename = "mapped_file.bin";
    uint32_t size = 4567;

    // Make sure that the test file does not exist before starting the test
    boost::filesystem::remove(filename);

    boost::iostreams::mapped_file_params params;
    params.path = "mapped_file.bin";
    params.new_file_size = size;

    auto file = boost::iostreams::mapped_file_sink(params);

    EXPECT_TRUE(file.is_open());
    EXPECT_EQ(file.size(), size);

    // Create a vector of random bytes
    std::vector<char> buffer(size);
    for (uint32_t i = 0; i < buffer.size(); ++i)
    {
        buffer[i] = rand() % 256;
    }

    // Write this random data to the file
    memcpy(file.data(), buffer.data(), size);

    file.close();

    // Re-open the same file and verify that the random bytes are not zeroed!
    // It is important to preserve the data when using a file coder
    // which is stopped after completing some blocks, and restarted later.

    boost::iostreams::mapped_file_params params2;
    params2.path = "mapped_file.bin";
    // We do not set the "new_file_size" property for params2

    auto file2 = boost::iostreams::mapped_file_sink(params2);

    EXPECT_TRUE(file2.is_open());
    EXPECT_EQ(file2.size(), size);

    // Copy the file data to a vector for comparison
    std::vector<char> reopened(file2.data(), file2.data() + file2.size());
    EXPECT_EQ(buffer, reopened);

    file2.close();
}
