#AM_CPPFLAGS = -g @BOOST_CFLAGS@ 
AM_CPPFLAGS = -g -Iengine/ -Igraph/ -Inodes/ 

lib_LTLIBRARIES=libfission.la
#libfission_la_LIBADD = @BOOST_LIBS@ 
libfission_la_LDFLAGS = -Wl,-rpath,./ 
libfission_la_SOURCES = \
./engine/Context.h\
./engine/Engine.cpp\
./engine/Engine.h\
./engine/GLDisplay.cpp\
./engine/GLDisplay.h\
./engine/GraphEdge.h\
./engine/GraphVertex.h\
./engine/Link.h\
./engine/List.h\
./engine/Name.h\
./engine/Node.cpp\
./engine/Node.h\
./engine/NodeGraph.cpp\
./engine/NodeGraph.h\
./engine/Parameter.cpp\
./engine/Parameter.h\
./engine/Plug.h\
./engine/Process.h\
./engine/Status.h\
./engine/TestValue.cpp\
./engine/TestValue.h\
./engine/Types.h\
./graph/Edge.h\
./graph/Graph.h\
./graph/Identifier.h\
./graph/Node.h\
./graph/NodeCollection.h\
./graph/Parameter.h\
./graph/Plug.h\
./graph/PlugLink.h\
./graph/Vertex.h
