#include <iostream>
#include <cstring>

// Declaración de la función ensambladora
extern "C"{
    int compareWords(const char* palabra1, const char* palabra2, unsigned int n);
    const char* getWordByIndex(int index);
    int loadMap(int8_t* a);
}


int main() {
    int index;
    std::cout << "Ingrese el índice de la palabra que desea: ";
    std::cin >> index;

    const char* word = getWordByIndex(index);

    const char* word2 = "apple";
    unsigned int n = 4;  // Número de caracteres a comparar

    // Llama a la función ensambladora y obtiene el resultado
    int resultado = compareWords(word, word2, n);

    // Imprime el resultado de la comparación
    if (resultado == 1) {
        std::cout << "Las palabras son iguales." << std::endl;
    }
    else {
        std::cout << "Las palabras son diferentes." << std::endl;
    }

    std::int8_t tempVector[312] = { 0 };
    loadMap(tempVector);
    for (int i = 0; i < 13 ; i++) {
        for (int j = 0; j < 24; j++) {
            std::cout << static_cast <int>(tempVector[i * 24 + j]);
        }
        std::cout << "\n";
    }
    std::cout << static_cast <int>(tempVector[1 * 24 + 0]);


    return 0;
}
