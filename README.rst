Introduction
============

This repo provides a Waf build script for a subset of the Boost C++ Libraries.

We use Boost in several of our libraries. As some of our target platforms
do not have a package manager and since we depend on a quite recent version
we provide it as a dependency.

We use Waf to cross-compile Boost for the different platforms we support.
This repo includes the wscript files needed to build the Boost libraries.

This is in no way a complete build system for Boost, we would be happy to
accept improvements if somebody has time.

.. image:: https://travis-ci.org/steinwurf/boost.svg?branch=master
    :target: https://travis-ci.org/steinwurf/boost

If you have any questions or suggestions about this library, please contact
us at our developer mailing list (hosted at Google Groups):

* http://groups.google.com/group/steinwurf-dev

Documentation
-------------

To get started, see the manual here:
http://docs.steinwurf.com

Quick Start
-----------

If you already installed a C++14 compiler, git and python on your system,
then you can clone this repository to a suitable folder::

    git clone git@github.com:steinwurf/boost.git

Configure and build the project::

    cd boost
    python waf configure
    python waf build

Run the unit tests::

    python waf --run_tests

Upgrade with fabric
-------------------

1. Download the latest Boost release from http://www.boost.org/users/download/

   (Always choose the *.tar.bz2 archive that uses Unix line endings!)

2. Extract the contents of the downloaded archive to some folder(but **not**
   into this repository!)

3. Invoke the ``boost.upgrade`` fabric task to copy the required files from
   the new release to this project (the old files will be deleted first).
   For example::

       fab boost.upgrade:"C:\steinwurf\boost_1_62_0"

4. Create a new branch, and try to compile the new release on the build system
   without any patches to see what errors or warnings are produced.

5. Based on the results, select the patches that are relevant for this release
   and copy them to the **root folder** of this repository.

6. Invoke the ``boost.apply_patches`` fabric task to apply the selected patches
   one-by-one (if a patch cannot be applied cleanly, then fix the conflicts
   manually)::

       fab boost.apply_patches
