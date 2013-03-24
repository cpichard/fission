if CPPUNIT
TESTS = $(check_PROGRAMS)
AM_CPPFLAGS = -g -O0 @CPPUNIT_CFLAGS@ -I../../src/
AM_LDFLAGS = -g -O0 @CPPUNIT_LIBS@ -L../../src/ -lfission
fission_test_SOURCES = main.cpp \
ModuleTest.h \
ModuleTest.cpp \
GraphTest.cpp \
GraphTest.h \
ParameterTest.h \
ParameterTest.cpp \
ValueTest.h \
ValueTest.cpp
UNITTESTS_PROGS = fission_test
noinst_PROGRAMS = $(UNITTESTS_PROGS)
check_PROGRAMS = $(UNITTESTS_PROGS)
endif


