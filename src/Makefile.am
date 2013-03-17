
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

#AM_CPPFLAGS = -g @BOOST_CFLAGS@ 
AM_CPPFLAGS = -g -O0 -Wall -Iengine/ -Igraph/ -Inodes/ -Irtts/  `llvm-config --cppflags`

lib_LTLIBRARIES=libfission.la
#libfission_la_LIBADD = @BOOST_LIBS@ 
libfission_la_LDFLAGS = -g -O0 -Wall -Wl,-rpath,./ -L$(LOCALLIBS)/ $(CLANGLIBS) `llvm-config --ldflags --libs `
libfission_la_SOURCES = \
./engine/Context.h\
./engine/ComputeEngine.cpp\
./engine/ComputeEngine.h\
./engine/NodeCompiler.h\
./engine/NodeCompiler.cpp\
./graph/Name.h\
./engine/Status.h\
./rtts/Types.h\
./graph/Edge.h\
./graph/Graph.h\
./graph/ObjectId.h\
./graph/Node.h\
./graph/Node.cpp\
./graph/NodeDesc.h\
./graph/Module.h\
./graph/Module.cpp\
./graph/Parameter.h\
./graph/Parameter.cpp\
./graph/ParameterDesc.h\
./graph/ParameterDesc.cpp\
./graph/Plug.h\
./graph/Plug.cpp\
./graph/PlugLink.h\
./graph/Vertex.h\
./nodes/TestSource.cpp\
./nodes/TestSource.h\
./nodes/TestOp.cpp\
./nodes/TestOp.h\
./nodes/TestSink.cpp\
./nodes/TestSink.h\
./rtts/Value.h\
./rtts/StandardTypes.h\
./rtts/StandardTypes.cpp
