
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


