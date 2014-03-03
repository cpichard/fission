include_directories( . )

find_package(LLVM)
if( NOT LLVM_FOUND )
  message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
endif()

execute_process(COMMAND llvm-config --libdir
    OUTPUT_VARIABLE LLVM_LIB_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

set( CLANG_RESSOURCEDIR ${LLVM_LIB_DIR}/clang/3.4 )
add_definitions( -DCLANG_RESSOURCEDIR="${CLANG_RESSOURCEDIR}" -DSRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}" )

# fission library source files
add_library(fission SHARED
engine/ComputeEngine.cpp
engine/ComputeEngine.h
engine/Context.h
engine/ImageBuffer.h
engine/JITEngine.cpp
engine/JITEngine.h
engine/NodeCompiler.cpp
engine/NodeCompiler.h
engine/Status.h
graph/Edge.h
graph/Graph.h
graph/GraphAlgorithms.h
graph/Module.cpp
graph/Module.h
graph/Name.h
graph/Node.cpp
graph/Node.h
graph/NodeDesc.h
graph/ObjectId.cpp
graph/ObjectId.h
graph/Parameter.cpp
graph/Parameter.h
graph/Plug.cpp
graph/Plug.h
graph/PlugLink.cpp
graph/PlugLink.h
graph/Vertex.h
rtts/StandardTypes.cpp
rtts/StandardTypes.h
rtts/Type.h
rtts/Value.h
rtts/ValueModification.cpp
rtts/ValueModification.h
)
include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )
#add_definitions( -DCLANG_RESSOURCEDIR="" -DSRC_DIR="" )
set( REQ_CLANG_LIBRARIES clangFrontendTool
clangARCMigrate
clangAST
clangASTMatchers
clangAnalysis
clangBasic
clangCodeGen
clangDriver
clangDynamicASTMatchers
clangEdit
clangFormat
clangFrontend
clangFrontendTool
clangIndex
clangLex
clangParse
clangRewriteCore
clangRewriteFrontend
clangSema
clangSerialization
clangStaticAnalyzerCheckers
clangStaticAnalyzerCore
clangStaticAnalyzerFrontend
clangTooling)

set( REQ_LLVM_LIBRARIES 
LLVMInstrumentation
LLVMIRReader
LLVMAsmParser
LLVMDebugInfo
LLVMOption
LLVMLTO
LLVMLinker
LLVMipo
LLVMVectorize
LLVMBitWriter
LLVMBitReader
LLVMTableGen
LLVMXCoreDisassembler
LLVMXCoreCodeGen
LLVMXCoreDesc
LLVMXCoreInfo
LLVMXCoreAsmPrinter
LLVMX86Disassembler
LLVMX86AsmParser
LLVMX86CodeGen
LLVMX86Desc
LLVMX86Info
LLVMX86AsmPrinter
LLVMX86Utils
LLVMSystemZDisassembler
LLVMSystemZCodeGen
LLVMSystemZAsmParser
LLVMSystemZDesc
LLVMSystemZInfo
LLVMSystemZAsmPrinter
LLVMSparcCodeGen
LLVMSparcDesc
LLVMSparcInfo
LLVMR600CodeGen
LLVMR600Desc
LLVMR600Info
LLVMR600AsmPrinter
LLVMPowerPCCodeGen
LLVMPowerPCAsmParser
LLVMPowerPCDesc
LLVMPowerPCInfo
LLVMPowerPCAsmPrinter
LLVMNVPTXCodeGen
LLVMNVPTXDesc
LLVMNVPTXInfo
LLVMNVPTXAsmPrinter
LLVMMSP430CodeGen
LLVMMSP430Desc
LLVMMSP430Info
LLVMMSP430AsmPrinter
LLVMMipsDisassembler
LLVMMipsCodeGen
LLVMMipsAsmParser
LLVMMipsDesc
LLVMMipsInfo
LLVMMipsAsmPrinter
LLVMHexagonCodeGen
LLVMHexagonAsmPrinter
LLVMHexagonDesc
LLVMHexagonInfo
LLVMCppBackendCodeGen
LLVMCppBackendInfo
LLVMARMDisassembler
LLVMARMCodeGen
LLVMARMAsmParser
LLVMARMDesc
LLVMARMInfo
LLVMARMAsmPrinter
LLVMAArch64Disassembler
LLVMAArch64CodeGen
LLVMSelectionDAG
LLVMAsmPrinter
LLVMAArch64AsmParser
LLVMAArch64Desc
LLVMAArch64Info
LLVMAArch64AsmPrinter
LLVMAArch64Utils
LLVMMCDisassembler
LLVMMCParser
LLVMInterpreter
LLVMMCJIT
LLVMJIT
LLVMCodeGen
LLVMObjCARCOpts
LLVMScalarOpts
LLVMInstCombine
LLVMTransformUtils
LLVMipa
LLVMAnalysis
LLVMRuntimeDyld
LLVMExecutionEngine
LLVMTarget
LLVMMC
LLVMObject
LLVMCore
LLVMSupport )

target_link_libraries(fission ${REQ_CLANG_LIBRARIES} ${REQ_LLVM_LIBRARIES} )
# install the library in ${CMAKE_PREFIX}/lib
install (TARGETS fission DESTINATION lib)
