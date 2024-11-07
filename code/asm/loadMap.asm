; Loading a matrix ptr with the representation of the game map

.386 ; 32 bits program
.MODEL flat, c ; Flat memory model and C calling convention
.STACK 512

.data
    map db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1
        db 1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1
        db 1,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0,1
        db 1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1
        db 1,0,1,0,1,1,1,1,0,1,1,2,1,1,0,1,1,1,1,1,1,1,0,1
        db 1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1
        db 1,0,1,0,1,1,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0,1,0,1
        db 1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0,1
        db 1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1
        db 1,0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1
        db 1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    ; mapSize EQ $ - map

.code
loadMap PROC
    ; First parameter in ESP+4 (int8_t*)
    mov EBX, [ESP+4] ; ptr to the c++ matrix to load the map representation
    
    ; Load matrix
    mov ECX, 312 ; Second parameter, size of the matrix
    mov ESI, 0 ; Source index
    mov EDI, 0 ; Destination index
    loadByte:
        mov AL, map[ESI] ; obtain from source
        mov [EBX], AL ; load into the matrix
        inc ESI
        inc EBX
        loop loadByte ; loop ECX times
    

    exitSuccess: mov EAX, 0
    ret
loadMap ENDP

; checkColision(int32_t* movementFactor, int32_t xcords, int32_t ycords)
checkColision PROC
    ; First parameter in ESP+4 (int32_t*)
    mov EBX, [ESP+4] ; movement factor vector
    mov ECX, [ESP+8] ; x coordinate of the entity position (Column)
    mov EDX, [ESP+12] ; y coordinate of the entity position (Row)
    
    ; Simplify coordinates scale, 32 -> 1
    ;sub ECX, 65 ; substract the origine displayment in x
    ;sar ECX, 5 ; division by 32: 2^5, assume result in CL
    ;sub EDX, 127 ; substract the origin displayment in y
    ;sar EDX, 5 ; division by 32: 2^5, assume result in DL
    
    ; Obtain the index in the map according to the coordinates (actualRow*totalColumns + actualColumn)
    mov AL, 24 ; totalColumns
    imul DL ; row * 24 = AX
    add CX, AX ; column + (row*24)
    mov EDI, ECX ; index of the actual entity position
    
    ; Check movement factor
    mov EAX, [EBX] ; x movement factor
    cmp EAX, 0 ; no movement
    jne horizontal
    mov EAX, [EBX+4] ; y movement factor
    cmp EAX, 0 ; no movement
    jne vertical
    jmp noColision
    
    horizontal:
        
        add EDI, EAX ; add movementFactor
        cmp EDI, 312 ; avoid index out of bounds
        jge colision
        mov AL, map[EDI] ; obtain element in the map
        cmp AL, 0 ; empty cell
        je noColision
        jmp colision
        
    vertical:
        
        mov ECX, 24
        imul ECX ; y movementFactor(EAX) * 24(ECX) to access the element bellow in the next column
        add EDI, EAX ; add movementFactor
        cmp EDI, 312 ; avoid index out of bounds
        jge colision
        mov AL, map[EDI] ; obtain element in the map
        cmp AL, 0 ; empty cell
        je noColision
        jmp colision
    
    noColision: mov EAX, 0
    jmp return
    
    colision: mov EAX, 1
    jmp return
    
    return: ret
checkColision ENDP

end

