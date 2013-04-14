
from ctypes import *
from PySide import QtGui, QtOpenGL
from OpenGL.GL import *

from WorkspaceGL import WorkspaceGLWidget

class GraphEditorWidget(WorkspaceGLWidget):
    """
    Fission graph editor
    """
    def __init__(self, parent, lib_fission):
        WorkspaceGLWidget.__init__(self, parent)
        self.libf = lib_fission

        # new module for this editor
        self.module = self.libf.fission_module_new()
        self.libf.fission_module_compile_node(self.module, "nodes/TestOp.cpp")
        self.libf.fission_module_compile_node(self.module, "nodes/TestSource.cpp")
        self.libf.fission_module_compile_node(self.module, "nodes/TestSink.cpp")
        
        node = self.libf.fission_node_new(self.module, "TestOp", "testop1")
        node = self.libf.fission_node_new(self.module, "TestOp", "testop2")

    def drawWorkspace(self):
        #nodes = self.libf.fission_module_nodes()
        #for node in self.nodes:
        #    node.draw()
        #for conn in self.connections:
        #    conn.draw()

        glBegin(GL_QUADS)
        glVertex3f( 0.0, 0.2, 0.0)
        glVertex3f( 0.2, 0.2, 0.0)
        glVertex3f( 0.2, 0.0, 0.0)
        glVertex3f( 0.0, 0.0, 0.0)
        glEnd()
