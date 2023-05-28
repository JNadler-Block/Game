#include "Shop.h"

int SpellShardCost = 1000;

using namespace std;

int Shop::ScanForInt() {
    int i;
    while (true) {
        cin >> i;
        if (!cin)
        {
            cout << "\nPlease enter the amount." << endl;
            cout << "Enter \"0\" to cancel.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
    }
    return i;
}

static void ShopIntro(Character c, Potion p, AncientSpirit a) {
	cout << "\nWelcome to the shop." << endl;
	cout << "You have " << c.SeeGold() << " gold" << endl;
	cout << "Today what we have in stock is: " << endl;
	cout << "Health Potions:\t\t" << p.SeePotionCost() << " gold each" << endl;
	cout << "Ancient Spirits:\t" << a.SeeCost() << " gold each" << endl;
    if (c.SeeBossKills() > 0)
        cout << "Spell Shards:\t\t" << SpellShardCost << " gold for 1-1000" << endl;
	cout << "\nTo buy an item, enter \"b\"" << endl;
	cout << "To sell an item, enter \"s\"" << endl;
	cout << "To exit the shop, enter \"e\"\n" << endl;
}

void Shop::ShopLoop(Character &c, Monster &m, Potion &p, AncientSpirit a, Game g, Leaderboard l) {
	ShopIntro(c, p, a);
	string input;
	cin >> input;
	while (!(input == "b") && !(input == "e") && !(input == "s")) {
		cin >> input;
	}
    if (input == "b") {
        cout << "\nWhat would u like to buy?" << endl;
        cout << "Ancient Spirit:\t\t\"a\"\nPotion:\t\t\t\"p\"" << endl;
        if (c.SeeBossKills() > 0)
            cout << "Spell Shards:\t\t\"s\"" << endl;
        cout << "Back:\t\t\t\"b\"\n" << endl;
        string input2;
        cin >> input2;
        while (input2 != "b" && input2 != "a" && input2 != "p" && input2 != "s") {
            cout << "\nWhat would u like to buy?\n" << endl;
            cin >> input2;
        }
        if (input2 == "p") {
            cout << "\nHow many potions would you like to buy? You can afford " << c.SeeGold() / p.SeePotionCost() << " potions." << endl;
            cout << "You have " << c.SeeGold() << " gold." << endl;
            cout << "Enter \"0\" to cancel purchase.\n" << endl;
            int i = ScanForInt();
            if (i <= 0) {
                ShopLoop(c, m, p, a, g, l);
            }
            else {
                while (!Transaction(c, p, i)) {
                    cout << "\nHow many would you like to buy?\n" << endl;
                    i = ScanForInt();
                    if (i <= 0) {
                        ShopLoop(c, m, p, a, g, l);
                    }
                }
            }
        }
        else if (input2 == "a") {
            cout << "\nHow many Ancient Spirits would you like to buy? You can afford " << c.SeeGold() / a.SeeCost() << " Ancient Spirits." << endl;
            cout << "You have " << c.SeeGold() << " gold." << endl;
            cout << "Enter \"0\" to cancel purchase.\n" << endl;
            int i = ScanForInt();
            if (i <= 0) {
                ShopLoop(c, m, p, a, g, l);
            }
            else {
                while (!Transaction(c, a, i)) {
                    cout << "\nHow many would you like to buy?\n" << endl;
                    i = ScanForInt();
                    if (i <= 0) {
                        ShopLoop(c, m, p, a, g, l);
                    }
                }
            }
        }
        else if (input2 == "s" && c.SeeBossKills() > 0) {
            cout << "\nHow many Spell Shard packs would you like to buy? (" << c.SeeGold() / 1000 << " max)" << endl;
            cout << "Each Spell Shard pack contains 1 to 1000 Spell shards and costs 1000 gold." << endl;
            cout << "You have " << c.SeeGold() << " gold." << endl;
            cout << "Enter \"0\" to cancel purchase.\n" << endl;
            int i = ScanForInt();
            if (i <= 0) {
                ShopLoop(c, m, p, a, g, l);
            }
            else {
                while (!SpellShardTransaction(c, i)) {
                    cout << "\nHow many would you like to buy?\n" << endl;
                    i = ScanForInt();
                    if (i <= 0) {
                        ShopLoop(c, m, p, a, g, l);
                    }
                }
            }
        }

    }
    else if (input == "s") {
        cout << "\nPotions sell for " << p.SeePotionPrice() << " gold." << endl;
        cout << "You have " << c.SeePotions() << " potions." << endl;
        cout << "How many would you like to sell?\n" << endl;
        int i = ScanForInt();
        while (i > c.SeePotions() || i < 0) {
            if (i > 0 || i < 0) {
                cout << "\nYou only have " << c.SeePotions() << " potions." << endl;
                cout << "How many would you like to sell?\n" << endl;
                i = ScanForInt();
            }
        }
        if(i > 0) 
            SellPotion(c, p, i);
    }
}

bool Shop::Transaction(Character &c, Potion &p, int i) {
    if (c.SeeGold() - Amount(p.SeePotionCost(), i) >= 0) {
        c.IncreasePotions(i);
        c.DecreaseGold(Amount(p.SeePotionCost(), i));
        if (i == 1) {
            if (c.SeePotions() == 1)
                cout << "\nYou have bought " << i << " potion and now have " << c.SeePotions() << " potion." << endl;
            else
                cout << "\nYou have bought " << i << " potion and now have " << c.SeePotions() << " potions." << endl;
        }
        else {
            cout << "\nYou have bought " << i << " potions and now have " << c.SeePotions() << " potions." << endl;
        }
        cout << "You have " << c.SeeGold() << " gold remaining." << endl;
        return true;
    }
    else {
        cout << "\nYou do not have enough gold for that purchase." << endl;
        return false;
    }
}

bool Shop::Transaction(Character &c, AncientSpirit a, int i) {
    if (c.SeeGold() - Amount(a.SeeCost(), i) >= 0) {
        c.IncreaseAncientCount(i);
        c.DecreaseGold(Amount(a.SeeCost(), i));
        if (i == 1) {
            if (c.SeeAncientCount() == 1)
                cout << "\nYou have bought " << i << " Ancient Spirit and now have " << c.SeeAncientCount() << " Ancient Spirit." << endl;
            else
                cout << "\nYou have bought " << i << " Ancient Spirit and now have " << c.SeeAncientCount() << " Ancient Spirits." << endl;
        }
        else {
            cout << "\nYou have bought " << i << " Ancient Spirits and now have " << c.SeeAncientCount() << " Ancient Spirits." << endl;
        }
        cout << "You have " << c.SeeGold() << " gold remaining." << endl;
        return true;
    }
    else {
        cout << "\nYou do not have enough gold for that purchase." << endl;
        return false;
    }
}

int SpellShardRoll(Character& c) {
    Random r;
    int d = r.RandomInt(1, 1000, c.rng);
    if (d < 850) {
        return 1;
    }
    else if (d >= 850 && d < 950) {
        return 5;
    }
    else if (d >= 950 && d < 990) {
        return 10;
    }
    else if (d >= 990 && d < 1000) {
        return 100;
    }
    else {
        return 1000;
    }
}

bool Shop::SpellShardTransaction(Character& c, int i) {
    if (c.SeeGold() - Amount(SpellShardCost, i) >= 0) {
        int sp;
        cout << endl;
        for (int roll = 0; roll < i; roll++) {
            sp = SpellShardRoll(c);
            if (sp > 1)
                cout << "You gained " << sp << " Spell Shards!\n" << endl;
            else if (sp == 1)
                cout << "You gained a Spell Shard.\n" << endl;
            c.IncreaseSpellShards(sp);
        }
        c.DecreaseGold(Amount(SpellShardCost, i));
        cout << "You now have " << c.SeeSpellShards() << " Spell Shards." << endl;
        cout << "You have " << c.SeeGold() << " gold remaining." << endl;
        return true;
    }
    else {
        cout << "\nYou do not have enough gold for that purchase." << endl;
        return false;
    }
}

void Shop::SellPotion(Character &c, Potion &p, int i) {
    c.DecreasePotions(i);
    c.IncreaseGold(Amount(p.SeePotionPrice(), i));
    if (i == 1) {
        if (c.SeePotions() == 1) {
            cout << "\nYou have sold " << i << " potion and now have " << c.SeePotions() << " potion." << endl;
        }
        else {
            cout << "\nYou have sold " << i << " potion and now have " << c.SeePotions() << " potions." << endl;
        }
    }
    else {
        if (c.SeePotions() == 1) {
            cout << "\nYou have sold " << i << " potions and now have " << c.SeePotions() << " potion." << endl;
        }
        else {
            cout << "\nYou have sold " << i << " potions and now have " << c.SeePotions() << " potions." << endl;
        }
    }
    cout << "You now have " << c.SeeGold() << " gold!" << endl;
}