; ModuleID = 'TestOp_s.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define double @_Z14TestOP_executedd(double %a, double %b) nounwind uwtable {
entry:
  %a.addr = alloca double, align 8
  %b.addr = alloca double, align 8
  store double %a, double* %a.addr, align 8
  store double %b, double* %b.addr, align 8
  %0 = load double* %a.addr, align 8
  %mul = fmul double 2.000000e+00, %0
  %1 = load double* %b.addr, align 8
  %mul1 = fmul double 3.000000e+00, %1
  %add = fadd double %mul, %mul1
  ret double %add
}
