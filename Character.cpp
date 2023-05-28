#include "Character.h"

using namespace std;

Character::Character(const string n, const int m, const int M,
	const int h, const int ch, const int ma, const int cm, const int damager,
	const int g, const int k, const int bk,
	const int p, const int s, const int a, const int e, const int sp, const int d,
	const int ksd, const bool ba, const bool da, const bool sf) {
	Name = n;
	MinDamage = m;
	MaxDamage = M;
	Health = h;
	CurrentHealth = ch;
	Mana = ma;
	CurrentMana = cm;
	DamageReduction = damager;
	Gold = g;
	Kills = k;
	BossKills = bk;
	Potions = p;
	Short = s;
	AncientCount = a;
	EternalCount = e;
	SpellShards = sp;
	DungeonLevel = d;
	KillsSinceDungeon = ksd;
	BossAvailable = ba;
	DungeonLevelAvailable = da;
	SlimeFriend = sf;
}

int T(int pow) {
	int t = 1;
	for (int i = 0; i < pow; i++) {
		t *= 2;
	}
	return t;
}

void Character::DamageReductionCalculator() {
	double total = 0;
	int dr = SeeDamageReduction();
	int f = 1;
	int s = 2;
	int t = 4;
	for (int i = 4; i <= SeeDungeonLevel(); i += 3) {
		f += 1 * ((i + 2) / 3) * T((i - 1) / 9);
		s += 2 * ((i + 2) / 3) * T((i - 1) / 9);
		t += 4 * ((i + 2) / 3) * T((i - 1) / 9);
	}
	if (dr >= f) {
		dr -= f;
		total += 0.25;
	}
	else {
		total += 0.25 * (double)dr / f;
		dr = 0;
	}
	if (dr >= s) {
		dr -= s;
		total += 0.25;
	}
	else {
		total += 0.25 * (double)dr / s;
		dr = 0;
	}
	if (dr >= t) {
		dr -= t;
		total += 0.25;
	}
	else {
		total += 0.25 * (double)dr / t;
		dr = 0;
	}
	SetDR(total);
}

void Character::Attributes() {
	cout << "\nYour Attributes" << endl;
	cout << "Damage: " << SeeMinDamage() << "-" << SeeMaxDamage() << endl;
	cout << "Maximum Health: " << SeeHealth() << endl;
	cout << "Current Health: " << SeeCurrentHealth() << endl;
	cout << "Mana: " << SeeCurrentMana() << endl;
	if (SeeDamageReduction() != 0) {
		cout << setprecision(2) << fixed;
		cout << "Damage Reduction: " << 100 * SeeDR() << "%" << endl;
	}
	if (Rune.RuneIdentity != 0) {
		cout << "Rune: " << Rune.SeeName() << endl;
	}
	cout << "Gold: " << SeeGold() << endl;
	cout << "Health Potions: " << SeePotions() << endl;
	cout << "Ancient Spirits: " << SeeAncientCount() << endl;
	cout << "Eternal Orbs: " << SeeEternalCount() << endl;
	cout << "Spell Shards: " << SeeSpellShards() << endl;
	cout << "Kills: " << SeeKills() << endl;
	cout << "Boss Kills: " << SeeBossKills() << endl;
	cout << "You are on level " << SeeDungeonLevel() << " of the dungeon." << endl;
}

void Character::BossFightAttributes() {
	cout << "\nYour Attributes" << endl;
	cout << "Damage: " << SeeMinDamage() << "-" << SeeMaxDamage() << endl;
	cout << "Maximum Health: " << SeeHealth() << endl;
	cout << "Current Health: " << SeeCurrentHealth() << endl;
	cout << "Mana: " << SeeCurrentMana() << endl;
	if (SeeDamageReduction() != 0) {
		cout << setprecision(2) << fixed;
		cout << "Damage Reduction: " << 100 * SeeDR() << "%" << endl;
	}
	cout << "Health Potions: " << SeePotions() << endl;
}

void Character::InventoryDisplay() {
	cout << endl;
	if (Rune.SeeName() == "RuneStone") {
		cout << "You do not have a Rune equipped.\n" << endl;
	}
	else {
		cout << "Rune Equipped " << endl;
		cout << "-------------" << endl;
		cout << Rune.SeeName() << endl;
		cout << Rune.SeeDescription() << endl;
		cout << endl;
	}
	if (Inventory.size() != 0) {
		cout << "Inventory" << endl;
		cout << "-------------" << endl;
		for (int i = 0; i < Inventory.size(); i++) {
			if (i > 0)
				cout << endl;
			cout << Inventory[i].SeeName() << endl;
			cout << Inventory[i].SeeDescription() << endl;
		}
	}
}

