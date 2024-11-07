.386                      ; Habilitar instrucciones de 32 bits
.MODEL flat, C            ; Usar modelo plano y convención de llamada C
.STACK 512                ; Tamaño de la pila

PUBLIC getWordByIndex     ; Exponer el procedimiento al linker

.DATA
wordsList db 'apple', 0
          db 'book', 0
          db 'cat', 0
          db 'dog', 0
          db 'elephant', 0
          db 'friend', 0
          db 'garden', 0
          db 'house', 0
          db 'ice', 0
          db 'jump', 0
          db 'key', 0
          db 'light', 0
          db 'music', 0
          db 'night', 0
          db 'orange', 0
          db 'paper', 0
          db 'queen', 0
          db 'river', 0
          db 'sun', 0
          db 'tree', 0
          db 'umbrella', 0
          db 'village', 0
          db 'water', 0
          db 'yellow', 0
          db 'zebra', 0
          db 'chair', 0
          db 'table', 0
          db 'door', 0
          db 'window', 0
          db 'roof', 0
          db 'moon', 0
          db 'star', 0
          db 'beach', 0
          db 'mountain', 0
          db 'ocean', 0
          db 'bridge', 0
          db 'road', 0
          db 'school', 0
          db 'teacher', 0
          db 'student', 0
          db 'bookstore', 0
          db 'library', 0
          db 'computer', 0
          db 'phone', 0
          db 'mouse', 0
          db 'keyboard', 0
          db 'clock', 0
          db 'watch', 0
          db 'glass', 0
          db 'bottle', 0
          db 'shirt', 0
          db 'pants', 0
          db 'shoes', 0
          db 'hat', 0
          db 'coat', 0
          db 'bag', 0
          db 'spoon', 0
          db 'fork', 0
          db 'knife', 0
          db 'plate', 0
          db 'cup', 0
          db 'food', 0
          db 'drink', 0
          db 'bread', 0
          db 'fruit', 0
          db 'vegetable', 0
          db 'meat', 0
          db 'fish', 0
          db 'chicken', 0
          db 'sugar', 0
          db 'salt', 0
          db 'pepper', 0
          db 'coffee', 0
          db 'tea', 0
          db 'milk', 0
          db 'juice', 0
          db 'car', 0
          db 'bus', 0
          db 'train', 0
          db 'plane', 0
          db 'bicycle', 0
          db 'walk', 0
          db 'run', 0
          db 'swim', 0
          db 'dance', 0
          db 'sing', 0
          db 'laugh', 0
          db 'smile', 0
          db 'cry', 0
          db 'love', 0
          db 'happy', 0
          db 'sad', 0
          db 'angry', 0
          db 'tired', 0
          db 'fast', 0
          db 'slow', 0
          db 'big', 0
          db 'small', 0
          db 'hot', 0
          db 'cold', 0
          db 'manzana', 0
          db 'libro', 0
          db 'gato', 0
          db 'perro', 0
          db 'elefante', 0
          db 'amigo', 0
          db 'jardin', 0
          db 'casa', 0
          db 'hielo', 0
          db 'saltar', 0
          db 'llave', 0
          db 'luz', 0
          db 'musica', 0
          db 'noche', 0
          db 'naranja', 0
          db 'papel', 0
          db 'reina', 0
          db 'rio', 0
          db 'sol', 0
          db 'arbol', 0
          db 'paraguas', 0
          db 'aldea', 0
          db 'agua', 0
          db 'amarillo', 0
          db 'cebra', 0
          db 'silla', 0
          db 'mesa', 0
          db 'puerta', 0
          db 'ventana', 0
          db 'techo', 0
          db 'luna', 0
          db 'estrella', 0
          db 'playa', 0
          db 'montana', 0
          db 'oceano', 0
          db 'puente', 0
          db 'camino', 0
          db 'escuela', 0
          db 'profesor', 0
          db 'estudiante', 0
          db 'libreria', 0
          db 'biblioteca', 0
          db 'computadora', 0
          db 'telefono', 0
          db 'raton', 0
          db 'teclado', 0
          db 'reloj', 0
          db 'pulsera', 0
          db 'vaso', 0
          db 'botella', 0
          db 'camisa', 0
          db 'pantalones', 0
          db 'zapatos', 0
          db 'sombrero', 0
          db 'abrigo', 0
          db 'bolsa', 0
          db 'cuchara', 0
          db 'tenedor', 0
          db 'cuchillo', 0
          db 'plato', 0
          db 'taza', 0
          db 'comida', 0
          db 'bebida', 0
          db 'pan', 0
          db 'fruta', 0
          db 'vegetal', 0
          db 'carne', 0
          db 'pescado', 0
          db 'pollo', 0
          db 'azucar', 0
          db 'sal', 0
          db 'pimienta', 0
          db 'cafe', 0
          db 'te', 0
          db 'leche', 0
          db 'jugo', 0
          db 'carro', 0
          db 'autobus', 0
          db 'tren', 0
          db 'avion', 0
          db 'bicicleta', 0
          db 'caminar', 0
          db 'correr', 0
          db 'nadar', 0
          db 'bailar', 0
          db 'cantar', 0
          db 'reir', 0
          db 'sonrisa', 0
          db 'llorar', 0
          db 'amor', 0
          db 'feliz', 0
          db 'triste', 0
          db 'enojado', 0
          db 'cansado', 0
          db 'rapido', 0
          db 'lento', 0
          db 'grande', 0
          db 'pequeno', 0
          db 'caliente', 0
          db 'frio', 0

wordsCount DWORD 200        ; Cantidad de palabras en la lista

.CODE

getWordByIndex PROC
    ; Guardar registros usados
    push ebp
    mov ebp, esp

    ; Obtener el índice de la pila
    mov eax, [ebp+8]      ; El índice está en [ebp+8]

    ; Verificar si el índice es válido
    cmp eax, wordsCount
    jae invalid_index     ; Si índice >= wordsCount, es inválido

    ; Calcular la posición de la palabra
    mov ecx, 0            ; Contador de palabras
    mov edi, OFFSET wordsList

find_word:
    cmp ecx, eax          ; Comparar el contador con el índice
    je word_found         ; Si son iguales, hemos encontrado la palabra
    inc ecx               ; Incrementar el contador

    ; Avanzar al siguiente elemento en la lista
next_char:
    inc edi
    cmp byte ptr [edi], 0 ; Buscar el delimitador de fin de palabra (0)
    jne next_char         ; Seguir hasta encontrar el 0
    inc edi               ; Moverse al carácter después de 0
    jmp find_word         ; Repetir hasta encontrar la palabra deseada

word_found:
    mov eax, edi          ; Guardar la dirección de la palabra en eax
    jmp done

invalid_index:
    mov eax, 0            ; Retornar 0 si el índice es inválido

done:
    ; Restaurar registros y retornar
    pop ebp
    ret
getWordByIndex ENDP

END
