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
        cmp Al, 2   ;Leaves the enemy's room and the player cannot enter
        je enemyExit
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
        cmp AL, 2  ;Leaves the enemy's room and the player cannot enter
        je enemyExit
        jmp colision
    
    noColision: mov EAX, 0
    jmp return
    
    colision: mov EAX, 1
    jmp return

    enemyExit: mov EAX, 2 ;Leaves the enemy's room and the player cannot enter
    jmp return
    
    return: ret
checkColision ENDP

; checkObstacleHorizontal(int32_t* playerCoords, int32_t* enemyCoords)
checkObstacleHorizontal PROC
    ; Parámetros:
    ; ESP+4 -> int32_t* playerCoords
    ; ESP+8 -> int32_t* enemyCoords

    ; Cargar los vectores
    mov EBX, [ESP+4]  ; Dirección del vector playerCoords
    mov ECX, [ESP+8]  ; Dirección del vector enemyCoords

    ; Cargar coordenadas del jugador
    mov EDX, [EBX]    ; x1 (jugador)
    mov ESI, [EBX+4]  ; y1 (jugador)

    ; Cargar coordenadas del enemigo
    mov EDI, [ECX]    ; x2 (enemigo)
    ; mov EDI, [ECX+4]  ; y2 (enemigo) -> no se necesita para horizontal

    ; Calcular dirección de iteración
    cmp EDX, EDI
    jle iterHorizontal ; Si x1 <= x2, iterar hacia la derecha
    xchg EDX, EDI      ; Intercambiar x1 y x2 si x1 > x2

    ; Bucle de iteración horizontal
iterHorizontal:
checkloopObstacle:
    mov AL, 24         ; Total columnas del mapa
    imul DL            ; row * 24 (DL contiene y1)
    add DX, AX        ; Calcular posición: columna + fila * columnas
    mov AL, map[EDX]  ; Leer valor del mapa en la posición calculada
    cmp AL, 0         ; ¿Es un obstáculo?
    jne Obstacle       ; Saltar si se encuentra un obstáculo
    inc EDX            ; Avanzar a la siguiente columna
    cmp EDX, EDI       ; ¿Llegamos a x2?
    jl checkloopObstacle ; Repetir si no hemos llegado
    jmp NoObstacle     ; No se encontraron obstáculos

NoObstacle:
    mov EAX, 0         ; Resultado: No hay obstáculos
    ret

Obstacle:
    mov EAX, 1         ; Resultado: Hay un obstáculo
    ret

checkObstacleHorizontal ENDP

; checkObstacleVertical(int32_t* playerCoords, int32_t* enemyCoords)
checkObstacleVertical PROC
    ; Parámetros:
    ; ESP+4 -> int32_t* playerCoords
    ; ESP+8 -> int32_t* enemyCoords

    ; Cargar los vectores
    mov EBX, [ESP+4]  ; Dirección del vector playerCoords
    mov ECX, [ESP+8]  ; Dirección del vector enemyCoords

    ; Cargar coordenadas del jugador
    mov EDX, [EBX]    ; x1 (jugador)
    mov ESI, [EBX+4]  ; y1 (jugador)

    ; Cargar coordenadas del enemigo
    mov EDI, [ECX+4]  ; y2 (enemigo)

    ; Calcular dirección de iteración
    cmp ESI, EDI
    jle iterVertical  ; Si y1 <= y2, iterar hacia abajo
    xchg ESI, EDI     ; Intercambiar y1 y y2 si y1 > y2

    ; Bucle de iteración vertical
iterVertical:
checkloopObstacle:
    mov AL, 24        ; Total columnas del mapa
    imul DL           ; row * 24 (DL contiene x1)
    add SI, AX        ; Calcular posición: columna + fila * columnas
    mov AL, map[SI]  ; Leer valor del mapa en la posición calculada
    cmp AL, 0        ; ¿Es un obstáculo?
    jne Obstacle      ; Saltar si se encuentra un obstáculo
    inc SI            ; Avanzar a la siguiente fila
    cmp SI, DI        ; ¿Llegamos a y2?
    jl checkloopObstacle ; Repetir si no hemos llegado
    jmp NoObstacle     ; No se encontraron obstáculos

NoObstacle:
    mov EAX, 0        ; Resultado: No hay obstáculos
    ret

Obstacle:
    mov EAX, 1        ; Resultado: Hay un obstáculo
    ret

checkObstacleVertical ENDP

end

