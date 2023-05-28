#pragma once
#include <iostream>
#include <cstdio>
#include <string>

#include "AncientSpirit.h"
#include "Monster.h"
#include "Leaderboard.h"

#ifndef _GAME_H_
#define _GAME_H_

extern bool PlayGame;

class Game
{
public:
	Game() { }

	int ScanForInt();
	std::string Intro();
	void IntroMessage();
	void NewGame(Character &c, Potion &p, Monster &m);
	void LoadGame(Character &c, Potion &p, Monster &m);
	void AskPlayGame(Character &c, Potion &p, Monster &m);
	void StartGame(Character &c, Potion &p, Monster &m, Leaderboard l, AncientSpirit a);
	bool IfMonsterSlain(Monster& m, Character& c, Potion& p, std::string adj);
	bool IfBossSlain(Monster& m, Character& c, Potion& p);
	void AttackBoss(Monster &m, Character &c, Potion &p, Leaderboard l);
	void AttackedByBoss(Monster &m, Character &c, Potion& p, Leaderboard l);
	void AttackedBySlime(Monster& m, Character& c, Potion& p, Leaderboard l);
	void Turn(Character& c, Monster& m, Potion &p, bool &run);
	void Turn(Monster& m, Character& c);
	void SlimeTurn(Monster& m, Character& c, bool& PlayerKnockedOut);
	void BattleOptions(Character c, Monster m);
	void NextFight(Monster& m, Character& c, Potion& p, Leaderboard l);
	void Attack(Monster &m, Character &c, std::string adj, Potion &p, Leaderboard l);
	void AttackShort(Monster &m, Character &c, std::string adj, Potion &p, Leaderboard l);
	void EternalOrbTutorial(Character& c);
	void EquipTutorial(Character& c);
	void EquipMenu(Character& c);
	void KeyPressed(Character &c, Monster &m, Potion &p, AncientSpirit a, Leaderboard l);
	void Options(Character &c);
	void Tutorial(Character &c, Monster &m, Potion &p);
	void TutorialAttack(Monster &m, Character &c, Potion &p);
	void ShopTutorial(Character &c, Monster &m, Potion &p);
	bool BossTutorial(Character& c, Monster& m, Potion& p);
	void SpellUpgradeTutorial(Character& c);
	void AncientTutorial(Character& c);
	void Use(Character& c, AncientSpirit a);
	void UseEternal(Character& c, AncientSpirit a);

	void Information(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l);
	void MonsterInformationIntro(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l);
	void MonsterInformation(Character c, Monster m, Potion p, AncientSpirit a, Leaderboard l);
};

#endif
