#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Create Functions
void DisplayMenu();
void VisitLocation(string location);
void OpenShop();
void InitializeLocations();
void ListControls();
void DisplayLocations();
void LookAround();
void InterrogateStranger();
void HandleCommand(string command);
void ShowInventory();
void UseItem(string itemName);
void DisplaySuspects();
void DisplayEvidence();
void EnterCaseSolvingMode();
void AccuseSuspect(string suspectName);
void CollectEvidence(string evidence);

//Functions to display random events
string GetUsefulPhrase();
string GetUselessPhrase();
string PositiveRandomLookEvent();
string NeutralRandomLookEvent();
string NegativeRandomLookEvent();

struct ShopItem
{
    string Description;
    int Price;
};

struct Suspect
{
    string FirstName;
    string LastName;
    string FoundLocation;
    bool IsMurderer;
    vector<string> EvidenceAgainst;
};

// Useful Variables
vector<string> Locations;

string CurrentPlayerLocation;

vector<Suspect> Suspects;
vector<string> FirstNames = {"Matt", "Paul", "Matthew", "Jason", "Emma", "Will", "William", "George", "Shane", "Quinn", "Micheal"};
vector<string> LastNames = {"Smith", "Hayward", "Wills", "Hancock", "Manley", "Dawson", "Potter", "Fischbach"};

map<string, ShopItem> ShopItems = 
{
    {"Cypher Kit", {"A kit to help you decrypt codes easier.", 25}},
    {"Binoculars", {"Useful for spying on suspects from afar.", 25}}
};

map<string, string> PlayerInventory;
int PlayerMoney = 100; // Starting money for the player
double InterrogationClueChance = 50.0;

int RandomCode1{};
int RandomCode2{};
int RandomCode3{};

bool IsAtSafe = false;
bool IsCaseSolvingMode = false;

string MurdererFullName;

int main()
{
    srand(time(0)); // Create a seed for the game

    // Initializations
    InitializeLocations();

    // Set the crime boy at the start
    Suspect Murderer;
    Murderer.FirstName = FirstNames[rand() % FirstNames.size()];
    Murderer.LastName = LastNames[rand() % LastNames.size()];
    Murderer.IsMurderer = true;
    Murderer.FoundLocation = Locations[rand() % Locations.size()];
    
    // Store the crime boys full name
    MurdererFullName = Murderer.FirstName + " " + Murderer.LastName;
    
    // Add the crime boy to the list
    Suspects.push_back(Murderer);
    
    string command{};
    cout << "Welcome back, Detective. We have received a new case in your absence.\n\n";
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
    if (IsCaseSolvingMode)
    {
        
    }
    else
    {
        // Convert string to lowercase
        for (char &c : command) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }
    }

    // Special handling for case solving mode
    if (IsCaseSolvingMode)
    {
        if (command == "cancel")
        {
            cout << "Case solving mode cancelled.\n";
            IsCaseSolvingMode = false;
            return;
        }
        
        // Allow accusation by full name
        AccuseSuspect(command);
        return;
    }

    // Existing command handling
    if (command == "solve case")
    {
        EnterCaseSolvingMode();
    }
    else if (command == "show evidence")
    {
        DisplayEvidence();
    }
    else if (command == "shop" || command == "store")
    {
        OpenShop();
    } 
    else if (find(Locations.begin(), Locations.end(), command) != Locations.end())
    {
        VisitLocation(command);
    } 
    else if (command == "look around")
    {
        LookAround();
    } 
    else if (command == "interrogate stranger")
    {
        InterrogateStranger();
    } 
    else if (command == "quit")
    {
        cout << "Goodbye, Detective.\n";
        exit(0);
    } 
    else if (command == "help")
    {
        ListControls();
    } 
    else if (command == "list locations")
    {
        DisplayLocations();
    } 
    else if (command == "show inventory")
    {
        ShowInventory();
    }
    else if (command.find("use ") == 0)
    {
        UseItem(command.substr(4));
    }
    else if (command == "suspects")
    {
        DisplaySuspects();
    }
    else
    {
        cout << "Unknown command. Try again.\n";
    }

    return;
}

void DisplayMenu()
{
    cout << "Commands: type the name of a location to visit, 'shop' to open the store, or 'quit' to exit. Type 'help' for help\n\n";
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
    cout << "   Show Evidence\n";
    cout << "   Suspects\n";
    cout << "   Solve Case\n";
    cout << "   Quit\n";
}

void VisitLocation(string location)
{
    cout << "You arrive at the " << location << ".\n";

    CurrentPlayerLocation = location;
    
    // Decide on a random event type: positive, neutral, or negative
    int eventType = rand() % 3;
    string eventMessage;
    
    switch (eventType)
    {
        case 0:  // Positive Event
            eventMessage = PositiveRandomLookEvent();
            cout << eventMessage;
            
            if (eventMessage.find("extra money") != string::npos)
            {
                int moneyFound = rand() % 20 + 10; // Random amount between 10 and 30
                PlayerMoney += moneyFound;
                cout << "You found " << moneyFound << " coins! Your new balance: " << PlayerMoney << "\n";
            }
            else if (eventMessage.find("reward") != string::npos)
            {
                int reward = rand() % 50 + 25; // Random reward between 25 and 75
                PlayerMoney += reward;
                cout << "You received a reward of " << reward << "! Your new balance: " << PlayerMoney << "\n";
            }
            break;
            
        case 1:  // Neutral Event
            eventMessage = NeutralRandomLookEvent();
            cout << eventMessage;
            // No effect on player stats or inventory for neutral events
            break;
            
        case 2:  // Negative Event
            eventMessage = NegativeRandomLookEvent();
            cout << eventMessage;
            
            if (eventMessage.find("picked pocketed") != string::npos)
            {
                int moneyLost = rand() % 15 + 5; // Random amount between 5 and 20
                if (PlayerMoney >= moneyLost)
                {
                    PlayerMoney -= moneyLost;
                    cout << "You lost " << moneyLost << " coins. Your new balance: " << PlayerMoney << "\n";
                }
                else
                {
                    cout << "Luckily, you didn't have any money to lose.\n";
                }
            }
            else if (eventMessage.find("forgot to bring something") != string::npos)
            {
                // Add additional effect if needed, such as modifying player status
            }
            break;
    }
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
        cout << "- " << item.first << ": " << item.second.Description << " (Price: " << item.second.Price << ")\n";
    }

    string purchase;
    cout << "Enter the name of the item you wish to buy or type 'exit' to leave the shop:\n> ";
    getline(cin, purchase);

    bool itemFound = false;
    for (const auto& item : ShopItems)
    {
        if (CaseInsensitiveCompare(purchase, item.first))
        {
            if (PlayerMoney >= item.second.Price)
            {
                PlayerInventory[item.first] = item.second.Description;
                PlayerMoney -= item.second.Price;
                cout << "You have purchased: " << item.first << ". Remaining Money: " << PlayerMoney << "\n";
            }
            else
            {
                cout << "You don't have enough money to buy " << item.first << ".\n";
            }
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
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (PlayerInventory.empty() & PlayerMoney > 0())
    {
        cout << "You have no items except for " << PlayerMoney << ".";
    }
    else if (PlayerInventory.empty() && PlayerMoney < 1)
    {
        cout << "You have no items.\n";
    }
    else if (PlayerInventory.size() > 0)
    {
        for (const auto& item : PlayerInventory)
        {
            cout << "You have, " << PlayerMoney << "\n";
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
            itemFound = true;

            // Cypher Kit functionality (only works at a safe)
            if (itemName == "cypher kit")
            {
                if (IsAtSafe)
                {
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    cout << "You use the Cypher Kit to decrypt a hidden message!\n";

                    // Example: Revealing a random code or clue
                    int revealedCode = rand() % 900 + 100; // Random 3-digit code
                    cout << "You successfully decrypt the code: " << revealedCode << "\n";
                    cout << "The safe unlocks with a satisfying click. Time to check inside!\n";

                    // Optionally, remove the Cypher Kit after use
                    PlayerInventory.erase(item.first);
                }
                else
                {
                    cout << "You can't use the Cypher Kit right now. There's no safe nearby to decrypt.\n";
                }
            }

            // Binoculars functionality (random location spotting)
            else if (itemName == "binoculars")
            {
                this_thread::sleep_for(chrono::milliseconds(1000));
                cout << "You use the Binoculars to scout the area from afar.\n";

                // Randomly select a location from the list
                srand(time(nullptr)); // Seed for randomness
                string location = Locations[rand() % Locations.size()];

                cout << "You spot someone suspicious in the distance. They seem to be heading to the " << location << ".\n";

                // Optionally, remove the Binoculars after use
                PlayerInventory.erase(item.first);
            }

            else
            {
                cout << "You use the " << item.first << ".\n";
            }

            break; // Exit the loop once the item is found and used
        }
    }

    if (!itemFound)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "You don't have " << itemName << " in your inventory.\n";
    }
}


string PositiveRandomLookEvent()
{
    vector<string> PositiveRandomisedLookEvent =
    {
        "You found a blood-stained handkerchief on the ground.\n",
        "Somebody recognised you as the detective and shared a crucial witness statement.\n",
        "You discovered a hidden note with a suspicious message.\n",
    };
    
    string selectedEvent = PositiveRandomisedLookEvent[rand() % PositiveRandomisedLookEvent.size()];
    
    // Randomly decide to collect evidence
    if (rand() % 2 == 0)
    {
        CollectEvidence(selectedEvent.substr(0, selectedEvent.length() - 1));
    }
    
    return selectedEvent;
}

string NeutralRandomLookEvent()
{
    vector<string> NeutralRandomisedLookEvent =
    {
        "You managed to reach your destination.\n",
        "You had a nice chat with somebody waiting at the bus stop.\n",
        "You watched everybody walking around town while walking to your destination.\n",
    };
    
    // Return a random phrase
    return NeutralRandomisedLookEvent[rand() % NeutralRandomisedLookEvent.size()];
}

string NegativeRandomLookEvent()
{
    vector<string> NegativeRandomisedLookEvent =
    {
        "You found a mysterious torn piece of clothing.\n",
        "You overheard a suspicious conversation fragment.\n",
        "You noticed a strange footprint near the crime scene.\n",
    };
    
    // Return a random phrase and potentially collect evidence
    string selectedEvent = NegativeRandomisedLookEvent[rand() % NegativeRandomisedLookEvent.size()];
    
    // Randomly decide to collect evidence
    if (rand() % 2 == 0)
    {
        CollectEvidence(selectedEvent.substr(0, selectedEvent.length() - 1));
    }
    
    return selectedEvent;
}

void LookAround()
{
    cout << "You carefully look around your surroundings, observing every detail for clues.\n";
    
    bool foundSomething = rand() % 2;
    
    if (foundSomething)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1500));
        cout << "You spot something interesting nearby.\n";
        cout << PositiveRandomLookEvent(); // Adds a random positive event
    }
    else
    {
        this_thread::sleep_for(std::chrono::milliseconds(1500));
        cout << "You don't notice anything unusual here.\n";
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
            this_thread::sleep_for(std::chrono::milliseconds(1500));
            string usefulPhrase = GetUsefulPhrase();
            cout << usefulPhrase << "\n";
            
            // Randomly decide to collect evidence
            if (rand() % 2 == 0)
            {
                CollectEvidence(usefulPhrase);
            }
            
            InterrogationClueChance /= 1.75; // Reduce the chance for the next interrogation
        }
        else
        {
            this_thread::sleep_for(std::chrono::milliseconds(1500));
            cout << GetUselessPhrase() << "\n";
            InterrogationClueChance /= 1.25; // Reduce the chance for the next interrogation
        }
    }
    else
    {
        this_thread::sleep_for(std::chrono::milliseconds(1500));
        cout << "The stranger doesn't have any useful information.\n";
    }

    cout << "Do you want to add this person to your list of suspects? (yes/no): ";
    string response;
    getline(cin, response);

    if (response == "yes")
    {
        // Generate a random suspect
        Suspect NewSuspect;
        NewSuspect.FirstName = FirstNames[rand() % FirstNames.size()];
        NewSuspect.LastName = LastNames[rand() % LastNames.size()];
        NewSuspect.FoundLocation = CurrentPlayerLocation;
        NewSuspect.IsMurderer = false;  // Not the actual murderer

        // Add to suspect list
        Suspects.push_back(NewSuspect);
        cout << "Added " << NewSuspect.FirstName << " " << NewSuspect.LastName << " to your list of suspects.\n";
    }
    else
    {
        cout << "You decide not to add this stranger to your list of suspects.\n";
    }
}

void DisplaySuspects()
{
    if (Suspects.empty())
    {
        cout << "You currently have no suspects.\n";
        return;
    }

    cout << "List of Suspects:\n";
    for (size_t i = 0; i < Suspects.size(); ++i)
    {
        cout << i + 1 << ". " << Suspects[i].FirstName << " " << Suspects[i].LastName << " - Found at: " << Suspects[i].FoundLocation << "\n";
    }
}

void InitializeLocations()
{
    Locations = {"kitchen", "restaurant", "park", "mansion", "school", "arcade", "staffs uni"};
}

void CollectEvidence(string evidence)
{
    // Find the murderer in the suspects list
    for (auto& suspect : Suspects)
    {
        if (suspect.IsMurderer)
        {
            suspect.EvidenceAgainst.push_back(evidence);
            cout << "Evidence collected: " << evidence << "\n";
            return;
        }
    }
}

void DisplayEvidence()
{
    for (const auto& suspect : Suspects)
    {
        if (suspect.IsMurderer)
        {
            if (suspect.EvidenceAgainst.empty())
            {
                cout << "No evidence collected yet.\n";
            }
            else
            {
                cout << "Evidence against the suspect:\n";
                for (const auto& evidence : suspect.EvidenceAgainst)
                {
                    cout << "- " << evidence << "\n";
                }
            }
            return;
        }
    }
}



void EnterCaseSolvingMode()
{
    if (Suspects.empty())
    {
        cout << "You haven't identified any suspects yet. Continue investigating.\n";
        return;
    }

    IsCaseSolvingMode = true;
    cout << "\n===== CASE SOLVING MODE =====\n";
    cout << "You're ready to accuse a suspect. Choose carefully...\n";
    DisplaySuspects();
    cout << "\nEnter the FULL NAME of the suspect you want to accuse (or 'cancel' to exit):\n> ";
}

// Function to handle the final accusation
void AccuseSuspect(string suspectName)
{
    bool suspectFound = false;
    Suspect AccusedSuspect;

    // Find the accused suspect
    for (const auto& suspect : Suspects)
    {
        string fullName = suspect.FirstName + " " + suspect.LastName;
        if (suspectName == fullName)
        {
            suspectFound = true;
            AccusedSuspect = suspect;
            break;
        }
    }

    if (!suspectFound)
    {
        cout << "No suspect found with that name. Accusation cancelled.\n";
        IsCaseSolvingMode = false;
        return;
    }

    // Check if the evidence is sufficient
    if (AccusedSuspect.IsMurderer && AccusedSuspect.EvidenceAgainst.size() >= 3)
    {
        cout << "\n===== CASE SOLVED! =====\n";
        cout << "Congratulations, Detective! " << suspectName 
             << " was indeed the culprit!\n";
        cout << "You successfully solved the case and brought justice to the town.\n";
        exit(0);  // End the game with a win
    }
    else if (AccusedSuspect.IsMurderer)
    {
        cout << "You've identified the correct suspect, but you don't have enough evidence yet.\n";
        cout << "Collect at least 3 pieces of evidence before making your final accusation.\n";
    }
    else
    {
        cout << "\n===== CASE FAILED =====\n";
        cout << "Oh no! " << suspectName 
             << " was innocent.\n";
        cout << "You've been fired from the detective agency for falsely accusing a civilian.\n";
        exit(0);  // End the game with a loss
    }

    IsCaseSolvingMode = false;
}
