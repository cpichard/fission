
import sys
from ctypes import CDLL, RTLD_GLOBAL 
from PySide.QtCore import *
from PySide.QtGui import *

from MainWindow import MainWindowWidget

def main():
    #lib = cdll.LoadLibrary("libfission.so", mode=RTLD_GLOBAL)
    lib = CDLL("libfission.so", mode=RTLD_GLOBAL)
    lib.fission_init()
    app = QApplication(sys.argv)
    mainWindow = MainWindowWidget(lib)
    mainWindow.show()
    app.exec_()
    lib.fission_exit()
    sys.exit()

if __name__ == "__main__":
    main()
