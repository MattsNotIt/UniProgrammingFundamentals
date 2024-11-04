#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// List functions up here for use in main
void DisplayMenu();
void VisitLocation(string location);
void OpenShop();
void InitializeLocations();
void ListControls();
void DisplayLocations();
string GetRandomLocation();


vector<string> Locations;

// A map lets you assign something as a pair. In this case, an item with a pair of information. (I only learnt this from unreal engine)
map<string, string> ShopItems =
{
    {"Cypher Kit", "A kit to help you decrypt codes easier."},
    {"Binoculars", "Useful for spying on suspects from afar."}
};

int main() {
    srand(time(0)); // Create a seed for the game
    
    InitializeLocations();
    
    string command{};
    cout << "Welcome back, Detective. We have received a new case in your absence.\n";
    DisplayMenu();

    // The main game loop
    while (true) {
        cout << "\n> ";
        getline(cin, command);

        if (command == "shop" || command == "store")
        {
            OpenShop();
        }
        else if (find(Locations.begin(), Locations.end(), command) != Locations.end())
        {
            VisitLocation(command);
        }
        else if (command == "quit")
        {
            cout << "Goodbye, Detective.\n";
            break;
        }
        else if (command == "help")
        {
            ListControls();
        }
        else if (command == "list locations")
        {
            DisplayLocations();
        }
        else
        {
            cout << "Unknown command. Try again.\n";
        }
    }

    return 0;
}

// Start with the main menu
void DisplayMenu()
{
    cout << "Commands: type the name of a location to visit, 'shop' to open the store, or 'quit' to exit. Type 'help' for help\n";
    cout << "We have narrowed the relevant locations to these spots here: ";
    for (const auto& Location : Locations)
    {
        cout << Location << ", ";
    }
    cout << "\b\b \n"; // Remove the last comma and space
}

void DisplayLocations()
{
    for (const auto& Location : Locations)
    {
        cout << Location << ", ";
    }
    cout << "\b\b \n"; // Same as Display menu but less jargon
}

void ListControls()
{
    cout << "~~~Usable Commands~~~\n" << endl;
    cout << "   Look around\n";
    cout << "   Investigate [Thing]\n";
    cout << "   Shop or Store\n";
    cout << "   [Location]\n";
    cout << "   Quit\n";
}

// Arrived at the new location
void VisitLocation(string Location)
{
    cout << "You arrive at the " << Location << ". What do you want to do here?\n";
    // Lorem Ipsum (will be used for game logic in the map)
}

// Open up the shop to view items from the map data
void OpenShop()
{
    cout << "Welcome to the shop! Here are the available items:\n";
    for (const auto& item : ShopItems) {
        cout << "- " << item.first << ": " << item.second << "\n";
    }
    // Lorem Ipsum (Buying logic over here)
}

// locations, easily addable (is that even a word??)
void InitializeLocations()
{
    Locations = {"Kitchen", "Store", "Restaurant", "Park", "Mansion", "School", "Arcade"};
}

/*
 *
// Get a random location (spits out 50000 errors, sick)
string GetRandomLocation()
{
    int index = rand() % locations.size();
    return locations[index];
}
*/