if CPPUNIT
TESTS = $(check_PROGRAMS)
AM_CPPFLAGS = @CPPUNIT_CFLAGS@ -I../../src/engine -I../../src/graph -I../../src/nodes -I../../src/rtts
AM_LDFLAGS = @CPPUNIT_LIBS@ -lfission
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


