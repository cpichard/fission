import sys
from PySide import QtCore, QtGui, QtOpenGL
from OpenGL.GL import *

class GLWidget(QtOpenGL.QGLWidget):
    """ Widget OpenGL. """
 
    def __init__(self, parent):
        QtOpenGL.QGLWidget.__init__(self, parent)
        self.setMinimumSize(1024,1024)
        self.curFrame = 0
        self.tx = 0.0 
        self.ty = 0.0
        self.scale = 1.0
        self.ratio = 1
 
    def initializeGL(self):
        """ Set up display lists, OpenGL options. """
        glClearColor(0.0,0.0,0.0,0.0)
        glEnable(GL_DEPTH_TEST);        
        glEnable(GL_TEXTURE_2D) 
        # TODO self.ie.initializeGL()

        #self.ie = ImageEngine.ICache()
        #if self.curSequence:
        #    self.ie.prepareCache(1920,1080, GL_UNSIGNED_BYTE, self.curSequence.nbFrames() )
        #
        #    for f in self.curSequence.listFiles():
        #        self.ie.cacheImage(f)
        
    
    def paintGL(self):
        """        
        Clear buffers, apply transformations, paint.
        """
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        
        glScale(self.scale,self.scale, 1.0)
        glScale(1.0, self.ratio, 0.0)
        glTranslate(self.tx, self.ty, 0.0)
        glColor(1.0, 1.0, 1.0)
        glDisable(GL_LIGHTING)
        #self.ie.drawImage(self.curSequence.filename(self.curFrame))    
        self.renderText( 10, self.height()-10, "Frame %s " % str(self.curFrame))
        glDisable(GL_DEPTH_TEST)
        self.renderText( 0.5, 0.5, -0.5, "annotation example")
        #TODO : for all gizmos, overlay.draw()

    def resizeGL(self, width, height ):
        """ Resize viewport, recalculate matrices. """
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glClearColor(0.0,0.0,0.0,0.0)
        self.ratio = float(width)/float(height)


    def currentFrame( self ):
        # TODO : in the timeline
        """ Change the current frame. """
        self.curFrame = self.curFrame + 1
        if self.curSequence:
            if self.curFrame >= self.curSequence.last:
                self.curFrame = self.curSequence.first
    
        self.updateGL()

