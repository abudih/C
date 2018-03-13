/**
 * This program does a guessing game to the user.
 * It calculates a random number then asks the user to input
 * a number until it hits that number right.
 * Andrew Budihardja
 */


#include<stdio.h>
#define CONST 50 //constant to control the range of the pseudorandom numbers

//global variables
int number_of_games=0;
int number_of_guesses=0;
int max_guesses=0;
/**
 * gives the user instruction in order
 * for them to know how to play the game.
 */
void ask_user(){
	printf("This program allows you to play a guessing game.\n"
				"I will think of a number between 1 and %d\n"
				"and will allow you to guess until you get it.\n"
				"For each guess, I will tell you whether the\n"
				"right answer is higher or lower than your guess\n", CONST);
}
/**
 * plays the game to the user in 1 cycle until
 * the user hits the right number.
 */
void play_game(int number){

	int input;
	int guess =1;
	int bool= 1;

	while(bool){
		printf("\nYour guess?");
		scanf("%d",&input);
		if(input>number){
			printf("lower");
			guess++;
		}else if(input<number){
			printf("higher");
			guess++;
		}else{
			printf("You got it right in %d guesses.\n",guess);
			bool=0;
		}
	}
	if(guess>max_guesses){
			max_guesses=guess;
	}
	number_of_guesses+=guess;
}
/**
 * prints the overall reports to the user
 * after the user does not want to play the game anymore.
 */
void print_results(){

	printf("\nOverall results:\n"
			"\t total games   = %d\n"
			"\t total guesses = %d\n"
			"\t guesses/game  = %.14f\n"
			"\t max guesses   = %d",number_of_games,number_of_guesses,((float)number_of_guesses/number_of_games),max_guesses);
}

/**
 * main method that controls the 3 other functions.
 * ask_user & play_game & print_results
 */
int main(){
	//srand(&CONST);
	ask_user();

	play_game(rand()%CONST);

	int bool=1;
	char words[50];
	number_of_games++;

	while(bool){
		printf("Do you want to play again?");
		scanf("%s",&words);
		if(words[0]=='y'||words[0]=='Y'){
			printf("\nI'm thinking of a number...");
			play_game(rand()%CONST);
			number_of_games++;
		}else{
			print_results();
			bool=0;
		}
	}
	return 0;
}



