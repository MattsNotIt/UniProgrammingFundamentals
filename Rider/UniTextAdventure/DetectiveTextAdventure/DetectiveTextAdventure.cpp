#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Create Functions
void DisplayMenu();
void VisitLocation(string location);
void OpenShop();
void InitializeLocations();
int InitializeCodes();
void ListControls();
void DisplayLocations();
void LookAround();
void InterrogateStranger();
void HandleCommand(string command);
void ShowInventory();
void UseItem(string itemName);
string GetRandomPhrase();


vector<string> Locations;
map<string, string> PlayerInventory;
map<string, string> ShopItems =
{
    {"Cypher Kit", "A kit to help you decrypt codes easier."},
    {"Binoculars", "Useful for spying on suspects from afar."}
};

double InterrogationClueChance{50};

int RandomCode1{};
int RandomCode2{};
int RandomCode3{};
int playerMoney = 100; // Starting money for the player

int main()
{
    srand(time(0)); // Create a seed for the game

    // Initializations
    InitializeLocations();
    InitializeCodes();
    
    string command{};
    cout << "Welcome back, Detective. We have received a new case in your absence.\n";
    DisplayMenu();

    // The main game loop
    while (true)
    {
        cout << "\n> ";
        getline(cin, command);

        HandleCommand(command);
    }

    return 0;
}

// Function to handle player commands
void HandleCommand(string command)
{
    // Convert string to lowercase
    for (char &c : command) {
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
    }

    if (command == "shop" || command == "store") {
        OpenShop();
    } 
    else if (find(Locations.begin(), Locations.end(), command) != Locations.end()) {
        VisitLocation(command);
    } 
    else if (command == "look around") {
        LookAround();
    } 
    else if (command == "interrogate stranger") {
        InterrogateStranger();
    } 
    else if (command == "quit") {
        cout << "Goodbye, Detective.\n";
        return; // Indicate to exit the game loop
    } 
    else if (command == "help") {
        ListControls();
    } 
    else if (command == "list locations") {
        DisplayLocations();
    } 
    else if (command == "show inventory") {
        ShowInventory();
    }
    else if (command.find("use ") == 0) {
        UseItem(command.substr(4)); // Extract the item name after "use "
    }
    else {
        cout << "Unknown command. Try again.\n";
    }

    return; // Continue the game loop
}

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
    cout << "\b\b \n"; // Same as DisplayMenu but less jargon
}

void ListControls()
{
    cout << "~~~Usable Commands~~~\n" << endl;
    cout << "   Look around\n";
    cout << "   Interrogate Stranger\n";
    cout << "   Shop or Store\n";
    cout << "   [Location]\n";
    cout << "   Show Inventory\n";
    cout << "   Use [itemname]\n";
    cout << "   Quit\n";
}

void VisitLocation(string Location)
{
    cout << "You arrive at the " << Location << ". What do you want to do here?\n";
}

string GetUsefulPhrase()
{
    vector<string> InterrogatedPhrases =
    {
        "The suspect seemed nervous.",
        "You notice a slight hesitation in their voice.",
        "Their tone suggests they are hiding something.",
        "They mention a shadowy figure they saw earlier.",
        "You catch a clue from an offhand remark.",
        "The stranger talks about a strange noise they heard.",
        "A bead of sweat forms on their forehead.",
        "They stammer while recalling the events of last night.",
        "The person gives a description of an unknown individual."
    };
    
    // Return a random phrase
    return InterrogatedPhrases[rand() % InterrogatedPhrases.size()];
}

string GetUselessPhrase()
{
    vector<string> InterrogatedPhrases =
    {
        "The stranger shrugs you off and walks away.",
        "The stranger said they have no idea.",
        "The stranger doesn't speak your language",
        "You mess up your wording",
        "The stranger glances around, avoiding eye contact.",
        "They turned the corner before you spoke",
        "You decided that this person wont be of help",
        "They whisper something barely audible.",
        "They offer an alibi that doesn't quite add up.",
        "The person looks confused and denies everything.",
        "The individual gives you an irrelevant but curious fact.",
    };
    
    // Return a random phrase
    return InterrogatedPhrases[rand() % InterrogatedPhrases.size()];
}

// Double fix for the case sensitive command stuff
bool CaseInsensitiveCompare(const string& str1, const string& str2)
{
    if (str1.size() != str2.size()) return false;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i])) return false;
    }
    return true;
}

void OpenShop()
{
    cout << "Welcome to the shop! Here are the available items:\n";
    for (const auto& item : ShopItems)
    {
        cout << "- " << item.first << ": " << item.second << "\n";
    }

    string purchase;
    cout << "Enter the name of the item you wish to buy or type 'exit' to leave the shop:\n> ";
    getline(cin, purchase);

    bool itemFound = false;
    for (const auto& item : ShopItems)
    {
        if (CaseInsensitiveCompare(purchase, item.first))
        {
            cout << "You have purchased: " << item.first << ".\n";
            PlayerInventory[item.first] = item.second;
            itemFound = true;
            break;
        }
    }

    if (!itemFound && purchase != "exit")
    {
        cout << "Invalid item. Try again or type 'exit' to leave.\n";
    }
}

void ShowInventory()
{
    cout << "Your Inventory:\n";
    if (PlayerInventory.empty())
    {
        cout << "You have no items.\n";
    }
    else
    {
        for (const auto& item : PlayerInventory)
        {
            cout << "- " << item.first << ": " << item.second << "\n";
        }
    }
}

void UseItem(string itemName)
{
    bool itemFound = false;
    for (const auto& item : PlayerInventory)
    {
        if (CaseInsensitiveCompare(itemName, item.first))
        {
            cout << "You use the " << item.first << ".\n";
            // Add logic for what happens when the item is used
            PlayerInventory.erase(item.first); // Remove the item after use
            itemFound = true;
            break;
        }
    }
    if (!itemFound) {
        cout << "You don't have " << itemName << " in your inventory.\n";
    }
}


void LookAround()
{
    cout << "You carefully look around your surroundings, observing every detail for clues.\n";

    // Random true or false
    bool RandomValue = RAND_MAX / 2;

    if (RandomValue)
    {
        cout << "Found something";
    }
    else
    {
        cout << "Found Nothing";
    }
}

void InterrogateStranger()
{
    cout << "You approach a nearby stranger and start to question them about recent events.\n";

    // Generate a random double between 0 and 1
    double RandomValue = static_cast<double>(rand()) / RAND_MAX;

    // Generate a random boolean value
    bool IsUsefulPhrase = rand() % 2;

    // Use the correct variable name and logic
    if (RandomValue < InterrogationClueChance / 100.0)  // Convert percentage to probability
    {
        if (IsUsefulPhrase)
        {
            cout << GetUsefulPhrase() << "\n";
            InterrogationClueChance /= 1.75; // Reduce the chance for the next interrogation
        }
        else
        {
            cout << GetUselessPhrase() << "\n";
            InterrogationClueChance /= 1.25; // Reduce the chance for the next interrogation
        }
    }
    else
    {
        cout << "The stranger doesn't have any useful information.\n";
    }

    // Output the current interrogation clue chance for debugging
    cout << "Interrogation clue chance: " << InterrogationClueChance << "%\n";
}


void InitializeLocations()
{
    Locations = {"kitchen", "store", "restaurant", "park", "mansion", "school", "arcade"};
}

int InitializeCodes()
{
    RandomCode1 = (rand() % 1000) + 99001;
    RandomCode2 = (rand() % 1000) + 5345;
    RandomCode3 = (rand() % 1000) + 29573;
    
    cout << RandomCode1 << "\n" << RandomCode2 << "\n" << RandomCode3 << "\n";
    return RandomCode1;
}