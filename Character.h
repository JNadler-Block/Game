#pragma once

#include <vector>
#include <random>
#include <iomanip>

#include "Spell.h"
#include "RuneStone.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class Character
{
	private:
		std::string Name = "Henry";
		int MinDamage = 1;
		int MaxDamage = 4;
		int Health = 50;
		int CurrentHealth = Health;
		int Mana = 10;
		int CurrentMana = Mana;
		int DamageReduction = 0;
		double dr = 0;
		int Gold = 0;
		int Kills = 0;
		int BossKills = 0;
		int Potions = 0;
		int Short = 0;
		int AncientCount = 0;
		int EternalCount = 0;
		int SpellShards = 0;
		int DungeonLevel = 1;
		int KillsSinceDungeon = 0;
		bool DungeonLevelAvailable = false;
		bool BossAvailable = false;

	public:
		std::mt19937 rng{ std::random_device{}() };
		bool Blocking = false;
		bool SlimeFriend = false;
		std::vector<Spell> Spells;
		RuneStone Rune = RuneStone();
		std::vector<RuneStone> Inventory;
		int TempDamageReduction = 0;
		int TDRTurns = 0;
		// Constructors
		Character() { }
		Character(const std::string n) { Name = n; }
		Character(const std::string n, const int m, const int M,
			const int h, const int ch, const int ma,
			const int cm, const int damager, const int g, const int k,
			const int bk, const int p, const int s, const int a, const int e, const int sp,
			const int d, const int ksd, const bool ba, const bool da, const bool sf);

		// Accessor Functions
		std::string SeeName() { return Name; }
		int SeeMinDamage() { return MinDamage; }
		int SeeMaxDamage() { return MaxDamage; }
		int SeeHealth() { return Health; }
		int SeeCurrentHealth() { return CurrentHealth; }
		int SeeMana() { return Mana; }
		int SeeCurrentMana() { return CurrentMana; }
		int SeeDamageReduction() { return DamageReduction; }
		double SeeDR() { return dr; }
		int SeeGold() { return Gold; }
		int SeeKills() { return Kills; }
		int SeeBossKills() { return BossKills; }
		int SeePotions() { return Potions; }
		int SeeShort() { return Short; }
		int SeeAncientCount() { return AncientCount; }
		int SeeEternalCount() { return EternalCount; }
		int SeeSpellShards() { return SpellShards; }
		int SeeDungeonLevel() { return DungeonLevel; }
		int SeeKillsSinceDungeon() { return KillsSinceDungeon; }
		bool SeeDungeonLevelAvailable() { return DungeonLevelAvailable; }
		bool SeeBossAvailable() { return BossAvailable; }

		// Manipulation Functions
		void SetName(std::string n) { Name = n; }
		void SetMinDamage(int m) { MinDamage = m; }
		void SetMaxDamage(int m) { MaxDamage = m; }
		void SetHealth(int h) { Health = h; }
		void SetCurrentHealth(int ch) { CurrentHealth = ch; }
		void SetMana(int m) { Mana = m; }
		void SetCurrentMana(int cm) { CurrentMana = cm; }
		void SetDamageReduction(int damr) { DamageReduction = damr; }
		void SetDR(double damr) { dr = damr; }
		void SetGold(int g) { Gold = g; }
		void SetKills(int k) { Kills = k; }
		void SetBossKills(int bk) { BossKills = bk; }
		void SetPotions(int p) { Potions = p; }
		void SetShort(int s) { Short = s; }
		void SetAncientCount(int a) { AncientCount = a; }
		void SetEternalCount(int e) { EternalCount = e; }
		void SetSpellShards(int s) { SpellShards = s; }
		void SetDungeonLevel(int d) { DungeonLevel = d; }
		void SetKillsSinceDungeon(int ksd) { KillsSinceDungeon = ksd; }
		void SetDungeonLevelAvailable(bool da) { DungeonLevelAvailable = da; }
		void SetBossAvailable(bool ba) { BossAvailable = ba; }

		void IncreaseMinDamage(int m) { MinDamage += m; }
		void IncreaseMinDamage() { MinDamage++; }
		void IncreaseMaxDamage(int m) { MaxDamage += m; }
		void IncreaseMaxDamage() { MaxDamage++; }
		void IncreaseHealth(int h) { Health += h; }
		void IncreaseHealth() { Health++; }
		void IncreaseCurrentHealth(int h) { CurrentHealth += h; }
		void IncreaseCurrentHealth() { CurrentHealth++; }
		void IncreaseMana(int m) { Mana += m; }
		void IncreaseMana() { Mana++; }
		void IncreaseCurrentMana(int cm) { CurrentMana += cm; }
		void IncreaseCurrentMana() { CurrentMana++; }
		void IncreaseDamageReduction(int dr) { DamageReduction += dr; }
		void IncreaseDamageReduction() { DamageReduction++; }
		void IncreaseGold(int g) { Gold += g; }
		void IncreaseGold() { Gold++; }
		void IncreaseKills(int k) { Kills += k; }
		void IncreaseKills() { Kills++; }
		void IncreaseBossKills(int bk) { BossKills += bk; }
		void IncreaseBossKills() { BossKills++; }
		void IncreasePotions(int p) { Potions += p; }
		void IncreasePotions() { Potions++; }
		void IncreaseAncientCount(int a) { AncientCount += a; }
		void IncreaseAncientCount() { AncientCount++; }
		void IncreaseEternalCount(int e) { EternalCount += e; }
		void IncreaseEternalCount() { EternalCount++; }
		void IncreaseSpellShards(int s) { SpellShards += s; }
		void IncreaseSpellShards() { SpellShards++; }
		void IncreaseDungeonLevel(int d) { DungeonLevel += d; }
		void IncreaseDungeonLevel() { DungeonLevel++; }
		void IncreaseKillsSinceDungeon(int ksd) { KillsSinceDungeon += ksd; }
		void IncreaseKillsSinceDungeon() { KillsSinceDungeon++; }

		void DecreaseMinDamage(int m) { MinDamage -= m; }
		void DecreaseMinDamage() { MinDamage--; }
		void DecreaseMaxDamage(int m) { MaxDamage -= m; }
		void DecreaseMaxDamage() { MaxDamage--; }
		void DecreaseHealth(int h) { Health -= h; }
		void DecreaseHealth() { Health--; }
		void DecreaseCurrentHealth(int h) { CurrentHealth -= h; }
		void DecreaseCurrentHealth() { CurrentHealth--; }
		void DecreaseMana(int m) { Mana -= m; }
		void DecreaseMana() { Mana--; }
		void DecreaseCurrentMana(int cm) { CurrentMana -= cm; }
		void DecreaseCurrentMana() { CurrentMana--; }
		void DecreaseDamageReduction(int dr) { DamageReduction -= dr; }
		void DecreaseDamageReduction() { DamageReduction--; }
		void DecreaseGold(int g) { Gold -= g; }
		void DecreaseGold() { Gold--; }
		void DecreaseKills(int k) { Kills -= k; }
		void DecreaseKills() { Kills--; }
		void DecreasePotions(int p) { Potions -= p; }
		void DecreasePotions() { Potions--; }
		void DecreaseAncientCount(int a) { AncientCount -= a; }
		void DecreaseAncientCount() { AncientCount--; }
		void DecreaseEternalCount(int e) { EternalCount -= e; }
		void DecreaseEternalCount() { EternalCount--; }
		void DecreaseSpellShards(int s) { SpellShards -= s; }
		void DecreaseSpellShards() { SpellShards--; }
		void DecreaseDungeonLevel(int d) { DungeonLevel -= d; }
		void DecreaseDungeonLevel() { DungeonLevel--; }

		// Other Functions
		void DamageReductionCalculator();
		void Attributes();
		void BossFightAttributes();
		void InventoryDisplay();
};

#endif

