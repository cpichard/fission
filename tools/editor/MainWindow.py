from PySide import QtGui

from GraphEditor import GraphEditorWidget
from MainWindowUI import Ui_MainWindow

class MainWindowWidget(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("Fission editor")

        self.graph_editor = GraphEditorWidget(self)
        self.setCentralWidget(self.graph_editor)

