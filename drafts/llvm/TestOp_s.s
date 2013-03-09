; ModuleID = 'TestOp_s.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.fission::Context" = type { i32, i32 }

define double @_Z14TestOP_executeN7fission7ContextEdd(%"class.fission::Context"* %ctx, double %a, double %b) nounwind {
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
