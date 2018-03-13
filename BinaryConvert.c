/**
 *Andrew Budihardja
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**
 * converts binary numbers
 * into float
 */
float binary_float(char number[]){

	int i =0,k =0,j,integer=0;
	float result,fractional=0;
	int before_dec[20], after_dec[20];

	while(number[i]!='.'){
		before_dec[i]=(int)number[i]-48;
		i++;
	}

	j=i;
	i--;
	for(;i>=0;i--){
		 integer = integer + (before_dec[i] *(int) pow(2,k));
		 k++;
	}

	k=-1;
	for(int l = j+1;l<strlen(number);l++){

		after_dec[l]=(int)number[l]-48;
		fractional = fractional + (after_dec[l]*pow(2,k));
		k--;
	}
	result=integer+fractional;
	return result;
}


/**
 * converts float to binary numbers
 */
void float_binary(float theNumber){
	int integer,i=0,m=0;
	float fractional,result, temp;
	int d[20];
	char f[30], d2[100];

	integer=(int)theNumber;
	fractional = theNumber - integer;

//	printf("\n\n %d", integer);
//	printf("\n%f", fractional);
	while(integer>0){
		 d[i]=integer%2;
		 i++;
		 integer=integer/2;
	}

	for(int j=i-1;j>=0;j--){
		d2[m]=(char)d[j]+48;
		m++;
	}

	int g= -1,k=m+1;
	d2[m]='.';
	while(fractional>=0){
		if((k-(m+1)==20)){
			break;
		}

		if(fractional>=pow(2,g)){
			fractional=fractional-pow(2,g);
			d2[k]='1';
			k++;
			g--;
		}else{
			d2[k]='0';
			k++;
			g--;
		}
	}

	if(d2[0]=='.'){
		printf("\n0%s\n",d2);
	}else if(d2[m+1]=='\0'){
		d2[m+1]='0';
		printf("\n%s0\n", d2);
	}else{
		printf("\n%s0\n", d2);
	}
}

/**
 *calculates 2 float numbers
 *then calculate them using operator given.
 */
float calculate(float a , float b, char c){
	float result=0;

	if(c=='+'){
		result=a+b;
	}else if(c=='-'){
		result=a-b;
	}else if(c=='*'){
		result=a*b;
	}else{
		result=a/b;
	}
//	printf("\nresult :%f",result);
	return result;
}

int main(){

	char first_input[100];
	char second_input[100];
	float first_number,second_number,result ;
	char operator;

	while(1){
		printf("\nPlease enter two binary numbers with decimals(such as 11.11 and 11.11)\n"
				"& operators(addition,subtraction,multiplication and division).\nPlease use spaces "
				"between the operators and the numbers.  (Press Q to quit) : ");

		scanf("%s", &first_input);
		if(first_input[0]=='Q'){
			break;
		}else{

			first_number=binary_float(first_input);
			printf("\nfirst number: %f",first_number);
			scanf(" %c", &operator);

			scanf("%s", &second_input);
			second_number=binary_float(second_input);
			printf("\nsecond number: %f",second_number);
			result=calculate(first_number,second_number,operator);
			float_binary(result);
		}
	}
	return 0;
}
