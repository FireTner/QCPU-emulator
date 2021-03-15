; FT:
; Rendering
; Collision
; DP:
; Moving
; Drop

; %0 display x
; %1 display y
; %2 display update
; %3 display buffer
; %4 user input rotate left
; %5 user input rotate right
; %6 user input move left
; %7 user input move right

; Page 0: Init
; Page 1: Main Loop
; Page 2: 
; Page 3: 
; Page 4: 
; Page 5: Render
; Page 6: Tetromino list (data)
; Page 7: Playgrid + Current Tetromino (data)

; Page 7: Render stuff
; 16 bytes of playgrid
; 1 byte x
; 1 byte y
; 1 byte address to tetromino

; Page 6: Tetromino types
; Line1, Line2
; L1, L2, L3, L4
; L1, L2, L3, L4
; S
; S1, S2
; P1, P2, P3, P4
; S1, S2

.CollisionCheck ; Checking collision on bottom, sides of screen

; Idea is
; line loop:
; ast 6 ; 6 = pointer to byte (automatically incremented after ast 6)
; fetch line
; if not 16:
;  shl
;  if carry:
;   renderbit
;   goback
;  if zero:
;   jump out of loop
;  jump to next line

.Render ; rendering playgrid and current tetromini
    SLD 7
    LIM $5, 0x10
    LIM $6, 0xFF
.RenderNewLine
    AST $6
    POI $6
    MLD 0 ; POI bitwise ORs next memory address with register
    RST $1
; check for 16
    SUB $5
    CND 0b010
    JMP .RenderEnd
.RenderLine
    CND 2
    JMP .RenderNewLine
    ADD 
    CND 1
    JMP .RenderBit
.RenderBit
    

.RenderEnd

    


; %4 user input rotate left
; %5 user input rotate right
; %6 user input move left
; %7 user input move right
.UserIO
; init
    SLD 7
    CND 0b010
    LIM $1, 1
; code
    PLD %6 
    SUB $0
    JMP .AfterIOMoveLeft
; increment stuff
    MLD 17
    SUB $1
    MST 17
.AfterIOMoveLeft
    CND 0b010
    PLD %7
    ADD $0
    JMP .AfterIOMoveRight
    MLD 17
    ADD $1
    MST 17 ; 17 Bytes so far
.AfterIOMoveRight
.AfterIORotLeft
.AfterIORotRight
; deinit
    SST 7
    SLP 5