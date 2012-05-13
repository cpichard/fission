# subdirectories of fission library
include_directories( engine graph nodes )

# fission library source files
add_library(fission SHARED
engine/Context.h
engine/Engine.cpp
engine/Engine.h
engine/ImageBuffer.h
engine/Process.h
engine/deprecated
graph/Edge.h
graph/Graph.h
graph/GraphAlgorithms.h
graph/Module.cpp
graph/Module.h
graph/Name.h
graph/Node.cpp
graph/Node.h
graph/NodeDesc.h
graph/ObjectId.h
graph/Parameter.cpp
graph/Parameter.h
graph/ParameterDesc.cpp
graph/ParameterDesc.h
graph/Plug.h
graph/PlugLink.h
graph/Types.h
graph/Vertex.h
nodes/TestOp.cpp
nodes/TestOp.h
nodes/TestSink.cpp
nodes/TestSink.h
nodes/TestSource.cpp
nodes/TestSource.h
nodes/TestValue.cpp
nodes/TestValue.h
)

# install the library in ${CMAKE_PREFIX}/lib
install (TARGETS fission DESTINATION lib)
