
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

AM_CPPFLAGS = -g -O0 -I`llvm-config --includedir` -I../../src/ `llvm-config --cppflags`

bin_PROGRAMS=llvm_draft
llvm_draft_LINK = $(CXX) -g -O0 -rdynamic -Wl,--whole-archive -L../../src/ -lfission -o llvm_draft -Wl,-no-whole-archive $(CLANGLIBS) `llvm-config --ldflags --libs`
llvm_draft_SOURCES = Main.cpp

