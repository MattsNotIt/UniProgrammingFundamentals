#include <iostream>
#include <string>

int main()
{
    using namespace std;
    
    string PlayerName{};
    string InGameName{};
    string ClanTag{};

    unsigned int Exp{0};

    cout << "Please Enter Your Name: ";
    cin >> PlayerName;

    cout << "Please Enter The Name Of Your Character: ";
    cin >> InGameName;

    cout << "Please Enter A Clan Tag: ";
    cin >> ClanTag;

    cout << "How Many Experience Points Do You Have: ";
    cin >> Exp;

    cout << "\nYour name is " << PlayerName << " and your in-game name is [" << ClanTag << "]" << InGameName << ".\n";
    cout << "You have " << Exp << " experience points.\n\n";  //Tidied Version of using Cout


    unsigned int CurLvl = Exp / 100; // Get Current Player lvl
    unsigned int NextLvl = CurLvl + 1; // Say Next lvl
    unsigned int NeededExp = (NextLvl * 100) - Exp; // Points For Next lvl


    cout << "Your current level is " << CurLvl << ".\n";
    cout << "You need " << NeededExp << " points to reach the next level, which is " << NextLvl << ".\n\n\n\n\n";

}