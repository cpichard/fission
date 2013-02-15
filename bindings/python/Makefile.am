BUILT_SOURCES = fission_wrap.cpp
SWIG_SOURCES = \
$(top_srcdir)/src/engine/Context.i \
$(top_srcdir)/src/engine/ComputeEngine.i \
$(top_srcdir)/src/engine/Status.i \
$(top_srcdir)/src/graph/Name.i \
$(top_srcdir)/src/graph/Node.i \
$(top_srcdir)/src/graph/Module.i \
$(top_srcdir)/src/graph/Parameter.i 


SWIG_PYTHON_OPT = -python -c++


pkgpython_PYTHON = fission.py
pkgpyexec_LTLIBRARIES = _fission.la
_fission_la_SOURCES = fission_wrap.cpp $(SWIG_SOURCES)
_fission_la_CPPFLAGS = $(SWIG_PYTHON_CPPFLAGS) -I$(top_srcdir)/src/engine -I$(top_srcdir)/src/graph -I$(top_srcdir)/src/nodes -I$(top_srcdir)/src/rtts
_fission_la_LDFLAGS = -module
_fission_la_LIBADD = $(top_srcdir)/src/libfission.la

$(srcdir)/fission_wrap.cpp : $(SWIG_SOURCES)
	$(SWIG) $(SWIG_PYTHON_OPT) -I$(top_srcdir)/src/engine -I$(top_srcdir)/src/graph -I$(top_srcdir)/src/nodes -o $@ fission.i 



