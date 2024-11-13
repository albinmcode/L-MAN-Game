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
getElement PROC
     mov ECX, [ESP+4] ; x coordinate of the element to obtain (Column)
    mov EDX, [ESP+8] ; y coordinate of the element to obtain (Row)
    
    ; Obtain the index in the map according to the coordinates (actualRow*totalColumns + actualColumn)
    mov AL, 22 ; totalColumns
    imul DL ; row * 22 = AX
    add CX, AX ; column + (row*22)
    mov EDI, ECX ; element index on the map
    cmp EDI, 241
    ; check for invalid index
    jg retInvalid
    cmp EDI, 0
    jl retInvalid 2
    ; load into EAX, the specified value
    mov EAX, 0
    mov AL, elementsMap[EDI]
    jmp retElement
    
    retInvalid: mov EAX, -1 ; -1 index out of bounds
    retElement:    
        ret
getElement ENDP

; Save the given value into the elements map
saveElement PROC
    mov BL, [ESP+4] ; byte value to be saved in the matrix
    mov ECX, [ESP+5] ; x coordinate of the element to modify (Column)
    mov EDX, [ESP+9] ; y coordinate of the element to modify (Row)
    
    ; Obtain the index in the map according to the coordinates (actualRow*totalColumns + actualColumn)
    mov AL, 22 ; totalColumns
    imul DL ; row * 22 = AX
    add CX, AX ; column + (row*22)
    mov EDI, ECX ; element index on the map
    ; check for invalid index
    cmp EDI, 241
    jg retInvalidSave
    cmp EDI, 0
    jl retInvalidSave 2
    ; save BL value into the map
    mov elementsMap[EDI], BL
    mov EAX, 0 ; exit success
    jmp retElement
    
    retInvalidSave: mov EAX, -1 ; -1 index out of bounds
    
    retElement:    
        ret
saveElement ENDP