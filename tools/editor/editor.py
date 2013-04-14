
import sys
from PySide.QtCore import *
from PySide.QtGui import *

from MainWindow import MainWindowWidget

def main():
    from ctypes import CDLL, RTLD_GLOBAL
    lib = CDLL("libfission.so", RTLD_GLOBAL)
    app = QApplication(sys.argv)
    mainWindow = MainWindowWidget()
    mainWindow.show()
    app.exec_()
    sys.exit()

if __name__ == "__main__":
    main()
