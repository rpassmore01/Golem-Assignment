/*
    Name: Russell Passmore
    Class: ICS4U
    Assignment: Golem Assignment
    Date: October 2, 2022
*/

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
    node *newNode;
    newNode = new node;
    newNode->value = data;
    newNode->next = (*head);
    (*head) = newNode;
}

int main()
{
    srand(time(NULL));
    const int numLetters = 4;

    // Create regex for correct guesses
    stringstream ss;
    ss << "[AFWE]{" << numLetters << "}";
    const string letters = "FEAW";

    int guesses = 0;
    bool hint = false;

    char secretArray[numLetters];
    string secretString;

    // Linked list head node
    struct node *head = NULL;

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

    cout << "The Golems are starting to fight back after years of unfair working conditions.\nIt is up to you to neutralize the situation.\nYou can cast spells on the Golems using 4 elements: Fire, Water, Air and Earth.\nSpells must be cast in the following format: FEAW (Fire, Earth, Air and Water)\nYou can cast spells with the same element in it multiple times.\nAfter you cast a spell the Golem's eyes will glow red for every element that is in the correct place.\nThe Golem's eyes will glow blue for every correct letter, but in the wrong place.\nThese responses will look like this: RRBB\nYou will have only 10 attempts to neutralize the situation with the Golems.\nGood Luck!" << endl;

    string hintInput;
    const regex stringExp("[YN]{1}");

    while (!regex_match(hintInput, stringExp))
    {
        cout << "Would you like a hint? (y,n): ";
        cin >> hintInput;
        transform(hintInput.begin(), hintInput.end(), hintInput.begin(), ::toupper);
    }

    if (hintInput == "Y")
    {
        hint = true;
    }

    // Main game loops
    while (guesses < 10)
    {
        cout << "Guesses Left: " << 10 - guesses << endl;
        if(hint && guesses != 0) cout << "Hint: " << head->value << endl;
        else if(guesses == 0 && hint) cout << "Hint: FEAW" << endl;

        string inputSpell = "";
        char inputArray[numLetters];
        string hint;
        string plainHint;

        // Ask for input until it is correct
        const regex stringExp(ss.str());
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

        // Check for correct letters in correct location
        for (int i = 0; i < numLetters; i++)
        {
            if (inputArray[i] == secretArray[i])
            {
                hint += "\x1B[31;1mR\033[0m";
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
                    hint += "\x1B[34;1mB\033[0m";
                    plainHint += "B";
                    secretArray[j] = '$';
                    inputArray[i] = '$';
                }
            }
        }

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
            cout << hint << endl;
        }

        // Reset secret array
        for (int i = 0; i < numLetters; i++)
        {
            secretArray[i] = secretString[i];
        }

        // skim array and remove incorrect inputs
        node *temp = head;
        node *previous = head;
        while (temp != NULL)
        {
            string tempOutput;
            char tempSpell[numLetters];

            // Reset input array
            for (int i = 0; i < numLetters; i++)
            {
                inputArray[i] = inputSpell[i];
            }

            // Generate temporary spell array
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

            // Check if guess is a possible answer
            if (tempOutput != plainHint)
            {
                // If removing from the start of list
                if (temp == head)
                {
                    previous = temp;
                    head = head->next;
                    temp = head;
                    delete previous;
                    previous = head;
                }
                // If removing from end of list
                else if (temp->next == NULL)
                {
                    previous->next = NULL;
                    delete temp;
                    temp = previous->next;
                }
                // If removing from the middle of the list
                else
                {
                    previous->next = temp->next;
                    delete temp;
                    temp = previous->next;
                }
            }
            else
            {
                previous = temp;
                temp = temp->next;
            }
        }

        guesses++;
    }
}
