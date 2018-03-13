/**
 * Andrew Budihardja
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Converts the given number to hexadecimal string.
 *
 * @dec: the given number
 *
 * @return: hexadecimal string
 */
char* convert_decimal_to_hex(int dec) {
    char digit[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    char* hex = malloc(3);
    hex[0] = digit[dec / 16];
    hex[1] = digit[dec % 16];
    hex[2] = 0;

    return hex;
}

/* Converts the given number to binary string.
 *
 * @dec: the given number
 *
 * @return: binary string
 */
char* convert_decimal_to_binary(int dec) {
    char* bin = malloc(9);
    int i;
    for (i = 7; i >= 0; i--) {
        bin[i] = dec % 2 + '0';
        dec /= 2;
    }
    bin[8] = 0;
    return bin;
}

/* Creates a file with random numbers
 *
 * @return: 0 if successful; otherwise, return 1
 */
int random_number_file_generator(){
    FILE *file = fopen("randomNumbers.txt", "w");
    if (file == 0) {
        printf("\nError while creating randomNumbers.txt");
        return 1;
    }

    // Initializes random number generator
    srand(time(0));

    // Random a number between 10 and 100 (random 0-90 + 10)
    int i, nums = rand() % 91 + 10;

    // Random nums numbers (0-255), and write them into the file
    for (i = 0; i < nums; i++) {
        fprintf(file, "%d\r\n", rand() % 256);
    }

    fclose(file);
    return 0;
}

/* Reads the input file, converts, and then write to the output file.
 */
void hex_and_binary_file_generator(){

    FILE *inFile = fopen("randomNumbers.txt", "r");
    if (inFile == 0) {
        printf("\nError while reading randomNumbers.txt");
        return;
    }
    FILE *outFile = fopen("hexAndBinary.txt","w");
    if (outFile == 0) {
        printf("\nError while creating hexAndBinary.txt");
        return;
    }
    int dec;
    char* hex;
    char* bin;
    // reads input file and converts to other formats, and then write to output file
    while(fscanf(inFile, "%d", &dec) == 1) {
        hex = convert_decimal_to_hex(dec);
        bin = convert_decimal_to_binary(dec);
        fprintf(outFile, "0x%s: %s (%d)\r\n", hex, bin, dec);
    }
    fclose(inFile);
    fclose(outFile);
}

int main(void){


    random_number_file_generator();
    hex_and_binary_file_generator();
    printf("\nDone!");
    return 0;
}
