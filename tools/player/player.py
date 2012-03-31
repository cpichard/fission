
import sys, os
from PySide import QtCore, QtGui

from Viewer import Viewer
from Timeline import Timeline
from PlayerGraph import PlayerGraph
# Process
# ----------------------------------
if __name__ == "__main__":

    # Main Qt application
    app = QtGui.QApplication(sys.argv)
 
    # Main GUI 
    mainWindow = QtGui.QMainWindow()
    
    # The computation graph for the player
    graph = PlayerGraph()
    
    # Central widget is a simple viewer
    centralWidget = Viewer(mainWindow, graph)

    #QtCore.QObject.connect(animationTimer, QtCore.SIGNAL("timeout()"), centralWidget.currentFrame)
    
    # Build a Timeline object that stores the sequences of image
    timeline = Timeline(graph)

    # TODO : Connect timeline slots with widgets 
    #QtCore.QObject.connect(timeline, QtCore.SIGNAL("timeout()"), centralWidget.currentFrame)

    mainWindow.setCentralWidget(centralWidget)
    mainWindow.show()
    mainWindow.connect(centralWidget, QtCore.SIGNAL('closeApplication()'), QtCore.SLOT('close()'))
    sys.exit(app.exec_())
