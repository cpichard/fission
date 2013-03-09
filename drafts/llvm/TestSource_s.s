; ModuleID = 'TestSource_s.cpp'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%"class.fission::Context" = type { i32, i32 }

define double @_Z18TestSource_executeN7fission7ContextE(%"class.fission::Context"* nocapture %ctx) nounwind readonly {
entry:
  %m_first = getelementptr inbounds %"class.fission::Context"* %ctx, i32 0, i32 0
  %0 = load i32* %m_first, align 4, !tbaa !0
  %cmp3 = icmp eq i32 %0, 0
  br i1 %cmp3, label %for.end, label %for.body

for.body:                                         ; preds = %entry, %for.body
  %i.05 = phi i32 [ %inc, %for.body ], [ 0, %entry ]
  %tmp.04 = phi double [ %add, %for.body ], [ 0.000000e+00, %entry ]
  %add = fadd double %tmp.04, 1.000000e+00
  %inc = add nsw i32 %i.05, 1
  %cmp = icmp ult i32 %inc, %0
  br i1 %cmp, label %for.body, label %for.end

for.end:                                          ; preds = %for.body, %entry
  %tmp.0.lcssa = phi double [ 0.000000e+00, %entry ], [ %add, %for.body ]
  ret double %tmp.0.lcssa
}

!0 = metadata !{metadata !"int", metadata !1}
!1 = metadata !{metadata !"omnipotent char", metadata !2}
!2 = metadata !{metadata !"Simple C/C++ TBAA"}
