#pragma once
#include <iostream>
#include <cstdio>

#include "Game.h"

#ifndef _SHOP_H_
#define _SHOP_H_

extern int SpellShardCost;

class Shop
{
public:
	Shop() { }

	int ScanForInt();
	void ShopLoop(Character &c, Monster &m, Potion &p, AncientSpirit a, Game g, Leaderboard l);
	bool Transaction(Character &c, Potion &p, int i);
	bool Transaction(Character &c, AncientSpirit a, int i);
	bool SpellShardTransaction(Character& c, int i);
	void SellPotion(Character &c, Potion &p, int i);
	int Amount(int cost, int i) { return cost * i; }
};

#endif
