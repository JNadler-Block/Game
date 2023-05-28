#include "RuneStone.h"
#include "Monster.h"

using namespace std;

void RuneStone::Ability(Character& c, Monster &m, int dmg) {
	if (SeeName() == "Vampiric") {
		VampiricAbility(c, m, dmg);
	}
	else if (SeeName() == "Soul Siphon") {
		SoulSiphonAbility(c, m, dmg);
	}
	else if (SeeName() == "Bone Shatter") {
		BoneShatterAbility(c, m, dmg);
	}
}

int RuneStone::DamageAbility(Character& c, Monster& m, int dmg) {
	if (c.Rune.SeeName() == "Blood Crazed") {
		return c.Rune.ComboAbility(c, dmg);
	}
	else if (c.Rune.SeeName() == "Critical Strike") {
		return c.Rune.CriticalStrikeAbility(c, dmg);
	}
	return dmg;
}

void RuneStone::Vampiric() {
	Name = "Vampiric";
	Description = "Vampiric rune heals you for 20% of the attack damage you deal during boss fights.";
	RuneIdentity = 1;
}

void RuneStone::VampiricAbility(Character& c, Monster& m, int dmg) {
	int Heal = dmg * 0.2;
	cout << "Vampiric rune heals you for " << Heal << ", restoring your health to ";
	if (c.SeeCurrentHealth() + Heal > c.SeeHealth()) {
		c.SetCurrentHealth(c.SeeHealth());
	}
	else {
		c.SetCurrentHealth(c.SeeCurrentHealth() + Heal);
	}
	cout << c.SeeCurrentHealth() << "." << endl;
}

void RuneStone::Combo() {
	Name = "Blood Crazed";
	Description = "Blood Crazed rune increases the damage of each consecutive attack's damage by 15% during boss fights.";
	RuneIdentity = 2;
}

int RuneStone::ComboAbility(Character& c, int dmg) {
	int d = c.Rune.SeeComboBonus() * dmg;
	if (c.Rune.SeeComboBonus() > 1) {
		int i = c.Rune.SeeComboBonus() * dmg - dmg;
		cout << "Blood Crazed rune increased the damage you dealt by " << i << ", dealing a total of " << d << " damage." << endl;
	}
	c.Rune.IncreaseComboBonus();
	return d;
}

void RuneStone::SoulSiphon() {
	Name = "Soul Siphon";
	Description = "Soul Siphon rune has a 25% chance of returning 1 mana when attacking a boss.";
	RuneIdentity = 3;
}

void RuneStone::SoulSiphonAbility(Character& c, Monster& m, int dmg) {
	Random r;
	int random = r.RandomInt(1, 100, c.rng);
	if (random <= 25) {
		if (c.SeeCurrentMana() < c.SeeMana()) {
			c.IncreaseCurrentMana();
			cout << "Soul Siphon rune steals energy, restoring your mana to " << c.SeeCurrentMana() << "." << endl;
		}
	}
}

void RuneStone::BoneShatter() {
	Name = "Bone Shatter";
	Description = "Bone Shatter rune gives attacks a 15% chance of knocking out bosses.";
	RuneIdentity = 4;
}

void RuneStone::BoneShatterAbility(Character& c, Monster &m, int dmg) {
	Random r;
	int random = r.RandomInt(1, 100, c.rng);
	if (random <= 15) {
		cout << "Bone Shatter rune empowers your strike, knocking out your opponent for 1 turn." << endl;
		m.KnockedOut++;
	}
}

void RuneStone::CriticalStrike() {
	Name = "Critical Strike";
	Description = "Critical Strike rune has a 10% chance of dealing 3 times damage when attacking a boss.";
	RuneIdentity = 5;
}

int RuneStone::CriticalStrikeAbility(Character& c, int dmg) {
	Random r;
	int random = r.RandomInt(1, 100, c.rng);
	if (random <= 10) {
		int d = 3 * dmg;
		cout << "You dealt a Critical Strike, increasing the damage done to " << d << endl;
		return d;
	}
	return dmg;
}

void RuneStone::Equip(Character& c, int i) {
	RuneStone r = c.Rune;
	if (r.SeeName() != "RuneStone")
		c.Rune = c.Inventory[i];
	c.Inventory[i] = r;
	cout << "\n" << c.Rune.SeeName() << " is now equipped." << endl;
}

void RuneStone::Initialize(Character& c, int id) {
	if (id == 1) {
		Vampiric();
	}
	else if (id == 2) {
		Combo();
	}
	else if (id == 3) {
		SoulSiphon();
	}
	else if (id == 4) {
		BoneShatter();
	}
	else if (id == 5) {
		CriticalStrike();
	}
	else {
		Name = "RuneStone";
		RuneIdentity = 0;
	}
}

void RuneStone::RuneStoneDrop(Character& c) {
	if (c.Inventory.size() < 4) {
		Random r;
		int random = r.RandomInt(1, 200, c.rng);
		if (random == 200) {
			vector<int> RuneId;
			bool t;
			for (int i = 1; i <= 5; i++) {
				t = true;
				if (c.Rune.RuneIdentity == i) {
					t = false;
				}
				else {
					for (int j = 0; j < c.Inventory.size(); j++) {
						if (c.Inventory[j].RuneIdentity == i) {
							t = false;
							j = c.Inventory.size();
						}
					}
				}
				if (t) {
					RuneId.push_back(i);
				}
			}
			if (RuneId.size() > 0) {
				RuneStone rune; 
				rune.Initialize(c, RuneId[r.RandomInt(0, RuneId.size() - 1, c.rng)]);
				c.Inventory.push_back(rune);
				cout << "\nYou have obtained a powerful rune: " << rune.SeeName() << endl;
				cout << rune.SeeDescription() << endl;
				cout << "\nWould you like to equip it or add it to your inventory? (e/i)\n" << endl;
				string in;
				cin >> in;
				while (in != "e" && in != "i") {
					cout << "\nEnter \"e\" to equip the your new rune, or \"i\" to add it to your inventory.\n" << endl;
					cin >> in;
				}
				if (in == "e") {
					rune.Equip(c, c.Inventory.size() - 1);
				}
				else {
					cout << "\n" << rune.SeeName() << " has been added to your inventory." << endl;
				}
			}
		}
	}
}