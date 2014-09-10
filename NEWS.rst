News for external-boost-light
=============================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* Minor: Added boost iostreams (only the subset covering memory mapped files)

1.4.1
-----
* Bugfix: Introduce shared defines for Boost Python which should be used in
  Python extensions that are statically linked with Boost Python.

1.4.0
-----
* Minor: Updated waf to version 1.8.0pre1.
* Bugfix: Restore correct build directory.

1.3.2
-----
* Bugfix: Removed redundant binary and doc files.

1.3.1
-----
* Bugfix: Fixed bug when using boost python as a dependency.

1.3.0
-----
* Minor: Added boost python.
* Bugfix: Fixed bug when building with llvm 5.1. The official patches are
  located here: goo.gl/3ie4Ty and goo.gl/IbkM4S.

1.2.2
-----
* Bugfix: Fix spurious g++ warnings in Boost bind and concept with upstream
  patches.

1.2.1
-----
* Bugfix: On some platforms, linking with librt requires libpthread.
  This was not added for boost-chrono.

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
