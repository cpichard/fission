; ModuleID = 'TestSink_s.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.fission::Context" = type { i32, i32 }

define void @_Z16TestSink_executeN7fission7ContextEd(%"class.fission::Context"* %ctx, double %a) nounwind {
entry:
  %a.addr = alloca double, align 8
  store double %a, double* %a.addr, align 8
  ret void
}
