if CPPUNIT

LOCALLIBS=`llvm-config --libdir`

CLANGLIBS = $(LOCALLIBS)/libclangFrontendTool.a \
$(LOCALLIBS)/libclangFrontend.a \
$(LOCALLIBS)/libclangDriver.a \
$(LOCALLIBS)/libclangSerialization.a \
$(LOCALLIBS)/libclangCodeGen.a \
$(LOCALLIBS)/libclangParse.a \
$(LOCALLIBS)/libclangSema.a \
$(LOCALLIBS)/libclangStaticAnalyzerFrontend.a \
$(LOCALLIBS)/libclangStaticAnalyzerCheckers.a \
$(LOCALLIBS)/libclangStaticAnalyzerCore.a \
$(LOCALLIBS)/libclangAnalysis.a \
$(LOCALLIBS)/libclangARCMigrate.a \
$(LOCALLIBS)/libclangRewriteFrontend.a \
$(LOCALLIBS)/libclangRewriteCore.a \
$(LOCALLIBS)/libclangEdit.a \
$(LOCALLIBS)/libclangAST.a \
$(LOCALLIBS)/libclangLex.a \
$(LOCALLIBS)/libclangBasic.a


TESTS = $(check_PROGRAMS)
AM_CPPFLAGS = -g -O0 @CPPUNIT_CFLAGS@ -I../../src/
#AM_LDFLAGS = -g -O0 @CPPUNIT_LIBS@ -L../../src/ -lfission
fission_test_LINK = $(CXX) -g -O0 @CPPUNIT_LIBS@ -rdynamic -Wl,--whole-archive -L../../src/ -lfission -o fission_test -Wl,-no-whole-archive $(CLANGLIBS) `llvm-config --ldflags --libs`
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


