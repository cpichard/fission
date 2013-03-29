
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
CLANG_RESSOURCEDIR=`llvm-config --libdir`/clang/3.2/
SRC_DIR=@abs_srcdir@

AM_CPPFLAGS = -g -O0 -Wall -DSRC_DIR=\"$(SRC_DIR)\" -DCLANG_RESSOURCEDIR=\"$(CLANG_RESSOURCEDIR)\" -Iengine/ -Igraph/ -Inodes/ -Irtts/  `llvm-config --cppflags`
AM_LDFLAGS = -g -O0 -Wall -L$(LOCALLIBS)/ $(CLANGLIBS) `llvm-config --ldflags --libs ` -Wl,--export-all-symbols

lib_LIBRARIES=libfission.a
libfission_a_SOURCES = \
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
./graph/Parameter.cpp\
./graph/ParameterDesc.cpp\
./graph/ParameterDesc.h\
./graph/Parameter.h\
./graph/Plug.cpp\
./graph/Plug.h\
./graph/PlugLink.h\
./graph/Vertex.h\
./rtts/StandardTypes.cpp\
./rtts/StandardTypes.h\
./rtts/Types.h\
./rtts/Value.h


