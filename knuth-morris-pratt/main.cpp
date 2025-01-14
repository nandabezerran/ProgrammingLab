#include <iostream>
#include <string.h>
#include "instancias_Reais_Trabalho_2.hpp"
#include <time.h>
#include <chrono>

/* It counts how many elements there is in the char vector
 * @param pPointer the vector we want to count
 */
int countCStringSize(const char* pPointer){
    int count = 0;
    while(*pPointer != '\0'){
        count++;
        pPointer++;
    }
    return count;
}

/* It generates an vector with only a's. If the variable b is 1 our last letter will be a b
 * @param pVector the structure already allocated
 * @param pSize how big the user want the vector
 * @param b to know if we are going to have a b how the last letter of the vector
 */
void generateVectorA(char* pVector, int pSize, int b){
    for (int i = 0; i < pSize - 1; ++i) {
        pVector[i] = 'a';
    }
    if (b == 1){
        pVector[pSize - 1] = 'b';
        pVector[pSize] = '\0';
    }
    else {
        pVector[pSize - 1] = '\0';
    }
}
/* It generates an aleatory vector given a size with the first range letters of de alphabet
 * @param vector the structure already allocated
 * @param size how big the user want the vector
 * @param range the firsts letters of the alphabet
 */
void aleatoryVector(char* vector, int size, int range){
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                       'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for (int i = 0; i < size - 1; ++i) {
        vector[i] = alphabet[rand() % range];
    }
    vector[size-1] = '\0';

}

/* Print to the user the result vector
 * @param vector the vector we want to print
 */
void printResultVector(const int *vector){
    int elements = 0;
    while(*vector != -1){
        std::cout << *vector << std::endl;
        vector = vector + 1;
        elements++;
    }
    std::cout << elements << std::endl;
}

/* Print a char vector
 * @param vector the vector we want to print
 */
void printCharVector(const char *vector){
    while(*vector != '\0'){
        std::cout << *vector;
        vector = vector + 1;
    }
    std::cout << std::endl;
}

/* Searches using a brute force way subsequences in the text which are equal to the pattern. Then fill up the pResult
 * vector with the index in which those subsequences starts. When there is no more ocurrencies the last item of the vector is a
 * -1 to indicate the end of the content, because the pResult may be bigger than its content.
 * @param pText the text in which we want to search the subsequences
 * @param pPattern pattern we want to search in the text.
 * @param pResult vector that will be filled up with the index in which those subsequences starts.
 */
void bruteForceAlgorithm(const char* pText, const char* pPattern, int *pResult){
    const char *goThroughText = pText;      // It counts in which index we are in the text;
    int countText = countCStringSize(pText);
    const char *finalText = pText + countText;
    int porcentText;
    int porcentAux = -1;
    int aux = 0;

    while(*goThroughText != '\0'){
        if(*goThroughText == *pPattern){
            const char *match = goThroughText + 1;
            const char *patternAux = pPattern + 1;
            while(*match == *patternAux && *patternAux != '\0') {
                match++;
                patternAux++;
            }
            if(*patternAux == '\0') {
                *pResult = (int) (goThroughText - pText);
                pResult++;
            }
        }
        goThroughText++;
        porcentText = (int)((countText - (double)(finalText - goThroughText))*100/countText);
        if (porcentAux != porcentText) {
            std::cout << "[";

            for (int i = 0; i <= porcentText / 10; i++) {
                std::cout << "=";
                aux++;
            }
            std::cout << ">";
            for (int j = 0; j <= (10 - aux); j++) {
                std::cout << ".";
            }
            std::cout << "] ";

            std::cout << porcentText;
            std::cout << "%";
            std::cout << "\r";
            aux = 0;
        }
        porcentAux = porcentText;
    }
    std::cout << std::endl;
    *pResult = -1;
}

/* Calculates the vector pPiVector, where pPiVector[j] is the length of the longest proper prefix of the pattern
 * pPattern[0 ... j] which is also a suffix of this pattern.
 * @param pPattern the pattern you want to search the ocurrencies in the text
 * @param pPiVector the vector to be filled with the size of the longest prefix in every pPattern[0 ... j]
 */
void computationOfPi(const char* pPattern, int* pPiVector){
    int k;
    int length;
    *pPiVector = 0;
    for (int i = 1; pPattern[i] != '\0' ; ++i) {
        k = i - 1;
        for(;;){
            length = pPiVector[k];
            if (length == 0) {
                if (pPattern[0] == pPattern[i]) {
                    pPiVector[i] = 1;
                    break;
                } else {
                    pPiVector[i] = 0;
                    break;
                }
            } else {
                if (pPattern[i] == pPattern[length]) {
                    pPiVector[i] = length + 1;
                    break;
                } else {
                    k = length - 1;
                }
            }
        }
    }
}

/* Searches using the technique of Knuth Morris Pratt subsequences in the text which are equal to the pattern.
 * Then fill up the pResult vector with the index in which those subsequences starts.
 * When there is no more ocurrencies the last item of the vector is a -1 to indicate the end of the content, because
 * the pResult may be bigger than its content.
 * @param pText the text in which we want to search the subsequences
 * @param pPattern pattern we want to search in the text.
 * @param pResult vector that will be filled up with the index in which those subsequences starts.
 */
void knuthMorrisPratt(const char* pText, const char* pPattern, int *pResult){
    int *piVector =  new int[countCStringSize(pPattern)]();
    int goThroughText = 0;
    int goThroughPattern = 0;

    int countText = countCStringSize(pText);
    int porcentText;
    int porcentAux = -1;
    int aux = 0;


    computationOfPi(pPattern, piVector);

    while(pText[goThroughText] != '\0'){
        if(pText[goThroughText] != pPattern[goThroughPattern]){
            if(goThroughPattern == 0){
                goThroughText++;
            }
            else{
                goThroughPattern = piVector[goThroughPattern - 1];
            }
        }
        else{
            if(pPattern[goThroughPattern + 1] == '\0' ){
                *pResult = goThroughText - goThroughPattern;
                pResult = pResult + 1;
                goThroughPattern = piVector[goThroughPattern];
                goThroughText++;
            }
            else{
                goThroughText++;
                goThroughPattern++;
            }
        }
        porcentText = (int)((double)(countText - (countText - goThroughText))*100/countText);
        if (porcentAux != porcentText) {
            std::cout << "[";
            for (int i = 0; i <= porcentText / 10; i++) {
                std::cout << "=";
                aux++;
            }
            std::cout << ">";
            for (int j = 0; j <= (10 - aux); j++) {
                std::cout << ".";
            }
            std::cout << "] ";

            std::cout << porcentText;
            std::cout << "%";
            std::cout << "\r";
            aux = 0;
        }
        porcentAux = porcentText;
    }
    std::cout << std::endl;
    *pResult = -1;
    delete[] piVector;

}
/* It compares two vectors to check if they are equal. Return true if they are equal and false otherwise
 * @param pResultBrute
 * @param pResultKnuth
 */
bool checkEquality(int* pResultBrute, int* pResultKnuth){
    bool flag = true;
    while(*pResultBrute != -1 && *pResultKnuth != -1){
        if(*pResultBrute != *pResultKnuth){
            flag = false;
        }
        pResultBrute++;
        pResultKnuth++;
    }
    return flag;
}

int main() {

    srand((unsigned)clock()); // To generate the aleatory vectors;

    int instancesOp;
    int indexRealPattern;
    int textSize;
    int patternSize;
    int firstLetters;
    int op = 1;
    bool eqResultVectors;

    while(op == 1) {
        std::cout << "Please, enter the kind of instances generator you want\n >>> 1 - Random\n >>> 2 -"
                     " Real\n >>> 3 - Worst Case #1\n >>> 4 - Worst Case #2" << std::endl;
        std::cin >> instancesOp;

        while(instancesOp < 1 || instancesOp > 4){
            std::cout << "Please, reenter the what of instances generator you want, you entered a invalid one\n"
                         " >>> 1 - Random\n >>> 2 -"
                         " Real\n >>> 3 - Worst Case #1\n >>> 4 - Worst Case #2" << std::endl;
            std::cin >> instancesOp;
        }

        if (instancesOp == 1) {

            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern it must be smaller than the size of the text"
                         "" << std::endl;
            std::cin >> patternSize;
            std::cout << "Please, enter your L, it must be a number between 0 ... 26. (L firts leters of the alphabet)"
                      << std::endl;
            std::cin >> firstLetters;

            while(patternSize > textSize){
                std::cout << "Please, reenter the size of the text" << std::endl;
                std::cin >> textSize;
                std::cout << "Please, reenter the size of the pattern it must be smaller than the size of the text"
                             "" << std::endl;
                std::cin >> patternSize;
            }

            while(firstLetters < 0 || firstLetters > 26){
                std::cout << "Please, reenter your L, it must be a number between 0 ... 26. (L firts leters of the "
                             "alphabet)"<< std::endl;
                std::cin >> firstLetters;
            }

            textSize++;
            patternSize++;

            char *text = new char[textSize];
            char *pattern = new char[patternSize];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            aleatoryVector(text, textSize, firstLetters);
            aleatoryVector(pattern, patternSize, firstLetters);

//            printCharVector(text);
//            printCharVector(pattern);

            auto start = std::chrono::high_resolution_clock::now(); // Starts the clock;
            bruteForceAlgorithm(text, pattern, resultBrute);
            auto stop = std::chrono::high_resolution_clock::now();

            // Compute the duration of the function;
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by BruteForce algorithm: "
                 << duration.count() << " microseconds\n" << std::endl;

            start = std::chrono::high_resolution_clock::now();
            knuthMorrisPratt(text, pattern, resultKnuth);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by Knuth Morris Pratt algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;


            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            std::cout << "---------------------------------------------------------------------------------------------"
                      << std::endl;

            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;
        }

        if (instancesOp == 2) {
            std::cout << "Please, enter the index of the Pattern, its a number in [0 ... 35129]" << std::endl;
            std::cin >> indexRealPattern;

            while(indexRealPattern < 0 || indexRealPattern > 35129 ){
                std::cout << "Please, reenter the index of the Pattern, it must be a number in [0 ... 35129]"
                << std::endl;
                std::cin >> indexRealPattern;
            }

            std::cout << "The pattern you choose: ";
            std::cout << Padroes_Palavras[indexRealPattern] ;
            std::cout << "\n" << std::endl;

            int *resultBrute = new int[sizeof(Padroes_Palavras)]();
            int *resultKnuth = new int[sizeof(Padroes_Palavras)]();

            auto start = std::chrono::high_resolution_clock::now(); // Starts the clock;
            bruteForceAlgorithm(Texto_Livros, Padroes_Palavras[indexRealPattern], resultBrute);
            auto stop = std::chrono::high_resolution_clock::now();

            // Compute the duration of the function;
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by BruteForce algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            start = std::chrono::high_resolution_clock::now();
            knuthMorrisPratt(Texto_Livros, Padroes_Palavras[indexRealPattern], resultKnuth);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by Knuth Morris Pratt algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            std::cout << "---------------------------------------------------------------------------------------------"
                      << std::endl;

            delete[] resultBrute;
            delete[] resultKnuth;
        }

        if (instancesOp == 3){
            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern" << std::endl;
            std::cin >> patternSize;

            while(patternSize > textSize){
                std::cout << "Please, reenter the size of the text" << std::endl;
                std::cin >> textSize;
                std::cout << "Please, reenter the size of the pattern it must be smaller than the size of the text"
                             "" << std::endl;
                std::cin >> patternSize;
            }

            textSize++;
            patternSize++;

            char       *text = new char[textSize];
            char    *pattern = new char[patternSize];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            generateVectorA(text, textSize, 0);
            generateVectorA(pattern, patternSize - 1, 1);

//            printCharVector(text);
//            printCharVector(pattern);


            auto start = std::chrono::high_resolution_clock::now(); // Starts the clock;
            bruteForceAlgorithm(text, pattern, resultBrute);
            auto stop = std::chrono::high_resolution_clock::now();

            // Compute the duration of the function;
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by BruteForce algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            start = std::chrono::high_resolution_clock::now();
            knuthMorrisPratt(text, pattern, resultKnuth);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by Knuth Morris Pratt algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            std::cout << "---------------------------------------------------------------------------------------------"
                      << std::endl;

            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;

        }

        if (instancesOp == 4){
            std::cout << "Please, enter the size of the text" << std::endl;
            std::cin >> textSize;
            std::cout << "Please, enter the size of the pattern" << std::endl;
            std::cin >> patternSize;

            while(patternSize > textSize){
                std::cout << "Please, reenter the size of the text" << std::endl;
                std::cin >> textSize;
                std::cout << "Please, reenter the size of the pattern it must be smaller than the size of the text"
                             "" << std::endl;
                std::cin >> patternSize;
            }


            // Adding the extra char for the \0
            textSize++;
            patternSize++;

            char       *text = new char[textSize];
            char    *pattern = new char[patternSize];
            int *resultBrute = new int[textSize];
            int *resultKnuth = new int[textSize];

            generateVectorA(text, textSize, 0);
            generateVectorA(pattern, patternSize, 0);

//            printCharVector(text);
//            printCharVector(pattern);

            auto start = std::chrono::high_resolution_clock::now(); // Starts the clock;
            bruteForceAlgorithm(text, pattern, resultBrute);
            auto stop = std::chrono::high_resolution_clock::now();

            // Compute the duration of the function;
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by BruteForce algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            start = std::chrono::high_resolution_clock::now();
            knuthMorrisPratt(text, pattern, resultKnuth);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::cout << "Time taken by Knuth Morris Pratt algorithm: "
                      << duration.count() << " microseconds\n" << std::endl;

            eqResultVectors = checkEquality(resultBrute, resultKnuth);

            if(!eqResultVectors){
                std::cout << "The result vectors aren't equal" << std::endl;
            }
            else{
                std::cout << "The result vectors are equal" << std::endl;
            }

            std::cout << "---------------------------------------------------------------------------------------------"
            << std::endl;
            delete[] text;
            delete[] pattern;
            delete[] resultBrute;
            delete[] resultKnuth;
        }
        std::cout << "Do you want to continue?\n >>> Press 1 to continue\n >>> Press anything to exit." << std::endl;
        std::cin >> op;

    }
    return 0;
}