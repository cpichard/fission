

AM_CPPFLAGS = -g -O0 -I`llvm-config --includedir` -I../../src/ `llvm-config --cppflags`
AM_LDFLAGS = -g -O0 -L../../src -lfission -lpthread -ldl

bin_PROGRAMS=llvm_draft
llvm_draft_SOURCES = Main.cpp

