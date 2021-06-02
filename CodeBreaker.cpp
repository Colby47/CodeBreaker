// Instructions
// 
// Implement a code breaking game as a console application. At the beginning of the game, it randomly generates a secret 4 digit code.
// Each digit should be unique. For example, 0123, 9548, and 3217 are valid codes, but 1102, 4445, and 7313 are not.
//
// Once the number has been generated, the player has 8 chances to guess the code. After each guess, the game should report how many digits
// they guessed correctly, and how many had the right number, but in the wrong place. For example, with a secret code of 0123, a guess of 0451
// has one digit correct (the 0), and one digit with the right number in the wrong place (the 1).
// 
// After the player has either correctly broken the code or run out of guesses, ask if they would like to play again. If so, generate a new
// code and start again, otherwise exit the program.
//
// If the player enters a code that isn't valid, prompt them to try again but do NOT count the invalid guess as one of the 8 attempts. Also be sure that
// your game can handle any unexpected inputs without crashing.
//
// All your code should go in this file. Please do NOT include your name, as we anonymize tests during evaluation to reduce bias.
//
// Good luck!

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<time.h>
#include<cctype>

//prototypes
void generateCode(int[4]);
void playGame(int[4]);
void flushInput();
int compareCode(char[4], int[4], int, int);
void playAgain();


int main()
{
    //sets seed of rand to time so it's truly random
    srand((unsigned int)time(NULL));

    //create code array
    int code[4];

    //function to generate code
    generateCode(code);
    std::cout << "Code Generated\n";

    //play game
    playGame(code);
    
    return 0;
}

void generateCode(int code[4]) {

    //for loop to loop through numbers
    for (int i = 0; i < 4; i++) {

        //sets to random number 0 -9
        code[i] = (rand() % 10);

        //loop that checks digits leading up to current digit, if it is the same, call the function again to generate new numbers
        for (int j = 0; j < i; j++) {
            if ((code[j] == code[i]) && (i != j)) {
                generateCode(code);
            }
        }
    }
    return;
}

void playGame(int code[4]) {

    int guesses = 8;
    int count = 0;
    int correct = 0;
    int wrongSpot = 0;

    //while loop to keep track of number of guesses
    while (guesses > 0) {

        //display number of guesses and takes input
        //unsure of how to handle edge case of huge input, so I just made a large array, pretty inefficient but gets the job done
        char input[1000];
        printf("Guesses: %d\n", guesses);
        std::cout << "\nPlease enter a 4 digit code:\n";
        std::cin >> input;

        //loop through input, if one of the character is not a digit OR input is too small/ too big, it is invalid
        for (int i = 0; i < 4; i++) {
            if (isdigit(input[i]) == 0) {
                count = 1;
                //calls function to flush the input buffer in case of a mismatch failure
                flushInput();
                std::cout << "Error... Input Invalid\n";
                break;
            }
            if (strlen(input) != 4) {
                count = 1;
                //calls function to flush the input buffer in case of a mismatch failure
                flushInput();
                std::cout << "Error... Input Invalid\n";
                break;
            }
            else {
                count = 0;
            }
        }

        //if there was an invalid input, restart the loop without subtracting a guess
        if (count == 1)
            continue;

        //we have to -48 from each value to get the real value of the digit
        for (int i = 0; i < 4; i++) {
            input[i] = input[i] - 48;
        }

        //if the code entered matches, congratulate user and end program
        if (compareCode(input, code, correct, wrongSpot) == 1)
            exit;

        //subtract a guess
        guesses--;
    }

    //since we ran out of guesses and left the while loop, call playAgain function
    std::cout << "\nYou weren't able to crack the code, would you like to play again?\n";
    playAgain();

    return;
}

//flushes input buffer
void flushInput() {
    int c = getchar();

    while (c != '\n') {
        c = getchar();
    }
}


int compareCode(char input[4], int code[4], int correct, int wrongSpot) {

    //loops through input and code and increments when digits are correct, as well as when digits are correct in wrong spot
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            //if the digit is the same and in same spot, increment correct
            if ((input[j] == code[i]) && (i == j)) {
                correct++;
                break;
            }

            //if digit is same but in different spots, increment wrongSpot
            if (input[j] == code[i] && (i != j)) {
                wrongSpot++;
                break;
            }
        }
    }

    //if there were 4 correct digits, you won, return 1
    if (correct == 4) {
        printf("You cracked the code!");
        return 1;
    }
    //else give correct and wrong spots and return 0
    else {
        printf("\nCorrect Digits in Correct Spots: %d\nCorrect Digits in Wrong Spots: %d\n", correct, wrongSpot);
        return 0;
    }
}


void playAgain() {

    char input;
    std::cout << "Please Enter: Y or N\n";
    std::cin >> input;

    //if input is Y, create new code and play game again
    if (input == 'Y') {

        int code[4];
        generateCode(code);
        std::cout << "Code Generated\n";

        playGame(code);
    }
    //if input is N, thank user and return to end program
    else if (input == 'N') {

        std::cout << "\nThank you for playing!\n";
        return;
    }
    //else its a bad input, flush input in case of mismatch and call function again to get new input
    else {
        //calls function to flush the input buffer in case of a mismatch failure
        flushInput();
        std::cout << "Error... Input Invalid\n";
        playAgain();
    }

    return;
}
