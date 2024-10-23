; Programa en TASM para leer e imprimir las tres primeras palabras de un archivo de texto

.model small
.stack 100h

.data
    filename db 'input.txt',0      ; Nombre del archivo a leer (terminado en null)
    buffer db 256 dup (?)          ; Buffer para almacenar los datos le?dos
    wordBuffer db 256 dup ('$')   ; Buffer para la palabra actual (terminado en '$')

    messageErrorFile db 'Error al abrir el archivo.$'
    messageErrorRead db 'Error al leer el archivo.$'

.code
main proc
    mov ax, @data
    mov ds, ax
    mov es,ax
    
    ; Abrir el archivo
    mov ah, 3Dh        ; Funcion 3Dh - Abrir archivo
    mov al, 0          ; Modo de acceso: lectura
    lea dx, filename   ; Direcci?n del nombre del archivo
    int 21h
    jc fileError      
    mov bx, ax         

    ; Leer del archivo
    mov ah, 3Fh        ; Funcion 3Fh - Leer archivo
    mov cx, 256        
    lea dx, buffer     
    int 21h
    jc readError     

    ; Cerrar el archivo
    mov ah, 3Eh        ; Funcion 3Eh - Cerrar archivo
    int 21h

    ; Inicializar variables
    lea si, buffer         
    lea di, wordBuffer   
    mov cx, 0             

findWords:
    cmp cx, 10              
    je endProgram         

    lodsb                  
    cmp al, 0              
    je printAndCheck     

    cmp al, ' '            
    je printAndCheck    
    cmp al, 13             
    je printAndCheck    
    cmp al, 10             
    je printAndCheck     

    stosb                  
    jmp findWords         

printAndCheck:
    cmp di, offset wordBuffer ; Hay algo en wordBuffer?
    je skipPrint; Si DI apunta al inicio, no hay palabra que imprimir

    mov byte ptr [di], '$' 

    ; Imprimir la palabra
    mov ah, 9              
    lea dx, wordBuffer    
    int 21h

    ; Imprimir un espacio entre palabras
    mov ah, 2              
    mov dl, ' '            
    int 21h

    ; Reiniciar wordBuffer
    lea di, wordBuffer    

    ; Incrementar contador de palabras
    inc cx

skipPrint:
    cmp al, 0             
    je endProgram         
    jmp findWords         

endProgram:
    ; Salto de linea al final
    mov ah, 2              
    mov dl, 13             
    int 21h
    mov dl, 10            
    int 21h

    ; Salir del programa
    mov ah, 4Ch           
    int 21h

fileError:
    ; Manejo de error al abrir el archivo
    mov ah, 9              
    lea dx, messageErrorFile      
    int 21h
    jmp exit

readError:
    ; Manejo de error al leer el archivo
    mov ah, 9             
    lea dx, messageErrorRead   
    int 21h
    jmp exit

exit:
    mov ah, 4Ch            
    int 21h

main endp
end main