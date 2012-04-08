import fission as f

# 

graph = f.NodeGraph("compo1")
#reader=graph.createNode("ImageReader", "test1")
#reader=graph.nodes.ImageReader("test1")
#print reader

writer=graph.ImageWriter("test2")
print writer

# Connect reader and writer
#print graph.connect(reader.out(0), writer.in(0))

# Test names
print f.nodename(reader)  # ensure you have a node
print reader.name()     # returns the name

# TODO 
#reader["filesequence"] = "/tmp/toto.###.dpx"
#writer["filesequence"] = "/tmp/tata.###.dpx"

# Create a new rendering engine
engine=f.Engine()

# Create a render context
rendercontext=f.Context(0, 10)

# Launch the computation async
engine.compute_async(writer, rendercontext)

# Monitor progress
#while renderStatus.progress()
#while rendercontext.progress() < 100.0:
#    sleep 2
#    print renderContext.progress()



