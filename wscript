#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'boost'
VERSION = '2.2.0'

import waflib.extras.wurf_options


def options(opt):

    opt.load('wurf_common_tools')
    opt.load('python')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    # Internal dependencies
    if ctx.is_toplevel():

        ctx.add_dependency(resolve.ResolveVersion(
            name='gtest',
            git_repository='github.com/steinwurf/gtest.git',
            major=3))


def configure(conf):

    conf.load("wurf_common_tools")

    try:
        conf.load('python')
        conf.check_python_headers()
        conf.env['BUILD_PYTHON'] = True
    except:
        conf.env['BUILD_PYTHON'] = False

    if conf.is_mkspec_platform('linux'):

        if not conf.env['LIB_PTHREAD']:
            conf.check_cxx(lib='pthread')

        if not conf.env['LIB_RT']:
            conf.check_cxx(lib='rt')

    # Set the shared defines
    conf.env['DEFINES_BOOST_SHARED'] = _boost_shared_defines(conf)


def _boost_shared_defines(conf):
    """
    returns shared defines for boost
    """

    defines = ['BOOST_ALL_NO_LIB=1', 'BOOST_DETAIL_NO_CONTAINER_FWD',
               'BOOST_SYSTEM_NO_DEPRECATED']

    # Disable the noexcept keyword for all compilers
    defines += ['BOOST_NO_CXX11_NOEXCEPT']

    return defines


def build(bld):

    bld.load("wurf_common_tools")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_BOOST_VERSION="{}"'.format(VERSION))

    include_dirs = ['.', 'src']

    # Build boost thread
    if bld.is_mkspec_platform('windows'):
        bld.stlib(
            features='cxx',
            source=(bld.path.ant_glob('libs/thread/src/win32/*.cpp') +
                    bld.path.ant_glob('libs/thread/src/*.cpp')),
            target='boost_thread',
            includes=include_dirs,
            export_includes=include_dirs,
            defines=['BOOST_THREAD_BUILD_LIB=1'],
            use=['BOOST_SHARED', 'boost_system'])
    else:
        bld.stlib(
            features='cxx',
            source=(bld.path.ant_glob('libs/thread/src/pthread/*.cpp') +
                    bld.path.ant_glob('libs/thread/src/*.cpp')),
            target='boost_thread',
            includes=include_dirs,
            export_includes=include_dirs,
            defines=['BOOST_THREAD_BUILD_LIB=1',
                     'BOOST_THREAD_POSIX'],
            use=['BOOST_SHARED', 'PTHREAD', 'boost_system'])

    # Build boost system
    bld.stlib(
        features='cxx',
        source=['libs/system/src/error_code.cpp'],
        target='boost_system',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_SYSTEM_STATIC_LINK=1'],
        use='BOOST_SHARED')

    # Build boost chrono
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/chrono/src/*.cpp'),
        target='boost_chrono',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_CHRONO_STATIC_LINK=1',
                 'BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING'],
        use=['BOOST_SHARED', 'RT', 'PTHREAD'])

    # Build boost timer
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/timer/src/*.cpp'),
        target='boost_timer',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_TIMER_STATIC_LINK=1'],
        use=['BOOST_SHARED', 'boost_chrono'])

    # Build boost program options
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/program_options/src/*.cpp'),
        target='boost_program_options',
        includes=include_dirs,
        export_includes=include_dirs,
        use='BOOST_SHARED')

    # Build boost iostreams (only the memory mapped files part)
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/iostreams/src/mapped_file.cpp'),
        target='boost_iostreams',
        includes=include_dirs,
        export_includes=include_dirs,
        use='BOOST_SHARED')

    if bld.env['BUILD_PYTHON']:
        # Build boost-python, but only if we managed to find the appropiate
        # Python headers.

        # Set the shared defines that should be used in Python extensions
        bld.env['DEFINES_BOOST_PYTHON_SHARED'] = \
            [
                "BOOST_PYTHON_SOURCE", "BOOST_PYTHON_STATIC_LIB",
                "BOOST_PYTHON_STATIC_MODULE"
            ]

        bld.stlib(
            features='cxx',
            source=bld.path.ant_glob('libs/python/src/**/*.cpp'),
            target='boost_python',
            includes=include_dirs + bld.env['INCLUDES_PYEXT'],
            export_includes=include_dirs,
            use=['BOOST_SHARED', 'BOOST_PYTHON_SHARED'])

    # Build boost filesystem
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/filesystem/src/*.cpp'),
        target='boost_filesystem',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_FILESYSTEM_STATIC_LINK=1'],
        use=['BOOST_SHARED', 'boost_system'])

    # Define boost_includes for apps/libs only using the boost headers
    bld(includes=include_dirs,
        export_includes=include_dirs,
        name='boost_includes',
        use='BOOST_SHARED')

    if bld.is_toplevel():

        bld.recurse('test')
