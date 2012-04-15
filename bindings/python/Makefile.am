BUILT_SOURCES = fission_wrap.cpp
SWIG_SOURCES = \
$(top_srcdir)/src/engine/Context.i \
$(top_srcdir)/src/engine/Engine.i \
$(top_srcdir)/src/engine/GLDisplay.i \
$(top_srcdir)/src/engine/ImageReader.i \
$(top_srcdir)/src/engine/ImageWriter.i \
$(top_srcdir)/src/engine/Name.i \
$(top_srcdir)/src/engine/Node.i \
$(top_srcdir)/src/engine/NodeGraph.i \
$(top_srcdir)/src/engine/Parameter.i \
$(top_srcdir)/src/engine/Status.i

SWIG_PYTHON_OPT = -python -c++


pkgpython_PYTHON = fission.py
pkgpyexec_LTLIBRARIES = _fission.la
_fission_la_SOURCES = fission_wrap.cpp $(SWIG_SOURCES)
_fission_la_CPPFLAGS = $(SWIG_PYTHON_CPPFLAGS) -I$(top_srcdir)/src/engine -I$(top_srcdir)/src/graph
_fission_la_LDFLAGS = -module
_fission_la_LIBADD = $(top_srcdir)/src/libfission.la

$(srcdir)/fission_wrap.cpp : $(SWIG_SOURCES)
	$(SWIG) $(SWIG_PYTHON_OPT) -I$(top_srcdir)/src/engine -I$(top_srcdir)/src/graph -o $@ fission.i 



