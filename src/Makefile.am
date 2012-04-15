#AM_CPPFLAGS = -g @BOOST_CFLAGS@ 
AM_CPPFLAGS = -g -Iengine/ -Igraph/ -Inodes/ 

lib_LTLIBRARIES=libfission.la
#libfission_la_LIBADD = @BOOST_LIBS@ 
libfission_la_LDFLAGS = -Wl,-rpath,./ 
libfission_la_SOURCES = \
./engine/Context.h\
./engine/Engine.cpp\
./engine/Engine.h\
./engine/Link.h\
./engine/List.h\
./engine/Name.h\
./engine/Process.h\
./engine/Status.h\
./engine/Types.h\
./graph/Edge.h\
./graph/Graph.h\
./graph/Identifier.h\
./graph/Node.h\
./graph/NodeCollection.h\
./graph/Parameter.h\
./graph/Plug.h\
./graph/PlugLink.h\
./graph/Vertex.h\
./nodes/GLDisplay.cpp\
./nodes/GLDisplay.h\
./nodes/TestValue.cpp\
./nodes/TestValue.h
