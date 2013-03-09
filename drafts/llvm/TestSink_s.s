; ModuleID = 'TestSink_s.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.fission::Context" = type { i32, i32 }

@.str = private unnamed_addr constant [19 x i8] c"sink received: %g\0A\00", align 1

define double @_Z16TestSink_executeN7fission7ContextEd(%"class.fission::Context"* nocapture %ctx, double %a) nounwind {
entry:
  %call = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([19 x i8]* @.str, i32 0, i32 0), double %a)
  ret double %a
}

declare i32 @printf(i8* nocapture, ...) nounwind
