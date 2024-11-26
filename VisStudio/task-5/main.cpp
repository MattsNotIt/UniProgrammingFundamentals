#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

void ToLowerCase(string& input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);
}

void ToUpperCase(string& input)
{
    transform(input.begin(), input.end(), input.begin(), ::toupper);
}

void ToSentenceCase(string& input)
{
    bool NewSentence = true;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (NewSentence && isalpha(input[i]))
        {
            input[i] = toupper(input[i]);
            NewSentence = false;
        }
        else if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            NewSentence = true;
        }
        else
        {
            input[i] = tolower(input[i]);
        }
    }
}

void ToAlternatingCase(string& input)
{
    bool uppercase = false;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (isalpha(input[i]))
        {
            input[i] = uppercase ? toupper(input[i]) : tolower(input[i]);
            uppercase = !uppercase;
        }
    }
}

bool HasAlphabets(const string& input)
{
    for (char ch : input)
    {
        if (isalpha(ch))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string input;

    cout << "Enter the string: ";
    getline(cin, input);

    if (!HasAlphabets(input))
    {
        cout << "Warning: The text has no alphabetical characters.\n";
        exit(0);
    }

    string original = input; // store the original string for reference

    // Convert to lowercase
    string LowerCaseInput = original;
    ToLowerCase(LowerCaseInput);
    cout << "Lowercase: " << LowerCaseInput << endl;

    // Convert to uppercase
    string UpperCaseInput = original;
    ToUpperCase(UpperCaseInput);
    cout << "Uppercase: " << UpperCaseInput << endl;

    // Convert to sentence case
    string SentenceCaseInput = original;
    ToSentenceCase(SentenceCaseInput);
    cout << "Sentence case: " << SentenceCaseInput << endl;

    // Convert to alternating case
    string AlternatingCaseInput = original;
    ToAlternatingCase(AlternatingCaseInput);
    cout << "Alternating case: " << AlternatingCaseInput << endl;

    return 0;
}
