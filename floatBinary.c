/**
 *Andrew Budihardja
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

union ufloat{

    float f;
    unsigned u;

};


char *int2bin(int input){

    size_t bits = sizeof(int) * CHAR_BIT;
    char *str = malloc(bits + 1);

    if(!str){
    	return NULL;

    }
    str[bits] = 0;
    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&input;

    for(; bits--; u >>= 1){
    	str[bits] = u & 1 ? '1' : '0';
    }
    return str;

}


int bin2int(char *arr){

    //printf("~~~~~~~~What We Got: %s\n", arr);
    //convert 8bit string to integer
    int i = 0; int t = 0;

    for(; i < 8; i++)
        if(arr[7-i] == '1')
            t = t + (pow(2,i));
    return t;

}

float fraction_process(char *frac, float ff){

    int i = 0;
    //*
    for(; i < 23; i++){
        //do operation on reform according to the binary string
        if(frac[i] == '1'){
            ff = ff + (0.5/((int)pow(2, i)));
            printf("fraction = %f, after adding %f\n", ff, 0.5/((int)pow(2, i)));
        }else if(frac[i] == '0'){
            printf("fraction = %f, after skipping %f\n", ff, 0.5/((int)pow(2, i)));
        }
    }
    //*/
    return ff;
}

float expon_process(int expp, float ff){

    int i = 0;

    if(expp > 0){
        for(; i < expp; i++){
            ff = ff * 2;
            printf("times 2 = %f\n", ff);
        }

    }else if(expp < 0){

        for(; i > expp; i--){
            ff = ff / 2;
            printf("divided by 2 = %f\n", ff);
        }
    }
    return ff;
}

int main(){

    union ufloat n;
    char * bin_notation; char sign; char exponent[9]; char fraction[24];
    int expon = 0;
    float reformed = 1;//will use this variable to recreate the number from binary to single precision floating point

    printf("Enter a float:\t");
    scanf("%f", &n.f); bin_notation = int2bin(n.u);

    sign = bin_notation[0]; //sign is the most significant bit of the number
    strncpy(exponent, &bin_notation[1], 8);exponent[8] = 0; //exponent are the next eight bits of the number
    strncpy(fraction, &bin_notation[9], 23);fraction[23] = 0; //fraction are the next twenty three bits of the number

    printf("your float was read as: %f\n", n.f);
    printf("your float in 32 bits: %s\n", bin_notation);
    printf("Sign: %c\nExponent: %s\nFraction: %s\n", sign, exponent, fraction);
    printf("Creating the fraction:\n");
    printf("fraction = %f (the implicit 1)\n", reformed);

    reformed = fraction_process(fraction, reformed);//function call to process fraction
    expon = bin2int(exponent);//function call to make int out of binary string
    expon = expon - 127;//normalizing the exponent
    printf("Applying the exponent:\nunbiased exponent = %d\n", expon);

    reformed = expon_process(expon, reformed);//function call to process the exponent
    printf("final answer: %f\n", reformed);

    return 0;
}
