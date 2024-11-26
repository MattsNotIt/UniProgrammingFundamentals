#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Item
{
    string name;
    string type;
    int price;
    int damage;
    string role;
    bool isPurchased;
};

struct Player
{
    string name;
    string role;
    string weapon;
    int damage;
    int coins;
};

void printItems(const vector<Item>& items)
{
    cout << "You currently have coins. You can buy the following items:\n";
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (!items[i].isPurchased)
        {
            cout << i + 1 << ". " << items[i].name << " [" << items[i].price << " coins, " << items[i].damage << " damage]\n";
        }
    }
}

bool validInput(int choice, const vector<Item>& items)
{
    return choice >= 1 && choice <= items.size() && !items[choice - 1].isPurchased;
}

void purchaseItem(Player& player, vector<Item>& items, int itemIndex)
{
    if (player.coins >= items[itemIndex].price)
    {
        player.coins -= items[itemIndex].price;
        player.weapon = items[itemIndex].name;
        player.damage = items[itemIndex].damage;
        items[itemIndex].isPurchased = true;
        cout << player.name << " bought a " << items[itemIndex].name << " for " << items[itemIndex].price << " coins.\n";
        cout << "The party now has " << player.coins << " coins.\n";
    }
    else
    {
        cout << "[ ! ] ERROR: Not enough coins, the " << items[itemIndex].name << " is " << items[itemIndex].price
            << " coins and there are only " << player.coins << " available for use!\n";
    }
}

int main()
{
    vector<Item> items = {
        {"Great Sword", "Sword", 40, 100, "Knight", false},
        {"Scimitar", "Sword", 35, 75, "Knight", false},
        {"Dagger", "Sword", 10, 35, "Knight", false},
        {"Longbow", "Bow", 20, 55, "Archer", false},
        {"Crossbow", "Bow", 40, 100, "Archer", false},
        {"Rusty spear", "Spear", 10, 35, "Spearman", false},
        {"Iron spear", "Spear", 20, 65, "Spearman", false}
    };

    Player players[3];
    int numPlayers = 3;

    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player " << i + 1 << "'s name: ";
        getline(cin, players[i].name);
        players[i].coins = 100;
        players[i].role = (i == 0) ? "Knight" : (i == 1) ? "Archer" : "Spearman";
    }

    cout << ">> Welcome ";
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << players[i].name;
        if (i < numPlayers - 1)
            cout << ", ";
    }
    cout << " to the shop!\n";

    bool gameStarted = false;
    while (!gameStarted)
    {
        for (int i = 0; i < numPlayers; ++i)
        {
            printItems(items);

            int choice;
            bool valid = false;
            while (!valid)
            {
                cout << "Player " << i + 1 << ", please enter a weapon to buy: ";
                cin >> choice;

                if (cin.fail() || !validInput(choice, items))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[ ! ] ERROR: Please choose a valid item number.\n";
                }
                else
                {
                    valid = true;
                }
            }

            purchaseItem(players[i], items, choice - 1);
        }

        string response;
        cout << ">> Are you happy with your selection of weapons? (yes/no): ";
        cin >> response;
        if (response == "yes")
        {
            gameStarted = true;
        }
        else
        {
            // Reset items for next selection if no
            for (size_t i = 0; i < items.size(); ++i)
            {
                items[i].isPurchased = false;
            }
        }
    }

    cout << ">> The party:\n";
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Player " << i + 1 << " (" << players[i].name << "), Role: " << players[i].role
            << ", Weapon: " << players[i].weapon << ", Damage: " << players[i].damage << ".\n";
    }

    return 0;
}
