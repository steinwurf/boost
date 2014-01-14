News for external-boost-light
=============================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* tbd

1.2.1
-----
* Bugfix: One some platforms linking with librt requires libpthread
  this was not added for boost-chrono

1.2.0
-----
* Upgrade to Boost release 1.55.0
* Bugfix: Fix boost-atomic linking issue in boost-thread with g++ 4.7+
  cross-compilers that do not support atomic locks natively

1.1.0
-----
* Bugfix: Simplify pthread and rt shared library usage on Linux
* Minor: Additional unit tests for boost filesystem and chrono

1.0.0
-----
* Initial release with Boost 1.53.0
