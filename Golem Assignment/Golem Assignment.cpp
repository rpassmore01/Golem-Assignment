// Golem Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>
#include <time.h>

using namespace std;

void generateSecretCode( char [] &secretArray, string &secretString) {

}

int main()
{
    cout << "The Golems are starting to fight back after years of unfair working conditions. It is up to you to neutralize the situation.\nYou can cast spells on the Golems using 4 elements: Fire, Water, Air and Earth.\nSpells must be cast in the following format: FEAW (Fire, Earth, Air and Water)\nYou can cast spells with the same element twice.\nAfter you cast a spell the Golem's eyes will glow red for every element that is in the correct place.\nThe Golem's eyes will glow blue for every correct letter that is in the wrong place.\nThese responses will look like this: RRBB\nYou will have only 10 attempts to neutralize the situation with the Golems.\nGood Luck!" << endl;
   
    const int numLetters = 4;

    int guesses = 0;
    regex stringExp("[AFWE]{4}");
    string letters = "FEAW";
    srand(time(NULL));

    char secretArray[numLetters];
    string secretString;

    for (int i = 0; i < 4; i++) {
        secretArray[i] = letters[rand()%numLetters];
    }

    for (int i = 0; i < numLetters; i++) {
        secretString = secretString + secretArray[i];
    }

    while (guesses < 10) {
        cout <<"Guesses Left: " << 10 - guesses << endl;
        string inputSpell = "";

        while (!regex_match(inputSpell, stringExp)) {
            string input;
            cout << "Enter a spell: ";
            cin >> inputSpell;
            transform(inputSpell.begin(), inputSpell.end(), inputSpell.begin(), ::toupper);
            if (!regex_match(inputSpell, stringExp)) {
                cout << "Please enter only 4 characters using any combination FEAW" << endl;
            }
        }

        string hintR;
        string hintB;

        for (int i = 0; i < numLetters; i++) {
            if (inputSpell[i] == secretString[i]) {
                hintR = hintR + "R";
            }
            else if (count(begin(secretArray), end(secretArray), inputSpell[i])) {
                hintB = hintB + "B";
            }
        }

        cout << hintR << hintB << endl;


        if (inputSpell == secretString) {
            cout << "Congrats, you beat the Golems!" << endl;
            break;
        }
        else if (guesses >= 9) {
            cout << "You lost, the Golems now rule the city and you are their slave. The secret code was: " << secretString << endl;
        }

        guesses++;
    }
}
