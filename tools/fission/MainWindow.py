from PySide import QtGui

from GraphEditor import GraphEditorWidget
from MainWindowUI import Ui_MainWindow

class MainWindowWidget(QtGui.QMainWindow):
    def __init__(self, lib_fission):
        QtGui.QMainWindow.__init__(self)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle("Fission editor")

        self.lib_fission = lib_fission
        self.graph_editor = GraphEditorWidget(self, lib_fission)
        self.setCentralWidget(self.graph_editor)

