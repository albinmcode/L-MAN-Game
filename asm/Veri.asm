.model small
.stack 100h

.data
    palabra1 db 'HolaMundo', 0    ; Primera cadena con terminador null
    palabra2 db 'HolaTierra', 0   ; Segunda cadena con terminador null
    n dw 5                      ; N?mero de caracteres a comparar (declarado como palabra)
    mensaje_iguales db 'Las palabras son iguales.$', 0
    mensaje_diferentes db 'Las palabras son diferentes.$', 0

.code
main:
    mov ax, @data        ; Inicializar segmento de datos
    mov ds, ax
    mov es, ax

    lea si, palabra1     ; Cargar direcci?n de palabra1 en SI
    lea di, palabra2     ; Cargar direcci?n de palabra2 en DI
    mov cx, [n]          ; Cargar n en CX (n?mero de comparaciones)

comparar:
    mov al, [si]         ; Cargar car?cter actual de palabra1 en AL
    mov bl, [di]         ; Cargar car?cter actual de palabra2 en BL
    cmp al, bl           ; Comparar los caracteres
    jne diferente        ; Saltar a 'diferente' si no coinciden
    inc si               ; Avanzar al siguiente car?cter en palabra1
    inc di               ; Avanzar al siguiente car?cter en palabra2
    loop comparar        ; Repetir hasta que CX sea 0

iguales:
    lea dx, mensaje_iguales  ; Cargar mensaje de igualdad
    jmp imprimir             ; Saltar a imprimir

diferente:
    lea dx, mensaje_diferentes ; Cargar mensaje de diferencia

imprimir:
    mov ah, 09h              ; Funci?n DOS para imprimir cadena
    int 21h

    ; Salir del programa
    mov ax, 4C00h
    int 21h

end main
