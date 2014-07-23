
LOCALLIBS=`llvm-config --libdir`

CLANGLIBS = -lclangFrontendTool \
-lclangFrontend \
-lclangDriver \
-lclangSerialization \
-lclangCodeGen \
-lclangParse \
-lclangSema \
-lclangStaticAnalyzerFrontend \
-lclangStaticAnalyzerCheckers \
-lclangStaticAnalyzerCore \
-lclangAnalysis \
-lclangARCMigrate \
-lclangRewriteFrontend \
-lclangRewriteCore \
-lclangEdit \
-lclangAST \
-lclangLex \
-lclangBasic

CLANG_RESSOURCEDIR=`llvm-config --libdir`/clang/3.4
SRC_DIR=@abs_srcdir@

AM_CPPFLAGS = -g -O0 -Wall -DSRC_DIR=\"$(SRC_DIR)\" -DCLANG_RESSOURCEDIR=\"$(CLANG_RESSOURCEDIR)\" -Iengine/ -Igraph/ -Inodes/ -Irtts/  `llvm-config --cppflags`


lib_LTLIBRARIES=libfission.la
libfission_la_LDFLAGS = -g -O0 -Wall --export-all-symbols -L$(LOCALLIBS)/ $(CLANGLIBS) `llvm-config --libs` -ldl -lpthread -ltinfo
libfission_la_SOURCES = \
./engine/ComputeEngine.cpp\
./engine/ComputeEngine.h\
./engine/Context.h\
./engine/JITEngine.cpp\
./engine/JITEngine.h\
./engine/NodeCompiler.cpp\
./engine/NodeCompiler.h\
./engine/Status.h\
./graph/Edge.h\
./graph/Graph.h\
./graph/Module.cpp\
./graph/Module.h\
./graph/Name.h\
./graph/Node.cpp\
./graph/NodeDesc.h\
./graph/Node.h\
./graph/ObjectId.h\
./graph/ObjectId.cpp\
./graph/Parameter.cpp\
./graph/Parameter.h\
./graph/Plug.cpp\
./graph/Plug.h\
./graph/PlugLink.h\
./graph/PlugLink.cpp\
./graph/Vertex.h\
./rtts/StandardTypes.cpp\
./rtts/StandardTypes.h\
./rtts/Types.h\
./rtts/Value.h\
./rtts/ValueModification.cpp\
./rtts/ValueModification.h


