#pragma once
#include <iostream>
#include <string>

#ifndef _SPELL_H_
#define _SPELL_H_
class Monster;
class Character;
class Spell 
{
	private:
		std::string Name = "";
		std::string SpellLine = "You have cast a spell.";
		int MinDamage = 1;
		int MaxDamage = 2;
		int ManaCost = 10;
		double KnockOut = 0;
		double SkeletonEffective = 1;
		double WizardEffective = 1;
		double ZombieEffective = 1;
		double SlimeEffective = 1;
		double DamageMult = 1;
	public:
		bool PlayerDamage = true;
		int SpellIdentity = 0;
		int Level = 1;
		int Turns = 0;
		Spell() { }
		Spell(std::string n) { Name = n; }
		Spell(int i) { SpellIdentity = i; }
		Spell(std::string n, std::string sl, int m, int M, int mc, double k, double se, double we, double ze, double slime, double dm, bool pd);
		
		std::string SeeName() { return Name; }
		std::string SeeSpellLine() { return SpellLine; }
		int SeeMinDamage() { return MinDamage; }
		int SeeMaxDamage() { return MaxDamage; }
		int SeeManaCost() { return ManaCost; }
		double SeeKnockOut() { return KnockOut; }
		double SeeSkeletonEffective() { return SkeletonEffective; }
		double SeeWizardEffective() { return WizardEffective; }
		double SeeZombieEffective() { return ZombieEffective; }
		double SeeSlimeEffective() { return SlimeEffective; }
		double SeeDamageMult() { return DamageMult; }

		void SkullCrusher();
		void DeadlyStab();
		void FlameBellow();
		void LightningBolt();
		void Heal();
		void BlockAttack();
		void MagicShield();
		
		void KnockMonsterOut(Monster &m, Character &c);
		void CastSpell(Character &c, Monster &m);
		int Damage(Character &c, Monster &m);

		int TotalLevel(Character& c);
		int AverageLevel(Character& c);
		int UpgradeLevelRequirement(Character& c);
		void LearnSpell(Character &c);
		int UpgradeCost();
		void UpgradeTo(Character& c, int u);
		void Upgrade(Character& c);
		void UpgradeMenu(Character& c);

		void Attributes(Character& c);
};

#endif