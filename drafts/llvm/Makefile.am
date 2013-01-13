AM_CPPFLAGS = -I/home/cyril/usr/local/include -I../../src/engine -I../../src/graph -I../../src/nodes -I../../src/rtts `llvm-config --cppflags`
AM_LDFLAGS = -L../../src -lfission `llvm-config --ldflags --libs core jit native`

bin_PROGRAMS=llvm_draft
llvm_draft_SOURCES = Main.cpp

