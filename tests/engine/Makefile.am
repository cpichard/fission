AM_CPPFLAGS = @CPPUNIT_CFLAGS@ -I../../src/engine 
AM_LDFLAGS = @CPPUNIT_LIBS@ -L/Users/cyril/usr/local/lib -lfission

engine_test_SOURCES = main.cpp GraphTest.cpp GraphTest.h


## Target check - runs tests
UNITTESTS_PROGS = engine_test
noinst_PROGRAMS = $(UNITTESTS_PROGS)
check_PROGRAMS = $(UNITTESTS_PROGS)
TESTS = $(check_PROGRAMS)
