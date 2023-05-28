#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#include "Character.h"
#include "Potion.h"

#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

const int LEADERBOARDLENGTH = 10;

class Leaderboard
{
	public:
		Leaderboard() { }

		void DisplayLeaderboard();
		//void ChangeLeaderboard(Character c);
		void UpdateLeaderboard(Character &c);

		void SaveGame(Character c, Potion p, int x);
		std::vector<int> LoadSave(std::string Name);
		bool CheckValidSave(std::string Name);
		bool CheckAlive(std::string Name);

};

#endif