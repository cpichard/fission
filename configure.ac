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
#${CC=clang}
#${CXX=clang++}

AC_PROG_CXX
AC_PROG_MAKE_SET

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AM_PATH_PYTHON(2.3)

AC_CONFIG_MACRO_DIR([m4])

# SWIG 
AC_PATH_PROGS([SWIG],[swig swig2.0])
if test -z "$SWIG" ; then
        enable_swig=no
else
        enable_swig=yes
        AX_PKG_SWIG(1.3.36,[] ,[AC_MSG_ERROR("Swig is required.")])
        AX_SWIG_ENABLE_CXX
        AX_SWIG_MULTI_MODULE_SUPPORT
        AX_SWIG_PYTHON
fi


AC_CONFIG_FILES([
	Makefile
	src/Makefile
    tests/Makefile
    tests/cppunit/Makefile
    drafts/Makefile
    drafts/llvm/Makefile
	])

AC_OUTPUT
