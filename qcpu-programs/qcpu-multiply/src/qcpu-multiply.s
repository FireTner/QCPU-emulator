; Layout:
; for y:
;   result += x
;
; R1 = X
; R2 = Y

.Start:
    LIM $1, ;X
    LIM $2, ;Y
    LIM $3, 0x01
.Loop:
    CND 2
; Result += X
    AST $4
    ADD $1
    RST $4
; Y--
    AST $2
    SUB $3
; If Y == 0 Then HLT
    JMP .End
    CND 0
    JMP Loop
; After Mult
.End
    MSC 1