from PySide import QtCore, QtGui, QtOpenGL

import GLWidget

class Viewer(GLWidget.GLWidget):
    """ 
    Viewer, all the movement and interaction in the GLWidget 
    are implemented here.
    """

    """ Interations modes """
    Idle, Translate, Scale = range(3)
    
    def __init__(self, parent, playerGraph):
        GLWidget.GLWidget.__init__(self, parent)
        self.mode = self.Idle
        self.playerGraph = playerGraph

    def mouseMoveEvent ( self, QMouseEvent):
        divisor = self.width()/2.0
        if self.mode == self.Translate:
            self.tx = self.curTX + (QMouseEvent.x()-self.mousX)/divisor
            self.ty = self.curTY - (QMouseEvent.y()-self.mousY)/divisor
        if self.mode == self.Scale:
            multiplier = (1.0+(QMouseEvent.x()-self.mousX)/divisor)
            if multiplier > 0 :
                self.scale = self.curScale*multiplier
            
    def mousePressEvent ( self, QMouseEvent):
        if QMouseEvent.button() == QtCore.Qt.LeftButton:
            self.mode = self.Translate
        
        if QMouseEvent.button() == QtCore.Qt.RightButton:
            self.mode = self.Scale
        
        # store current position and scale
        self.curTX = self.tx
        self.curTY = self.ty
        self.curScale = self.scale
        self.mousX = QMouseEvent.x()
        self.mousY = QMouseEvent.y()

        print "mouse press"
    
    def mouseReleaseEvent ( self, QMouseEvent):
        print "mouse release"
        self.Mode = self.Idle     
