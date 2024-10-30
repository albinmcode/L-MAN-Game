; Reading a key from the options {W,A,S,D} to return the movement factor
; ///////////////////////////////////////////////////////////////
; MovementFactor:
; ## two digits number
; - Tens digit for horizontal movement
; - Units digit for vertical movement
; -1 value indicates left/up
; 0 value indicates no movement
; 1 value indicates right/down
; //////////////////////////////////////////////////////////////

cmpAlChr MACRO chr, tag
    cmp al, chr
    je tag
ENDM


.386 ; 32 bits program
.MODEL flat, c ; Flat memory model and C calling convention
.STACK 512


.code
movInput PROC
    ; Parameters in the stack declared as: extern "C" std::int32_t movInput(std::int32_t*, std::int8_t*)
    mov EBX, ESP
    add EBX, 4 ;  Access the first parameter pointer (int32_t*)
    mov EDX, [EBX] ; Obtain the real direction of the array
    ; Set movement factor to no movement
    mov ECX, 0
    mov [EDX], ECX
    mov [EDX+4], ECX
    ; Access the second parameter that contains the ASCII code of the pressed key
    add EBX, 4
    mov al, [EBX]
    
    input:
    ; Capture the keyboard
        ;mov ah, 01h       ; BIOS service to read character
        ;int 21h           ; Interruption to capture the keyboard
        ;mov al, 'd'
    
        cmpAlChr 'd', right
        cmpAlChr 'D', right
        cmpAlChr 'a', left
        cmpAlChr 'A', left
        cmpAlChr 's', down
        cmpAlChr 'S', down
        cmpAlChr 'w', up
        cmpAlChr 'W', up
        cmpAlChr ' ', space
        
        jmp any

    right: ; [1, 0]: move one place to the right and no vertical movement
        mov ECX, 1
        mov [EDX], ECX
        mov ECX, 0
        mov [EDX+4], ECX
        jmp any
    
    left: ; [-1, 0] : move one place to the left and no vertical movement
        mov ECX, -1
        mov [EDX], ECX
        mov ECX, 0
        mov [EDX+4], ECX
        jmp any
    
    down: ; [0, 1]: move one place down and no horizontal movement
        mov ECX, 0
        mov [EDX], ECX
        mov ECX, 1
        mov [EDX+4], ECX
        jmp any
    
    up: ; [0, -1]: move one place up and no horizontal movement
        mov ECX, 0
        mov [EDX], ECX
        mov ECX, -1
        mov [EDX+4], ECX
        jmp any
    
    space:
        mov EAX, 2 ; return value that indicates space key captured
        jmp return
    any:
        mov EAX, 0 ; no action
        
    return:
        ret
movInput ENDP

end