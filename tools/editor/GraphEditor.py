
from PySide import QtGui, QtOpenGL
from OpenGL.GL import *
from fission import fission as f
from WorkspaceGL import WorkspaceGLWidget

class GraphEditorWidget(WorkspaceGLWidget):
    """
    Fission graph editor
    """
    def __init__(self, parent):
        WorkspaceGLWidget.__init__(self, parent)

        # new module for this editor
        # first compile a few nodes for it
        self.jit = f.JITEngine()
        testOp = self.jit.loadNodeDescription("nodes/TestOp.cpp")
        testSource = self.jit.loadNodeDescription("nodes/TestSource.cpp")
        testSink = self.jit.loadNodeDescription("nodes/TestSink.cpp")
        self.module = f.Module("Module Test")
        self.module.registerNodeDesc(testOp)
        self.module.registerNodeDesc(testSource)
        self.module.registerNodeDesc(testSink)
        # create a simple node
        node1 = self.module.createNode("TestSource", "Src1")
        node2 = self.module.createNode("TestSource", "Src2")
        node3 = self.module.createNode("TestSource", "Src3")

    def drawNode(self, node):
        """ Draw a node without its connections. """
        # TODO : get node position
        glTranslate(0.2, 0.1, 0.0)
        glBegin(GL_QUADS)
        glVertex3f( 0.0, 0.2, 0.0)
        glVertex3f( 0.2, 0.2, 0.0)
        glVertex3f( 0.2, 0.0, 0.0)
        glVertex3f( 0.0, 0.0, 0.0)
        glEnd()


    def drawWorkspace(self):
        """ This is the main drawing function called by WorkspaceGL. """
        #print self.module.getNodes()
        glMatrixMode(GL_MODELVIEW)
        glPushMatrix()
        for i, node in enumerate(self.module.getNodes()):
            self.drawNode(node)

        glMatrixMode(GL_MODELVIEW)
        glPopMatrix()
