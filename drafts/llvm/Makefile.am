LOCALLIBS=`llvm-config --libdir`


AM_CPPFLAGS = -g -O0 -I`llvm-config --includedir` -I@abs_srcdir@/../../src `llvm-config --cppflags`
#AM_LDFLAGS = -g -O0 -L../../src -lfission $(CLANGLIBS) `llvm-config --libfiles` -lpthread -ldl
AM_LDFLAGS = -g -O0 -L../../src -lfission -lpthread -ldl
#AM_LDFLAGS = -g -O0 -L../../src -lfission `llvm-config --libfiles` -lclang -lpthread -ldl

bin_PROGRAMS=llvm_draft
llvm_draft_SOURCES = Main.cpp

