.386                     ; Habilitar instrucciones de 32 bits
.MODEL flat, C           ; Usar modelo plano y convención de llamada C
.STACK 512               ; Tamaño de la pila

PUBLIC compareWords      ; Exponer el procedimiento al linker

.CODE

compareWords PROC
    ; Parámetros:
    ;   esi -> dirección de la primera palabra
    ;   edi -> dirección de la segunda palabra
    ;   ecx -> número de caracteres a comparar

    push ebp
    mov ebp, esp          ; Establecer el marco de pila

    ; Inicializar punteros y contador
    mov esi, [ebp + 8]    ; Cargar dirección de la primera palabra en esi
    mov edi, [ebp + 12]   ; Cargar dirección de la segunda palabra en edi
    mov ecx, [ebp + 16]   ; Cargar número de caracteres a comparar en ecx

comparar:
    mov al, [esi]         ; Cargar el carácter actual de palabra1 en al
    mov bl, [edi]         ; Cargar el carácter actual de palabra2 en bl
    cmp al, bl            
    jne diferente         
    inc esi               
    inc edi               
    loop comparar         

iguales:
    mov eax, 1            
    jmp finalizar

diferente:
    mov eax, 0            

finalizar:
    pop ebp
    ret
compareWords ENDP

END
