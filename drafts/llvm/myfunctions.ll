; ModuleID = 'myfunctions.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

define double @_Z7executeRdS_(double* %a, double* %b) nounwind {
entry:
  %a.addr = alloca double*, align 4
  %b.addr = alloca double*, align 4
  store double* %a, double** %a.addr, align 4
  store double* %b, double** %b.addr, align 4
  %0 = load double** %a.addr, align 4
  %1 = load double* %0, align 4
  %2 = load double** %b.addr, align 4
  %3 = load double* %2, align 4
  %add = fadd double %1, %3
  ret double %add
}
