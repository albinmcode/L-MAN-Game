; Matrix with the representation of the words and dictionaries on the map

.386 ; 32 bits program
.MODEL flat, c ; Flat memory model and C calling convention
.STACK 512

.data
    mapElements db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3
                db 0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0
                db 0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0
                db 0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0
                db 0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0
                db 0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0
                db 0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0
                db 0,1,1,1,3,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0
                db 0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
                db 0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0
                db 3,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0
    ; mapSize EQ $ - map

.code

; Obtain the value of a element on the map according to the specified coordinates
; getElement(row, column)
getElementXY PROC
     mov ECX, [ESP+4] ; x coordinate of the element to obtain (Column)
    mov EDX, [ESP+8] ; y coordinate of the element to obtain (Row)
    
    ; Obtain the index in the map according to the coordinates (actualRow*totalColumns + actualColumn)
    mov AL, 22 ; totalColumns
    imul DL ; row * 22 = AX
    add CX, AX ; column + (row*22)
    mov EDI, ECX ; element index on the map
    cmp EDI, 241
    ; check for invalid index
    jg retInvalidXY
    cmp EDI, 0
    jl retInvalidXY
    ; load into EAX, the specified value
    mov EAX, 0
    mov AL, mapElements[EDI]
    jmp retElement
    
    retInvalidXY: mov EAX, -1 ; -1 index out of bounds
    retElement:    
        ret
getElementXY ENDP

; Obtain the value of a element on the map according to the specified index
; getElement(index)
getElement PROC
     mov EBX, [ESP+4] ; index of the element to obtain
     
    ; check for invalid index
     cmp EBX, 241
    jg retInvalid
    cmp EDI, 0
    jl retInvalid

    ; load into EAX, the specified value
    mov EAX, 0
    mov AL, mapElements[EBX]
    jmp retElement
    
    retInvalid: mov EAX, -1 ; -1 index out of bounds
    retElement:
        ret
getElement ENDP

; Save the given value into the elements map
; saveElement(value, row, column)
saveElementXY PROC
    mov BL, [ESP+4] ; byte value to be saved in the matrix
    mov ECX, [ESP+8] ; x coordinate of the element to modify (Column)
    mov EDX, [ESP+12] ; y coordinate of the element to modify (Row)
    
    ; Obtain the index in the map according to the coordinates (actualRow*totalColumns + actualColumn)
    mov AL, 22 ; totalColumns
    imul DL ; row * 22 = AX
    add CX, AX ; column + (row*22)
    mov EDI, ECX ; element index on the map
    
    ; check for invalid index
    cmp EDI, 241
    jg retInvalidSaveXY
    cmp EDI, 0
    jl retInvalidSaveXY
    
    ; save BL value into the map
    mov mapElements[EDI], 'r';BL
    mov EAX, 0 ; exit success
    jmp retElementSavedXY
    
    retInvalidSaveXY: mov EAX, -1 ; -1 index out of bounds
    
    retElementSavedXY:    
        ret
saveElementXY ENDP

; Save the given value into the elements map
; saveElement(value, index)
saveElement PROC
    mov DL, [ESP+4] ; byte value to be saved in the matrix
    mov EBX, [ESP+8] ; index of the element to modify (Column)
    
    ; check for invalid index
    cmp EBX, 241
    jg retInvalidSave
    cmp EBX, 0
    jl retInvalidSave
    
    ; save BL value into the map
    mov mapElements[EBX], DL
    mov EAX, 0 ; exit success
    jmp retElementSave
    
    retInvalidSave: mov EAX, -1 ; -1 index out of bounds
    
    retElementSave:    
        ret
saveElement ENDP

END