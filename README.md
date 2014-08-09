Fission
=======

Description
===========
fission is a framework used to experiment "just in time" compilation on a graph of processing nodes. The initial goal behind this project was to understand the feasability of a compositing software able to recompile its internal graph, and find the gains in rendering time.

Why ? I worked on a in-house compositing software for several years. Back then we were faced with challenges like:

* Using efficiently machine ressources, cpu cores, gpu, ...
* Optimizing compositing graphs, 
* Changing scheduling and graph computation
* Providing fast development cycles.

Using a just in time compiler can help tackling these challenges. For instance it's not unreasonable to think that we could target cpu or gpu with the same processing code using a just in time compiler. We could also recompile with a different rendering algorithm, scanline or full buffer, depending on the machine capabilities or the complexity of the graph. With the help of a compiler, we could optimize the computation graph at the code level without adding extra cases like node concatenation for color operators. After all, a compositing software can be seen as a high level compiler with specialized optimization. 
How great would it be for a developper prototype its plugins directly inside the sofware without restarting it ?

This project aims to understand the feasability of such features by testing with just in time compilation provided by llvm.

Status
======
Righ now I have implemented only simple nodes, like addition, source and sink. The draft subfolder contains the current examples to test the framework. Everything is still work in progress and updates are sparse given the little amount of time I have to play with this exciting project. If you are interested by this project, you can send me a mail.


Compilation
===========
Fission should compile on snow leopard and linux. It also uses clang, clang++ and llvm version 3.4 framework, so you have to install llvm and its tools. 

You can compile with the standard autotools:

autoreconf -i
./configure
make

You can also compile it with cmake.

mkdir build
cd build
ccmake ..
make

See also
========
Julia
Natron
Root
Halide
