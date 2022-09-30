// Golem Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;

// Linked list node
struct node
{
    string value;
    node *next;
};

// Insert node to the front of the linked list
void insert(string data, node **head)
{
    struct node *newNode;
    newNode = new node;
    newNode->value = data;
    newNode->next = (*head);
    (*head) = newNode;
}

void skimList(node **head, int numLetters, string secretString, string ouput)
{
}

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

    // Linked list head node
    struct node *head;

    // Populate linked list with all possible inputs
    int i = 0;
    while (i < pow(numLetters, 4))
    {
        int numPossibilities = pow(numLetters, 4);
        string output;
        output += letters[floor(i / (numPossibilities / 4))];
        output += letters[floor((i / (numPossibilities / 16)) % 4)];
        output += letters[floor((i / (numPossibilities / 64)) % 4)];
        output += letters[i % 4];

        insert(output, &head);

        i++;
    }

    // Generate secret array and string
    for (int i = 0; i < numLetters; i++)
    {
        char letter = letters[rand() % 4];
        secretArray[i] = letter;
        secretString = secretString + letter;
    }

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

        // Generate input array from string
        for (int i = 0; i < numLetters; i++)
        {
            inputArray[i] = inputSpell[i];
        }

        string hintR;
        string hintB;
        string plainHint;

        // Check for correct letters in correct location
        for (int i = 0; i < numLetters; i++)
        {
            if (inputArray[i] == secretArray[i])
            {
                hintR += "\x1B[31;1mR\033[0m";
                plainHint += "R";
                secretArray[i] = '$';
                inputArray[i] = '$';
            }
        }

        // Check for correct letters in incorrect location
        for (int i = 0; i < numLetters; i++)
        {
            for (int j = 0; j < numLetters; j++)
            {
                if (inputArray[i] == secretArray[j] && inputArray[i] != '$')
                {
                    hintB += "\x1B[34;1mB\033[0m";
                    plainHint += "B";
                    secretArray[j] = '$';
                    inputArray[i] = '$';
                }
            }
        }

        // skim array and remove incorrect inputs
        node *temp = head;
        node *prev = head;
        while (temp != NULL)
        {
            string tempOutput;
            char tempSpell[numLetters];

            // Reset input array
            for (int i = 0; i < numLetters; i++)
            {
                inputArray[i] = inputSpell[i];
            }

            //Generate temporary spell array
            for (int i = 0; i < numLetters; i++)
            {
                tempSpell[i] = temp->value[i];
            }

            // Check for correct letters in correct location
            for (int i = 0; i < numLetters; i++)
            {
                if (inputArray[i] == tempSpell[i])
                {
                    tempOutput += "R";
                    inputArray[i] = '$';
                    tempSpell[i] = '$';
                }
            }

            // Check for correct letters in incorrect location
            for (int i = 0; i < numLetters; i++)
            {
                for (int j = 0; j < numLetters; j++)
                {
                    if (inputArray[i] == tempSpell[j] && inputArray[i] != '$')
                    {
                        tempOutput += "B";
                        tempSpell[j] = '$';
                        inputArray[i] = '$';
                    }
                }
            }

            if(tempOutput == plainHint){
                cout << "possible answer ->" << endl;
                //prev->next = temp->next;
            }

            cout << temp->value << "\t" << tempOutput << "\t" << plainHint << endl;

            /*prev = temp;
            if(prev == NULL) break;*/
                temp = temp->next;
        }

        cout << "got here" << endl;

        if (inputSpell == secretString)
        {
            cout << "You beat the Golems" << endl;
            break;
        }
        else if (guesses == 9)
        {
            cout << "You lost. The secret code was: " << secretString << endl;
        }
        else
        {
            cout << hintR << hintB << endl;
        }

        guesses++;
    }
}
