"""
Computation graph for the player.
Just a connected reader and display node from fission
"""

from fission import fission as f

class PlayerGraph(object):

    def __init__(self):
        """ Creates a computation graph for the player. """

        # Only one track for now.
        # Multiple tracks can be implemented as multiple readers and a switch
        self.reader = f.ImageReader("track1")
        # TODO :
        #self.cache = f.ResultCache("cache")
        # The Display
        self.display = f.GLDisplay("maindisplay")
        f.connect(self.reader, self.display)
        #f.connect(self.reader, self.cache)
        #f.connect(self.cache, self.display)
        
        # Current engine
        self.engine = f.Engine()
       
    def preRoll(self):
        context = Context(0, 10) # TODO 
        self.engine.compute(self.display, context)

    def draw(self, imageNumber):
        context = Context(imageNumber)
        self.engine.compute(self.display, context)
        self.display.drawLastResult()

