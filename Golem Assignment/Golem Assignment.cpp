// Golem Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>
#include <time.h>

using namespace std;

int main()
{
    // cout << "The Golems are starting to fight back after years of unfair working conditions. It is up to you to neutralize the situation.\nYou can cast spells on the Golems using 4 elements: Fire, Water, Air and Earth.\nSpells must be cast in the following format: FEAW (Fire, Earth, Air and Water)\nYou can cast spells with the same element twice.\nAfter you cast a spell the Golem's eyes will glow red for every element that is in the correct place.\nThe Golem's eyes will glow blue for every correct letter that is in the wrong place.\nThese responses will look like this: RRBB\nYou will have only 10 attempts to neutralize the situation with the Golems.\nGood Luck!" << endl;
    srand(time(NULL));

    const int numLetters = 4;
    stringstream ss;
    ss << "[AFWE]{" << numLetters << "}";
    const regex stringExp(ss.str());
    const string letters = "FEAW";

    int guesses = 0;

    char secretArray[numLetters];
    string secretString;

    // Generate secret array and string
    for (int i = 0; i < numLetters; i++)
    {
        char letter = letters[rand() % numLetters];
        secretArray[i] = letter;
        secretString = secretString + letter;
    }

    cout << secretString << endl;

    // Main game loop
    while (guesses < 10)
    {
        cout << "Guesses Left: " << 10 - guesses << endl;
        string inputSpell = "";
        char inputArray[numLetters];

        // Ask for input until it matches the REGEX
        while (!regex_match(inputSpell, stringExp))
        {
            string input;
            cout << "Enter a spell: ";
            cin >> inputSpell;

            // Make input string all caps
            transform(inputSpell.begin(), inputSpell.end(), inputSpell.begin(), ::toupper);
            if (!regex_match(inputSpell, stringExp))
            {
                cout << "Please enter " << numLetters << " characters using any combination FEAW" << endl;
            }
        }

        //Generate input array from string
        for(int i = 0; i < numLetters; i++){
            inputArray[i] = inputSpell[i];
        }

        string hintR;
        string hintB;

        // Check for correct letters in correct location
        for (int i = 0; i < numLetters; i++)
        {
            if (inputArray[i] == secretArray[i])
            {
                hintR = hintR + "\x1B[31;1mR\033[0m";
                secretArray[i] = '$';
            }
        }

        // Check for correct letters in incorrect location
        for(int i = 0; i < numLetters; i++){
            for(int j = 0; j < numLetters; j++){
                cout << inputArray[i] << secretArray[j] << endl;
                if(inputArray[i] == secretArray[j]){
                    hintB = hintB + "\x1B[33;1mB\033[0m";
                    secretArray[j] = '$';
                }
            }
        }

        if (inputSpell == secretString)
        {
            cout << "You beat the Golems" << endl;
            break;
        }
        else
        {
            cout << hintR << hintB << endl;
        }

        //"\033[1;34mB\033[0m" for colored letter

        guesses++;
    }
}
