#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'boost-light'
VERSION = '1.2.2'


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse([p])


def options(opt):

    import waflib.extras.wurf_dependency_bundle as bundle
    import waflib.extras.wurf_dependency_resolve as resolve

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/external-waf-tools.git',
        major_version=2))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='gtest',
        git_repository='github.com/steinwurf/external-gtest.git',
        major_version=2))

    opt.load("wurf_dependency_bundle")
    opt.load('wurf_tools')


def configure(conf):

    if conf.is_toplevel():

        conf.load("wurf_dependency_bundle")
        conf.load("wurf_tools")
        conf.load_external_tool('mkspec', 'wurf_cxx_mkspec_tool')
        conf.load_external_tool('runners', 'wurf_runner')
        conf.load_external_tool('install_path', 'wurf_install_path')
        conf.load_external_tool('project_gen', 'wurf_project_generator')

        recurse_helper(conf, 'gtest')
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


def boost_cxx_flags(bld):
    """
    returns cxx flags used to compile the boost libs
    """
    CXX = bld.env.get_flat("CXX")

    # Matches both /usr/bin/g++ and /user/bin/clang++
    if 'g++' in CXX or 'clang' in CXX:
        return ['-pedantic', '-finline-functions', '-Wno-inline',
                '-Wno-long-long']

    elif 'CL.exe' in CXX or 'cl.exe' in CXX:
        return ['/GR', '/Zc:forScope', '/Zc:wchar_t', '/wd4675']

    else:
        bld.fatal('unknown compiler no boost flags specified')


def boost_shared_defines(bld):
    """
    returns shared defines for boost
    """

    defines = \
        [
            'BOOST_ALL_NO_LIB=1', 'BOOST_DETAIL_NO_CONTAINER_FWD'
        ]

    CXX = bld.env.get_flat("CXX")
    # Matches both /usr/bin/g++ and /user/bin/clang++
    if 'g++' in CXX or 'clang' in CXX:
        defines += ['BOOST_NO_CXX11_NOEXCEPT']

    if bld.is_mkspec_platform('android'):
        # Android does not seem to have an intrincsic wchar_t.
        # See the toolchain sysroot/usr/include/wchar.h it is simply a
        # define. Also wchar_t support is quite broken on Android so we
        # should avoid using it anyway.
        # See NDK docs docs/STANDALONE-TOOLCHAIN.html
        # section 5.2
        defines += ['__GLIBC__', '_GLIBCXX_USE_WCHAR_T']

        # Problem with boost::chrono and std::u16string and friends
        # http://goo.gl/3FJc5r
        # Work around seems to be to add:
        defines += ['_GLIBCXX_USE_C99_STDINT_TR1']

    return defines


def build(bld):

    # Set the boost specific cxx flags
    bld.env['CXXFLAGS_BOOST_SHARED'] = boost_cxx_flags(bld)

    # Set the shared defines
    bld.env['DEFINES_BOOST_SHARED'] = boost_shared_defines(bld)

    include_dirs = ['.']

    # Build boost thread
    if bld.is_mkspec_platform('windows'):
        bld.stlib(
            features='cxx',
            source=bld.path.ant_glob('libs/thread/src/win32/*.cpp') +
            bld.path.ant_glob('libs/thread/src/*.cpp'),
            target='boost_thread',
            includes=include_dirs,
            export_includes=include_dirs,
            defines=['BOOST_THREAD_BUILD_LIB=1'],
            use='BOOST_SHARED')
    else:
        bld.stlib(features='cxx',
                  source=bld.path.ant_glob('libs/thread/src/pthread/*.cpp') +
                  bld.path.ant_glob('libs/thread/src/*.cpp'),
                  target='boost_thread',
                  includes=include_dirs,
                  export_includes=include_dirs,
                  defines=['BOOST_THREAD_BUILD_LIB=1',
                           'BOOST_THREAD_POSIX'],
                  use=['BOOST_PAGESIZE_FIX', 'BOOST_SHARED', 'PTHREAD'])

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
        defines=['BOOST_SYSTEM_STATIC_LINK=1',
                 'BOOST_SYSTEM_NO_DEPRECATED'],
        use=['BOOST_SHARED', 'RT', 'PTHREAD'])

    # Build boost timer
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/timer/src/*.cpp'),
        target='boost_timer',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_SYSTEM_STATIC_LINK=1',
                 'BOOST_SYSTEM_NO_DEPRECATED',
                 'BOOST_SYSTEM_STATIC_LINK=1',
                 'BOOST_CHRONO_STATIC_LINK=1',
                 'BOOST_TIMER_STATIC_LINK=1'],
        use='BOOST_SHARED')

    # Build boost program options
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/program_options/src/*.cpp'),
        target='boost_program_options',
        includes=include_dirs,
        export_includes=include_dirs,
        use='BOOST_SHARED')
    if bld.env['BUILD_PYTHON']:
        # Build boost python, but only if we managed to find the appropiate
        # python headers.
        bld.stlib(
            features='cxx',
            source=(bld.path.ant_glob('libs/python/src/*.cpp') +
                    bld.path.ant_glob('libs/python/src/object/*.cpp') +
                    bld.path.ant_glob('libs/python/src/converter/*.cpp')),
            target='boost_python',
            includes=include_dirs + bld.env['INCLUDES_PYEXT'],
            export_includes=include_dirs,
            defines=["BOOST_PYTHON_SOURCE", "BOOST_PYTHON_STATIC_LIB"],
            use=['BOOST_SHARED'])

    # Build boost filesystem
    bld.stlib(
        features='cxx',
        source=bld.path.ant_glob('libs/filesystem/src/*.cpp'),
        target='boost_filesystem',
        includes=include_dirs,
        export_includes=include_dirs,
        defines=['BOOST_SYSTEM_STATIC_LINK=1',
                 'BOOST_FILESYSTEM_STATIC_LINK=1'],
        use='BOOST_SHARED')

    # Make use flag for apps/libs only using the boost headers
    bld(includes=include_dirs,
        export_includes=include_dirs,
        name='boost_includes',
        use='BOOST_SHARED')

    if bld.is_toplevel():

        bld.load('wurf_dependency_bundle')

        recurse_helper(bld, 'gtest')

        bld.recurse('test')
