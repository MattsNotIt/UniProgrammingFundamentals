#include <iostream>
#include <cmath>

int main(int argc, char* argv[])
{
    using namespace std;

    //Variables
    double number{};

    //Enter Inputs
    cout << "Enter A Number: ";
    cin >> number;

    if (!(cin >> number))
    {
        cerr << "[!] ERROR: I was expecting a number, not a string. Exiting." << endl;
        return 1; // End Program
    }

    //Print Results
    cout << "Negation: " << -number << endl;
    cout << "Absolute value: " << fabs(number) << endl;
    cout << "Squared: " << pow(number, 2) << endl;
    cout << "Cubed: " << pow(number, 3) << endl;
    cout << "Square root: " << sqrt(number) << endl;
    cout << "Floor: " << floor(number) << endl;
    cout << "Ceil: " << ceil(number) << endl;
    cout << "Rounded: " << round(number) << endl;

    return 0;
}