if CPPUNIT
TESTS = $(check_PROGRAMS)
AM_CPPFLAGS = @CPPUNIT_CFLAGS@ -I../../src/engine -I../../src/graph -I../../src/nodes   
AM_LDFLAGS = @CPPUNIT_LIBS@ -L/Users/cyril/usr/local/lib -lfission
engine_test_SOURCES = main.cpp GraphTest.cpp GraphTest.h
UNITTESTS_PROGS = engine_test
noinst_PROGRAMS = $(UNITTESTS_PROGS)
check_PROGRAMS = $(UNITTESTS_PROGS)
endif


