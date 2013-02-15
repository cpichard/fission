import unittest

from fission import fission as f

# TESTS not updated

class GraphTests(unittest.TestCase):

    def test_NodeCreation(self):
        self.reader=f.ImageReader("test1")
        self.assertFalse( self.reader==None, "unable to create read node")
        print self.reader
        self.writer=f.ImageWriter("test2")
        self.assertFalse( self.writer==None, "unable to create read node")
        print self.writer

    def test_Connection(self):

        self.reader=f.ImageReader("test1")
        self.assertFalse( self.reader==None, "unable to create read node")
        print self.reader
        self.writer=f.ImageWriter("test2")
        # Connect reader and writer
        print f.connect(self.reader, self.writer)

    def test_NodeName(self):
        self.reader=f.ImageReader("test1")
        self.assertFalse( self.reader==None, "unable to create read node")
        print self.reader
        self.writer=f.ImageWriter("test2")
        print f.connect(self.reader, self.writer)
        # Test names
        print f.nodename(self.reader)  # ensure you have a node
        print self.reader.name()     # returns the name

        # TODO 
        #reader["filesequence"] = "/tmp/toto.###.dpx"
        #writer["filesequence"] = "/tmp/tata.###.dpx"

        # Create a new rendering engine
        engine=f.Engine()

        # Create a render context
        rendercontext=f.Context(0, 10)

        # Launch the computation async
        engine.compute_async(self.writer, rendercontext)

# Monitor progress
#while renderStatus.progress()
#while rendercontext.progress() < 100.0:
#    sleep 2
#    print renderContext.progress()

if __name__ == '__main__':
    unittest.main()

