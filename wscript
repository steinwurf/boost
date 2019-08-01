#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'boost'
VERSION = '4.0.0'


def configure(conf):

    if conf.is_mkspec_platform('linux'):
        if not conf.env['LIB_PTHREAD']:
            # If we have not looked for pthread yet
            conf.check_cxx(lib='pthread')


def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_BOOST_VERSION="{}"'.format(VERSION))

    bld.env['DEFINES_BOOST_SHARED'] = \
        ['BOOST_ALL_NO_LIB=1', 'BOOST_DETAIL_NO_CONTAINER_FWD',
         'BOOST_SYSTEM_NO_DEPRECATED', 'BOOST_NO_AUTO_PTR']

    include_dirs = ['.']

    # Define boost_includes for apps/libs only using the boost headers
    bld(includes=include_dirs,
        export_includes=include_dirs,
        name='boost_includes',
        use='BOOST_SHARED')

    # boost_asio_includes is used to link with pthreads on Linux
    bld(includes=include_dirs,
        export_includes=include_dirs,
        name='boost_asio_includes',
        use=['BOOST_SHARED', 'PTHREAD'])

    # Build a static library if this is top-level, otherwise just .o files
    features = ['cxx']
    if bld.is_toplevel():
        features += ['cxxstlib']

    # Build boost system
    bld(features=features,
        source=['libs/system/src/error_code.cpp'],
        target='boost_system',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_SYSTEM_STATIC_LINK=1'],
        use='BOOST_SHARED')

    # Build boost program options
    bld(features=features,
        source=bld.path.ant_glob('libs/program_options/src/*.cpp'),
        target='boost_program_options',
        includes=include_dirs,
        export_includes=include_dirs,
        use='BOOST_SHARED')

    # Build boost iostreams (only the memory mapped files part)
    bld(features=features,
        source=bld.path.ant_glob('libs/iostreams/src/mapped_file.cpp'),
        target='boost_iostreams',
        includes=include_dirs,
        export_includes=include_dirs,
        use='BOOST_SHARED')

    # Build boost filesystem
    bld(features=features,
        source=bld.path.ant_glob('libs/filesystem/src/*.cpp'),
        target='boost_filesystem',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_FILESYSTEM_STATIC_LINK=1'],
        use=['BOOST_SHARED', 'boost_system'])

    if bld.is_toplevel():

        bld.recurse('test')
