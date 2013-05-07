Introduction
============

This repo provides a Waf build script for a subset of the Boost C++ Libraries.

We use Boost in several of our libraries. As some of our target platforms
do not have a package manager and since we depend on a quite recent version 
we provide it as a dependency. 

We use Waf to cross-compile Boost for the different platforms
we support. For that reason we provide the Waf and wscript files
needed to build the Boost libraries.

This is in no way a complete build system for Boost, we would be happy to 
accept improvements if somebody has time.

Dependencies
------------

1. Git: A suitable git client installed (see the "Set Up Git" guide at 
   the `github help`_ pages)
2. Python: To use Waf you need to install Python version 2.7 or newer. 
3. C++ compiler: To build the Boost libraries you need a C++11 compiler. 

.. _github help: http://help.github.com/

Usage
-----

Download the source from github by cloning the repository. Run this command
from your terminal (Linux) or your Git Bash terminal (Windows)::
  
    git clone https://github.com/steinwurf/external-boost-light.git


To build the libraries for your host platform. The options to configure
```--bundle=ALL```, tells waf to fetch all additional dependencies to build boost.
The ```--bundle-path=/path/to/store/dependencies``` option can also be used to
tell Waf where to store the dependencies:: 

    python waf configure --bundle=ALL
    python waf build


