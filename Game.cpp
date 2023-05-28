#include <cctype>

#include "Game.h"
#include "Shop.h"

bool PlayGame = false;

using namespace std;

int Game::ScanForInt() {
    int i;
    while (true) {
        cin >> i;
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
    }
    return i;
}

string Game::Intro() {
    cout << "\nPlease enter a name for your character\n" << endl;
    string name;
    cin >> name;
    cout << "\nHello " << name << endl;
    return name;
}
void Game::IntroMessage() {
    cout << "Welcome!\nEnter \"leaderboard\" to view the leaderboard.\nEnter \"load\" to continue an already existing character.\nEnter any other key to create a character.\n" << endl;
}

void Game::NewGame(Character &c, Potion &p, Monster &m) {
    c = Character();
    p = Potion();
    c.SetName(Intro());
    Tutorial(c, m, p);
    PlayGame = true;
}

void Game::LoadGame(Character &c, Potion &p, Monster &m) {
    Leaderboard l = Leaderboard();
    cout << "\nWhat is the name of the character you would like to load?\n" << endl;
    string CharName;
    cin >> CharName;
    while (!l.CheckValidSave(CharName) && CharName != "n") {
        cout << "\nI'm sorry that character does not exist.\n" << endl;
        cout << "What is the name of the character you would like to load? Enter \"n\" if you wish to create a new character.\n" << endl;
        cin >> CharName;
    }
    if (CharName == "n") {
        NewGame(c, p, m);
    }
    else {
        vector<int> at = l.LoadSave(CharName);
        c = Character(CharName, at[0], at[1], at[2], at[3], at[4], at[5], at[6], at[7], at[8], at[9], at[10], at[11], at[12], at[13], at[14], at[15], at[16], at[17], at[18], at[19]);
        p = Potion(at[20], at[21], at[22]);
        int u = 0;
        int p = 23;
        for (int i = 23; i < at.size() && at[i] != -1; i += 2) {
            Spell s = Spell();
            s.SpellIdentity = at[i];
            s.LearnSpell(c);
            c.Spells[u].UpgradeTo(c, at[i + 1]);
            u++;
            p = i + 1;
        }
        p+=2;
        if (p < at.size()) {
            RuneStone r = RuneStone();
            //cout << at[p] << endl;
            r.Initialize(c, at[p]);//at[p]
            c.Rune = r;
            for (int i = p + 1; i < at.size(); i++) {
                RuneStone rune = RuneStone();
                rune.Initialize(c, at[i]);
                c.Inventory.push_back(rune);
            }
        }
        c.DamageReductionCalculator();
        PlayGame = true;
    }
}

void Game::AskPlayGame(Character &c, Potion &p, Monster &m) {
    cout << "Would you like play the game? (y/n)\n" << endl;
    string in;
    cin >> in;
    if (in != "n") {
        cout << "\nEnter \"load\" to continue an already existing character, or enter any other key to create a character.\n" << endl;
        cin >> in;
        if (in == "load") {
            LoadGame(c, p, m);
        }
        else {
            NewGame(c, p, m);
        }
    }
}

void Game::StartGame(Character &c, Potion &p, Monster &m, Leaderboard l, AncientSpirit a) {
    IntroMessage();
    string in;
    cin >> in;
    if (in == "leaderboard") {
        l.DisplayLeaderboard();
        cout << "Would you like play the game? (y/n)\n" << endl;
        cin >> in;
        if (in != "n") {
            cout << "\nEnter \"load\" to continue an already existing character, or enter any other key to create a character.\n" << endl;
            cin >> in;
            if (in == "load") {
                LoadGame(c, p, m);
            }
            else {
                NewGame(c, p, m);
            }

        }
    }
    else if (in == "load") {
        LoadGame(c, p, m);
    }
    else {
        NewGame(c, p, m);
    }
}

static string MobAdj(Character &c) {
    Random r;
    string MobAdj [37] = {"rambunctious", "erroneous", "bloodcrazed","muscular","chubby","boney","hysterical","possessed","naughty","fabulous","helpless","lovely","wretched","delightful","winged","huge", "emphatic",
      "dangerous","carnivorous","horned","poisounous","handsome","chaotic","peace-loving","ravenous","fat","fearless","frail","wicked","beautiful","terrible","sinister","Frank the","diseased","stealthy","buoyant","phenomenally attractive" };
    return MobAdj[r.RandomInt(0, 37 - 1, c.rng)];
}

static void IncreaseDungeonLevel(Character &c, Potion &p) {
    c.IncreaseDungeonLevel();
    c.DamageReductionCalculator();
    c.SetKillsSinceDungeon(0);
    c.SetDungeonLevelAvailable(false);
    cout << "\nWelcome to level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
    if (c.SeeDungeonLevel() == 2) {
        cout << "A new monster type awaits you on this floor... Zombies!" << endl;
    }
    else if (c.SeeDungeonLevel() == 4) {
        cout << "A new monster type awaits you on this floor... Slimes!" << endl;
    }
    //cout << "Challenging foes await." << endl;
}

int AncientSpiritDrop(Character &c) {
    AncientSpirit a = AncientSpirit();
    Random r;
    double ancient = r.RandomDouble(0, 1, c.rng);
    if (ancient <= a.SeeDropRate()) {
        return 1 + AncientSpiritDrop(c);
    }
    return 0;
}

int EternalDrop(Character& c) {
    AncientSpirit a = AncientSpirit();
    Random random;
    double Eternal = random.RandomDouble(0, 1, c.rng);
    if (Eternal <= a.SeeEternalRate()) {
        return 1 + EternalDrop(c);
    }
    return 0;
}

int SpellShardDrop(Character &c) {
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

bool ContainsSpell(Character &c, int i) {
    for (auto s : c.Spells) {
        if (s.SpellIdentity == i) {
            return true;
        }
    }
    return false;
}

void SpellDrop(Character& c) {
    if (c.SeeDungeonLevel() > 3 || (c.SeeDungeonLevel() == 3 && c.SeeBossAvailable() == true)) {
        Random r;
        for (int i = 5; i < 8; i++) {
            if (r.RandomInt(1, 20, c.rng) == 20) {
                if (!ContainsSpell(c, i)) {
                    Spell s = Spell(i);
                    s.LearnSpell(c);
                    cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
                    cout << "Would you like to learn more about what " << s.SeeName() << " does? (y/n)\n" << endl;
                    string input;
                    cin >> input;
                    if (input == "y" || input == "yes") {
                        s.Attributes(c);
                    }
                }
            }
        }
    }
}

bool Game::IfMonsterSlain(Monster& m, Character& c, Potion& p, string adj) {
    if (m.SeeCurrentHealth() <= 0) {
        Random r;
        cout << "You have slain the " << adj << " " << m.SeeName() << "." << endl;
        cout << "You survived the fight with " << c.SeeCurrentHealth() << " health remaining." << endl;
        int GoldDrop = r.RandomInt(m.SeeGoldMin(), m.SeeGoldMax(), c.rng);
        c.IncreaseKills();
        c.IncreaseGold(GoldDrop);
        if (GoldDrop > 0)
            cout << "You gained " << GoldDrop << " gold." << endl;
        int Potions = m.PotionDrop(c);
        c.IncreasePotions(Potions);
        if (Potions > 1)
            cout << "You gained " << Potions << " health potions." << endl;
        else if (Potions == 1)
            cout << "You gained a health potion." << endl;

        if (c.SeeKills() > 5)
        {
            int Ancient = AncientSpiritDrop(c);
            if (Ancient > 1)
                cout << "You gained " << Ancient << " Ancient Spirits!!!" << endl;
            else if (Ancient == 1)
                cout << "You gained an Ancient Spirit!!!" << endl;
            c.IncreaseAncientCount(Ancient);

        }
        else if (c.SeeKills() == 5) {
            AncientTutorial(c);
        }

        if (c.SeeBossKills() > 0) {
            int sp = r.RandomInt(1, 100, c.rng);
            if (sp == 100) {
                sp = SpellShardDrop(c);
                if (sp > 1)
                    cout << "*** You gained " << sp << " Spell Shards ***" << endl;
                else if (sp == 1)
                    cout << "*** You gained a Spell Shard ***" << endl;
                c.IncreaseSpellShards(sp);
            }
        }
        
        c.IncreaseKillsSinceDungeon();
        if (c.SeeKillsSinceDungeon() == 50) {
            c.SetBossAvailable(true);
            cout << "\nThe boss of level " << c.SeeDungeonLevel() << " is available to fight!" << endl;
            cout << "Enter \"fb\" to fight the boss now, or enter \"w\" to wait till later." << endl;
            cout << "If you wait, you can enter \"fb\" later when you feel ready.\n" << endl;
            string in;
            cin >> in;
            while (in != "fb" && in != "w") {
                cout << "\nEnter \"fb\" to fight the boss now, or enter \"w\" to wait til later.\n" << endl;
                cin >> in;
            }
            if (in == "fb") {
                if (BossTutorial(c, m, p)) {
                    Leaderboard l = Leaderboard();
                    AttackBoss(m, c, p, l);
                }
            }
        }

        if (c.SeeKills() == 10 && c.SeeShort() == 0) {
            cout << "\nTo change whether fights display each back and fourth, you can always enter \"t\"." << endl;
        }

        if (c.SeeKills() == 2) {
            cout << "\nTo heal between fights, enter \"p\" to drink a potion." << endl;
        }

        if (c.SeeKills() == 25) {
            cout << "\nAfter a total of 50 kills, the first boss will be available to fight." << endl;
            cout << "25 more kills to go!" << endl;

        }

        return true;
    }
    else {
        return false;
    }
}

static void WizzySlain(Monster& m, Character& c, Potion& p) {
    cout << m.SeeName() << " cries out to you: " << endl;
    cout << "\"Please " << c.SeeName() << ", spare me and give me 100 potions, so I can live to see another day.\"" << endl;
    cout << "\"I will leave you with everything in my bag, and even teach you about the art of potion tasting.\"" << endl;
    cout << "\"I beg you to help me...\"" << endl;
    cout << "\nWould you like to help " << m.SeeName() << "? (y/n)\nYou have " << c.SeePotions() << " potions.\n" << endl;
    string in;
    cin >> in;
    if (in == "y" || in == "yes") {
        cout << "\nYou hand over 100 potions to " << m.SeeName() << ", hoping to not regret it." << endl;
        c.DecreasePotions(100);
        if (c.SeePotions() != 1) {
            cout << "You have " << c.SeePotions() << " potions left.\n" << endl;
        }
        else {
            cout << "You have " << c.SeePotions() << " potion left.\n" << endl;
        }
        cout << "*Glug Glug Glug*" << endl;
        cout << "\"Ahhhhh, thank you " << c.SeeName() << ". Now to teach you the art of potion drinking.\"" << endl;
        cout << "\"Now the key to mastering the art of potion drinking is to swirl it like your favorite glass of wine.\"" << endl;
        cout << "\"Practice it with me!\"" << endl;
        cout << "\"Wow such a beautiful job " << c.SeeName() << ". You will be a potion tasting master in no time.\"" << endl;
        p.IncreasePotionMin(10);
        p.IncreasePotionMax(15);
        cout << "\nPotions will now heal you 10-15 more health!" << endl;
        cout << "They now heal you for " << p.SeePotionMin() + 5 * (c.SeeHealth() / 100) << " to " << p.SeePotionMax() + 5 * (c.SeeHealth() / 100) << " health.\n" << endl;
    }
    else {
        cout << "\nYou decide to kill " << m.SeeName() << " anyways." << endl;
    }
}

bool Game::IfBossSlain(Monster& m, Character& c, Potion& p) {
    if (m.SeeCurrentHealth() <= 0) {
        Random r;
        if (m.SeeName() == "Wizzy the Wizard" && c.SeePotions() >= 100) {
            WizzySlain(m, c, p);
            
        }
        else {
            cout << "You have slain the " << m.SeeName() << "!" << endl;
        }
        
        cout << "You survived the dangerous fight with " << c.SeeCurrentHealth() << " health remaining." << endl;
        if (c.SeeCurrentMana() != c.SeeMana()) {
            c.SetCurrentMana(c.SeeMana());
            cout << "Your mana has replenished to " << c.SeeCurrentMana() << "." << endl;
        }

        int GoldDrop = r.RandomInt(m.SeeGoldMin(), m.SeeGoldMax(), c.rng);
        c.IncreaseBossKills();
        c.IncreaseGold(GoldDrop);
        if (GoldDrop > 0)
            cout << "You gained " << GoldDrop << " gold." << endl;
        int Potions = m.PotionDrop(c);
        c.IncreasePotions(Potions);
        if (Potions > 1)
            cout << "You gained " << Potions << " health potions." << endl;
        else if (Potions == 1)
            cout << "You gained a health potion." << endl;

        int Ancient = r.RandomInt(1, 2 + c.SeeDungeonLevel(), c.rng);
        if (Ancient > 1)
            cout << "You gained " << Ancient << " Ancient Spirits!!!" << endl;
        else if (Ancient == 1)
            cout << "You gained an Ancient Spirit!!!" << endl;
        c.IncreaseAncientCount(Ancient);

        int sp = SpellShardDrop(c);
        if (sp > 1)
            cout << "*** You gained " << sp << " Spell Shards ***" << endl;
        else if (sp == 1)
            cout << "*** You gained a Spell Shard ***" << endl;
        c.IncreaseSpellShards(sp);
        if (c.SeeBossKills() == 1) {
            SpellUpgradeTutorial(c);
        }
        else if (c.SeeBossKills() == 2) {
            EternalOrbTutorial(c);
        }
        else { // if eternal orbs have a chance of dropping
            int Eternal = EternalDrop(c);
            if (Eternal > 1) {
                cout << "\n  -------------------------" << endl;
                cout << "| You gained " << Eternal << " Eternal Orbs | " << endl;
                cout << "  -------------------------" << endl;
            }
            else if (Eternal == 1) {
                cout << "\n  -------------------------" << endl;
                cout << "| You gained an Eternal Orb |" << endl;
                cout << "  -------------------------" << endl;
            }
            c.IncreaseEternalCount(Eternal);
        }

        /*if (c.SeeDungeonLevel() == 1 && c.SeeBossAvailable()) {
            Spell s = Spell("Skull Crusher");
            s.LearnSpell(c);
            cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
        }
        else if (c.SeeDungeonLevel() == 2 && c.SeeBossAvailable()) {*/
        if (c.SeeDungeonLevel() == 2 && c.SeeBossAvailable()) {
            Spell s = Spell("Deadly Stab");
            s.LearnSpell(c);
            cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
            cout << "Would you like to learn more about what " << s.SeeName() << " does? (y/n)\n" << endl;
            string input;
            cin >> input;
            if (input == "y" || input == "yes") {
                s.Attributes(c);
            }

        }
        else if (c.SeeDungeonLevel() == 3 && c.SeeBossAvailable()) {
            Spell s = Spell("Flame Bellow");
            s.LearnSpell(c);
            cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
            cout << "Would you like to learn more about what " << s.SeeName() << " does? (y/n)\n" << endl;
            string input;
            cin >> input;
            if (input == "y" || input == "yes") {
                s.Attributes(c);
            }
        }
        else if ((c.SeeDungeonLevel() == 10 || c.SeeDungeonLevel() == 19) && c.SeeBossAvailable()) {
            EquipTutorial(c);
        }

        if (c.SeeDungeonLevel() >= 19) {
            c.Rune.RuneStoneDrop(c);
        }

        c.Blocking = false;
        c.TempDamageReduction = 0;
        c.TDRTurns = 0;
        c.Rune.ResetComboBonus();

        SpellDrop(c);

        if (c.SeeBossAvailable()) {
            c.SetBossAvailable(false);
        }
        if (!c.SeeDungeonLevelAvailable()) {
            c.SetDungeonLevelAvailable(true);
            cout << "\nYou have found the way to the next level of the dungeon!\nEnter \"delve\"";
            cout << " when you would like to go to level " << c.SeeDungeonLevel() + 1 << " of the dungeon." << endl;
            //if (c.SeeDungeonLevel() == 1) {
            cout << "If you choose to stay on this level after defeating the boss, other bosses can sneak up on you when you aren't expecting it!" << endl;
            //}
        }
        return true;
    }
    return false;
}

static bool IfBossSlimeSlain(Monster& m, Character& c, Potion& p) {
    if (m.SeeCurrentHealth() <= 0) {
        Random r;
        cout << "You have slain " << m.SeeName() << "!" << endl;
        cout << "You survived the dangerous fight with " << c.SeeCurrentHealth() << " health remaining." << endl;

        c.SetCurrentMana(c.SeeMana());
        cout << "Your mana has replenished to " << c.SeeCurrentMana() << "." << endl;

        int GoldDrop = r.RandomInt(m.SeeGoldMin(), m.SeeGoldMax(), c.rng);
        c.IncreaseBossKills();
        c.IncreaseGold(GoldDrop);
        if (GoldDrop > 0)
            cout << "You gained " << GoldDrop << " gold." << endl;
        int Potions = m.PotionDrop(c);
        c.IncreasePotions(Potions);
        if (Potions > 1)
            cout << "You gained " << Potions << " health potions." << endl;
        else if (Potions == 1)
            cout << "You gained a health potion." << endl;

        int Ancient = r.RandomInt(5, 3 + 2 * c.SeeDungeonLevel(), c.rng);
        cout << "You gained " << Ancient << " Ancient Spirits!!!" << endl;
        c.IncreaseAncientCount(Ancient);


        int sp =  2 * SpellShardDrop(c);
        cout << "*** You gained " << sp << " Spell Shards ***" << endl;
        c.IncreaseSpellShards(sp);

        int Eternal = EternalDrop(c);
        if (Eternal > 1) {
            cout << "\n  -------------------------" << endl;
            cout << "| You gained " << Eternal << " Eternal Orbs | " << endl;
            cout << "  -------------------------" << endl;
        }
        else if (Eternal == 1) {
            cout << "\n  -------------------------" << endl;
            cout << "| You gained an Eternal Orb |" << endl;
            cout << "  -------------------------" << endl;
        }
        c.IncreaseEternalCount(Eternal);

        c.Blocking = false;
        c.TempDamageReduction = 0;
        c.TDRTurns = 0;

        if (!ContainsSpell(c, 4)) {
            Spell s = Spell("Lightning Bolt");
            s.LearnSpell(c);
            cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
            cout << "Would you like to learn more about what " << s.SeeName() << " does? (y/n)\n" << endl;
            string input;
            cin >> input;
            if (input == "y" || input == "yes") {
                s.Attributes(c);
            }
        }
        return true;
    }
    return false;
}

static bool IfYouSlain(Character &c, Potion &p, Leaderboard l) {
    if (c.SeeCurrentHealth() <= 0) {
        cout << "\nYou have been slain." << endl;
        l.SaveGame(c, p, 0);
        l.UpdateLeaderboard(c);
        PlayGame = false;
        return true;
    }
    return false;
}

void Game::AttackBoss(Monster &m, Character &c, Potion& p, Leaderboard l) {
    m = m.ChooseBoss(c);
    bool run = false;
    cout << "\nYou have approached " << m.SeeName() << " who is guarding the way to level " << c.SeeDungeonLevel() + 1 << " of the dungeon." << endl;
    while (!IfYouSlain(c, p, l) && !(IfBossSlain(m, c, p)) && !run) {
        cout << "It is your turn. What would you like to do?\n" << endl;
        Turn(c, m, p, run);
        if (m.SeeCurrentHealth() > 0 && !run) {
            Turn(m, c);
        }
    }
}

void Game::AttackedByBoss(Monster &m, Character &c, Potion &p, Leaderboard l) {
    bool run = false;
    while (!IfYouSlain(c, p, l) && !IfBossSlain(m, c, p) && !run) {
        Turn(m, c);
        if (c.SeeCurrentHealth() > 0) {
            cout << "It is your turn. What would you like to do?\n" << endl;
            Turn(c, m, p, run);
        }
    }
}

void BossSlimeGift(Monster& m, Character& c, Potion& p, bool first) {
    if (!first) {
        cout << "\nYou see " << m.SeeName() << " approaching you.\n" << endl;
        cout << "\n   ------- " << endl;
        cout << "|_|  o o  |_|" << endl;
        cout << "  |   O   |" << endl;
        cout << "   -------\n" << endl;
        cout << "\"Hey " << c.SeeName() << ", it's great to see you again friend.\"" << endl;
        c.Blocking = false;
        c.TempDamageReduction = 0;
        c.TDRTurns = 0;
    }
    Random r;
    int Ancient = r.RandomInt(5, 3 + 2 * c.SeeDungeonLevel(), c.rng);
    c.IncreaseAncientCount(Ancient);
    int GoldDrop = r.RandomInt(m.SeeGoldMin(), m.SeeGoldMax(), c.rng);
    GoldDrop /= 2;
    c.IncreaseGold(GoldDrop);

    int sp = SpellShardDrop(c);
    sp *= 2;
    c.IncreaseSpellShards(sp);

    cout << "\"I've got a present for you!\"" << endl;
    //cout << "\"Goodbye " << c.SeeName() << ", I hope our paths will cross again soon.\"" << endl;
    cout << "You open your present to find " << GoldDrop << " gold, " << Ancient << " Ancient Spirits, and " << sp << " Spell Shards!" << endl;
    int e = r.RandomInt(1, 10, c.rng);
    if (!first && e == 10) {
        c.IncreaseEternalCount();
        cout << "Even though slimes LOVE eternal orbs, " << m.SeeName() << " left you one in your present." << endl;
    }
    if (!ContainsSpell(c, 4)) {
        Spell s = Spell("Lightning Bolt");
        s.LearnSpell(c);
        cout << "\nYou have learned the spell " << s.SeeName() << "!" << endl;
        cout << "Would you like to learn more about what " << s.SeeName() << " does? (y/n)\n" << endl;
        string input;
        cin >> input;
        if (input == "y" || input == "yes") {
            s.Attributes(c);
        }
    }

    string input;
    cout << "\nWould you like to say \"thank you\" or \"leave\" abruptly?\n" << endl;
    getline(cin, input);
    while (input.find("Thank you") == string::npos && input.find("thank you") == string::npos && input.find("Thank You") == string::npos && input.find("Leave") == string::npos && input.find("leave") == string::npos) {
        cout << "\nWould you like to say \"thank you\" or \"leave\"?\n" << endl;
        getline(cin, input);
    }
    if (input.find("Leave") != string::npos || input.find("leave") != string::npos) {
        cout << "\nYou look behind to see a heartbroken look on Blobby's face...\nYou have lost a friend." << endl;
        c.SlimeFriend = false;
    }
    else {
        int d = r.RandomInt(1, 20, c.rng);
        if (d == 20) {
            cout << "\n\"Wait " << c.SeeName() << ", I...\"" << endl;
            cout << "*Blobby starts blushing*" << endl;
            cout << "\"I love you!!!\"" << endl;
            cout << "\nThings get a little awkward, so you scurry away." << endl;
        }
        else {
            cout << "\n\"Goodbye " << c.SeeName() << ", I hope our paths will cross again soon.\"" << endl;
        }
    }
}

void SlimeGift(Monster& m, Character& c, Potion& p) {
    cout << "\n   ----- " << endl;
    cout << "\\ | O O | /" << endl;
    cout << " \\|  V  |/" << endl;
    cout << "   -----" << endl;
    cout << "\n\"Hey " << c.SeeName() << "!\"" << endl;
    Random r;
    int dialogue = r.RandomInt(1, 4, c.rng);
    if (dialogue == 1) {
        cout << "A small slime runs up to you and jumps in your arms." << endl;
    }
    else if (dialogue == 2) {
        cout << "A small slime sits down in front of you smiling :)" << endl;
    }
    else if (dialogue == 3) {
        cout << "A slime hops on your back, hoping for a quick piggy back ride." << endl;

    }
    else {
        cout << "A cute little slime jumps on your back and gnaws on your shoulder affectionately." << endl;
    }
    int Ancient = AncientSpiritDrop(c);
    c.IncreaseAncientCount(Ancient);
    int GoldDrop = r.RandomInt(m.SeeGoldMin(), m.SeeGoldMax(), c.rng);
    c.IncreaseGold(GoldDrop);
    if (r.RandomInt(0, 1, c.rng) == 0)
        cout << "The slime throws up a present covered in slime goo and scurries away." << endl;
    else
        cout << "The slime hands you a present covered in slime goo and scurries away." << endl;
    cout << "You get the goo off your present and find " << GoldDrop << " gold!" << endl;

    if (Ancient > 1)
        cout << "The slime also gave you " << Ancient << " Ancient Spirits!!!" << endl;
    else if (Ancient == 1)
        cout << "The slime also gave you an Ancient Spirit!" << endl;
    int e = r.RandomInt(1, 150, c.rng);
    if (e == 150) {
        c.IncreaseEternalCount();
        cout << "Even though slimes LOVE eternal orbs, it left you one in your present." << endl;
    }
}

void Game::AttackedBySlime(Monster& m, Character& c, Potion& p, Leaderboard l) {
    bool run = false;
    bool PlayerKnockedOut = false;
    while (!IfYouSlain(c, p, l) && !(IfBossSlimeSlain(m, c, p)) && !run && !c.SlimeFriend) {
        SlimeTurn(m, c, PlayerKnockedOut);
        if (c.SeeCurrentHealth() > 0) {
            if (!PlayerKnockedOut) {
                cout << "It is your turn. What would you like to do?\n" << endl;
                Turn(c, m, p, run);
            }
            else {
                PlayerKnockedOut = false;
                cout << "You spend your turn getting all the slime goo off of you.\n" << endl;
            }
        }
    }
}

static void AttackMonster(Character &c, Monster &m) {
    Random r;
    int YourDmg = r.RandomInt(c.SeeMinDamage(), c.SeeMaxDamage(), c.rng);
    cout << "\nYou attack " << m.SeeName() << " and hit for " << YourDmg << " damage!" << endl;
    YourDmg = c.Rune.DamageAbility(c, m, YourDmg);
    c.Rune.Ability(c, m, YourDmg);
    m.SetCurrentHealth(m.SeeCurrentHealth() - YourDmg);
    if (m.SeeCurrentHealth() > 0)
        cout << "The " << m.SeeName() << " has " << m.SeeCurrentHealth() << " health remaining.\n" << endl;
}

void Game::Turn(Character &c, Monster &m, Potion &p, bool &run) {
    string input;
    cin >> input;
    while (input != "a" && input != "b" && input != "p" && input != "s" && input != "r" && input != "i" && input != "g" && input != "pa") {
        BattleOptions(c, m);
        cin >> input;
    }
    if (input == "a") {
        AttackMonster(c, m);
        if (c.SeeCurrentMana() < c.SeeMana())
            c.IncreaseCurrentMana();
    }
    else if (input == "b") {
        cout << "\nYou prepare to block the next incoming attack.\n" << endl;
        c.Blocking = true;
        if (c.SeeCurrentMana() < c.SeeMana())
            c.IncreaseCurrentMana();
        c.Rune.ResetComboBonus();
    }
    else if (input == "g") {
        if (m.SeeName() == "Blobby the Slime" && !c.SlimeFriend && c.SeeEternalCount() > 0) {
            cout << "\nYou throw an eternal orb to " << m.SeeName() << "." << endl;
            cout << "He jumps into the air, catching it in his mouth with a delighted smiled on his face." << endl;
            cout << "\"Eternal Orbs are my favorite food! I almost never get to eat such a tasty snack.\"" << endl;
            cout << "\"I will let the other slimes know that you are a friend :)\"" << endl;
            cout << "\"Oh and by the way...\"" << endl;
            c.SlimeFriend = true;
            c.DecreaseEternalCount();
            c.Rune.ResetComboBonus();
            BossSlimeGift(m, c, p, true);
        }
        else {
            Turn(c, m, p, run);
        }
    }
    else if (input == "i") {
        m.BossInformation(c);
        Turn(c, m, p, run);
    }
    else if (input == "p") {
        p.PotionDrink(c);
        if (c.SeeCurrentMana() < c.SeeMana())
            c.IncreaseCurrentMana();
        cout << endl;
        c.Rune.ResetComboBonus();
    }
    else if (input == "pa") {
        c.BossFightAttributes();
        cout << "\nWhat would you like to do?\n" << endl;
        Turn(c, m, p, run);
    }
    else if (input == "r") {
        cout << "\nAre you sure you would like to run away from the fight like a coward? (y/n)" << endl;
        double Gold = 0.5 * c.SeeGold();
        int GoldLost = (int)Gold;
        cout << "You would lose " << GoldLost << " gold in the process.\n" << endl;
        cin >> input;
        if (input == "y" || input == "yes") {
            run = true;
            c.DecreaseGold(GoldLost);
            cout << "\nYou have fled the fight like a loser." << endl;
            c.SetCurrentMana(c.SeeMana());
        }
        else {
            Turn(c, m, p, run);
        }
        c.Rune.ResetComboBonus();
        
    }
    else if (input == "s") {
        if (c.Spells.size() == 0) {
            cout << "\nYou do not know how to cast any spells.  What would you like to do?\n" << endl;
            Turn(c, m, p, run);
        }
        else if (c.SeeCurrentMana() == 0) {
            cout << "\nYou have 0 mana remaining. What would you like to do?\n" << endl;
            Turn(c, m, p, run);
        }
        else {
            cout << "\nWhich spell would you like to cast? You have " << c.SeeCurrentMana() << " mana." << endl;
            cout << "Enter:\t\tSpell Name:\tMana Cost:\n" << endl;
            for (int i = 0; i < c.Spells.size(); i++) {
                cout << " " << i + 1 << "\t\t" << c.Spells[i].SeeName();
                if (c.Spells[i].SeeName() == "Heal")
                    cout << "\t";
                cout << "\t" << c.Spells[i].SeeManaCost() << " Mana" << endl;
            }
            cout << endl;
            int in = ScanForInt();
            while (in < 0 || in > c.Spells.size()) {
                cout << "\nEnter a spell number between 1-" << c.Spells.size() << " or 0 to pick something else to do.\n" << endl;
                in = ScanForInt();
            }
            if (in != 0) {
                if ((c.SeeCurrentMana() - c.Spells[in - 1].SeeManaCost()) < 0) {
                    cout << "\nYou do not have enough mana to cast " << c.Spells[in - 1].SeeName() << "." << endl;
                    cout << "You have " << c.SeeCurrentMana() << " mana. What would you like to do?\n" << endl;
                    Turn(c, m, p, run);
                }
                else {
                    c.Spells[in - 1].CastSpell(c, m);
                    cout << "You have " << c.SeeCurrentMana() << " mana remaining.\n" << endl;
                    c.Rune.ResetComboBonus();
                    //if (c.SeeCurrentMana() < c.SeeMana())
                        //c.IncreaseCurrentMana();
                }
            }
            else {
                cout << "\nWhat would you like to do?\n" << endl;
                Turn(c, m, p, run);
            }
        }
    }
}

void Game::Turn(Monster &m, Character &c) {
    if (!m.BossKnockedOut(c)) {
        Random r;
        int Dmg = m.BossEnraged(c);
        /*if ((Dmg - c.SeeDamageReduction()) < 0)
            Dmg = 0;
        else
            Dmg -= (c.SeeDamageReduction());*/
        cout << m.SeeName() << " swings at you dealing " << Dmg << " damage." << endl;
        if (c.TempDamageReduction > 0) {
            if ((Dmg - c.TempDamageReduction) < 0) {
                Dmg = 0;
                cout << "Your magic shield protects you from the damage." << endl;
            }
            else {
                Dmg -= (c.TempDamageReduction);
                cout << "Your magic shield reduces the damage taken by " << c.TempDamageReduction << " damage." << endl;
            }
            if (!c.Blocking)
                cout << "You take " << Dmg << " damage." << endl;
        }
        if (c.Blocking) {
            double B = 0.2 * Dmg;
            int BlockDamage = (int)B;
            cout << "You have blocked the hit, and take only " << BlockDamage << " damage.\n" << endl;
            c.DecreaseCurrentHealth(BlockDamage);
        }
        else {
            c.DecreaseCurrentHealth(Dmg);
        }
    }
    c.Blocking = false;
    if (c.TDRTurns > 0)
        c.TDRTurns--;
    if (c.TDRTurns == 0)
        c.TempDamageReduction = 0;
    if (c.SeeCurrentHealth() > 0)
        cout << "You have " << c.SeeCurrentHealth() << " health remaining and " << c.SeeCurrentMana() << " mana remaining.\n" << endl;
}

void Game::SlimeTurn(Monster& m, Character& c, bool &PlayerKnockedOut) {
    if (!m.BossKnockedOut(c)) {
        Random r;
        int i = r.RandomInt(1, 6, c.rng);
        int Dmg = 0;
        if (i == 1 || i == 2) {
            cout << m.SeeName() << " gives you a hard stare." << endl;
            if (c.Blocking) {
                c.Blocking = false;
                cout << "You stare back aggressively." << endl;
            }
            cout << endl;
        }
        else if (i == 3 || i == 4 || i == 5) {
            Dmg = r.RandomInt(m.SeeMinDamage(), m.SeeMaxDamage(), c.rng);
            Dmg = Dmg - (c.SeeDR() * Dmg);
            if ((Dmg - c.TempDamageReduction) < 0)
                Dmg = 0;
            else
                Dmg -= c.TempDamageReduction;
            cout << m.SeeName() << " bites your leg dealing " << Dmg << " damage." << endl;
            if (c.Blocking) {
                cout << "You attempt to block the bite, but fail miserably." << endl;
                c.Blocking = false;
            }
            c.DecreaseCurrentHealth(Dmg);
            cout << "You have " << c.SeeCurrentHealth() << " health remaining and " << c.SeeCurrentMana() << " mana remaining.\n" << endl;
        }
        else if (i == 6) {
            Dmg = r.RandomInt(m.SeeMinDamage(), m.SeeMaxDamage(), c.rng);
            Dmg = Dmg - (c.SeeDR() * Dmg);
            if ((Dmg - c.TempDamageReduction) < 0)
                Dmg = 0;
            else
                Dmg -= - c.TempDamageReduction;
            cout << m.SeeName() << " jumps at you";
            if (c.Blocking) {
                cout << ", but you are able to deflect him backwards." << endl;
                c.Blocking = false;
            }
            else {
                cout << ", and you become enveloped in slime goo taking " << Dmg << " damage." << endl;
                c.DecreaseCurrentHealth(Dmg);
                PlayerKnockedOut = true;
                cout << "You have " << c.SeeCurrentHealth() << " health remaining and " << c.SeeCurrentMana() << " mana remaining.\n" << endl;
            }
        }
    }
    if (c.TDRTurns > 0)
        c.TDRTurns--;
    if (c.TDRTurns == 0)
        c.TempDamageReduction = 0;
    c.Blocking = false;
}

void Game::BattleOptions(Character c, Monster m) {
    cout << "\nOptions" << endl;
    cout << "Attributes:\t\"pa\"" << endl;
    cout << "Attack:\t\t\"a\"" << endl;
    cout << "Block:\t\t\"b\"" << endl;
    if (!c.SlimeFriend && c.SeeEternalCount() > 0 && m.SeeName() == "Blobby the Slime")
        cout << "Give:\t\t\"g\"" << endl;
    cout << "Info:\t\t\"i\"" << endl;
    cout << "Potion:\t\t\"p\"" << endl;
    cout << "Run:\t\t\"r\"" << endl;
    cout << "Spell:\t\t\"s\"\n" << endl;
}

void Game::NextFight(Monster &m, Character &c, Potion &p, Leaderboard l) {
    Random r;
    int boss = r.RandomInt(1, 75, c.rng);
    if (!c.SeeDungeonLevelAvailable() || boss != 75) {
        string adj = MobAdj(c);
        m = m.ChooseEnemy(c);
        if (m.SeeName() == "slime" && c.SlimeFriend) {
            SlimeGift(m, c, p);
        }
        else {
            cout << "\nYou have encountered a " << adj << " " << m.SeeName() << "!" << endl;
            if (c.SeeShort() == 0) {
                while (m.SeeCurrentHealth() > 0 && c.SeeCurrentHealth() > 0) {
                    Attack(m, c, adj, p, l);
                }
            }
            else {
                while (m.SeeCurrentHealth() > 0 && c.SeeCurrentHealth() > 0) {
                    AttackShort(m, c, adj, p, l);
                }
            }
        }
    }
    else {
        int slime = r.RandomInt(1, 25, c.rng);
        if (slime == 25 && c.SeeDungeonLevel() > 2) {
            m = m.SummonSlimeBoss(c);
            if (!c.SlimeFriend) {
                cout << "\n" << m.SeeName() << " has somehow snuck up on you, despite being large and sluggish.\n" << endl;
                cout << "   ------- " << endl;
                cout << "|_|  o o  |_|" << endl;
                cout << "  |   O   |" << endl;
                cout << "   -------" << endl;
                cout << "\nCaution!!! Although " << m.SeeName() << " appears very cute, he is indeed very dangerous." << endl;
                cout << "Would you like to proceed? (y/n)\n" << endl;
                string in;
                cin >> in;
                while (in != "y" && in != "yes" && in != "n" && in != "no") {
                    cout << "\nWould you like to fight " << m.SeeName() << "?\n" << endl;
                    cin >> in;
                }
                if (in == "y" || in == "yes") {
                    cout << endl;
                    AttackedBySlime(m, c, p, l);
                }
            }
            else {
                BossSlimeGift(m, c, p, false);
            }
        }
        else {
            m = m.ChooseRandomBoss(c);
            cout << "\n" << m.SeeName() << " has snuck up on you while you were picking your nose!" << endl;
            AttackedByBoss(m, c, p, l);
        }
    }
    string dead;
    if (c.SeeCurrentHealth() <= 0)
        cin >> dead;
}

void Game::Attack(Monster &m, Character &c, string adj, Potion &p, Leaderboard l) {
    Random r;
    int YourDmg = r.RandomInt(c.SeeMinDamage(), c.SeeMaxDamage(), c.rng);
    cout << "You attack the " << m.SeeName() << ", hitting for " << YourDmg << " damage." << endl;
    m.SetCurrentHealth(m.SeeCurrentHealth() - YourDmg);
    if (!(IfMonsterSlain(m, c, p, adj))) {
        cout << "The " << m.SeeName() << " has " << m.SeeCurrentHealth() << " health remaining." << endl;
        int Dmg = r.RandomInt(m.SeeMinDamage(), m.SeeMaxDamage(), c.rng);
        Dmg = Dmg - (c.SeeDR() * Dmg);
        /*if ((Dmg - c.SeeDamageReduction()) < 0)
            Dmg = 0;
        else
            Dmg -= c.SeeDamageReduction();*/
        cout << "The " << m.SeeName() << " attacks you, hitting for " << Dmg << " damage." << endl;
        c.DecreaseCurrentHealth(Dmg);
        if (!IfYouSlain(c, p, l)) {
            cout << "You have " << c.SeeCurrentHealth() << " health remaining." << endl;
        }
    }
}

void Game::AttackShort(Monster &m, Character &c, string adj, Potion &p, Leaderboard l) {
    Random r;
    int YourDmg = r.RandomInt(c.SeeMinDamage(), c.SeeMaxDamage(), c.rng);
    m.SetCurrentHealth(m.SeeCurrentHealth() - YourDmg);
    if (!(IfMonsterSlain(m, c, p, adj))) {
        int Dmg = r.RandomInt(m.SeeMinDamage(), m.SeeMaxDamage(), c.rng);
        Dmg = Dmg - (c.SeeDR() * Dmg);
        /*if ((Dmg - c.SeeDamageReduction()) < 0)
            Dmg = 0;
        else
            Dmg -= c.SeeDamageReduction();*/
        c.DecreaseCurrentHealth(Dmg);
        IfYouSlain(c, p, l);
    }
}

/*static void Disable(Character& c, Potion& p) {
    cout << "\nWhat would u like to disable/enable?" << endl;
    cout << "Enter \"ad\" or \"ae\" to disable/enable short attack." << endl;
    cout << "Enter \"pd\" or \"pe\" to disable/enable potion tutorial.\n" << endl;
    string input;
    cin >> input;
    if (input == "ad") {
        cout << "\nShort attack disabled." << endl;
        c.SetShort(0);
    }
    else if (input == "ae") {
        cout << "\nShort attack enabled." << endl;
        c.SetShort(1);
    }
    else if (input == "pd") {
        cout << "\nPotion tutorial disabled." << endl;
        p.SetPotionTut(false);
    }
    else if (input == "pe") {
        cout << "\nPotion tutorial enabled." << endl;
        p.SetPotionTut(true);
    }
}*/

void Game::Information(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l) {
    cout << "\nCharacter information:\t\"ci\"" << endl;
    cout << "Monster information:\t\"mi\"" << endl;
    cout << "Potion information:\t\"pi\"" << endl;
    cout << "Back:\t\t\t\"b\"\n" << endl;
    string input;
    cin >> input;
    if (input == "ci") {
        c.Attributes();
        Information(c, m, p, a, l);
    }
    else if (input == "mi") {
        MonsterInformationIntro(c, m, p, a, l);
    }
    else if (input == "pi") {
        if (c.SeePotions() == 1)
            cout << "\nYou have " << c.SeePotions() << " potion." << endl;
        else
            cout << "\nYou have " << c.SeePotions() << " potions." << endl;
        cout << "Potions heal you for " << p.SeePotionMin() << " - " << p.SeePotionMax() << "  + 5 health for every 100 maximum health you have.\n" << endl;
        Information(c, m, p, a, l);
    }
}

void Game::MonsterInformationIntro(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l) {
    cout << "\nWhich monster would u like more information on?" << endl;
    cout << "Skeleton: \"skeleton\"" << endl;
    cout << "Wizard: \"wizard\"" << endl;
    cout << "Zombie: \"zombie\"" << endl;
    cout << "Slime: \"slime\"" << endl;
    cout << "Enter \"b\" if you wish to go back to the previous page\n" << endl;
    string input;
    cin >> input;
    if (input == "b") {
        Information(c, m, p, a, l);
    }
    else if (input == "wizard") {
        MonsterInformation(c, m.SummonWizard(c), p, a, l);
    }
    else if (input == "skeleton") {
        MonsterInformation(c, m.SummonSkeleton(c), p, a, l);
    }
    else if (input == "zombie") {
        MonsterInformation(c, m.SummonZombie(c), p, a, l);
    }
    else if (input == "slime") {
        MonsterInformation(c, m.SummonSlime(c), p, a, l);
    }
    else if (input == "b") {
        Information(c, m, p, a, l);
    }
}

void Game::MonsterInformation(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l) {
    string name = m.SeeName() + "s";
    name[0] = toupper(name[0]);
    cout << "\n" << name << " deal " << m.SeeMinDamage() << "-" << m.SeeMaxDamage() << " damage and have " << m.SeeHealth() << " hitpoints." << endl;
    cout << "On death, they have a " << (int)(m.SeeDropRate() * 100) << "% chance to drop " << m.SeeGoldMin() << "-" << m.SeeGoldMax() << " gold when slain." << endl;
    cout << name << " also have a " << (int)(m.SeePotionDropRate() * 100) << "% chance to drop a health potion." << endl;
    if (m.SeeName() == "zombie") {
        cout << "This monster can only be found on floor 2 or deeper of the dungeon." << endl;
    }
    else if(m.SeeName() == "slime") {
        cout << "This monster can only be found on floor 4 or deeper of the dungeon." << endl;
    }
    cout << endl;
    Information(c, m, p, a, l);
}

void Game::Options(Character &c) {
    cout << "\nYour Options" << endl;
    cout << "Enter \"a\" to view attributes." << endl;
    if (c.Spells.size() > 0)
        cout << "Enter \"sa\" to view info about your spells." << endl;
    if (c.Inventory.size() > 0) {
        cout << "Enter \"i\" to see your inventory." << endl;
    }
    cout << "Enter \"f\" to fight your next opponent." << endl;
    if (c.SeeBossAvailable())
        cout << "Enter \"fb\" to fight the boss." << endl;
    else if(c.SeeDungeonLevelAvailable())
        cout << "Enter \"delve\" to delve deeper into the dungeon." << endl;
    cout << "Enter \"p\" to drink a health potion." << endl;
    if (c.Rune.SeeName() != "RuneStone") {
        cout << "Enter \"i\" view your inventory." << endl;
    }
    if (c.Inventory.size() > 0) {
        cout << "Enter \"e\" to equip a rune from your inventory." << endl;
    }
    cout << "Enter \"info\" to view general information." << endl;
    cout << "Enter \"s\" to go to the shop." << endl;
    cout << "Enter \"save\" to save game, or enter \"se\" to save and exit game." << endl;
    cout << "Enter \"l\" to view the leaderboard." << endl;
    cout << "Enter \"t\" to shorten or lengthen fight descriptions." << endl;
    cout << "Enter \"u\" to use an Ancient Spirit." << endl;
    if (c.SeeEternalCount() > 0)
        cout << "Enter \"ue\" to use an Eternal Orb." << endl;
    if (c.SeeSpellShards() > 0 && c.Spells.size() > 0)
        cout << "Enter \"up\" to upgrade spells." << endl;
}

void Game::Tutorial(Character &c, Monster &m, Potion &p) {
    cout << "Enemies block your path towards escaping the dungeon." << endl;
    cout << "To fight your first enemy, enter \"f\".\n" << endl;
    string input;
    cin >> input;
    while (input != "f") {
        cout << "\nEnter \"f\"\n" << endl;
        cin >> input;
    }
    cout << "\nYou have encountered a wild " << m.SeeName() << "!" << endl;
    while (m.SeeCurrentHealth() > 0 && c.SeeCurrentHealth() > 0) {
        TutorialAttack(m, c, p);
    }
    cout << "To view your options in the future, enter \"o\"" << endl;
}

void Game::TutorialAttack(Monster &m, Character &c, Potion &p) {
    Random r;
    int YourDmg = r.RandomInt(c.SeeMinDamage(), c.SeeMaxDamage(), c.rng);
    cout << "You attack the " << m.SeeName() << ", hitting for " << YourDmg << " damage." << endl;
    m.SetCurrentHealth(m.SeeCurrentHealth() - YourDmg);
    if (m.SeeCurrentHealth() <= 0) {
        cout << "You did it! You have slain the " << m.SeeName() << "." << endl;
        cout << "\nYou survived your first battle with " << c.SeeCurrentHealth() << " hitpoints remaining." << endl;
        cout << "\nYou eat the enemies's bone marrow, thinking it's a marshmallow, and heal to full health!\nIt almost gave you diabetes, you won't make that mistake again..." << endl;
        c.SetCurrentHealth(c.SeeHealth());
        cout << "You have gained 5 gold." << endl;
        c.IncreaseGold(5);
        cout << "You can use gold in the shop to buy health potions and other goodies." << endl;
        cout << "To access the shop, enter \"s\"\n" << endl;
        string input;
        cin >> input;
        while (input != "s") {
            cout << "\nEnter \"s\" so you can go on a shopping spree\n" << endl;
            cin >> input;
        }
        ShopTutorial(c, m, p);
    }
    else {
        cout << "The " << m.SeeName() << " has " << m.SeeCurrentHealth() << " health remaining." << endl;
        int Dmg = r.RandomInt(m.SeeMinDamage(), m.SeeMaxDamage(), c.rng);
        cout << "The " << m.SeeName() << " attacks you, hitting for " << Dmg << " damage." << endl;
        c.DecreaseCurrentHealth(Dmg);
        cout << "You have " << c.SeeCurrentHealth() << " health remaining." << endl;
    }
}

void Game::ShopTutorial(Character &c, Monster &m, Potion &p) {
    Shop s = Shop();
    cout << "\nWelcome to the shop." << endl;
    cout << "You have " << c.SeeGold() << " gold" << endl;
    cout << "Today what we have in stock is: " << endl;
    cout << "Health Potions: " << p.SeePotionCost() << " gold each" << endl;
    cout << "To buy this item, enter \"b\"\n" << endl;
    string input;
    cin >> input;
    while (input != "b") {
        cout << "\nI recommend you purchase a healing potion before going out in the world.\n" << endl;
        cin >> input;
    }
    s.Transaction(c, p, 1);
    cout << "You are going to need more than one potion, here is an extra 4!" << endl;
    //cout << "To heal in the future, enter \"p\" to drink a potion.\n" << endl;
    c.IncreasePotions(4);
}

bool Game::BossTutorial(Character& c, Monster& m, Potion& p) {
    if (c.Spells.size() == 0) {
        Spell s = Spell("Skull Crusher");
        s.LearnSpell(c);
        cout << "\nTo aid in your first boss fight, you have learned the spell " << s.SeeName() << "!!!" << endl;
        cout << "Would you like to learn more about what Skull Crusher does? (y/n)\n" << endl;
        string input;
        cin >> input;
        if (input == "y" || input == "yes") {
            c.Spells[0].Attributes(c);
        }
        cout << "\nDuring boss fights you can use mana to cast powerful spells." << endl;
        cout << "If you don't cast a spell on your turn, you regain one mana." << endl;
        //cout << "Bosses are difficult, and if you ever feel a little too scared, you can enter \"r\" to runaway... for a hefty price." << endl;
        cout << "Are you ready for your first boss fight? (y/n)\n" << endl;
        cin >> input;
        while (input != "y" && input != "yes" && input != "n" && input != "no") {
            cout << "\nAre you ready for your first boss fight?\n" << endl;
            cin >> input;
        }
        if (input == "n" || input == "no") {
            cout << "\nYou can enter \"fb\" to fight the boss when you feel ready." << endl;
            return false;
        }
    }
    return true;
}

void Game::SpellUpgradeTutorial(Character& c) {
    cout << "\nSpell Shards are used to upgrade your spells!" << endl;
    cout << "Enter \"up\" to pick a spell to upgrade.\n" << endl;
    string input;
    cin >> input;
    while (input != "up") {
        cout << "\nUpgrade Skull Crusher!\n" << endl;
        cin >> input;
    }
    if (c.SeeSpellShards() != 1)
        cout << "\nWhich spell would you like to upgrade? You have " << c.SeeSpellShards() << " Spell Shards." << endl;
    else
        cout << "\nWhich spell would you like to upgrade? You have " << c.SeeSpellShards() << " Spell Shard." << endl;
    cout << "Enter:\t\tSpell Name:\t\tSpell Shard Cost:\n" << endl;
    for (int i = 0; i < c.Spells.size(); i++) {
        cout << " " << i + 1 << "\t\t" << c.Spells[i].SeeName() << "\t\t";
        cout << c.Spells[i].UpgradeCost() << " Spell Shards" << endl;
    }
    cout << endl;
    cin >> input;
    while (input != "1") {
        cout << "\nEnter \"1\" to upgrade Skull Crusher!\n" << endl;
        cin >> input;
    }
    c.DecreaseSpellShards(c.Spells[0].UpgradeCost());
    c.Spells[0].Upgrade(c);
    cout << "\nCongratulations! " << c.Spells[0].SeeName() << " is now Level " << c.Spells[0].Level << "." << endl;
    //cout << "You have " << c.SeeSpellShards() << " Spell Shards remaining." << endl;
    cout << "\nTo see more information about your spells and how powerful they are, you can always enter \"sa\"." << endl;
}

void Game::AncientTutorial(Character& c) {
    cout << "You have found an Ancient Spirit!!!" << endl;
    c.IncreaseAncientCount();
    cout << "\nAncient Spirits are a magical item that will permantently increase your damage or health!" << endl;
    cout << "To use one, enter \"u\" to become more powerful.\n" << endl;
    string input;
    cin >> input;
    while (input != "u") {
        cout << "\nUse your Ancient Spirit!\n" << endl;
        cin >> input;
    }
    AncientSpirit a = AncientSpirit();
    a.AncientUsed(c, 1);
}

void Game::Use(Character& c, AncientSpirit a) {
    if (c.SeeAncientCount() == 1) {
        cout << "\nAre you sure you would like to use an Ancient Spirit? (y/n)\n" << endl;
        string p2;
        cin >> p2;
        if (p2 == "y") {
            a.AncientUsed(c, 1);
        }
    }
    else if (c.SeeAncientCount() > 1) {
        cout << "\nHow many Ancient Spirits would you like to use? (You have " << c.SeeAncientCount() << " Ancient Spirits)\n" << endl;
        int x = ScanForInt();
        while (x < 0 || x > c.SeeAncientCount()) {
            cout << "\nHow many Ancient Spirits would you like to use? Enter \"0\" to cancel.\n" << endl;
            x = ScanForInt();
        }
        a.AncientUsed(c, x);
    }
    else {
        cout << "\nI'm sorry you don't have any Ancient Spirits to use." << endl;
    }
}

void Game::UseEternal(Character& c, AncientSpirit a) {
    if (c.SeeEternalCount() == 1) {
        cout << "\nAre you sure you would like to use an Eternal Orb? (y/n)\n" << endl;
        string p2;
        cin >> p2;
        if (p2 == "y") {
            a.EternalUsed(c, 1);
        }
    }
    else if (c.SeeEternalCount() > 1) {
        cout << "\nHow many Eternal Orbs would you like to use? (You have " << c.SeeEternalCount() << " Eternal Orbs)\n" << endl;
        int x = ScanForInt();
        while (x < 0 || x > c.SeeEternalCount()) {
            cout << "\nHow many Eternal Orbs would you like to use? Enter \"0\" to cancel.\n" << endl;
            x = ScanForInt();
        }
        a.EternalUsed(c, x);
    }
    else {
        cout << "\nI'm sorry you don't have any Eternal Orbs to use." << endl;
    }
}

void Game::EternalOrbTutorial(Character& c) {
    cout << "\n  -------------------------" << endl;
    cout << "| You gained an Eternal Orb |" << endl;
    cout << "  -------------------------" << endl;
    c.IncreaseEternalCount();
    cout << "\nEternal Orbs are a rare item that drop from bosses!" << endl;
    cout << "They will permantently increase your damage reduction by up to 75%!" << endl;
    cout << "Damage reduction is based on your Eternal Orbs consumed and the level of the dungeon you are on." << endl;
    cout << "Eternal Orbs are also incredibly tasty to all sorts of creatures." << endl;
    cout << "Enter \"ue\" to use your Eternal Orb.\n" << endl;
    string input;
    cin >> input;
    while (input != "ue") {
        cout << "\nUse your Eternal Orb!\n" << endl;
        cin >> input;
    }
    AncientSpirit a = AncientSpirit();
    a.EternalUsed(c, 1);
}

void Game::EquipTutorial(Character& c) {
    if (c.Rune.SeeName() == "RuneStone") {
        RuneStone r1, r2, r3;
        r1.Initialize(c, 1);
        r2.Initialize(c, 2);
        r3.Initialize(c, 3);
        cout << "\nRunes are a way of enhancing your abilities during boss fights." << endl;
        cout << "Only one rune can be equipped at a time." << endl;
        cout << "\n1 " << r1.SeeDescription() << "\n" << endl;
        cout << "2 " << r2.SeeDescription() << "\n" << endl;
        cout << "3 " << r3.SeeDescription() << endl;

        cout << "\nChoose a rune to use.\n" << endl;
        int x = ScanForInt();
        while (x < 1 || x > 3) {
            cout << "\nPick a rune (1-3)\n" << endl;
            x = ScanForInt();
        }
        c.Rune.Initialize(c, x);
        cout << "\n" << c.Rune.SeeName() << " has been equipped." << endl;
    }
}

void Game::EquipMenu(Character& c) {
    if (c.Inventory.size() > 0) {
        RuneStone r = RuneStone();
        if (c.Rune.SeeName() != "RuneStone") {
            cout << "\n" << c.Rune.SeeName() << " rune is currently equipped." << endl;
            cout << c.Rune.SeeDescription() << "\n" << endl;
        }
        cout << "-------------\n" << endl;
        for (int i = 0; i < c.Inventory.size(); i++) {
            cout << i + 1 << ":" << endl;
            cout << c.Inventory[i].SeeName() << endl;
            cout << c.Inventory[i].SeeDescription() << endl;
            cout << endl;
        }
        cout << "\nWhich rune would you like to equip? (0 to cancel)\n" << endl;
        int input = ScanForInt();
        while (input < 0 && input > c.Inventory.size()) {
            if (c.Inventory.size() > 1) {
                cout << "\nEnter a number between 1 and " << c.Inventory.size() << ". (0 to cancel)\n" << endl;
            }
            else {
                cout << "\nEnter 1 to equip a new run or 0 to cancel.\n" << endl;
            }
            input = ScanForInt();
        }
        if (input != 0) {
            r.Equip(c, input - 1);
        }
    }
    else {
        cout << "\nYou have no runes in your inventory." << endl;
    }
}

void Game::KeyPressed(Character &c, Monster &m, Potion &p, AncientSpirit a, Leaderboard l) {
    cout << "\nWhat would you like to do next?\n" << endl;
    string input;
    cin >> input;
    if (input == "a") {
        c.Attributes();
    }
    else if (input == "e" && c.Inventory.size() > 0) {
        EquipMenu(c);
    }
    else if (input == "sa") {
        cout << "\nYou know " << c.Spells.size() << " Spells" << endl;
        for (int i = 0; i < c.Spells.size(); i++) {
            c.Spells[i].Attributes(c);
        }
    }
    else if (input == "f") {
        NextFight(m, c, p, l);
    }
    else if (input == "fb") {
        if (c.SeeBossAvailable()) {
            if (BossTutorial(c, m, p)) {
                AttackBoss(m, c, p, l);
            }
        }
        else {
            cout << "\nI'm sorry, you are not ready to fight the boss of this floor yet." << endl;
        }   
    }
    else if (input == "delve") {
        if (c.SeeDungeonLevelAvailable()) {
            if ((c.SeeDungeonLevel() - 1) % 3 == 2) {
                if (c.SeeDungeonLevel() % 9 == 0) {
                    cout << "\nDanger! The next level has been taken over by powerful Vampires!" << endl;
                }
                else {
                    cout << "\nWarning! Every 3 levels the monsters get considerably stronger." << endl;
                }
                cout << "Do you wish to continue to level " << c.SeeDungeonLevel() + 1 << " of the dungeon? (y/n)\n" << endl;
                string i;
                cin >> i;
                if (i == "y" || i == "yes") {
                    IncreaseDungeonLevel(c, p);
                    l.SaveGame(c, p, 0);
                    l.UpdateLeaderboard(c);
                }
            }
            else {
                IncreaseDungeonLevel(c, p);
                l.SaveGame(c, p, 0);
                l.UpdateLeaderboard(c);
            }
        }
        else {
            cout << "\nI'm sorry, you have not found the way to the next level of the dungeon yet." << endl;
        }
    }
    else if (input == "u") {
        Use(c, a);
    }
    else if (input == "up") {
        if (c.Spells.size() < 1) {
            cout << "\nYou don't have any spells to upgrade." << endl;
        }
        else if (c.SeeSpellShards() < 1) {
            cout << "\nYou don't have any Spell Shards." << endl;
        }
        else {
            c.Spells[0].UpgradeMenu(c);
        }
    }
    else if (input == "ue" && c.SeeEternalCount() > 0) {
        UseEternal(c, a);
    }
    else if (input == "l") {
        l.DisplayLeaderboard();
    }
    else if (input == "o") {
        Options(c);
    }
    else if (input == "p") {
        p.PotionDrink(c);
    }
    else if (input == "i") {
        c.InventoryDisplay();
    }
    else if (input == "info") {
        Information(c, m, p, a, l);
    }
    else if (input == "s") {
        Shop sh = Shop();
        sh.ShopLoop(c, m, p, a, *this, l);
    }
    else if (input == "save") {
        l.SaveGame(c, p, 1);
    }
    else if (input == "se") {
        l.SaveGame(c, p, 1);
        PlayGame = false;
    }
    else if (input == "t") {
        //Disable(c, p);
        if (c.SeeShort() == 0) {
            cout << "\nFight text has been shortened." << endl;
            c.SetShort(1);
        }
        else {
            cout << "\nFight text has been lengthened." << endl;
            c.SetShort(0);
        }
    }
    else {
        cout << "\nTo view your options, enter \"o\"" << endl;
    }
}