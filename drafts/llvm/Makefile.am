
LOCALLIBS=/home/cyril/usr/local/lib

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

AM_CPPFLAGS = -g -O0 -I/home/cyril/usr/local/include -I../../src/ `llvm-config --cppflags`
AM_LDFLAGS = -g -O0 -L../../src -lfission $(CLANGLIBS) `llvm-config --ldflags --libs`


bin_PROGRAMS=llvm_draft
llvm_draft_SOURCES = Main.cpp

