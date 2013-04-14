from PySide import QtOpenGL, QtGui, QtCore
from OpenGL.GL import *

class WorkspaceGLWidget(QtOpenGL.QGLWidget):
    """ Implements a simple 2d workspace that can be
        translated, scaled 
    """
    # Moving mode
    Idle, Translate, Scale = range(3)

    def __init__(self, parent):
        # Select GL format
        gl_format = QtOpenGL.QGLFormat()
        gl_format.setRgba(True)
        gl_format.setDoubleBuffer(True)
        gl_format.setSwapInterval(1) # enables vsync
        QtOpenGL.QGLWidget.__init__(self, gl_format, parent)

        # Allows to overpaint on gl content
        self.setAutoFillBackground(False);
        self.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.setMouseTracking(True)

        # Movement variables
        self.ratio = 1.0
        self.moving_mode = self.Idle
        self.tx = 0.0
        self.ty = 0.0
        self.scale = 0.95

        self.current_tx = self.tx
        self.current_ty = self.ty
        self.current_scale = self.scale
        self.mouse_x = 0
        self.mouse_y = 0

    def initializeGL(self):
        glEnable(GL_DEPTH_TEST)

    def resizeGL(self, width, height):
        self.setupViewport(width, height)

    def setupViewport(self, width, height):
        """  """
        if width == 0 or height == 0:
            return

        w = float(width)
        h = float(height)
        r = 0.5*h/w
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-0.5, 0.5, -r, r, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glScale(self.scale, self.scale, 1.0)
        glTranslate(self.tx, self.ty, 0.0)

        self.ratio=2.0*r

    def mousePressEvent(self, event):
        """ Select the moving mode on press event """
        if(_translateKeys(event)):
            self.moving_mode = self.Translate
            event.accept()
        elif (_scaleKeys(event)):
            self.moving_mode = self.Scale
            event.accept()
        else:
            event.ignore()

        # store current position and scale
        self.current_tx = self.tx
        self.current_ty = self.ty
        self.current_scale = self.scale
        self.mouse_x = event.x()
        self.mouse_y = event.y()

    def mouseMoveEvent(self, event):
        # Change values of translate and scale
        divisor = float(self.width())
        if divisor != 0:
            if self.moving_mode == self.Translate:
                self.tx = self.current_tx + (event.x()-self.mouse_x)/(divisor*self.scale)
                self.ty = self.current_ty - (event.y()-self.mouse_y)/(divisor*self.scale)
                self.update()
                event.accept()
            elif self.moving_mode == self.Scale:
                multiplier = (1.0+(event.x()-self.mouse_x)/divisor)
                if multiplier > 0 :
                    self.scale = self.current_scale*multiplier
                self.update()
                event.accept()
            else:
                event.ignore()
        else:
            event.ignore()

    def mouseReleaseEvent(self, event):
        if self.moving_mode in (self.Translate, self.Scale):
            self.moving_mode = self.Idle
            event.accept()
        else:
            event.ignore()

    def paintEvent(self, event):
        """
        Function redefined to paint OpenGL code
        and QPainter code
        """
        glClearColor(0.2, 0.2, 0.2, 1.0)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        #self.setupViewport(self.width(), self.height())

        # Push matrices before QPainter
        glMatrixMode(GL_PROJECTION);
        glPushMatrix()
        glMatrixMode(GL_MODELVIEW)
        glPushMatrix()

        # Do the scene repositionning
        glLoadIdentity()
        glScale(self.scale, self.scale, 1.0)
        glTranslate(self.tx, self.ty, 0.0)

        # Call GL function
        self.drawWorkspace()

        glMatrixMode(GL_PROJECTION)
        glPopMatrix()
        glMatrixMode(GL_MODELVIEW)
        glPopMatrix()

        painter = QtGui.QPainter()
        #painter.setRenderHint(QtGui.QPainter.Antialiasing);
        painter.begin(self)
        #painter.setRenderHint(QtGui.QPainter.TextAntialiasing)
        # call QT paint function
        self.myPaintQT(painter)
        painter.end()

    def myPaintQT(self, painter):
        painter.drawRect(10, 10, 100, 100)
        painter.drawText(30, 30, "tx=%s " % self.tx) 

#    def paintGL(self):
#        # Push matrices before QPainter
#        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
#        glMatrixMode(GL_PROJECTION);
#        glPushMatrix()
#        glMatrixMode(GL_MODELVIEW)
#        glPushMatrix()
#
#        # Do the scene repositionning
#        glLoadIdentity()
#        glScale(self.scale, self.scale, 1.0)
#        glTranslate(self.tx, self.ty, 0.0)
#        glBegin(GL_TRIANGLES)
#        glVertex3f( 0.0,  1.0, 0.0)
#        glVertex3f(-1.0, -1.0, 0.0)
#        glVertex3f( 1.0, -1.0, 0.0)
#        glEnd()
#        
#        glMatrixMode(GL_PROJECTION)
#        glPopMatrix()
#        glMatrixMode(GL_MODELVIEW)
#        glPopMatrix()
    

def _translateKeys(event):
    return (event.button() in (QtCore.Qt.LeftButton, QtCore.Qt.RightButton)
    and event.modifiers() == QtCore.Qt.ControlModifier )

def _scaleKeys(event):
    return (event.button() == QtCore.Qt.MidButton
    and event.modifiers() == QtCore.Qt.ControlModifier)




