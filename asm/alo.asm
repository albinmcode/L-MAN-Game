.model small
.stack 100h

.data
    filename db 'input.txt', 0      ; Nombre del archivo a leer (terminado en null)
    buffer db 4096 dup (?)          ; Buffer para los datos le?dos
    lastWord db 16 dup ('$')       ; Buffer para la ?ltima palabra (m?ximo 16 bytes)
    error db 'Error al abrir el archivo.$'
    readError db 'Error al leer el archivo.$'
    leer dw 1                      ; M?ximo n?mero de palabras a leer y procesar

.code
main proc
    mov ax, @data
    mov ds, ax
    mov es, ax

    ; Abrir el archivo
    mov ah, 3Dh        ; Funci?n 3Dh - Abrir archivo
    mov al, 0          ; Modo de acceso: lectura
    lea dx, filename   ; Direcci?n del nombre del archivo
    int 21h
    jc file_error      ; Si hay error, saltar a file_error
    mov bx, ax         ; Guardar el handle del archivo en BX

    ; Leer el archivo completo en buffer
    mov ah, 3Fh        ; Funci?n 3Fh - Leer archivo
    mov cx, 4096       ; Leer hasta 4096 bytes
    lea dx, buffer     ; Direcci?n del buffer
    int 21h
    jc read_error      ; Si hay error, saltar a read_error

    ; Cerrar el archivo
    mov ah, 3Eh        ; Funci?n 3Eh - Cerrar archivo
    int 21h

    
    lea si, buffer         ; Puntero fuente (SI) al inicio del buffer
    lea di, lastWord      ; Puntero destino (DI) al inicio de last_word
    mov cx, 0              ; Contador de palabras le?das

find_words:
    cmp cx, leer           ; ?Hemos alcanzado el l?mite de palabras?
    je print_last_word     ; Si alcanzamos el l?mite, imprimir la ?ltima palabra

    lodsb                  ; Cargar byte de [SI] en AL y aumentar SI
    cmp al, 0              ; ?Fin del buffer?
    je print_last_word     ; Si es fin, imprimir la ?ltima palabra

    cmp al, 13             ; ?Es retorno de carro?
    je store_word          ; Si es, almacenar la palabra
    cmp al, 10             ; ?Es salto de l?nea?
    je store_word          ; Si es, almacenar la palabra

    stosb                  ; Almacenar byte en [DI] y aumentar DI
    jmp find_words         ; Continuar leyendo caracteres

store_word:
    ; Terminar la palabra actual con '$'
    mov byte ptr [di], '$'

    ; Incrementar contador de palabras
    inc cx                  ; Incrementar el contador aqu?

    ; Reiniciar DI para la siguiente palabra en last_word
    lea di, lastWord

    ; Saltar los caracteres no deseados (CR/LF)
    jmp find_words

print_last_word:
    ; Imprimir la ?ltima palabra almacenada
    mov ah, 9              ; Funci?n 9 - Imprimir cadena
    lea dx, lastWord      ; Direcci?n de la ?ltima palabra
    int 21h

    ; Salto de l?nea final
    mov ah, 2              ; Funci?n 2 - Salida de car?cter
    mov dl, 13             ; Retorno de carro
    int 21h
    mov dl, 10             
    int 21h

    ; Salir del programa
    mov ah, 4Ch            ; Funci?n 4Ch - Terminar programa
    int 21h

file_error:
    ; Manejo de error al abrir el archivo
    mov ah, 9              
    lea dx, error        
    int 21h
    jmp exit

read_error:
    ; Manejo de error al leer el archivo
    mov ah, 9              
    lea dx, readError   
    int 21h
    jmp exit

exit:
    mov ah, 4Ch            
    int 21h

main endp
end main
