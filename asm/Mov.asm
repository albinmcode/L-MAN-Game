.model small
.stack 100h
.data
    mensajeLetraD db 'Tecla presionada: D $', 0
    mensajeLetraA db 'Tecla presionada: A $', 0
    mensajeLetraS db 'Tecla presionada: S $', 0
    mensajeLetraW db 'Tecla presionada: W $', 0
    mensajeError db 'Otra tecla presionada$', 0
.code
main:
    mov ax, @data     ; Inicializa el segmento de datos
    mov ds, ax
    mov es,ax
init:
    ; Esperar una tecla
    mov ah, 00h       ; Funci?n BIOS para leer tecla
    int 16h           ; Interrupci?n para capturar la tecla

    
    cmp al, 'd' or "D"       ; Compara con el ASCII de 'd'
    je teclaD
    cmp al, 'a' or "A"      ; Compara con el ASCII de 'a'
    je teclaA
    cmp al, 's' or "S"
    je teclaS
    cmp al, "w" or "W"
    je teclaW
    cmp al,"q"
    je exit
    jmp init

teclaD:
    ; Mostrar mensaje para la tecla 'd'
    mov ah, 09h       ; Funci?n DOS para mostrar cadena
    lea dx, mensajeLetraD
    int 21h
    jmp init

teclaA:
    ; Mostrar mensaje para la tecla 's'
    mov ah, 09h       ; Funci?n DOS para mostrar cadena
    lea dx, mensajeLetraA
    int 21h
    jmp init
    
teclaS:
    ; Mostrar mensaje para la tecla 'd'
    mov ah, 09h       ; Funci?n DOS para mostrar cadena
    lea dx, mensajeLetraS
    int 21h
    jmp init
teclaW:
    ; Mostrar mensaje para la tecla 'd'
    mov ah, 09h       ; Funci?n DOS para mostrar cadena
    lea dx, mensajeLetraW
    int 21h
    jmp init

otraTecla:
    ; Mostrar mensaje si no es 'd' ni 's'
    mov ah, 09h       ; Funci?n DOS para mostrar cadena
    lea dx, mensajeError
    int 21h

exit:
    ; Salir del programa
    mov ah, 4Ch       ; Terminar el programa
    int 21h
end main
