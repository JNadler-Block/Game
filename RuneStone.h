#pragma once
#include <iostream>
#include <string>

#ifndef _RUNESTONE_H_
#define _RUNESTONE_H_
class Monster;
class Character;
class RuneStone
{
private:
	std::string Name = "RuneStone";
	std::string Description = "";
	double ComboBonus = 1;
public:
	int RuneIdentity = 0;
	
	RuneStone() { }
	RuneStone(std::string n) { Name = n; }

	std::string SeeName() { return Name; }
	std::string SeeDescription() { return Description; }

	double SeeComboBonus() { return ComboBonus; }
	void ResetComboBonus() { ComboBonus = 1; }
	void IncreaseComboBonus() { ComboBonus += 0.15; }

	int DamageAbility(Character& c, Monster& m, int dmg);
	void Ability(Character& c, Monster& m, int dmg);

	void Vampiric();
	void VampiricAbility(Character& c, Monster& m, int dmg);

	void Combo();
	int ComboAbility(Character& c, int dmg);

	void SoulSiphon();
	void SoulSiphonAbility(Character& c, Monster& m, int dmg);

	void BoneShatter();
	void BoneShatterAbility(Character& c, Monster &m, int dmg);

	void CriticalStrike();
	int CriticalStrikeAbility(Character& c, int dmg);

	void Equip(Character& c, int i);

	void Initialize(Character& c, int id);

	void RuneStoneDrop(Character& c);
};

#endif
