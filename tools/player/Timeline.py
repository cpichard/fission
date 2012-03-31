
from PySide import QtCore, QtGui


class Timeline(QtCore.QObject):

    def __init__(self, playerGraph):
        self.playerGraph = playerGraph
        # The timeline stores the current frame
        self.currentFrame = 0

        # list of filesequence with there cuts 
        self.sequences = [] 

        # Qt timer
        self.animationTimer = QtCore.QTimer()
        self.animationTimer.setSingleShot(False);
        self.animationTimer.setInterval(1.0/48.0*1000)
        QtCore.QObject.connect(self.animationTimer, QtCore.SIGNAL("timeout()"), self.tick)
        self.animationTimer.start()

    def tick(self):
        pass

    def clear(self):
        """
        Clears the timeline and the image cache
        """

    def setCurrentFrame(self, frame):
        self.currentFrame = frame

    def getCurrentFrame(self):
        return frame
    
    def nextFrame(self):
        self.frame = self.frame + 1
        #return or yield ?
        return self.frame    

    def previousFrame(self):
        self.frame = self.frame - 1 

