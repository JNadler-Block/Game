#include "Leaderboard.h"

using namespace std;

void Leaderboard::DisplayLeaderboard() {
	// open Leaderboard.txt and LeaderboardNames.txt
	ifstream LeaderboardLevels ("Leaderboard.txt");
	ifstream LeaderboardNames ("LeaderboardNames.txt");

	vector<int> a;
	vector<string> b;

	int x;
	while (LeaderboardLevels >> x) {
		a.push_back(x);
	}

	string name;
	while (getline(LeaderboardNames, name)) {
		if(name != "")
			b.push_back(name);
	}
	int LeaderboardAmount = (int)b.size(); // amount of players on the leaderboard

	cout << endl;
	for (int i = 0; i < LeaderboardAmount; i++) {
		cout << (i + 1) << ".\tDungeon Level " << a[i] << "\t";
		if (a[i] < 10)
			cout << "\t";
		cout << b[i] << endl;
	}

	if (LeaderboardAmount == 0) 
		cout << "The leaderboard is up for grabs" << endl;
	cout << endl;

	LeaderboardLevels.close();
	LeaderboardNames.close();
}

/*void Leaderboard::ChangeLeaderboard(Character c) {
	// open Leaderboard.txt and LeaderboardNames.txt
	ifstream LeaderboardLevels ("Leaderboard.txt");
	ifstream LeaderboardNames ("LeaderboardNames.txt");

	vector<int> a;
	vector<string> b;

	int x;
	while (LeaderboardLevels >> x) {
		a.push_back(x);
	}

	string name;
	while (getline(LeaderboardNames, name)) {
		if (name != "")
			b.push_back(name);
	}

	vector<int> a2 = a;
	vector<string> b2 = b;
	int LeaderboardAmount = (int)b.size(); // amount of players on the leaderboard

	int index = -1;
	for (int i = 0; i < a.size(); i++) {
		if (c.SeeDungeonLevel() > a[i]) {
			a[i] = c.SeeDungeonLevel();
			b[i] = c.SeeName();
			index = i;
			break;
		}
	}
	if (index == -1 && LeaderboardAmount > 0 && LeaderboardAmount < LEADERBOARDLENGTH) {
		a.push_back(c.SeeDungeonLevel());
		b.push_back(c.SeeName());
		LeaderboardAmount++;
		cout << "Congratulations, " << c.SeeName() << "! ";
		cout << "You made it to position " << LeaderboardAmount << " on the leaderboard ending on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
		cout << "Your deeds shall be remembered" << endl;
	}
	else if (LeaderboardAmount == 0) {
		a.push_back(c.SeeKills());
		b.insert(b.begin(), c.SeeName());
		LeaderboardAmount++;
		cout << "Congratulations, " << c.SeeName() << "! " << endl;
		cout << "You are the first player on the leaderboard! You ended on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
		cout << "Your deeds shall be remembered" << endl;
	}
	else if (index != -1) {
		cout << "Congratulations, " << c.SeeName() << "! ";
		cout << "You made it to position " << index + 1 << " on the leaderboard! You ended on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
		cout << "Your deeds shall be remembered" << endl;
		for (int i = index; i < b2.size() && i < LEADERBOARDLENGTH; i++) {
			if (i == b2.size() - 1) {
				a.push_back(a2[i]);
				b.push_back(b2[i]);
			}
			else {
				a[i + 1] = a2[i];
				b[i + 1] = b2[i];
			}
		}
		if (LeaderboardAmount < LEADERBOARDLENGTH)
			LeaderboardAmount++;
	}
	else {
		cout << "I'm sorry " << c.SeeName() << ", dying on level " << c.SeeDungeonLevel() << " of the dungeon wasn't enough to place you on the leaderboard." << endl;
		cout << "Your deeds shall not be remembered" << endl;
	}

	LeaderboardLevels.close();
	LeaderboardNames.close();

	ofstream LeaderboardK ("Leaderboard.txt");
	ofstream LeaderboardN ("LeaderboardNames.txt");

	for (int i = 0; i < LeaderboardAmount; i++) {
		LeaderboardK << a[i] << endl;
		LeaderboardN << b[i] << endl;
	}

	LeaderboardK.close();
	LeaderboardN.close();
}*/

void Leaderboard::UpdateLeaderboard(Character &c) {
	// open Leaderboard.txt and LeaderboardNames.txt
	ifstream LeaderboardLevels("Leaderboard.txt");
	ifstream LeaderboardNames("LeaderboardNames.txt");

	vector<int> a;
	vector<string> b;

	int x;
	while (LeaderboardLevels >> x) {
		a.push_back(x);
	}

	string name;
	while (getline(LeaderboardNames, name)) {
		if (name != "")
			b.push_back(name);
	}

	int LeaderboardAmount = (int)b.size(); // amount of players on the leaderboard

	int index = -1;
	for (int i = 0; i < a.size(); i++) {
		if (c.SeeDungeonLevel() > a[i]) {
			a.insert(a.begin() + i, c.SeeDungeonLevel());
			b.insert(b.begin() + i, c.SeeName());
			index = i;
			break;
		}
	}
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == c.SeeDungeonLevel() - 1 && b[i] == c.SeeName()) {
			a.erase(a.begin() + i);
			b.erase(b.begin() + i);
		}
	}
	if (a.size() > LEADERBOARDLENGTH) {
		a.pop_back();
		b.pop_back();
	}
	if (index == -1 && LeaderboardAmount > 0 && LeaderboardAmount < LEADERBOARDLENGTH) {
		a.push_back(c.SeeDungeonLevel());
		b.push_back(c.SeeName());
		LeaderboardAmount++;
		if (c.SeeCurrentHealth() > 0) {
			cout << "You are at position " << LeaderboardAmount << " on the leaderboard." << endl;
		}
		else {
			cout << "Congratulations, " << c.SeeName() << "! ";
			cout << "You made it to position " << LeaderboardAmount << " on the leaderboard ending on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
			cout << "Your deeds shall be remembered." << endl;
		}
	}
	else if (LeaderboardAmount == 0) {
		a.push_back(c.SeeDungeonLevel());
		b.insert(b.begin(), c.SeeName());
		LeaderboardAmount++;
		if (c.SeeCurrentHealth() > 0) {
			cout << "You are the first player on the leaderboard." << endl;
		}
		else {
			cout << "Congratulations, " << c.SeeName() << "! ";
			cout << "You made it to position " << LeaderboardAmount << " on the leaderboard ending on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
			cout << "Your deeds shall be remembered." << endl;
		}
	}
	else if (index != -1) {
		if (c.SeeCurrentHealth() > 0) {
			cout << "You are at position " << index + 1 << " on the leaderboard." << endl;
		}
		else {
			cout << "Congratulations, " << c.SeeName() << "! ";
			cout << "You made it to position " << index + 1 << " on the leaderboard! You ended on level " << c.SeeDungeonLevel() << " of the dungeon!" << endl;
			cout << "Your deeds shall be remembered." << endl;
		}
	}
	else {
		if (c.SeeCurrentHealth() <= 0) {
			cout << "I'm sorry " << c.SeeName() << ", dying on level " << c.SeeDungeonLevel() << " of the dungeon wasn't enough to place you on the leaderboard." << endl;
			cout << "Your deeds shall not be remembered." << endl;
		}
	}

	LeaderboardLevels.close();
	LeaderboardNames.close();

	ofstream LeaderboardK("Leaderboard.txt");
	ofstream LeaderboardN("LeaderboardNames.txt");

	for (int i = 0; i < LeaderboardAmount; i++) {
		LeaderboardK << a[i] << endl;
		LeaderboardN << b[i] << endl;
	}

	LeaderboardK.close();
	LeaderboardN.close();
}

void Leaderboard::SaveGame(Character c, Potion p, int x) {
	ofstream CharacterFile ("CharacterSaves//" + c.SeeName() + ".txt");

	CharacterFile << c.SeeMinDamage() << endl;
	CharacterFile << c.SeeMaxDamage() << endl;
	CharacterFile << c.SeeHealth() << endl;
	CharacterFile << c.SeeCurrentHealth() << endl;
	CharacterFile << c.SeeMana() << endl;
	CharacterFile << c.SeeCurrentMana() << endl;
	CharacterFile << c.SeeDamageReduction() << endl;
	CharacterFile << c.SeeGold() << endl;
	CharacterFile << c.SeeKills() << endl;
	CharacterFile << c.SeeBossKills() << endl;
	CharacterFile << c.SeePotions() << endl;
	CharacterFile << c.SeeShort() << endl;
	CharacterFile << c.SeeAncientCount() << endl;
	CharacterFile << c.SeeEternalCount() << endl;
	CharacterFile << c.SeeSpellShards() << endl;
	CharacterFile << c.SeeDungeonLevel() << endl;
	CharacterFile << c.SeeKillsSinceDungeon() << endl;
	CharacterFile << c.SeeBossAvailable() << endl;
	CharacterFile << c.SeeDungeonLevelAvailable() << endl;
	CharacterFile << c.SlimeFriend << endl;

	CharacterFile << p.SeePotionMin() << endl;
	CharacterFile << p.SeePotionMax() << endl;
	CharacterFile << p.SeePotionTut() << endl;

	for (int i = 0; i < c.Spells.size(); i++) {
		CharacterFile << c.Spells[i].SpellIdentity << endl;
		CharacterFile << c.Spells[i].Level << endl;
	}

	CharacterFile << -1 << endl;
	CharacterFile << c.Rune.RuneIdentity << endl;
	for (int i = 0; i < c.Inventory.size(); i++) {
		CharacterFile << c.Inventory[i].RuneIdentity << endl;
	}

	if(x > 0)
		cout << "\nGame Saved" << endl;

	CharacterFile.close();
}

vector<int> Leaderboard::LoadSave(string Name) {
	ifstream CharacterFile ("CharacterSaves//" + Name + ".txt");
	vector<int> a;
	int x;
	while (CharacterFile >> x) {
		a.push_back(x);
	}
	CharacterFile.close();
	return a;
}

bool Leaderboard::CheckValidSave(string Name) {
	ifstream CharacterFile;
	CharacterFile.open("CharacterSaves//" + Name + ".txt");
	bool valid = false;
	if (CharacterFile) {
		if (CheckAlive(Name)) {
			valid = true;
			cout << "\nWelcome back, " << Name << "!" << endl;
		}
		else {
			cout << "\nI'm sorry that character is no longer alive.\n" << endl;
		}
	}
	CharacterFile.close();
	return valid;
}

bool Leaderboard::CheckAlive(string Name) {
	vector<int> a = LoadSave(Name);
	return (a[3] > 0);
}