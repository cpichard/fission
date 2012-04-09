#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# TODO make tags with correct cuda tagging
#ctags --langmap=c:+.cu --exclude=".pc" --recurse 

AC_PREREQ(2.61)
AC_INIT(fission, 0.1, cyril.pichard@xxxxxx.xxx)
AC_CONFIG_SRCDIR(src)
#AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE

# cppUnit testing
AC_ARG_ENABLE(cppunit,
  [AS_HELP_STRING([--enable-cppunit], [enable unit testing (default: yes)])],
  [], [])
AC_MSG_RESULT($enable_cppunit)
AM_CONDITIONAL(CPPUNIT, test "$enable_cppunit" = yes)
if test "$enable_cppunit" = yes; then
  AM_PATH_CPPUNIT(1.9.0,
          [AM_CONDITIONAL(CPPUNIT, true)],
          [AM_CONDITIONAL(CPPUNIT, false)])
fi


# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET



AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AM_PATH_PYTHON(2.3)
AC_PROG_SWIG(1.3.21)
SWIG_ENABLE_CXX
SWIG_PYTHON



#AC_ARG_WITH([boost-include-path],
#  [AS_HELP_STRING([--with-boost-include-path],
#    [location of the boost libraries])],
#  [BOOST_CFLAGS="-I$withval"],
#  [BOOST_CFLAGS='-I/home/cyril/Installs/boost_1_45_0/'])
#AC_SUBST([BOOST_CFLAGS])
#
#AC_ARG_WITH([boost-lib-path],
#  [AS_HELP_STRING([--with-boost-lib-path],
#    [location of the boost libs])],
#  [BOOST_LIBS="-L$withvali"],
#  [BOOST_LIBS='-L/usr/local/lib/ -lboost_thread -lboost_program_options -lboost_system'])
#AC_SUBST([BOOST_LIBS])

#AC_ARG_WITH([tbb-lib-path],
#  [AS_HELP_STRING([--with-tbb-include-path],
#    [location of the tbb libs])],
#  [TBB_LIBS="-L$withvali"],
#  [TBB_LIBS='-L/home/cyril/Installs/tbb22_20090809oss/build/linux_ia32_gcc_cc4.3.2_libc2.7_kernel2.6.26_release/ -ltbb'])
#AC_SUBST([TBB_LIBS])



AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/engine/Makefile
	src/bindings/python/Makefile
    tests/Makefile
    tests/engine/Makefile
	])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
