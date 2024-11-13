.386                     
.MODEL flat, C           
.STACK 512               

PUBLIC stringLength     

.CODE

stringLength PROC
    ; Parámetro:
    ;   esi -> dirección de la cadena

    push ebp
    mov ebp, esp          

    ; Inicializar el puntero y el contador
    mov esi, [ebp + 8]    
    xor ecx, ecx          

contar:
    mov al, [esi]         
    cmp al, 0             
    je fin                
    inc ecx               
    inc esi               
    jmp contar            

fin:
    mov eax, ecx          ; Colocar el número de caracteres en eax como retorno

    pop ebp
    ret
stringLength ENDP

END
