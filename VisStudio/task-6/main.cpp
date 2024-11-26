#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

int GenerateRandomNumber()
{
    return rand() % 101;
}

void PrintGuessFeedback(int difference)
{
    if (difference >= 50)
    {
        cout << "Freezing" << endl;
    }
    else if (difference >= 35)
    {
        cout << "Colder" << endl;
    }
    else if (difference >= 25)
    {
        cout << "Cold" << endl;
    }
    else if (difference >= 15)
    {
        cout << "Warm" << endl;
    }
    else if (difference >= 10)
    {
        cout << "Warmer" << endl;
    }
    else if (difference >= 5)
    {
        cout << "Hot" << endl;
    }
    else if (difference >= 3)
    {
        cout << "Hotter" << endl;
    }
    else if (difference >= 1)
    {
        cout << "Boiling" << endl;
    }
    else
    {
        cout << "Correct! The answer was " << difference << "!" << endl;
    }
}

bool IsValidGuess(int guess)
{
    // If guess was bigger or smaller than 0-100
    if (guess < 1 || guess > 100)
    {
        cerr << "Enter number between 1-100" << endl;
        return false;
    }
    return true;
}

int main()
{
    srand(time(0)); // Create a random seed for the random number
    int CorrectAnswer = GenerateRandomNumber();
    int guess;
    int guessCount = 0;

    cout << "Wow, fine, you wanna cheat, here is the answer ( for marking purposes ._. ): " << CorrectAnswer << endl;

    while (true)
    {
        cout << "Enter a guess: ";
        cin >> guess;

        // If answer includes letters
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Do not input letters.\nEnter number between 1-100" << endl;
            continue;
        }

        // Make sure guess is in between 0-100
        if (!IsValidGuess(guess))
        {
            continue;
        }

        // Add on the the guess count at the end
        guessCount++;

        int difference = abs(guess - CorrectAnswer);

        if (difference == 0)
        {
            cout << "Correct! The answer was " << CorrectAnswer << "!" << endl;
            cout << "Total number of guesses: " << guessCount << endl;
            break;
        }
        else
        {
            PrintGuessFeedback(difference);
        }
    }

    return 0;
}
