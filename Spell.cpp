#include "Spell.h"
#include "Monster.h"

using namespace std;

Spell::Spell(string n, string sl, int m, int M, int mc, double k, double se, double we, double ze, double slime, double dm, bool pd) {
	Name = n;
	SpellLine = sl;
	MinDamage = m;
	MaxDamage = M;
	ManaCost = mc;
	KnockOut = k;
	SkeletonEffective = se;
	WizardEffective = we;
	ZombieEffective = ze;
	SlimeEffective = slime;
	DamageMult = dm;
	PlayerDamage = pd;
}

void Spell::SkullCrusher() {
	SpellLine = "You use the skill Skull Crusher to deal a deadly blow, crushing the bones of your enemy.";
	Name = "Skull Crusher";
	MinDamage = 0;
	MaxDamage = 0;
	ManaCost = 5;
	KnockOut = 0.5;
	SkeletonEffective = 2;
	SpellIdentity = 1;
}

void Spell::DeadlyStab() {
	SpellLine = "You perform a precise stab, vicously wounding your enemy.";
	Name = "Deadly Stab";	
	MinDamage = 2;
	MaxDamage = 4;
	ManaCost = 4;
	WizardEffective = 2;
	SpellIdentity = 2;
}

void Spell::FlameBellow() {
	SpellLine = "You breath out a huge gush of flames, warming your insides.";
	Name = "Flame Bellow";
	PlayerDamage = false;
	MinDamage = 22;
	MaxDamage = 28;
	ManaCost = 6;
	ZombieEffective = 2;
	SpellIdentity = 3;
}

void Spell::LightningBolt() {
	SpellLine = "You feel charged with energy, zapping a strong bolt of lightning out of your fingers.";
	Name = "Lightning Bolt";
	PlayerDamage = false;
	MinDamage = 1;
	MaxDamage = 200;
	KnockOut = 0.5;
	ManaCost = 10;
	SlimeEffective = 2;
	SpellIdentity = 4;
}

void Spell::Heal() {
	SpellLine = "You feel a rejuvinating sensation.";
	Name = "Heal";
	PlayerDamage = false;
	MinDamage = 80;
	MaxDamage = 100;
	ManaCost = 9;
	SpellIdentity = 5;
}

void Spell::BlockAttack() {
	SpellLine = "You prepare to strike quickly before defending.";
	Name = "Block Attack";
	PlayerDamage = true;
	MinDamage = 0;
	MaxDamage = 0;
	ManaCost = 4;
	SpellIdentity = 6;
}

void Spell::MagicShield() {
	SpellLine = "You feel a magical sense of safety and prepare to defend yourself.";
	Name = "Magic Shield";
	PlayerDamage = false;
	MinDamage = 30;
	MaxDamage = 30;
	ManaCost = 8;
	Turns = 3;
	SpellIdentity = 7;
}

int Spell::Damage(Character& c, Monster& m) {
	Random r;
	double Dmg;
	if (PlayerDamage)
		Dmg = r.RandomDouble(c.SeeMinDamage() + SeeMinDamage(), c.SeeMaxDamage() + SeeMaxDamage(), c.rng) * DamageMult;
	else
		Dmg = r.RandomDouble(MinDamage, MaxDamage, c.rng);
	if (SeeName() == "Heal")
		Dmg += 0.1 * c.SeeHealth();
	if (m.SeeName() == "skeleton" || m.SeeName() == "Skeleton Man") {
		Dmg *= SkeletonEffective;
	}
	else if (m.SeeName() == "wizard"  || m.SeeName() == "Wizzy the Wizard") {
		Dmg *= WizardEffective;
	}
	else if (m.SeeName() == "zombie" || m.SeeName() == "Henry the Zombie") {
		Dmg *= ZombieEffective;
	}
	else if (m.SeeName() == "slime" || m.SeeName() == "Blobby the Slime") {
		Dmg *= SlimeEffective;
	}
	return (int)Dmg;
}

void Spell::KnockMonsterOut(Monster &m, Character &c) {
	Random r;
	if (KnockOut > 1) {
		m.KnockedOut += (int)(KnockOut);
		//cout << (int)(KnockOut) << endl;
		double rounds = KnockOut - floor(KnockOut);
		if (r.RandomDouble(0, 1, c.rng) <= rounds) {
			m.KnockedOut++;
		}
		cout << "The " << m.SeeName() << " has been knocked out for " << m.KnockedOut << " turns." << endl;
	}
	else if (r.RandomDouble(0, 1, c.rng) <= KnockOut) {
		m.KnockedOut += (int)(KnockOut + 1);
		cout << "The " << m.SeeName() << " has been knocked out for " << m.KnockedOut << " turn." << endl;
	}
}

void Spell::CastSpell(Character &c, Monster &m) {
	int Dmg = Damage(c, m);
	cout << SpellLine << endl;
	if (SeeName() == "Heal") {
		if (c.SeeCurrentHealth() + Dmg >= c.SeeHealth()) {
			c.SetCurrentHealth(c.SeeHealth());
			cout << "You have been healed back to " << c.SeeCurrentHealth() << " health." << endl;
		}
		else {
			c.IncreaseCurrentHealth(Dmg);
			cout << "You heal yourself for " << Dmg << " health and now have " << c.SeeCurrentHealth() << " health remaining." << endl;
		}
	}
	else if (SeeName() == "Magic Shield") {
		c.TDRTurns = Turns;
		c.TempDamageReduction = Dmg;
		c.Blocking = true;
	}
	else {
		if (SeeName() == "Block Attack")
			c.Blocking = true;
		m.SetCurrentHealth(m.SeeCurrentHealth() - Dmg);
		cout << SeeName() << " hits for " << Dmg << " damage!" << endl;
		if (m.SeeCurrentHealth() > 0)
			cout << m.SeeName() << " has " << m.SeeCurrentHealth() << " health remaining." << endl;
		KnockMonsterOut(m, c);
	}
	if ((c.SeeCurrentMana() - SeeManaCost()) < 0)
		c.SetCurrentMana(0);
	else
		c.DecreaseCurrentMana(SeeManaCost());
}

void Spell::LearnSpell(Character &c) {
	if (SeeName() == "Skull Crusher" || SpellIdentity == 1) {
		SkullCrusher();
	}
	else if (SeeName() == "Deadly Stab" || SpellIdentity == 2) {
		DeadlyStab();
	}
	else if (SeeName() == "Flame Bellow" || SpellIdentity == 3) {
		FlameBellow();
	}
	else if (SeeName() == "Lightning Bolt" || SpellIdentity == 4) {
		LightningBolt();
	}
	else if (SeeName() == "Heal" || SpellIdentity == 5) {
		Heal();
	}
	else if (SeeName() == "Block Attack" || SpellIdentity == 6) {
		BlockAttack();
	}
	else if (SeeName() == "Magic Shield" || SpellIdentity == 7) {
		MagicShield();
	}
	Spell s = *this;
	c.Spells.push_back(s);
}

int Spell::UpgradeCost() {
	if (Level == 1) {
		return 1;
	}
	if (Level > 99) {
		return 250;
	}
	int c = 0;
	for (int i = 2; i <= 21; i++) {
		c += 5;
		if (Level == i) {
			return c;
		}
	}
	return c;
}

void Spell::UpgradeTo(Character& c, int u) {
	for (int i = Level; i < u; i++) {
		Upgrade(c);
	}
}

int Spell::TotalLevel(Character& c) {
	int total = 0;
	for (int i = 0; i < c.Spells.size(); i++) {
		total += c.Spells[i].Level;
	}
	return total;
}

int Spell::AverageLevel(Character& c) {
	return TotalLevel(c) / c.Spells.size();
}

int Spell::UpgradeLevelRequirement(Character& c) {
	int r = AverageLevel(c);
	int l = (Level - (Level % 10) + 10) / 2; 
	if (r >= l || Level < 30) {
		r = 0;
	}
	else {
		r = l * c.Spells.size() - TotalLevel(c);
	}
	return r;
}

void Spell::Upgrade(Character& c) {
	Level++;
	if (SpellIdentity == 1) {
		//MinDamage += 5;
		//MaxDamage += 10;
		if (Level > 99) {
			MinDamage += 1800;
			MaxDamage += 3600;
		}
		else if (Level < 50) {
			//DamageMult += 0.1;
			MinDamage += (9 * (Level - 1));
			MaxDamage += (18 * (Level - 1));
		}
		else {
			//DamageMult += 0.05;
			MinDamage += 450;
			MaxDamage += 900;
		}
		if (KnockOut < 1) {
			KnockOut += 0.02;
		}
		if (Level == 5 || Level == 9) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 2) {
		//MinDamage += 8;
		//MaxDamage += 15;
		if (Level > 99) {
			MinDamage += 200;
			MaxDamage += 5200;
		}
		else if (Level < 50) {
			//DamageMult += 0.11;
			MinDamage += (1 * (Level - 1));
			MaxDamage += (26 * (Level - 1));
		}
		else {
			//DamageMult += 0.05;
			MinDamage += 50;
			MaxDamage += 1300;
		}
		if (Level == 5 || Level == 9) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 3) {
		if (Level > 99) {
			MinDamage += 2800;
			MaxDamage += 6200;
		}
		else if (Level < 50) {
			MinDamage += (14 * (Level - 1));
			MaxDamage += (28 * (Level - 1));
		}
		else {
			MinDamage += 700;
			MaxDamage += 1400;
		}
		if (Level == 7 || Level == 12 || Level == 20) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 4) {
		if (Level > 99) {
			MaxDamage += 10000;
		}
		else if (Level < 50) {
			MaxDamage += (50 * (Level - 1));
		}
		else {
			MaxDamage += 2500;
		}
		//MaxDamage += (40 * (Level - 1));
		if (KnockOut < 2) {
			KnockOut += 0.02;
		}
		if (Level == 6 || Level == 11 || Level == 18) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 5) {
		if (Level > 99) {
			MinDamage += 4000;
			MaxDamage += 12000;
		}
		else if (Level < 50) {
			MinDamage += (20 * (Level - 1));
			MaxDamage += (60 * (Level - 1));
		}
		else {
			MinDamage += 1000;
			MaxDamage += 3000;
		}
		if (Level == 5 || Level == 9) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 6) {
		//MinDamage += 5;
		//MaxDamage += 10;
		if (Level > 99) {
			MinDamage += 1800;
			MaxDamage += 3600;
		}
		else if (Level < 50) {
			//DamageMult += 0.1;
			MinDamage += (9 * (Level - 1));
			MaxDamage += (18 * (Level - 1));
		}
		else {
			//DamageMult += 0.05;
			MinDamage += 450;
			MaxDamage += 900;
		}
		if (Level == 5 || Level == 9) {
			ManaCost--;
		}
	}
	else if (SpellIdentity == 7) {
		if (Level > 99) {
			MinDamage += 1000;
			MaxDamage += 2000;
		}
		else if (Level < 50) {
			MinDamage += (5 * (Level - 1));
			MaxDamage += (10 * (Level - 1));
		}
		else {
			MinDamage += 250;
			MaxDamage += 500;
		}
		if (Level == 5 || Level == 10) {
			ManaCost--;
		}
		else if (Level == 6 || Level == 10 || Level == 25) {
			Turns++;
		}
	}
}

int ScanForInt() {
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

void Spell::UpgradeMenu(Character& c) {
	if (c.SeeSpellShards() != 1)
		cout << "\nWhich spell would you like to upgrade? (0 to cancel) You have " << c.SeeSpellShards() << " Spell Shards." << endl;
	else
		cout << "\nWhich spell would you like to upgrade? (0 to cancel) You have " << c.SeeSpellShards() << " Spell Shard." << endl;
	cout << "Enter:\t\tSpell Name:\t\tSpell Shard Cost:\n" << endl;
	for (int i = 0; i < c.Spells.size(); i++) {
		cout << " " << i + 1 << "\t\t" << c.Spells[i].SeeName() << "\t\t";
		if (c.Spells[i].SeeName() == "Heal")
			cout << "\t";
		cout << c.Spells[i].UpgradeCost() << " Spell Shards" << endl;
	}
	cout << endl;
	int in = ScanForInt();
	while (in < 0 || in > c.Spells.size()) {
		cout << "\nEnter a spell number between 1 and " << c.Spells.size() << ", or 0 to cancel.\n" << endl;
		in = ScanForInt();
	}
	if (in != 0) {
		if ((c.SeeSpellShards() - c.Spells[in - 1].UpgradeCost()) < 0) {
			cout << "\nYou do not have enough Spell Shards to upgrade " << c.Spells[in - 1].SeeName() << endl;
		}
		else if (c.Spells[in - 1].UpgradeLevelRequirement(c) != 0) {
			cout << "\nYou need to upgrade " << c.Spells[in - 1].UpgradeLevelRequirement(c) << " more spells before you can upgrade " << c.Spells[in - 1].SeeName() << "." << endl;
		}
		else {
			c.DecreaseSpellShards(c.Spells[in - 1].UpgradeCost());
			c.Spells[in - 1].Upgrade(c);
			cout << "\nCongratulations! " << c.Spells[in - 1].SeeName() << " is now Level " << c.Spells[in - 1].Level << "." << endl;
			cout << "You have " << c.SeeSpellShards() << " Spell Shards remaining." << endl;
		}
	}
}

void Spell::Attributes(Character &c) {
	cout << "\n" << SeeName() << " is level " << Level << endl;
	cout << SeeName() << " costs " << SeeManaCost() << " mana." << endl;
	if (SeeName() == "Heal") {
		cout << SeeName() << " heals you for " << SeeMinDamage() << "-" << SeeMaxDamage() << " health + 10% of your maximum health." << endl;
	}
	else if (SeeName() == "Magic Shield") {
		if (SeeMinDamage() == SeeMaxDamage())
		 cout << SeeName() << " shields you from " << SeeMinDamage() << " damage each turn for the next " << Turns << " turns." << endl;
		else 
			cout << SeeName() << " shields you from " << SeeMinDamage() << "-" << SeeMaxDamage() << " damage each turn for the next " << Turns << " turns." << endl;
		cout << "It also prepares you to block the next attack from your enemy." << endl;
	}
	else if (SeeName() == "Block Attack") {
		cout << SeeName() << " deals ";
		cout << (int) (DamageMult * (c.SeeMinDamage() + SeeMinDamage())) << "-" << (int)(DamageMult * (c.SeeMaxDamage() + SeeMaxDamage())) << " damage (based on your damage)." << endl;
		cout << "It also prepares you to block the next attack from your enemy." << endl;
	}
	else {
		cout << SeeName() << " deals ";
		if (PlayerDamage) {
			cout << (int)(DamageMult * (c.SeeMinDamage() + SeeMinDamage())) << "-" << (int)(DamageMult * (c.SeeMaxDamage() + SeeMaxDamage())) << " damage (based on your damage). ";
		}
		else {
			cout << SeeMinDamage() << "-" << SeeMaxDamage() << " damage. ";
		}
		if (SeeSkeletonEffective() != 1) {
			cout << SeeName() << " deals " << (int)(SeeSkeletonEffective() * 100) << "% damage to skeletons." << endl;
		}
		if (SeeWizardEffective() != 1) {
			cout << SeeName() << " deals " << (int)(SeeWizardEffective() * 100) << "% damage to wizards." << endl;
		}
		if (SeeZombieEffective() != 1) {
			cout << SeeName() << " deals " << (int)(SeeZombieEffective() * 100) << "% damage to zombies." << endl;
		}
		if (SeeSlimeEffective() != 1) {
			cout << SeeName() << " deals " << (int)(SeeSlimeEffective() * 100) << "% damage to slimes." << endl;
		}
		if (KnockOut > 0 && KnockOut <= 1) {
			cout << SeeName() << " has a " << (int)(KnockOut * 100) << "% chance to knock the enemy out for a turn." << endl;
		}
		else if (KnockOut > 1) {
			cout << SeeName() << " knocks the opponent out for " << KnockOut << " turns." << endl;
		}
	}
}