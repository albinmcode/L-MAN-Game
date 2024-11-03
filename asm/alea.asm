.model small
.stack 100h
.data
    mensaje db 'Numero aleatorio: $'
    resultado db '00$', 0

.code
main:
    ; Inicializamos los segmentos de datos
    mov ax, @data
    mov ds, ax
    mov es, ax

    ; Llamar a la funci?n para generar el n?mero aleatorio
    call generar_aleatorio

    ; Mostrar el mensaje en pantalla
    lea dx, mensaje
    mov ah, 09h
    int 21h

    ; Mostrar el n?mero aleatorio en pantalla
    lea dx, resultado
    mov ah, 09h
    int 21h

    ; Finalizar el programa
    mov ah, 4Ch
    int 21h

generar_aleatorio:
    ; Llamar a INT 1Ah para obtener el conteo de tiempo
    mov ah, 00h
    int 1Ah  ; AL y AH contendr?n el conteo de ticks

    ; Usar el valor del temporizador como semilla pseudoaleatoria
    ; Hacer AND para limitar el valor al rango 0-99
    mov al, dl  ; Usamos DL porque contiene los ticks de baja frecuencia
    and al, 63  ; Asegura que el valor est? entre 0 y 63 (solo 6 bits)

    ; Convertir a dos d?gitos ASCII
    mov ah, 0   ; Limpiar AH
    mov bl, 10  ; Dividir entre 10 para separar los d?gitos
    div bl      ; AH = d?gito m?s significativo, AL = d?gito menos significativo

    ; Convertir ambos d?gitos a ASCII
    add ah, '0'
    add al, '0'

    ; Guardar los dos d?gitos en la variable resultado
    mov [resultado], ah   ; Primer d?gito
    mov [resultado + 1], al  ; Segundo d?gito

    ret

end main
