#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'boost'
VERSION = '3.1.8'


def configure(conf):

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
               'BOOST_SYSTEM_NO_DEPRECATED', 'BOOST_NO_AUTO_PTR']

    return defines


def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_BOOST_VERSION="{}"'.format(VERSION))

    include_dirs = ['.']

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
