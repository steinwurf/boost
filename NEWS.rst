News for boost
==============

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* Minor: Updated waf.

4.0.2
-----
* Patch: Fixed g++ 9 warnings in boost::iostreams.

4.0.1
-----
* Patch: Added boost_asio_includes to allow automatic linking with pthreads
  on Linux (this is required by boost::asio).

4.0.0
-----
* Major: Removed the boost-python, boost-thread, boost-chrono and boost-timer
  libraries which should be replaced by C++14 built-in libraries.
* Major: Upgrade to Boost release 1.70.0.

3.1.8
-----
* Patch: Avoid the double configuration of Python extension build flags.
  Another library (e.g. pybind11) might be the first to run this configuration
  step, so it would be problematic to repeat that.
* Patch: Use ``poll.h`` include instead of ``sys/poll.h`` in boost::asio.

3.1.7
-----
* Patch: Suppressed some clang 7.0 warnings when compiling boost-python.

3.1.6
-----
* Patch: Suppressed some new clang warnings when compiling boost-python.

3.1.5
-----
* Patch: Suppressed some warnings in boost::filesystem.

3.1.4
-----
* Patch: Suppressed some warnings for newer compilers to maintain compatibility
  with Python 2.7 headers when compiling boost-python.

3.1.3
-----
* Patch: Fixed boost::thread compatibility with Visual Studio 2017.

3.1.2
-----
* Patch: Improved compatibility with g++ 8 and Python 3.7.

3.1.1
-----
* Patch: Suppressed g++ initialization warning in boost/python/extract.hpp.

3.1.0
-----
* Minor: Fixed the overwriting behavior of the iostreams mapped_file: when
  opening an existing file, the original content will be preserved instead
  of overwriting the file with zeroes. Also added a corresponding unit test
  to expose this issue.
* Patch: Fixed the _FILE_OFFSET_BITS define in boost::filesystem which led to
  some compilation issues with the Android NDK r15 and later.

3.0.0
-----
* Major: Upgrade to waf-tools 4
* Minor: Upgrade to gtest 4

2.3.0
-----
* Minor: Added unit test for boost::dynamic_bitset.
* Patch: Fixed warnings in boost::asio and boost::dynamic_bitset.

2.2.1
-----
* Patch: Removed obsolete defines for Android, which can cause issues with
  the recent NDK toolchains (especially with threads and mutexes).

2.2.0
-----
* Minor: Upgrade to Boost release 1.62.0

2.1.0
-----
* Minor: Upgrade to Boost release 1.60.0

2.0.0
-----
* Major: Upgrade to waf-tools 3
* Minor: Upgrade to gtest 3

1.11.0
------
* Minor: Upgrade to Boost release 1.59.0

1.10.0
------
* Minor: Upgrade to Boost release 1.58.0

1.9.1
-----
* Patch: Removed shared CXXFLAGS to avoid conflicts with the flags defined in
  various mkspecs. The ``-pedantic`` and ``-finline-functions`` flags are
  moved to ``gxx_common.py`` in waf-tools, so these will be applied for all
  projects.

1.9.0
-----
* Minor: Added tests for boost::random to verify that the same random values
  are generated on all platforms.
* Patch: Fixed warnings in ``boost/random/binomial_distribution.hpp``.

1.8.1
-----
* Patch: Fix version define.

1.8.0
-----
* Minor: Added version define.

1.7.0
-----
* Minor: Added support for Emscripten compiler.
* Patch: Moved ``boost_cxx_flags`` and ``boost_shared_defines`` from ``build``
  to ``configure``.

1.6.0
-----
* Minor: Upgrade to Boost release 1.56.0
* Minor: Removed compiler flags that are not supported by clang 3.5

1.5.1
-----
* Patch: Fixed a bug that made boost think that clang doesn't have
  ``std::shared_ptr``. The bug was fixed by using the following `patch
  <http://goo.gl/ooTmbd>`_.

1.5.0
-----
* Minor: Added boost iostreams (only the subset covering memory mapped files)

1.4.1
-----
* Patch: Introduce shared defines for Boost Python which should be used in
  Python extensions that are statically linked with Boost Python.

1.4.0
-----
* Minor: Updated waf to version 1.8.0pre1.
* Patch: Restore correct build directory.

1.3.2
-----
* Patch: Removed redundant binary and doc files.

1.3.1
-----
* Patch: Fixed bug when using boost python as a dependency.

1.3.0
-----
* Minor: Added boost python.
* Patch: Fixed bug when building with llvm 5.1. The official patches are
  located here: goo.gl/3ie4Ty and goo.gl/IbkM4S.

1.2.2
-----
* Patch: Fix spurious g++ warnings in Boost bind and concept with upstream
  patches.

1.2.1
-----
* Patch: On some platforms, linking with librt requires libpthread.
  This was not added for boost-chrono.

1.2.0
-----
* Upgrade to Boost release 1.55.0
* Patch: Fix boost-atomic linking issue in boost-thread with g++ 4.7+
  cross-compilers that do not support atomic locks natively

1.1.0
-----
* Patch: Simplify pthread and rt shared library usage on Linux
* Minor: Additional unit tests for boost filesystem and chrono

1.0.0
-----
* Initial release with Boost 1.53.0
