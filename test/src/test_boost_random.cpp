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

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/bernoulli_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>

#include <cstdlib>
#include <limits>
#include <vector>

#include <gtest/gtest.h>

using namespace boost::random;

namespace
{
    template<class T>
    void test_uniform(mt19937& random_generator, uint32_t count,
                      std::vector<T> expected_results)
    {
        uniform_int_distribution<T> distribution;

        std::vector<T> results;
        for (uint32_t i = 0; i < count; ++i)
        {
            T value = distribution(random_generator);
            results.push_back(value);
            EXPECT_GE(value, (T)0);
            EXPECT_LE(value, std::numeric_limits<T>::max());
        }

        EXPECT_EQ(expected_results, results);
    }


    void test_bernoulli(mt19937& random_generator, uint32_t count,
                        uint32_t expected_heads,
                        std::vector<uint32_t> expected_results)
    {
        bernoulli_distribution<> bernoulli(0.5);

        uint32_t heads = 0;
        std::vector<uint32_t> results;
        for (uint32_t i = 0; i < count; ++i)
        {
            if (bernoulli(random_generator))
            {
                heads++;
                results.push_back(i);
            }
        }
        EXPECT_EQ(heads, expected_heads);
        EXPECT_EQ(expected_results, results);
    }

    void test_binomial(uint32_t seed, uint32_t n, uint32_t count,
                       std::vector<uint32_t> expected_results)
    {
        mt19937 random_generator;
        random_generator.seed(seed);

        binomial_distribution<> binomial(n, 0.5);

        uint32_t heads = 0;
        std::vector<uint32_t> results;
        for (uint32_t i = 0; i < count; ++i)
        {
            heads = binomial(random_generator);
            results.push_back(heads);
            EXPECT_GE(heads, 0U);
            EXPECT_LE(heads, n);
        }
        EXPECT_EQ(expected_results, results);
    }
}

TEST(TestBoostRandom, mt19937_uniform_distribution_uint8)
{
    mt19937 random_generator;

    uint32_t count = 10;

    random_generator.seed(42);

    std::vector<uint8_t> expected_results =
        { 95, 203, 243, 46, 187, 199, 153, 152, 39, 114 };
    test_uniform<uint8_t>(random_generator, count, expected_results);

    random_generator.seed(123456);

    expected_results =
        { 32, 131, 247, 229, 66, 180, 229, 199, 96, 238 };
    test_uniform<uint8_t>(random_generator, count, expected_results);
}

TEST(TestBoostRandom, mt19937_uniform_distribution_uint16)
{
    mt19937 random_generator;

    uint32_t count = 10;

    random_generator.seed(1337);

    std::vector<uint16_t> expected_results =
        { 17172, 36734, 10399, 13932, 18227, 35591, 30101, 2226, 21037, 15426 };
    test_uniform<uint16_t>(random_generator, count, expected_results);

    random_generator.seed(123456);

    expected_results =
        { 8321, 33745, 63354, 58859, 17070, 46256, 58801, 51041, 24690, 61054 };
    test_uniform<uint16_t>(random_generator, count, expected_results);
}

TEST(TestBoostRandom, mt19937_uniform_distribution_uint32)
{
    mt19937 random_generator;

    uint32_t count = 10;

    random_generator.seed(42);

    std::vector<uint32_t> expected_results =
        { 1608637542, 3421126067, 4083286876, 787846414, 3143890026,
          3348747335, 2571218620, 2563451924, 670094950, 1914837113 };
    test_uniform<uint32_t>(random_generator, count, expected_results);

    random_generator.seed(123456);

    expected_results =
        { 545331265, 2211535594, 4152021490, 3857419313, 1118735928,
          3031474347, 3853601519, 3345048107, 1618127707, 4001288224 };
    test_uniform<uint32_t>(random_generator, count, expected_results);
}

TEST(TestBoostRandom, mt19937_bernoulli_distribution)
{
    mt19937 random_generator;
    random_generator.seed(42);

    std::vector<uint32_t> expected_results =
        { 0, 3, 8, 9, 10, 11, 12, 13, 15, 17 };
    test_bernoulli(random_generator, 20, 10, expected_results);

    random_generator.seed(123456);

    expected_results =
        { 0, 4, 8, 10, 12, 13, 15, 16, 17, 19 };
    test_bernoulli(random_generator, 20, 10, expected_results);
}

TEST(TestBoostRandom, mt19937_binomial_distribution_10)
{
    // binomial_distribution uses the "inversion" algorithm if (n+1) * p < 11
    std::vector<uint32_t> expected_results =
        { 4, 5, 3, 4, 4, 5, 5, 2, 4, 4, 5, 5, 4, 4, 8, 4, 6, 4, 3, 6 };
    test_binomial(1337, 10, 20, expected_results);
}

TEST(TestBoostRandom, mt19937_binomial_distribution_100)
{
    // binomial_distribution uses the "BTRD" algorithm if (n+1) * p >= 11
    std::vector<uint32_t> expected_results =
        { 50, 49, 50, 39, 43, 51, 49, 58, 64, 52,
          47, 46, 48, 46, 48, 46, 47, 55, 41, 52 };
    test_binomial(1337, 100, 20, expected_results);
}
