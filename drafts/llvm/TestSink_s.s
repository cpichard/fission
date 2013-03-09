; ModuleID = 'TestSink_s.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define void @_Z16TestSink_executed(double %a) nounwind uwtable {
entry:
  %a.addr = alloca double, align 8
  store double %a, double* %a.addr, align 8
  ret void
}
