; ModuleID = 'myfunctions.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

define void @_Z5func1Pdd(double* %a, double %b) nounwind {
entry:
  %a.addr = alloca double*, align 4
  %b.addr = alloca double, align 8
  %i = alloca i32, align 4
  store double* %a, double** %a.addr, align 4
  store double %b, double* %b.addr, align 8
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32* %i, align 4
  %cmp = icmp slt i32 %0, 64
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load double* %b.addr, align 8
  %2 = load i32* %i, align 4
  %3 = load double** %a.addr, align 4
  %arrayidx = getelementptr inbounds double* %3, i32 %2
  store double %1, double* %arrayidx, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32* %i, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

define void @_Z5func2Pdd(double* %a, double %b) nounwind {
entry:
  %a.addr = alloca double*, align 4
  %b.addr = alloca double, align 8
  %i = alloca i32, align 4
  store double* %a, double** %a.addr, align 4
  store double %b, double* %b.addr, align 8
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32* %i, align 4
  %cmp = icmp slt i32 %0, 64
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load double* %b.addr, align 8
  %2 = load i32* %i, align 4
  %3 = load double** %a.addr, align 4
  %arrayidx = getelementptr inbounds double* %3, i32 %2
  %4 = load double* %arrayidx, align 4
  %add = fadd double %4, %1
  store double %add, double* %arrayidx, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i32* %i, align 4
  %inc = add nsw i32 %5, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

define double @_Z7executev() nounwind {
entry:
  %a = alloca [64 x double], align 4
  %arraydecay = getelementptr inbounds [64 x double]* %a, i32 0, i32 0
  call void @_Z5func1Pdd(double* %arraydecay, double 1.000000e+01)
  %arraydecay1 = getelementptr inbounds [64 x double]* %a, i32 0, i32 0
  call void @_Z5func2Pdd(double* %arraydecay1, double 2.000000e+01)
  %arrayidx = getelementptr inbounds [64 x double]* %a, i32 0, i32 50
  %0 = load double* %arrayidx, align 4
  ret double %0
}
