#AM_CPPFLAGS = -g @BOOST_CFLAGS@ 
AM_CPPFLAGS = -g 

lib_LTLIBRARIES=libfission.la
#libfission_la_LIBADD = @BOOST_LIBS@ 
libfission_la_LDFLAGS = -Wl,-rpath,./ 
libfission_la_SOURCES = \
Context.h \
Engine.cpp \
Engine.h \
GLDisplay.h \
GLDisplay.cpp \
ImageBuffer.h \
ImageReader.cpp \
ImageReader.h \
ImageWriter.cpp \
ImageWriter.h \
Name.h \
Node.cpp \
Node.h \
NodeGraph.cpp \
NodeGraph.h \
Parameter.cpp \
Parameter.h \
Process.h \
Status.h\
TestValue.h\
TestValue.cpp
