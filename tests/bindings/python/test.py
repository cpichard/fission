from fission import fission as f

# 
reader=f.ImageReader("test1")
print reader
writer=f.ImageWriter("test2")
print writer

# Connect reader and writer
print f.connect(reader, writer)

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



