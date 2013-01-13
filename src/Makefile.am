#AM_CPPFLAGS = -g @BOOST_CFLAGS@ 
AM_CPPFLAGS = -std=c++11 -g -Iengine/ -Igraph/ -Inodes/ -Irtts/ `llvm-config --cppflags`

lib_LTLIBRARIES=libfission.la
#libfission_la_LIBADD = @BOOST_LIBS@ 
libfission_la_LDFLAGS = -Wl,-rpath,./ `llvm-config --ldflags --libs core jit native`
libfission_la_SOURCES = \
./engine/Context.h\
./engine/ExecutionEngine.cpp\
./engine/ExecutionEngine.h\
./graph/Name.h\
./engine/Process.h\
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
